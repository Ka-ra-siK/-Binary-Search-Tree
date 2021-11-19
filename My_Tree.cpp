#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include "time.h"
#include <math.h>
using namespace std;

template<class T, class Tk>
class BSTree { //��������� ����� ��� ������� ������
public:
    int size; //������ ���������(����� ��������� � �������)
    int ops;
    class Node {
    public:
        Tk key; //�������� �����
        T data; //�������� ������
        Node *left; //��������� �� ������ ����
        Node *right; //��������� �� ������� ����
        Node(Tk key, T data) {
            this->key = key;
            this->data = data;
            this->left = NULL;
            this->right = NULL;
        }
        Node* copyTree(Node* TreePtr) {
            Node* newlptr;
            Node* newrptr;
            if (TreePtr == NULL)
                return NULL;
            if (TreePtr->left != NULL)
                newlptr = copyTree(TreePtr->left);
            else
                newlptr = NULL;
            if (TreePtr->right != NULL)
                newrptr = copyTree(TreePtr->right);
            else
                newrptr = NULL;
            Node* newNode = new Node(TreePtr->key, TreePtr->val);
            newNode->left = newlptr;
            newNode->right = newrptr;
            return newNode;
        };

    };

public:
    BSTree(); //�����������
    BSTree(const BSTree &t);// ����������� �����������
    ~BSTree(); //����������
    int getSize() { return size; };
    Node *getRoot() { return root; };
    void remove(Node *removeNode);
    void print();
    void printTree(Node *currentNode, int level);
    bool LTR(Node *currentNode);
    bool add(Tk key, T data);
    bool clearTree();
    bool isClear();
    bool remove(Tk key);
    T find(Tk key);
    T getKey(Node *t);
    T getData(Node *t);
    T rewriteData(Tk key, T data);
    Node* root; //������ BST
    mutable size_t operations;
    inline int getOps() { return ops; }

    class Iterator_base {
    protected:
        Node *_current;
        Node *_parent;
        std::vector<Node *> nodes;
        void setNode(const BSTree<T, Tk>& srcBst);
        virtual void setNodeHelp(Node* t);

    public:
        Iterator_base();
        ~Iterator_base();
    };

    class Iterator : public Iterator_base {
    protected:
        Node* cur;
        std::vector<Node*> nodes;
        void setNode(const BSTree<T, Tk>& srcBst);
        void setNodeHelp(Node* t);

    public:
        Iterator(Node *node, Node *parent);
        Iterator() {};
        Iterator(const BSTree<T, Tk>& srcBst);
        ~Iterator();
        void begin();
        void end();
        Iterator& operator++();
        Iterator& operator--();
        bool operator==(const Iterator& src);
        bool operator!=(const Iterator& src);
        Node* operator*();
    };

    class Inverse_iterator : public Iterator_base {
    protected:
        Node* cur;
        std::vector<Node*> nodes;
        void setNode(const BSTree<T, Tk>& srcBst);
        void setNodeHelp(Node* t);

    public:
        Inverse_iterator(Node* node, Node* parent);
        Inverse_iterator() {};
        Inverse_iterator(const BSTree<T, Tk>& srcBst);
        ~Inverse_iterator();
        void rBegin();
        void rEnd();
        Inverse_iterator& operator++();
        Inverse_iterator& operator--();
        bool operator==(const Inverse_iterator& src);
        bool operator!=(const Inverse_iterator& src);
        Node* operator*();
    };

};

template<class T, class Tk>
BSTree<T, Tk>::BSTree() {
    this->size = 0;
    this->ops = 0;
    this->root = NULL;
    this->operations = 0;
}

template<class T, class Tk>
BSTree<T, Tk>::BSTree(const BSTree &t) {
    this->size = t->size;
    this->root = copyTree(t->root);
}

template<class T, class Tk>
BSTree<T, Tk>::~BSTree() {
    clearTree();
    delete this->root;
    cout << "���������� ��������" << endl;
}

template<class T, class Tk>
void BSTree<T, Tk>::remove(Node *removeNode) {
    Node *left_tree = removeNode->left;
    Node *right_tree = removeNode->right;
    if (left_tree != NULL)
        remove(left_tree);
    if (right_tree != NULL)
        remove(right_tree);
    return;
}

