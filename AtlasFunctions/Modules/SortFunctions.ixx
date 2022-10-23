module;

#include "../../Macros/Macros.h"

export module AtlasSortFunctions;
import AtlasDefinitions;
import AtlasDefaultFunctions;
import AtlasTypeInfo;
import AtlasAdapters;
import AtlasValidation;
import AtlasConfiguration;

export namespace Atlas
{
	namespace Implementation
	{
		template<typename CollectionType>
		class Sort
		{
			private: using DataType = Deduce::CollectionIndexedType<CollectionType , unsigned int>;
			private: using ComparatorType = Definition::Comparator<DataType>;

			public:
			constexpr static void MergeSort( CollectionType& collection, const unsigned int inclusiveFrom, const unsigned int exclusiveTo, const ComparatorType& comparator)
			{
				if ( inclusiveFrom >= exclusiveTo )
				{
					return;
				}
				else
				{
					const unsigned int middle = inclusiveFrom + ( exclusiveTo - inclusiveFrom ) / 2;

					Sort<CollectionType>::MergeSort( collection, inclusiveFrom, middle, comparator );
					Sort<CollectionType>::MergeSort( collection, middle, exclusiveTo, comparator );
					Sort<CollectionType>::Merge( collection, inclusiveFrom, middle, exclusiveTo, comparator );
				}
			}
			
			public: 
			constexpr static void QuickSort( CollectionType& collection, const unsigned int inclusiveFrom, const unsigned int exclusiveTo, const ComparatorType& comparator )
			{
				if ( inclusiveFrom < exclusiveTo )
				{
					const unsigned int partition = Sort<CollectionType>::Partition( collection, inclusiveFrom, exclusiveTo, comparator );

					Sort<CollectionType>::QuickSort( collection, inclusiveFrom, partition - 1, comparator );
					Sort<CollectionType>::QuickSort( collection, partition + 1, exclusiveTo, comparator );
				}
			}

			public:
			constexpr static void HeapSort( CollectionType& collection, const unsigned int inclusiveFrom, const unsigned int exclusiveTo, const ComparatorType& comparator )
			{
				for ( unsigned int i = exclusiveTo / 2 - 1; i >= inclusiveFrom; )
				{
					Sort<CollectionType>::Heapify( collection, exclusiveTo, i--, comparator );
				}

				for ( unsigned int i = exclusiveTo - 1; i > inclusiveFrom; )
				{
					Sort<CollectionType>::Swap( collection, 0, i );

					Sort<CollectionType>::Heapify( collection, i--, inclusiveFrom, comparator );
				}
			}

			public:
			constexpr static void SelectionSort( CollectionType& collection, const unsigned int inclusiveFrom, const unsigned int exclusiveTo, const ComparatorType& comparator )
			{
				unsigned int minPos;

				for ( unsigned int i = inclusiveFrom; i < exclusiveTo; )
				{
					minPos = i;

					for ( unsigned int j = i + 1; j < exclusiveTo; ++j )
					{
						if ( comparator( collection[i], collection[j] ) > 0 )
						{
							minPos = j;
						}
					}

					Sort<CollectionType>::Swap( collection, i++, minPos );
				}
			}

			public: 
			constexpr static void InsertionSort( CollectionType& collection , const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ComparatorType& comparator )
			{
				unsigned int i = inclusiveFrom + 1;
				unsigned int j;

				if constexpr ( Type<DataType>::IsFundamental )
				{
					DataType key;

					for ( ; i < exclusiveTo;)
					{
						key = collection[i];
						j = i - 1;

						while ( j >= 0 && comparator( collection[j] , key ) > 0 )
						{
							collection[j + 1] = collection[j];
							j = j - 1;
						}
						collection[i++] = key;
					}
				}
				else
				{
					DataType* key;

					for ( ; i < exclusiveTo;)
					{
						key = &collection[i];
						j = i - 1;

						while ( j >= 0 && comparator( collection[j] , ( *key ) ) > 0 )
						{
							collection[j + 1] = collection[j];
							j = j - 1;
						}
						collection[i++] = ( *key );
					}
				}
			}
		
