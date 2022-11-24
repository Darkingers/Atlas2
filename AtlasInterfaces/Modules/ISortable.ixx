module;

#include "../../Macros/Macros.h"

export module AtlasInterfaces:ISortable;
import AtlasDefinitions;
import AtlasDefaultFunctions;

export namespace Atlas::Interface
{
	template<typename DataType>
	class DLLApi ISortable 
	{
		private: using ComparatorType = Definition::Comparator<DataType>;

		public:
		virtual void MergeSort( const unsigned int inclusiveStart , const unsigned int exclusiveEnd , const ComparatorType comparator = Default::Comparator ) = 0;
		public:
		virtual void MergeSort( const ComparatorType comparator = Default::Comparator ) = 0;

		public:
		virtual void QuickSort( const unsigned int inclusiveStart , const unsigned int exclusiveEnd , const ComparatorType comparator = Default::Comparator ) = 0;
		public:
		virtual void QuickSort( const ComparatorType comparator = Default::Comparator ) = 0;

		public:
		virtual void HeapSort( const unsigned int inclusiveStart , const unsigned int exclusiveEnd , const ComparatorType comparator = Default::Comparator ) = 0;
		public:
		virtual void HeapSort( const ComparatorType comparator = Default::Comparator ) = 0;

		public:
		virtual void SelectionSort( const unsigned int inclusiveStart , const unsigned int exclusiveEnd , const ComparatorType comparator = Default::Comparator ) = 0;
		public:
		virtual void SelectionSort( const ComparatorType comparator = Default::Comparator ) = 0;

		public:
		virtual void InsertionSort( const unsigned int inclusiveStart , const unsigned int exclusiveEnd , const ComparatorType comparator = Default::Comparator )  = 0;
		public:
		virtual void InsertionSort( const ComparatorType comparator = Default::Comparator )  = 0;
	};
}