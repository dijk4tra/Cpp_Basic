#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

/**
 * std::string 常见操作
 *
 * string 是 C++ 标准库提供的字符串类型，
 * 相比 C 风格字符串 char * / char[]，
 * string 使用起来更加安全、方便。
 *
 * 常见操作包括：
 * 1. 元素访问
 *    at()
 *    operator[]
 *    迭代器
 *
 * 2. 容量相关
 *    size()
 *    empty()
 *
 * 3. 插入和追加
 *    insert()
 *    push_back()
 *    append()
 *
 * 4. 删除
 *    erase()
 *
 * 5. 拼接
 *    operator+
 *
 * 6. 截取
 *    substr()
 *
 * 7. 查找
 *    find()
 *
 * 8. 遍历
 *    下标遍历
 *    范围 for 遍历
 *    迭代器遍历
 */

// 常见的字符串操作
void test1()
{
    // 创建 string 对象 str，并初始化为 "abcdef"
    string str {"abcdef"};

    // 元素访问

    /**
     * at(pos)
     *
     * 作用：
     * 访问指定下标位置的字符。
     *
     * 注意：
     * at() 会进行越界检查。
     * 如果下标越界，会抛出异常。
     *
     * 这里 str.at(0) 访问的是第 0 个字符，
     * 也就是 'a'。
     */
    cout << str.at(0) << endl;

    /**
     * operator[]
     *
     * 作用：
     * 也可以通过下标访问字符串中的字符。
     *
     * 注意：
     * operator[] 通常不会进行越界检查。
     * 如果下标越界，可能导致未定义行为。
     *
     * 这里 str[1] 访问的是第 1 个字符，
     * 也就是 'b'。
     */
    cout << str[1] << endl;

    /**
     * 通过迭代器访问字符串中的字符
     *
     * begin() 返回指向第一个字符的迭代器。
     * 迭代器可以理解为一种“类似指针”的对象，
     * 可以通过 *it 访问它指向的元素。
     */
    auto it = str.begin();

    // it 向后移动 2 个位置
    // 原来指向 'a'，移动后指向 'c'
    it += 2;

    // 解引用迭代器，得到它当前指向的字符
    cout << *it << endl;

    // 容量

    /**
     * size()
     *
     * 返回字符串中字符的个数。
     * "abcdef" 一共有 6 个字符，
     * 所以这里输出 6。
     */
    cout << str.size() << endl;

    /**
     * empty()
     *
     * 判断字符串是否为空。
     *
     * 返回值：
     * true  表示字符串为空
     * false 表示字符串不为空
     *
     * cout 输出 bool 值时，
     * 默认 true 输出 1，
     * false 输出 0。
     */
    cout << str.empty() << endl;

    /**
     * c_str()
     *
     * 返回 string 内部保存的 C 风格字符串。
     *
     * C 风格字符串本质上是：
     * 以 '\0' 结尾的字符数组。
     *
     * 当需要把 string 传给只接收 const char * 的函数时，
     * 可以使用 c_str()。
     */
    cout << str.c_str() << endl;
}

// 插入insert
void test2()
{   
    /**
     * insert()
     *
     * 作用：
     * 在 string 的指定位置插入内容。
     *
     * 可以插入：
     * 1. string 对象
     * 2. C 风格字符串
     * 3. 字符
     * 4. 某个范围内的字符
     */

    // insert : 插入string对象,C风格字符串....
    string str {"hello"};
    cout << str << endl;

    string str2 {"abc"};

    // 在 str 的下标 1 的位置插入 str2
    // 原字符串：hello
    // 下标 1 的位置是字符 'e' 前面
    // 插入后：habcello
    str.insert(1, str2);
    cout << str << endl;

    // 在 str 的下标 1 的位置插入 C 风格字符串 "xyz"
    str.insert(1, "xyz");
    cout << str << endl;

    cout << "--------" << endl;
    
    /**
     * push_back()
     *
     * 作用：
     * 在字符串末尾追加一个字符。
     *
     * 注意：
     * push_back 一次只能追加一个字符，
     * 不能直接追加字符串。
     */
    str2.push_back('A');
    cout << str2 << endl;

    /**
     * append()
     *
     * 作用：
     * 在字符串末尾追加内容。
     *
     * append 可以追加：
     * 1. string 对象
     * 2. C 风格字符串
     * 3. 某个迭代器范围内的字符
     */
    string str3 {"bbb"};

    // 将 str3 的内容追加到 str2 的末尾
    str2.append(str3);
    cout << str2 << endl;

    // 将 str 的 [begin(), end()) 范围中的字符追加到 str2 的末尾
    // 这个范围是左闭右开区间，包含 begin()，不包含 end()
    str2.append(str.begin(), str.end());
    cout << str2 << endl;
}

// 删除erase
void test3()
{
    string str {"abcdef"};

    // begin() 指向第一个字符 'a'
    auto it = str.begin();

    // 迭代器向后移动 2 个位置，指向 'c'
    it += 2;

    /**
     * erase(iterator)
     *
     * 作用：
     * 删除迭代器指向的那个字符。
     *
     * 返回值：
     * 返回一个新的迭代器，
     * 指向被删除元素后面的那个位置。
     *
     * 当前 it 指向 'c'，
     * 删除 'c' 后，字符串变成 "abdef"，
     * 返回的 it2 指向 'd'。
     */
    auto it2 = str.erase(it);
    cout << str << endl;
    cout << *it2 << endl;

    cout << "--------" << endl;

    /**
     * erase(first, last)
     *
     * 作用：
     * 删除一个迭代器范围内的字符。
     *
     * 删除区间为 [first, last)，
     * 也就是左闭右开区间。
     */
    auto it3 = str.begin();
    it3 += 2;

    // 删除从 it3 指向的位置到字符串末尾之前的所有字符
    // 当前 str 是 "abdef"
    // it3 指向 'd'
    // 删除 [it3, str.end()) 后，剩下 "ab"
    str.erase(it3, str.end());

    cout << str << endl;
}

