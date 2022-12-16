module;

#include "../../../../../Macros/Macros.h"

export module AtlasAdapters:MatchAdapters;

import AtlasDefinitions;
import AtlasConcepts;
import AtlasAPI;

export namespace Atlas
{
	template<typename TA , typename TB> requires 
		Concept::HasIterator<TA>&&
		Concept::HasIterator<TB>&&
		Concept::IsSame<typename CollectionTraits<TA>::ElementType , typename CollectionTraits<TB>::ElementType>
	class DLLApi MatchAdapter<TA , TB> :		
		public std::true_type
	{

	public:

		constexpr static inline auto Match( TA a , TB b , const unsigned int matchLength )
			noexcept( QueryAPI::IsMatch( IteratorAPI::ConstBegin( a ) , IteratorAPI::ConstBegin( b ) , matchLength ) )
		{	
			return QueryAPI::IsMatch( IteratorAPI::ConstBegin( a ) , IteratorAPI::ConstBegin( b ) , matchLength );
		}
	};

	template<typename TA , typename TB> requires
		Concept::IsIterator<TA>&&
		Concept::IsIterator<TB>&&
		Concept::IsSame<typename IteratorTraits<TA>::IteratedType , typename IteratorTraits<TB>::IteratedType>
		class DLLApi MatchAdapter<TA , TB> :
		public std::true_type
	{

		public:

		constexpr static inline auto Match( TA a , TB b , const unsigned int matchLength )
			noexcept( Concept::IsNoexceptIterator<TA> && Concept::IsNoexceptIterator<TB> )
		{
			for ( unsigned int i = 0; i < matchLength; i++ )
			{
				if ( IteratorAPI::Current( a ) != IteratorAPI::Current( b ) )
				{
					return false;
				}

				IteratorAPI::Next( a );
				IteratorAPI::Next( b );
			}

			return true;
		}
	};

	template<typename TA , typename TB> requires
		Concept::HasMatch<TA,TB>
		class DLLApi MatchAdapter<TA , TB> :
		public std::true_type
	{

		public:

		constexpr static inline auto Match( TA a , TB b , const unsigned int matchLength )
			noexcept( a.Match( b , matchLength ) )
		{
			return a.Match( b , matchLength );
		}
	};
}