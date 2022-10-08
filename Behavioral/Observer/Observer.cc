#include <iostream>
#include <list>
using namespace std;
class Observer {
   public:
    virtual void Update() = 0;
};

class Subject {
   public:
    virtual void Attach(Observer* observer) = 0;
    virtual void Detach(Observer* observer) = 0;
    virtual void Notify() = 0;
};

class ConcreteSubject : public Subject {
   public:
    void Attach(Observer* observer) override { observers_.push_back(observer); }
    void Detach(Observer* observer) override { observers_.remove(observer); }
    void Notify() override {
        for (auto& observer : observers_) {
            observer->Update();
        }
    }

   private:
    list<Observer*> observers_;
};

class ConcreteObserver1 : public Observer {
   public:
    ConcreteObserver1(ConcreteSubject* subject) : subject_(subject) {}
    void Update() override { cout << "ConcreteObserver1::Update()" << endl; }

   private:
    ConcreteSubject* subject_;
};

class ConcreteObserver2 : public Observer {
   public:
    ConcreteObserver2(ConcreteSubject* subject) : subject_(subject) {}
    void Update() override { cout << "ConcreteObserver2::Update()" << endl; }

   private:
    ConcreteSubject* subject_;
};

// test
int main() {
    ConcreteSubject* subject = new ConcreteSubject();
    ConcreteObserver1* observer1 = new ConcreteObserver1(subject);
    ConcreteObserver2* observer2 = new ConcreteObserver2(subject);
    subject->Attach(observer1);
    subject->Attach(observer2);
    subject->Notify();
    subject->Detach(observer1);
    subject->Notify();
    delete subject;
    delete observer1;
    delete observer2;
    return 0;
}