#include <iostream>
using namespace std;

class Burger {
    virtual void burgerType() = 0;
};

// Regular Burgers
class Basic : public Burger {
public:
    void burgerType() override { cout << "Basic" << endl; }
};

class Premium : public Burger {
public:
    void burgerType() override { cout << "Premium" << endl; }
};

class ExtraOrdinary : public Burger {
public:
    void burgerType() override { cout << "ExtraOrdinary" << endl; }
};

// Wheat Burgers
class BasicWheat : public Burger {
public:
    void burgerType() override { cout << "Basic Wheat" << endl; }
};

class PremiumWheat : public Burger {
public:
    void burgerType() override { cout << "Premium Wheat" << endl; }
};

class ExtraOrdinaryWheat : public Burger {
public:
    void burgerType() override { cout << "ExtraOrdinary Wheat" << endl; }
};

// Abstract Factory
class BurgerFactory {
public:
    virtual Burger* createBurger(string inp) = 0;
};

// Concrete Factories
class SinghBurger : public BurgerFactory {
public:
    Burger* createBurger(string inp) override {
        if (inp == "Basic") return new BasicWheat();
        if (inp == "Premium") return new PremiumWheat();
        if (inp == "Extra") return new ExtraOrdinaryWheat();
        return nullptr;
    }
};

class BurgerKing : public BurgerFactory {
public:
    Burger* createBurger(string inp) override {
        if (inp == "Basic") return new Basic();
        if (inp == "Premium") return new Premium();
        if (inp == "Extra") return new ExtraOrdinary();
        return nullptr;
    }
};

int main() {
    BurgerFactory* obj = new BurgerKing();
    Burger* burger = obj->createBurger("Basic");

    if (burger != nullptr) {
        burger->burgerType();
        delete burger;
    } else {
        cout << "Invalid burger type!" << endl;
    }

    delete obj;
    return 0;
}
