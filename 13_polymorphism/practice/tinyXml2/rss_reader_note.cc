#include "tinyxml2.h"   // 引入 tinyxml2 库的头文件，用来解析 XML/RSS 文件

#include <iostream>     // 标准输入输出，例如 cout、cerr
#include <fstream>      // 文件输出流 ofstream，用来生成 pagelib.txt
#include <vector>       // vector 容器，用来保存多个 RSS item
#include <string>       // string 字符串类型
#include <regex>        // 正则表达式，用来去除 HTML 标签
#include <stdexcept>    // 标准异常类 runtime_error

using std::string;
using std::vector;

// 使用 tinyxml2 命名空间，这样后面就可以直接写 XMLDocument、XMLElement
using namespace tinyxml2;

/*
 * RssItem 用来保存一篇 RSS 文章的信息
 *
 * 每一个 <item> 节点对应一个 RssItem 对象
 *
 * 例如 RSS 中的一篇文章大概长这样：
 *
 * <item>
 *     <title>文章标题</title>
 *     <link>文章链接</link>
 *     <description>文章摘要</description>
 *     <content:encoded>文章正文</content:encoded>
 * </item>
 */
struct RssItem {
    string title;        // 文章标题
    string link;         // 文章链接
    string description;  // 文章摘要
    string content;      // 文章正文内容
};

/*
 * getText 函数：
 *
 * 功能：
 *     从某个 XML 元素 parent 中查找指定名字的子元素，
 *     并返回该子元素中的文本内容。
 *
 * 参数：
 *     parent : 父节点，例如 <item> 节点
 *     name   : 要查找的子节点名字，例如 "title"、"link"
 *
 * 返回值：
 *     如果找到对应子节点并且有文本，则返回文本内容；
 *     如果没找到，或者文本为空，则返回空字符串 ""。
 *
 * 举例：
 *     getText(item, "title")
 *     表示从 item 节点中找到 <title> 标签，并取出里面的文字。
 */
static string getText(XMLElement *parent, const char *name)
{
    // 如果父节点为空，说明传入参数有问题，直接返回空字符串
    if (!parent) {
        return "";
    }

    // 在 parent 下面查找第一个名字为 name 的子元素
    XMLElement *elem = parent->FirstChildElement(name);

    // 如果没有找到该元素，或者该元素没有文本内容，则返回空字符串
    if (!elem || !elem->GetText()) {
        return "";
    }

    // 返回该 XML 标签中的文本内容
    return elem->GetText();
}

/*
 * stripHtml 函数：
 *
 * 功能：
 *     去除字符串中的 HTML 标签，并处理一些常见的 HTML 实体。
 *
 * RSS 中的 description 和 content:encoded 里通常包含 HTML 内容，
 * 例如：
 *
 *     <p>这是一段文字</p>
 *     <a href="xxx">Read More</a>
 *     &nbsp;
 *     &amp;
 *
 * 但是作业要求生成网页库文本，所以一般需要把 HTML 标签去掉。
 *
 * 参数：
 *     s : 原始字符串，可能包含 HTML 标签
 *
 * 返回值：
 *     去掉 HTML 标签后的普通文本
 */
static string stripHtml(const string &s)
{
    // ret 用来保存处理后的结果
    string ret = s;

    /*
     * 使用正则表达式去除 HTML 标签
     *
     * 正则表达式 "<[^>]*>" 的含义：
     *     <       匹配左尖括号
     *     [^>]*   匹配任意多个不是右尖括号的字符
     *     >       匹配右尖括号
     *
     * 所以它可以匹配：
     *     <p>
     *     </p>
     *     <a href="xxx">
     *     <img src="xxx" />
     *
     * 然后统一替换成一个空格。
     */
    ret = std::regex_replace(ret, std::regex("<[^>]*>"), " ");

    /*
     * 处理一些常见的 HTML 实体
     *
     * 例如：
     *     &nbsp;  表示空格
     *     &amp;   表示 &
     *     &lt;    表示 <
     *     &gt;    表示 >
     *     &quot;  表示 "
     */
    ret = std::regex_replace(ret, std::regex("&nbsp;"), " ");
    ret = std::regex_replace(ret, std::regex("&amp;"), "&");
    ret = std::regex_replace(ret, std::regex("&lt;"), "<");
    ret = std::regex_replace(ret, std::regex("&gt;"), ">");
    ret = std::regex_replace(ret, std::regex("&quot;"), "\"");
    ret = std::regex_replace(ret, std::regex("&#39;|&apos;"), "'");

    /*
     * 合并多余的空白字符
     *
     * [ \t\r\n]+ 的含义：
     *     空格、制表符、回车、换行，出现一次或多次
     *
     * 统一替换成一个普通空格，让输出文本更整洁。
     */
    ret = std::regex_replace(ret, std::regex("[ \t\r\n]+"), " ");

    return ret;
}

