#include <iostream>

using namespace std;

// Define a Node class for the linked list
class Node {
public:
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

// Define LinkedList class
class LinkedList {
private:
    Node* head;

public:
    LinkedList() {
        head = nullptr;
    }

    // Method to add elements to the end of the list
    void add(int value) {
        Node* new_node = new Node(value);
        if (head == nullptr) {
            head = new_node;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new_node;
        }
    }

    // Method to display the linked list
    void display() {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "nullptr" << endl;
    }

    // Method to delete the last occurrence of a specified item
    void delete_last_occurrence(int value) {
        if (head == nullptr) {
            return;
        }

        Node* last_occurrence = nullptr;
        Node* current = head;
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->data == value) {
                last_occurrence = prev;
            }
            prev = current;
            current = current->next;
        }

        if (last_occurrence == nullptr && head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
        } else if (last_occurrence != nullptr && last_occurrence->next != nullptr) {
            Node* temp = last_occurrence->next;
            last_occurrence->next = last_occurrence->next->next;
            delete temp;
        }

        cout << "Deleted last occurrence of " << value << endl;
    }
};

// Test the implementation
int main() {
    LinkedList ll;

    // Adding elements to the list
    ll.add(1);
    ll.add(2);
    ll.add(3);
    ll.add(2);
    ll.add(4);
    ll.add(2);

    // Display the initial list
    cout << "Original linked list:" << endl;
    ll.display();

    // Delete last occurrence of 2
    ll.delete_last_occurrence(2);

    // Display the modified list
    cout << "Linked list after deletion:" << endl;
    ll.display();

    // Test deleting the last occurrence of an item that appears multiple times
    ll.delete_last_occurrence(2);
    cout << "Linked list after deleting another occurrence of 2:" << endl;
    ll.display();

    // Test deleting the last occurrence of the only occurrence
    ll.delete_last_occurrence(1);
    cout << "Linked list after deleting the only occurrence of 1:" << endl;
    ll.display();

    // Test deleting the last occurrence of an item that does not exist
    ll.delete_last_occurrence(5);  // 5 doesn't exist in the list
    cout << "Linked list remains unchanged:" << endl;
    ll.display();

    return 0;
}

