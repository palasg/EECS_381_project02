/* Ordered_list is a linked-list class template  with iterators similar to
the Standard Library std::list class. Each list node contains an object of the
type specified in the first template parameter, T.

This is an ordered list in that the nodes are automatically kept in order. The
type of the ordering function is a second template parameter, OF (for Ordering
Function), whose default value is a type given by a small template for a
function object class that orders two objects of type T using that type's
less-than operator. Thus the default is to order objects from smallest to
largest using their defined less-than relationship. Another template provides a
function object class that orders two pointers to objects of type T by
dereferencing the pointers and applying T's less-than operator. For example:

    // Thing objects in order by Thing::operator<.
        Ordered_list<Thing, Less_than_ref> ol_things;

        // the same as above, by default
        Ordered_list<Thing> ol_things;

    // Thing pointers in order by Thing::operator< applied to dereferenced
pointers. Ordered_list<Thing*, Less_than_ptrs> ol_things;

    // Thing pointers in order by a custom ordering.
        Ordered_list<Thing*, My_ordering_class> ol_things;

The only way to add to the list is with the insert function, which automatically
puts the new item in the proper place in the list using the ordering function to
determine the point of insertion. If a matching object is already in the list
(as determined by the ordering function) the insertion fails - the list is not
modified, and false is returned by the insert function.

The iterators encapsulate a pointer to the list nodes, and are a public class
nested within the Ordered_list class, and would be declared e.g. as
Ordered_list<Thing*, Less_than_ptr>::Iterator;
Operators ++, *, and -> are overloaded for iterators similar to
std::list<>::iterator.

This container supports const operations; if the container is declared as a
const object, then the compiler will automatically apply the const versions of
the begin(), end(), and find() functions, which will return const_Iterators. A
const_Iterator can not be used to modify the data to which it points.
const_Iterators are also a public class nested within the Ordered_list class.

Copy constructor and assignment operators are defined, so that Ordered_lists can
be used like built-in types. Move construction and assignment operators are also
defined, consistent with C++11 container library practice.

The operations on Ordered_list provide exception safety in the form of the basic
exception guarantee - if an attempt to create or modify an Ordered_list fails
and an exception is thrown, no memory is leaked and the exception is propagated
out to the client code to catch. In addition, the relevant operations also
provide the strong exception guarantee - if an attempt to modify an Ordered_list
fails, it is left in its original state, and the exception is propagated out to
the client code to catch. Finally, many operations also provide the no-throw
guarantee and are specified with noexcept. See comments on individual member
functions for specifics.

To find an object in the list that matches a supplied "probe" object, the
ordering function is used to determine equality. That is, the find functions
assume that if both (x < y) and (y < x) are false, then x == y. This allows both
insert and find operations to be done with only the less-than relation.

When an object is inserted in the list using the copy version of insert,
a list node is constructed that contains a copy of the supplied object,
so objects stored in the list must have accessible and properly defined copy
constructors. The move version of the insert function will attempt to move
construct the supplied object in the new list node instead of copying it. A move
constructor for the object must be available for this to happen.

When a node is removed from the list with erase(), it is destroyed, and so a
class-type object contained in the node must have an accessible and properly
defined destructor function. When the list is destroyed, or cleared with the
clear() function, all of the list nodes are destroyed.

Unless the container is declared to be const, this class does not protect the
list items from being modified. If a list item is modified in a way that changes
where it should appear in the list, the list will become disordered and list
items may become un-findable or new items will be inserted incorrectly - the
effects are undefined, although a specific implementation might behave in a
predictable manner. It is user's responsibility to ensure that items are not
changed in a way that affects the validity of the ordering in the list.

If the user declares a list of pointers to objects, the user is responsible for
allocating and deallocating the pointed-to objects. Note especially that if the
Ordered_list is deallocated or cleared, or a single node is erased from the
list, the pointed-to data is NOT deallocated. In short, the Ordered_list does
not attempt to manage the user's objects.

If any operations are attempted that are erroneous (e.g. erasing a non-existent
node), the results are undefined.

This module includes some function templates for applying functions to items in
the container, using iterators to specify the range of items to apply the
function to.

All Ordered_list constructors and the destructor increment/decrement
g_Ordered_list_count. The list Node constructors and destructor
increment/decrement g_Ordered_list_Node_count.
*/

