module;

#include "../../../../Macros/Macros.h"

export module AtlasDefault;

import AtlasDefinitions;

export import AtlasDefault:Compare;

export namespace Atlas
{
	template<typename TA, typename TB>
	class DLLApi Compare
	{
		public:
		constexpr static inline auto Difference( const TA a , const TB b )
			noexcept( noexcept( a - b ) )
		{
			return a - b;
		}
		
		public: 
		constexpr static inline auto Equal( const TA& a , const TB& b )
			noexcept( noexcept( a == b ) )
		{
			return a == b;
		}

		public: 
		constexpr static inline auto NotEqual( const TA& a , const TB& b )
			noexcept( noexcept( a != b ) )
		{
			return a != b;
		}

		public: 
		constexpr static inline auto LessThan( const TA& a , const TB& b )
			noexcept( noexcept( a < b ) )
		{
			return a < b;
		}

		public:
		constexpr static inline auto LessThanOrEqual( const TA& a , const TB& b )
			noexcept( noexcept( a <= b ) )
		{
			return a <= b;
		}

		public:
		constexpr static inline auto GreaterThan( const TA& a , const TB& b )
			noexcept( noexcept( a > b ) )
		{
			return a > b;
		}

		public: 
		constexpr static inline auto GreaterThanOrEqual( const TA& a , const TB& b )
			noexcept( noexcept( a >= b ) )
		{
			return a >= b;
		}
	};
}
