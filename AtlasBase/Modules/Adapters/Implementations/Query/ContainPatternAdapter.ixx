module;

#include "../../../../../Macros/Macros.h"

export module AtlasAdapters:ContainPatternAdapters;

import AtlasDefinitions;
import AtlasConcepts;
import AtlasAPI;

export namespace Atlas
{
	template<typename TCollection , typename TPattern> requires
		Concept::HasIterator<TCollection>&&
		Concept::HasIterator<TPattern>&&
		Concept::IsSame<typename CollectionTraits<TCollection>::ElementType , typename CollectionTraits<TPattern>::ElementType>
	class DLLApi ContainPatternAdapter<TCollection, TPattern> :
		public std::true_type
	{
	
	public:

		constexpr static inline auto Contains( TCollection collection , TPattern pattern , const unsigned int matchLength )
			noexcept( QueryAPI::IsMatch( IteratorAPI::ConstBegin( collection ) , IteratorAPI::ConstBegin( pattern ) , matchLength ) && Concept::HasNoexceptConstIterator<TCollection>&& Concept::HasNoexceptConstIterator<TPattern> )
		{
			const auto collectionEnd = IteratorAPI::ConstEnd( collection );
			auto collectionStart = IteratorAPI::ConstBegin( collection );

			while ( collectionStart != collectionEnd )
			{
				if ( QueryAPI::IsMatch( collectionStart , IteratorAPI::ConstBegin( pattern ) , matchLength ) )
				{
					return true;
				}

				IteratorAPI::Next( collectionStart );
			}

			return false;
		}
	};

	template<typename TCollection , typename TPattern> requires
		Concept::HasContainPattern<TCollection , TPattern>
		class DLLApi ContainPatternAdapter<TCollection , TPattern> :
		public std::true_type
	{

	public:

		constexpr static inline auto Contains( TCollection collection , TPattern pattern , const unsigned int matchLength )
			noexcept( collection.Contains( pattern , matchLength ) )
		{
			return collection.Contains( pattern , matchLength );
		}
	};
}