/* *** NOTE:
This is a "skeleton" for the header file. Its purpose is to specify what must be
in the correct header file while leaving you the job of creating the correct
header file. Thus there is a variety of items you will have to add to this file
to get a complete correct header file.

If there is a comment "fill this in" remove the comment and replace
it with the proper code here in the header file.

Comments starting with "***" are instructions to you - remove them from your
finished code. Remove this comment too. */

#ifndef ORDERED_LIST_H
#define ORDERED_LIST_H

#include <cassert>
#include <utility>

#include "Globals.hpp"

// These Function Object Class templates make it simple to use a class's
// less-than operator for the ordering function in declaring an Ordered_list
// container. These declare operator() as a const member function because the
// function does not modify the state of the function object, meaning that it
// can be used in a const member function of the Ordered_list class.

// Compare two objects (passed by const&) using T's operator<
template <typename T>
struct Less_than_ref {
  bool operator()(const T& t1, const T& t2) const { return t1 < t2; }
};

// Compare two pointers (T is a pointer type) using *T's operator<
template <typename T>
struct Less_than_ptr {
  bool operator()(const T p1, const T p2) const { return *p1 < *p2; }
};

// A custom ordering function object class is similar, but no template is
// needed. For example:
//  struct My_ordering_class {
//		bool operator() (const Thing* p1, const Thing* p2) const {return
///* whatever you want */;}
//	};

// Forward declaration of the Ordered_list
template <typename T, typename OF>
class Ordered_list;

// Node is a template class for a node in an Ordered_list. Because it is an
// implementation detail of Ordered_list, it has no public interface - all of
// its members are private, but it declares class Ordered_list<T, OF> as a
// friend. The supplied members are shown to make it clear when the node count
// should be incremented or decremented. Because it has no public interface, you
// can add members of your choice, such as special constructors. T is the type
// of the objects in the list - the data item in the list node. See
// Stroustrup 23.4.6.3.
template <typename T>
class Node {
 private:
  // declare the client class as a friend - note we use different template
  // parameter names here
  template <typename A, typename B>
  friend class Ordered_list;

  // Construct a node containing a copy of the T data; the copy operation
  // might throw an exception, so the basic and strong guarantee should
  // be satisfied as long as the copy is attempted before the containing list is
  // modified.
  Node(const T& new_datum, Node* new_prev, Node* new_next)
      : datum(new_datum), prev(new_prev), next(new_next) {
    g_Ordered_list_Node_count++;
  }

  // Move version constructs a node using a rvalue reference to the new datum
  // and move constructs the datum member variable from it, using its move
  // constructor.
  Node(T&& new_datum, Node* new_prev, Node* new_next)
      : datum(std::move(new_datum)), prev(new_prev), next(new_next) {
    g_Ordered_list_Node_count++;
  }

  // Copy constructor, move constructor, and dtor defined only to support
  // allocation counting. Node copy constructor should provide the same basic
  // and strong guarantee as Node construction.
  Node(const Node& original)
      : datum(original.datum), prev(original.prev), next(original.next) {
    g_Ordered_list_Node_count++;
  }

  // The following functions should not be needed and so are deleted
  Node(Node&& original) = delete;
  Node& operator=(const Node& rhs) = delete;
  Node& operator=(Node&& rhs) = delete;

  // only defined to support allocation counting
  ~Node() { g_Ordered_list_Node_count--; }

  T datum;
  Node* prev = nullptr;  // pointer to previous node
  Node* next = nullptr;  // pointer to next node
};

// T is the type of the objects in the list - the data item in the list node
// OF is the ordering function object type, defaulting to Less_than_ref for T
template <typename T, typename OF = Less_than_ref<T> >
class Ordered_list {
 public:
  // Default constructor creates an empty container that has an ordering
  // function object
  // of the type specified in the second template type parameter (OF).
  Ordered_list();

