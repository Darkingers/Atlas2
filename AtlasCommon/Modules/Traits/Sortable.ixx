module;

#include "../../../Macros/Macros.h"

export module AtlasTraits:Sortable;
import AtlasDefinitions;
import AtlasDefaultFunctions;
import AtlasSortFunctions;
import AtlasInterfaces;

export namespace Atlas
{
	template<typename DerivedType>
	class DLLApi Sortable : 
		public ISortable<DeduceCollectionContainedType<DerivedType>>
	{
		private: using DataType = DeduceCollectionContainedType<DerivedType>;
		private: using IteratorType = DeduceConstBeginIteratorType<DerivedType>;
		private: using ComparatorType = Comparator<DataType>;


		public: 
		static void MergeSort( const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ComparatorType comparator = Default::Comparator ) final
		{

			Sort::MergeSort( This() , inclusiveFrom , exclusiveTo , comparator );
		}
		public:
		static void MergeSort( const ComparatorType comparator = Default::Comparator ) final
		{
			Sort::MergeSort( This(), comparator );
		}

		public: 
		static void QuickSort( const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ComparatorType comparator = Default::Comparator ) final
		{
			Sort::QuickSort( This( ) , inclusiveFrom , exclusiveTo , comparator );
		}
		public:
		static void QuickSort( const ComparatorType comparator = Default::Comparator ) final
		{
			Sort::QuickSort( This( ) , comparator );
		}

		public: 
		static void HeapSort( const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ComparatorType comparator = Default::Comparator ) final
		{
			Sort::HeapSort( This( ) , inclusiveFrom , exclusiveTo , comparator );
		}
		public:
		static void HeapSort( const ComparatorType comparator = Default::Comparator ) final
		{
			Sort::HeapSort( This( ) , comparator );
		}

		public:  
		static void SelectionSort( const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ComparatorType comparator = Default::Comparator ) final
		{
			Sort::SelectionSort( This( ) , inclusiveFrom , exclusiveTo , comparator );
		}
		public: 
		static void SelectionSort( const ComparatorType comparator = Default::Comparator ) final
		{
			Sort::SelectionSort( This( ) , comparator );
		}

		public: 
		static void InsertionSort( const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ComparatorType comparator = Default::Comparator )final
		{
			Sort::InsertionSort( This( ) , inclusiveFrom , exclusiveTo , comparator );
		}
		public: 
		static void InsertionSort( const ComparatorType comparator = Default::Comparator )  final
		{
			Sort::InsertionSort( This( ) , comparator );
		}

		private:
		DerivedType& This( ) const 
		{
			return static_cast<DerivedType&>( *this );
		}
	};
}