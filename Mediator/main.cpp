#include <iostream>
#include <queue>
#include <string>
#include <mutex>
#include <thread>
/*
## Mediator Design Pattern
### Intent
* Define an object that encapsulates how a set of objects interact. Mediator promotes loose coupling by keeping objects from referring to each other explicitly, and it lets you vary their interaction independently.
* Design an intermediary to decouple many peers.
* Promote the many-to-many relationships between interacting peers to "full object status".
### Problem
We want to design reusable components, but dependencies between the potentially reusable pieces demonstrates the "spaghetti code" phenomenon (trying to scoop a single serving results in an "all or nothing clump").
### Check list
* Identify a collection of interacting objects that would benefit from mutual decoupling.
* Encapsulate those interactions in the abstraction of a new class.
* Create an instance of that new class and rework all "peer" objects to interact with the Mediator only.
* Balance the principle of decoupling with the principle of distributing responsibility evenly.
* Be careful not to create a "controller" or "god" object.
*/
using namespace std;
class Mediator
{
public:
    Mediator()=delete;
    ~Mediator()=delete;
    Mediator(const Mediator&) = delete;
    Mediator(const Mediator &&) = delete;
    Mediator& operator=(const Mediator&) = delete;
    Mediator& operator=(const Mediator&&) = delete;
    //static functions
    static void store(const std::string& message)
    {
        const std::lock_guard<std::mutex> lock(m_mutex);
        m_MessageQueue.push(message);
    }
    static std::string retrive()
    {
       const std::lock_guard<std::mutex> lock(m_mutex);
       std::string Message = m_MessageQueue.front();
       m_MessageQueue.pop();
       return Message;
    }
    static bool isEmpty()
    {
       return m_MessageQueue.empty();
    }
public:
    static std::mutex m_mutex;
    static std::queue<std::string> m_MessageQueue;
};
std::queue<std::string> Mediator::m_MessageQueue{};
std::mutex Mediator::m_mutex{};
static int MessageCount=0;
std::mutex out_mutex;
std::mutex in_mutex;
class Producer
{

public:
    void operator()() const
    {
       const std::lock_guard<std::mutex> lock(in_mutex);
       MessageCount++;
       std::string Message = "Producer Message No:" + std::to_string(MessageCount);
       Mediator::store(Message);
    }
};
class Consumer
{
public:
    void operator()() const
    {
        const std::lock_guard<std::mutex> lock(out_mutex);
        if(!Mediator::isEmpty())
        {
         std::cout<<"Consumer Consume Message From: "<<Mediator::retrive()<<std::endl;
        }
        else
        {
          std::cout<<"No Message For Consume"<<std::endl;
        }
    }
};

int main()
{
    for(int i=0;i<10;i++)
    {
     std::thread ProducerObj{Producer()};
     ProducerObj.join();
     std::thread ConsumerObj{Consumer()};
     ConsumerObj.join();
    }
     std::thread ConsumerObj{Consumer()};
     ConsumerObj.join();
    return 0;
}
