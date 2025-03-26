#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Component interface
class Component {
public:
    virtual ~Component() = default;
    virtual void display(int depth = 0) const = 0;
    virtual std::string getName() const = 0;
};

// File class (Leaf)
class File : public Component {
private:
    std::string name;

public:
    File(std::string name) : name(name) {}

    void display(int depth = 0) const override {
        std::cout << std::string(depth * 2, ' ') << "File: " << name << std::endl;
    }

    std::string getName() const override {
        return name;
    }
};

// Directory class (Composite)
class Directory : public Component {
private:
    std::string name;
    std::vector<std::unique_ptr<Component>> components;

public:
    Directory(std::string name) : name(name) {}

    void addComponent(Component* component) {
        components.emplace_back(component);
    }

    void display(int depth = 0) const override {
        std::cout << std::string(depth * 2, ' ') << "Directory: " << name << std::endl;
        for (const auto& component : components) {
            component->display(depth + 1);
        }
    }

    std::string getName() const override {
        return name;
    }
};

int main() {
    Directory root("Root");
    File* file1 = new File("File1.txt");
    File* file2 = new File("File2.txt");
    Directory* dir1 = new Directory("Dir1");
    File* file3 = new File("File3.txt");
    File* file4 = new File("File4.txt");
    Directory* dir2 = new Directory("Dir2");

    root.addComponent(file1);
    root.addComponent(file2);
    root.addComponent(dir1);
    dir1->addComponent(file3);
    dir1->addComponent(file4);
    dir1->addComponent(dir2);

    root.display();

    // No need to delete manually since we're using unique_ptr
    // The components will be automatically deleted when the Directory is destroyed

    return 0;
}
