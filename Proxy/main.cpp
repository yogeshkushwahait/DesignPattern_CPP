#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
/*
## Proxy Design Pattern
### Intent
* Provide a surrogate or placeholder for another object to control access to it.
* Use an extra level of indirection to support distributed, controlled, or intelligent access.
* Add a wrapper and delegation to protect the real component from undue complexity.
### Problem
You need to support resource-hungry objects, and you do not want to instantiate such objects unless and until they are actually requested by the client.
### Check list
* Identify the leverage or "aspect" that is best implemented as a wrapper or surrogate.
* Define an interface that will make the proxy and the original component interchangeable.
* Consider defining a Factory that can encapsulate the decision of whether a proxy or original object is desirable.
* The wrapper class holds a pointer to the real class and implements the interface.
* The pointer may be initialized at construction, or on first use.
* Each wrapper method contributes its leverage, and delegates to the wrappee object.
*/
using namespace std;
class AbstractItemModel
{
public:
    virtual void appendItem(const std::string& Item)=0;
    virtual ~AbstractItemModel() =default;
    virtual void printItem()=0;
    virtual std::vector<std::string> fetchItemList()=0;
};
class StandardItemModel:public AbstractItemModel
{
public:
    void appendItem(const std::string& Item) override
    {
       m_ItemList.push_back(Item);
    }
    std::vector<std::string> fetchItemList()override {return m_ItemList;}
    void printItem() override
    {
        for(auto Item:m_ItemList)
        {
            cout<<Item<<std::endl;
        }
    }
 private:
     std::vector<std::string> m_ItemList;

};
class AbstractProxyModel
{
public:
    AbstractProxyModel(const std::shared_ptr<AbstractItemModel> & model):m_BaseModel{model}{}
    virtual void printItem()=0;
    virtual ~AbstractProxyModel()=default;
protected:
    std::shared_ptr<AbstractItemModel> m_BaseModel;
};
class SortedProxyModel:public AbstractProxyModel
{
public:
    SortedProxyModel(const std::shared_ptr<AbstractItemModel> & model):AbstractProxyModel(model){}
    void printItem() override
    {
        std::cout<<"==============sorted Items==========="<<std::endl;
        std::vector<std::string> ItemList = m_BaseModel->fetchItemList();
        std::sort(ItemList.begin(),ItemList.end());
        for(auto Item:ItemList)
        {
            std::cout<<Item<<std::endl;
        }
    }
};
int main()
{
    std::shared_ptr<AbstractItemModel> ItemModel = std::make_shared<StandardItemModel>();
    ItemModel->appendItem("Mango");
    ItemModel->appendItem("Pineapple");
    ItemModel->appendItem("Apple");
    ItemModel->appendItem("Orange");
    ItemModel->appendItem("Banana");
    ItemModel->printItem();
    std::shared_ptr<AbstractProxyModel> ProxyModel = std::make_shared<SortedProxyModel>(ItemModel);
    ProxyModel->printItem();
    return 0;
}
