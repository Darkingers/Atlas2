module;

#include "../../../../../Macros/Macros.h"

export module AtlasAdapters:PredicateAdapters;

import AtlasDefinitions;
import AtlasConcepts;
import AtlasAPI;

export namespace Atlas
{
	template<typename TCollection , typename TPredicate> requires 
		Concept::HasIterator<TCollection> &&
		Concept::IsInvokable<bool , TPredicate , typename TCollection::ElementType>
	class DLLApi AnyAdapter<TCollection, TPredicate> :
		public std::true_type
	{
		public:

		constexpr static inline auto Any( TCollection collection , TPredicate predicate )
		{
			const auto end = IteratorAPI::ConstEnd( collection );
			auto start = IteratorAPI::ConstBegin( collection );
			
			while(start!=end )
			{
				if ( predicate( IteratorAPI::Current( start ) ) )
				{
					return true;
				}

				IteratorAPI::Next( start );
			}
		}
	};

	template<typename TCollection , typename TPredicate>requires
		Concept::HasIterator<TCollection>&&
		Concept::IsInvokable<bool , TPredicate , typename TCollection::ElementType>
	class DLLApi AllAdapter<TCollection , TPredicate> :
	 public std::true_type
	{
		public:

		constexpr static inline auto All( TCollection collection , TPredicate predicate )
		{
			const auto end = IteratorAPI::ConstEnd( collection );
			auto start = IteratorAPI::ConstBegin( collection );

			while ( start != end )
			{
				if ( !predicate( IteratorAPI::Current( start ) ) )
				{
					return false;
				}

				IteratorAPI::Next( start );
			}

			return true;
		}
	};
}