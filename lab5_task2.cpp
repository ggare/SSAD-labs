#include <iostream>
#include <memory>
using namespace std;

class Box {
public:
    int value;

    Box(int val) : value(val) {
        cout << "Box created with value: " << value << endl;
    }

    ~Box() {
        cout << "Box destroyed with value: " << value << endl;
    }
};

int create_unique(int value) {
    unique_ptr<Box> uniqueBox = make_unique<Box>(value);
    cout << "Value inside unique_ptr Box: " << uniqueBox->value << endl;

    unique_ptr<Box> anotherUniqueBox = move(uniqueBox);
    if (!uniqueBox) {
        cout << "uniqueBox is now nullptr after move" << endl;
    }

    return anotherUniqueBox->value;
}

void create_shared_boxes() {
    shared_ptr<Box> sharedBox1 = make_shared<Box>(10);
    shared_ptr<Box> sharedBox2 = make_shared<Box>(20);

    cout << "sharedBox1 use count: " << sharedBox1.use_count() << endl;
    cout << "sharedBox2 use count: " << sharedBox2.use_count() << endl;

    shared_ptr<Box> sharedBox3 = sharedBox1;
    cout << "sharedBox1 use count after sharing: " << sharedBox1.use_count() << endl;

    cout << "sharedBox1 use count after sharedBox3 is destroyed: " << sharedBox1.use_count() << endl;
}

// Function to demonstrate weak_ptr
void demonstrate_weak_ptr() {
    shared_ptr<Box> sharedBox = make_shared<Box>(30);
    weak_ptr<Box> weakBox = sharedBox;

    cout << "sharedBox use count: " << sharedBox.use_count() << endl;

    if (auto tempSharedBox = weakBox.lock()) {
        cout << "weak_ptr points to a Box with value: " << tempSharedBox->value << endl;
    } else {
        cout << "weak_ptr points to nothing" << endl;
    }

    sharedBox.reset();

    if (auto tempSharedBox = weakBox.lock()) {
        cout << "weak_ptr points to a Box with value: " << tempSharedBox->value << endl;
    } else {
        cout << "weak_ptr points to nothing after sharedBox is reset" << endl;
    }
}

int main() {
    int value = create_unique(5);
    cout << "Returned value from create_unique: " << value << endl;
    create_shared_boxes();
    demonstrate_weak_ptr();

    return 0;
}