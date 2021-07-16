#include "1_Movie.h"
#include <memory>
using namespace std;

template <typename KeyType>
class AVL {

    struct node {
        explicit node(const KeyType &data1, node *parent1=nullptr, node *left1=nullptr, node *right1=nullptr) : key(data1) {
            parent = parent1;
            left = left1;
            right = right1;
        }
        friend ostream & operator << (ostream &out, const node &a) {out << a.data.getName(); return out;};
        KeyType key;
        node *parent;
        node *left;
        node *right;
        int height = 1;     // leaves 1

        int left_height() {
            if (left == nullptr) return 0;
            else return left->height;
        }

        int right_height() {
            if (right == nullptr) return 0;
            else return right->height;
        }
    };

    node *root;
    int size = 0;

    template<typename Search>
    node *_find(node *t, const Search &key) {
        if (t->key == key) return t;
        else if (t->key > key && t->left) return _find<Search>(t->left, key);
        else if (t->key < key && t->right) return _find<Search>(t->right, key);
        return t;
    }

    void _insert(KeyType &key) {
        if (root == nullptr) {
            size = 1;
            root = new node(key);
        } else {
            node *t = _find<KeyType>(root, key);
            if (key < t->key) {
                size++;
                t->left = new node(key, t);
                rebalance(t);
            } else if (key > t->key) {
                size++;
                t->right = new node(key, t);
                rebalance(t);
            }
        }
    }

    void inorder(node *t, vector<KeyType> &list) {
        if (t != nullptr) {
            inorder(t->left, list);
            list.push_back(t->key);
            inorder(t->right, list);
        }
    }

    int height(node *t=nullptr) {
        if (t == nullptr) return 0;
        return t->height - 1;
    }

    void rebalance(node *t) {
        while (t != nullptr) {
            int old_height = t->height;
            if (!is_balanced(t)) {
                t = restructure(tall_grandchild(t));
                recompute_height(t->left);
                recompute_height(t->right);
            }
            recompute_height(t);
            if (t->height == old_height) t = nullptr;
            else t = t->parent;
        }
    }

    ///////////////////////////

    void recompute_height(node *t) {
        t->height = 1 + max(t->left_height(), t->right_height());
    }

    bool is_balanced(node *t) {
        return abs(t->left_height() - t->right_height()) <= 1;
    }

    node *tall_child(node *t, bool favorleft=false) {   // returns taller child
        int x;
        if (favorleft) x = 1;   // if L and R same height -> return L
        else x = 0;
        if (t->left_height() + x > t->right_height()) return t->left;
        return t->right;
    }

    node *tall_grandchild(node *t) {
        node *child = tall_child(t);
        bool alignment = (child == t->left);
        return tall_child(child, alignment);
    }

    void relink(node *parent, node *child, bool make_left_child) {  // makes child
        if (make_left_child) parent->left = child;
        else parent->right = child;
        if (child != nullptr) child->parent = parent;
    }

    node *restructure(node *x) {    // LL, RR, LR, RL -> middle value (B) becomes root
        node *y = x->parent;    // parent
        node *z = y->parent;    // grandparent
        if ((x == y->right) == (y == z->right)) {   // LR or RL
            rotate(y);
            return y;
        } else {    // LL or RR
            rotate(x);
            rotate(x);
            return x;
        }
    }

    void rotate(node *t) {
        node *x = t;
        node *y = x->parent;    // parent
        node *z = y->parent;    // grandparent
        if (z == nullptr) {     // if x is below root, then it becomes root
            root = x;
            x->parent = nullptr;
        } else relink(z, x, y==z->left);    // pushes x up, thus becomes z's child

        if (x == y->left) {     // swaps x and y
            relink(y, x->right, true);
            relink(x, y, false);
        } else {
            relink(y, x->left, false);
            relink(x, y, true);
        }
    }


public:

    AVL() {
        root = nullptr;
    };

    int getSize() {return size;};

    void insert(KeyType& x) { _insert(x); };

    KeyType find(const string &movieName) {
        return _find<string>(root, movieName)->key;
    };

    int getHeight() {return height(root);};

    vector<KeyType> list() {
        vector<KeyType> list;
        inorder(root, list);
        return list;
    };
};