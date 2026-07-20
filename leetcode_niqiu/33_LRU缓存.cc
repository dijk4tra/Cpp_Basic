#include <unordered_map>
#include <list>
#include <utility>

using namespace std;

class LRUCache {
private:
    int _capacity; // 缓存容量
    // 双向链表, 存储 {key, value}
    // 1. 越靠近 begin() 越新，越靠近 back() 越旧。
    // 2. 为什么存 pair 而非单单一个 value？
    //    为了在尾部淘汰时，能拿到这里的 pair.first (key) 去反向删除哈希表中的映射。
    list<pair<int, int>> _cache;
    // 哈希表, 存储 key 到 链表节点迭代器 的映射
    // 1. _map 的 Key (it->first) 与 _cache 里的 pair.first (key) 的值保持绝对一致！
    // 2. _map 的 Value (it->second) 存储的是指向链表对应节点的“迭代器”（本质是内存地址）。
    // 3. 它的作用是实现 O(1) 的时间复杂度闪现到对应的链表节点，避免遍历链表。
    unordered_map<int, list<pair<int, int>>::iterator> _map;

public:
    LRUCache(int capacity) {
        _capacity = capacity;
        // 预先保留空间，防止运行期间哈希表频繁扩容（Rehash）导致性能抖动
        _map.reserve(_capacity);
    }

    int get(int key) {
        // 在 map 中查找 key
        auto it = _map.find(key);
        if (it == _map.end()) {
            return -1;
        }

        // 找到了：利用 splice 将该节点移动到链表头部 (表示最近使用)
        // cache.begin() 是目的地，cache 是源链表，it->second 是要移动的节点迭代器
        // 作用：将 it->second（即对应节点的内存地址）指向的节点，剪切并粘贴到链表头部（_cache.begin()）
        // 核心：只修改节点的前后指针指向，没有任何内存拷贝或重新分配，纯粹的 O(1) 操作！
        // 注意：splice 后，原本指向该节点的迭代器依然有效，物理内存没变，所以不需要更新 _map。
        _cache.splice(_cache.begin(), _cache, it->second);

        // 先通过 it->second 拿到链表节点，再通过 ->second 拿到该节点的 value
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
            _cache.pop_back(); // 从双向链表中移除
        }

        // 将新元素插入至链表头部
        _cache.emplace_front(key, value);
        // 在哈希表中建立映射：key -> 链表头节点的迭代器
        _map[key] = _cache.begin();
    }
};
