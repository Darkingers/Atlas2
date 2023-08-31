module;

#include "../../../../../Macros/Macros.h"

export module AtlasAdapters:CountPatternAdapters;

import AtlasDefinitions;
import AtlasConcepts;
import AtlasAPI;

export namespace Atlas
{
	template<typename TCollection , typename TPattern> requires
		( !Concept::IsIndexable<TCollection> ) &&
		Concept::HasIterator<TCollection>&&
		Concept::IsIterableWith<TPattern , typename CollectionTraits<TCollection>::ElementType>
	class DLLApi CountPatternAdapter<TCollection , TPattern> :
		public std::true_type
	{

	private:

		using CollectionIterator = typename CollectionTraits<TCollection>::IteratorType;
		using PatternIterator = typename CollectionTraits<TPattern>::IteratorType;

	public:

		constexpr static inline auto CountPattern(
			TCollection collection , 
			TPattern pattern 
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
	class DLLApi CountPatternAdapter<TIteratorA , TIteratorA , TIteratorB , TIteratorB> :
		public std::true_type
	{

	public:

		constexpr static inline auto CountPattern( 
			TIteratorA startA , 
			TIteratorA endA ,
			TIteratorB startB ,
			TIteratorB endB 
		)
		{
			auto count = 0;

			while ( startA != endA )
			{
				if ( QueryAPI::IsMatch( startA , endA , startB , endB ) )
				{
					count++;
				}
				
				IteratorAPI::Next( startA );
			}

			return count;
		}
	};

	template<typename TIteratorA , typename TIteratorB> requires
		Concept::IsIterator<TIteratorA>&&
		Concept::IsIterator<TIteratorB>&&
		Concept::IsSame<typename IteratorTraits<TIteratorA>::IteratedType , typename IteratorTraits<TIteratorB>::IteratedType>
	class DLLApi CountPatternAdapter<TIteratorA , TIteratorA , TIteratorB , unsigned int> :
		public std::true_type
	{

	public:

		constexpr static inline auto CountPattern(
			TIteratorA startA ,
			TIteratorA endA , 
			TIteratorB patternStart ,
			const unsigned int patternLength
		)
		{
			auto count = 0;

			while ( startA != endA )
			{
				if ( QueryAPI::IsMatch( startA , endA , patternStart, patternLength ) )
				{
					count++;
					
					IteratorAPI::Move( startA , patternLength );
				}
				else
				{
					IteratorAPI::Next( startA );
				}
			}

			return count;
		}
	};
}