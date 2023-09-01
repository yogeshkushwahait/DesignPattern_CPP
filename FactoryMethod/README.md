## Factory Method Design Pattern

### Intent:
* Define an interface for creating an object, but let subclasses decide which class to instantiate.
  Factory Method lets a class defer instantiation to subclasses.
* Defining a "virtual" constructor.
* The new operator considered harmful.
### Problem:
A framework needs to standardize the architectural model for a range of applications,
but allow for individual applications to define their own domain objects and provide for
their instantiation.
### Check list:
* If you have an inheritance hierarchy that exercises polymorphism,consider adding
   a polymorphic creation capability by defining a static factory method in the base class.
* Design the arguments to the factory method. What qualities or characteristics are necessary
   and sufficient to identify the correct derived class to instantiate?
* Consider designing an internal "object pool" that will allow objects to be reused instead
  of created from scratch.
* Consider making all constructors private or protected.
