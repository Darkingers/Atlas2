module;

#include <algorithm>

#include "../../../../Macros/Macros.h"

export module AtlasAdapters:ContainAdapter;

import AtlasConcepts;
import AtlasDefinitions;
import AtlasIntegration;

export namespace Atlas
{
	template<typename DataType>
	class DLLApi ContainAdapter<DataType , DataType> :
		public std::true_type
	{
		public:
		constexpr static inline bool Contains( const DataType& d1 , const DataType& d2 )
			noexcept ( noexcept ( d1 == d2 ) )
		{
			return d1 == d2;
		}
	};
	
	template<typename TCollection, typename DataType> 
		requires Concept::HasContainFunction<TCollection, DataType>
	class DLLApi ContainAdapter<TCollection, DataType> :
		public std::true_type
	{
	    public:
		constexpr static inline bool Contains(const TCollection& collection, const DataType& contained)
			noexcept ( noexcept ( collection.Contains( contained ) ) )
		{
			return collection.Contains(contained);
		}
	};

	template<typename TCollection, typename DataType>
		requires Concept::IsIterableWith<TCollection, DataType>
	class DLLApi ContainAdapter<TCollection, DataType> :
		public std::true_type
	{
		public:
		constexpr inline bool Contains( const TCollection& collection , const DataType& contained ) 
			noexcept( Concept::IsNoexceptIterableWith<TCollection , DataType> )
		{
			auto iterator = std::cbegin( collection );
			const auto endIterator = std::cend( collection );
			
			for (; iterator != endIterator; std::advance(iterator,1) )
			{
				if ( *iterator == contained )
				{
					return true;
				}
			}

			return false;
		}
	};
}