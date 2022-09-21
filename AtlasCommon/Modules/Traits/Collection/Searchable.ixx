module;

#include "../../../../Macros/Macros.h"

export module AtlasCollectionTraits:Searchable;
import AtlasDefinitions;
import AtlasDefaultFunctions;
import AtlasSearchFunctions;
import AtlasInterfaces;

export namespace Atlas::Trait
{
	template<typename DerivedType>
	class DLLApi Searchable:
		public Interface::ISearchable<Deduce::CollectionContainedType<DerivedType>>
	{
		private: using DataType = Deduce::CollectionContainedType<DerivedType>;
		private: using ComparatorType = Definition::Comparator<DataType>;


		public:
		constexpr unsigned int BinarySearch( const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const DataType value ,const ComparatorType& comparator = Default::Comparator ) const final
		{
			return Search::BinarySearch( This( ) , inclusiveFrom , exclusiveTo , value , comparator );
		}
		public: 
		constexpr unsigned int BinarySearch( const DataType& value ,const ComparatorType& comparator = Default::Comparator )const  final
		{
			return Search::BinarySearch( This( ) , value , comparator );
		}

		public:
		constexpr unsigned int LinearSearch(  const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const DataType value , const ComparatorType comparator ) const final
		{
			return Search::LinearSearch( This( ) , inclusiveFrom , exclusiveTo , value , comparator );
		}
		public: 
		constexpr unsigned int LinearSearch( const DataType& value , const ComparatorType& comparator = Default::Comparator )const  final
		{
			return Search::LinearSearch( This( ) , value , comparator );
		}

		public:
		constexpr unsigned int JumpSearch( const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const DataType& value , const ComparatorType& comparator = Default::Comparator ) const final
		{
			return Search::JumpSearch( This( ) , inclusiveFrom , exclusiveTo , value , comparator );
		}
		public: 
		constexpr unsigned int JumpSearch( const DataType value , const ComparatorType& comparator = Default::Comparator )const  final
		{
			return Search::JumpSearch( This( ) , value , comparator );
		}

		private:
		constexpr inline const DerivedType& This( ) const
		{
			return static_cast<DerivedType&>( *this );
		}
	};
}