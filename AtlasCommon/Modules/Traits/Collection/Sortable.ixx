module;

#include "../../../../Macros/Macros.h"

export module AtlasCollectionTraits:Sortable;
import AtlasDefinitions;
import AtlasDefaultFunctions;
import AtlasSortFunctions;
import AtlasInterfaces;

export namespace Atlas::Trait
{
	template<typename DerivedType>
	class DLLApi Sortable : 
		public Interface::ISortable<Deduce::CollectionContainedType<DerivedType>>
	{
		private: using DataType = Deduce::CollectionContainedType<DerivedType>;
	private: using TIterator = Deduce::ConstBeginTIterator<DerivedType>;
		private: using ComparatorType = Definition::Comparator<DataType>;


		public: 
		constexpr static void MergeSort( const unsigned int inclusiveStart , const unsigned int exclusiveEnd , const ComparatorType& comparator = Default::Comparator ) final
		{

			Sort::MergeSort( This() , inclusiveStart , exclusiveEnd , comparator );
		}
		public:
		constexpr static void MergeSort( const ComparatorType comparator = Default::Comparator ) final
		{
			Sort::MergeSort( This(), comparator );
		}

		public: 
		constexpr static void QuickSort( const unsigned int inclusiveStart , const unsigned int exclusiveEnd , const ComparatorType& comparator = Default::Comparator ) final
		{
			Sort::QuickSort( This( ) , inclusiveStart , exclusiveEnd , comparator );
		}
		public:
		constexpr static void QuickSort( const ComparatorType& comparator = Default::Comparator ) final
		{
			Sort::QuickSort( This( ) , comparator );
		}

		public: 
		constexpr static void HeapSort( const unsigned int inclusiveStart , const unsigned int exclusiveEnd , const ComparatorType& comparator = Default::Comparator ) final
		{
			Sort::HeapSort( This( ) , inclusiveStart , exclusiveEnd , comparator );
		}
		public:
		constexpr static void HeapSort( const ComparatorType& comparator = Default::Comparator ) final
		{
			Sort::HeapSort( This( ) , comparator );
		}

		public:  
		constexpr static void SelectionSort( const unsigned int inclusiveStart , const unsigned int exclusiveEnd , const ComparatorType& comparator = Default::Comparator ) final
		{
			Sort::SelectionSort( This( ) , inclusiveStart , exclusiveEnd , comparator );
		}
		public: 
		constexpr static void SelectionSort( const ComparatorType& comparator = Default::Comparator ) final
		{
			Sort::SelectionSort( This( ) , comparator );
		}

		public: 
		constexpr static void InsertionSort( const unsigned int inclusiveStart , const unsigned int exclusiveEnd , const ComparatorType& comparator = Default::Comparator )final
		{
			Sort::InsertionSort( This( ) , inclusiveStart , exclusiveEnd , comparator );
		}
		public: 
		constexpr static void InsertionSort( const ComparatorType& comparator = Default::Comparator )  final
		{
			Sort::InsertionSort( This( ) , comparator );
		}

		private:
		constexpr inline DerivedType& This( )
		{
			return static_cast<DerivedType&>( *this );
		}
	};
}