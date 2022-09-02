module;

#include <iterator>
#include <algorithm>
#include "../../Macros/Macros.h"

export module AtlasSearchFunctions;
import AtlasDefinitions;
import AtlasMathFunctions;
import AtlasDefaultFunctions;
import AtlasValidation;
import AtlasConfiguration;

export namespace Atlas
{
	namespace Implementation
	{
		template<typename CollectionType>
		class Search
		{
			private: using DataType = DeduceCollectionContainedType<CollectionType>;
			private: using IteratorType = DeduceConstBeginIteratorType<CollectionType>;
			private: using ComparatorType = Comparator<DataType>;

			public:
			static unsigned int BinarySearch( const CollectionType& collection, const unsigned int inclusiveFrom, const unsigned int exclusiveTo, const DataType value, const ComparatorType comparator )
			{
				unsigned int low = inclusiveFrom;
				unsigned int high = exclusiveTo;
				unsigned int current;

				while ( low <= high )
				{
					current = ( low + high ) / 2;

					if ( comparator( collection[current], value ) > 0 )
					{
						high = current - 1;
					}
					else if ( comparator( collection[current], value ) < 0 )
					{
						low = current + 1;
					}
					else
					{
						return current;
					}
				}

				return exclusiveTo;
			}

			public:
			static unsigned int LinearSearch( const CollectionType& collection, const unsigned int inclusiveFrom, const unsigned int exclusiveTo, const DataType value , const ComparatorType comparator )
			{
				for ( unsigned int i = 0; i < exclusiveTo; ++i )
				{
					if ( comparator( collection[i], value ) == 0 )
					{
						return i;
					}
				}

				return exclusiveTo;
			}

			public:
			static unsigned int JumpSearch( const CollectionType& collection,  const unsigned int inclusiveFrom, const unsigned int exclusiveTo, const DataType value , const ComparatorType comparator )
			{
				const unsigned int stepDiff = MathFunctions::SquareRoot( exclusiveTo - inclusiveFrom );
				unsigned int current = stepDiff;
				unsigned int previous = inclusiveFrom;

				while ( comparator( collection[current], value ) < 0 )
				{
					if ( current >= exclusiveTo )
					{
						return exclusiveTo;
					}
					else
					{
						previous = current;
						current = MathFunctions::Minimum( current + stepDiff, exclusiveTo );
					}
				}

				while ( comparator( collection[current--], value ) > 0 )
				{
					if ( previous == current )
					{
						return exclusiveTo;
					}
				}

				if ( comparator( collection[current], value ) == 0 )
				{
					return current;
				}
				else
				{
					return exclusiveTo;
				}
			}
		};
	}

	class DLLApi Search
	{
		public: template<typename CollectionType, typename DataType>
		static unsigned int BinarySearch( const CollectionType& collection, const unsigned int inclusiveFrom, const unsigned int exclusiveTo, const DataType& value, const Comparator<DataType>& comparator = Default::Comparator )
		{
			Search::Validate( collection, inclusiveFrom , exclusiveTo );

			return Implementation::Search<CollectionType>::BinarySearch( collection, inclusiveFrom, exclusiveTo, value, comparator );
		}
		
		public: template<typename CollectionType, typename DataType>
		static unsigned int BinarySearch( const CollectionType& collection, const DataType& value, const Comparator<DataType>& comparator = Default::Comparator )
		{
			return Implementation::Search<CollectionType>::BinarySearch( collection, 0, CountAdapter<CollectionType>::Count( collection ), value, comparator );
		}

		public: template<typename CollectionType, typename DataType>
		static unsigned int LinearSearch( const CollectionType& collection, const unsigned int inclusiveFrom, const unsigned int exclusiveTo, const DataType& value , const Comparator<DataType>& comparator = Default::Comparator )
		{
			Search::Validate( collection , inclusiveFrom , exclusiveTo );

			return Implementation::Search<CollectionType>::LinearSearch( collection, inclusiveFrom, exclusiveTo, value, comparator );
		}
		
		public: template<typename CollectionType, typename DataType>
		static unsigned int LinearSearch( const CollectionType& collection, const DataType& value, const Comparator<DataType>& comparator = Default::Comparator )
		{
			return Implementation::Search<CollectionType>::LinearSearch( collection, 0, CountAdapter<CollectionType>::Count( collection ), value, comparator );
		}

		public: template<typename CollectionType, typename DataType>
		static unsigned int JumpSearch( const CollectionType& collection, const unsigned int inclusiveFrom, const unsigned int exclusiveTo, const DataType& value , const Comparator<DataType>& comparator = Default::Comparator )
		{
			Search::Validate( collection , inclusiveFrom , exclusiveTo );

			return Implementation::Search<CollectionType>::JumpSearch( collection, inclusiveFrom, exclusiveTo, value, comparator );
		}
		
		public: template<typename CollectionType, typename DataType>
		static unsigned int JumpSearch( const CollectionType& collection, const DataType& value, const Comparator<DataType>& comparator = Default::Comparator )
		{
			return Implementation::Search<CollectionType>::JumpSearch( collection, 0, CountAdapter<CollectionType>::Count( collection ), value, comparator );
		}
	
		private: template<typename CollectionType>
		inline static void Validate( const CollectionType& collection , const unsigned int inclusiveFrom , const unsigned int exclusiveTo )
		{
			if constexpr ( Configuration::EnableArgumentCheck )
			{
				const unsigned int count = CountAdapter<CollectionType>::Count( collection );

				Ensure::IsMore( count , 0 );
				Ensure::PositiveRange( inclusiveFrom , exclusiveTo );
				Ensure::IsLessOrEqual( exclusiveTo , count );
			}
		}
	};
}