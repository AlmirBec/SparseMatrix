#ifndef LIST_CPP
#define LIST_CPP

#include "list.h"
template <typename Type>
void List<Type>::init() {
  tail = new Node(Type(), 0);
  head = new Node(Type(), -1, tail);
  tail->prev = head;
  n = 0;
}

template <typename Type>
typename List<Type>::Iterator List<Type>::Insert(List<Type>::Iterator it, Type value) {
    //Posto insertujemo prije novog cvora pozicija novog cvora ce biti za jedan manja, ali ce se pozicija starog za jedan povecat
    auto it2 = it;
    while(it2 != nullptr){
        it2.node->position = it2.node->position + 1;
        it2 = it2.node->next;
    }
  it.node->prev = new Node(value , it.node->position - 1, it.node, it.node->prev);
  it.node->prev->prev->next = it.node->prev;
  n++;
  return it.node->prev;
}

template <typename Type>
typename List<Type>::Iterator List<Type>::Insert(List<Type>::Iterator it, Type value, int position) {
  it.node->prev = new Node(value , position, it.node, it.node->prev);
  it.node->prev->prev->next = it.node->prev;
  n++;
  return it.node->prev;
}

template <typename Type>
typename List<Type>::Iterator List<Type>::Erase(Iterator it) {
  it.node->prev->next = it.node->next;
  it.node->next->prev = it.node->prev;
  Iterator it2(it.node->next);
  delete it.node;
  n--;
  return it2;
}

template <typename Type>
List<Type>::List(int n, Type value) {
  init();
  for(int i = 0; i < n; i++)
    PushBack(value);
}

template <typename Type>
List<Type>::List(const List<Type> &Copy) {
  init();
  Node* pom;
  for(Node* node = Copy.head->next; node != Copy.tail; node = node->next) {
    Insert(tail, node->value, node->position);
  }
}
template <typename Type>
List<Type>::List(List<Type> &&Copy) {
  head = Copy.head;
  tail = Copy.tail;
  n = Copy.n;
  Copy.head = nullptr;
  Copy.tail = nullptr;
  Copy.n = 0;
}

template <typename Type>
List<Type>& List<Type>::operator=(const List<Type> &rhs) {
  if(this == &rhs)
    return *this;
  Clear();
  for(Node* node = rhs.head->next; node != rhs.tail; node = node->next) {
    Insert(tail, node->value, node->position);
  }
  return *this;
}
template <typename Type>
List<Type>& List<Type>::operator=(List<Type> &&rhs) {
  Clear();
  delete head;
  delete tail;
  head = rhs.head;
  tail = rhs.tail;
  n = rhs.n;
  rhs.head = nullptr;
  rhs.tail = nullptr;
  rhs.n = 0;
  return *this;
}

template <typename Type>
void List<Type>::ForEach(void (*Action)(Type &, int &)) {
  for(Node* node = head->next; node != tail; node = node->next)
    Action(node->value, node->position);
}

#endif // LIST_CPP
