//
//  lists.hpp
//  oop-lab1
//
//  Created by Золотарева Марина Олеговна on 26.09.2020.
//

#ifndef lists_hpp
#define lists_hpp

#include <stdio.h>
template <class T>
class Node
{
private:
    T value;
    Node* pNext;
    Node* pPrev;
public:
    Node(T nodeValue):value(nodeValue)
    {
        pNext = nullptr;
        pPrev = nullptr;
    }
    ~Node()
    {
        delete pNext;
    }
};

template <class T>
class LinkedList
{
private:
    Node<T>* head;
    int numberOfElements;
public:
    LinkedList()
    {
        head = nullptr;
        numberOfElements = 0;
    }
    void pushBack(T value)
    {
        Node<T>* newNode = new Node<T>(value);
        if(head == nullptr)
        {
            head = newNode;
        }
        else
        {
            Node<T>* currentNode = head;
            while(currentNode->pNext!=nullptr)
            {
                currentNode = currentNode->pNext;
            }
            currentNode->pNext = newNode;
            newNode->pPrev = currentNode;
        }
        numberOfElements++;
    }
};
template <class T>
class Stack: public LinkedList<T>
{
private:
    Node<T>* head;
    int numberOfElements;
public:
    void pop()
    {
        if(head == nullptr) return;
        Node<T>* currentNode = head;
        while(currentNode->pNext!=nullptr)
        {
            currentNode = currentNode->pNext;
        }
        currentNode->pPrev->pNext = nullptr;
        delete currentNode;
        numberOfElements--;
    }
    T peek()
    {
        if(head == nullptr) return;
        Node<T>* currentNode = head;
        while(currentNode->pNext!=nullptr)
        {
            currentNode = currentNode->pNext;
        }
        return currentNode->value;
    }
};
template <class T>
class Queue: public LinkedList<T>
{
private:
    Node<T>* head;
    int numberOfElements;
public:
    void pop()
    {
        if(head == nullptr) return;
        head = head->pNext;
        delete head->pPrev;
        head->pPrev = nullptr;
        numberOfElements--;
    }
    T peek()
    {
        return head->value;
    }
};
template <class T>
class deque: public LinkedList<T>
{
private:
    Node<T>* head;
    int numberOfElements;
public:
    void popBack()
    {
        if(head == nullptr) return;
        Node<T>* currentNode = head;
        while(currentNode->pNext!=nullptr)
        {
            currentNode = currentNode->pNext;
        }
        currentNode->pPrev->pNext = nullptr;
        delete currentNode;
        numberOfElements--;
    }
    void popFront()
    {
        if(head == nullptr) return;
        head = head->pNext;
        delete head->pPrev;
        head->pPrev = nullptr;
        numberOfElements--;
    }
    void pushFront(T value)
    {
        Node<T>* newNode = new Node<T>(value);
        if(head == nullptr)
        {
            head = newNode;
        }
        else
        {
            newNode->pNext = head;
            head->pPrev = newNode;
            head = newNode;
        }
    }
};


#endif /* lists_hpp */
