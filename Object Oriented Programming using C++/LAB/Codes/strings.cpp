#include <iostream>
#include <queue> // Include the queue library

using namespace std;

int main() {
    // Create a queue to store integer values
    queue<int> myQueue;

    // Enqueue elements onto the queue
    myQueue.push(10);  // Add 10 to the back
    myQueue.push(20);  // Add 20 to the back
    myQueue.push(30);  // Add 30 to the back

    // Display the front and back elements
    cout << "Front element: " << myQueue.front() << endl;
    cout << "Back element: " << myQueue.back() << endl;

    // Dequeue elements from the queue
    cout << "Dequeuing elements from the queue: ";
    while (!myQueue.empty()) {
        cout << myQueue.front() << " "; // Access the front element
        myQueue.pop();                  // Remove the front element
    }
    cout << endl;

    // Check if the queue is empty
    if (myQueue.empty()) {
        cout << "The queue is now empty." << endl;
    }

    return 0;
}
