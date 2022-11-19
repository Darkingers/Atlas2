module;

#include "../../../../Macros/Macros.h"

export module AtlasMath:ASin;

export namespace Atlas
{
	template<typename NumberType>
	class DLLApi ASin
	{
		public:
		constexpr static inline auto Calculate( NumberType number )
			noexcept( noexcept( std::asin( number ) ) )
		{
			return std::asin( number );
		}
	};

	template<>
	class DLLApi ASin<float>
	{
		public:
		constexpr static inline auto Calculate( float number )
			noexcept( noexcept( std::asinf( number ) ) )
		{
			return std::asinf( number );
		}
	};

	template<>
	class DLLApi ASin<long double>
	{
		public:
		constexpr static inline auto Calculate( long double number )
			noexcept( noexcept( std::asinl( number ) ) )
		{
			return std::asinl( number );
		}
	};
}