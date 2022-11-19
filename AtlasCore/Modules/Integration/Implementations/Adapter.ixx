module;

#include "../../../../Macros/Macros.h"

export module AtlasIntegration:Adapter;

import AtlasDefinitions;
import AtlasTypeInfo;

export namespace Atlas
{
	template<typename ClearedType>
	class DLLApi ClearAdapter :
		public std::false_type
	{};

	template<typename CollectionType , typename DataType>
	class DLLApi ContainAdapter :
		public std::false_type
	{};

	template<typename CollectionType , typename ContainedCollectionType>
	class DLLApi ContainAllAdapter :
		public std::false_type
	{};

	template<typename DataType>
	class DLLApi SizeAdapter :
		public std::true_type
	{
		public:
		constexpr static inline auto Size( ) noexcept
		{
			return 1;
		}
	};

	template<typename DataType>
	class DLLApi HashAdapter :
		public std::false_type
	{};

	template<typename CollectionType>
	class DLLApi IterableAdapter :
		public std::false_type
	{};
		

	template<typename CollectionType>
	class DLLApi IteratorAdapter:
		public std::false_type
	{};

	export namespace Concept
	{
		template<typename CollectionType>
		concept IsNoexceptClear = noexcept( ClearAdapter<Deduce::SimpleType<CollectionType>>::Clear( std::declval<CollectionType>( ) ) );

		template<typename CollectionType , typename DataType>
		concept IsNoexceptContain = noexcept( ContainAdapter<Deduce::SimpleType<CollectionType> , Deduce::SimpleType<DataType>>::Contain( std::declval<CollectionType>( ) , std::declval<DataType>( ) ) );

		template<typename CollectionType , typename ContainedCollectionType>
		concept IsNoexceptContainAll = noexcept( ContainAllAdapter<Deduce::SimpleType<CollectionType> , Deduce::SimpleType<ContainedCollectionType>>::ContainAll( std::declval<CollectionType>( ) , std::declval<ContainedCollectionType>( ) ) );

		template<typename DataType>
		concept IsNoexceptCount = noexcept( SizeAdapter<Deduce::SimpleType<DataType>>::Count( std::declval<DataType>( ) ) );

		template<typename DataType>
		concept IsNoexceptHash = noexcept( HashAdapter<Deduce::SimpleType<DataType>>::Hash( std::declval<DataType>( ) ) );

		template<typename CollectionType>
		concept IsNoexceptBegin = noexcept( IterableAdapter<Deduce::SimpleType<CollectionType>>::Begin( std::declval<CollectionType>( ) ) );

		template<typename CollectionType>
		concept IsNoexceptEnd = noexcept( IterableAdapter<Deduce::SimpleType<CollectionType>>::End( std::declval<CollectionType>( ) ) );

		template<typename CollectionType>
		concept IsNoexceptConstBegin = noexcept( IterableAdapter<Deduce::SimpleType<CollectionType>>::ConstBegin( std::declval<CollectionType>( ) ) );
		
		template<typename CollectionType>
		concept IsNoexceptConstEnd = noexcept( IterableAdapter<Deduce::SimpleType<CollectionType>>::ConstEnd( std::declval<CollectionType>( ) ) );

		template<typename IteratorType>
		concept IsNoexceptCurrentValue = noexcept( IteratorAdapter<Deduce::SimpleType<IteratorType>>::CurrentValue( std::declval<IteratorType>( ) ) );

		template<typename IteratorType>
		concept IsNoexceptIterable = noexcept( IteratorAdapter<Deduce::SimpleType<IteratorType>>::Iterate( std::declval<IteratorType>( ), std::declval<int>() ) );	

		template<typename CollectionType>
		concept HasNoexceptIterator = IsNoexceptBegin<CollectionType> && IsNoexceptEnd<CollectionType> && IsNoexceptIterable<TypeDetails<CollectionType>::IteratorType> && IsNoexceptCurrentValue<TypeDetails<CollectionType>::IteratorType>;

