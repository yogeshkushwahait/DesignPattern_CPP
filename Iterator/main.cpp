#include <iostream>
#include <memory>
#include <vector>
/*
## Iterator Design Pattern
### Intent
* Provide a way to access the elements of an aggregate object sequentially without exposing its underlying representation.
* The C++ and Java standard library abstraction that makes it possible to decouple collection classes and algorithms.
* Promote to "full object status" the traversal of a collection.
* Polymorphic traversal
### Problem
Need to "abstract" the traversal of wildly different data structures so that algorithms can be defined that are capable of interfacing with each transparently.
### Check list
* Add a create_iterator() method to the "collection" class, and grant the "iterator" class privileged access.
* Design an "iterator" class that can encapsulate traversal of the "collection" class.
* Clients ask the collection object to create an iterator object.
* Clients use the first(), is_done(), next(), and current_item() protocol to access the elements of the collection class.
*/
using namespace std;
using DataType = std::string;
const int arrsize = 4;

class NameRepository
{
public:
class Iterator
{
public:
   bool hasNext()
   {
      return (index < arrsize);
   };
   DataType next()
   {
      if(hasNext())
      {
         return names[index++];
      }
      return DataType{};
   };
private:
    int index{0};
};
   std::shared_ptr<Iterator> getIterator()
   {
      return std::make_shared<Iterator>();
   }
private:
    friend class Iterator;
    static std::string names[arrsize];
};
 std::string NameRepository::names[arrsize]={"Robert" , "John" ,"Julie" , "Lora"};


int main()
{
    std::shared_ptr<NameRepository> nameRepo = std::make_shared<NameRepository>();
    std::shared_ptr<NameRepository::Iterator> nameRepoItr = nameRepo->getIterator();
    while(nameRepoItr->hasNext())
    {
      std::cout<<nameRepoItr->next()<<std::endl;
    }
    return 0;
}
