module;

#include "../../../../Macros/Macros.h"

export module AtlasMath:Sqrt;

export namespace Atlas
{
	template<typename NumberType>
	class DLLApi Sqrt
	{
		public:
		constexpr static inline auto Calculate( NumberType number )
			noexcept( noexcept( std::sqrt( number ) ) )
		{
			return std::sqrt( number );
		}
	};

	template<>
	class DLLApi Sqrt<float>
	{
		public:
		constexpr static inline auto Calculate( float number )
			noexcept( noexcept( std::sqrtf( number ) ) )
		{
			return std::sqrtf( number );
		}
	};

	template<>
	class DLLApi Sqrt<long double>
	{
		public:
		constexpr static inline auto Calculate( long double number )
			noexcept( noexcept( std::sqrtl( number ) ) )
		{
			return std::sqrtl( number );
		}
	};
}