  // Copy construct this list from another list by copying its data.
  // The basic exception guarantee:
  // If an exception is thrown when the type T contents of a node are copied,
  // any nodes already constructed are destroyed, so that no memory is leaked,
  // and the exception is then propagated from this constructor.
  Ordered_list(const Ordered_list& original);

  // Move construct this list from another list by taking its data,
  // leaving the original in an empty state (like when default constructed).
  // Since no type T data is copied, no exceptions are possible,
  // so the no-throw guarantee is made.
  Ordered_list(Ordered_list&& original) noexcept;

  // Copy assign this list with a copy of another list, using the copy-swap
  // idiom.
  // Basic and strong exception guarantee:
  // If an exception is thrown during the copy, no memory is leaked, and lhs is
  // unchanged.
  Ordered_list& operator=(const Ordered_list& rhs);

  // Move assignment operator simply swaps the current content with the rhs.
  // Since no type T data is copied, no exceptions are possible,
  // so the no-throw guarantee is made.
  Ordered_list& operator=(Ordered_list&& rhs) noexcept;

  // deallocate all the nodes in this list
  ~Ordered_list() {
    std::cout << "/n inside dtor of ordered list " << std::endl;

    clear();

    // while (m_length> 0 && m_head->next!= nullptr)
    // {
    // 	Node<T>* node_to_delete = m_head;
    // 	m_head = m_head->next;
    // 	node_to_delete->next = nullptr;
    // 	node_to_delete->prev = nullptr;
    // 	delete node_to_delete;
    // 	node_to_delete = nullptr;
    // 	--m_length;
    // }
    // if (m_length==1)
    // {
    // 	delete m_head;
    // 	m_head = nullptr;
    // }
  }

  // Delete the nodes in the list, if any, and initialize it.
  // No exceptions are supposed to happen so the no-throw guarantee is made.
  void clear() noexcept;

  // Return the number of nodes in the list
  std::size_t size() const { return m_length; }

  // Return true if the list is empty
  bool empty() const { return m_length > 0 ? false : true; }

  // Iterator is a public nested class within Ordered_list.
  // An Iterator object designates a Node by encapsulating a pointer to the
  // Node, and provides Standard Library-style operators for using,
  // manipulating,
  // and comparing Iterators. This class is nested inside Ordered_list<> as
  // a public member; refer to as e.g. Ordered_list<int, My_of>::Iterator
  class Iterator {
   public:
    // default initialize to nullptr
    Iterator() : node_ptr(nullptr) {}

    // Overloaded dereferencing operators
    // The * operator returns a reference to the datum in the pointed-to node.
    T& operator*() const {
      assert(node_ptr);
      return node_ptr->datum;
    }
    // The -> operator simply returns the address of the data in the pointed-to
    // node. The compiler reapplies the -> operator with the returned pointer.
    /* *** The definition is supplied here because it is a special-case of
     * operator overloading. */
    T* operator->() const {
      assert(node_ptr);
      return &(node_ptr->datum);
    }

    // Prefix ++ operator moves the iterator forward to point to the next node
    // and returns this iterator.
    Iterator& operator++()  // prefix
    {
      node_ptr = node_ptr->next;
      return *this;
    }
    // Postfix ++ operator saves the current address for the pointed-to node,
    // moves this iterator to point to the next node, and returns
    // an iterator pointing to the node at the saved address.
    Iterator operator++(int)  // postfix
    {
      assert(node_ptr);
      Iterator temp{node_ptr};
      ++*this;
      return temp;
    }
    // Iterators are equal if they point to the same node
    bool operator==(Iterator rhs) const { return !(*this != rhs); }
    bool operator!=(Iterator rhs) const {
      // if both node_ptr are null
      if (rhs.node_ptr == nullptr && node_ptr == nullptr) {
        return false;
      } else if (rhs.node_ptr == nullptr && node_ptr != nullptr) {
        return true;
      } else if (rhs.node_ptr != nullptr && node_ptr == nullptr) {
        return true;
      } else if (rhs.node_ptr != nullptr && node_ptr != nullptr) {
        return rhs.node_ptr != node_ptr;
      }
      return false;
    }

