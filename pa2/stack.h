/**
 * @file stack.h
 * Definition of the Stack class.
 *
 * You **should not** modify this file for the PA!
 *
 */
#ifndef _STACK_H_
#define _STACK_H_

#define DEFAULTCAPACITY 4 // Initial capacity of the array.
#define EXPANSIONFACTOR 2 // Factor to multiply or divide current size by when resizing.
#define SHRINKRATE 4      // When the size of the array is less than equal 1 over this value the array should resize

#include "ordering_structure.h"

template <class T> class Stack : public OrderingStructure<T>
{
  public:
    Stack();

    ~Stack();

    /**
     * Adds the parameter object to the top of the Stack.
     *
     * @param newItem The object to be added to the Stack.
     */
    void push(const T &newItem);

    /**
     * Removes the object on top of the Stack, and returns it.
     *
     * @return The element that used to be at the top of the Stack.
     */
    T pop();

    /**
     * Adds an element to the ordering structure.
     *
     * @see OrderingStructure::add()
     */
    void add(const T &theItem);

    /**
     * Removes an element from the ordering structure.
     *
     * @see OrderingStructure::remove()
     */
    T remove();

    /**
     * Finds the object on top of the Stack, and returns it to the caller.
     * Unlike pop(), this operation does not alter the Stack itself.
     *
     * @return The element at the top of the Stack.
     */
    T peek();

    /**
     * Determines if the Stack is empty.
     *
     * @return Whether or not the stack is empty (bool).
     */
    bool isEmpty() const;

    /**
     * Return the maximum number of items the stack can hold.
     *
     * Note: This is an implementation detail we would normally hide.
     * We include it here for testing purposes.
     */
    size_t capacity() const;

    /**
     * Return the number of items on the stack.
     */
    size_t size() const;

  private:
    /**
     * The maximum number of items the stack can store without a resize
     */
    size_t max_items;

    /**
     * The number of items currently in the stack
     */
    size_t num_items;

    /**
     * The dynamic array representing our Stack
     */
    T *items;

    /**
     * Resize the the member variable `items`.
     * Don't forget to free up any memory that is no longer used.
     *
     * @param n The size of the stack after resizing
     */
    void resize(size_t n);
};

#include "stack.cpp" // needed for template instantiation

#endif
