#include <iostream>
#include <vector>
using namespace std;

// ---------------------
// ❌ LSP VIOLATION EXAMPLE
// ---------------------

class Vehicle {
public:
    virtual int getNoofTyres() { return 4; }
    virtual const bool* hasEngine() { 
        static const bool value = true;
        return &value;
    }
    virtual ~Vehicle() {}
};

class Car : public Vehicle {
    // uses default implementation
};

class MotorCycle : public Vehicle {
public:
    int getNoofTyres() override {
        return 2;
    }
};

class Bicycle : public Vehicle {
public:
    const bool* hasEngine() override {
        return nullptr; //  LSP Violation: Returning NULL
    }
};

int main() {
    vector<Vehicle*> vt;
    vt.push_back(new MotorCycle());
    vt.push_back(new Car());
    vt.push_back(new Bicycle());

    // LSP Violation Demonstration: This will crash at runtime
    for (auto v : vt) {
        cout << "Tyres: " << v->getNoofTyres() 
             << ", Engine: " << (*v->hasEngine() ? "Yes" : "No") << endl;
    }

    for (auto v : vt) delete v;
    return 0;
}


//liskov implementation -- all the child classes should be 
// able to substitute each other without breaking the code


// ---------------------
// ✅ LSP-COMPLIANT DESIGN
// ---------------------
class Vehicle {
public:
    virtual int getNoofTyres() { return 4; }
    virtual ~Vehicle() {}
};

// Separate hierarchy for vehicles WITH engine
class EngineVehicle : public Vehicle {
public:
    virtual bool hasEngine() { return true; }
};

class Car : public EngineVehicle {
    // inherits hasEngine()
};

class MotorCycle : public EngineVehicle {
public:
    int getNoofTyres() override { return 2; }
};

class Bicycle : public Vehicle {
public:
    int getNoofTyres() override { return 2; }
};

int main() {
    cout << "\n---- LSP-Compliant Example ----" << endl;
    vector<Vehicle*> vt;
    vt.push_back(new MotorCycle());
    vt.push_back(new Car());
    vt.push_back(new Bicycle());

    for (auto v : vt) {
        cout << "Tyres: " << v->getNoofTyres();

        // ✅ We now need to check type safely (no null crash!)
        if (auto ev = dynamic_cast<EngineVehicle*>(v)) {
            cout << ", Engine: " << (ev->hasEngine() ? "Yes" : "No");
        }
        cout << endl;
    }

    for (auto v : vt) delete v;
    return 0;
}
