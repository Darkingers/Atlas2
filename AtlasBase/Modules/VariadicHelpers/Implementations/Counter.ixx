module;

#include "../../../../Macros/Macros.h"

export module AtlasVariadicHelpers:Counter;
import AtlasAdapters;

export namespace Atlas::Variadics
{
	class DLLApi Counter
	{
	    public: template<typename DataType, typename... Args>
		constexpr static inline auto Count(const DataType& current, const Args&... arguments)
		{
			const auto count = Adapter::Count( current );

			if constexpr ( sizeof...( arguments ) > 0 )
			{
				return count + Counter::Count( std::forward<const Args&>( arguments )... );
			}
			else
			{
				return count;
			}
		}
	};
}