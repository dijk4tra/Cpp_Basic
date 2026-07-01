#include <algorithm>
#include <unordered_map>
#include <list>

using namespace std;

// 1. 定义结点信息
// 将缓存项的 key、value 以及当前被访问的频次 freq 打包封装在一起
// 为什么 Node 结构体里面不仅要存 value，还必须把 key 也存进去？
// 因为当缓存满了、需要从 freq_table 中淘汰末尾结点时，我们只能拿到该末尾结点对象。
// 如果没有把 key 存在结点里，我们就无法知道这个结点对应的键是什么，
// 也就无法在 O(1) 时间内去 key_table 中同步删除它。
struct Node {
    int _key;
    int _value;
    int _freq;
};

class LFUCache
{
private:
    int cap;       // 缓存的最大容量限制
    int min_freq;  // 全局最小频率，缓存满时用于定位需要淘汰的群组

    // 【哈希表 1】核心索引表
    // 映射：key -> 双向链表中的结点迭代器（可以理解为精确的内存指针）
    // 作用：让我们能在 O(1) 时间内判断 key 是否存在，并直接定位到对应的 Node 进行修改或删除
    unordered_map<int, list<Node>::iterator> key_table;

    // 【哈希表 2】频次管理表
    // 映射：freq -> 拥有该频次的所有结点组成的双向链表 (std::list)
    // 作用：把相同访问频次的结点聚合在一起
    // 约定：链表头部（front）是最新访问的，链表尾部（back）是最久未访问的
    unordered_map<int, list<Node>> freq_table;

    // 内部辅助函数：每当某个结点被访问时，提升它的频次，并调整它在频次表中的位置
    void increase_freq(list<Node>::iterator it) {
        int key = it->_key;
        int value = it->_value;
        int freq = it->_freq;

        // 步骤 1: 从原频次链表中删除该结点
        freq_table[freq].erase(it);

        // 步骤 2：边界检查
        // 如果这个旧频次的链表被删空了，及时从哈希表中删除该链表，释放空间
        if (freq_table[freq].empty()) {
            freq_table.erase(freq);
            // 关键：如果被删空的旧频次刚好是全局最小频率 min_freq，
            // 说明这个频次彻底没有了，那么全局最小频率必须随之递增 1
            if (min_freq == freq) {
                min_freq++;
            }
        }

        // 步骤 3：把节点频率加 1，并插入到新频次对应的链表头部
        freq_table[freq + 1].push_front(Node{key, value, freq + 1});

        // 步骤 4：同步更新索引表 key_table
        // 因为节点移动到了新链表，它在内存中的位置变了，必须重新记录它在新链表头部的迭代器
        key_table[key] = freq_table[freq + 1].begin();
    }

public:
    // 初始化缓存容量
    LFUCache(int capacity) {
        cap = capacity;
        min_freq = 0;
        key_table.reserve(cap);
    }

    // 获取数据
    int get(int key) {
        // 防御性编程：容量为 0 直接返回 -1
        if (cap == 0) return -1;

        // 在索引表中查找 key
        auto it = key_table.find(key);
        if (it == key_table.end()) {
            // 没找到，说明缓存未命中
            return -1;
        }

        // 缓存命中，通过迭代器拿到节点数据
        list<Node>::iterator node_it = it->second;
        int val = node_it->_value;
        // 触发一次频率提升
        increase_freq(node_it);

        return val;
    }

    void put(int key, int value) {
        if (cap == 0) return;

        auto it = key_table.find(key);
        if (it != key_table.end()) {
            // 【情况一】Key 已经存在：更新它的值，并提升其频次
            list<Node>::iterator node_it = it->second;
            node_it->_value = value;
            increase_freq(node_it);
        } else {
            // 【情况二】Key 不存在：属于新插入数据
            // 检查容量：如果缓存已经满了，必须先腾出空间
            if (key_table.size() == cap) {
                // 找到频次最低的链表，其尾部就是该频次下最久未访问的节点
                auto delete_it = freq_table[min_freq].back();

                // 1. 从索引表 key_table 中删除要被淘汰的 key
                // 此时如果没有在 Node 里面存 key，这一步就无法立即完成
                key_table.erase(delete_it._key);

                // 2. 从频次链表的尾部将该节点弹出
                freq_table[min_freq].pop_back();

                // 3. 如果该频次链表空了，顺手从哈希表中清理掉
                if (freq_table[min_freq].empty()) {
                    freq_table.erase(min_freq);
                }
            }

            // 插入新结点，新结点频次必然为 1
            min_freq = 1;
            // 将新节点插入到 freq_table[1] 的链表头部
            freq_table[1].push_front(Node{key, value, 1});
            // 在 key_table 中建立 key 到该节点迭代器的映射
            key_table[key] = freq_table[1].begin();
        }
    }
};
