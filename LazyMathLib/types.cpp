#include <iostream>
#include <algorithm>
#include <vector>
#include <conio.h>
#include "lazy_vector.h"


void log(const char* msg)
{
   static int numOperations = 0;

   std::cout << numOperations++ << " : " << msg << "\n";
}

int main()
{
   {
      log("LazyVector a{ 1.0, 2.0 };");
      LazyVector a{ 1.0, 2.0 };

      log("LazyVector b{ 3.0, 4.0, 5.0 };");
      LazyVector b{ 3.0, 4.0, 5.0 };

      log("LazyVector c{ 6.0 };");
      LazyVector c{ 6.0 };

      log("auto x1 = a + b;");
      auto x1 = a + b;

      log("auto x2 = x1 + c;");
      auto x2 = x1 + c;

      log("auto x3 = a + b + c;");
      auto x3 = a + b + c;

      log("auto y = static_cast<LazyVector>(x2);");
      auto y = static_cast<LazyVector>(x2);

      log("std::cout << y.toString();");
      std::cout << y.toString() << "\n";

      log("auto z = static_cast<LazyVector>(x3);");
      auto z = static_cast<LazyVector>(x3);

      log("std::cout << z.toString();");
      std::cout << z.toString() << "\n";
   }

   _getch();

   return 0;
}