#include <iostream>
#include <memory>
#include <map>
/*
## Chain of Responsibility
### Intent
* Avoid coupling the sender of a request to its receiver by giving more than one object a chance to handle the request. Chain the receiving objects and pass the request along the chain until an object handles it.
* Launch-and-leave requests with a single processing pipeline that contains many possible handlers.
* An object-oriented linked list with recursive traversal.
### Problem
There is a potentially variable number of "handler" or "processing element" or "node" objects, and a stream of requests that must be handled. Need to efficiently process the requests without hard-wiring handler relationships and precedence, or request-to-handler mappings.
### Check list
* The base class maintains a "next" pointer.
* Each derived class implements its contribution for handling the request.
* If the request needs to be "passed on", then the derived class "calls back" to the base class, which delegates to the "next" pointer.
* The client (or some third party) creates and links the chain (which may include a link from the last node to the root node).
* The client "launches and leaves" each request with the root of the chain.
* Recursive delegation produces the illusion of magic.
*/
using namespace std;
class Database
{
public:
    bool isValidUser(const std::string& userName)
    {
        auto itr = m_useDB.find(userName);
        bool result = (itr != m_useDB.end());
        return result;
    }
    bool isValidPassword(const std::string& userName,const std::string& password)
    {
        auto itr = m_useDB.find(userName);
        bool result = (itr->second == password);
        return result;
    }
    std::string whatsRole(const std::string& userName)
    {
        std::string RoleName = "Customer";
        if(userName == "Admin")
        {
          RoleName = "Employee";
        }
        return RoleName;
    }
private:
    std::map<std::string,std::string> m_useDB{{"Admin","@#$%K0H"},{"User1","@#$%K1p"},{"User2","@#$%UY1p"}};
};
class Handler
{
public:
     Handler(std::shared_ptr<Database> database):m_Database{database}{}
     virtual ~Handler() = default;
     virtual void handle(const std::string& userName,const std::string& password)=0;
     void setNextHandler(std::shared_ptr<Handler>& handler){m_NextHandler=handler;}
protected:
     bool handleNext(const std::string& userName,const std::string& password)
     {
         bool result = false;
         if(m_NextHandler != nullptr)
         {
            m_NextHandler->handle(userName,password);
            result = true;
         }
         return result;
     }
private:
    std::shared_ptr<Handler> m_NextHandler;
protected:
    std::shared_ptr<Database>    m_Database;
};

class UserExistHandler:public Handler
{
public:
   UserExistHandler(std::shared_ptr<Database> database):Handler(database){}
   void handle(const std::string& userName,const std::string& password)
   {
       if(m_Database->isValidUser(userName))
       {
         handleNext(userName,password);
       }
       else
       {
         std::cout<<"User Name does not Exist."<<std::endl;
       }
   }
};
class ValidPasswordHandler:public Handler
{
public:
   ValidPasswordHandler(std::shared_ptr<Database> database):Handler(database){}
   void handle(const std::string& userName,const std::string& password)
   {
       if(m_Database->isValidPassword(userName,password))
       {
         handleNext(userName,password);
       }
       else
       {
         std::cout<<"User Name and password does not match."<<std::endl;
       }
   }
};
class RoleCheckHandler:public Handler
{
public:
   RoleCheckHandler(std::shared_ptr<Database> database):Handler(database){}
   void handle(const std::string& userName,const std::string& password)
   {
      std::cout<<"Welcome "<<m_Database->whatsRole(userName)<<"!"<<std::endl;
   }
};
class AuthService
{
public:
    AuthService(std::shared_ptr<Handler>& handler):m_Handler{handler}{}
    void LogIn(const std::string& userName,const std::string& password)
    {
        m_Handler->handle(userName,password);
    }
private:
   std::shared_ptr<Handler> m_Handler;
};
int main()
{
    std::shared_ptr<Database> databse    = std::make_shared<Database>();
    std::shared_ptr<Handler> UEHandler   = std::make_shared<UserExistHandler>(databse);
    std::shared_ptr<Handler> VPHandler   = std::make_shared<ValidPasswordHandler>(databse);
    std::shared_ptr<Handler> RCHandler   = std::make_shared<RoleCheckHandler>(databse);
    UEHandler->setNextHandler(VPHandler);
    VPHandler->setNextHandler(RCHandler);

    std::shared_ptr<AuthService> authService = std::make_shared<AuthService>(UEHandler);
    authService->LogIn("Admin","@#$%K0H");
   authService->LogIn("value","@#$%K0H");
   authService->LogIn("User1","@#$%K0H");
   authService->LogIn("User2","@#$%UY1p");
    return 0;
}
