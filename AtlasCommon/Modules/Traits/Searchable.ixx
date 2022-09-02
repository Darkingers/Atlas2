module;

#include "../../../Macros/Macros.h"

export module AtlasTraits:Searchable;
import AtlasDefinitions;
import AtlasDefaultFunctions;
import AtlasSearchFunctions;
import AtlasInterfaces;

export namespace Atlas
{
	template<typename DerivedType>
	class DLLApi Searchable:
		public ISearchable<DeduceCollectionContainedType<DerivedType>>
	{
		private: using DataType = DeduceCollectionContainedType<DerivedType>;
		private: using ComparatorType = Comparator<DataType>;


		public:
		unsigned int BinarySearch( const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const DataType value ,const ComparatorType& comparator = Default::Comparator ) const final
		{
			return Search::BinarySearch( This( ) , inclusiveFrom , exclusiveTo , value , comparator );
		}
		public: 
		unsigned int BinarySearch( const DataType& value ,const ComparatorType& comparator = Default::Comparator )const  final
		{
			return Search::BinarySearch( This( ) , value , comparator );
		}

		public:
		unsigned int LinearSearch(  const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const DataType value , const ComparatorType comparator ) const final
		{
			return Search::LinearSearch( This( ) , inclusiveFrom , exclusiveTo , value , comparator );
		}
		public: 
		unsigned int LinearSearch( const DataType& value , const ComparatorType& comparator = Default::Comparator )const  final
		{
			return Search::LinearSearch( This( ) , value , comparator );
		}

		public:
		unsigned int JumpSearch( const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const DataType& value , const ComparatorType& comparator = Default::Comparator ) const final
		{
			return Search::JumpSearch( This( ) , inclusiveFrom , exclusiveTo , value , comparator );
		}
		public: 
		unsigned int JumpSearch( const DataType value , const ComparatorType& comparator = Default::Comparator )const  final
		{
			return Search::JumpSearch( This( ) , value , comparator );
		}

		private:
		DerivedType& This( ) const 
		{
			return static_cast<DerivedType&>( *this );
		}
	};
}