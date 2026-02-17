
///////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   : SinglyLLL
//  Input           : Nothing
//  Output          : Nothing
//  Description     : Used to Construct the class SinglyLLL
//  Author          : Aditya Vijay Mali
//  Date            : 06/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

template <class T>
SinglyLLL<T> :: SinglyLLL()
{
    cout<<"Object of Singlyll gets created. \n";
    this -> first = NULL;
    this -> iCount = 0;
}   // end of SinglyLLL

///////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   : InsertFirst
//  Input           : Data of Node
//  Output          : Nothing
//  Description     : Used to insert node at first position
//  Author          : Aditya Vijay Mali
//  Date            : 06/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

template <class T>
void SinglyLLL<T> :: InsertFirst(T no)
{
    SinglyLLLnode<T> * newn = NULL;

    newn = new SinglyLLLnode<T>(no);

    newn -> next = this -> first;
    this -> first = newn;

    this -> iCount++;
}   // End of InsertFirst

///////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   : InsertLast
//  Input           : Data of Node
//  Output          : Nothing
//  Description     : Used to insert node at last position
//  Author          : Aditya Vijay Mali
//  Date            : 06/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

template <class T>
void SinglyLLL<T> :: InsertLast(T no)
{
    SinglyLLLnode<T> * newn = NULL;
    SinglyLLLnode<T> * temp = NULL;

    newn = new SinglyLLLnode<T>(no);
    
    if (this -> iCount == 0)            // Updated
    {
        this -> first = newn;
    }
    else
    {
        temp = this -> first;

        while (temp -> next != NULL)
        {
            temp = temp -> next;
        }

        temp -> next = newn;
    }

    this -> iCount++;
}   //End of InsertLast

///////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   : DeleteFirst
//  Input           : Nothing
//  Output          : Nothing
//  Description     : Used to Delete node at first position
//  Author          : Aditya Vijay Mali
//  Date            : 06/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

template <class T>
void SinglyLLL<T> :: DeleteFirst()
{
    SinglyLLLnode<T> * temp = NULL;
    if (this -> first == NULL)
    {
        return;
    }
    else if(this -> first -> next == NULL)      // else if(this -> iCount == 1)
    {
        delete this -> first;
        this -> first = NULL;
    }
    else
    {
        temp = this -> first;
        this -> first = this -> first -> next;
        delete temp;
    }

    this -> iCount--;
}   // End of DeleteFirst

///////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   : DeleteLast
//  Input           : Nothing
//  Output          : Nothing
//  Description     : Used to Delete node at last position
//  Author          : Aditya Vijay Mali
//  Date            : 06/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

template <class T>
void SinglyLLL<T> :: DeleteLast()
{
    SinglyLLLnode<T> * temp = NULL;

    if (this -> first == NULL)
    {
        return;
    }
    else if(this -> first -> next == NULL)      // else if(this -> iCount == 1)
    {
        delete this -> first;
        this -> first = NULL;
    }
    else
    {
        temp = this -> first;

        while (temp -> next -> next != NULL)
        {
            temp = temp -> next;
        }

        delete temp -> next;
        temp -> next = NULL;                
    }

    this -> iCount--;
}   // End of DeleteLast

///////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   : InsertAtPos
//  Input           : Data of Node
//  Output          : Nothing
//  Description     : Used to insert node at Given position
//  Author          : Aditya Vijay Mali
//  Date            : 06/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

template <class T>
void SinglyLLL<T> :: InsertAtPos(T no,int pos)
{
    SinglyLLLnode<T> * newn = NULL;
    SinglyLLLnode<T> * temp = NULL;

    int iCnt = 0;

    if (pos < 1 || pos > this -> iCount + 1)
    {
        cout<<"Invalid position \n";
        return;
    }

    if (pos == 1)
    {
        this -> InsertFirst(no);
    }
    else if(pos == this -> iCount +1)
    {
        this -> InsertLast(no);
    }
    else
    {
        newn = new SinglyLLLnode<T>(no);

        temp = this -> first;

        for(iCnt = 1; iCnt < pos -1; iCnt++)
        {
            temp = temp -> next;
        }

        newn-> next = temp -> next;
        temp -> next = newn;

        this -> iCount++;
    }            
}   // End of InsertAtPos

///////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   : DeleteAtPos
//  Input           : Position
//  Output          : Nothing
//  Description     : Used to Delete node of given position
//  Author          : Aditya Vijay Mali
//  Date            : 06/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

template <class T>
void SinglyLLL<T> :: DeleteAtPos(int pos)
{
    SinglyLLLnode<T> * temp = NULL;
    SinglyLLLnode<T> * target = NULL;
    int iCnt = 0;

    if (pos < 1 || pos > this -> iCount + 1)
    {
        cout<<"Invalid position \n";
        return;
    }

    if (pos == 1)
    {
        this -> DeleteFirst();
    }
    else if(pos == this -> iCount)
    {
        this -> DeleteLast();
    }
    else
    {
        temp = this -> first;

        for (iCnt = 1; iCnt < pos - 1; iCnt++)
        {
            temp = temp -> next;
        }
        
        target = temp -> next;
        temp -> next = target -> next;
        delete target;

        this -> iCount--;
    }
}   // End of DeleteAtPos

