module;

#include "../../../../../Macros/Macros.h"

export module AtlasAdapters:AllAdapters;

import AtlasDefinitions;
import AtlasConcepts;
import AtlasAPI;

export namespace Atlas
{
	template<typename TCollection , typename TPredicate> requires
		( !Concept::IsIndexable<TCollection> ) &&
		Concept::HasIterator<TCollection>&&
		Concept::IsInvokable<bool , TPredicate , typename CollectionTraits<TCollection>::ElementType>
	class DLLApi AllAdapter<TCollection , TPredicate> :
		public std::true_type
	{
	private:

		using IteratorType = typename CollectionTraits<TCollection>::IteratorType;

	public:

		constexpr static inline auto All
			( 
				TCollection collection ,
				TPredicate predicate
			)
			noexcept
			(
				Concept::HasNoexceptConstIterator<TCollection>&&
				Concept::IsNoexceptAll<IteratorType , IteratorType , TPredicate>
			)
		{
			return QueryAPI::All
			(
				IteratorAPI::ConstBegin( collection ) ,
				IteratorAPI::ConstEnd( collection ) ,
				predicate
			);
		}
	};

	template<typename TIterator , typename TPredicate> requires
		Concept::IsIterator<TIterator>&&
		Concept::IsInvokable<bool , TPredicate , typename IteratorTraits<TIterator>::IteratedType>
	class DLLApi AllAdapter<TIterator , TIterator , TPredicate> :
		public std::true_type
	{
	private:

		using TElement = typename IteratorTraits<TIterator>::IteratedType;

	public:

		constexpr static inline auto All
			(
				TIterator start , 
				TIterator end ,
				TPredicate predicate 
			)
			noexcept
			(
				Concept::IsNoexceptIterator<TIterator>&&
				Concept::IsNoexceptInvokable<bool , TPredicate , TElement>
			)
		{
			while ( start != end )
			{
				if ( predicate( *start ) )
				{
					return true;
				}
			}

			return false;
		}
	};
}