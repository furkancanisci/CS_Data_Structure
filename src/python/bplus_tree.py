class BPlusNode:
    def __init__(self, is_leaf=False):
        self.is_leaf = is_leaf
        self.keys = []
        # In internal nodes: children are pointers to other BPlusNodes
        # In leaf nodes: children are actual data/values
        self.children = []  
        # Pointer to the next leaf node for fast range scans (O(1) to next leaf)
        self.next_leaf = None


class BPlusTree:
    def __init__(self, order=4):
        self.order = order
        self.root = BPlusNode(is_leaf=True)

    def search(self, key):
        """
        Traverses from root to leaf to find the exact key.
        Complexity: O(log n)
        """
        node = self.root
        # Navigate through internal nodes using keys as guideposts
        while not node.is_leaf:
            i = 0
            while i < len(node.keys) and key >= node.keys[i]:
                i += 1
            node = node.children[i]

        # Once at leaf, do a linear search within the small node
        for i, k in enumerate(node.keys):
            if k == key:
                return node.children[i]
        return None

    def insert(self, key, value):
        """
        Inserts a key-value pair and handles root splitting if necessary.
        """
        root = self.root
        # If root is full, the tree grows in height
        if len(root.keys) == self.order - 1:
            new_root = BPlusNode(is_leaf=False)
            new_root.children.append(root)
            self._split_child(new_root, 0)
            self.root = new_root

        self._insert_non_full(self.root, key, value)
        
    def _insert_non_full(self, node, key, value):
        """
        Recursive helper to find the correct leaf for insertion.
        """
        if node.is_leaf:
            i = 0
            while i < len(node.keys) and key > node.keys[i]:
                i += 1
            node.keys.insert(i, key)
            node.children.insert(i, value)
        else:
            i = 0
            while i < len(node.keys) and key >= node.keys[i]:
                i += 1
            # Proactive split: split child if it's full before descending
            if len(node.children[i].keys) == self.order - 1:
                self._split_child(node, i)
                if key >= node.keys[i]:
                    i += 1
            self._insert_non_full(node.children[i], key, value)
            
    def _split_child(self, parent, index):
        """
        The core of self-balancing. Splits a full node into two and
        moves the median key to the parent.
        """
        node_to_split = parent.children[index]
        new_node = BPlusNode(is_leaf=node_to_split.is_leaf)
        
        mid = self.order // 2
        
        # Promote the median key to parent
        parent.keys.insert(index, node_to_split.keys[mid])
        parent.children.insert(index + 1, new_node)
        
        # Distribute keys and children between old and new node
        new_node.keys = node_to_split.keys[mid + 1:]
        node_to_split.keys = node_to_split.keys[:mid]
        
        if not node_to_split.is_leaf:
            new_node.children = node_to_split.children[mid + 1:]
            node_to_split.children = node_to_split.children[:mid + 1]
        else:
            # Leaf node specific logic: link the leaves together
            new_node.children = node_to_split.children[mid + 1:]
            node_to_split.children = node_to_split.children[:mid + 1]
            new_node.next_leaf = node_to_split.next_leaf
            node_to_split.next_leaf = new_node
        

    def print_levels(self):
        """
        BFS traversal to visualize tree levels.
        """
        q = [self.root]
        level = 0
        while q:
            next_q = []
            print(f"Level {level}:", [n.keys for n in q])
            for n in q:
                if not n.is_leaf:
                    next_q.extend(n.children)
            q = next_q
            level += 1
            
# --- MAIN DEMO ---
if __name__ == "__main__":
    # Order 4 means a node can have max 3 keys
    bpt = BPlusTree(order=4)
    
    print("--- Inserting 0 to 9 ---")
    for i in range(10):
        bpt.insert(i, f"Data_{i}")
    
    bpt.print_levels()
    
    print("\n--- Search Results ---")
    print(f"Key 5: {bpt.search(5)}")
    print(f"Key 11: {bpt.search(11)}")