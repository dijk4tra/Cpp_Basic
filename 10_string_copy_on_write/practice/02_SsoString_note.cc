#include <iostream>
#include <cstring>
#include <stdexcept>

using std::cout;
using std::endl;
using std::ostream;
using std::out_of_range;

class String {
public:
    /*
        构造函数：
        根据传入字符串的长度，决定使用本地数组 _local，
        还是使用堆空间 _pointer。

        SSO 思想：
        - 短字符串：直接存在对象内部的 _local[16] 中
        - 长字符串：申请堆内存，由 _pointer 指向
    */
    String(const char * pstr)
    : _size(strlen(pstr))
    {
        /*
            _local[16] 最多存 15 个有效字符，
            因为最后一个位置要留给字符串结束符 '\0'。

            因此：
            - _size <= 15 时，使用 _local
            - _size > 15 时，使用 _pointer
        */
        if (_size <= 15) {
            /*
                这里约定：
                _capacity == 15 表示当前对象使用 _local 存储。

                _capacity 表示不包含 '\0' 的最大可容纳字符数。
            */
            _capacity = 15;

            /*
                把 pstr 中的内容复制到本地数组中。
                strcpy 会连同 '\0' 一起复制。
            */
            strcpy(_buffer._local, pstr);
        } else {
            /*
                长字符串无法放进 _local[16]，
                因此需要在堆上申请空间。

                这里简单处理：
                容量刚好等于字符串长度。
                例如长度为 16，就申请 17 个 char，
                其中 16 个放有效字符，最后 1 个放 '\0'。
            */
            _capacity = _size;

            /*
                new char[_capacity + 1]：
                +1 是为了存放 '\0'。

                后面的 () 会把数组初始化为 0，
                虽然后面 strcpy 会覆盖内容，
                但这样写比较安全。
            */
            _buffer._pointer = new char[_capacity + 1]();

            /*
                把字符串内容复制到堆空间中。
            */
            strcpy(_buffer._pointer, pstr);
        }
    }

    /*
        拷贝构造函数：
        用一个已有的 String 对象初始化新对象。

        例如：
            String s1("hello");
            String s2 = s1;

        如果原对象使用 _local，新对象也使用自己的 _local。
        如果原对象使用 _pointer，新对象必须重新申请堆空间，
        不能直接拷贝指针地址，否则会出现浅拷贝问题。
    */
    String(const String & rhs)
    : _size(rhs._size)
    , _capacity(rhs._capacity)
    {
        if (rhs.usingLocal()) {
            /*
                rhs 使用本地数组，
                当前对象也使用自己的本地数组。
            */
            strcpy(_buffer._local, rhs._buffer._local);
        } else {
            /*
                rhs 使用堆空间，
                当前对象需要重新申请一块堆空间，
                然后复制字符串内容。
            */
            _buffer._pointer = new char[_capacity + 1]();
            strcpy(_buffer._pointer, rhs._buffer._pointer);
        }
    }

    /*
        赋值运算符：
        用一个已有对象给另一个已经存在的对象赋值。

        例如：
            String s1("hello");
            String s2("world");
            s2 = s1;

        注意：
        赋值运算符要考虑三个问题：
        1. 自赋值：s1 = s1;
        2. 原对象如果使用堆空间，需要先释放旧空间
        3. 根据 rhs 的存储方式重新复制内容
    */
    String & operator=(const String & rhs) {
        /*
            防止自赋值。

            如果没有这个判断，s1 = s1 时，
            可能先 delete 掉自己的堆空间，
            后面又从已经释放的空间里读取数据。
        */
        if (this != &rhs) {
            /*
                如果当前对象原来使用的是堆空间，
                赋新值之前要先释放旧的堆空间，
                防止内存泄漏。
            */
            if (!usingLocal()) {
                delete [] _buffer._pointer;
                _buffer._pointer = nullptr;
            }

            /*
                复制基本信息。
            */
            _size = rhs._size;
            _capacity = rhs._capacity;

            /*
                根据 rhs 的存储方式进行复制。
            */
            if (rhs.usingLocal()) {
                strcpy(_buffer._local, rhs._buffer._local);
            } else {
                _buffer._pointer = new char[_capacity + 1]();
                strcpy(_buffer._pointer, rhs._buffer._pointer);
            }
        }

        /*
            返回当前对象本身，支持连续赋值：

                s3 = s2 = s1;
        */
        return *this;
    }

