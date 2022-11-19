module;

#include "../../../../Macros/Macros.h"

export module AtlasMath:Factorial;

export namespace Atlas
{
	template<typename NumberType>
	class DLLApi Factorial
	{
		public:
		constexpr static inline auto Calculate( NumberType number )
			noexcept
		{
			return number == 0 ? 1 : number * Factorial<NumberType>::Calculate( number-1 );
		}
	};
}