    // *** here, declare the outer Ordered_list class as a friend

    template <typename A, typename B>
    friend class Ordered_list;

   private:
    /* *** define here a private constructor for Iterator that takes a Node<T>*
    parameter. Ordered_list can use this to create Iterators conveniently
    initialized to point to a Node. It is private because the client code can't
    and shouldn't be using it - it isn't even supposed to know about the Node
    objects.  */

    Iterator(Node<T>* node_) : node_ptr(node_) {}
    /* *** you may have additional private member functions, but no additional
     * member variables */
    Node<T>* node_ptr;
  };
  // end of nested Iterator class declaration

  // const_Iterator is a public nested class within Ordered_list.
  // It behaves identically to an Iterator except that it cannot be used to
  // modify the pointed-to data, as shown by its dereferencing operators
  // returning const.
  class const_Iterator {
   public:
    // default initialize to nullptr
    const_Iterator() : node_ptr(nullptr) {}

    // A conversion constructor: construct a const_Iterator from an Iterator
    const_Iterator(Iterator original) : node_ptr(original.node_ptr) {}

    // Overloaded dereferencing operators
    // The * operator returns a const reference to the datum in the pointed-to
    // node.
    const T& operator*() const { return node_ptr->datum; }
    // The -> operator returns the address of the data in the pointed-to node as
    // const.
    const T* operator->() const {
      assert(node_ptr);
      return &(node_ptr->datum);
    }

    // prefix ++ operator moves the iterator forward to point to the next node
    // and returns this iterator.
    const_Iterator& operator++()  // prefix
    {
      node_ptr = node_ptr->next;
      return *this;
    }
    // postfix ++ operator saves the current address for the pointed-to node,
    // moves this iterator to point to the next node, and returns
    // an iterator pointing to the node at the saved address.
    const_Iterator operator++(int)  // postfix
    {
      const_Iterator temp{node_ptr};
      ++*this;
      return temp;
    }
    // const_Iterators are equal if they point to the same node.
    bool operator==(const_Iterator rhs) const { return !(*this != rhs); }
    bool operator!=(const_Iterator rhs) const {
      // if both node_ptr are null
      if (rhs.node_ptr == nullptr && node_ptr == nullptr) {
        return false;
      } else if (rhs.node_ptr == nullptr && node_ptr != nullptr) {
        return true;
      } else if (rhs.node_ptr != nullptr && node_ptr == nullptr) {
        return true;
      } else if (rhs.node_ptr != nullptr && node_ptr != nullptr) {
        return rhs.node_ptr != node_ptr;
      }
    }

    // *** here, declare the outer Ordered_list class as a friend

   private:
    /* *** define here a private constructor for const_Iterator that takes a
    const Node<T>* parameter. Ordered_list can use this to create
    const_Iterators conveniently initialized to point to a Node. It is private
    because the client code can't and shouldn't be using it - it isn't even
    supposed to know about the Node objects.  */
    /* *** you may have additional private member functions, but no additional
     * member variables */
    const Node<T>* node_ptr;
  };
  // end of nested const_Iterator class declaration

  /* Supply begin and end iterators for a non-const container */
  // Return an Iterator pointing to the first node.
  // If the list is empty, the begin Iterator points to "past the end"
  Iterator begin() { return Iterator(m_head); }
  // Return an iterator pointing to "past the end". Sending a nullptr is
  // soemtime troublesome but
  // I do not have any idea how to implement how it could be better
  Iterator end() { return Iterator(); }  // same as next pointer of last node

  // Return a const_Iterator pointing to the first node.
  // If the list is empty, the Iterator points to "past the end".
  const_Iterator cbegin() { return const_Iterator(m_head); }
  // return an iterator pointing to "past the end"
  const_Iterator cend() { return const_Iterator(nullptr); }