template<class T, class Tk>
bool BSTree<T, Tk>::add(Tk key, T data) { //������� �������� � ������
    if (this->root == NULL) { //���� ��� �����
        this->root = new Node(key, data);
        this->size++;
        ops = 1;
        return true;
    } else {
        Node *currentNode = this->root;
        ops = 1;
        Node *prevNode = NULL;
        while (currentNode != NULL) {
            prevNode = currentNode;
            if (key == currentNode->key)
                return false;
            else if (key < currentNode->key)
                currentNode = currentNode->left;
            else
                currentNode = currentNode->right;
        }
        if (key < prevNode->key) {
            prevNode->left = new Node(key, data);
            currentNode = prevNode->left;
        } else {
            prevNode->right = new Node(key, data);
            currentNode = prevNode->right;
        }
        ops++;
    }
    this->size++;
    return true;
}

template<class T, class Tk>
bool BSTree<T, Tk>::clearTree() { //������� ������
    if (this->size == 0)
        return false;
    this->remove(this->root);
    this->size = 0;
    this->root = NULL;
    cout << "��������� ������� ������" << endl;
    return true;
}

template<class T, class Tk>
bool BSTree<T, Tk>::isClear() { //�������� �� �������
    if (this->size == 0)
        return true;
    else
        return false;
}

template<class T, class Tk>
bool BSTree<T, Tk>::remove(Tk key) { //���������� �� ������
    if (isClear()) //�������� �� �������
        throw "������ ��� �����";
    Node *currentNode = this->root;
    Node *prevNode = NULL;
    ops = 1;
    while (currentNode != NULL) { //����� �������� �� ������
        if (key == currentNode->key)
            break;
        ops++;
        prevNode = currentNode;
        if (key < currentNode->key)
            currentNode = currentNode->left;
        else
            currentNode = currentNode->right;
    }

    if (currentNode == NULL) //���� �� ������
        return false;


    //���� ��� ����
    if ((currentNode->right == NULL) || (currentNode->left == NULL)) {
        Node *intermediaryNode; //
        if ((currentNode->right == NULL) && (currentNode->left == NULL)) //���� ��� ������� ������
            intermediaryNode = NULL;
        else if (currentNode->right == NULL) //���� ������ ��� ����, �� ��������� ������ ����
            intermediaryNode = currentNode->left;
        else //���� ����� ��� ����, �� ���������� ������� ����
            intermediaryNode = currentNode->right;

        if (this->root->key == key)
            this->root = intermediaryNode;
        else {
            if (key < prevNode->key)
                prevNode->left = intermediaryNode;
            else
                prevNode->right = intermediaryNode;
        }
    } else { //���� 2 ����
        Node *intermediaryNode = currentNode->right;
        Node *prevIntermediaryNode = currentNode;
        while (intermediaryNode != NULL) { //���� �� ������ ����� ����������� (����� �����) �������
            if (intermediaryNode->left != NULL) {
                prevIntermediaryNode = intermediaryNode;
                intermediaryNode = intermediaryNode->left;
            } else
                break;
        }
        if (prevIntermediaryNode != currentNode) { // ���� � ������ ��������� ���������� �������� ���� ����� ���
            prevIntermediaryNode->left = intermediaryNode->right;
        }
        if (key == this->root->key) { //���� ��������� ������� - ������
            this->root = intermediaryNode;
            intermediaryNode->left = currentNode->left;
            if (currentNode->right != intermediaryNode) {
                intermediaryNode->right = currentNode->right;
            }
        } else {
            if (key < prevNode->key) {
                prevNode->left = intermediaryNode;
                intermediaryNode->left = currentNode->left;
                if (currentNode->right != intermediaryNode)
                    intermediaryNode->right = currentNode->right;
            } else {
                prevNode->right = intermediaryNode;
                if (currentNode->right != intermediaryNode)
                    intermediaryNode->right = currentNode->right;
                intermediaryNode->left = currentNode->left;
            }

        }
    }
    delete currentNode;
    this->size--;
    return true;
}

