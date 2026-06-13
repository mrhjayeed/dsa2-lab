#include <bits/stdc++.h>
using namespace std;

class LRUCache {
    private:
    struct Node {
        int key;
        int value;
        Node* next;
        Node* prev;

        Node(int k, int v) {
            key = k;
            value = v;
            next = nullptr;
            prev = nullptr;
        }
    };

    int capacity;
    unordered_map<int, Node*> cache;

    Node* head;
    Node* tail;

    void addNode(Node* n) {
        tail->prev->next = n;
        n->prev = tail->prev;

        n->next = tail;
        tail->prev = n;
    }

    void deleteNode(Node* n) {
        n->prev->next = n->next;
        n->next->prev = n->prev;

        n->prev = n->next = nullptr;
    }

    public:
    LRUCache(int cap) {
        capacity = cap;

        head = new Node(-1, -1);
        tail = new Node(-1, -1);

        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        auto it = cache.find(key);

        if (it == cache.end()) return -1;

        Node* node = it->second;

        deleteNode(node);
        addNode(node);

        return node->value;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];

            node->value = value;

            deleteNode(node);
            addNode(node);

            return;
        }

        if ((int)cache.size() == capacity) {
            Node* lru = head->next;
            
            deleteNode(lru);
            cache.erase(lru->key);

            delete lru;
        }

        Node* newNode = new Node(key, value);

        addNode(newNode);
        cache[key] = newNode;
    }
};

int main() {
    LRUCache lru(2);

    lru.put(1, 10);
    lru.put(2, 20);

    cout << lru.get(1) << endl;

    lru.put(3, 30);

    cout << lru.get(2) << endl;
    cout << lru.get(3) << endl;

    return 0;
}