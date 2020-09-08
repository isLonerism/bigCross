// node.h

struct Node {
    int value;
    Node *next;

    class iterator : public std::iterator<std::input_iterator_tag, Node> {
        Node* n;
    public:
        iterator(Node* n) : n(n) {}
        iterator(const iterator& it) :n(it.n) {}
        iterator& operator++() { n = n->next; return *this; }
        iterator operator++(int) { iterator tmp(*this); operator++(); return tmp; }
        bool operator==(const iterator& it) const { return n == it.n; }
        bool operator!=(const iterator& it) const { return n != it.n; }
        Node& operator*() { return *n; }
    };
};