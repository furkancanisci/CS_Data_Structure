#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// B+ Tree Node Structure
struct BPlusNode {
    bool is_leaf;
    std::vector<int> keys;
    std::vector<BPlusNode*> children; // For internal nodes: pointers to children
    std::vector<std::string> values;  // For leaf nodes: actual data
    BPlusNode* next_leaf;             // Linked list pointer for range scans

    BPlusNode(bool leaf) : is_leaf(leaf), next_leaf(nullptr) {}
};

class BPlusTree {
private:
    BPlusNode* root;
    int order; // Maximum number of children a node can have

    // Internal helper for non-full insertion
    void insertNonFull(BPlusNode* node, int key, const std::string& value) {
        if (node->is_leaf) {
            auto it = std::lower_bound(node->keys.begin(), node->keys.end(), key);
            int idx = std::distance(node->keys.begin(), it);
            
            node->keys.insert(it, key);
            node->values.insert(node->values.begin() + idx, value);
        } else {
            int i = node->keys.size() - 1;
            while (i >= 0 && key < node->keys[i]) i--;
            i++;

            if (node->children[i]->keys.size() == order - 1) {
                splitChild(node, i);
                if (key > node->keys[i]) i++;
            }
            insertNonFull(node->children[i], key, value);
        }
    }

    // Core self-balancing logic: Splitting a full node
    void splitChild(BPlusNode* parent, int i) {
        BPlusNode* node_to_split = parent->children[i];
        BPlusNode* new_node = new BPlusNode(node_to_split->is_leaf);
        int mid = (order - 1) / 2;

        // Push the median key up to the parent
        parent->keys.insert(parent->keys.begin() + i, node_to_split->keys[mid]);
        parent->children.insert(parent->children.begin() + i + 1, new_node);

        // Move keys and values/children to the new node
        new_node->keys.assign(node_to_split->keys.begin() + mid + 1, node_to_split->keys.end());
        node_to_split->keys.erase(node_to_split->keys.begin() + mid, node_to_split->keys.end());

        if (node_to_split->is_leaf) {
            new_node->values.assign(node_to_split->values.begin() + mid + 1, node_to_split->values.end());
            node_to_split->values.erase(node_to_split->values.begin() + mid, node_to_split->values.end());
            
            // Link the leaf nodes for O(1) sequential access
            new_node->next_leaf = node_to_split->next_leaf;
            node_to_split->next_leaf = new_node;
        } else {
            new_node->children.assign(node_to_split->children.begin() + mid + 1, node_to_split->children.end());
            node_to_split->children.erase(node_to_split->children.begin() + mid + 1, node_to_split->children.end());
        }
    }

public:
    BPlusTree(int _order = 4) : order(_order) {
        root = new BPlusNode(true);
    }

    void insert(int key, const std::string& value) {
        if (root->keys.size() == order - 1) {
            BPlusNode* new_root = new BPlusNode(false);
            new_root->children.push_back(root);
            splitChild(new_root, 0);
            root = new_root;
        }
        insertNonFull(root, key, value);
    }

    bool find(int key, std::string& value) {
        BPlusNode* curr = root;
        while (!curr->is_leaf) {
            int i = 0;
            while (i < curr->keys.size() && key >= curr->keys[i]) i++;
            curr = curr->children[i];
        }

        for (size_t i = 0; i < curr->keys.size(); i++) {
            if (curr->keys[i] == key) {
                value = curr->values[i];
                return true;
            }
        }
        return false;
    }

    // Simplified level-order print for visualization
    void display() {
        if (!root) return;
        std::vector<BPlusNode*> q;
        q.push_back(root);
        while (!q.empty()) {
            std::vector<BPlusNode*> next_q;
            for (auto node : q) {
                std::cout << "[ ";
                for (int k : node->keys) std::cout << k << " ";
                std::cout << "] ";
                if (!node->is_leaf) {
                    for (auto child : node->children) next_q.push_back(child);
                }
            }
            std::cout << std::endl;
            q = next_q;
        }
    }
};

int main() {
    BPlusTree bpt(4); // Max 3 keys per node

    bpt.insert(10, "User_10");
    bpt.insert(20, "User_20");
    bpt.insert(5, "User_5");
    bpt.insert(15, "User_15"); // This will trigger a split
    bpt.insert(30, "User_30");

    std::cout << "--- B+ Tree Structure ---" << std::endl;
    bpt.display();

    std::string val;
    if (bpt.find(15, val)) {
        std::cout << "\nFound key 15: " << val << std::endl;
    } else {
        std::cout << "\nKey 15 not found!" << std::endl;
    }

    return 0;
}