class HashTable:

    def __init__(self, size=10):
        self.size = size
        # Create a list of lists (buckets) for chaining
        self.table = [[] for _ in range(self.size)]

    def _hash_function(self, key):
        return hash(key) % self.size

    def insert(self, key, value):
        index = self._hash_function(key)
        
        # Check if key already exists in the bucket (Chain)
        for i, (k, v) in enumerate(self.table[index]):
            if k == key:
                self.table[index][i] = (key, value)
                return
        
        # If not found, append to the bucket (Collision handled by Chaining)
        self.table[index].append((key, value))

    def get(self, key):
        """Retrieve value by key. Returns None if not found."""
        index = self._hash_function(key)
        for k, v in self.table[index]:
            if k == key:
                return v
        return None

    def delete(self, key):
        """Remove a key-value pair from the table."""
        index = self._hash_function(key)
        for i, (k, v) in enumerate(self.table[index]):
            if k == key:
                del self.table[index][i]
                return True
        return False

    def display(self):
        """Print the internal structure of the table to see collisions."""
        for i, bucket in enumerate(self.table):
            print(f"Bucket {i}: {bucket}")


# --- DEMO & COLLISION TEST ---
if __name__ == "__main__":
    # Create a small table to force collisions
    my_hash = HashTable(size=5)

    print("--- Inserting Data ---")
    my_hash.insert("Furkan", "Computer Engineer")
    my_hash.insert("Gemini", "AI Assistant")
    my_hash.insert("Kocaeli", "University")
    
    # These keys might collide depending on Python's internal hash()
    # Let's add more to ensure some buckets have multiple items
    my_hash.insert("Python", "Language")
    my_hash.insert("Data", "Structure")

    print("\n--- Current Hash Table State ---")
    my_hash.display()

    print("\n--- Retrieval Test ---")
    print(f"Get 'Furkan': {my_hash.get('Furkan')}")
    print(f"Get 'Unknown': {my_hash.get('Ghost')}")

    print("\n--- Deletion Test ---")
    my_hash.delete("Python")
    print("After deleting 'Python':")
    my_hash.display()