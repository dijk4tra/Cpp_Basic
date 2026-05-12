#include <iostream>
#include <cstring>

using std::cout;
using std::endl;
using std::ostream;

class String {
public:
    String(const char * pstr)
    : _size(strlen(pstr))
    {
        if (_size < 16) {
            // 使用本地数组，最多存 15 个字符 + '\0'
            _capacity = 15;
            strcpy(_buffer._local, pstr);
        } else {
            // 使用堆空间
            _capacity = _size;
            _buffer._pointer = new char[_capacity + 1]();
            strcpy(_buffer._pointer, pstr);
        }
    }

    ~String() {
        if (_capacity > 15) {
            delete [] _buffer._pointer;
            _buffer._pointer = nullptr;
        }
    }

    char & operator[](size_t idx) {
        if (_capacity <= 15) {
            return _buffer._local[idx];
        } else {
            return _buffer._pointer[idx];
        }
    }

    friend
    ostream & operator<<(ostream & os, const String & rhs);

private:
    union Buffer {
        char * _pointer;
        char _local[16];
    };

    size_t _size;
    size_t _capacity;
    Buffer _buffer;
};

ostream & operator<<(ostream & os, const String & rhs) {
    if (rhs._capacity <= 15) {
        os << rhs._buffer._local;
    } else {
        os << rhs._buffer._pointer;
    }

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