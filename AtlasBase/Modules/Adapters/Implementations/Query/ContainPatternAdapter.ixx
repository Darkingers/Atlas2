module;

#include "../../../../../Macros/Macros.h"

export module AtlasAdapters:ContainPatternAdapters;

import AtlasDefinitions;
import AtlasConcepts;
import AtlasAPI;

export namespace Atlas
{
	template<typename TCollection , typename TPattern> requires
		( !Concept::IsIndexable<TCollection> ) &&
		Concept::HasIterator<TCollection>&&
		Concept::IsIterableWith<TPattern , typename CollectionTraits<TCollection>::ElementType>
		class DLLApi ContainPatternAdapter<TCollection , TPattern> :
		public std::true_type
	{

		private:

		using CollectionIterator = typename CollectionTraits<TCollection>::IteratorType;
		using PatternIterator = typename CollectionTraits<TPattern>::IteratorType;

		public:

		constexpr static inline auto ContainsPattern
			( 
				TCollection collection ,
				TPattern pattern 
			)
			noexcept
			(
				Concept::HasNoexceptIterator<TCollection>&&
				Concept::HasNoexceptIterator<TPattern>&&
				Concept::IsNoexceptContainPattern<CollectionIterator , CollectionIterator , PatternIterator , PatternIterator>
			)
		{
			return QueryAPI::ContainsPattern
			(
				IteratorAPI::ConstBegin( collection ) ,
				IteratorAPI::ConstEnd( collection ) ,
				IteratorAPI::ConstBegin( pattern ) ,
				IteratorAPI::ConstEnd( pattern )
			);
		}
	};
	
	template<typename TIteratorA , typename TIteratorB> requires
		Concept::IsIterator<TIteratorA>&&
		Concept::IsIterator<TIteratorB>&&
		Concept::IsSame<typename IteratorTraits<TIteratorA>::IteratedType , typename IteratorTraits<TIteratorB>::IteratedType>
		class DLLApi ContainPatternAdapter<TIteratorA , TIteratorA , TIteratorB , TIteratorB> :
		public std::true_type
	{

		public:

		constexpr static inline auto ContainsPattern
			(
				TIteratorA startA ,
				TIteratorA endA , 
				TIteratorB startB ,
				TIteratorB endB 
			)
			noexcept
			(
				Concept::IsNoexceptIterator<TIteratorA>&&
				Concept::IsNoexceptIterator<TIteratorB>&&
				Concept::IsNoexceptMatch< TIteratorA , TIteratorA , TIteratorB , TIteratorB>
			)
		{
			while ( startA != endA )
			{
				if ( QueryAPI::IsMatch( startA , endA , startB , endB ) )
				{
					return true;
				}
				else
				{
					IteratorAPI::Next( startA );
				}
			}

			return false;
		}
	};
}