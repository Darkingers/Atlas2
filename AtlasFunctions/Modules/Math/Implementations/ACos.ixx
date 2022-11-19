module;

#include "../../../../Macros/Macros.h"

export module AtlasMath:ACos;

export namespace Atlas
{
	template<typename NumberType>
	class DLLApi ACos
	{
		public: 
		constexpr static inline auto Calculate( NumberType number )
			noexcept( noexcept( std::acos( number ) ) )
		{
			return std::acos( number );
		}
	};

	template<>
	class DLLApi ACos<float>
	{
		public:
		constexpr static inline auto Calculate( float number )
			noexcept( noexcept( std::acosf( number ) ) )
		{
			return std::acosf( number );
		}
	};

	template<>
	class DLLApi ACos<long double>
	{
		public:
		constexpr static inline auto Calculate(long double number )
			noexcept( noexcept( std::acosl( number ) ) )
		{
			return std::acosl( number );
		}
	};
}