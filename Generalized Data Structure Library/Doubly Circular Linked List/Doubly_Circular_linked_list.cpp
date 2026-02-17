///////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   : DoublyCLL
//  Input           : Nothing
//  Output          : Nothing
//  Description     : Used to Construct the object
//  Author          : Aditya Vijay Mali
//  Date            : 06/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

template<class T>
DoublyCLL<T> ::DoublyCLL()
{
    cout<<"object of DoublyCLL gets created.\n";
    this->first = NULL;
    this->last = NULL;
    this->iCount = 0;
}

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

template<class T>
void DoublyCLL<T> :: InsertFirst(T no)
{
    DoublyCLLnode <T> * newn = NULL;

    newn = new DoublyCLLnode<T>(no);

    if ((this -> first == NULL) && (this -> last == NULL))
    {
        this -> first = newn;
        this -> last = newn;
    }
    else 
    {
        newn -> next = this -> first;
        this -> first -> prev = newn;
        this -> first = newn;
    }

    this -> first -> prev = this -> last;
    this -> last -> next = this -> first;

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

template<class T>
void DoublyCLL<T> :: InsertLast(T no)
{
    DoublyCLLnode <T> *newn = NULL;

    newn = new DoublyCLLnode<T>(no);

    if ((this -> first == NULL) && (this -> last == NULL))
    {
        this -> first = newn;
        this -> last = newn;
    }
    else 
    {
        newn -> prev = this -> last;
        this -> last -> next = newn;
        this -> last = newn;
    }

    this -> last -> next = this -> first;
    this -> first -> prev = this -> last;
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

template<class T>
void DoublyCLL<T> :: InsertAtPos(T no, int pos)
{
    DoublyCLLnode <T> * newn = NULL;
    DoublyCLLnode <T> * temp = NULL;
    int iCnt = 0;

    if (pos < 1 || pos > this -> iCount + 1)
    {
        cout<<"Invalid Position"<<endl;
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
        newn = new DoublyCLLnode<T>(no);

        temp = this -> first;

        for(iCnt = 1; iCnt < pos -1; iCnt++)
        {
            temp = temp -> next;
        }

        newn -> next = temp -> next;
        temp -> next -> prev = newn;
        temp -> next = newn;
        newn -> prev = temp;

        this -> iCount++;
    }
}   // End Of InsertAtPos

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

template<class T>
void DoublyCLL<T> :: DeleteFirst()
{
    if ((this -> first == NULL) && (this -> last == NULL))
    {
        return;
    }
    else if ((this -> first) == (this -> last))
    {
        delete this -> first;
        this -> first = NULL;
        this -> last = NULL;
    }
    else
    {
        this -> first = this -> first -> next;
        delete this -> first -> prev;

        this -> last -> next = this -> first;
        this -> first -> prev = this -> last;
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

template<class T>
void DoublyCLL<T> :: DeleteLast()
{
    if ((this -> first == NULL) && (this -> last == NULL))
    {
        return;
    }
    else if ((this -> first) == (this -> last))
    {
        delete this -> first;
        this -> first = NULL;
        this -> last = NULL;
    }
    else
    {
        this -> last = this -> last -> prev;
        delete this -> last -> next;

        this -> first -> prev = this -> last;
        this -> last -> next = this -> first;
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

template<class T>
void DoublyCLL<T> :: DeleteAtPos(int pos)
{
    DoublyCLLnode <T> * temp = NULL;
    int iCnt = 0;

    if (pos < 1 || pos > this -> iCount)
    {
        cout<<"Invalid Position"<<endl;
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

        for(iCnt = 1; iCnt < pos -1; iCnt++)
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

template<class T>
void DoublyCLL<T> :: Display()
{
    DoublyCLLnode <T> *temp = NULL;
    if ((this -> first == NULL) && (this -> last == NULL))
    {
        cout<<"List is Empty";
        return;
    }

    temp = this -> first;

    do
    {
        cout<<"| "<<temp-> data<<" | <=>";
        temp = temp -> next;
    }while(temp  != this -> last -> next);

    cout<<endl;
}   //End of Display

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

template<class T>
int DoublyCLL<T> :: Count()
{
    return this -> iCount;
}   //End of Count

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
void DoublyCLL<T> :: DeleteAll()
{
    DoublyCLLnode <T> *temp =NULL;

    if ((this -> first == NULL) && (this -> last == NULL))
    {
        return;
    }

    temp = this -> first;
    this -> last -> next = NULL;
    this->last = NULL;

    while(this -> first != NULL)
    {
        temp = this -> first;
        this -> first = this -> first -> next;
        delete temp;
        this -> iCount--;
    }
    this -> Display();
}   // End of DeleteAll

template <class T>
void DoublyCLL<T> :: PhysicalReverse()
{
	DoublyCLLnode <T> * pCourrent = this -> first;
	DoublyCLLnode <T> * pNext = NULL;

	(this -> last) -> next = NULL;

	while(pCourrent -> next != NULL)
	{
		pNext = pCourrent -> next;
		pCourrent -> next = pCourrent -> prev;
		pCourrent -> prev = pNext;
		pCourrent = pNext;
	}

	pCourrent -> next = pCourrent -> prev;
	pCourrent -> prev = this -> first;

	this -> last  = this -> first;
	this -> first = pCourrent;
}


template <class T>
void DoublyCLL<T> :: ReverseDisplay()
{
    DoublyCLLnode <T> *temp =NULL;

	if (NULL == this -> first && NULL == this -> last)
	{
		printf("List is Empty\n");
		return;
	}

    temp = this -> last;
	do
	{
        cout<<"| "<<temp-> data<<" | <=>";
		temp = temp -> prev;

	}while(temp != this -> first -> prev);

	printf("\n");
}


template <class T>
int DoublyCLL<T> :: SearchFirstOccurrence(T iKey)
{
    int iCount = 0;
    int iPos = 0;

    DoublyCLLnode <T> *temp = this -> first;

	if(NULL == temp)
		return 0;

	do 
	{
		iCount++;
		if(iKey == temp -> data)
			iPos =  iCount;
		temp = temp -> next;
	}while(temp != this -> last -> next);

	return iPos;
}

template <class T>
int DoublyCLL<T> :: SearchLastOccurrence(T iKey)
{
    int iCount = 0;
	int iPos = 0;
    DoublyCLLnode <T> *temp = this -> first;
	
	if(NULL == this -> first && NULL == this -> last)
    {
	    return 0;
    }

	do 
	{
		iCount++;
		if(iKey == temp -> data)
			iPos = iCount;
		temp = temp -> next;
	}while(temp != this -> last -> next);

	return iPos;
}

template <class T>
int DoublyCLL<T> :: SearchAllOccurrence(T iKey)
{
	int iCount = 0;
	int iPos = 0;
    DoublyCLLnode <T> *temp = this -> first;

	if(NULL == this -> first && NULL == this -> last)
	{
        return 0;
    }

	do 
	{
		iPos++;
		if(iKey == temp -> data)
			iCount ++;
		temp = temp -> next;
	}while(temp != this -> last -> next);

	return iCount;
}