// 字符串的拼接
void test4()
{
    string str {"abc"};
    string str2 {"abc"};

    /**
     * operator+
     *
     * 作用：
     * 拼接字符串，并生成一个新的 string 对象。
     *
     * 注意：
     * str + str2 不会修改 str 和 str2 本身，
     * 而是产生一个新的拼接结果。
     */

    // string + string
    string str3 = str + str2;
    cout << str3 << endl;

    // string + C 风格字符串
    string str4 = str + "xyz";
    cout << str4 << endl;

    /**
     * 这里 "A" 是字符串字面值，
     * 类型不是 char，而是 const char[2]，
     * 里面包含字符 'A' 和结尾符 '\0'。
     *
     * 所以 str + "A" 是 string 和 C 风格字符串拼接。
     */
    string str5 = str + "A";
    cout << str5 << endl;
}

// 字符串的截取
void test5()
{
    string str {"abcdef"};

    /**
     * substr(pos, len)
     *
     * 作用：
     * 从字符串中截取一部分内容，
     * 返回一个新的 string 对象。
     *
     * 参数：
     * pos 表示开始截取的位置。
     * len 表示要截取的字符个数。
     *
     * 注意：
     * substr 不会修改原字符串。
     */
    string str2 = str.substr(0, 3);
    cout << str2 << endl;
    
    /**
     * substr(pos)
     *
     * 如果只传一个参数，
     * 表示从 pos 位置开始，
     * 一直截取到字符串末尾。
     *
     * 这里从下标 2 开始截取，
     * 得到 "cdef"。
     */
    string str3 = str.substr(2);
    cout << str3 << endl; 
}

// 字符串的查找
void test6()
{
    string str {"abcdef"};

    /**
     * find()
     *
     * 作用：
     * 在字符串中查找指定内容第一次出现的位置。
     *
     * 返回值：
     * 如果找到了，返回第一次出现位置的下标。
     * 如果没有找到，返回 string::npos。
     *
     * 注意：
     * find() 的返回类型通常是 string::size_type，
     * 它是无符号整数类型。
     *
     * 这里为了演示，使用 int 接收结果。
     * 实际开发中更推荐写成：
     *
     * string::size_type index = str.find("de");
     * if(index == string::npos) {
     *     ...
     * }
     */
    int index = str.find("de");

    /**
     * 因为这里 index 是 int，
     * 如果没有找到，string::npos 转成 int 后通常会变成 -1，
     * 所以可以用 index < 0 判断。
     *
     * 但这种写法不够严谨，
     * 更推荐使用 index == string::npos。
     */
    if(index < 0){
        cout << "not found" << endl;
    }else{
        cout << "index: " << index << endl;
    }
}

// 字符串的遍历
void test7()
{
    string str = "abc";

    /**
     * 字符串遍历方式：
     * 1. 下标遍历
     * 2. 范围 for 遍历
     * 3. 迭代器遍历
     */

    // for i 循环
    /**
     * 使用下标访问每一个字符。
     *
     * i 从 0 开始，
     * 只要 i 小于 str.size() 就继续循环。
     *
     * 注意：
     * str.size() 的返回类型是无符号整数类型，
     * 这里用 int 接收在学习阶段可以理解，
     * 实际开发中也可以写成：
     *
     * for(size_t i = 0; i < str.size(); ++i)
     */
    for(int i = 0; i < str.size(); i++){
        /* cout << str[i] << endl; */

        // at(i) 访问第 i 个字符，并且会进行越界检查
        cout << str.at(i) << endl;
    }

    cout << "---------" << endl;

    // foreach增强for循环
    /**
     * 范围 for 循环
     *
     * 语法：
     * for(元素类型 变量名 : 容器)
     * {
     *     循环体
     * }
     *
     * 每次循环时，
     * ch 会依次引用 str 中的每一个字符。
     *
     * 这里使用 char & ch，
     * 表示 ch 是字符的引用。
     * 如果在循环中修改 ch，
     * 就会修改字符串中对应的字符。
     *
     * 如果只是读取字符，也可以写成：
     * for(char ch : str)
     * 或者：
     * for(const char & ch : str)
     */
    /* for(char & ch : str){ */
    for(char & ch : str){
        cout << ch << endl;
    }

    cout << "---------" << endl;

    // 迭代器遍历
    /**
     * 使用迭代器遍历 string。
     *
     * begin() 返回指向第一个字符的迭代器。
     * end() 返回指向最后一个字符后一个位置的迭代器。
     *
     * 注意：
     * end() 指向的位置不是有效字符，
     * 它只是作为遍历结束的标记。
     */
    auto itBegin = str.begin();

    // 只要迭代器还没有走到 end()，就继续遍历
    for( ; itBegin != str.end(); ++itBegin){
        // 解引用迭代器，访问当前字符
        cout << *itBegin << endl;
    }

    // 或者使用while循环,条件为 it != end()
}

int main(int argc, char *argv[])
{
    /**
     * main 函数是程序入口。
     *
     * 当前只有 test7() 没有被注释，
     * 所以程序运行时只会执行 test7()。
     *
     * 如果想测试其它函数，
     * 可以取消对应函数调用前面的注释。
     */

    /* test1(); */
    /* test2(); */
    /* test3(); */
    /* test4(); */
    /* test5(); */
    /* test6(); */
    test7();

    return 0;
}