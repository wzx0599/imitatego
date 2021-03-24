/**
 * @file   : lru_cache.hpp
 * @brief  : HashMap+双向链表实现LRU缓存
 * @author : Wei Zixian
 * @date   : 2021-02-07
 */

#include <iostream>
#include <unordered_map>

using namespace std;

class Node
{
public:
    Node() : key(0), value(0), prev(nullptr), next(nullptr) {}
    Node(int key, int value) : key(key), value(value), prev(nullptr), next(nullptr) {}

    int key;
    int value;
    Node *prev;
    Node *next;
};

class LRUCache
{
public:
    LRUCache() = delete;

    LRUCache(const int capacity) : _capacity(capacity), _size(0)
    {
        _head = new Node();
        _tail = new Node();
        _head->next = _tail;
        _tail->prev = _head;
    }

    int get(int key)
    {
        if (_cache.count(key))
        {
            Node *node = _cache[key];
            moveToHead(node);
            return node->value;
        }
        return -1;
    }

    void put(const int key, const int value)
    {
        if (!_cache.count(key))
        {
            Node *node = new Node(key, value);
            _cache[key] = node;
            addToHead(node);
            _size++;
            if (_size > _capacity)
            {
                Node *removed = removeTail();
                _cache.erase(removed->key);
                delete removed;
                _size--;
            }
        }
        else
        {
            Node *node = _cache[key];
            node->value = value;
            moveToHead(node);
        }
    }

private:
    void addToHead(Node *node)
    {
        node->prev = _head;
        node->next = _head->next;
        _head->next->prev = node;
        _head->next = node;
    }

    void removeNode(Node *node)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveToHead(Node *node)
    {
        removeNode(node);
        addToHead(node);
    }

    Node* removeTail()
    {
        Node *node = _tail->prev;
        removeNode(node);
        return node;
    }

    const int _capacity;
    int _size;
    unordered_map<int, Node*> _cache;
    Node *_head;
    Node *_tail;
};

int main(int argc, char *argv[])
{
    printf("LRU Cache Test.\r\n");
    LRUCache *lru_cache = new LRUCache(2);
    lru_cache->put(1, 1);
    lru_cache->put(2, 2);
    cout << lru_cache->get(1) << " ";
    lru_cache->put(3, 3);
    cout << lru_cache->get(2) << " ";
    lru_cache->put(4, 4);
    cout << lru_cache->get(1) << " ";
    cout << lru_cache->get(3) << " ";
    cout << lru_cache->get(4) << " ";
    cout << endl;
}
