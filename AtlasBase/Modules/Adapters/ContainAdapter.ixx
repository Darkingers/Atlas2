module;

#include <algorithm>
#include "../../../Macros/Macros.h"

export module AtlasAdapters:ContainAdapter;
import AtlasConcepts;
import AtlasDefinitions;
import AtlasExceptions;

export namespace Atlas::Adapters
{
	template<typename CollectionType , typename DataType>
	class DLLApi ContainAdapter :
		public std::false_type
	{
		public:
		inline static constexpr bool Contains( const CollectionType&& collection , const DataType& contained )
		{
			throw AdapterResolveException( "Could not resolve ContainAdapter" , &collection );
		}
	};

	template<typename CollectionType, typename DataType>
		requires HasContainFunction<CollectionType, DataType>
	class DLLApi ContainAdapter<CollectionType, DataType> :
		public std::true_type
	{
		private: static constexpr bool NoExcept = noexcept ( std::declval<CollectionType>.Contains( std::declval<DataType>( ) ) );

	    public:
		inline static bool Contains(const CollectionType& collection, const DataType& contained) noexcept ( NoExcept )
		{
			return collection.Contains(contained);
		}
	};

	template<typename CollectionType, typename DataType>
		requires IsIterableWith<CollectionType, DataType>
	class DLLApi ContainAdapter<CollectionType, DataType> :
		public std::true_type
	{
		private: using EndIteratorType = DeduceConstEndIteratorType<CollectionType>;
		
		private: static constexpr bool NoExceptBegin = noexcept ( std::cbegin( std::declval<CollectionType>( ) ) );
		private: static constexpr bool NoExceptEnd = noexcept ( std::cend( std::declval<CollectionType>( ) ) );
		private: static constexpr bool NoExceptFind = noexcept ( std::find( std::cbegin( std::declval<CollectionType>( ) ) , std::cend( std::declval<CollectionType>( ) ) , std::declval<DataType>( ) ) );
		private: static constexpr bool NoExcept = NoExceptBegin && NoExceptEnd && NoExceptFind;


		public:
		inline bool Contains( const CollectionType& collection , const DataType& contained ) noexcept( NoExcept )
		{
			const auto endIterator = std::cend( collection );

			return std::find( std::cbegin( collection ) , endIterator , contained ) != endIterator;
		}
	};
}