#ifndef BST_H
#define BST_H

#include <iostream>

template <typename T>
class BST {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insert(Node*& node, const T& value) {
        if (!node) {
            node = new Node(value);
        }
        else if (value < node->data) {
            insert(node->left, value);
        }
        else {
            insert(node->right, value);
        }
    }

    void remove(Node*& node, const T& value) {
        if (!node) return;

        if (value < node->data) {
            remove(node->left, value);
        }
        else if (value > node->data) {
            remove(node->right, value);
        }
        else {
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                node = temp;
            }
            else if (!node->right) {
                Node* temp = node->left;
                delete node;
                node = temp;
            }
            else {
                Node* temp = findMin(node->right);
                node->data = temp->data;
                remove(node->right, temp->data);
            }
        }
    }

    Node* findMin(Node* node) const {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    bool search(Node* node, const T& value) const {
        if (!node) return false;
        if (value == node->data) return true;
        if (value < node->data) return search(node->left, value);
        return search(node->right, value);
    }

    T find(Node* node, const T& value) const {
        if (!node) throw std::out_of_range("Service not found");
        if (value == node->data) return node->data;
        if (value < node->data) return find(node->left, value);
        return find(node->right, value);
    }

    void inOrderTraversal(Node* node, void (*visit)(const T&)) const {
        if (!node) return;
        inOrderTraversal(node->left, visit);
        visit(node->data);
        inOrderTraversal(node->right, visit);
    }

public:
    BST() : root(nullptr) {}

    void insert(const T& value) {
        insert(root, value);
    }

    void remove(const T& value) {
        remove(root, value);
    }

    bool search(const T& value) const {
        return search(root, value);
    }

    T find(const T& value) const {
        return find(root, value);
    }

    void inOrderTraversal(void (*visit)(const T&)) const {
        inOrderTraversal(root, visit);
    }
};

#endif