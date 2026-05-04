#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* prev;
    Node* next;
    Node(int val) : data(val), prev(NULL), next(NULL) {}
};

class CircularDoublyLinkedList {
private:
    Node* head;

public:
    CircularDoublyLinkedList() {
        head = NULL;
    }

    // Insert at beginning
    void insertAtBeginning(int val) {
        Node* newNode = new Node(val);
        if (head == NULL) {
            newNode->next = newNode;
            newNode->prev = newNode;
            head = newNode;
        }
        else {
            Node* tail = head->prev;
            newNode->next = head;
            newNode->prev = tail;
            tail->next = newNode;
            head->prev = newNode;
            head = newNode;
        }
        cout << val << " inserted at beginning.\n";
    }

    // Insert at end
    void insertAtEnd(int val) {
        Node* newNode = new Node(val);
        if (head == NULL) {
            newNode->next = newNode;
            newNode->prev = newNode;
            head = newNode;
        }
        else {
            Node* tail = head->prev;
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
        }
        cout << val << " inserted at end.\n";
    }

    // Delete from beginning
    void deleteAtBeginning() {
        if (head == NULL) {
            cout << "List is empty. Cannot delete.\n";
            return;
        }
        if (head->next == head) {
            // Single node
            cout << head->data << " deleted 'was only node becuase only signle node is there'.\n";
            delete head;
            head = NULL;
            return;
        }
        Node* tail = head->prev;
        Node* toDelete = head;
        head = head->next;
        head->prev = tail;
        tail->next = head;
        cout << toDelete->data << " deleted from beginning.\n";
        delete toDelete;
    }

    // Delete from end
    void deleteAtEnd() {
        if (head == NULL) {
            cout << "List is empty. Cannot delete.\n";
            return;
        }
        if (head->next == head) {
            // Single node
            cout << head->data << " deleted from 'End as it is single node'.\n";
            delete head;
            head = NULL;
            return;
        }
        Node* tail = head->prev;
        tail->prev->next = head;
        head->prev = tail->prev;
        cout << tail->data << " deleted from end.\n";
        delete tail;
    }

    // Search
    void search(int val) {
        if (head == NULL) {
            cout << "List is empty.\n";
            return;
        }
        Node* temp = head;
        int pos = 1;
        while (temp != NULL) {
            if (temp->data == val) {
                cout << val << " found at position " << pos << ".\n";
                return;
            }
            temp = temp->next;
            pos++;
            if (temp == head)
                break;
        }
        cout << val << " not found in list.\n";
    }

    // Forward traversal
    void displayForward() {
        if (head == NULL) {
            cout << "List is empty.\n";
            return;
        }
        cout << "Forward: ";
        Node* temp = head;
        while (temp != NULL) {
            cout << temp->data;
            if (temp->next != head) cout << " <-> ";
            temp = temp->next;
            if (temp == head)
                break;
        }
        cout << " 'circular back to " << head->data << "\n";
    }

    // Backward traversal
    void displayBackward() {
        if (head == NULL) {
            cout << "List is empty.\n";
            return;
        }
        cout << "Backward: ";
        Node* tail = head->prev;
        Node* temp = tail;
        while (temp != NULL) {
            cout << temp->data;
            if (temp->prev != tail) cout << " <-> ";
            temp = temp->prev;
            if (temp == tail)
                break;
        }
        cout << " (circular back to " << tail->data << ")\n";
    }

    ~CircularDoublyLinkedList() {
        if (head == NULL) return;
        Node* tail = head->prev;
        tail->next = NULL; // break the circle
        Node* temp = head;
        while (temp != NULL) {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        head = NULL;
    }
};

int main() {
    CircularDoublyLinkedList cir;

    cir.insertAtEnd(3);
    cir.insertAtEnd(4);
    cir.insertAtEnd(7);
    cir.displayForward();
    cir.displayBackward();

    cir.insertAtBeginning(5);
    cir.displayForward();

    cir.deleteAtBeginning();
    cir.displayForward();

    cir.deleteAtEnd();
    cir.displayForward();

    cir.search(20);
    cir.search(3);

    //  single node(cases)
    cir.deleteAtBeginning();
    cir.deleteAtBeginning();
    cir.deleteAtBeginning(); // empty list check

    return 0;
}