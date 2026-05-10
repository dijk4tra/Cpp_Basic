#include <iostream>
#include <cstring>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <string>

using namespace std;

class String
{
public:
    // 默认构造函数
    // 创建一个空字符串
    String();
    
    // 带参构造函数
    // 用C风格字符串初始化String对象
    String(const char *);
    
    // 拷贝构造函数
    // 用一个已有String对象初始化新对象
    String(const String &);

    // 析构函数
    // 释放对象内部申请的堆内存
    ~String();

    // 拷贝复制运算符
    // 用一个已有 String 对象给当前对象赋值
    String &operator=(const String &);

    // 用C风格字符串给当前对象赋值
    String &operator=(const char *);
    
    // 拼接另一个 String 对象
    String &operator+=(const String &);

    // 拼接另一个C风格字符串
    String &operator+=(const char *);

    // 下标访问运算符
    // 非const对象可以通过它修改字符
    char &operator[](int index);

    // const对象只能读取字符,不能修改字符
    const char &operator[](int index) const;

    // 返回字符串长度,不包括'\0'
    int size() const;

    // 返回内部C风格字符串的指针
    const char* c_str() const;

    // 判断两个字符串是否相等
    friend bool operator==(const String &, const String &);

    // 判断两个字符串是否不相等
    friend bool operator!=(const String &, const String &);

    // 字典序比较
    friend bool operator<(const String &, const String &);
    friend bool operator>(const String &, const String &);
    friend bool operator<=(const String &, const String &);
    friend bool operator>=(const String &, const String &);

    // 输出运算符
    friend ostream &operator<<(ostream &os, const String &s);

    // 输入运算符
    friend istream &operator>>(istream &is, String &s);

private:
    char * _pstr;
};


// 默认构造函数
// 创建一个空字符串
String::String()
{
    // 分配1个字符空间用于保存字符串结束符 '\0'
    _pstr = new char[1];
    _pstr[0] = '\0';
}

// 带参构造函数
// 允许这样创建对象：String s("hello");
String::String(const char *str)
{
    // 如果传入的是空指针 nullptr
    // 把它当作空字符串处理
    if(str == nullptr)
    {
        _pstr = new char[1];
        _pstr[0] = '\0';
    }else{
        // strlen(str) 计算字符串长度，不包括 '\0'
        // 所以申请空间时必须 +1，用来存放 '\0'
        _pstr = new char[strlen(str) + 1];
        //  strcpy 会把字符串内容和最后的 '\0' 一起复制过去
        strcpy(_pstr, str);
    }
}

// 拷贝构造函数
// 用一个已有对象初始化新对象
// 例如：String s2(s1);
String::String(const String &rhs)
{   
    // 申请一块新的内存
    // 大小和 rhs 中的字符串一样
    _pstr = new char[strlen(rhs._pstr) + 1];
    // 把 rhs 的字符串内容复制到当前对象中
    strcpy(_pstr, rhs._pstr);
}

// 析构函数
String::~String()
{
    // 由于前面使用 new char[] 申请内存
    // 所以这里必须使用 delete[]
    delete[] _pstr;
    _pstr = nullptr;
}

// 赋值运算符
// 赋值运算符函数,例如: s1 = s2;
String & String::operator=(const String &rhs)
{
    // 防止自赋值
    // 例如：s1 = s1;
    if(this != &rhs)
    {
        // 先申请新空间
        char *tmp = new char[strlen(rhs._pstr) + 1];
        // 把 rhs 的字符串复制到 tmp 中
        strcpy(tmp, rhs._pstr);
        // 释放当前对象原来的字符串空间
        delete[] _pstr;
        // 让当前对象指向新的字符串空间
        _pstr = tmp;
    }
    
    // 返回当前对象本身
    // 这样可以支持连续赋值：s1 = s2 = s3;
    return *this;
}

// 使用 C 风格字符串给 String 对象赋值
// 例如：s1 = "hello";
String & String::operator=(const char *str)
{
    // 如果传入 nullptr，就当作空字符串处理
    if(str == nullptr)
    {
        str = "";
    }
    // 先申请新空间
    char *tmp = new char[strlen(str) + 1];
    // 复制字符串内容
    strcpy(tmp, str);
    // 释放原来的空间
    delete[] _pstr;
    // 指向新的空间
    _pstr = tmp;

    return *this;
}

// 拼接运算符
// 把另一个 String 对象拼接到当前对象后面
// 例如：s1 += s2;
String &String::operator+=(const String &rhs)
{
    // 当前字符串的长度
    int len1 = strlen(_pstr);
    // 右边字符串的长度
    int len2 = strlen(rhs._pstr);
    //home/lws/my_project/Cpp_ProgrammingTraining/08_operator_overload/practice/ 新字符串的长度=len1+len2+1
    char *tmp = new char[len1 + len2 + 1];
    // 先复制当前字符串到tmp
    strcpy(tmp, _pstr);
    // 再把rhs的字符串追加到tmp后面
    strcat(tmp, rhs._pstr);
    // 释放原来的空间
    delete [] _pstr;
    // 当前对象指向拼接后的新字符串
    _pstr = tmp;

    return *this;
}

// 拼接 C 风格字符串
// 例如：s1 += " world";
String &String::operator+=(const char *str)
{
    // 如果 str 是 nullptr，直接不做任何操作
    if(str==nullptr)
    {
        return *this;
    }
    
    int len1 = strlen(_pstr);
    int len2 = strlen(str);
    
    char *tmp = new char[len1 + len2 + 1];

    strcpy(tmp, _pstr);
    strcat(tmp, str);

    delete[] _pstr;
    _pstr = tmp;

    return *this;
}

