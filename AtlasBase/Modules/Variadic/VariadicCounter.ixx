module;

#include "../../../Macros/Macros.h"

export module AtlasVariadic:VariadicCounter;
import AtlasAdapters;

export namespace Atlas
{
	class DLLApi VariadicCounter
	{
	    public: template<typename DataType, typename... Args>
		inline static auto Count(const DataType& current, const Args&... arguments) 
		{
			using Counter = CountAdapter<DataType>;

			const auto count = Counter::Count( current );

			if constexpr ( sizeof...( arguments ) > 0 )
			{
				return count + VariadicCounter::Count( std::forward<const Args&>( arguments )... );
			}
			else
			{
				return count;
			}
		}
	};
}