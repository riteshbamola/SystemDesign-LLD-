#include<iostream>
#include<mutex>
using namespace std;


class Singleton{
    private:
    static Singleton * instance;
    static mutex mx;

    Singleton(){
        cout<<"Object Created";
    }
    public:
    static Singleton * getInstance(){

        // if(instance==NULL)
        // {
        //     instance= new Singleton();         //------> Not thread safe <----------..
        // }

        // return instance;

        //Thread Safe

        if(instance==NULL){
            lock_guard<mutex> lock(mx);   // (multiple Threads can access at sameTime) it ensures one thread at a time will access this section 
            if(instance==NULL){    // to check again  wheather previous thread created object or not ..(Double Check)
                instance= new Singleton(); // obj creation
            }
            
        }
        return instance;
    }
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};
// Singleton * Singleton:: instance = new Singleton();   // Inefficient when we dont need any object; overhead because of memoy;
Singleton* Singleton::instance = nullptr;
mutex Singleton::mx;

int main() {
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();

    cout << "\nAddress s1: " << s1 << "\nAddress s2: " << s2 << "\n";
    return 0;
}