  /* Supply begin and end iterators for a const container */
  // Return a const_Iterator pointing to the first node.
  // If the list is empty, the Iterator points to "past the end".
  const_Iterator begin() const { return const_Iterator(m_head); }
  // Return a const_Iterator pointing to "past the end".
  const_Iterator end() const { return const_Iterator(nullptr); }
  // Return a const_Iterator pointing to the first node,
  // If the list is empty, the Iterator points to "past the end"
  const_Iterator cbegin() const { return const_Iterator(m_head); }
  // return a const_Iterator pointing to "past the end".
  const_Iterator cend() const { return const_Iterator(nullptr); }
  // The insert functions add the new datum to the list using the ordering
  // function. If an "equal" datum is already in the list, then the list is not
  // modified and false is returned. Otherwise, the new datum is inserted, and
  // true is returned.
  // A copy of the datum object is made in the new list node.
  bool insert(const T& new_datum);
  // This version of insert provides for moving the contents of a datum
  // into the new list node instead of copying it.
  bool insert(T&& new_datum);

  // The find function returns an iterator designating the node containing
  // the datum that according to the ordering function, is equal to the
  // supplied probe_datum; end() is returned if the node is not found.
  // If a matching item is not present, the scan is terminated as soon as
  // possible by detecting when the scan goes past where the matching item would
  // be.
  Iterator find(const T& probe_datum) noexcept;
  // The const version of find returns a const_Iterator
  const_Iterator find(const T& probe_datum) const noexcept;

  // Delete the specified node, specified by a const_Iterator because it only
  // designates the location of the to-be-removed data. This function can be
  // called with an Iterator which will be simply converted to a const_Iterator
  // by the conversion function above. Caller is responsible for any required
  // deletion of any pointed-to data beforehand. Do not attempt to dereference
  // the iterator after calling this function - it is invalid after this
  // function executes. The results are undefined if the
  // Iterator does not point to an actual node, or the list is empty.
  void erase(const_Iterator it) noexcept;

  // Interchange the member variable values of this list with the other list;
  // Only the pointers and size are interchanged;
  // no allocation or deallocation of list Nodes is done.
  // Thus the no-throw guarantee can be provided.
  // This function can only be called with another list of the same type as
  // this list, which means that the ordering function objects must be
  // identical, and so do not need to be swapped.
  void swap(Ordered_list& other) noexcept;

 private:
  // member variable declaration for the ordering function object.
  OF ordering_fo;  // declares an object of OF type
  /* *** other private member variables and functions are your choice. */
  Node<T>* m_head;
  std::size_t m_length;
  Node<T>* m_tail; /*keep track of last node so that every time in push back we
                      do not have to lopp entire list*/
  // member variables
  const_Iterator push_back(const Node<T>& new_node);
  const_Iterator push_back(const_Iterator node_itr);
  const_Iterator push_back(const T& datum);
};

// These function templates are given two iterators, usually .begin() and
// .end(), and apply a function to each item (dereferenced iterator) in the
// list. The templates work for both Iterators and const_Iterators. Note that
// the function must be an ordinary function; these templates will not
// instantiate if the function is a member function of some class. However, you
// can often use a simple ordinary function with parameters that calls the
// member function using the parameter values.

template <typename IT, typename F>
void apply(IT first, IT last, F function) {
  for (; first != last; ++first) function(*first);
}

// the fourth parameter is used as the second argument of the function
template <typename IT, typename F, typename A>
void apply_arg(IT first, IT last, F function, A arg) {
  for (; first != last; ++first) {
    function(*first, arg);
  }
}

// this function templates accept the second argument by reference - useful for
// streams.
template <typename IT, typename F, typename A>
void apply_arg_ref(IT first, IT last, F function, A& arg) {
  for (; first != last; ++first) {
    function(*first, arg);
  }
}

// the function must return true/false; apply the function until true is
// returned, then return true; otherwise return false.
template <typename IT, typename F>
bool apply_if(IT first, IT last, F function) {
  for (; first != last; ++first)
    if (function(*first)) return true;
  return false;
}

