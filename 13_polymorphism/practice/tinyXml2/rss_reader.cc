#include "tinyxml2.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <stdexcept>

using std::string;
using std::vector;
using namespace tinyxml2;

struct RssItem {
    string title;
    string link;
    string description;
    string content;
};

static string getText(XMLElement *parent, const char *name)
{
    if (!parent) {
        return "";
    }

    XMLElement *elem = parent->FirstChildElement(name);
    if (!elem || !elem->GetText()) {
        return "";
    }

    return elem->GetText();
}

static string stripHtml(const string &s)
{
    string ret = s;

    // 去除 HTML 标签，例如 <p>、<a href="...">、<img ...>
    ret = std::regex_replace(ret, std::regex("<[^>]*>"), " ");

    // 处理常见 HTML 实体
    ret = std::regex_replace(ret, std::regex("&nbsp;"), " ");
    ret = std::regex_replace(ret, std::regex("&amp;"), "&");
    ret = std::regex_replace(ret, std::regex("&lt;"), "<");
    ret = std::regex_replace(ret, std::regex("&gt;"), ">");
    ret = std::regex_replace(ret, std::regex("&quot;"), "\"");
    ret = std::regex_replace(ret, std::regex("&#39;|&apos;"), "'");

    // 合并多余空白
    ret = std::regex_replace(ret, std::regex("[ \t\r\n]+"), " ");

    return ret;
}

static string xmlEscape(const string &s)
{
    string out;
    out.reserve(s.size());

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
            out += ch;
            break;
        }
    }

    return out;
}

class RssReader {
public:
    RssReader(const string &rssFile = "coolshell.xml")
    : _rssFile(rssFile)
    {}

    void parseRss();
    void dump(const string &filename);

private:
    string _rssFile;
    vector<RssItem> _rss;
};

void RssReader::parseRss()
{
    XMLDocument doc;

    XMLError err = doc.LoadFile(_rssFile.c_str());
    if (err != XML_SUCCESS) {
        throw std::runtime_error("LoadFile failed: " + _rssFile);
    }

    XMLElement *rss = doc.FirstChildElement("rss");
    if (!rss) {
        throw std::runtime_error("missing <rss>");
    }

    XMLElement *channel = rss->FirstChildElement("channel");
    if (!channel) {
        throw std::runtime_error("missing <channel>");
    }

    for (XMLElement *item = channel->FirstChildElement("item");
         item != nullptr;
         item = item->NextSiblingElement("item")) {

        RssItem rssItem;

        rssItem.title = stripHtml(getText(item, "title"));
        rssItem.link = stripHtml(getText(item, "link"));
        rssItem.description = stripHtml(getText(item, "description"));

        // 注意：content:encoded 是带命名空间前缀的标签名，
        // tinyxml2 可以直接用完整字符串查找。
        rssItem.content = stripHtml(getText(item, "content:encoded"));

        _rss.push_back(rssItem);
    }
}

void RssReader::dump(const string &filename)
{
    std::ofstream ofs(filename);
    if (!ofs) {
        throw std::runtime_error("open output failed: " + filename);
    }

    for (size_t i = 0; i < _rss.size(); ++i) {
        ofs << "<doc>\n";
        ofs << "\t<docid>" << i + 1 << "</docid>\n";
        ofs << "\t<title>" << xmlEscape(_rss[i].title) << "</title>\n";
        ofs << "\t<link>" << xmlEscape(_rss[i].link) << "</link>\n";
        ofs << "\t<description>" << xmlEscape(_rss[i].description) << "</description>\n";
        ofs << "\t<content>" << xmlEscape(_rss[i].content) << "</content>\n";
        ofs << "</doc>\n";
    }
}

int main(int argc, char **argv)
{
    string rssFile = "coolshell.xml";
    string outFile = "pagelib.txt";

    if (argc >= 2) {
        rssFile = argv[1];
    }

    if (argc >= 3) {
        outFile = argv[2];
    }

    try {
        RssReader reader(rssFile);
        reader.parseRss();
        reader.dump(outFile);

        std::cout << "generated " << outFile << std::endl;
    } catch (const std::exception &ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}