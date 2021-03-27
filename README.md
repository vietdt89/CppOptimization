# CppOptimization
+ Static variables: The advantage of static data is that it can be initialized to desired values before the program
starts
+ ```C++
  float SomeFunction (int x) {
  static const float list[] = {1.1, 0.3, -2.0, 4.4, 2.5};
  return list[x];
  }
  ```
  
  The advantage of this is that the list does not need to be initialized every time the function is called. The static declaration helps the compiler decide that the          table can be reused from one call to the next. 
  static means variable has to be init first time but not on subsequent calls, so function needs extra overhead to check if variable is called first time or not. So adding const helps compiler see the variable never changes
  
+ Volatile keyword: 
  ```C++
  volatile int seconds; // incremented every second by another thread
  void DelayFiveSeconds() {
  seconds = 0;
  while (seconds < 5) {
    }
  }
  ```
  In this example, the DelayFiveSeconds function will wait until seconds has been incremented to 5 by another thread. If seconds was not declared volatile then an  optimizing compiler would assume that seconds remains zero in the while loop because nothing inside the loop can change the value. The loop would be while (0 < 5) {}
which would be an infinite loop.
The effect of the keyword volatile is that it makes sure the variable is stored in memory rather than in a register and prevents all optimizations on the variable. This can be useful in test situations to avoid that some expression is optimized away

+ i++ and ++i: 
  Is the same in
  ```C++
  for (i=0; i<n; i++)
  for (i=0; i<n; ++i)
  ```
  a[++i] is more efficient than a[++i] because in the latter case, the calculation of the address of the array element has to wait for the new value of i which will delay the  availability of x for approximately two clock cycles. Obviously, the initial value of i must be adjusted if you change pre-increment to post-increment.
  There are also situations where pre-increment is more efficient than post-increment. For example, in the case a = ++b; the compiler will recognize that the values of a and b are the same after this statement so that it can use the same register for both, while the expression a = b++; will make the values of a and b different so that they cannot use the same register
  
+ It may be advantageous to put the operand that is most often true last in an && expression, or first in an || expression

+ A multidimensional array should be organized so that the last index changes fastest. This makes sure that the elements are accessed sequentially. The opposite order of the two loops would make the access non-sequential which makes the data caching less efficient.

+ Static function:
   - By declaring a function member as static, you make it independent of any particular object of the class.
   - A static member function can be called even if no objects of the class exist and the static functions are accessed using only the class name and the scope resolution operator ::.
   - A static member function can only access static data member, other static member functions and any other functions from outside the class.
   - Static member functions have a class scope and they do not have access to the this pointer of the class. You could use a static member function to determine whether some objects of the class have been created or not.
   - The preferred method for transferring composite objects to a function is by a const reference. A const reference makes sure that the original object is not modified
   - A static member function cannot access any non-static data members or non-static member functions. A static member function is faster than a non-static member function because it does not need the 'this' pointer
+ Stack is freed when function returns 
+ Global or static variables are stored in static part of memory
+ The static data area is usually divided into three parts: one for constants that are never modified by the program, one for initialized variables that may be modified by the program, and one for uninitialized variables that may be modified by the program

+ Global variable has external linkage. In other files, same name refers to same location in memory
Static global variables are private to the source file where they are defined and do not conflict with other variables in other source files which would have the same name.
Both global, as well as static variables, have static initialization, which means that if you don't assign them a value, they will get initialized to 0 (common variables) or NULL (pointers).
+ Static local variables: Variables declared as static inside a function are statically allocated, thereby keeping their memory cell throughout all program execution, while also having the same scope of visibility as automatic local variables. Hence whatever values the function puts into its static local variables during one call will remain the same whenever the function is called again
+ The advantage of static data is that it can be initialized to desired values before the program starts. The disadvantage is that the memory space is occupied throughout the whole program execution. This makes data caching less efficient because the memory space cannot be reused for another purpose
+ A copy constructor may be called whenever an object is copied by assignment, as afunction parameter, or as a function return value. The copy constructor can be a time consumer if it involves allocation of memory or other resources -> Use a reference or pointer to the object instead of copying it
   
+ A template class can be used for implementing a compile-time polymorphism, which is more efficient than the runtime polymorphism that is obtained with virtual member functions

+ The cost of thread:
   - The cost of start and stop thread. Do not put a task into a separate thread if it is short in duration compared with the time it takes to start and stop the thread
   - The cost of task switching. This cost is minimized if the number of threads with the same priority is no more than the number of CPU cores.
   - The cost of sync and communicating between threads. A shared variable must be declared volatile
   - No function or class using multiple threads shoud rely on static or globle variables

+ Using a union is not a safe programming practice, of course, because you will get no warning from the compiler if the uses of a and b overlap. You should use this method only
for big objects that take a lot of cache space. Putting simple variables into a union is not optimal because it prevents the use of register variables

+ The time it takes to call a virtual member function is a few clock cycles more than it takes to call a non-virtual member function, provided that the function call statement always calls the same version of the virtual function

+ Integer multiplication takes longer time than addition and subtraction (3 - 10 clock cycles, depending on the processor). Optimizing compilers will often replace integer multiplication by a constant with a combination of additions and shift operations

+ Integer division takes much longer time than addition, subtraction and multiplication (27 - 80 clock cycles for 32-bit integers, depending on the processor).
+ Integer division by a power of 2 can be done with a shift operation, which is much faster 
+ The following guidelines can be used for improving code that contains integer division:
   - Integer division by a constant is faster than division by a variable. Make sure the
value of the divisor is known at compile time.
   - Integer division by a constant is faster if the constant is a power of 2
   - Integer division by a constant is faster if the dividend is unsigned

+ Floating point division takes much longer time than addition, subtraction and multiplication
(20 - 45 clock cycles).
+ Floating point division by a constant should be done by multiplying with the reciprocal
+ Conversions from double <-> float take a lot of time
