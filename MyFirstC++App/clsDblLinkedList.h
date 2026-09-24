#pragma once
#include <iostream>
using namespace std;

template <class T>
class clsDblLinkedList
{

protected:
    int _Size = 0;

public:

    class Node {
    public:
        T value;
        Node* next;
        Node* prev;
    };

    Node* head = NULL;

    void InsertAtBeginning(T value)
    {

        Node* newNode = new Node();
        newNode->value = value;
        newNode->next = head;
        newNode->prev = NULL;

        if (head != NULL) {
            head->prev = newNode;
        }
        head = newNode;
        _Size++;

    }

    void PrintList() {
        Node* Current = head;

        while (Current != NULL) {
            cout << Current->value << " ";
            Current = Current->next;
        }
        cout << "\n";


    }

    Node* Find(T Value)
    {
        Node* Current = head;
        while (Current != NULL) {

            if (Current->value == Value)
                return Current;

            Current = Current->next;
        }

        return NULL;

    }

    void InsertAfter(Node* current, T value) {

        Node* newNode = new Node();
        newNode->value = value;
        newNode->next = current->next;
        newNode->prev = current;

        if (current->next != NULL) {
            current->next->prev = newNode;
        }
        current->next = newNode;
        _Size++;

    }

    void InsertAtEnd(T value) {

        Node* newNode = new Node();
        newNode->value = value;
        newNode->next = NULL;
        if (head == NULL) {
            newNode->prev = NULL;
            head = newNode;
        }
        else {
            Node* current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
            newNode->prev = current;

        }
        _Size++;

    }

    void DeleteNode(Node*& NodeToDelete) {

        if (head == NULL || NodeToDelete == NULL) {
            return;
        }
        if (head == NodeToDelete) {
            head = NodeToDelete->next;
        }
        if (NodeToDelete->next != NULL) {
            NodeToDelete->next->prev = NodeToDelete->prev;
        }
        if (NodeToDelete->prev != NULL) {
            NodeToDelete->prev->next = NodeToDelete->next;
        }
        delete NodeToDelete;
        _Size--;


    }

    void DeleteFirstNode()
    {

        if (head == NULL) {
            return;
        }
        Node* temp = head;
        head = head->next;
        if (head != NULL) {
            head->prev = NULL;
        }
        delete temp;
        _Size--;

    }

    void DeleteLastNode() {

        if (head == NULL) {
            return;
        }

        if (head->next == NULL) {
            delete head;
            head = NULL;
            return;
        }

        Node* current = head;

        while (current->next->next != NULL)
        {
            current = current->next;
        }

        Node* temp = current->next;
        current->next = NULL;
        delete temp;
        _Size--;

    }

    short Size() {
        return _Size;

    }

    bool IsEmpty() {
        return (_Size == 0 ? true : false);
    }

    void Clear() {
        while (_Size > 0) {
            DeleteFirstNode();
        }
    }

    void  Reverse()
    {
        Node* current = head;
        Node* temp = nullptr;
        while (current != nullptr) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }

        if (temp != nullptr) {
            head = temp->prev;
        }
    }

    Node* GetNode(int Index) {

        Node* Current = head;

        int Counter = 0;

        if (Index > _Size - 1 || Index < 0) {
            return NULL;
        }


        while (Current != NULL && (Current->next != NULL)) {
            if (Counter == Index) {
                break;
            }
            Current = Current->next;
            Counter++;
        }
        return Current;
    }

    T GetItem(int Index) {

        Node* ItemNode = GetNode(Index);

        if (ItemNode == NULL)
            return NULL;
        else
            return ItemNode->value;

    }

    bool UpdateItem(int Index, T NewValue) {
        Node* ItemNode = GetNode(Index);

        if (ItemNode != NULL) {
            ItemNode->value = NewValue;
            return true;
        }
        else {
            return false;
        }
    }

    bool InsertAfter(int Index, T Value) {
        Node* ItemNode = GetNode(Index);

        if (ItemNode != NULL) {
            InsertAfter(ItemNode, Value);
            return true;
        }
        else {
            return false;
        }
    }
};
