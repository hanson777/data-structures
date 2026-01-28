This vector implementation aims for simplicity and performance and follows the Rule of Five, meaning the following constructors have been user-defined: 
- Destructor: `~Vector()`
- Copy Constructor: `Vector(const Vector &Other)`
- Copy Assignment Operator: `Vector& operator=(const Vector &other)`
- Move Constructor: `Vector(Vector &&Other)`
- Move Assignment Operator: `Vector &operator=(Vector &&other)`

For performance optimization, we use `operator new` and `operator delete` (C++'s version of `malloc/free`) instead of `new` and `delete` for raw memory management. 
