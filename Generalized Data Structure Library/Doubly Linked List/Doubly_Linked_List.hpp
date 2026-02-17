///////////////////////////////////////////////////////////////////////////////////
//      Doubly Linear linked List using Genric Approch
///////////////////////////////////////////////////////////////////////////////////

#include<iostream>
#include<string.h>
using namespace std;

#pragma pack(1)
template <class  T>
class DoublyLLLnode
{
    public :
        T data;
        DoublyLLLnode * next;
        DoublyLLLnode * prev;

        DoublyLLLnode(T no)
        {
            this -> data = no;
            this -> next = NULL;
            this -> prev = NULL;
        }
};  // End of Class DoublyLLLnode

template <class  T>
class DoublyLLL
{
    private:
        DoublyLLLnode<T> * first;
        int iCount;
        
    public :
        DoublyLLL();

        void InsertFirst(T);
        void InsertLast(T);
        void InsertAtPos(T,int);

        void DeleteFirst();
        void DeleteLast();
        void DeleteAtPos(int);
        void DeleteAll();

        void Display();
        int Count();
        int SearchFirstOccurrence(T);
        int SearchLastOccurrence(T);
        int SearchAllOccurrence(T);

        void PhysicalReverse();
        void ReverseDisplay();

};  // End of Class DoublyLLL Diclaration

#include"Doubly_Linked_List.cpp"