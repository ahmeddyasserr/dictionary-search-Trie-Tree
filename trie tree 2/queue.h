#include <iostream>
using namespace std;

class Queue {
private:
    int* arr;
    int capacity;
    int front;
    int rear;

public:
    Queue(int size) {
        arr = new int[size];
        capacity = size;
        front = -1;
        rear = -1;
    }

    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue is full. Cannot enqueue " << value << endl;
            return;
        }

        if (isEmpty()) {
            front = 0;
        }

        rear = (rear + 1) % capacity;
        arr[rear] = value;
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty. Cannot dequeue." << endl;
            return -1;
        }

        int value = arr[front];

        if (front == rear) {
            front = -1;
            rear = -1;
        }
        else {
            front = (front + 1) % capacity;
        }

        return value;
    }

    bool isEmpty() {
        return front == -1 && rear == -1;
    }

    bool isFull() {
        return (rear + 1) % capacity == front;
    }

    int size() {
        if (isEmpty()) {
            return 0;
        }

        if (front <= rear) {
            return rear - front + 1;
        }
        else {
            return capacity - front + rear + 1;
        }
    }
};

