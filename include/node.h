//Реалиация списка

#ifndef NODE

#define NODE

#include<iostream>
#include<vector>
#include<string>

template <class T>
struct Node
{
    T data;
    Node* prev;
    Node* next;

    Node()
    {
        prev = next = nullptr;
    }
};

template <class T>
class List {
    Node<T>* Head;
    Node<T>* Tail;
public:
    List()
    {
        Head = Tail = nullptr;
    }

    void SetHead(Node<T>* t)
    {
        Head = t;
    }
    void SetTail(Node<T>* t)
    {
        Tail = t;
    }
    
    Node<T>* head() 
    {
        return Head;
    }
    Node<T>* tail()
    {
        return Tail;
    }

    void clear()
    {
        //Удаляем элементы
        while (Head!=nullptr && Head->next != nullptr)
        {
            Head = Head->next;
            delete Head->prev;
        }
        if(Head != nullptr)
            delete Head;
        //--------------------
        Head = Tail = nullptr;
    }

    void push_back(T& value)
    {
        Node<T>* tmp = new Node<T>;
        tmp->data = value;
        if (Head == nullptr)
        {
            Head = Tail = tmp;
            return;
        }
        Tail->next = tmp;
        tmp->prev = Tail;
        Tail = tmp;
    }

    void sort()
    {
        if (Head == nullptr)
            return;
        Node <T>* elem1 = Head;
        while (elem1->next != nullptr)
        {
            Node<T>* elem2 = elem1->next;
            while (elem2 != nullptr)
            {
                if (elem1->data < elem2->data)
                {
                    T tmp = elem1->data;
                    elem1->data = elem2->data;
                    elem2->data = tmp;
                }
                elem2 = elem2->next;
            }
            elem1 = elem1->next;
        }
    }

};
#endif