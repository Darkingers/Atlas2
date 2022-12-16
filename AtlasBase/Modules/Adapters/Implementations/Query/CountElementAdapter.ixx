module;

#include "../../../../../Macros/Macros.h"

export module AtlasAdapters:CountElementAdapters;

import AtlasDefinitions;
import AtlasConcepts;
import AtlasAPI;

export namespace Atlas
{
	template<typename TCollection , typename TElement> requires 
		Concept::IsIterableWith<TCollection , TElement>
	class DLLApi CountElementAdapter<TCollection , TElement> :
		public std::true_type
	{

	public:

		constexpr static inline auto Count( TCollection collection , TElement element )
			noexcept( Concept::HasNoexceptConstIterator<TCollection> )
		{
			auto start = IteratorAPI::ConstBegin( collection );
			const auto end = IteratorAPI::ConstEnd( collection );

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

	template<typename TCollection , typename TElement> requires 
		Concept::HasCountFunction<TCollection, TElement>
	class DLLApi CountElementAdapter<TCollection , TElement> :
		public std::true_type
	{

	public:

		constexpr static inline auto Count( TCollection collection , TElement element )
			noexcept( collection.Count( element ) )
		{
			return collection.Count( element );
		}
	};

	template<typename TCollection , typename TElement> requires 
		Concept::IsArrayOf<TCollection , TElement>
	class DLLApi CountElementAdapter<TCollection , TElement> :
		public std::true_type
	{

	public:

		template<unsigned int Size>
		constexpr static inline auto Count( TCollection( &collection )[Size] , TElement element )
			noexcept
		{
			auto count = 0;

			for ( auto i = 0; i < Size; i++ )
			{
				if ( collection[i] == element )
				{
					count++;
				}
			}

			return count;
		}
	};
}