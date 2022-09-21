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
	private: using IteratorType = Deduce::ConstBeginIteratorType<DerivedType>;
		private: using ComparatorType = Definition::Comparator<DataType>;


		public: 
		constexpr static void MergeSort( const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ComparatorType& comparator = Default::Comparator ) final
		{

			Sort::MergeSort( This() , inclusiveFrom , exclusiveTo , comparator );
		}
		public:
		constexpr static void MergeSort( const ComparatorType comparator = Default::Comparator ) final
		{
			Sort::MergeSort( This(), comparator );
		}

		public: 
		constexpr static void QuickSort( const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ComparatorType& comparator = Default::Comparator ) final
		{
			Sort::QuickSort( This( ) , inclusiveFrom , exclusiveTo , comparator );
		}
		public:
		constexpr static void QuickSort( const ComparatorType& comparator = Default::Comparator ) final
		{
			Sort::QuickSort( This( ) , comparator );
		}

		public: 
		constexpr static void HeapSort( const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ComparatorType& comparator = Default::Comparator ) final
		{
			Sort::HeapSort( This( ) , inclusiveFrom , exclusiveTo , comparator );
		}
		public:
		constexpr static void HeapSort( const ComparatorType& comparator = Default::Comparator ) final
		{
			Sort::HeapSort( This( ) , comparator );
		}

		public:  
		constexpr static void SelectionSort( const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ComparatorType& comparator = Default::Comparator ) final
		{
			Sort::SelectionSort( This( ) , inclusiveFrom , exclusiveTo , comparator );
		}
		public: 
		constexpr static void SelectionSort( const ComparatorType& comparator = Default::Comparator ) final
		{
			Sort::SelectionSort( This( ) , comparator );
		}

		public: 
		constexpr static void InsertionSort( const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ComparatorType& comparator = Default::Comparator )final
		{
			Sort::InsertionSort( This( ) , inclusiveFrom , exclusiveTo , comparator );
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