#include <iostream>
#include <memory>
/*
## Template Method Design Pattern
### Intent
* Define the skeleton of an algorithm in an operation, deferring some steps to client subclasses. Template Method lets subclasses redefine certain steps of an algorithm without changing the algorithm's structure.
* Base class declares algorithm 'placeholders', and derived classes implement the placeholders.
### Problem
Two different components have significant similarities, but demonstrate no reuse of common interface or implementation. If a change common to both components becomes necessary, duplicate effort must be expended.
### Check list
* Examine the algorithm, and decide which steps are standard and which steps are peculiar to each of the current classes.
* Define a new abstract base class to host the "don't call us, we'll call you" framework.
* Move the shell of the algorithm (now called the "template method") and the definition of all standard steps to the new base class.
* Define a placeholder or "hook" method in the base class for each step that requires many different implementations. This method can host a default implementation – or – it can be defined as abstract (Java) or pure virtual (C++).
* Invoke the hook method(s) from the template method.
* Each of the existing classes declares an "is-a" relationship to the new abstract base class.
* Remove from the existing classes all the implementation details that have been moved to the base class.
* The only details that will remain in the existing classes will be the implementation details peculiar to each derived class.
*/
using namespace std;
class FrameWorkClass
{
public:
    void templateMethod()
    {
       std::cout<<"FrameWorkClass::templateMethod() Called"<<std::endl;
       stepOne();
       stepTwo();
       stepThree();
    }
    virtual void stepOne(){std::cout<<"FrameWorkClass::stepOne() Called"<<std::endl;}
    virtual void stepTwo(){std::cout<<"FrameWorkClass::stepTwo() Called"<<std::endl;}
    virtual void stepThree(){std::cout<<"FrameWorkClass::stepThree() Called"<<std::endl;}
    virtual ~FrameWorkClass()=default;
};
class ApplicationClassOne:public FrameWorkClass
{
public:
     void stepTwo() override{std::cout<<"ApplicationClassOne::stepTwo() Called"<<std::endl;}
};
class ApplicationClassTwo:public FrameWorkClass
{
public:
     void stepThree() override{std::cout<<"ApplicationClassTwo::stepThree() Called"<<std::endl;}
};
//#define ONE
int main()
{
#ifdef ONE
    std::unique_ptr<FrameWorkClass> pFrameWorkClass = std::make_unique<ApplicationClassOne>();
#else
   std::unique_ptr<FrameWorkClass> pFrameWorkClass = std::make_unique<ApplicationClassTwo>();
#endif
    pFrameWorkClass->templateMethod();
    return 0;
}
