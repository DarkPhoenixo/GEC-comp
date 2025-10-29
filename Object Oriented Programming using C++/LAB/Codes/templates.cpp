#include <iostream>

using namespace std;

template <typename T>
struct Node {
    T value;
    Node<T>* previous;
    Node<T>* next;
};

template <typename T>
class DoublyLinkedList {
public:
    DoublyLinkedList() : start(nullptr) {}

    void initList(T data) {
        start = new Node<T>();
        start->value = data;
        start->previous = nullptr;
        start->next = nullptr;
    }

    void insertAtBeginning(T data) {
        Node<T>* newNode = new Node<T>();
        newNode->value = data;
        newNode->previous = nullptr;
        newNode->next = start;
        if (start) {
            start->previous = newNode;
        }
        start = newNode;
    }

    void insertAtEnd(T data) {
        Node<T>* newNode = new Node<T>();
        Node<T>* tempNode = start;
        while (tempNode->next != nullptr) {
            tempNode = tempNode->next;
        }
        newNode->value = data;
        newNode->previous = tempNode;
        newNode->next = nullptr;
        tempNode->next = newNode;
    }

    void insertAfter(T data, T item) {
        Node<T>* newNode = new Node<T>();
        Node<T>* tempNode = start;
        while (tempNode != nullptr) {
            if (tempNode->value == item) {
                newNode->value = data;
                newNode->previous = tempNode;
                newNode->next = tempNode->next;
                if (tempNode->next != nullptr) {
                    tempNode->next->previous = newNode;
                }
                tempNode->next = newNode;
                return;
            }
            tempNode = tempNode->next;
        }
        cout << "Item not found\n";
    }

    void insertBefore(T item, T data) {
        Node<T>* newNode = new Node<T>();
        Node<T>* tempNode = start;
        if (start == nullptr) {
            cout << "\nThe list is empty\n";
            return;
        }
        if (start->value == item) {
            newNode->value = data;
            newNode->next = start;
            start = newNode;
            return;
        }
        while (tempNode->next != nullptr) {
            if (tempNode->next->value == item) {
                newNode->value = data;
                newNode->next = tempNode->next;
                tempNode->next = newNode;
                return;
            }
            tempNode = tempNode->next;
        }
        cout << "\nItem not found\n";
    }

    void createList() {
        int numElements;
        T data;
        cout << "How many elements would you like to add? ";
        cin >> numElements;
        if (numElements == 0) {
            return;
        }
        cout << "Enter the first element: ";
        cin >> data;
        initList(data);
        for (int i = 1; i < numElements; i++) {
            cout << "Enter the next element: ";
            cin >> data;
            insertAtEnd(data);
        }
    }

    void printList() const {
        Node<T>* temp = start;

        // Print start pointer in a box pointing to the first node
        cout << "\n  start\n";
        cout << "----------\n";
        cout << "|" << start << "|\n";
        cout << "----------\n";
        cout << "     |               \n";
        if (start != nullptr) {
            cout << "     V               \n\n";
        }

        while (temp != nullptr) {
            if (temp->previous == nullptr) {
                cout << "  -----------------------------------------    \n";
                cout << " | Prev: NULL   | Data: " << temp->value << " | Next: " << temp->next << " |     " << temp << " \n";
                cout << "  -----------------------------------------    \n";
            } else if (temp->next == nullptr) {
                cout << "  -----------------------------------------    \n";
                cout << " | Prev: " << temp->previous << " | Data: " << temp->value << " | Next:  NULL  |     " << temp << " \n";
                cout << "  -----------------------------------------    \n";
            } else {
                cout << "  -----------------------------------------    \n";
                cout << " | Prev: " << temp->previous << " | Data: " << temp->value << " | Next: " << temp->next << " |     " << temp << " \n";
                cout << "  -----------------------------------------    \n";
            }

            if (temp->next != nullptr) {
                cout << "          ^                        |\n";
                cout << "          |                        v\n";
            }
            temp = temp->next;
        }
        cout << "\nNULL\n";
    }

    int countNodes() const {
        int count = 0;
        for (Node<T>* tempNode = start; tempNode != nullptr; tempNode = tempNode->next) {
            count++;
        }
        return count;
    }

