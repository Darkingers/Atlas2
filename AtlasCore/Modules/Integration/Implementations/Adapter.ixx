module;

#include "../../../../Macros/Macros.h"

export module AtlasIntegration:Adapter;
import AtlasDefinitions;

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

	template<typename TypeA , typename TypeB>
	class DLLApi EqualityAdapter :
		public std::false_type
	{};

	template<typename DataType>
	class DLLApi HashAdapter :
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

		template<typename DataTypeType>
		concept IsNoexceptCount = noexcept( SizeAdapter<Deduce::SimpleType<DataTypeType>>::Count( std::declval<DataTypeType>( ) ) );

		template<typename TypeA , typename TypeB>
		concept IsNoexceptEquality = noexcept( EqualityAdapter<Deduce::SimpleType<TypeA> , Deduce::SimpleType<TypeB>>::Equality( std::declval<TypeA>( ) , std::declval<TypeB>( ) ) );

		template<typename DataType>
		concept IsNoexceptHash = noexcept( HashAdapter<Deduce::SimpleType<DataType>>::Hash( std::declval<DataType>( ) ) );
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

		public: template<typename TypeA , typename TypeB>
		constexpr static inline bool Equals( const TypeA& a , const TypeB& b )
			noexcept ( Concept::IsNoexceptEquality<TypeA,TypeB> )
		{
			return EqualityAdapter<Deduce::SimpleType<TypeA> , Deduce::SimpleType<TypeB>>::Equals( a , b );
		}

		public: template<typename DataType>
		constexpr static inline void GetHash( const DataType& data )
			noexcept ( Concept::IsNoexceptHash )
		{
			return HashAdapter<Deduce::SimpleType<DataType>>::GetHash( data );
		}
	};
}
