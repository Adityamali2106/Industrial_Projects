#include<iostream>
#include<string.h>
using namespace std;

///////////////////////////////////////////////////////////////////////////////////
//      Singly Circular linked List using Genric Approch
///////////////////////////////////////////////////////////////////////////////////

template <class T>
class SinglyCLLnode
{
    public:
        T data;
        SinglyCLLnode<T> *next;

        SinglyCLLnode(T no)
        {
            this -> data = no;
            this -> next = NULL;
        }
};  // End of Class SinglyCLLnode

template <class T>
class SinglyCLL
{
    private:
        SinglyCLLnode<T> * first;
        SinglyCLLnode<T> * last;
        int iCount;

    public:
        SinglyCLL();
        void InsertFirst(T no);
        void InsertLast(T no);
        void DeleteFirst();
        void DeleteLast();
        void Display();
        int Count();
        void DeleteAtPos(int pos);
        void InsertAtPos(T no, int pos);
        void DeleteAll();
        void PhysicalReverse();
        void ReverseDisplay();
        int SearchFirstOccurrence(T);
        int SearchLastOccurrence(T);
        int SearchAllOccurrence(T);

};  // End of Class Diclaration SinglyCLL

#include "Singly_Circular_Linked_List.cpp"
