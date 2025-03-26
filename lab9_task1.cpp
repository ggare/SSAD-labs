#include <iostream>
#include <string>
#include <memory>

// Enemy class
class Enemy {
private:
    std::string name;
    int strength;

public:
    Enemy(const std::string& name, int strength) : name(name), strength(strength) {}

    void takeDamage(int damage) {
        strength -= damage;
        if (strength < 0) strength = 0;
    }

    std::string getName() const {
        return name;
    }

    void displayStrength() const {
        std::cout << name << " STRENGTH LEVEL IS: " << strength << std::endl;
    }
};

// AttackStrategy interface
class AttackStrategy {
public:
    virtual ~AttackStrategy() = default;
    virtual void attack(Enemy& enemy) const = 0;
    virtual std::string getAttackName() const = 0;
};

// Concrete attack strategies
class MageAttack : public AttackStrategy {
public:
    void attack(Enemy& enemy) const override {
        std::cout << "Mage attack!" << std::endl;
        enemy.takeDamage(10);
    }

    std::string getAttackName() const override {
        return "Mage";
    }
};

class RogueAttack : public AttackStrategy {
public:
    void attack(Enemy& enemy) const override {
        std::cout << "Rogue attack!" << std::endl;
        enemy.takeDamage(15);
    }

    std::string getAttackName() const override {
        return "Rogue";
    }
};

class WarriorAttack : public AttackStrategy {
public:
    void attack(Enemy& enemy) const override {
        std::cout << "Warrior attack!" << std::endl;
        enemy.takeDamage(25);
    }

    std::string getAttackName() const override {
        return "Warrior";
    }
};

// Character class
class Character {
private:
    std::string name;
    std::unique_ptr<AttackStrategy> attackStrategy;

public:
    Character(const std::string& name, std::unique_ptr<AttackStrategy> strategy)
        : name(name), attackStrategy(std::move(strategy)) {}

    void attack(Enemy& enemy) {
        std::cout << name << " (" << attackStrategy->getAttackName() << ") attacks!" << std::endl;
        attackStrategy->attack(enemy);
        enemy.displayStrength();
    }

    void setAttackStrategy(std::unique_ptr<AttackStrategy> newStrategy) {
        attackStrategy = std::move(newStrategy);
    }
};

int main() {
    // Create enemies
    Enemy blackKiller("BLACK KILLER", 100);
    Enemy brownBiter("BROWN BITER", 25);

    // Create characters with different attack strategies
    Character warrior("Warrior", std::make_unique<WarriorAttack>());
    Character mage("Mage", std::make_unique<MageAttack>());
    Character rogue("Rogue", std::make_unique<RogueAttack>());

    // Perform attacks
    warrior.attack(blackKiller);
    mage.attack(brownBiter);
    rogue.attack(blackKiller);

    // Switch strategy dynamically
    mage.setAttackStrategy(std::make_unique<WarriorAttack>());
    std::cout << "\nMage switches to warrior attack style!\n";
    mage.attack(brownBiter);

    return 0;
}
