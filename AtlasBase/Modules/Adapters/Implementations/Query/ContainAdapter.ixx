module;

#include "../../../../../Macros/Macros.h"

export module AtlasAdapters:ContainAdapters;

import AtlasDefinitions;
import AtlasConcepts;
import AtlasAPI;

export namespace Atlas
{
	template<typename TCollection , typename TElement> requires 
		( !Concept::IsIndexable<TCollection> ) &&
		Concept::IsIterableWith<TCollection ,TElement>
	class DLLApi ContainAdapter<TCollection,TElement> :
		public std::true_type
	{

	private:

		using IteratorType = typename CollectionTraits<TCollection>::IteratorType;

	public:

		constexpr static inline auto Contain
			(
				TCollection collection ,
				TElement element
			)
			noexcept
			( 
				Concept::HasNoexceptConstIterator<TCollection> &&
				Concept::IsNoexceptContain<IteratorType, IteratorType, TElement>
			)
		{
			return QueryAPI::Contains
			(
				IteratorAPI::ConstBegin( collection ) ,
				IteratorAPI::ConstEnd( collection ) ,
				element 
			);
		}
	};

	template<typename TIterator , typename TElement> requires
		Concept::IsIteratorForType<TIterator , TElement>
	class DLLApi ContainAdapter<TIterator , TIterator, TElement> :
		public std::true_type
	{

	public:

		constexpr static inline auto Contain
			(
				TIterator start,
				TIterator end , 
				TElement element 
			)
			noexcept
			(
				Concept::IsNoexceptIterator<TIterator>&&
				Concept::IsNoexceptEqual<TElement , TElement>
			)
		{
			while ( start != end )
			{
				if ( IteratorAPI::Current( start ) == element )
				{
					return true;
				}

				IteratorAPI::Next( start );
			}

			return false;
		}
	};
}