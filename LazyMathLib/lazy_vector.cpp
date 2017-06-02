#include "lazy_vector.h"
#include <iostream>
#include <algorithm>


LazyVector::LazyVector() noexcept
   : x(0.0)
   , y(0.0)
   , z(0.0)
{
   std::cout << "\tLazyVector::c'tor [0, 0, 0]\n";
}

LazyVector::LazyVector(const std::initializer_list<double>& v) noexcept
{
   auto numInputComponents = static_cast<int>(std::distance(v.begin(), v.end()));
   auto numComponentsToCopy = std::min(3, numInputComponents);

   std::copy_n(v.begin(), numComponentsToCopy, this->v);
   std::fill(this->v + numComponentsToCopy, this->v + 3, 0.0);

   std::cout << "\tLazyVector::c'tor initializer_list [" << x << ", " << y << ", " << z << "]\n";

}

LazyVector::LazyVector(const LazyVector& rhs) noexcept
   : x(rhs.x)
   , y(rhs.y)
   , z(rhs.z)
{
   std::cout << "\tLazyVector::copy c'tor [" << x << ", " << y << ", " << z << "]\n";
}

LazyVector::LazyVector(LazyVector&& rhs) noexcept
{
   std::swap(this->v, rhs.v);
   std::cout << "\tLazyVector::move c'tor [" << x << ", " << y << ", " << z << "]\n";
}

LazyVector::~LazyVector() noexcept
{
   std::cout << "\tLazyVector::d'tor [" << x << ", " << y << ", " << z << "]\n";
}

LazyVector& LazyVector::operator=(const LazyVector& rhs) noexcept
{
   x = rhs.x;
   y = rhs.y;
   z = rhs.z;
   std::cout << "\tLazyVector::copy operator= [" << x << ", " << y << ", " << z << "]\n";
   return *this;
}

LazyVector& LazyVector::operator=(LazyVector&& rhs) noexcept
{
   std::swap(this->v, rhs.v);

   std::cout << "\tLazyVector::move operator= [" << x << ", " << y << ", " << z << "]\n";
   return *this;
}

std::string LazyVector::toString() const
{
   char tmpStr[256];
   sprintf_s(tmpStr, "[%.3f, %.3f, %.3f]", x, y, z);
   return std::string{tmpStr};
}