/*
 * xmlEscape 函数：
 *
 * 功能：
 *     对输出到 pagelib.txt 中的特殊字符进行转义。
 *
 * 为什么需要这个函数？
 *
 * 因为 pagelib.txt 的格式类似 XML：
 *
 *     <title>...</title>
 *
 * 如果正文里本身含有 <、>、& 等字符，
 * 就可能破坏 XML 结构。
 *
 * 例如：
 *     原始内容：Tom & Jerry
 *
 * 如果直接输出：
 *     <title>Tom & Jerry</title>
 *
 * 这里的 & 在 XML 中是不安全的。
 *
 * 应该转成：
 *     <title>Tom &amp; Jerry</title>
 *
 * 这样生成的 pagelib.txt 更规范。
 */
static string xmlEscape(const string &s)
{
    string out;

    // 提前申请空间，减少字符串扩容次数，提高一点效率
    out.reserve(s.size());

    // 逐个字符扫描原字符串
    for (char ch : s) {
        switch (ch) {
        case '&':
            out += "&amp;";
            break;
        case '<':
            out += "&lt;";
            break;
        case '>':
            out += "&gt;";
            break;
        case '"':
            out += "&quot;";
            break;
        case '\'':
            out += "&apos;";
            break;
        default:
            // 普通字符不需要处理，直接追加
            out += ch;
            break;
        }
    }

    return out;
}

/*
 * RssReader 类：
 *
 * 功能：
 *     负责读取 RSS 文件，解析其中的文章信息，
 *     然后把解析结果输出成 pagelib.txt。
 *
 * 成员函数：
 *     parseRss()
 *         解析 RSS 文件，把每篇文章保存到 _rss 中。
 *
 *     dump(filename)
 *         把 _rss 中保存的文章信息写入指定文件。
 *
 * 成员变量：
 *     _rssFile
 *         RSS 文件名，例如 "coolshell.xml"。
 *
 *     _rss
 *         vector<RssItem>，保存所有解析出来的文章。
 */
class RssReader {
public:
    /*
     * 构造函数：
     *
     * 参数 rssFile 有默认值 "coolshell.xml"。
     * 如果创建对象时不传文件名，就默认解析 coolshell.xml。
     *
     * 例如：
     *     RssReader reader;
     *
     * 等价于：
     *     RssReader reader("coolshell.xml");
     */
    RssReader(const string &rssFile = "coolshell.xml")
    : _rssFile(rssFile)
    {}

    /*
     * parseRss：
     *     解析 RSS 文件。
     */
    void parseRss();

    /*
     * dump：
     *     把解析后的 RSS 内容输出到文件。
     */
    void dump(const string &filename);

private:
    string _rssFile;       // RSS 文件名
    vector<RssItem> _rss;  // 保存所有文章信息
};

/*
 * RssReader::parseRss
 *
 * 功能：
 *     使用 tinyxml2 解析 RSS 文件。
 *
 * RSS 文件结构大概如下：
 *
 * <rss>
 *     <channel>
 *         <item>
 *             <title>...</title>
 *             <link>...</link>
 *             <description>...</description>
 *             <content:encoded>...</content:encoded>
 *         </item>
 *
 *         <item>
 *             ...
 *         </item>
 *     </channel>
 * </rss>
 *
 * 解析步骤：
 *     1. 加载 XML 文件
 *     2. 找到根节点 <rss>
 *     3. 找到 <channel>
 *     4. 遍历 channel 下面的所有 <item>
 *     5. 从每个 item 中取 title、link、description、content
 *     6. 保存到 _rss 容器中
 */
void RssReader::parseRss()
{
    // XMLDocument 是 tinyxml2 中表示整个 XML 文档的类
    XMLDocument doc;

    // 加载 RSS 文件
    XMLError err = doc.LoadFile(_rssFile.c_str());

    // 如果加载失败，抛出异常
    if (err != XML_SUCCESS) {
        throw std::runtime_error("LoadFile failed: " + _rssFile);
    }

    // 获取根节点 <rss>
    XMLElement *rss = doc.FirstChildElement("rss");

    // 如果没有找到 <rss>，说明文件格式不正确
    if (!rss) {
        throw std::runtime_error("missing <rss>");
    }

    // 获取 <rss> 下面的 <channel> 节点
    XMLElement *channel = rss->FirstChildElement("channel");

    // 如果没有找到 <channel>，说明 RSS 文件结构不符合预期
    if (!channel) {
        throw std::runtime_error("missing <channel>");
    }

    /*
     * 遍历 channel 下面的所有 item 节点。
     *
     * FirstChildElement("item")：
     *     找到第一个 <item> 节点。
     *
     * NextSiblingElement("item")：
     *     找到下一个同级的 <item> 节点。
     *
     * 当 item 为 nullptr 时，说明已经遍历结束。
     */
    for (XMLElement *item = channel->FirstChildElement("item");
         item != nullptr;
         item = item->NextSiblingElement("item")) {

        // 创建一个 RssItem 对象，用来保存当前文章的信息
        RssItem rssItem;

        /*
         * 读取 title、link、description、content:encoded。
         *
         * getText 用来获取标签文本；
         * stripHtml 用来去除其中可能存在的 HTML 标签。
         */
        rssItem.title = stripHtml(getText(item, "title"));
        rssItem.link = stripHtml(getText(item, "link"));
        rssItem.description = stripHtml(getText(item, "description"));

        /*
         * 注意：
         *
         * RSS 中正文内容的标签名通常是：
         *
         *     <content:encoded>
         *
         * 这是带命名空间前缀的标签。
         *
         * 在 tinyxml2 中，可以直接使用完整标签名：
         *
         *     "content:encoded"
         *
         * 不能只写成 "content"。
         */
        rssItem.content = stripHtml(getText(item, "content:encoded"));

        // 把当前文章保存到 vector 容器中
        _rss.push_back(rssItem);
    }
}

