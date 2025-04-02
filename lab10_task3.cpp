#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>

// User roles
enum class UserRole {
    GUEST,
    REGULAR,
    ADMIN
};

// Document interface
class Document {
public:
    virtual ~Document() = default;
    virtual void display(const std::string& user) const = 0;
};

// RealDocument class - the actual sensitive document
class RealDocument : public Document {
private:
    std::string content;

public:
    explicit RealDocument(const std::string& docContent) : content(docContent) {}

    void display(const std::string& user) const override {
        std::cout << "Displaying sensitive document to " << user << ":\n";
        std::cout << content << "\n";
    }
};

// SecureDocumentProxy class - controls access to RealDocument
class SecureDocumentProxy : public Document {
private:
    std::unique_ptr<RealDocument> realDocument;
    UserRole requiredRole;

public:
    SecureDocumentProxy(const std::string& content, UserRole role) 
        : realDocument(std::make_unique<RealDocument>(content)), requiredRole(role) {}

    void display(const std::string& user) const override {
        // Check access based on user role (simplified - in real app, you'd have user objects)
        UserRole userRole = getUserRole(user);

        if (userRole >= requiredRole) {
            std::cout << "Access granted to " << user << " (role: " << roleToString(userRole) << ")\n";
            realDocument->display(user);
        } else {
            std::cout << "Access denied to " << user << " (role: " << roleToString(userRole) 
                      << "). Required role: " << roleToString(requiredRole) << "\n";
        }
    }

private:
    // Helper function to simulate getting user role (in a real app, this would check a database)
    UserRole getUserRole(const std::string& user) const {
        if (user == "admin") return UserRole::ADMIN;
        if (user == "john" || user == "mary") return UserRole::REGULAR;
        return UserRole::GUEST;
    }

    // Helper function to convert role to string
    std::string roleToString(UserRole role) const {
        switch (role) {
            case UserRole::GUEST: return "Guest";
            case UserRole::REGULAR: return "Regular";
            case UserRole::ADMIN: return "Admin";
            default: return "Unknown";
        }
    }
};

// Main function to demonstrate the proxy
int main() {
    // Create documents with different access levels
    auto publicDoc = SecureDocumentProxy("Public information", UserRole::GUEST);
    auto confidentialDoc = SecureDocumentProxy("Company confidential data", UserRole::REGULAR);
    auto topSecretDoc = SecureDocumentProxy("Top secret plans", UserRole::ADMIN);

    // Test access with different users
    std::cout << "=== Testing Public Document ===\n";
    publicDoc.display("guest");
    publicDoc.display("john");
    publicDoc.display("admin");

    std::cout << "\n=== Testing Confidential Document ===\n";
    confidentialDoc.display("guest");
    confidentialDoc.display("john");
    confidentialDoc.display("admin");

    std::cout << "\n=== Testing Top Secret Document ===\n";
    topSecretDoc.display("guest");
    topSecretDoc.display("john");
    topSecretDoc.display("admin");

    return 0;
}
