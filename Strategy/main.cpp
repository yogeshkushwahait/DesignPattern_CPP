#include <iostream>
#include <memory>
/*
## Strategy Design Pattern
### Intent
* Define a family of algorithms, encapsulate each one, and make them interchangeable. Strategy lets the algorithm vary independently from the clients that use it.
* Capture the abstraction in an interface, bury implementation details in derived classes.
### Problem
One of the dominant strategies of object-oriented design is the "open-closed principle".
### Check list
* Identify an algorithm (i.e. a behavior) that the client would prefer to access through a "flex point".
* Specify the signature for that algorithm in an interface.
* Bury the alternative implementation details in derived classes.
* Clients of the algorithm couple themselves to the interface.
*/
using namespace std;
class Strategy
{
public:
    virtual void algorithm()=0;
    virtual ~Strategy()=default;
};
class Context
{
public:
    Context(std::shared_ptr<Strategy> pStrategy):m_Strategy{pStrategy}{}
    void execute(){m_Strategy->algorithm();}
private:
   std::shared_ptr<Strategy> m_Strategy;
};
class ImplemetationOne:public Strategy
{
public:
    void algorithm() override{std::cout<<"ImplemetationOne::algorithm() Called"<<std::endl;}
};
class ImplemetationTwo:public Strategy
{
public:
    void algorithm() override{std::cout<<"ImplemetationTwo::algorithm() Called"<<std::endl;}
};
#define ONE
int main()
{
#ifdef ONE
    std::shared_ptr<Strategy> pStrategy = std::make_shared<ImplemetationOne>();
#else
    std::shared_ptr<Strategy> pStrategy = std::make_shared<ImplemetationTwo>();
#endif
    std::unique_ptr<Context> pContext = std::make_unique<Context>(pStrategy);
    pContext->execute();
    return 0;
}