/*
 * RssReader::dump
 *
 * 功能：
 *     把 _rss 中保存的所有文章输出到指定文件中。
 *
 * 输出格式：
 *
 * <doc>
 *     <docid>1</docid>
 *     <title>...</title>
 *     <link>...</link>
 *     <description>...</description>
 *     <content>...</content>
 * </doc>
 *
 * 每一篇文章对应一个 <doc>。
 */
void RssReader::dump(const string &filename)
{
    // 创建文件输出流
    std::ofstream ofs(filename);

    // 如果文件打开失败，抛出异常
    if (!ofs) {
        throw std::runtime_error("open output failed: " + filename);
    }

    /*
     * 遍历 _rss 中保存的所有文章。
     *
     * i 从 0 开始，
     * 但是 docid 通常从 1 开始，
     * 所以输出 docid 时使用 i + 1。
     */
    for (size_t i = 0; i < _rss.size(); ++i) {
        ofs << "<doc>\n";

        ofs << "\t<docid>" << i + 1 << "</docid>\n";

        /*
         * 输出文本前使用 xmlEscape 转义特殊字符，
         * 避免正文里的 <、>、& 等字符破坏 XML 格式。
         */
        ofs << "\t<title>"
            << xmlEscape(_rss[i].title)
            << "</title>\n";

        ofs << "\t<link>"
            << xmlEscape(_rss[i].link)
            << "</link>\n";

        ofs << "\t<description>"
            << xmlEscape(_rss[i].description)
            << "</description>\n";

        ofs << "\t<content>"
            << xmlEscape(_rss[i].content)
            << "</content>\n";

        ofs << "</doc>\n";
    }
}

/*
 * main 函数：
 *
 * 程序入口。
 *
 * 支持两种运行方式：
 *
 * 方式一：
 *     ./rss_reader
 *
 *     默认读取 coolshell.xml，
 *     默认输出 pagelib.txt。
 *
 * 方式二：
 *     ./rss_reader coolshell.xml pagelib.txt
 *
 *     第一个参数表示输入 RSS 文件；
 *     第二个参数表示输出文件。
 */
int main(int argc, char **argv)
{
    /*
     * 设置默认输入文件和输出文件
     */
    string rssFile = "coolshell.xml";
    string outFile = "pagelib.txt";

    /*
     * argc 表示命令行参数个数。
     *
     * 如果 argc >= 2，说明用户传入了第一个参数，
     * 用 argv[1] 作为 RSS 文件名。
     *
     * 例如：
     *     ./rss_reader coolshell.xml
     *
     * 此时：
     *     argv[1] 是 "coolshell.xml"
     */
    if (argc >= 2) {
        rssFile = argv[1];
    }

    /*
     * 如果 argc >= 3，说明用户传入了第二个参数，
     * 用 argv[2] 作为输出文件名。
     *
     * 例如：
     *     ./rss_reader coolshell.xml pagelib.txt
     *
     * 此时：
     *     argv[2] 是 "pagelib.txt"
     */
    if (argc >= 3) {
        outFile = argv[2];
    }

    try {
        /*
         * 创建 RssReader 对象，并指定要解析的 RSS 文件
         */
        RssReader reader(rssFile);

        /*
         * 解析 RSS 文件
         */
        reader.parseRss();

        /*
         * 把解析结果输出到 pagelib.txt
         */
        reader.dump(outFile);

        /*
         * 输出提示信息，说明程序执行成功
         */
        std::cout << "generated " << outFile << std::endl;
    } catch (const std::exception &ex) {
        /*
         * 如果 parseRss 或 dump 中抛出了异常，
         * 会在这里捕获，并输出错误原因。
         */
        std::cerr << ex.what() << std::endl;

        // 返回 1 表示程序异常退出
        return 1;
    }

    // 返回 0 表示程序正常结束
    return 0;
}