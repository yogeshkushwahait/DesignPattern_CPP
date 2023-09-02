#include <iostream>
#include <memory>
#include <map>
/*
## Prototype Design Pattern
### Intent
* Specify the kinds of objects to create using a prototypical instance, and create new objects by copying this prototype.
* Co-opt one instance of a class for use as a breeder of all future instances.
* The new operator considered harmful.
### Problem
Application "hard wires" the class of object to create in each "new" expression.
### Check list
* Add a clone() method to the existing "product" hierarchy.
* Design a "registry" that maintains a cache of prototypical objects. The registry could be encapsulated in a new Factory class, or in the base class of the "product" hierarchy.
* Design a factory method that: may (or may not) accept arguments, finds the correct prototype object, calls clone() on that object, and returns the result.
* The client replaces all references to the new operator with calls to the factory method.
*/
using namespace std;
class Shape
{
public:
  virtual void draw()=0;
  virtual std::shared_ptr<Shape> clone() = 0;
  virtual ~Shape() = default;
};
class Rectangle:public Shape
{
 public:
    std::shared_ptr<Shape> clone() override{std::cout<<"Clone Rectangle"<<std::endl;return std::make_shared<Rectangle>(*this);}
    void draw() override {std::cout<<"Draw Rectangle"<<std::endl;}
};
class Circle:public Shape
{
 public:
    std::shared_ptr<Shape> clone() override{std::cout<<"Clone Circle"<<std::endl;return std::make_shared<Circle>(*this);}
    void draw() override {std::cout<<"Draw Circle"<<std::endl;}
};
class Triangle:public Shape
{
 public:
    std::shared_ptr<Shape> clone() override{std::cout<<"Clone Triangle"<<std::endl;return std::make_shared<Triangle>(*this);}
    void draw() override {std::cout<<"Draw Triangle"<<std::endl;}
};
class Polygon:public Shape
{
 public:
    std::shared_ptr<Shape> clone() override{std::cout<<"Clone Polygon"<<std::endl;return std::make_shared<Polygon>(*this);}
    void draw() override {std::cout<<"Draw Polygon"<<std::endl;}
};
enum class ShapeType
{
 ShapeType_Rectangle =0,
 ShapeType_Circle =1,
 ShapeType_Triangle=2,
 ShapeType_Polygon=3
}ShapetypeObj;
class ShapeCache
{

public:
     ShapeCache()=delete;
     ~ShapeCache()=delete;
     ShapeCache(const ShapeCache&)=delete;
     ShapeCache(ShapeCache&&)=delete;
     ShapeCache& operator=(const ShapeCache&)=delete;
     ShapeCache& operator=(ShapeCache&&)=delete;
     static void LoadCache()
     {
         m_ShapeMap[ShapeType::ShapeType_Rectangle] = make_shared<Rectangle>();
         m_ShapeMap[ShapeType::ShapeType_Circle]    = make_shared<Circle>();
         m_ShapeMap[ShapeType::ShapeType_Triangle]  = make_shared<Triangle>();
         m_ShapeMap[ShapeType::ShapeType_Polygon]  = make_shared<Polygon>();

     }
     static std::shared_ptr<Shape> getShape(ShapeType type){return m_ShapeMap[type]->clone();}
private:
    static std::map<ShapeType,std::shared_ptr<Shape>> m_ShapeMap;
};
std::map<ShapeType,std::shared_ptr<Shape>> ShapeCache::m_ShapeMap{};
int main()
{
    ShapeCache::LoadCache();
    std::shared_ptr<Shape> shape1 = ShapeCache::getShape(ShapeType::ShapeType_Rectangle);
    shape1->draw();
    std::shared_ptr<Shape> shape2 = ShapeCache::getShape(ShapeType::ShapeType_Circle);
    shape1->draw();
    std::shared_ptr<Shape> shape3 = ShapeCache::getShape(ShapeType::ShapeType_Triangle);
    shape1->draw();
    std::shared_ptr<Shape> shape4 = ShapeCache::getShape(ShapeType::ShapeType_Polygon);
    shape1->draw();
    return 0;
}
