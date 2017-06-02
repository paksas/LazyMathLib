#pragma once

#include <initializer_list>
#include <string>
#include <iostream>


struct LazyVector
{
   LazyVector() noexcept;
   LazyVector(const std::initializer_list<double>& v) noexcept;
   LazyVector(const LazyVector& rhs) noexcept;
   LazyVector(LazyVector&& rhs) noexcept;
   ~LazyVector() noexcept;

   LazyVector& operator=(const LazyVector& rhs) noexcept;
   LazyVector& operator=(LazyVector&& rhs) noexcept;

   std::string toString() const;

   union
   {
      double v[3];

      struct
      {
         double x;
         double y;
         double z;
      };
   };
};


template<typename LArg, typename RArg>
struct LazyVectorAdd
{
   explicit LazyVectorAdd(const LArg& rhs, const RArg& lhs) noexcept
      : m_lhs(lhs)
      , m_rhs(rhs)
   {
   }

   operator LazyVector() noexcept
   {
      std::cout << "\tLazyVectorAdd::evaluate\n";

      auto lhs = static_cast<LazyVector>(m_lhs);
      auto rhs = static_cast<LazyVector>(m_rhs);

      return LazyVector{
         rhs.x + lhs.x,
         rhs.y + lhs.y,
         rhs.z + lhs.z };
   }

   LArg m_rhs;
   RArg m_lhs;
};

template<typename LArg, typename RArg>
auto operator+(const LArg& lhs, const RArg& rhs) noexcept -> decltype(LazyVectorAdd<LArg, RArg>(lhs, rhs))
{
   return LazyVectorAdd<LArg, RArg>(lhs, rhs);
}
