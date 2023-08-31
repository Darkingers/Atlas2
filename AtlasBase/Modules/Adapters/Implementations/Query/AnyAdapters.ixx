module;

#include "../../../../../Macros/Macros.h"

export module AtlasAdapters:AnyAdapters;

import AtlasDefinitions;
import AtlasConcepts;
import AtlasAPI;

export namespace Atlas
{
	template<typename TCollection , typename TPredicate> requires 
		( !Concept::IsIndexable<TCollection> ) &&
		Concept::HasIterator<TCollection> &&
		Concept::IsInvokable<bool , TPredicate , typename CollectionTraits<TCollection>::ElementType>
	class DLLApi AnyAdapter<TCollection, TPredicate> :
		public std::true_type
	{
	private:
		
		using IteratorType = typename CollectionTraits<TCollection>::IteratorType;

	public:

		constexpr static inline auto Any(
			TCollection collection ,
			TPredicate predicate
		)
		{
			return QueryAPI::Any
			(
				IteratorAPI::ConstBegin( collection ),
				IteratorAPI::ConstEnd( collection ),
				predicate
			);
		}
	};

	template<typename TIterator , typename TPredicate> requires
		Concept::IsIterator<TIterator>&&
		Concept::IsInvokable<bool , TPredicate , typename IteratorTraits<TIterator>::IteratedType>
	class DLLApi AnyAdapter<TIterator, TIterator , TPredicate> :
	 public std::true_type
	{
	private:
		
		using TElement = typename IteratorTraits<TIterator>::IteratedType;
		
	public:

		constexpr static inline auto Any( 
			TIterator start,
			TIterator end ,
			TPredicate predicate 
		)
		{
			while ( start != end )
			{
				if ( predicate( *start ) )
				{
					return true;
				}
				else
				{
					IteratorAPI::Next( start );
				}
			}

			return false;
		}
	};
}