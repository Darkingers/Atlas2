module;

#include "../../../../Macros/Macros.h"

export module AtlasMath:Log;

export namespace Atlas
{
	template<typename NumberType>
	class DLLApi Log
	{
		public:
		constexpr static inline auto Calculate( NumberType number )
			noexcept( noexcept( std::log( number ) ) )
		{
			return std::log( number );
		}
	};

	template<>
	class DLLApi Log<float>
	{
		public:
		constexpr static inline auto Calculate( float number )
			noexcept( noexcept( std::logf( number ) ) )
		{
			return std::logf( number );
		}
	};

	template<>
	class DLLApi Log<long double>
	{
		public:
		constexpr static inline auto Calculate( long double number )
			noexcept( noexcept( std::logl( number ) ) )
		{
			return std::logl( number );
		}
	};
}