// this function works like apply_if, with a fourth parameter used as the second
// argument for the function
template <typename IT, typename F, typename A>
bool apply_if_arg(IT first, IT last, F function, A arg) {
  for (; first != last; ++first) {
    if (function(*first, arg)) {
      return true;
    }
  }
  return false;
}

template <typename T, typename OF>
void Ordered_list<T, OF>::erase(const_Iterator it) noexcept {
  Node<T>* copy_head = m_head;
  while (copy_head != nullptr) {
    // find a match
    if (copy_head->datum == *it) {
      // if the found node is begining node
      if (copy_head->prev == nullptr) {
        copy_head->next->prev = nullptr;
        m_head = copy_head->next;
      } else if (copy_head->next == nullptr) {  // match was end
        copy_head->prev->next = nullptr;
      } else {  // its not the begining
        copy_head->next->prev = copy_head->prev;
        copy_head->prev->next = copy_head->next;
      }
      // erase the copy_head and decrease length
      --m_length;
      delete copy_head;
      copy_head = nullptr;
      return;
    } else {
      copy_head = copy_head->next;
    }
  }
  if (copy_head == nullptr) {
    return;
  }
}

template <typename T, typename OF>
Ordered_list<T, OF>::Ordered_list()
    : m_head{nullptr}, m_length{0}, m_tail{nullptr} {}

template <typename T, typename OF>
bool Ordered_list<T, OF>::insert(const T& new_datum) {
  if (m_head == nullptr && m_length == 0) {  // inserting into an empty node
    m_head = new Node<T>{new_datum, nullptr, nullptr};
    m_length = 1;
    m_tail = m_head;
    return true;
  } else {
    // serach the place where the new node shuld be placed
    Node<T>* next_node = m_head;
    T list_elem = next_node->datum;
    while (ordering_fo(list_elem, new_datum)) {
      if (next_node->next == nullptr) {
        // insert at end
        Node<T>* new_node = new Node<T>{new_datum, nullptr, nullptr};
        next_node->next = new_node;
        new_node->prev = next_node;
        m_tail = new_node;
        m_length++;
        return true;
      } else {
        // increment next_node
        next_node = next_node->next;
        list_elem = next_node->datum;
      }
    }
    //   Node<T>* new_node = new Node<T>{new_datum, nullptr, nullptr};
    Node<T>* new_node = new Node<T>{new_datum, nullptr, nullptr};
    new_node->next = next_node;
    new_node->prev = next_node->prev;
    next_node->prev = new_node;
    if (new_node->prev != nullptr) {
      new_node->prev->next = new_node;
    }
    // change the head
    if (new_node->prev == nullptr) {
      m_head = new_node;
    }

    m_length++;
    return true;
  }
}

template <typename T, typename OF>
void Ordered_list<T, OF>::clear() noexcept {
  while (m_head != nullptr && m_length > 0) {
    Node<T>* next = m_head->next;
    delete m_head;
    m_head = next;
    --m_length;
  }
}

template <typename T, typename OF>
typename Ordered_list<T, OF>::Iterator Ordered_list<T, OF>::find(
    const T& prob_object) noexcept {
  Iterator first = this->begin();
  Iterator last = this->end();
  for (; first != last; ++first) {
    if (*first == prob_object) {
      return first;
    } else {
      /* check if the prob object is less than the current one
       there is no meaning for searchign further beacuse list
       is a ordered container*/
      if (prob_object < *first) {
        return last;
      }
    }
  }

  return last;
}

  // The const version of find returns a const_Iterator
template <typename T, typename OF>
typename Ordered_list<T, OF>::const_Iterator Ordered_list<T, OF>::find(
    const T& prob_object) const noexcept {

    }

