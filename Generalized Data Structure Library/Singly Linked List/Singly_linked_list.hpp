#include<iostream>
#include <string.h>
using namespace std;

///////////////////////////////////////////////////////////////////////////////////
//
//      Singly Linear linked List using Genric Approch
//
///////////////////////////////////////////////////////////////////////////////////


#pragma pack(1)
template <class T>
class SinglyLLLnode
{
    public:
        T data;
        SinglyLLLnode<T> * next;

        SinglyLLLnode(T no)
        {
            this -> data = no;
            this -> next = NULL;
        }
};  // End of Class SinglyLLLnode

template <class T>
class SinglyLLL
{
    private:
        SinglyLLLnode<T> * first;
        int iCount;

    public: 
        SinglyLLL();
        void InsertFirst(T);
        void InsertLast(T);
        void DeleteFirst();
        void DeleteLast(); 
        void Display();
        int Count();
        void InsertAtPos(T,int);
        void DeleteAtPos(int);
        void DeleteAll();
        void PhysicalReverse();
        void ReverseDisplay();
        int SearchFirstOccurrence(T);
        int SearchLastOccurrence(T);
        int SearchAllOccurrence(T);
};  // End of Class Diclaration

#include "singly_linked_list.cpp"