///////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   : Display
//  Input           : Nothing
//  Output          : Nothing
//  Description     : Used to Display linked list
//  Author          : Aditya Vijay Mali
//  Date            : 06/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

template <class T>
void SinglyLLL<T> :: Display()
{
    SinglyLLLnode<T> * temp = NULL;
    if (this -> first == NULL)
    {
        cout<<"\nLinked List is Empty\n";
    }
    else
    {
        temp = this -> first;

        while(temp != NULL)
        {
            cout<<"| "<<temp->data<<" | -> ";
            temp = temp -> next;
        }

        cout <<"NULL \n";
    }
}   // End of Display

///////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   : Count
//  Input           : Nothing
//  Output          : Integer
//  Description     : Used to Count the nodes of the linked list 
//  Author          : Aditya Vijay Mali
//  Date            : 06/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

template <class T>
int SinglyLLL<T> :: Count()
{
    return this -> iCount;
}   // End of Count

///////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   : DeleteAll
//  Input           : Position
//  Output          : Nothing
//  Description     : Used to Delete All nodes of linked list 
//  Author          : Aditya Vijay Mali
//  Date            : 06/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

template <class T>
void SinglyLLL<T> :: DeleteAll()
{
    SinglyLLLnode<T> * temp = NULL;

    while(this -> first != NULL)
    {
        temp = this -> first;
        first = temp -> next;
        delete temp;
        this -> iCount--;
    }
    this -> Display();
}

///////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   : PhysicalReverse
//  Input           : Nothing
//  Output          : Nothing
//  Description     : Used to Reverse linked list physically. 
//  Author          : Aditya Vijay Mali
//  Date            : 06/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

template <class T>
void SinglyLLL<T> :: PhysicalReverse()
{
    SinglyLLLnode<T> *pNext = NULL;
	SinglyLLLnode<T> *pCurrent = this -> first;
	SinglyLLLnode<T> *pPrev = NULL;

	while(pCurrent != NULL)
	{
		pNext = pCurrent -> next;
		pCurrent -> next = pPrev;
		pPrev = pCurrent;
		pCurrent = pNext;
	}

	this -> first = pPrev;
}

///////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   : ReverseDisplay
//  Input           : Nothing
//  Output          : Nothing
//  Description     : Used to display the linked list in Reverse order 
//  Author          : Aditya Vijay Mali
//  Date            : 06/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

template <class T>
void SinglyLLL<T> :: ReverseDisplay()
{
	if (NULL == this -> first)
	{
		printf("List is Empty\n");
		return;
	}

	PhysicalReverse();
	Display();
	PhysicalReverse();
}   // End of ReverseDisplay

///////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   : SearchFirstOccurrence
//  Input           : Data to find in linked list
//  Output          : First position of data present in a linked list 
//  Description     : Used to find the First occurrence of a data in linked list 
//  Author          : Aditya Vijay Mali
//  Date            : 06/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

template <class T>
int SinglyLLL<T> :: SearchFirstOccurrence(int iKey)
{
	int iCnt = 0;
    int iPos = 0;
    SinglyLLLnode<T> *pTemp = this -> first;

	while(pTemp != NULL)
	{
		iCnt++;
		if(pTemp -> data == iKey)
			iPos = iCnt;
		pTemp = pTemp -> next;
	}

	return iPos;
}   // End of SearchFirstOccurrence

///////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   : SearchLastOccurrence
//  Input           : Data to find in linked list
//  Output          : Last position of data present in a linked list 
//  Description     : Used to find the last occurrence of a data in linked list 
//  Author          : Aditya Vijay Mali
//  Date            : 06/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

template <class T>
int SinglyLLL<T> :: SearchLastOccurrence(int iKey)
{
	int iPos = 0;
	int iLastPos = 0;
    SinglyLLLnode<T> *pTemp = this -> first;

	while(pTemp != NULL)
	{
		iPos++;
		if(iKey == pTemp -> data)
			iLastPos = iPos;
		pTemp = pTemp -> next;
	}

	return iLastPos;
}   // End of SearchLastOccurrence

///////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   : SearchLastOccurrence
//  Input           : Data to find in linked list
//  Output          : count of data present in a linked list 
//  Description     : Used to count the occurrence of a data present in a linked list 
//  Author          : Aditya Vijay Mali
//  Date            : 06/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

template <class T>
int SinglyLLL<T> :: SearchAllOccurrence(int iKey)
{
	int iPos = 0;
	int iCount = 0;
    SinglyLLLnode<T> *pTemp = this -> first;


	while(pTemp != NULL)
	{
		iPos++;
		if(iKey == pTemp -> data)
			iCount++;
		pTemp = pTemp -> next;
	}

	return iCount;
}   // End of SearchAllOccurrence

