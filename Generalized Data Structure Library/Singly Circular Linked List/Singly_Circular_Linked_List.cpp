///////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   : SinglyCLL
//  Input           : Nothing
//  Output          : Nothing
//  Description     : Used to Construct the object
//  Author          : Aditya Vijay Mali
//  Date            : 06/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

template <class T>
SinglyCLL<T>::SinglyCLL()
{
    cout<<"Inside constructor of SinglyCLL\n";

    this->first = NULL;
    this->last = NULL;
    this->iCount = 0;
}   // End of SinglyCLL

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
void SinglyCLL<T>::InsertFirst(T no)
{
    SinglyCLLnode<T> * newn = NULL;

    newn = new SinglyCLLnode<T>(no);

    if((this -> first == NULL) && (this -> last == NULL))   // if(iCount == 0)
    {
        this -> first = newn;
        this -> last = newn;

        this -> last -> next = this -> first;
    }
    else
    {
        newn -> next = this -> first;
        this -> first = newn;

        this -> last -> next = this -> first;
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

template <class T>
void SinglyCLL<T>::InsertLast(T no)
{
    SinglyCLLnode<T> * newn = NULL;

    newn = new SinglyCLLnode<T>(no);

    if((this -> first == NULL) && (this -> last == NULL))
    {
        this -> first = newn;
        this -> last = newn;

        this -> last -> next = this -> first;
    }
    else
    {
        this -> last -> next = newn;
        this -> last = newn;

        this -> last -> next = this -> first;
    }

    this -> iCount++;
}   // End of InsertLast

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
void SinglyCLL<T>::DeleteFirst()
{
    if((this -> first == NULL) && (this -> last == NULL))
    {
        return;
    }
    else if((this -> first) == (this -> last))
    {
        delete this -> first;

        this -> first = NULL;
        this -> last = NULL;
    }
    else
    {
        this -> first = this -> first -> next;
        delete this -> last->next;

        this -> last->next = first;
    }
    this -> iCount--;
}   // End Of DeleteFirst

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
void SinglyCLL<T>::DeleteLast()
{
    SinglyCLLnode<T> * temp = NULL;

    if(this -> first == NULL && this -> last == NULL)
    {
        return;
    }
    else if(this -> first == this -> last)
    {
        delete this -> first;

        this -> first = NULL;
        this -> last = NULL;
    }
    else
    {
        temp = this -> first;

        while(temp -> next != this -> last)
        {
            temp = temp -> next;
        }

        delete this ->last;
        this -> last = temp;

        this -> last->next = first;
    }
    this -> iCount--;
}   // End of DeleteLast

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

template <class T>
void SinglyCLL<T>::DeleteAtPos(int pos)
{
    SinglyCLLnode<T> * temp = NULL;
    SinglyCLLnode<T> * target = NULL;
    
    int iCnt = 0;
    
    if(pos < 1 || pos > this -> iCount)
    {
        cout<<"Invalid position\n";
        return;
    }

    if(pos == 1)
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

        for(iCnt = 1; iCnt < pos - 1; iCnt++)
        {
            temp = temp -> next;
        }

        target = temp -> next;

        temp->next = target->next;
        delete target;

        this -> iCount--;
    }
}   // End of DeleteAtPos

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
void SinglyCLL<T>::InsertAtPos(T no, int pos)
{
    SinglyCLLnode<T> * temp = NULL;
    SinglyCLLnode<T> * newn = NULL;

    int iCnt = 0;

    if(pos < 1 || pos > this -> iCount+1)
    {
        cout<<"Invalid position\n";
        return;
    }

    if(pos == 1)
    {
        this -> InsertFirst(no);
    }
    else if(pos == iCount+1)
    {
        this -> InsertLast(no);
    }
    else
    {
        newn = new SinglyCLLnode<T>(no);

        temp = this -> first;

        for(iCnt = 1; iCnt < pos -1; iCnt++)
        {
            temp = temp -> next;
        }

        newn->next = temp -> next;
        temp->next = newn;

        this -> iCount++;
    }
}   // End of InsertAtPos

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

template <class T>
void SinglyCLL<T>::Display()
{
    SinglyCLLnode<T> * temp = NULL;
    if((this -> first == NULL) && (this -> last == NULL))
    {
        cout<<"Linked List is Empty\n";
        return;
    }

    temp = this -> first;

    do
    {
        cout<<"| "<<temp->data<<" | -> ";
        temp = temp -> next;
    } while (temp != this -> last ->next);
    
    cout<<"\n";
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
int SinglyCLL<T>::Count()
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
void SinglyCLL<T> :: DeleteAll()
{
    SinglyCLLnode<T> *temp = NULL;

    if (this -> iCount == 0) 
    {
        return;
    }

    temp = this -> first;
    this -> last -> next = NULL;
    this -> last = NULL;

    while(this -> first != NULL)
    {
        temp = this -> first;
        this -> first = this -> first -> next;
        delete temp;
        this -> iCount--;
    }
    this -> Display();
}   // End of DeleteAll

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
void SinglyCLL<T> :: PhysicalReverse()
{
    SinglyCLLnode<T> *pNext = NULL;
	SinglyCLLnode<T> *pCurrent = this -> first;
	SinglyCLLnode<T> *pPrev = this -> last;

    this -> last -> next = NULL;

	while(pCurrent != NULL)
	{
		pNext = pCurrent -> next;
		pCurrent -> next = pPrev;
		pPrev = pCurrent;
		pCurrent = pNext;
	}

    this -> last = this -> first;
	this -> first = pPrev;
}   // End of PhysicalReverse

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
void SinglyCLL<T> :: ReverseDisplay()
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
int SinglyCLL<T> :: SearchFirstOccurrence(T iKey)
{
	int iCount = 0;
	int iPos = 0;
    SinglyCLLnode<T> *pTemp = this -> first;

    if(NULL == this -> first && NULL == this -> last)
    {
        return 0;
    }

	do 
	{
		iCount++;
		if(iKey == pTemp -> data)
        {
			iPos = iCount;
            break;
        }
		pTemp = pTemp -> next;
	}while(pTemp != this -> last -> next);

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
int SinglyCLL<T> :: SearchLastOccurrence(T iKey)
{
	int iCount = 0;
    int iPos = 0;
    SinglyCLLnode<T> *pTemp = this -> first;

	if((NULL == this -> first) && (NULL == this -> last))
	{
        return 0;
    }

	do 
	{
		iCount++;
		if(iKey == pTemp -> data)
        {
			iPos =  iCount;
        }
        pTemp = pTemp-> next;
	}while(pTemp != this -> last -> next);

	return iPos;
}   // End of SearchLastOccurrence

///////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   : SearchAllOccurrence
//  Input           : Data to find in linked list
//  Output          : count of data present in a linked list 
//  Description     : Used to count the occurrence of a data present in a linked list 
//  Author          : Aditya Vijay Mali
//  Date            : 06/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

template <class T>
int SinglyCLL<T> :: SearchAllOccurrence(T iKey)
{
	int iCount = 0;
	int iPos = 0;
    SinglyCLLnode<T> *pTemp = this -> first;

    if (NULL == this -> first && NULL == this -> last)
    {
        return 0;
    }
    
	do 
	{
		iPos++;
		if(iKey == pTemp -> data)
			iCount ++;
		pTemp = pTemp -> next;
	}while(pTemp != this -> last -> next);

	return iCount;
}   // End of SearchAllOccurrence