template<class T, class Tk>
//����� �� ������
T BSTree<T, Tk>::find(Tk key) {
    if (isClear()) {
        cout << "������ �����" << endl;
        return T();
    }
    Node *t = this->root;
    ops = 1;
    while (t != NULL && key != t->key) {
        if (key < t->key)
            t = t->left;
        else
            t = t->right;
        ops++;
    }
    if (t == NULL) {
       // cout << "���� � �������� ������ �� ����������" << endl;
        return 0;
    } else {
        return t->data;
    }
}

template<class T, class Tk>
T BSTree<T, Tk>::getKey(Node *t) {
    return t->key;
}

template<class T, class Tk>
T BSTree<T, Tk>::getData(Node *t) {
    return t->data;
}

template<class T, class Tk>
T BSTree<T, Tk>::rewriteData(Tk key, T data_) {
    if (isClear()) {
        //throw "������ �����";
        cout << "������ �����" << endl;
        return 0;
    }
    Node *t = this->root;
    while (t != NULL && key != t->key) {
        if (key < t->key)
            t = t->left;
        else
            t = t->right;
    }
    if (t == NULL) {
        return 0;
    } else {
        t->data = data_;
        return 1;
    }
}

template<class T, class Tk>
void BSTree<T, Tk>::print() {
    if (this->size == 0)
        throw "������ �����";
    printTree(this->root, 0);
}

template<class T, class Tk>
void BSTree<T, Tk>::printTree(Node *currentNode, int level) {
    if (level == 0)
        cout << "������ ������ ������ � �������:" << endl;
    if (currentNode == NULL)
        return;

    printTree(currentNode->right, level + 1);
    for (int i = 0; i < level * 2; i++)
        cout << "   ";
    cout << currentNode->key << "[" << currentNode->data << "]" << endl << endl;
    printTree(currentNode->left, level + 1);
}

template<class T, class Tk>
bool BSTree<T, Tk>::LTR(Node *currentNode) { // ����� ������ L-t-R
    Node *q;
    if (size == 0) {
        cout << "������ �����";
        return false;
    }
    if (currentNode != NULL) {
        q = currentNode->left;
        LTR(q);
        cout << currentNode->key << " - ";
        q = currentNode->right;
        LTR(q);
    }
    return true;
};

/*
��������
*/

