#include<iostream>
using namespace std;

//abstract class
class BasePizza{     
    public:
    virtual int cost()=0;
};


//concrete classes
class Marghreta :public BasePizza{
    public:
    int cost() override{
        return 100;
    }
};

class FarmHouse : public BasePizza{
    public:
    int cost() override{
        return 200;
    }
};

class VegDelight : public BasePizza{
    public:
    int cost()override{
        return 150;
    }
};


//Toppings abstract class

class DecoratePizza : public BasePizza{   
};

class ExtraCheese : public DecoratePizza{
    BasePizza *pizza;
    public:
    ExtraCheese(BasePizza* obj){
        this->pizza= obj;
    }

    int cost()override{
        return this->pizza->cost()+ 20;
    }

};
class ExtraMushroom : public DecoratePizza{
    BasePizza *pizza;
    public:
    ExtraMushroom(BasePizza *obj){
        this->pizza= obj;
    }

    int cost()override{
        return this->pizza->cost()+ 15;
    }

};

int main(){

    VegDelight * pizza= new VegDelight();
    ExtraMushroom * p = new ExtraMushroom(pizza);  // VegDelight + Mushrrom
    ExtraCheese *c= new ExtraCheese(p); // VegDelight + Mushrrom + Cheese
    cout<<c->cost();
}