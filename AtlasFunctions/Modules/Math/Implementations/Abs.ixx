module;

#include "../../../../Macros/Macros.h"

export module AtlasMath:Abs;

export namespace Atlas
{
	template<typename NumberType>
	class DLLApi Abs
	{
		public: 
		constexpr static inline auto Calculate( NumberType number )
			noexcept( noexcept( std::abs( number ) ) )
		{
			return std::abs( number );
		}
	};
}