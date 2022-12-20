module;

#include "../../../../../Macros/Macros.h"

export module AtlasAdapters:MatchAdapters;

import AtlasDefinitions;
import AtlasConcepts;
import AtlasAPI;

export namespace Atlas
{
	template<typename TCollectionA , typename TCollectionB> requires 
		Concept::HasIterator<TCollectionA> &&
		Concept::IsIterableWith<TCollectionB, typename CollectionTraits<TCollectionA>::ElementType>
	class DLLApi MatchAdapter<TCollectionA , TCollectionB> :
		public std::true_type
	{
		
	private:

		using AIteratorType = typename CollectionTraits<TCollectionA>::IteratorType;
		using BIteratorType = typename CollectionTraits<TCollectionB>::IteratorType;

	public:

		constexpr static inline auto Match( TCollectionA collectionA , TCollectionB collectionB )
			noexcept
			( 
				Concept::HasNoexceptConstIterator<TCollectionA>&& 
				Concept::HasNoexceptConstIterator<TCollectionB>&&
				Concept::IsNoexceptMatch<AIteratorType, AIteratorType , BIteratorType, BIteratorType>
			)
		{	
			return QueryAPI::IsMatch
			( 
				IteratorAPI::ConstBegin( collectionA ) ,
				IteratorAPI::ConstEnd( collectionA ) ,
				IteratorAPI::ConstBegin( collectionB ) ,
				IteratorAPI::ConstEnd( collectionB )
			);
		}
	};

	template<typename TIteratorA , typename TIteratorB> requires
		Concept::IsIterator<TIteratorA>&&
		Concept::IsIteratorForType<TIteratorB, typename IteratorTraits<TIteratorA>::IteratedType>
	class DLLApi MatchAdapter<TIteratorA, TIteratorA , TIteratorB, TIteratorB> :
		public std::true_type
	{

	private:
		
		using ElementType = typename IteratorTraits<TIteratorA>::IteratedType;

	public:

		constexpr static inline auto Match( TIteratorA startA , TIteratorA endA , TIteratorB startB , TIteratorB endB )
			noexcept
			( 
				Concept::IsNoexceptIterator<TIteratorA>&& 
				Concept::IsNoexceptIterator<TIteratorB> &&
				Concept::IsNoexceptNotEqual<ElementType , ElementType>
			)
		{
			while ( startA != endA && startB != endB )
			{
				if ( IteratorAPI::Current( startA ) != IteratorAPI::Current( startB ) )
				{
					return false;
				}
				else
				{
					IteratorAPI::Next( startA );
					IteratorAPI::Next( startB );
				}
			}

			if ( startA != endA )
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	};

	template<typename TIteratorA , typename TIteratorB> requires
		Concept::IsIterator<TIteratorA>&&
		Concept::IsIteratorForType<TIteratorB , typename IteratorTraits<TIteratorA>::IteratedType>
		class DLLApi MatchAdapter<TIteratorA , TIteratorA , TIteratorB ,const unsigned int> :
		public std::true_type
	{

		private:

		using ElementType = typename IteratorTraits<TIteratorA>::IteratedType;

		public:

		constexpr static inline auto Match( TIteratorA startA , TIteratorA endA , TIteratorB patternStart ,const unsigned int patternLength )
			noexcept
			(
				Concept::IsNoexceptIterator<TIteratorA>&&
				Concept::IsNoexceptIterator<TIteratorB>&&
				Concept::IsNoexceptNotEqual<ElementType , ElementType>
			)
		{
			int step = 0;
			while ( startA != endA && step++ < patternLength )
			{
				if ( IteratorAPI::Current( startA ) != IteratorAPI::Current( patternStart ) )
				{
					return false;
				}
				else
				{
					IteratorAPI::Next( startA );
					IteratorAPI::Next( patternStart );
				}
			}

			return true;
		}
	};
}