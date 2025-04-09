#include <iostream>
#include <string>
using namespace std;

// Interface
class ITransport {
public:
    virtual void deliver() = 0;
    virtual ~ITransport() = default;
};

// Truck Class
class Truck : public ITransport {
private:
    string address;
public:
    Truck(const string& addr) : address(addr) {}
    void deliver() override {
        cout << "Delivering by Truck to address: " << address << endl;
    }
};

// Ship Class
class Ship : public ITransport {
private:
    string country;
public:
    Ship(const string& c) : country(c) {}
    void deliver() override {
        cout << "Delivering by Ship to country: " << country << endl;
    }
};

// Plane Class
class Plane : public ITransport {
private:
    string country;
public:
    Plane(const string& c) : country(c) {}
    void deliver() override {
        cout << "Delivering by Plane to country: " << country << endl;
    }
};

class TransportFactory {
public:
    ITransport* getTransport(const string& type, const string& location) {
        if (type == "Truck") {
            return new Truck(location);
        } else if (type == "Ship") {
            return new Ship(location);
        } else if (type == "Plane") {
            return new Plane(location);
        } else {
            return nullptr;
        }
    }
};

int main() {
    TransportFactory factory;

    ITransport* t1 = factory.getTransport("Truck", "123 Main Street");
    ITransport* t2 = factory.getTransport("Ship", "Germany");
    ITransport* t3 = factory.getTransport("Plane", "USA");

    if (t1) t1->deliver();
    if (t2) t2->deliver();
    if (t3) t3->deliver();

    // Clean up
    delete t1;
    delete t2;
    delete t3;

    return 0;
}
