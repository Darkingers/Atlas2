module;

#include "../../../../Macros/Macros.h"

export module AtlasMath:Ceil;

export namespace Atlas
{
	template<typename NumberType>
	class DLLApi Ceil
	{
		public:
		constexpr static inline auto Calculate( NumberType number )
			noexcept( noexcept( std::ceil( number ) ) )
		{
			return std::ceil( number );
		}
	};

	template<>
	class DLLApi Ceil<float>
	{
		public:
		constexpr static inline auto Calculate( float number )
			noexcept( noexcept( std::ceilf( number ) ) )
		{
			return std::ceilf( number );
		}
	};

	template<>
	class DLLApi Ceil<long double>
	{
		public:
		constexpr static inline auto Calculate( long double number )
			noexcept( noexcept( std::ceill( number ) ) )
		{
			return std::ceill( number );
		}
	};
}