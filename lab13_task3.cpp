#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>

using namespace std;

class File {
public:
    string path;
    File(const string& path) : path(path) {}
};

class EventListener {
public:
    virtual ~EventListener() = default;
    virtual void update(const string& eventType, const File& file) = 0;
};

class EventManager {
private:
    map<string, vector<shared_ptr<EventListener>>> listeners;

public:
    EventManager(const vector<string>& operations) {
        for (const auto& op : operations) {
            listeners[op] = vector<shared_ptr<EventListener>>();
        }
    }

    void subscribe(const string& eventType, shared_ptr<EventListener> listener) {
        if (listeners.find(eventType) != listeners.end()) {
            listeners[eventType].push_back(listener);
        }
    }

    void unsubscribe(const string& eventType, shared_ptr<EventListener> listener) {
        if (listeners.find(eventType) != listeners.end()) {
            auto& vec = listeners[eventType];
            vec.erase(vec.begin(), vec.end());
        }
    }

    void notify(const string& eventType, const File& file) {
        if (listeners.find(eventType) != listeners.end()) {
            for (const auto& listener : listeners[eventType]) {
                listener->update(eventType, file);
            }
        }
    }
};

class Editor {
public:
    unique_ptr<EventManager> events;
    unique_ptr<File> file;

    Editor() {
        events = make_unique<EventManager>(vector<string>{"open", "save"});
    }

    void openFile(const string& filePath) {
        file = make_unique<File>(filePath);
        events->notify("open", *file);
    }

    void saveFile() {
        if (!file) {
            cerr << "No file is open!" << endl;
            return;
        }
        // Simulate file saving
        cout << "Saving file: " << file->path << endl;
        events->notify("save", *file);
    }
};

// Concrete Listener 1: Logs all file operations
class LoggingListener : public EventListener {
public:
    void update(const string& eventType, const File& file) override {
        cout << "[LOG] " << eventType << " operation performed on file: "
             << file.path << endl;
    }
};

// Concrete Listener 2: Sends emails on specific events
class EmailNotificationListener : public EventListener {
    string email;
public:
    EmailNotificationListener(const string& email) : email(email) {}

    void update(const string& eventType, const File& file) override {
        if (eventType == "save") {
            cout << "[EMAIL] Sending notification to " << email
                 << ": File " << file.path << " was saved." << endl;
        }
    }
};

int main() {
    // Create editor
    Editor editor;

    // Create listeners
    auto logger = make_shared<LoggingListener>();
    auto emailAlerts = make_shared<EmailNotificationListener>("admin@example.com");

    // Subscribe listeners to events
    editor.events->subscribe("open", logger);
    editor.events->subscribe("save", logger);
    editor.events->subscribe("save", emailAlerts);

    // Test file operations
    cout << "Opening file1.txt..." << endl;
    editor.openFile("file1.txt");

    cout << "\nSaving file1.txt..." << endl;
    editor.saveFile();

    cout << "\nOpening another file..." << endl;
    editor.openFile("file2.txt");

    // Unsubscribe email alerts from save events
    editor.events->unsubscribe("save", emailAlerts);

    cout << "\nSaving file2.txt after unsubscribing email alerts..." << endl;
    editor.saveFile();

    return 0;
}
