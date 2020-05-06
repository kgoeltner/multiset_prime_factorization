//
// Karl Goeltner
// 917006087
// ECS 36C - 05/04/2020
//
// multiset.h - Implementation of the multiset ADT using a BST
// Public API: Size, Empty, Insert, Remove, Contains,
//             Count, Floor, Ceil, Max, Min
// Private Methods: Insert, Remove, Search, Floor, Ceil, EmptyError, Min
//

#ifndef MULTISET_H_
#define MULTISET_H_

#include <memory>
#include <utility>

template <typename K>
class Multiset {
 public:
  //
  // Public API
  //

  // * Capacity
  // Returns number of items in multiset --O(1)
  size_t Size();
  // Returns true if multiset is empty --O(1)
  bool Empty();

  // * Modifiers
  // Inserts an item corresponding to @key in multiset --O(log N) on average
  void Insert(const K &key);
  // Removes an item corresponding to @key from multiset --O(log N) on average
  //  Throws exception if key doesn't exist
  void Remove(const K &key);

  // * Lookup
  // Return whether @key is found in multiset --O(log N) on average
  bool Contains(const K& key);
  // Returns number of items matching @key in multiset --O(log N) on average
  //  Throws exception if key doesn't exist
  size_t Count(const K& key);

  // Return greatest key less than or equal to @key --O(log N) on average
  //  Throws exception if multiset is empty or no floor exists for key
  const K& Floor(const K &key);
  // Return least key greater than or equal to @key --O(log N) on average
  //  Throws exception if multiset is empty or no ceil exists for key
  const K& Ceil(const K &key);

  // Return max key in multiset --O(log N) on average
  //  Throws exception if multiset is empty
  const K& Max();
  // Return min key in multiset --O(log N) on average
  //  Throws exception if multiset is empty
  const K& Min();

 private:
  //
  // @@@ The class's internal members below can be modified @@@
  //

  // Node structure to hold a key value, quantity, left & right keys
  struct Node {
    K key;
    std::size_t quantity;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
  };

  // Private member variables
  // - Root element
  // - Current size of multiset
  std::unique_ptr<Node> root;
  std::size_t cur_size = 0;

  // Private methods
  void Insert(std::unique_ptr<Node> &n, const K &key);
  void Remove(std::unique_ptr<Node> &n, const K &key);
  Node* Search(const K& key);
  Node* Floor(Node *n, const K &key);
  Node* Ceil(Node *n, const K &key);
  void EmptyError();
  Node* Min(Node *n);
};

