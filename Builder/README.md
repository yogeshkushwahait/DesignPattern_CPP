## Builder Design Pattern
### Intent
* Separate the construction of a complex object from its representation so that the same construction process can create different representations.
* Parse a complex representation, create one of several targets.
### Problem
An application needs to create the elements of a complex aggregate. The specification for the aggregate exists on secondary storage and one of many representations needs to be built in primary storage.
### Check list
* Decide if a common input and many possible representations (or outputs) is the problem at hand.
* Encapsulate the parsing of the common input in a Reader class.
* Design a standard protocol for creating all possible output representations. Capture the steps of this protocol in a Builder interface.
* Define a Builder derived class for each target representation.
* The client creates a Reader object and a Builder object, and registers the latter with the former.
* The client asks the Reader to "construct".
* The client asks the Builder to return the result.

  
  ![image](./Builder.png)
