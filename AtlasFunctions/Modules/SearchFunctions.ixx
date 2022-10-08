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
import AtlasAdapters;

export namespace Atlas
{
	namespace Implementation
	{
		template<typename CollectionType>
		class Search
		{
			private: using DataType = Deduce::CollectionContainedType<CollectionType>;
		    private: using IteratorType = Deduce::ConstBeginIteratorType<CollectionType>;
			private: using ComparatorType = Definition::Comparator<DataType>;

			public:
			constexpr static unsigned int BinarySearch( const CollectionType& collection, const unsigned int inclusiveFrom, const unsigned int exclusiveTo, const DataType value, const ComparatorType comparator )
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
			constexpr static unsigned int LinearSearch( const CollectionType& collection, const unsigned int inclusiveFrom, const unsigned int exclusiveTo, const DataType value , const ComparatorType comparator )
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
			constexpr static unsigned int JumpSearch( const CollectionType& collection,  const unsigned int inclusiveFrom, const unsigned int exclusiveTo, const DataType value , const ComparatorType comparator )
			{
				const unsigned int stepDiff = Math::SquareRoot( exclusiveTo - inclusiveFrom );
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
						current = Math::Minimum( current + stepDiff, exclusiveTo );
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
		constexpr static unsigned int BinarySearch( const CollectionType& collection, const unsigned int inclusiveFrom, const unsigned int exclusiveTo, const DataType& value, const Definition::Comparator<DataType>& comparator = Default::Comparator )
		{
			Search::Validate( collection, inclusiveFrom , exclusiveTo );

			return Implementation::Search<CollectionType>::BinarySearch( collection, inclusiveFrom, exclusiveTo, value, comparator );
		}
		
		public: template<typename CollectionType, typename DataType>
		constexpr static unsigned int BinarySearch( const CollectionType& collection, const DataType& value, const Definition::Comparator<DataType>& comparator = Default::Comparator )
		{
			return Implementation::Search<CollectionType>::BinarySearch( collection, 0, Adapter::Count( collection ), value, comparator );
		}

		public: template<typename CollectionType, typename DataType>
		constexpr static unsigned int LinearSearch( const CollectionType& collection, const unsigned int inclusiveFrom, const unsigned int exclusiveTo, const DataType& value , const Definition::Comparator<DataType>& comparator = Default::Comparator )
		{
			Search::Validate( collection , inclusiveFrom , exclusiveTo );

			return Implementation::Search<CollectionType>::LinearSearch( collection, inclusiveFrom, exclusiveTo, value, comparator );
		}
		
		public: template<typename CollectionType, typename DataType>
		constexpr static unsigned int LinearSearch( const CollectionType& collection, const DataType& value, const Definition::Comparator<DataType>& comparator = Default::Comparator )
		{
			return Implementation::Search<CollectionType>::LinearSearch( collection, 0, Adapter::Count( collection ), value, comparator );
		}

		public: template<typename CollectionType, typename DataType>
		constexpr static unsigned int JumpSearch( const CollectionType& collection, const unsigned int inclusiveFrom, const unsigned int exclusiveTo, const DataType& value , const Definition::Comparator<DataType>& comparator = Default::Comparator )
		{
			Search::Validate( collection , inclusiveFrom , exclusiveTo );

			return Implementation::Search<CollectionType>::JumpSearch( collection, inclusiveFrom, exclusiveTo, value, comparator );
		}
		
		public: template<typename CollectionType, typename DataType>
		constexpr static unsigned int JumpSearch( const CollectionType& collection, const DataType& value, const Definition::Comparator<DataType>& comparator = Default::Comparator )
		{
			return Implementation::Search<CollectionType>::JumpSearch( collection, 0, Adapter::Count( collection ), value, comparator );
		}
	
		private: template<typename CollectionType>
		constexpr inline static void Validate( const CollectionType& collection , const unsigned int inclusiveFrom , const unsigned int exclusiveTo )
		{
			const unsigned int count = Adapter::Count( collection );

			Validate::IsMore( count , 0 );
			Validate::PositiveRange( inclusiveFrom , exclusiveTo );
			Validate::IsLessOrEqual( exclusiveTo , count );
		}
	};
}