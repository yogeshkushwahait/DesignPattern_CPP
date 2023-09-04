#include <iostream>
#include <memory>
#include <vector>
/*
## Observer Design Pattern
### Intent
* Define a one-to-many dependency between objects so that when one object changes state, all its dependents are notified and updated automatically.
* Encapsulate the core (or common or engine) components in a Subject abstraction, and the variable (or optional or user interface) components in an Observer hierarchy.
* The "View" part of Model-View-Controller.
### Problem
A large monolithic design does not scale well as new graphing or monitoring requirements are levied.
### Check list
* Differentiate between the core (or independent) functionality and the optional (or dependent) functionality.
* Model the independent functionality with a "subject" abstraction.
* Model the dependent functionality with an "observer" hierarchy.
* The Subject is coupled only to the Observer base class.
* The client configures the number and type of Observers.
* Observers register themselves with the Subject.
* The Subject broadcasts events to all registered Observers.
* The Subject may "push" information at the Observers, or, the Observers may "pull" the information they need from the Subject.
*/
using namespace std;
class Observer
{
public:
    virtual void update(const std::string& state)=0;
    virtual ~Observer()=default;
};
class Subject
{
public:
    void attach(Observer* pObserver){m_ObserverList.push_back(pObserver);}
    void setState(const std::string& astate)
    {
        m_state=astate;
        std::cout<<"for Subject model state is changed to "<<m_state<<std::endl;
        update();
    }
    std::string getState() const {return m_state;}
    void update()
    {
        for(auto Observer_obj:m_ObserverList)
        {
            Observer_obj->update(m_state);
        }

    }
private:
    std::string  m_state;
    vector<Observer*> m_ObserverList;
};

class ViewOne:public Observer
{
public:
    ViewOne(const std::shared_ptr<Subject>& sub){sub->attach(this);}
    void update(const std::string& state) override {std::cout<<"  for ViewOne model state is changed to "<<state<<std::endl;}
};
class ViewTwo:public Observer
{
public:
    ViewTwo(const std::shared_ptr<Subject>& sub){sub->attach(this);}
    void update(const std::string& state)override {std::cout<<"  for ViewTwo model state is changed to "<<state<<std::endl;}
};
int main()
{
    std::shared_ptr<Subject>  Subject_obj   = std::make_shared<Subject>();
    std::shared_ptr<Observer> Observer_obj1 = std::make_shared<ViewOne>(Subject_obj);
    std::shared_ptr<Observer> Observer_obj2 = std::make_shared<ViewTwo>(Subject_obj);
    Subject_obj->setState("New");
    Subject_obj->setState("Runnable");
    Subject_obj->setState("Running");
    Subject_obj->setState("Block");
    return 0;
}
