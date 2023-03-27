#ifndef LIST_H
#define LIST_H

template <typename Type>
class List {
  struct Node {
    Type value;
    Node *next,*prev;
    int position;
    Node(Type value, int position = 0, Node* next = nullptr, Node* prev = nullptr):value(value),position(position),next(next),prev(prev) {}
  };

  public:
  class Const_Iterator {
    protected:
    Node* node;
    public:
    int getPosition(){
    return node->position;
    }
    void setPosition(int pos){
        node->position = pos;
    }
    Const_Iterator(Node *node = nullptr):node(node) {}
    Type operator*() { return node->value; }
    Const_Iterator operator++() { node = node->next; return *this; }
    Const_Iterator operator++(int) { Const_Iterator Copy(*this); node = node->next; return Copy; }
    Const_Iterator operator--() { node = node->prev; return *this; }
    Const_Iterator operator--(int) { Const_Iterator Copy(*this); node = node->prev; return Copy; }
    friend bool operator==(Const_Iterator it1, Const_Iterator it2) { return it1.node == it2.node; }
    friend bool operator!=(Const_Iterator it1, Const_Iterator it2) { return it1.node != it2.node; }
    friend class List<Type>;
  };
  class Iterator: public Const_Iterator {
    public:
    Iterator(Node *node = nullptr):Const_Iterator(node) {}
    Type& operator*() { return Iterator::node->value; }
    Iterator operator++(){this->node = this->node->next; return *this;}
    Iterator operator++(int){
        Iterator Copy(*this); this->node = this->node->next; return Copy;
    }
    Iterator operator--(){this->node = this->node->prev; return *this;}
    Iterator operator--(int){
        Iterator Copy(*this); this->node = this->node->prev; return Copy;
    }
    friend bool operator ==(Iterator it1, Iterator it2){
    return it1.node == it2.node;
    }
    friend bool operator!=(Iterator it1, Iterator it2){
    return it1.node != it2.node;
    }
    friend class List<Type>;
  };

  private:
  Node* head;
  Node* tail;
  int n;
  void init();

  public:
    List() { init(); }
    List(int n, Type value = Type());
    List(const List<Type> &Copy);
    List(List<Type> &&Copy);
    List<Type>& operator=(const List<Type> &rhs);
    List<Type>& operator=(List<Type> &&rhs);
    ~List() { Clear(); delete head; delete tail; }
    int Size() { return n; }
    bool Empty() { return n == 0; }
    Iterator Insert(Iterator it, Type value);
    //Da lakse ubacujemo listu na odredjenu poziciju
    Iterator Insert(Iterator it, Type value, int position);
    void PushFront(Type value) { Insert(head->next, value); }
    void PushBack(Type value) { Insert(tail,value); }
    //void PushBack(Type value){}
    Iterator Erase(Iterator it);
    void PopBack() { Erase(tail->prev); }
    void PopFront() { Erase(head->next); }
    void Clear() { while(!Empty()) PopFront(); }
    void ForEach(void (*Action)(Type &, int &));
    Iterator Begin() { return head->next; }
    Const_Iterator Begin() const { return head->next; }
    Iterator End()  { return tail; }
    Const_Iterator End() const { return tail; }
};

#include "list.cpp"

#endif // LIST_H
