#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
using namespace std;

template <typename T>
class GenericStack {
private:
    vector<T> elements;
    size_t capacity;

public:
    explicit GenericStack(size_t initialCapacity = 10) : capacity(initialCapacity) {
        elements.reserve(initialCapacity);
    }

    void push(const T& element) {
        elements.push_back(element);
    }

    T pop() {
        if (elements.empty()) {
            throw out_of_range("Stack is empty");
        }
        T topElement = elements.back();
        elements.pop_back();
        return topElement;
    }

    T peek() const {
        if (elements.empty()) {
            throw out_of_range("Stack is empty");
        }
        return elements.back();
    }

    bool isEmpty() const {
        return elements.empty();
    }

    size_t size() const {
        return elements.size();
    }
};

class StringStack : public GenericStack<string> {
public:
    using GenericStack::GenericStack;

    void push(const std::string& element) {
        if (element.empty()) {
            throw std::invalid_argument("Cannot push an empty string");
        }
        GenericStack::push(element);
    }

    void concatTopTwo() {
        if (size() < 2) {
            throw std::out_of_range("Not enough elements to concatenate");
        }
        string first = pop();
        string second = pop();
        push(second + first);
    }
};

int main() {
    try {
        StringStack stack;
        stack.push("Hello");
        stack.push("World");
        stack.push("SSAD");
        stack.concatTopTwo();
        cout << "Top element after concatenation: " << stack.peek() << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}