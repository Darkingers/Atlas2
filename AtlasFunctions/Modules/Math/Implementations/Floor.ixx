module;

#include "../../../../Macros/Macros.h"

export module AtlasMath:Floor;

export namespace Atlas
{
	template<typename NumberType>
	class DLLApi Floor
	{
		public:
		constexpr static inline auto Calculate( NumberType number )
			noexcept( noexcept( std::floor( number ) ) )
		{
			return std::floor( number );
		}
	};

	template<>
	class DLLApi Floor<float>
	{
		public:
		constexpr static inline auto Calculate( float number )
			noexcept( noexcept( std::floorf( number ) ) )
		{
			return std::floorf( number );
		}
	};

	template<>
	class DLLApi Floor<long double>
	{
		public:
		constexpr static inline auto Calculate( long double number )
			noexcept( noexcept( std::floorl( number ) ) )
		{
			return std::floorl( number );
		}
	};
}