module;

#include "../../../../../Macros/Macros.h"

export module AtlasAdapters:ContainAdapters;

import AtlasDefinitions;
import AtlasConcepts;
import AtlasAPI;

export namespace Atlas
{
	template<typename TCollection , typename TElement> requires 
		Concept::IsIterableWith<TCollection ,TElement>
	class DLLApi ContainAdapter<TCollection,TElement> :
		public std::true_type
	{

	public:

		constexpr static inline auto Contain( TCollection collection , TElement element )
			noexcept( Concept::HasNoexceptConstIterator<TCollection> )
		{
			auto start = IteratorAPI::ConstBegin( collection );
			const auto end = IteratorAPI::ConstEnd( collection );
			
			while( start != end )
			{
				if ( IteratorAPI::Current(start) == element )
				{
					return true;
				}
				
				IteratorAPI::Next( start );
			}

			return false;
		}
	};

	template<typename TCollection , typename TElement> requires 
		Concept::HasContainFunction<TCollection , TElement>
	class DLLApi ContainAdapter<TCollection , TElement> :
		public std::true_type
	{

	public:

		constexpr static inline auto Contain( TCollection collection , TElement element )
			noexcept( collection.Contains( element ) )
		{
			return collection.Contains( element );		
		}
	};
}