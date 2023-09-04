#include <iostream>
#include <memory>
#include <vector>
/*
## Memento Design Pattern
### Intent
* Without violating encapsulation, capture and externalize an object's internal state so that the object can be returned to this state later.
* A magic cookie that encapsulates a "check point" capability.
* Promote undo or rollback to full object status.
### Problem
Need to restore an object back to its previous state (e.g. "undo" or "rollback" operations).
### Check list
* Identify the roles of “caretaker” and “originator”.
* Create a Memento class and declare the originator a friend.
* Caretaker knows when to "check point" the originator.
* Originator creates a Memento and copies its state to that Memento.
* Caretaker holds on to (but cannot peek into) the Memento.
* Caretaker knows when to "roll back" the originator.
* Originator reinstates itself using the saved state in the Memento.
*/
using namespace std;
class Memento
{
public:
    Memento(const std::string& state):m_state{state} {}
    std::string getState() const {return m_state;}
private:
        std::string m_state;
};

class Originator
{
public:
    void setState(const std::string& state)
    {
        std::cout<<"Originator: Setting state to " << state<<std::endl;
        m_state = state;
    }

    Memento* save()
    {
        std::cout<<"Originator: Saving to Memento."<<std::endl;
        return new Memento(m_state);
    }
    void restore(const Memento* m)
    {
        m_state = m->getState();
        std::cout<<"Originator: State after restoring from Memento: " << m_state<<std::endl;
    }
private:
    std::string m_state;
};

class Caretaker
{
public:
    void addMemento(Memento* m) {mementos.push_back(m);}
    Memento* getMemento() {return mementos[1];}
private:
    std::vector<Memento*> mementos;
};


int main()
{
  std::shared_ptr<Caretaker> caretaker   = std::make_shared<Caretaker>();
  std::shared_ptr<Originator> originator = std::make_shared<Originator>();
  originator->setState("State1");
  originator->setState("State2");
  caretaker->addMemento( originator->save() );
  originator->setState("State3");
  caretaker->addMemento( originator->save() );
  originator->setState("State4");
  originator->restore( caretaker->getMemento() );
  return 0;
}
