#include<iostream>
using namespace std;


// normal inheritance implementation  .. why it fails and not good for scalability
class Vehicle {
    public:
    virtual void drive(){
        cout<<"Driving Normal"<<endl;
    }

};

class Sport: public Vehicle{
    public:

    void drive() override{
        cout<<"Driving Special Ability"<<endl;
    }
};

class Offroad: public Vehicle{
    public:

    void drive() override{
        cout<<"Driving Special Ability"<<endl;  // duplicate code ..scalabiltiy issue .. no code reuse
    }

};

class Passenger: public Vehicle{
    // default
}

// ----- Strategy Interface -----
class DriveStrategy {
public:
    virtual void drive() = 0;
    virtual ~DriveStrategy() = default;
};

// ----- Concrete Strategies -----
class NormalDrive : public DriveStrategy {
public:
    void drive() override {
        cout << "Driving Normal" << endl;
    }
};

class SpecialDrive : public DriveStrategy {
public:
    void drive() override {
        cout << "Driving Special Ability" << endl;
    }
};

// ----- Context (Vehicle) -----
class Vehicle {
protected:
    unique_ptr<DriveStrategy> strategy; // composition (HAS-A)
public:
    Vehicle(unique_ptr<DriveStrategy> s) : strategy(move(s)) {}
    void drive() {
        strategy->drive(); // delegate behavior to strategy
    }
};

// ----- Different Vehicles -----
class Sport : public Vehicle {
public:
    Sport() : Vehicle(make_unique<SpecialDrive>()) {}
};

class Offroad : public Vehicle {
public:
    Offroad() : Vehicle(make_unique<SpecialDrive>()) {}
};

class Passenger : public Vehicle {
public:
    Passenger() : Vehicle(make_unique<NormalDrive>()) {}
};

int main() {
    Sport s;
    Offroad o;
    Passenger p;

    s.drive(); // Driving Special Ability
    o.drive(); // Driving Special Ability
    p.drive(); // Driving Normal

    return 0;
}