#include <iostream>
#include <memory>
/*
## Adapter Design Pattern
### Intent
* Convert the interface of a class into another interface clients expect. Adapter lets classes work together that couldn't otherwise because of incompatible interfaces.
* Wrap an existing class with a new interface.
* Impedance match an old component to a new system
### Problem
An "off the shelf" component offers compelling functionality that you would like to reuse, but its "view of the world" is not compatible with the philosophy and architecture of the system currently being developed.
### Check list
* Identify the players: the component(s) that want to be accommodated (i.e. the client), and the component that needs to adapt (i.e. the adaptee).
* Identify the interface that the client requires.
* Design a "wrapper" class that can "impedance match" the adaptee to the client.
* The adapter/wrapper class "has a" instance of the adaptee class.
* The adapter/wrapper class "maps" the client interface to the adaptee interface.
* The client uses (is coupled to) the new interface
*/
using namespace std;
typedef int Coordinate;
typedef int Dimension;
class LegacyRectangle
{
  public:
    LegacyRectangle(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2)
    {
        x1_ = x1;
        y1_ = y1;
        x2_ = x2;
        y2_ = y2;
        cout << "LegacyRectangle:  create.  (" << x1_ << "," << y1_ << ") => ("
          << x2_ << "," << y2_ << ")" << endl;
    }
    void oldDraw()
    {
        cout << "LegacyRectangle:  oldDraw.  (" << x1_ << "," << y1_ <<
          ") => (" << x2_ << "," << y2_ << ")" << endl;
    }
  private:
    Coordinate x1_;
    Coordinate y1_;
    Coordinate x2_;
    Coordinate y2_;
};
class Shape
{
public:
  virtual void draw()=0;
  virtual ~Shape() = default;
};
class Rectangle:public Shape
{
 public:
    Rectangle(Coordinate x, Coordinate y, Dimension w, Dimension h)
    {
      m_LegacyRectangle = std::make_unique<LegacyRectangle>(x, y, x + w, y + h);
    }
    void draw() override {std::cout<<"Draw Rectangle"<<std::endl;m_LegacyRectangle->oldDraw();}
 private:
    std::unique_ptr<LegacyRectangle> m_LegacyRectangle;
};

int main()
{
    Rectangle rect(20,10,30,50);
    rect.draw();
    return 0;
}