			private:
			constexpr static inline void Swap( CollectionType& collection , const unsigned int pos1 , const unsigned int pos2 )
			{
				DataType temp = collection[pos1];
				collection[pos1] = collection[pos2];
				collection[pos2] = temp;

				return *this;
			}

			private:
			constexpr static void Merge( CollectionType& collection , const unsigned int left , const unsigned int middle , const unsigned int right , const ComparatorType& comparator )
			{
				const unsigned int leftSize = middle - left + 1;
				const unsigned int rightSize = right - middle;
				const unsigned int middleFrom = middle + 1;

				DataType* leftArray = new DataType[leftSize];
				DataType* rightArray = new DataType[rightSize];

				unsigned int i;
				unsigned int j;
				unsigned int k = left;

				for ( i = 0; i < leftSize;)
				{
					leftArray[i++] = collection[left + i];
				}
				for ( j = 0; j < rightSize;)
				{
					rightArray[j++] = collection[middleFrom + j];
				}

				for ( i = 0 , j = 0; i < leftSize && j < rightSize; )
				{
					if ( comparator( leftArray[i] , rightArray[j] ) <= 0 )
					{
						collection[k++] = leftArray[i++];
					}
					else
					{
						collection[k++] = rightArray[j++];
					}
				}

				while ( i < leftSize )
				{
					collection[k++] = leftArray[i++];
				}
				while ( j < rightSize )
				{
					collection[k++] = rightArray[j++];
				}

				delete[] leftArray;
				delete[] rightArray;
			}

			private:
			constexpr static unsigned int Partition( CollectionType& collection , const unsigned int left , const unsigned int right , const ComparatorType comparator )
			{
				const DataType pivot = collection[right];
				unsigned int i = left - 1;

				for ( unsigned int j = left , limit = right - 1; j < limit; ++j )
				{
					if ( comparator( collection[j] , pivot ) < 0 )
					{
						Sort<CollectionType>::Swap( collection , ++i , j );
					}
				}

				Sort<CollectionType>::Swap( collection , i + 1 , right );

				return i + 1;
			}

			private:
			constexpr static void Heapify( CollectionType& collection , const unsigned int size , const unsigned int i , const ComparatorType comparator )
			{
				unsigned int largest = i;
				const unsigned int leftSize = i * 2 + 1;
				const unsigned int rightSize = i * 2 + 2;

				if ( leftSize < size && comparator( collection[leftSize] , collection[largest] ) > 0 )
				{
					largest = leftSize;
				}
				if ( rightSize < size && comparator( collection[rightSize] , collection[largest] ) > 0 )
				{
					largest = rightSize;
				}

				if ( largest != i )
				{
					Sort<CollectionType>::Swap( collection , largest , i );

					Sort<CollectionType>::Heapify( collection , size , largest , comparator );
				}
			}
        };
	}

	class DLLApi Sort
	{		
		public: template<typename CollectionType, typename unsigned int, typename ComparatorType>
		constexpr static void MergeSort( CollectionType& collection, const unsigned int inclusiveFrom, const unsigned int exclusiveTo, const ComparatorType& comparator = Default::Comparator )
		{
			Sort::Validate( collection , inclusiveFrom , exclusiveTo );

			if constexpr ( exclusiveTo - inclusiveFrom < 2 )
			{
				return;
			}

			Implementation::Sort<CollectionType>::MergeSort( collection, inclusiveFrom, exclusiveTo, comparator );
		}

		public: template<typename CollectionType, typename ComparatorType>
		constexpr static void MergeSort( CollectionType& collection, const ComparatorType& comparator = Default::Comparator )
		{
			const auto collectionSize = Adapter::Count( collection );
			if ( collectionSize < 2 )
			{
				return;
			}

			Implementation::Sort<CollectionType>::MergeSort( collection, 0, collectionSize, comparator );
		}

