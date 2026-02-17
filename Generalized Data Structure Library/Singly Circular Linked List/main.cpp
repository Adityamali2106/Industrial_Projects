#include "Singly_Circular_linked_list.hpp"

template <typename T>
void DiaplayMenu() {
    SinglyCLL<T> *sobj = new SinglyCLL<T>();
    int iChoice = 0, iPos = 0;
    T data;
    while (1)
    {
        cout<<"------------------------------------------------------------------------------------------------------\n";
        cout<<"-------------------------- 1. Insert node at First position                  -------------------------\n";
        cout<<"-------------------------- 2. Insert node at Last position                   -------------------------\n";
        cout<<"-------------------------- 3. Insert node at spacific position               -------------------------\n";
        cout<<"-------------------------- 4. Delete a node from first position              -------------------------\n";
        cout<<"-------------------------- 5. Delete a node from last position               -------------------------\n";
        cout<<"-------------------------- 6. Delete a node from spacific position           -------------------------\n";
        cout<<"-------------------------- 7. Delete all nodes present in linked list        -------------------------\n";
        cout<<"-------------------------- 8. Display the linked list in reverse order       -------------------------\n";
        cout<<"-------------------------- 9. physically reverse the linked list             -------------------------\n";
        cout<<"-------------------------- 10. Display lined list                            -------------------------\n";
        cout<<"-------------------------- 11. Get the count of nodes present in linked list -------------------------\n";
        cout<<"-------------------------- 12. Search First Occurrence of specific data in linked list ---------------\n";
        cout<<"-------------------------- 13. Search Last Occurrence of specific data in linked list ----------------\n";
        cout<<"-------------------------- 14. Search all Occurrence of specific data in linked list -----------------\n";
        cout<<"-----------------------------   15. Exit Application         -----------------------------------------\n\n";

        cout<<"------------------------------------------------------------------------------------------------------\n";
        cout<<"-----------------------------------  Enter your choice : ---------------------------------------------\n";
        cin>>iChoice;
        cout<<"------------------------------------------------------------------------------------------------------\n";

        switch (iChoice)
        {
        case 1:
            cout<<"---------------------------- Enter data to insert :     -----------------------------------------\n";
            cin>>data;
            sobj -> InsertFirst(data);
            break;
        case 2:
            cout<<"---------------------------- Enter data to insert :     -----------------------------------------\n"; 
            cin>>data;
            sobj -> InsertLast(data);
            break;
        case 3:
            cout<<"---------------------------- Enter data to insert :     -----------------------------------------\n"; 
            cin>>data;
            cout<<"-------------------------- Enter position to insert :   -----------------------------------------\n"; 
            int iPos;
            cin>>iPos;
            sobj -> InsertAtPos(data,iPos);
            break;
        case 4:
            sobj -> DeleteFirst();
            break;
        case 5:
            sobj -> DeleteLast();
            break;
        case 6:
            cout<<"-------------------------- Enter position to delete :  -----------------------------------------\n";
            cin>>iPos;
            sobj -> DeleteAtPos(iPos);
            break;
        case 7:
            sobj -> DeleteAll();
            break;
        case 8:
            sobj -> ReverseDisplay();
            break;
        case 9:
            sobj -> PhysicalReverse();
            break;
        case 10:
            sobj -> Display();
            break;
        case 11:
            cout<<"-------------------------- Count of nodes present in linked list :  -----------------------------\n";
            cout<<sobj -> Count()<<"\n";
            break;
        case 12:
            cout<<"-------------------------- Enter data to search :        -----------------------------------------\n";
            cin>>data;
            cout<<" Data found at position  :  \t";
            cout<<sobj -> SearchFirstOccurrence(data)<<"\n";
            break;
        case 13:
            cout<<"-------------------------- Enter data to search :     -----------------------------------------\n";
            cin>>data;
            cout<<" Data found at position  :  \t";
            cout<<sobj -> SearchLastOccurrence(data)<<"\n";
            break;
        case 14:
            cout<<"-------------------------- Enter data to search :     -----------------------------------------\n";
            cin>>data;
            cout<<"All Occurrence of "<<data<<" is : \t";
            cout<<sobj -> SearchAllOccurrence(data)<<"\n";
            break;
        case 15:
            cout<<"Thank You \n";
            exit(0);

        default : 
            cout<<"-------------------------- Invalid choice please enter valid choice :    ----------------------\n";
            break;
        }
    }
}

int main() {
    char Datatype[20];
    cout << "Enter the datatype (Integer, Charactor, float, Double): ";
    cin >> Datatype;

    if (strcmp(Datatype, "Integer") == 0) {
        DiaplayMenu<int>();
    } 
    else if (strcmp(Datatype, "Charactor") == 0) {
        DiaplayMenu<char>();
    } 
    else if (strcmp(Datatype, "float") == 0) {
        DiaplayMenu<float>();
    } 
    else if (strcmp(Datatype, "Double") == 0) {
        DiaplayMenu<double>();
    } 
    else {
        cout << "Invalid Data Type!" << endl;
    }

    return 0;
}