//
// Your implementation of the class should be located below
//

  // Size - returns number of items in multiset, O(1)
  template<typename K>
  size_t Multiset<K>::Size() {
    return cur_size;
  }

  // Empty - returns true if multiset is empty, O(1)
  template<typename K>
  bool Multiset<K>::Empty() {
    // Check the cur_size variable for number of elements in multiset
    if (cur_size == 0)
      return true;
    return false;
  }

  // Insert - insert item corresponding to @key in multiset, O(log N)
  template<typename K>
  void Multiset<K>::Insert(const K &key) {
    // Call helper Insert method
    Insert(root, key);
    cur_size++;
  }

  // HELPER METHOD - insert an item corresponding to @key in multiset
  template <typename K>
  void Multiset<K>::Insert(std::unique_ptr<Node> &n, const K &key) {
    // Insert Node HERE
    if (!n)
      n = std::unique_ptr<Node>(new Node{key, 1});
    // Move to LEFT branch
    else if (key < n->key)
      Insert(n->left, key);
    // Move to RIGHT branch
    else if (key > n->key)
      Insert(n->right, key);
    // Key already present, DUPLICATE
    else
      n->quantity = ++(n->quantity);
  }

  // Remove - remove an item corresponding to @key from multiset, O(log N)
  template <typename K>
  void Multiset<K>::Remove(const K &key) {
    // Call helper Remove method
    Remove(root, key);
    cur_size--;
  }

  // HELPER METHOD - remove an item corresponding to @key from multiset
  template <typename K>
  void Multiset<K>::Remove(std::unique_ptr<Node> &n, const K &key) {
    // Key NOT FOUND
    if (!n)
      throw std::out_of_range("Invalid key");

    // Move to LEFT branch
    if (key < n->key) {
      Remove(n->left, key);
    // Move to RIGHT branch
    } else if (key > n->key) {
      Remove(n->right, key);
    // FOUND specified node
    } else {
      // If a duplicate key exists, simply decrement quantity
      if (n->quantity > 1) {
        n->quantity = --(n->quantity);
      // TWO children: replace with min node in right subtree
      } else if (n->left && n->right) {
        n->key = Min(n->right.get())->key;
        Remove(n->right, n->key);
      // ONE child or NONE: replace with only child or nullptr
      } else {
        n = std::move((n->left) ? n->left : n->right);
      }
    }
  }

  // Contains - return whether @key is found in multiset, O(log N)
  template <typename K>
  bool Multiset<K>::Contains(const K& key) {
    // Call helper Search method to find node
    Node *n = Search(key);

    // Return false if key doesn't exist
    if (!n)
      return false;
    return true;
  }

  // Count - returns number of items matching @key in multiset, O(log N)
  template <typename K>
  size_t Multiset<K>::Count(const K& key) {
    // Call helper Search method to find node
    Node *n = Search(key);

    // Throw exception if key doesn't exist
    if (!n)
      throw std::out_of_range("Invalid key");
    return n->quantity;
  }

  // HELPER METHOD - return a node inside multiset based on @key
  template <typename K>
  typename Multiset<K>::Node* Multiset<K>::Search(const K& key) {
    Node *n = root.get();

    // Use BST structure to search for @key
    while (n) {
      // FOUND specified node, return node
      if (key == n->key)
        return n;
      // Move to LEFT branch
      if (key < n->key)
        n = n->left.get();
      // Move to RIGHT branch
      else
        n = n->right.get();
    }

    return nullptr;
  }

  // Floor - return greatest key less than or equal to @key, O(log N)
  template<typename K>
  const K& Multiset<K>::Floor(const K &key) {
    return Floor(root.get(), key)->key;
  }

  // HELPER METHOD - return greatest key less than or equal to @key
  template<typename K>
  typename Multiset<K>::Node* Multiset<K>::Floor(Node *n, const K &key) {
    // ERROR: throw exception if multiset is empty
    EmptyError();

    // ERROR: throw exception if minimum node is greater than input key
    if (Min() >= key)
      throw std::out_of_range("Invalid key");

    // If node is NIL
    if (!n)
      return nullptr;
    // Else if the node's key EQUALS searched key
    else if (n->key == key)
      return n;
    // Else if node's key is LARGER, continue floor search LEFT
    else if (n->key > key)
      return Floor(n->left.get(), key);
    // Else if node's key is SMALLER, compare RIGHT & CURRENT
    Node *floor = Floor(n->right.get(), key);

    // Check if right node OR current node has floor value, ensure not NULL
    if (floor)
      return ((floor->key <= key) ? floor : n);
    return n;
  }

  // Ceil - return least key greater than or equal to @key, O(log N)
  template<typename K>
  const K& Multiset<K>::Ceil(const K &key) {
    return Ceil(root.get(), key)->key;
  }

  // HELPER METHOD - return least key greater than or equal to @key
  template<typename K>
  typename Multiset<K>::Node* Multiset<K>::Ceil(Node *n, const K &key) {
    // ERROR: throw exception if multiset is empty
    EmptyError();

    // ERROR: throw exception if maximum node is less than input key
    if (Max() <= key)
      throw std::out_of_range("Invalid key");

    // If node is NIL
    if (!n)
      return nullptr;
    // Else if the node's key EQUALS searched key
    else if (n->key == key)
      return n;
    // Else if node's key is SMALLER, continue ceil search RIGHT
    else if (n->key < key)
      return Ceil(n->right.get(), key);
    // Else if node's key is LARGER, compare LEFT & CURRENT
    Node *ceil = Ceil(n->left.get(), key);

    // Check if left node OR current node has ceil value, ensure not NULL
    if (ceil)
      return ((ceil->key >= key) ? ceil : n);
    return n;
  }

  // HELPER METHOD - throw exception if multiset is empty
  template<typename K>
  void Multiset<K>::EmptyError() {
    if (Empty())
      throw std::underflow_error("Empty multiset");
  }

  // Max - return max key in multiset, O(log N)
  template<typename K>
  const K& Multiset<K>::Max() {
    // Check to see if multiset is empty
    if (!cur_size)
      throw std::underflow_error("Empty multiset");

    Node *n = root.get();

    // Keep traversing to attain the right-most MAX element
    while (n->right)
      n = n->right.get();
    return n->key;
  }

  // Min - return min key in multiset, O(log N)
  template <typename K>
  const K& Multiset<K>::Min() {
    // Check to see if multiset is empty
    if (!cur_size)
      throw std::underflow_error("Empty multiset");

    return Min(root.get())->key;
  }

  // HELPER METHOD - recursive min function used to return min node of a tree
  template <typename K>
  typename Multiset<K>::Node* Multiset<K>::Min(Node *n) {
    // Keep traversing to attain the left-most MIN element
    if (n->left)
      return Min(n->left.get());
    else
      return n;
  }

#endif  // MULTISET_H_
