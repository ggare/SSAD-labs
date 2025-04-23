#include <iostream>
#include <string>

using namespace std;

// Handler interface with setNext() and handle() methods
class Handler {
public:
    virtual ~Handler() {}
    virtual Handler* setNext(Handler* handler) = 0;
    virtual bool handle(const string& request) = 0;
};

// AbstractHandler base class that implements Handler
class AbstractHandler : public Handler {
private:
    Handler* next_handler;
public:
    AbstractHandler() : next_handler(nullptr) {}
    
    Handler* setNext(Handler* handler) override {
        this->next_handler = handler;
        return handler;
    }
    
    bool handle(const string& request) override {
        if (this->next_handler) {
            return this->next_handler->handle(request);
        }
        return true; // default behavior if no next handler
    }
};

// AuthenticationHandler that inherits from AbstractHandler
class AuthenticationHandler : public AbstractHandler {
public:
    bool handle(const string& request) override {
        if (request != "valid" && request != "admin") {
            cout << "Authentication failed: Invalid request." << endl;
            return false;
        }
        cout << "Authentication successful." << endl;
        return AbstractHandler::handle(request);
    }
};

// RoleCheckHandler that inherits from AbstractHandler
class RoleCheckHandler : public AbstractHandler {
public:
    bool handle(const string& request) override {
        if (request == "admin") {
            cout << "Role check: Admin privileges granted." << endl;
            return true;
        }
        cout << "Role check: Standard user privileges." << endl;
        return AbstractHandler::handle(request);
    }
};

void processRequest(const string& request, Handler* handler) {
    cout << "Processing: " << request << endl;
    if (!handler->handle(request)) {
        cout << "Request denied.\n" << endl;
    } else {
        cout << "Request approved.\n" << endl;
    }
}

int main() {
    Handler* roleCheck = new RoleCheckHandler();
    Handler* auth = new AuthenticationHandler();

    auth->setNext(roleCheck); // Set the chain: auth -> roleCheck

    processRequest("valid", auth);
    processRequest("invalid", auth);
    processRequest("admin", auth);

    delete auth;
    delete roleCheck;

    return 0;
}
