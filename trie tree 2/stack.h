template<typename T>
class Stacks {
private:
    T* items;
    int top;
    int size;  

public:
    
    Stacks(int Maxsize = 10) : size(Maxsize), top(-1) {  
        items = new T[size];
    }

    ~Stacks() {
        delete[] items;
    }

    bool isEmpty() const {
        return top == -1;
    }

    bool push(const T& newItem) {
        if (top >= size - 1) {
            return false; 
        }
        items[++top] = newItem;
        return true;
    }

    bool pop(T& topEntry) {
        if (isEmpty()) {
            return false;
        }
        topEntry = items[top--];
        return true;
    }

    bool peek(T& topEntry) const {
        if (isEmpty()) {
            return false;
        }
        topEntry = items[top];
        return true;
    }
};