template<class T, class Tk>
BSTree<T, Tk>::Iterator::Iterator(const BSTree<T, Tk>& srcBst){
    if (srcBst.size <= 0){
        std::cout << "������ �����" << std::endl;
    }
    else{
        this->setNode(srcBst);
    }
}
template<class T, class Tk>
BSTree<T, Tk>::Iterator::~Iterator(){
}
template<class T, class Tk>
BSTree<T, Tk>::Inverse_iterator::Inverse_iterator(const BSTree<T, Tk>& srcBst){
    if (srcBst.size <= 0){
        std::cout << "������ �����" << std::endl;
    }
    else{
        this->setNode(srcBst);
    }
}
template<class T, class Tk>
BSTree<T, Tk>::Inverse_iterator::~Inverse_iterator(){
}
template<class T, class Tk>
BSTree<T, Tk>::Iterator_base::Iterator_base(){
}
template<class T, class Tk>
BSTree<T, Tk>::Iterator_base::~Iterator_base(){
}
template<class T, class Tk>
void BSTree<T, Tk>::Iterator_base::setNodeHelp(Node* t){
}
template<class T, class Tk>
void BSTree<T, Tk>::Iterator::setNode(const BSTree<T, Tk>& srcBst){
    setNodeHelp(srcBst.root);
    if (nodes.size() != 0)
        this->cur = nodes[0];
    else
        std::cout << "�������� �� ����������" << std::endl;
}
template<class T, class Tk>
void BSTree<T, Tk>::Iterator::setNodeHelp(Node* t){
    if (t != nullptr){
        setNodeHelp(t->left);
        this->nodes.push_back(t);
        setNodeHelp(t->right);
    }
}
template<class T, class Tk>
void BSTree<T, Tk>::Inverse_iterator::setNode(const BSTree<T, Tk>& srcBst){
    setNodeHelp(srcBst.root);
}
template<class T, class Tk>
void BSTree<T, Tk>::Inverse_iterator::setNodeHelp(Node* t){
    if (t != nullptr){
        setNodeHelp(t->right);
        this->nodes.push_back(t);
        setNodeHelp(t->left);
    }
}
template<class T, class Tk>
typename BSTree<T, Tk>::Iterator&::BSTree<T, Tk>::Iterator::operator++(){
    if (nodes.size() <= 0)
        throw std::runtime_error("�������� �� ����������");
    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i]->key == cur->key)
        {
            if (i == nodes.size() - 1)
            {
                std::cout << "�������� �� ��������" << std::endl;
                return *this;
            }
            else
                cur = nodes[i + 1];
            break;
        }
    }
    return *this;
}
template<class T, class Tk>
typename BSTree<T, Tk>::Iterator& ::BSTree<T, Tk>::Iterator::operator--(){
    if (nodes.size() <= 0)
        throw std::runtime_error("�������� �� ����������");
    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i]->key == cur->key)
        {
            if (i == 0)
            {
                std::cout << "�������� �� ��������" << std::endl;
                return *this;
            }
            else
                cur = nodes[i - 1];
            break;
        }
    }
    return *this;
}
template<class T, class Tk>
void BSTree<T, Tk>::Iterator::begin(){
    if (nodes.size() != 0)
        this->cur = nodes[0];
    else
        std::cout << "�������� �� ����������" << std::endl;
}
template<class T, class Tk>
void BSTree<T, Tk>::Iterator::end(){
    if (nodes.size() != 0)
        this->cur = nodes[nodes.size() - 1];
    else
        std::cout << "�������� �� ����������" << std::endl;
}
template<class T, class Tk>
bool BSTree<T, Tk>::Iterator::operator==(const Iterator& src){
    {
        if (src == nullptr)
        {
            if (cur == nullptr)
                return true;
            else
                return false;
        }
        else
        {
            if (cur == nullptr)
                return true;
            else
                return cur->key != src->key;
        }
    }
}
template<class T, class Tk>
bool BSTree<T, Tk>::Iterator::operator!=(const Iterator& src){
    return !(*this == src);
}
template<class T, class Tk>
typename BSTree<T, Tk>::Node* ::BSTree<T, Tk>::Iterator::operator*(){
    return cur;
}
template<class T, class Tk>
typename BSTree<T, Tk>::Inverse_iterator& ::BSTree<T, Tk>::Inverse_iterator::operator++(){
    if (nodes.size() <= 0)
        throw std::runtime_error("�������� �� ����������");
    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i]->key == cur->key)
        {
            if (i == nodes.size() - 1)
            {
                std::cout << "�������� �� ��������" << std::endl;
                return *this;
            }
            else
                cur = nodes[i + 1];
            break;
        }
    }
    return *this;
}
template<class T, class Tk>
typename BSTree<T, Tk>::Inverse_iterator& ::BSTree<T, Tk>::Inverse_iterator::operator--(){
    if (nodes.size() <= 0)
        throw std::runtime_error("�������� �� ����������");
    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i]->key == cur->key)
        {
            if (i == 0)
            {
                std::cout << "�������� �� ��������" << std::endl;
                return *this;
            }
            else
                cur = nodes[i - 1];
            break;
        }
    }
    return *this;
}
template<class T, class Tk>
void BSTree<T, Tk>::Inverse_iterator::rBegin(){
    if (nodes.size() != 0)
        this->cur = nodes[0];
    else
        std::cout << "�������� �� ����������" << std::endl;
}
template<class T, class Tk>
void BSTree<T, Tk>::Inverse_iterator::rEnd(){
    if (nodes.size() != 0)
        this->cur = nodes[nodes.size() - 1];
    else
        std::cout << "�������� �� ����������" << std::endl;
}
template<class T, class Tk>
bool BSTree<T, Tk>::Inverse_iterator::operator==(const Inverse_iterator& src){
    {
        if (src == nullptr)
        {
            if (cur == nullptr)
                return true;
            else
                return false;
        }
        else
        {
            if (cur == nullptr)
                return true;
            else
                return cur->key != src->key;
        }
    }
}
template<class T, class Tk>

bool BSTree<T, Tk>::Inverse_iterator::operator!=(const Inverse_iterator& src){
    return !(*this == src);
}
template<class T, class Tk>
typename BSTree<T, Tk>::Node* ::BSTree<T, Tk>::Inverse_iterator::operator*(){
    return cur;
}