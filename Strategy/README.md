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

![image](./Strategy.png)
