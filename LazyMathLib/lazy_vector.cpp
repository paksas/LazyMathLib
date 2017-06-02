#include "lazy_vector.h"
#include <iostream>
#include <algorithm>


LazyVector::LazyVector() noexcept
   : x(0.0)
   , y(0.0)
   , z(0.0)
{
   std::cout << "\tLazyVector::c'tor\n";
}

LazyVector::LazyVector(const std::initializer_list<double>& v) noexcept
{
   std::cout << "\tLazyVector::c'tor initializer_list\n";

   auto numInputComponents = static_cast<int>(std::distance(v.begin(), v.end()));
   auto numComponentsToCopy = std::min(3, numInputComponents);

   std::copy_n(v.begin(), numComponentsToCopy, this->v);
   std::fill(this->v + numComponentsToCopy, this->v + 3, 0.0);
}

LazyVector::LazyVector(const LazyVector& rhs) noexcept
   : x(rhs.x)
   , y(rhs.y)
   , z(rhs.z)
{
   std::cout << "\tLazyVector::copy c'tor\n";
}

LazyVector::LazyVector(LazyVector&& rhs) noexcept
{
   std::cout << "\tLazyVector::move c'tor\n";
   std::swap(this->v, rhs.v);
}

LazyVector::~LazyVector() noexcept
{
   std::cout << "\tLazyVector::d'tor\n";
}

LazyVector& LazyVector::operator=(const LazyVector& rhs) noexcept
{
   std::cout << "\tLazyVector::copy operator=\n";
   x = rhs.x;
   y = rhs.y;
   z = rhs.z;
   return *this;
}

LazyVector& LazyVector::operator=(LazyVector&& rhs) noexcept
{
   std::cout << "\tLazyVector::move operator=\n";
   std::swap(this->v, rhs.v);

   return *this;
}

std::string LazyVector::toString() const
{
   char tmpStr[256];
   sprintf_s(tmpStr, "[%.3f, %.3f, %.3f]", x, y, z);
   return std::string{tmpStr};
}
