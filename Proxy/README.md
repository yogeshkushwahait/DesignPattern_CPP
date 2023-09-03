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

  ![image](./Proxy.png)
