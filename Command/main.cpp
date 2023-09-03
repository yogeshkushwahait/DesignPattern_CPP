#include <iostream>
#include <memory>
#include <vector>
/*
## Command Design Pattern
### Intent
* Encapsulate a request as an object, thereby letting you parametrize clients with different requests, queue or log requests, and support undoable operations.
* Promote "invocation of a method on an object" to full object status
* An object-oriented callback
### Problem
Need to issue requests to objects without knowing anything about the operation being requested or the receiver of the request.
### Check list
* Define a Command interface with a method signature like execute().
* Create one or more derived classes that encapsulate some subset of the following: a "receiver" object, the method to invoke, the arguments to pass.
* Instantiate a Command object for each deferred execution request.
* Pass the Command object from the creator (aka sender) to the invoker (aka receiver).
* The invoker decides when to execute().
*/
using namespace std;
class Stock
{
public:
    void buy(){std::cout<<"Stock Buy Successfully!"<<std::endl;}
    void sell(){std::cout<<"Stock Sell Successfully!"<<std::endl;}
};
class Order
{
public:
   Order(std::shared_ptr<Stock>& aStock):m_Stock{aStock}{}
   virtual void execute() =0;
   virtual ~Order() =default;
protected:
    std::shared_ptr<Stock> m_Stock;
};
class BuyStock:public Order
{
public:
    BuyStock(std::shared_ptr<Stock>& aStock ):Order(aStock){}
    void execute() override{m_Stock->buy();}
};
class SellStock:public Order
{
public:
    SellStock(std::shared_ptr<Stock>& aStock ):Order(aStock){}
    void execute() override{m_Stock->sell();}
};
class Broker
{
public:
    void takeOrder(std::shared_ptr<Order>& aOrder){m_OrderList.push_back(aOrder);}
    void placeOrder()
    {
       for(auto order:m_OrderList)
       {
          order->execute();
       }
    }
private:
    vector<std::shared_ptr<Order>> m_OrderList;
};
int main()
{
    std::shared_ptr<Stock> pStock     = std::make_shared<Stock>();
    std::shared_ptr<Order> pBuyStock  = std::make_shared<BuyStock>(pStock);
    std::shared_ptr<Order> pSellStock = std::make_shared<SellStock>(pStock);
    std::shared_ptr<Broker> pBroker   = std::make_shared<Broker>();
    pBroker->takeOrder(pBuyStock);
    pBroker->takeOrder(pSellStock);
    pBroker->placeOrder();
    return 0;
}
