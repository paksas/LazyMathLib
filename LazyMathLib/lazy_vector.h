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
   explicit LazyVectorAdd(const LArg& lhs, const RArg& rhs) noexcept
      : m_lhs(lhs)
      , m_rhs(rhs)
   {
      std::cout << "\tLazyVectorAdd::c'tor(" << m_lhs.toString() << ", " << m_rhs.toString() << ")\n";
   }

   LazyVectorAdd(const LazyVectorAdd<LArg, RArg>& rhs) noexcept
      : m_lhs(rhs.m_lhs)
      , m_rhs(rhs.m_rhs)
   {
      std::cout << "\tLazyVectorAdd::copy c'tor(" << m_lhs.toString() << ", " << m_rhs.toString() << ")\n";
   }

   LazyVectorAdd(LazyVectorAdd<LArg, RArg>&& rhs) noexcept
      : m_lhs(std::move(rhs.m_lhs))
      , m_rhs(std::move(rhs.m_rhs))
   {
      std::cout << "\tLazyVectorAdd::move c'tor(" << m_lhs.toString() << ", " << m_rhs.toString() << ")\n";
   }

   ~LazyVectorAdd() noexcept
   {
      std::cout << "\tLazyVectorAdd::d'tor\n";
   }

   std::string toString() const
   {
      char tmpStr[1024];
      sprintf_s(tmpStr, "%s + %s", m_rhs.toString().c_str(), m_lhs.toString().c_str());
      return std::string{ tmpStr };

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

   LArg m_lhs;
   RArg m_rhs;
};

template<typename LArg, typename RArg>
decltype(auto) operator+(LArg&& lhs, RArg&& rhs) noexcept
{
   std::cout << "\toperator+\n";

   return LazyVectorAdd<LArg, RArg>(std::forward<LArg>(lhs), std::forward<RArg>(rhs));
}
