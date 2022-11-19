module;

#include "../../../../Macros/Macros.h"

export module AtlasMath:Pow;

export namespace Atlas
{
	template<typename NumberType>
	class DLLApi Pow
	{
		public:
		constexpr static inline auto Calculate( NumberType base , NumberType exponent )
			noexcept( noexcept( std::pow( base , exponent ) ) )
		{
			return std::pow( base , exponent );
		}
	};

	template<>
	class DLLApi Pow<float>
	{
		public:
		constexpr static inline auto Calculate( float base , float exponent )
			noexcept( noexcept( std::powf( base , exponent ) ) )
		{
			return std::powf( base , exponent );
		}
	};

	template<>
	class DLLApi Pow<long double>
	{
		public:
		constexpr static inline auto Calculate( long double base , long double exponent )
			noexcept( noexcept( std::powl( base , exponent ) ) )
		{
			return std::powl( base , exponent );
		}
	};
}