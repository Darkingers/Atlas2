module;

#include "../../../../../Macros/Macros.h"

export module AtlasAdapters:CountElementAdapters;

import AtlasDefinitions;
import AtlasConcepts;
import AtlasAPI;

export namespace Atlas
{
	template<typename TCollection , typename TElement> requires 
		( !Concept::IsIndexable<TCollection> ) &&
		Concept::IsIterableWith<TCollection , TElement>
	class DLLApi CountElementAdapter<TCollection , TElement> :
		public std::true_type
	{
	private:
		
		using IteratorType = typename CollectionTraits<TCollection>::IteratorType;;

	public:

		constexpr static inline auto Count
			( 
				TCollection collection , 
				TElement element 
			)
			noexcept
			(
				Concept::HasNoexceptConstIterator<TCollection>&&
				Concept::IsNoexceptCountElement<IteratorType , IteratorType , TElement>
			)
		{
			return QueryAPI::CountElement
			(
				IteratorAPI::ConstBegin( collection ) , 
				IteratorAPI::ConstEnd( collection ) , 
				element 
			);
		}
	};

	template<typename TIterator , typename TElement> requires
		Concept::IsIteratorForType<TIterator , TElement>
	class DLLApi CountElementAdapter<TIterator , TIterator, TElement> :
		public std::true_type
	{

		public:

		constexpr static inline auto Count
			(
				TIterator start, 
				TIterator end , 
				TElement element 
			)
			noexcept
			(
				Concept::IsNoexceptIterator<TIterator> && 
				Concept::IsNoexceptEqual<TElement,TElement>
			)
		{
			auto count = 0;

			while ( start != end )
			{
				if ( IteratorAPI::Current( start ) == element )
				{
					count++;
				}

				IteratorAPI::Next( start );
			}

			return count;
		}
	};
}