// 下标访问运算符
// 非 const 对象调用这个版本
// 可以修改字符
char &String::operator[](int index)
{
    // 下标范围是 0 到 size() - 1
    // 如果 index >= size()，说明越界
    if(index >= size())
    {
        throw out_of_range("String index out of range");
    }
    // 返回字符的引用
    // 因为返回的是引用，所以可以修改
    return _pstr[index];
}

// const 对象调用这个版本
// 只能读取，不能修改
const char &String::operator[](int index) const
{
    if (index >= size())
    {
        throw std::out_of_range("String index out of range");
    }
    return _pstr[index];
}

// 返回字符串长度
// 不包括最后的 '\0'
int String::size() const
{
    return strlen(_pstr);
}

// 返回内部 C 风格字符串
const char* String::c_str() const
{
    return _pstr;
}

// 比较运算符
// strcmp(a, b) == 0   表示 a 和 b 内容相等
// strcmp(a, b) < 0    表示 a 按字典序小于 b
// strcmp(a, b) > 0    表示 a 按字典序大于 b
bool operator==(const String &lhs, const String &rhs)
{
    return strcmp(lhs._pstr, rhs._pstr) == 0;
}

bool operator!=(const String &lhs, const String &rhs)
{
    return !(lhs == rhs);
}

bool operator<(const String &lhs, const String &rhs)
{
    return strcmp(lhs._pstr, rhs._pstr) < 0;
}

bool operator>(const String &lhs, const String &rhs)
{
    return strcmp(lhs._pstr, rhs._pstr) > 0;
}

bool operator<=(const String &lhs, const String &rhs)
{
    return !(lhs > rhs);
}

bool operator>=(const String &lhs, const String &rhs)
{
    return !(lhs < rhs);
}

// 输入输出运算符
// 输出运算符
ostream &operator<<(ostream &os, const String &s)
{
    os << s._pstr;
    return os;
}

//输入运算符
istream &operator>>(istream &is, String &s)
{
    // 临时缓冲区
    // 这里最多读取 1023 个有效字符
    // 最后一个位置留给 '\0'
    char buffer[1024];

    // is >> buffer 会读取一个单词
    // 遇到空格、Tab、换行会停止
    if(is >> buffer)
    {
        // 调用 operator=(const char *)
        // 把 buffer 中的内容赋值给 s
        s = buffer;
    }
    
    return is;
}

// 加法运算符
// String + String
String operator+(const String &lhs, const String &rhs)
{
    // 先用 lhs 创建一个临时对象
    String tmp(lhs);
    // 再把 rhs 拼接到 tmp 后面
    tmp += rhs;
    // 返回拼接后的新对象
    return tmp;
}

// String + const char *
String operator+(const String &rhs, const char *lhs)
{
    String tmp(lhs);
    tmp += rhs;
    return tmp;
}


int main(int argc, char *argv[])
{   
    std::cout << "===== 1. 构造函数测试 =====" << std::endl;

    String s1;
    String s2("hello");
    String s3(s2);

    std::cout << "s1 = [" << s1 << "], size = " << s1.size() << std::endl;
    std::cout << "s2 = [" << s2 << "], size = " << s2.size() << std::endl;
    std::cout << "s3 = [" << s3 << "], size = " << s3.size() << std::endl;


    std::cout << "\n===== 2. 赋值运算符测试 =====" << std::endl;

    s1 = s2;
    std::cout << "执行 s1 = s2 后，s1 = " << s1 << std::endl;

    s1 = "world";
    std::cout << "执行 s1 = \"world\" 后，s1 = " << s1 << std::endl;

    s1 = s1;
    std::cout << "执行自赋值 s1 = s1 后，s1 = " << s1 << std::endl;


    std::cout << "\n===== 3. 拼接运算符 += 测试 =====" << std::endl;

    s1 += " ";
    s1 += s2;

    std::cout << "执行 s1 += \" \"; s1 += s2; 后，s1 = " << s1 << std::endl;


    std::cout << "\n===== 4. 加法运算符 + 测试 =====" << std::endl;

    String s4 = s2 + String(" cpp");
    String s5 = s2 + " language";
    String s6 = "say " + s2;

    std::cout << "s2 + String(\" cpp\") = " << s4 << std::endl;
    std::cout << "s2 + \" language\" = " << s5 << std::endl;
    std::cout << "\"say \" + s2 = " << s6 << std::endl;


    std::cout << "\n===== 5. 下标访问测试 =====" << std::endl;

    std::cout << "s2[0] = " << s2[0] << std::endl;

    s2[0] = 'H';
    std::cout << "修改 s2[0] = 'H' 后，s2 = " << s2 << std::endl;

    try
    {
        std::cout << "访问 s2[100]：" << std::endl;
        std::cout << s2[100] << std::endl;
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "捕获异常：" << e.what() << std::endl;
    }


    std::cout << "\n===== 6. 比较运算符测试 =====" << std::endl;

    String a("abc");
    String b("abd");
    String c("abc");

    std::cout << std::boolalpha;

    std::cout << "a == b: " << (a == b) << std::endl;
    std::cout << "a == c: " << (a == c) << std::endl;
    std::cout << "a != b: " << (a != b) << std::endl;
    std::cout << "a < b: " << (a < b) << std::endl;
    std::cout << "a > b: " << (a > b) << std::endl;
    std::cout << "a <= c: " << (a <= c) << std::endl;
    std::cout << "a >= c: " << (a >= c) << std::endl;


    std::cout << "\n===== 7. c_str 测试 =====" << std::endl;

    const char *p = s2.c_str();
    std::cout << "s2.c_str() = " << p << std::endl;


    std::cout << "\n===== 8. 输入运算符测试 =====" << std::endl;

    String input;
    std::cout << "请输入一个单词：";
    std::cin >> input;
    std::cout << "你输入的是：" << input << std::endl;

    return 0;
}

