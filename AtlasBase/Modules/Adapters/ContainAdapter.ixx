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
		private: static constexpr bool IsNoExcept = noexcept ( std::declval<CollectionType>.Contains( std::declval<DataType>( ) ) );

	    public:
		constexpr inline static bool Contains(const CollectionType& collection, const DataType& contained) noexcept ( IsNoExcept )
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
		
		private: static constexpr bool IsNoExceptBegin = noexcept ( std::cbegin( std::declval<CollectionType>( ) ) );
		private: static constexpr bool IsNoExceptEnd = noexcept ( std::cend( std::declval<CollectionType>( ) ) );
		private: static constexpr bool IsNoExceptFind = noexcept ( std::find( std::cbegin( std::declval<CollectionType>( ) ) , std::cend( std::declval<CollectionType>( ) ) , std::declval<DataType>( ) ) );
		private: static constexpr bool IsNoExcept = IsNoExceptBegin && IsNoExceptEnd && IsNoExceptFind;


		public:
		constexpr inline bool Contains( const CollectionType& collection , const DataType& contained ) noexcept( IsNoExcept )
		{
			const auto endIterator = std::cend( collection );

			return std::find( std::cbegin( collection ) , endIterator , contained ) != endIterator;
		}
	};
}

export namespace Atlas::Concept
{
	template<typename CollectionType , typename DataType>
	concept HasContainAdapter = Atlas::Adapters::ContainAdapter<CollectionType , DataType>::value;
}