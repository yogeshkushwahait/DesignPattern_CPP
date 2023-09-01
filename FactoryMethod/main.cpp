#include <iostream>
#include <memory>
#include <vector>
/*
============================================================
            Factory Method Design Pattern
============================================================
Intent:
1.Define an interface for creating an object, but let subclasses decide which class to instantiate.
  Factory Method lets a class defer instantiation to subclasses.
2.Defining a "virtual" constructor.
3.The new operator considered harmful.
Problem:
A framework needs to standardize the architectural model for a range of applications,
but allow for individual applications to define their own domain objects and provide for
their instantiation.
Check list:
1.If you have an inheritance hierarchy that exercises polymorphism,consider adding
   a polymorphic creation capability by defining a static factory method in the base class.
2.Design the arguments to the factory method. What qualities or characteristics are necessary
   and sufficient to identify the correct derived class to instantiate?
3.Consider designing an internal "object pool" that will allow objects to be reused instead
  of created from scratch.
4.Consider making all constructors private or protected.
*/
using namespace std;

class Shape
{
public:
  virtual void draw()=0;
  virtual ~Shape() = default;
};
class Rectangle:public Shape
{
 public:
    Rectangle(){std::cout<<"Create Rectangle"<<std::endl;}
    ~Rectangle(){std::cout<<"Destroy Rectangle"<<std::endl;}
    void draw() override {std::cout<<"Draw Rectangle"<<std::endl;}
};
class Circle:public Shape
{
 public:
    Circle(){std::cout<<"Create Circle"<<std::endl;}
    ~Circle(){std::cout<<"Destroy Circle"<<std::endl;}
    void draw() override {std::cout<<"Draw Circle"<<std::endl;}
};
class Triangle:public Shape
{
 public:
    Triangle(){std::cout<<"Create Triangle"<<std::endl;}
    ~Triangle(){std::cout<<"Destroy Triangle"<<std::endl;}
    void draw() override {std::cout<<"Draw Triangle"<<std::endl;}
};
class Polygon:public Shape
{
 public:
    Polygon(){std::cout<<"Create Polygon"<<std::endl;}
    ~Polygon(){std::cout<<"Destroy Polygon"<<std::endl;}
    void draw() override {std::cout<<"Draw Polygon"<<std::endl;}
};
class ShapeFactory
{
public:
    Shape* CreateRectangle(){return new Rectangle;}
    Shape* CreateCircle(){return new Circle;}
    Shape* CreateTriangle(){return new Triangle;}
    Shape* CreatePolygon(){return new Polygon;}
};
int main()
{

    std::vector<Shape*> ListShape;
    ShapeFactory shapefactory ;
    ListShape.push_back(shapefactory.CreateCircle());
    ListShape.push_back(shapefactory.CreateRectangle());
    ListShape.push_back(shapefactory.CreateTriangle());
    ListShape.push_back(shapefactory.CreatePolygon());
    for(auto& shape:ListShape)
    {
        shape->draw();
    }
    for(auto& shape:ListShape)
    {
       delete shape;
    }
    return 0;
}