		public: template<typename CollectionType, typename unsigned int, typename ComparatorType>
		constexpr static void QuickSort( CollectionType& collection, const unsigned int inclusiveFrom, const unsigned int exclusiveTo, const ComparatorType& comparator = Default::Comparator )
		{
			Sort::Validate( collection , inclusiveFrom , exclusiveTo );

			if constexpr ( exclusiveTo - inclusiveFrom < 2 )
			{
				return;
			}

			Implementation::Sort<CollectionType>::QuickSort( collection, inclusiveFrom, exclusiveTo, comparator );
		}

		public: template<typename CollectionType, typename ComparatorType>
		constexpr static void QuickSort( CollectionType& collection, const ComparatorType& comparator = Default::Comparator )
		{
			const auto collectionSize = Adapter::Count( collection );
			if ( collectionSize < 2 )
			{
				return;
			}

			Implementation::Sort<CollectionType>::QuickSort( collection, 0, collectionSize, comparator );
		}

		public: template<typename CollectionType, typename unsigned int, typename ComparatorType>
		constexpr static void HeapSort( CollectionType& collection, const unsigned int inclusiveFrom, const unsigned int exclusiveTo, const ComparatorType& comparator = Default::Comparator )
		{ 
			Sort::Validate( collection , inclusiveFrom , exclusiveTo );

			if constexpr ( exclusiveTo - inclusiveFrom < 2 )
			{
				return;
			}

			Implementation::Sort<CollectionType>::HeapSort( collection, inclusiveFrom, exclusiveTo, comparator );
		}

		public: template<typename CollectionType, typename ComparatorType>
		constexpr static void HeapSort( CollectionType& collection, const ComparatorType& comparator = Default::Comparator )
		{
			const auto collectionSize = Adapter::Count( collection );
			if ( collectionSize < 2 )
			{
				return;
			}

			Implementation::Sort<CollectionType>::HeapSort( collection, 0, collectionSize, comparator );
		}

		public: template<typename CollectionType, typename unsigned int, typename ComparatorType>
		constexpr static void SelectionSort( CollectionType& collection, const unsigned int inclusiveFrom, const unsigned int exclusiveTo, const ComparatorType& comparator = Default::Comparator )
		{
			Sort::Validate( collection , inclusiveFrom , exclusiveTo );

			if constexpr ( exclusiveTo - inclusiveFrom < 2 )
			{
				return;
			}

			Implementation::Sort<CollectionType>::SelectionSort( collection, inclusiveFrom, exclusiveTo, comparator );
		}

		public: template<typename CollectionType, typename ComparatorType>
		constexpr static void SelectionSort( CollectionType& collection, const ComparatorType& comparator = Default::Comparator )
		{
			const auto collectionSize = Adapter::Count( collection );
			if ( collectionSize < 2 )
			{
				return;
			}

			Implementation::Sort<CollectionType>::SelectionSort( collection, 0, collectionSize, comparator );
		}

		public: template<typename CollectionType, typename unsigned int, typename ComparatorType>
		constexpr static void InsertionSort( CollectionType& collection, const unsigned int inclusiveFrom, const unsigned int exclusiveTo, const ComparatorType& comparator = Default::Comparator )
		{
			Sort::Validate( collection , inclusiveFrom , exclusiveTo );

			if constexpr ( exclusiveTo - inclusiveFrom < 2 )
			{
				return;
			}

			Implementation::Sort<CollectionType>::InsertionSort( collection, inclusiveFrom, exclusiveTo, comparator );
		}

		public: template<typename CollectionType, typename ComparatorType>
		constexpr static void InsertionSort( CollectionType& collection, const ComparatorType& comparator = Default::Comparator )
		{
			const auto collectionSize = Adapter::Count( collection );
			if ( collectionSize < 2 )
			{
				return;
			}

			Implementation::Sort<CollectionType>::InsertionSort( collection, 0, collectionSize, comparator );
		}
	
		private: template<typename CollectionType>
		constexpr static inline void Validate( const CollectionType& collection , const unsigned int inclusiveFrom , const unsigned int exclusiveTo )
		{
			const auto count = Adapter::Count( collection );

			Validate::IsMore( count , 0 );
			Validate::PositiveRange( inclusiveFrom , exclusiveTo );
			Validate::IsLessOrEqual( exclusiveTo , count );
		}
    };
}