		template<typename CollectionType>
		concept HasNoexceptConstIterator = IsNoexceptConstBegin<CollectionType> && IsNoexceptConstEnd<CollectionType> && IsNoexceptIterable<TypeDetails<CollectionType>::ConstIteratorType> && IsNoexceptCurrentValue<TypeDetails<CollectionType>::ConstIteratorType>;
	}
	
	class DLLApi Adapter
	{
		public: template<typename CollectionType>
		constexpr static inline void Clear( CollectionType& collection )
			noexcept( Concept::IsNoexceptClear<CollectionType> )
		{
			ClearAdapter<Deduce::SimpleType<CollectionType>>::Clear( collection );
		}

		public: template<typename CollectionType , typename DataType>
		constexpr static inline bool Contains( const CollectionType& collection , const DataType& contained )
			noexcept ( Concept::IsNoexceptContain<CollectionType, DataType> )
		{
			return ContainAdapter<Deduce::SimpleType<CollectionType> , Deduce::SimpleType<DataType>>::Contains( collection , contained );
		}

		public: template<typename CollectionType , typename ContainedCollectionType>
		constexpr static inline bool ContainsAll( const CollectionType& collection , const ContainedCollectionType& containedContainer )
			noexcept ( Concept::IsNoexceptContainAll<CollectionType, ContainedCollectionType> )
		{
			return ContainAllAdapter<Deduce::SimpleType<CollectionType> , Deduce::SimpleType<ContainedCollectionType>>::ContainsAll( collection , containedContainer );
		}

		public: template<typename DataType>
		constexpr static inline auto Size( const DataType& data )
			noexcept ( Concept::IsNoexceptCount<DataType> )
		{
			return SizeAdapter<Deduce::SimpleType<DataType>>::Size( data );
		}

		public: template<typename DataType>
		constexpr static inline void GetHash( const DataType& data )
			noexcept ( Concept::IsNoexceptHash<DataType> )
		{
			return HashAdapter<Deduce::SimpleType<DataType>>::GetHash( data );
		}

		public: template<typename CollectionType>
		constexpr static inline auto Begin( const CollectionType& collection )
			noexcept ( Concept::IsNoexceptBegin<CollectionType> )
		{
			return IterableAdapter<Deduce::SimpleType<CollectionType>>::Begin( collection );
		}

		public: template<typename CollectionType>
		constexpr static inline auto ConstBegin( const CollectionType& collection )
			noexcept ( Concept::IsNoexceptConstBegin<CollectionType> )
		{
			return IterableAdapter<Deduce::SimpleType<CollectionType>>::ConstBegin( collection );
		}

		public: template<typename CollectionType>
		constexpr static inline auto End( const CollectionType& collection )
			noexcept ( Concept::IsNoexceptEnd<CollectionType> )
		{
			return IterableAdapter<Deduce::SimpleType<CollectionType>>::End( collection );
		}

		public: template<typename CollectionType>
		constexpr static inline auto ConstEnd( const CollectionType& collection )
			noexcept ( Concept::IsNoexceptConstEnd<CollectionType> )
		{
			return IterableAdapter<Deduce::SimpleType<CollectionType>>::ConstEnd( collection );
		}

		public: template<typename IteratorType>
		constexpr static inline auto CurrentValue( const IteratorType& iterator )
			noexcept ( Concept::IsNoexceptCurrentValue<IteratorType> )
		{
			return IteratorAdapter<Deduce::SimpleType<IteratorType>>::CurrentValue( iterator );
		}

		public: template<typename IteratorType>
		constexpr static inline void Iterate( IteratorType& iterator, int step = 1 )
			noexcept ( Concept::IsNoexceptIterable<IteratorType> )
		{
			IteratorAdapter<Deduce::SimpleType<IteratorType>>::Iterate( iterator, step );
		}
	};
}
