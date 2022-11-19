module;

#include "../../../../Macros/Macros.h"

export module AtlasDefault;

import AtlasDefinitions;

export import AtlasDefault:Compare;

export namespace Atlas
{
	template<typename TypeA, typename TypeB>
	class DLLApi Compare
	{
		public:
		constexpr static inline auto Difference( const TypeA a , const TypeB b )
			noexcept( noexcept( a - b ) )
		{
			return a - b;
		}
		
		public: 
		constexpr static inline auto Equal( const TypeA& a , const TypeB& b )
			noexcept( noexcept( a == b ) )
		{
			return a == b;
		}

		public: 
		constexpr static inline auto NotEqual( const TypeA& a , const TypeB& b )
			noexcept( noexcept( a != b ) )
		{
			return a != b;
		}

		public: 
		constexpr static inline auto LessThan( const TypeA& a , const TypeB& b )
			noexcept( noexcept( a < b ) )
		{
			return a < b;
		}

		public:
		constexpr static inline auto LessThanOrEqual( const TypeA& a , const TypeB& b )
			noexcept( noexcept( a <= b ) )
		{
			return a <= b;
		}

		public:
		constexpr static inline auto GreaterThan( const TypeA& a , const TypeB& b )
			noexcept( noexcept( a > b ) )
		{
			return a > b;
		}

		public: 
		constexpr static inline auto GreaterThanOrEqual( const TypeA& a , const TypeB& b )
			noexcept( noexcept( a >= b ) )
		{
			return a >= b;
		}
	};
}