/*Copy construct this list from another list by copying its data.
The basic exception guarantee:
If an exception is thrown when the type T contents of a node are copied,
any nodes already constructed are destroyed, so that no memory is leaked,
and the exception is then propagated from this constructor.*/
template <typename T, typename OF>
Ordered_list<T, OF>::Ordered_list(const Ordered_list& original) {
  ordering_fo = original.ordering_fo;
  m_length = original.m_length;
  m_length = 0;

  // Create an empty list (local variable so, if an exception happen compiler
  // cutomatically call list desctructor to erase the half the allocated node)
  // copy the source list into this temporarly local list
  // now swap this temporary list into *this object
  //  here we need to confirm that swap is noexception

  // create an empty object list
  Ordered_list<T, OF> temp_list;
  
  // loop through the element of original source list
  for (const_Iterator itr = original.cbegin(); itr != original.cend(); ++itr) {
    temp_list.push_back(*itr);
  }

  // swap this with the temp_list
  temp_list.swap(*this);

  // This is not exception gurantee  so dicsurd this
  //  deep copy
  //  get a copy of the head of original to iterate over nodes
  /*  Node<T>* original_head_copy = original.m_head;
   Node<T>* prev_ptr = nullptr;  // to iterate current list
   while (original_head_copy != nullptr) {
     // allocate space for node, it might throw an
     // if it does then we need to clear the half baked list
     // and also propagate the exception out of this constructor
     Node<T>* new_node_ptr =
         new Node<T>{original_head_copy->datum, nullptr, nullptr};
     if (m_length == 0) {  // first time : need to assign m_head
       m_head = new_node_ptr;
       m_length++;
       prev_ptr = new_node_ptr;
       new_node_ptr = nullptr;
     } else {  // link to next and prevs
       prev_ptr->next = new_node_ptr;
       new_node_ptr->prev = prev_ptr;
       prev_ptr = new_node_ptr;
       m_length++;
     }
     original_head_copy = original_head_copy->next;
   }
   original_head_copy = nullptr;
   prev_ptr = nullptr; */
}

template <typename T, typename OF>
bool Ordered_list<T, OF>::insert(T&& datum) {
  T copy_datum = datum;
  return this->insert(copy_datum);
}

template <typename T, typename OF>
void Ordered_list<T, OF>::swap(Ordered_list& other) noexcept {
  // no need to allocate deallocate (to make it no exception) only size and
  // pointer exchange taking copy of everthing before replace
  Node<T>* copy_current_head = m_head;
  std::size_t copy_current_length = m_length;
  OF copy_function_ptr = ordering_fo;
  // replacing
  m_head = other.m_head;
  m_length = other.m_length;
  ordering_fo = other.ordering_fo;
  // swaping
  other.m_head = copy_current_head;
  other.m_length = copy_current_length;
  other.ordering_fo = copy_function_ptr;
}

template <typename T, typename OF>
typename Ordered_list<T, OF>::const_Iterator Ordered_list<T, OF>::push_back(
    const Node<T>& new_node) {
  Node<T>* new_node_ptr = new Node<T>{new_node.datum, nullptr, nullptr};
  if (m_length == 0) {  // first time : need to assign m_head
    m_head = new_node_ptr;
    m_length++;
    m_tail = m_head;
    new_node_ptr = nullptr;
  } else {  // link to next and prevs
    m_tail->next = new_node_ptr;
    new_node_ptr->prev = m_tail;
    m_tail = new_node_ptr;
    m_length++;
  }
  return const_Iterator(m_tail);
}

template <typename T, typename OF>
typename Ordered_list<T, OF>::const_Iterator Ordered_list<T, OF>::push_back(
    const_Iterator node_itr) {
  Node<T> temp_node = *node_itr;
  return this->push_back(temp_node);
}

template <typename T, typename OF>
typename Ordered_list<T, OF>::const_Iterator Ordered_list<T, OF>::push_back(
    const T& datum) {
  Node<T> temp_node{datum, nullptr, nullptr};
  this->push_back(temp_node);
}


template<typename T, typename OF> 
std::ostream& operator<< (std::ostream& os, Ordered_list<T,OF> list){

  auto itr = list.begin();
  for (; itr != list.end(); ++itr)
  {
    os << *(itr);
  }
  

}

#endif