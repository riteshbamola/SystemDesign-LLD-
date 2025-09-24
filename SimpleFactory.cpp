#include<iostream>
using namespace std;


class Burger {
    virtual void burgerType()=0;
};

class Basic: public Burger{
    public:
    void burgerType() override {
        cout<<"Basic"<<endl;
    }
};

class Premium: public Burger{
    public:
    void burgerType() override {
        cout<<"Premium"<<endl;
    }
};

class ExtraOrdinary: public Burger{
    public:
    void burgerType() override {
        cout<<"ExtraOrdinary"<<endl;
    }

};

class BurgerFactory{
    public:
    Burger* createBurger(string inp){

        if(inp =="Basic")
            return new Basic();
        if(inp=="Premium")
            return new Premium();
        if(inp=="Extra")
            return new ExtraOrdinary();
        return nullptr;
    }
};

int main(){

 int main() {
    BurgerFactory* obj = new BurgerFactory();
    Burger* burger = obj->createBurger("Basic");

    if(burger != nullptr) {
        burger->burgerType();
        delete burger;
    } else {
        cout << "Invalid burger type!" << endl;
    }

    delete obj;
    return 0;
}

}