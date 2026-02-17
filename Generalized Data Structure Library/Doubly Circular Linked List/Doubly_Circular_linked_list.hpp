#include <iostream>
#include <string.h>
using namespace std;


///////////////////////////////////////////////////////////////////////////////////
//  Doubly Circular linked List using Genric Approch
///////////////////////////////////////////////////////////////////////////////////

template <class T>
class DoublyCLLnode
{
    public:
        T data;
        DoublyCLLnode<T> *next;
        DoublyCLLnode<T> *prev;

        DoublyCLLnode(T no)
        {
            this -> data = no;
            this -> next = NULL;
            this -> prev = NULL;
        }
};  // End of Class DoublyCLLnode

template<class T>
class DoublyCLL
{
    private:
        DoublyCLLnode <T> * first;
        DoublyCLLnode <T> * last;
        int iCount;

    public:
        DoublyCLL();
        void InsertFirst(T no);
        void InsertLast(T no);
        void InsertAtPos(T no, int pos);
        void DeleteFirst();
        void DeleteLast();
        void DeleteAtPos(int pos);
        void DeleteAll();
        void Display();
        int Count();
        void PhysicalReverse();
        void ReverseDisplay();
        int SearchFirstOccurrence(T);
        int SearchLastOccurrence(T);
        int SearchAllOccurrence(T);

};  // End of Class Diclatration DoublyCLL

#include "Doubly_Circular_linked_list.cpp"