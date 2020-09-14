# CppOptimization
+ Static variables: The advantage of static data is that it can be initialized to desired values before the program
starts
+ ```C++
  float SomeFunction (int x) {
  static const float list[] = {1.1, 0.3, -2.0, 4.4, 2.5};
  return list[x];
  }
  ```
  
  The advantage of this is that the list does not need to be initialized every time the function is called. The static declaration helps the compiler decide that the          table can be reused from one call to the next. The const declaration helps the compiler see that the table never changes
  
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
