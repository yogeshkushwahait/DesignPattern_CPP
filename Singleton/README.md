## Singleton Design Pattern 
### Intent:
* Ensure a class has only one instance, and provide a global point of access to it.
* Encapsulated "just-in-time initialization" or "initialization on first use".
### Problem:
Application needs one, and only one, instance of an object. Additionally, lazy initialization and global access are necessary.
### Check list:
* Define all constructors to be protected or private.
* Define a public static accessor function in the class which return instance of class
* Do "lazy initialization" (creation on first use) in the accessor function.
* Clients may only use the accessor function to manipulate the Singleton.
