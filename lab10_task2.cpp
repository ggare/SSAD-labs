#include <iostream>
#include <string>
#include <memory>

// Text interface
class Text {
public:
    virtual ~Text() = default;
    virtual std::string write() const = 0;
};

// PlainText concrete component
class PlainText : public Text {
private:
    std::string content;

public:
    explicit PlainText(const std::string& text) : content(text) {}

    std::string write() const override {
        return content;
    }
};

// TextDecorator abstract base class
class TextDecorator : public Text {
protected:
    std::unique_ptr<Text> wrappedText;

public:
    explicit TextDecorator(std::unique_ptr<Text> text) : wrappedText(std::move(text)) {}
};

// Bold decorator
class Bold : public TextDecorator {
public:
    explicit Bold(std::unique_ptr<Text> text) : TextDecorator(std::move(text)) {}

    std::string write() const override {
        return "\033[1m" + wrappedText->write() + "\033[0m";
    }
};

// Italic decorator
class Italic : public TextDecorator {
public:
    explicit Italic(std::unique_ptr<Text> text) : TextDecorator(std::move(text)) {}

    std::string write() const override {
        return "\033[3m" + wrappedText->write() + "\033[0m";
    }
};

// Underline decorator
class Underline : public TextDecorator {
public:
    explicit Underline(std::unique_ptr<Text> text) : TextDecorator(std::move(text)) {}

    std::string write() const override {
        return "\033[4m" + wrappedText->write() + "\033[0m";
    }
};

// Main function to demonstrate the decorators
int main() {
    // Create plain text
    auto text = std::make_unique<PlainText>("Hello, Decorator Pattern!");

    // Apply decorators
    auto boldText = std::make_unique<Bold>(std::move(text));
    auto boldItalicText = std::make_unique<Italic>(std::move(boldText));
    auto styledText = std::make_unique<Underline>(std::move(boldItalicText));

    // Output the results
    std::cout << "Plain text: " << std::make_unique<PlainText>("Hello, Decorator Pattern!")->write() << std::endl;
    std::cout << "Bold text: " << Bold(std::make_unique<PlainText>("Hello, Decorator Pattern!")).write() << std::endl;
    std::cout << "Bold + Italic text: " << Italic(std::make_unique<Bold>(std::make_unique<PlainText>("Hello, Decorator Pattern!"))).write() << std::endl;
    std::cout << "Fully styled text: " << styledText->write() << std::endl;

    return 0;
}
