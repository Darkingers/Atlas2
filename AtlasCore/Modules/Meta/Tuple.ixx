module;

#include <tuple>
#include "../../../Macros/Macros.h"

export module AtlasMeta:Tuple;
import AtlasDefinitions;
import AtlasConcepts;

export namespace Atlas::Meta
{
	namespace Implementation
	{
		template<unsigned int Index , typename CurrentType , typename... Args>
			requires Concept::IsSame<CurrentType , typename std::tuple_element<Index , std::tuple<Args...>>::type>
		void Reassign( std::tuple<Args...>& tuple , CurrentType&& current , Args&&... arguments )
		{
			std::get<Index>( tuple ) = std::forward<CurrentType&&>( current );

			if constexpr ( sizeof...( arguments ) > 0 )
			{
				Reassign<Index + 1>( tuple , std::forward<Args&&>( arguments )... );
			}
		}
	}	

	class DLLApi Tuple
	{
		template<typename... Args>
		std::tuple<Args...>& Reassign( std::tuple<Args...>& tuple , Args&&... arguments )
		{
			Implementation::Reassign<0>( tuple , std::forward<Args&&>( arguments )... );

			return tuple;
		}
	};
}