    Node<T>* search(T item) const {
        Node<T>* tempNode = start;
        while (tempNode != nullptr) {
            if (tempNode->value == item) {
                return tempNode;
            }
            tempNode = tempNode->next;
        }
        return nullptr;
    }

    void removeNode(T data) {
        Node<T>* tempNode = start;
        Node<T>* prevNode = nullptr;
        while (tempNode != nullptr) {
            if (tempNode->value == data) {
                if (prevNode != nullptr) {
                    prevNode->next = tempNode->next;
                } else {
                    start = tempNode->next;
                }
                if (tempNode->next != nullptr) {
                    tempNode->next->previous = prevNode;
                }
                delete tempNode;
                return;
            }
            prevNode = tempNode;
            tempNode = tempNode->next;
        }
        cout << "Element not found\n";
    }

    void reverseList() {
        Node<T>* tempNode = nullptr;
        Node<T>* current = start;
        while (current != nullptr) {
            tempNode = current->previous;
            current->previous = current->next;
            current->next = tempNode;
            current = current->previous;
        }
        if (tempNode != nullptr) {
            start = tempNode->previous;
        }
    }

    void swapAlternateNodes() {
        if (start == nullptr || start->next == nullptr) {
            return;
        }

        Node<T>* tempNode1 = start;
        Node<T>* tempNode2 = start->next;
        start = tempNode2;
        Node<T>* temp;

        while (true) {
            temp = tempNode2->next;
            tempNode2->next = tempNode1;
            tempNode2->previous = tempNode1->previous;
            tempNode1->previous = tempNode2;
            tempNode1->next = temp;
            if (temp == nullptr || temp->next == nullptr) {
                break;
            }
            tempNode1->next = temp->next;
            tempNode1 = temp;
            tempNode2 = tempNode1->next;
        }
    }

private:
    Node<T>* start;
};

int main() {
    int option;
    int data, item;
    DoublyLinkedList<int> list;

    do {
        cout << "\n\n****** OPTIONS ******\n";
        cout << "1. Initialize List\n";
        cout << "2. Display List\n";
        cout << "3. Count Nodes\n";
        cout << "4. Search for Element\n";
        cout << "5. Add to Empty List\n";
        cout << "6. Insert at Start\n";
        cout << "7. Insert at End\n";
        cout << "8. Insert After Element\n";
        cout << "9. Insert Before Element\n";
        cout << "10. Delete an Element\n";
        cout << "11. Reverse List\n";
        cout << "12. Exit\n";
        cout << "Choose an option: ";
        cin >> option;

        switch (option) {
            case 1:
                list.createList();
                break;
            case 2:
                list.printList();
                break;
            case 3:
                cout << "Total nodes: " << list.countNodes() << "\n";
                break;
            case 4:
                cout << "Enter the element to search for: ";
                cin >> item;
                if (list.search(item) != nullptr) {
                    cout << "Element found\n";
                } else {
                    cout << "Element not found\n";
                }
                break;
            case 5:
                cout << "Enter the value to add: ";
                cin >> data;
                list.initList(data);
                break;
            case 6:
                cout << "Enter the value to add: ";
                cin >> data;
                list.insertAtBeginning(data);
                break;
            case 7:
                cout << "Enter the value to add: ";
                cin >> data;
                list.insertAtEnd(data);
                break;
            case 8:
                cout << "Enter the value to add: ";
                cin >> data;
                cout << "Enter the element to insert after: ";
                cin >> item;
                list.insertAfter(data, item);
                break;
            case 9:
                cout << "Enter the value to add: ";
                cin >> data;
                cout << "Enter the element to insert before: ";
                cin >> item;
                list.insertBefore(item, data);
                break;
            case 10:
                cout << "Enter the element to delete: ";
                cin >> data;
                list.removeNode(data);
                break;
            case 11:
                list.reverseList();
                cout << "List reversed\n";
                break;
            case 12 :
                 break;
            default:
                cout << "Invalid option\n";
                break;
        }
    } while (option != 12);

    return 0;
}
