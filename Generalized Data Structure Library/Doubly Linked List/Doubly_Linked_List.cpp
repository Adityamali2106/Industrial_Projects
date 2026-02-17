///////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   : DoublyLLL
//  Input           : Nothing
//  Output          : Nothing
//  Description     : Used to Construct the object
//  Author          : Aditya Vijay Mali
//  Date            : 06/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

template <class  T>
DoublyLLL<T> :: DoublyLLL()
{
    cout<<"Linked List gets created \n";
    this -> first = NULL;
    this -> iCount = 0;
}      // End of DoublyLLL

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

template <class  T>
void DoublyLLL<T> :: InsertFirst(T no)
{
    DoublyLLLnode<T> *newn = NULL;

    newn = new DoublyLLLnode<T>(no);

    if (this-> first == NULL)
    {
        this ->first = newn;
    }
    else
    {
        newn -> next = this -> first;
        this -> first -> prev = newn;
        this -> first = newn; 
    }

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

template <class  T>
void DoublyLLL<T> :: InsertLast(T no)
{
    DoublyLLLnode<T> *newn = NULL;
    DoublyLLLnode<T> *temp = NULL;

    newn = new DoublyLLLnode<T>(no);

    if (first == NULL)
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
        newn -> prev = temp;
    }

    this -> iCount++;
}   // End of InsertLast

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

template <class  T>
void DoublyLLL<T> :: InsertAtPos(T no, int pos)
{
    DoublyLLLnode<T> *newn = NULL;
    DoublyLLLnode<T> *temp = NULL;
    int iCnt = 0;

    if (pos < 1 || pos > iCount +1 )
    {
        cout<< "Invalid Position\n";
        return;
    }
    
    if (pos == 1)
    {
        this -> InsertFirst(no);
    }
    else if (pos == iCount + 1)
    {
        this -> InsertLast(no);
    }
    else
    {
        newn = new DoublyLLLnode<T>(no);
        temp = this -> first;

        for (iCnt = 1; iCnt < pos -1; iCnt++)
        {
            temp = temp -> next;
        }

        newn -> next = temp -> next;
        temp -> next -> prev = newn;
        temp -> next = newn;
        newn -> prev = temp;

        this -> iCount++;
    }
}   // End of InsertAtPos

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

template <class  T>
void DoublyLLL<T> :: DeleteFirst()
{
    if (this -> first == NULL)
    {
        return;
    }
    else if (this -> first -> next == NULL)
    {
        delete this -> first;
        this -> first = NULL;
    }
    else
    {
        this -> first = this -> first -> next;
        delete first -> prev;
        this -> first -> prev = NULL;
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

template <class  T>
void DoublyLLL<T> :: DeleteLast()
{
    DoublyLLLnode<T> * temp = NULL;
    if (this -> first == NULL)
    {
        return;
    }
    else if (this -> first -> next == NULL)
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
}   // End of Delete Last

///////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   : DeleteAtPos
//  Input           : Position
//  Output          : Nothing
//  Description     : Used to Delete the node of Given position
//  Author          : Aditya Vijay Mali
//  Date            : 06/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

template <class  T>
void DoublyLLL<T> :: DeleteAtPos(int pos)
{
    DoublyLLLnode<T> *temp = NULL;
    int iCnt = 0;

    if (pos < 1 || pos > this ->iCount)
    {
        cout<< "Invalid Position\n";
        return;
    }
    
    if (pos == 1)
    {
        this -> DeleteFirst();
    }
    else if (pos == iCount)
    {
        this -> DeleteLast();
    }
    else
    {
        temp = this -> first;

        for (iCnt = 1; iCnt < pos -1; iCnt++)
        {
            temp = temp -> next;
        }

        temp -> next = temp -> next -> next;
        delete temp -> next -> prev;
        temp -> next -> prev = temp;

        this -> iCount--;        
    }
}   // End of DeleteAtPos

///////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   : Display
//  Input           : Nothing
//  Output          : Nothing
//  Description     : Used to Display All nodes present in linked list
//  Author          : Aditya Vijay Mali
//  Date            : 06/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

template <class  T>
void DoublyLLL<T> :: Display()
{
    DoublyLLLnode<T> * temp = NULL;

    if (this -> first == NULL)
    {
        cout <<"Linked list is Empty";
        return;
    }

    cout<<"\nNULL <=> ";
    temp = this -> first;

    while (temp != NULL)
    {
        cout<<"| "<<temp -> data<<" | <=>";
        temp = temp -> next;
    }
    cout<<"NULL \n";  
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

template <class  T>
int DoublyLLL<T> :: Count()
{
    return this -> iCount;
}   // End of Count

///////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   : DeleteAll
//  Input           : Nothing
//  Output          : Nothing
//  Description     : Used to Delete All nodes of linked list 
//  Author          : Aditya Vijay Mali
//  Date            : 06/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

template <class T>
void DoublyLLL<T> :: DeleteAll()
{
    DoublyLLLnode<T> *temp =NULL;

    while(this -> first != NULL)
    {
        temp = this -> first;
        first = temp -> next;
        delete temp;
        this -> iCount--;
    }
    this -> Display();
}   // End of DeleteAll

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
int DoublyLLL<T> :: SearchFirstOccurrence(T iKey)
{
	int iCnt = 0;
    int iPos = 0;
    DoublyLLLnode<T> *pTemp = this -> first;

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
int DoublyLLL<T> :: SearchLastOccurrence(T iKey)
{
	int iPos = 0;
	int iLastPos = 0;
    DoublyLLLnode<T> *pTemp = this -> first;

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
int DoublyLLL<T> :: SearchAllOccurrence(T iKey)
{
	int iCount = 0;
    DoublyLLLnode<T> *pTemp = this -> first;


	while(pTemp != NULL)
	{
		if(iKey == pTemp -> data)
        {
			iCount++;
        }
		pTemp = pTemp -> next;
	}

	return iCount;
}   // End of SearchAllOccurrence

template <class T>
void DoublyLLL<T> :: PhysicalReverse()
{
	DoublyLLLnode<T> *pNext = NULL;
	DoublyLLLnode<T> * pCurrent = this -> first;

	while(pCurrent -> next != NULL)
	{
		pNext = pCurrent -> next;
		pCurrent -> next = pCurrent -> prev;
		pCurrent -> prev = pNext;
		pCurrent = pNext;
	}

	pCurrent -> next = pCurrent -> prev;
	pCurrent -> prev = NULL;

	this -> first = pCurrent;
}

template <class T>
void DoublyLLL<T> :: ReverseDisplay()
{
	if (NULL == this -> first)
	{
		cout<<"List is Empty\n";
		return;
	}

	PhysicalReverse();
	Display();
	PhysicalReverse();
}
