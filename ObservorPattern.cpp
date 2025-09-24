#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Observer Interface
class Observer {
public:
    virtual void update() = 0;  
    virtual ~Observer() = default;
};

// Subject (Observable)
class Subject {
private:
    vector<Observer*> observers;
    int state{};

    void notify() {
        for (auto obs : observers) {
            obs->update();  
        }
    }

public:
    void add(Observer* obj) {
        observers.push_back(obj);
    }

    void detach(Observer* obj) {
        observers.erase(remove(observers.begin(), observers.end(), obj), observers.end());
    }

    void setState(int newState) {
        state = newState;
        notify();
    }

    int getData() const {
        return state;
    }
};

// Concrete Observer
class Display : public Observer {
private:
    string objname;
    Subject* observable;

public:
    Display(string name, Subject* obj)
        : objname(name), observable(obj) {}

    void update() override {
        cout << "Display [" << objname 
             << "] sees new state: " << observable->getData() << "\n";
    }
};

// Demo
int main() {
    Subject subject;

    Display d1("D1", &subject);
    Display d2("D2", &subject);

    subject.add(&d1);
    subject.add(&d2);

    subject.setState(10); // Notifies D1 & D2
    subject.detach(&d1);
    subject.setState(20); // Notifies only D2

    return 0;
}