    /*
        析构函数：
        对象生命周期结束时自动调用。

        如果当前对象使用堆空间，则需要 delete[]。
        如果使用 _local，则不需要手动释放。
    */
    ~String() {
        if (!usingLocal()) {
            delete [] _buffer._pointer;
            _buffer._pointer = nullptr;
        }
    }

    /*
        下标访问运算符：
        允许像数组一样访问和修改字符。

        例如：
            String s("hello");
            s[0] = 'H';

        返回 char&，所以既可以读，也可以写。
    */
    char & operator[](size_t idx) {
        /*
            做一个边界检查。
            idx >= _size 表示越界。

            注意：
            这里不允许访问 '\0' 的位置。
            如果想允许访问 '\0'，判断可以改成 idx > _size。
        */
        if (idx >= _size) {
            throw out_of_range("String subscript out of range");
        }

        if (usingLocal()) {
            return _buffer._local[idx];
        } else {
            return _buffer._pointer[idx];
        }
    }

    /*
        const 版本的 operator[]：
        当对象是 const String 时，也可以通过下标读取字符。

        例如：
            const String s("hello");
            cout << s[0] << endl;

        返回 const char&，只能读，不能改。
    */
    const char & operator[](size_t idx) const {
        if (idx >= _size) {
            throw out_of_range("String subscript out of range");
        }

        if (usingLocal()) {
            return _buffer._local[idx];
        } else {
            return _buffer._pointer[idx];
        }
    }

    /*
        返回字符串长度，不包含 '\0'。
    */
    size_t size() const {
        return _size;
    }

    /*
        返回当前容量，不包含 '\0'。

        在这个简单实现中：
        - 短字符串容量固定为 15
        - 长字符串容量等于字符串长度
    */
    size_t capacity() const {
        return _capacity;
    }

    /*
        判断当前是否使用 _local 存储。

        这是我们自己约定的判断规则：
        - _capacity <= 15：使用 _local
        - _capacity > 15：使用 _pointer

        因为 _local[16] 最多能存 15 个有效字符。
    */
    bool usingLocal() const {
        return _capacity <= 15;
    }

    /*
        返回 C 风格字符串指针。

        这样可以统一拿到字符串内容，
        不需要每次在外面判断使用的是 _local 还是 _pointer。
    */
    const char * c_str() const {
        if (usingLocal()) {
            return _buffer._local;
        } else {
            return _buffer._pointer;
        }
    }

    /*
        输出运算符重载。
        让 String 对象可以直接用 cout 输出。

        例如：
            String s("hello");
            cout << s << endl;
    */
    friend
    ostream & operator<<(ostream & os, const String & rhs);

private:
    /*
        union 联合体：
        _pointer 和 _local 共用同一块内存。

        使用场景：
        1. 短字符串时：
            使用 _local[16] 存储字符内容。
        2. 长字符串时：
            使用 _pointer 指向堆空间。

        注意：
        union 里同一时刻只能认为一个成员是有效的。
    */
    union Buffer {
        char * _pointer;
        char _local[16];
    };

    /*
        字符串长度，不包含 '\0'。
    */
    size_t _size;

    /*
        当前容量，不包含 '\0'。

        本实现中还用 _capacity 来判断当前存储方式：
        - _capacity <= 15：使用 _local
        - _capacity > 15：使用 _pointer
    */
    size_t _capacity;

    /*
        实际存储区域。
        可能是本地数组，也可能是堆指针。
    */
    Buffer _buffer;
};

/*
    operator<< 的实现。

    这里直接调用 c_str()，
    避免重复判断 usingLocal()。
*/
ostream & operator<<(ostream & os, const String & rhs) {
    os << rhs.c_str();
    return os;
}

void test1() {
    String str1("hello");
    String str2("hello,world!!!!!");

    cout << "str1 = " << str1 << endl;
    cout << "str2 = " << str2 << endl;

    str1[0] = 'H';
    str2[0] = 'H';

    cout << "修改后：" << endl;
    cout << "str1 = " << str1 << endl;
    cout << "str2 = " << str2 << endl;
}

int main() {
    test1();
    return 0;
}