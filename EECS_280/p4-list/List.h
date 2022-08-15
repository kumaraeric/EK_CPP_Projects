#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  List(); //done

  List(const List<T> &other); //done

  ~List(); //done

  List<T> &operator = (const List<T> &rhs); //done

  //EFFECTS:  returns true if the list is empty
  bool empty() const; //done

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
  int size() const; //done

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front(); //done

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back(); //done

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum); //done

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum); //done

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front(); //done

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back(); //done


  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear(); //done

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

private:
  int List_size; 
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other); //done

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty

public:
  ////////////////////////////////////////
  class Iterator {
    //OVERVIEW: Iterator interface to List
  friend class List;
    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

    Iterator& operator++() {
      assert(node_ptr);
      node_ptr = node_ptr->next;
      return *this;
    }

    T& operator*() {
      assert(node_ptr);
      return node_ptr->datum;
    }

    bool operator ==(Iterator rhs)const{
      return node_ptr == rhs.node_ptr;
    }

    bool  operator !=(Iterator rhs)const{
      return node_ptr != rhs.node_ptr;
    }

    Iterator():node_ptr(nullptr){}

    ~Iterator(){
       node_ptr = nullptr;
    }

    Iterator(const Iterator &other):node_ptr(other.node_ptr){}

    Iterator &operator = (const Iterator &rhs){
      if(this==&rhs){
        return *this;
      }
      node_ptr = rhs.node_ptr;
      return *this;
    }

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here

    // construct an Iterator at a specific position
    Iterator(Node *p):node_ptr(p){}

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  //done
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const{
    return Iterator(nullptr);
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i){
    assert(!empty() && i!=end());
    if(i==begin()){
      pop_front();
    }
    else if(i.node_ptr == last){
      pop_back();
    }
    else{
      Node* p_b = i.node_ptr->prev; 
      Node* p_a = i.node_ptr->next; 
      p_b->next = p_a; 
      p_a->prev = p_b; 
      delete i.node_ptr; 
      List_size--;
    }    
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum){
    if(i==begin()){
      push_front(datum);
    }
    else if(i==end()){
      push_back(datum);
    }
    else{
      Node* holder_b = i.node_ptr->prev; 
      Node* holder = i.node_ptr; 

      Node *p = new Node; 
      p->datum = datum; 
      p->next = holder; 
      p->prev = holder_b; 

      holder_b->next = p; 
      holder->prev = p; 
      List_size++;
    }   
  }

};

//List

////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.

template<typename T>
List<T>::List():List_size(0),first(nullptr),last(nullptr){
}

template<typename T>
List<T>::List(const List<T> &other):List(){
  copy_all(other);
}

template <typename T>
List<T> & List<T>::operator = (const List<T> &rhs){
  if(this==&rhs){
    return *this;
  }
  clear();
  copy_all(rhs);
  return *this;
}

template<typename T>
List<T>::~List(){
  clear();
}

template<typename T>
void List<T>::copy_all(const List<T> &other){
    assert(empty());
    Node* other_holder =  other.first; 
    while(other_holder!=nullptr){
      push_back(other_holder->datum);
      other_holder = other_holder->next;
    }
  }

//default - done
//copy - done
//destructor - done
//assignment - done

template <typename T> 
T & List<T>::front(){
  assert(!empty());
  return first->datum;
}

template<typename T>
int List<T>::size() const{
  return List_size; 
}

template <typename T> 
T & List<T>::back(){
  assert(!empty());
  return last->datum;
}

template <typename T> 
bool List<T>::empty() const{
  if(first == nullptr || last ==nullptr ||size()==0){
    return true; 
  }
  return false;
}

template<typename T>
void List<T>::push_back(const T &datum){
  Node *p = new Node;
  p->datum = datum;
  p->next = nullptr; 
  p->prev = last;
  if(empty()){
    last = first = p; 
  }
  else{
    last->next = p;
    last = p;
  }
  List_size++;
}

template<typename T>
void List<T>::push_front(const T &datum){
  Node *p = new Node;
  p->datum = datum;
  p->prev = nullptr;
  p->next = first; 
  if(empty()){
    last = first = p; 
  }
  else{
    first->prev = p;
    first = p;
  }
  List_size++;
}

 template<typename T>
 void List<T>::pop_front(){
   assert(!empty());
   Node *holder = first; 
   first = holder->next;
   delete holder;
   holder = nullptr; 
   List_size--;
   if(size()==0){
    first = nullptr;
    last = nullptr; 
  }
 }

template <typename T>
void List<T>::pop_back(){
  assert(!empty());
  Node * holder = last;
  last = holder -> prev;
  delete holder;
  holder = nullptr;
  List_size--;
  if(size()==0){
    first = nullptr;
    last = nullptr; 
  }
}

template<typename T>
void List<T>::clear(){
  while(!empty()){
    pop_front();
  }
}

#endif // Do not remove this. Write all your code above this line.
