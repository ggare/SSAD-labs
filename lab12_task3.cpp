#include <iostream>
#include <vector>
#include <string>

class IStoreVisitor;

class IStoreItem {
public:
    virtual ~IStoreItem() = default;
    virtual double accept(IStoreVisitor* visitor) = 0;
};

class Book : public IStoreItem {
    std::string isbn;
    double price;
    double tax;
public:
    Book(const std::string& isbn, double price, double tax)
        : isbn(isbn), price(price), tax(tax) {}

    std::string getIsbn() const { return isbn; }
    double getPrice() const { return price; }
    double getTax() const { return tax; }

    double accept(IStoreVisitor* visitor) override;
};

class Coffee : public IStoreItem {
    std::string brand;
    double price;
    double tax;
    bool discount;
public:
    Coffee(const std::string& brand, double price, double tax, bool discount)
        : brand(brand), price(price), tax(tax), discount(discount) {}

    std::string getBrand() const { return brand; }
    double getPrice() const { return price; }
    double getTax() const { return tax; }
    bool isDiscount() const { return discount; }

    double accept(IStoreVisitor* visitor) override;
};

class Tea : public IStoreItem {
    std::string brand;
    double price;
    double tax;
    bool discount;
public:
    Tea(const std::string& brand, double price, double tax, bool discount)
        : brand(brand), price(price), tax(tax), discount(discount) {}

    std::string getBrand() const { return brand; }
    double getPrice() const { return price; }
    double getTax() const { return tax; }
    bool isDiscount() const { return discount; }

    double accept(IStoreVisitor* visitor) override;
};

class IStoreVisitor {
public:
    virtual ~IStoreVisitor() = default;
    virtual double visit(Book& book) = 0;
    virtual double visit(Tea& tea) = 0;
    virtual double visit(Coffee& coffee) = 0;
};

class StoreVisitor : public IStoreVisitor {
public:
    double visit(Book& book) override {
        return book.getPrice() + book.getTax() * book.getPrice();
    }

    double visit(Tea& tea) override {
        double cost = tea.getPrice() + tea.getTax() * tea.getPrice();
        if (tea.isDiscount())
            cost -= cost * 0.1;
        return cost;
    }

    double visit(Coffee& coffee) override {
        double cost = coffee.getPrice() + coffee.getTax() * coffee.getPrice();
        if (coffee.isDiscount())
            cost -= cost * 0.15;
        return cost;
    }
};

double Book::accept(IStoreVisitor* visitor) {
    return visitor->visit(*this);
}

double Coffee::accept(IStoreVisitor* visitor) {
    return visitor->visit(*this);
}

double Tea::accept(IStoreVisitor* visitor) {
    return visitor->visit(*this);
}

int main() {
    std::vector<IStoreItem*> items;
    items.push_back(new Book("1234", 20.01, 0.08));
    items.push_back(new Book("5678", 345, 0.08));
    items.push_back(new Coffee("Espresso", 300, 0.092, false));
    items.push_back(new Coffee("Starbucks", 400, 0.099, true));
    items.push_back(new Tea("Curtis", 50, 0.003, true));

    IStoreVisitor* visitor = new StoreVisitor();
    double totalCost = 0;
    for (auto item : items) {
        totalCost += item->accept(visitor);
    }

    std::cout << "Total cost = " << totalCost << std::endl;
    
    for (auto item : items) {
        delete item;
    }
    delete visitor;

    return 0;
}
