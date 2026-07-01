#include <unordered_map>
#include <list>
#include <utility>

using namespace std;

class LRUCache {
private:
    int _capacity; // 缓存容量
    // 双向链表, 存储 {key, value}
    list<pair<int, int>> _cache;
    // 哈希表, 存储 key 到 链表节点迭代器 的映射
    unordered_map<int, list<pair<int, int>>::iterator> _map;

public:
    LRUCache(int capacity) {
        _capacity = capacity;
        _map.reserve(_capacity); // 防止频繁扩容
    }

    int get(int key) {
        // 在 map 中 查找 key
        auto it = _map.find(key);
        if (it == _map.end()) {
            return -1; // 没找到
        }

        // 找到了：利用 splice 将该节点移动到链表头部 (表示最近使用)
        // cache.begin() 是目的地，cache 是源链表，it->second 是要移动的节点迭代器
        _cache.splice(_cache.begin(), _cache, it->second);

        // 返回对应的 value
        return it->second->second;
    }

    void put(int key, int value) {
        auto it = _map.find(key);

        if (it != _map.end()) {
            // 情况 1: key 已经存在，更新 value 并移到头部
            it->second->second = value;
            _cache.splice(_cache.begin(), _cache, it->second);
            return;
        }

        // 情况 2: key 不存在，需要插入新元素
        if (_cache.size() == _capacity) {
            // 容量满了，需要淘汰链表尾部（最久未使用）的元素
            auto last_pair = _cache.back();
            _map.erase(last_pair.first); // 从哈希表中移除
            _cache.pop_back(); // 从链表中移除
        }

        // 将新元素插入到链表头部
        _cache.emplace_front(key, value);
        // 在哈希表中建立映射：key -> 链表头节点的迭代器
        _map[key] = _cache.begin();
    }
};
