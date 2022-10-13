module;

#include <algorithm>

#include "../../../Macros/Macros.h"

export module AtlasAdapters:ContainAdapter;

import AtlasTypeInfo;
import AtlasConcepts;
import AtlasDefinitions;

export namespace Atlas::Adapters
{
	template<typename CollectionType , typename DataType>
	class DLLApi ContainAdapter :
		public std::false_type
	{
	};

	template<typename CollectionType, typename DataType> 
		requires Concept::HasContainFunction<CollectionType, DataType>
	class DLLApi ContainAdapter<CollectionType, DataType> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = noexcept ( std::declval<CollectionType>().Contains( DataType( ) ) );

			
	    public:
		constexpr inline static bool Contains(const CollectionType& collection, const DataType& contained)
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
		private: using EndIteratorType = Deduce::ConstEndIteratorType<CollectionType>;
		
		private: constexpr static bool IsNoexceptBegin = Concept::IsNoexceptBegin<CollectionType>;
		private: constexpr static bool IsNoexceptEnd = Concept::IsNoexceptConstEnd<CollectionType>;
		private: constexpr static bool IsNoexcept = IsNoexceptBegin && IsNoexceptEnd;


		public:
		constexpr inline bool Contains( const CollectionType& collection , const DataType& contained ) 
			noexcept( IsNoexcept )
		{
			const auto endIterator = std::cend( collection );

			for ( auto iterator = std::cbegin( collection ); iterator != endIterator; ++iterator )
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