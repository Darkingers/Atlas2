module;

#include <algorithm>

#include "../../../../Macros/Macros.h"

export module AtlasAdapters:ContainAdapter;

import AtlasConcepts;
import AtlasDefinitions;
import AtlasIntegration;

export namespace Atlas
{
	template<typename CollectionType, typename DataType> 
		requires Concept::HasContainFunction<CollectionType, DataType>
	class DLLApi ContainAdapter<CollectionType, DataType> :
		public std::true_type
	{
		private: constexpr static inline bool IsNoexcept = noexcept ( std::declval<CollectionType>().Contains( std::declval<DataType>() ) );

			
	    public:
		constexpr static inline bool Contains(const CollectionType& collection, const DataType& contained)
			noexcept ( IsNoexcept )
		{
			return collection.Contains(contained);
		}
	};

	template<typename CollectionType, typename DataType>
		requires Concept::IsIterableWith<CollectionType, DataType>
	class DLLApi ContainAdapter<CollectionType, DataType> :
		public std::true_type
	{
		private: constexpr static inline bool IsNoexcept = Concept::IsNoexceptIterableWith<CollectionType,DataType>;


		public:
		constexpr inline bool Contains( const CollectionType& collection , const DataType& contained ) 
			noexcept( IsNoexcept )
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