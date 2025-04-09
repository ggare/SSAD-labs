#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

using namespace std;

// Flyweight class
class FormatType {
public:
    string font;
    int size;
    string color;

    FormatType(const string& f, int s, const string& c)
        : font(f), size(s), color(c) {}

    void print() const {
        cout << "Font: " << font << ", Size: " << size << ", Color: " << color << endl;
    }
};

// Flyweight Factory
class FormatFactory {
private:
    static unordered_map<string, shared_ptr<FormatType>> formats;

public:
    static shared_ptr<FormatType> getFormat(const string& font, int size, const string& color) {
        string key = font + "_" + to_string(size) + "_" + color;
        if (formats.find(key) == formats.end()) {
            formats[key] = make_shared<FormatType>(font, size, color);
        }
        return formats[key];
    }

    static int totalFormats() {
        return formats.size();
    }
};

unordered_map<string, shared_ptr<FormatType>> FormatFactory::formats;

// Context class
class FormattedCharacter {
private:
    char character;
    shared_ptr<FormatType> format;

public:
    FormattedCharacter(char c, shared_ptr<FormatType> f) : character(c), format(f) {}

    void print() const {
        cout << "Character: " << character << " with properties: ";
        format->print();
    }
};

// Client code
int main() {
    vector<FormattedCharacter> document;

    // Add characters using shared formats
    auto redArial12 = FormatFactory::getFormat("Arial", 12, "Red");
    auto blackTimes12 = FormatFactory::getFormat("Times New Roman", 12, "Black");
    auto blueArial14 = FormatFactory::getFormat("Arial", 14, "Blue");
    auto greenArial16 = FormatFactory::getFormat("Arial", 16, "Green");

    document.emplace_back('H', redArial12);
    document.emplace_back('e', redArial12);
    document.emplace_back('l', redArial12);
    document.emplace_back('l', redArial12);
    document.emplace_back('o', redArial12);

    document.emplace_back(' ', blackTimes12);

    document.emplace_back('W', blueArial14);
    document.emplace_back('o', blueArial14);
    document.emplace_back('r', blueArial14);
    document.emplace_back('l', blueArial14);
    document.emplace_back('d', blueArial14);

    document.emplace_back('!', greenArial16);

    // Output
    cout << "Document content:\n";
    for (const auto& fc : document) {
        fc.print();
    }

    // Memory analysis
    cout << "\nMemory Usage Analysis:\n";
    cout << "Total characters: " << document.size() << endl;
    cout << "Unique formats shared using Flyweight: " << FormatFactory::totalFormats() << endl;

    return 0;
}
