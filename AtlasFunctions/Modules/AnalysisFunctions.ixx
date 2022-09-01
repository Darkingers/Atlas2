module;

#include "../../Macros/Macros.h"

export module AtlasAnalysisFunctions;
import AtlasDefinitions;
import AtlasAdapters;
import AtlasDefaultFunctions;
import AtlasValidation;
import AtlasConfiguration;

export namespace Atlas
{
	namespace Implementation
	{
		template<typename CollectionType>
		class Analysis
		{
			private: using IteratorType = DeduceConstBeginIteratorType<CollectionType>;
			private: using DataType = DeduceCollectionContainedType<CollectionType>;
			private: using ComparatorType = Comparator<DataType>;


			public: 
		    static DataType Maximum( const CollectionType&& collection, const unsigned int inclusiveFrom, const unsigned int exclusiveTo, const ComparatorType comparator )
			{
				IteratorType currentIterator = std::cbegin( collection );
				std::advance( currentIterator, inclusiveFrom );

				DataType max = *currentIterator;
				DataType current;
				unsigned int i = inclusiveFrom;

				for ( std::advance( currentIterator , 1 ) , ++i; i < exclusiveTo; std::advance( currentIterator , 1 ) , ++i )
				{
					current = *currentIterator;

					if ( comparator( max, current ) < 0 )
					{
						max = current;
					}
				}

				return max;
			}	
			public: template<typename ConverterType, typename ConvertResultType> 
			static ConvertResultType Maximum( const CollectionType&& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ConverterType converter, const ComparatorType comparator )
			{
				IteratorType currentIterator = std::cbegin( collection );
				std::advance( currentIterator, inclusiveFrom );

				ConvertResultType max = converter(*currentIterator);
				ConvertResultType current;
				unsigned int i = inclusiveFrom;

				for ( std::advance( currentIterator , 1 ) , ++i; i < exclusiveTo; std::advance( currentIterator , 1 ) , ++i )
				{
					current = converter(*currentIterator);

					if ( comparator( max, current ) < 0 )
					{
						max = current;
					}
				}

				return max;
			}

			public: template<typename ConverterType, typename ConvertResultType> 
			static IteratorType MaximumBy( const CollectionType&& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ComparatorType comparator )
			{
				IteratorType currentIterator = std::cbegin( collection );
				std::advance( currentIterator, inclusiveFrom );

				IteratorType maxIterator = currentIterator;
				ConvertResultType max = *currentIterator;
				ConvertResultType current;
				unsigned int i = inclusiveFrom;

				for ( std::advance( currentIterator , 1 ) , ++i; i < exclusiveTo; std::advance( currentIterator , 1 ) , ++i )
				{
					current = *currentIterator;

					if ( comparator( max, current ) < 0 )
					{
						max = current;
						maxIterator = currentIterator;
					}
				}

				return maxIterator;
			}
			public: template<typename ConverterType, typename ConvertResultType = DeduceReturnType<ConverterType,DataType>>
			static IteratorType MaximumBy( const CollectionType&& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ConverterType converter, const ComparatorType comparator )
			{
				IteratorType currentIterator = std::cbegin( collection );
				std::advance( currentIterator, inclusiveFrom );

				IteratorType maxIterator = currentIterator;
				ConvertResultType max = converter( *currentIterator );
				ConvertResultType current;
				unsigned int i = inclusiveFrom;

				for ( std::advance( currentIterator , 1 ) , ++i; i < exclusiveTo; std::advance( currentIterator , 1 ) , ++i )
				{
					current = converter( *currentIterator );

					if ( comparator( max, current ) < 0 )
					{
						max = current;
						maxIterator = currentIterator;
					}
				}

				return maxIterator;
			}

			public:
			static DataType Minimum( const CollectionType&& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ComparatorType comparator )
			{
				IteratorType currentIterator = std::cbegin( collection );
				std::advance( currentIterator, inclusiveFrom );

				DataType min = *currentIterator;
				DataType current;
				unsigned int i = inclusiveFrom;

				for ( std::advance( currentIterator , 1 ) , ++i; i < exclusiveTo; std::advance( currentIterator , 1 ) , ++i )
				{
					current = *currentIterator;

					if ( comparator( min, current ) > 0 )
					{
						min = current;
					}
				}

				return min;
			}
			public: template<typename ConverterType, typename ConvertResultType>
			static ConvertResultType Minimum( const CollectionType&& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ConverterType converter, const ComparatorType comparator )
			{
				IteratorType currentIterator = std::cbegin( collection );
				std::advance( currentIterator, inclusiveFrom );

				ConvertResultType min = converter( *currentIterator );
				ConvertResultType current;
				unsigned int i = inclusiveFrom;

				for ( std::advance( currentIterator , 1 ) , ++i; i < exclusiveTo; std::advance( currentIterator , 1 ) , ++i )
				{
					current = converter( *currentIterator );

					if ( comparator( min, current ) > 0 )
					{
						min = current;
					}
				}

				return min;
			}

			public: template<typename ConverterType, typename ConvertResultType>
			static IteratorType MinimumBy( const CollectionType&& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ComparatorType comparator )
			{
				IteratorType currentIterator = std::cbegin( collection );
				std::advance( currentIterator, inclusiveFrom );

				IteratorType minIterator = currentIterator;
				ConvertResultType max = *currentIterator;
				ConvertResultType current;
				unsigned int i = inclusiveFrom;

				for ( std::advance( currentIterator , 1 ) , ++i; i < exclusiveTo; std::advance( currentIterator , 1 ) , ++i )
				{
					current = *currentIterator;

					if ( comparator( max, current ) > 0 )
					{
						max = current;
						minIterator = currentIterator;
					}
				}

				return minIterator;
			}
			public: template<typename ConverterType, typename ConvertResultType> 
			static IteratorType MinimumBy( const CollectionType&& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ConverterType converter, const ComparatorType comparator )
			{
				IteratorType currentIterator = std::cbegin( collection );
				std::advance( currentIterator, inclusiveFrom );

				IteratorType minIterator = currentIterator;
				ConvertResultType max = converter( *currentIterator );
				ConvertResultType current;
				unsigned int i = inclusiveFrom;

				for ( std::advance( currentIterator , 1 ) , ++i; i < exclusiveTo; std::advance( currentIterator , 1 ) , ++i )
				{
					current = converter( *currentIterator );

					if ( comparator( max, current ) > 0 )
					{
						max = current;
						minIterator = currentIterator;
					}
				}

				return minIterator;
			}

			public:
			static DataType Sum( const CollectionType&& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo )
			{
				IteratorType currentIterator = std::cbegin( collection );
				std::advance( currentIterator, inclusiveFrom );

				DataType sum = *currentIterator;
				unsigned int i = inclusiveFrom;

				for ( std::advance( currentIterator , 1 ) , ++i; i < exclusiveTo; std::advance( currentIterator , 1 ) , ++i )
				{
					sum += *currentIterator ;
				}

				return sum;
			}
			public: template<typename ConverterType, typename ConvertResultType>
			static ConvertResultType Sum( const CollectionType&& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ConverterType converter )
			{
				IteratorType currentIterator = std::cbegin( collection );
				std::advance( currentIterator, inclusiveFrom );

				ConvertResultType sum = converter(*currentIterator);
				unsigned int i = inclusiveFrom;

				for ( std::advance( currentIterator , 1 ) , ++i; i < exclusiveTo; std::advance( currentIterator , 1 ) , ++i )
				{
					sum += converter(*currentIterator);
				}

				return sum;
			}
			public: 
			static DataType Average( const CollectionType&& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo )
			{
				return Analysis<CollectionType>::Sum(collection, inclusiveFrom, exclusiveTo) / (exclusiveTo - inclusiveFrom + 1);
			}
			public: template<typename ConverterType, typename ConvertResultType> 
		    static ConvertResultType Average( const CollectionType&& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ConverterType converter )
			{
				return Analysis<CollectionType>::Sum( collection, inclusiveFrom, exclusiveTo, converter ) / ( exclusiveTo - inclusiveFrom + 1 );
			}	
		};
	}

	class DLLApi Analysis
	{
		public: template<typename CollectionType, typename DataType = DeduceCollectionContainedType<CollectionType>>
		DataType Maximum( const CollectionType&& collection, const Comparator<DataType> comparator = Default::Comparator )
		{
			const unsigned int count = CountAdapter<CollectionType>::Count( collection );

			Analysis::Validate( count );

			return Implementation::Analysis<CollectionType>::Maximum( collection, 0, count, comparator );
		}
		
		public: template<typename CollectionType, typename DataType = DeduceCollectionContainedType<CollectionType>>
		DataType Maximum( const CollectionType&& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const Comparator<DataType> comparator = Default::Comparator )
		{
			Analysis::Validate( collection , inclusiveFrom , exclusiveTo );

			return Implementation::Analysis<CollectionType>::Maximum( collection, inclusiveFrom, exclusiveTo, comparator );
		}

		public: template<typename CollectionType, typename ConverterType, typename DataType = DeduceCollectionContainedType<CollectionType>, typename ConvertResultType = DeduceReturnType<ConverterType,DataType>>
		ConvertResultType Maximum( const CollectionType&& collection , ConverterType converter , const Comparator<DataType> comparator = Default::Comparator )
		{
			const unsigned int count = CountAdapter<CollectionType>::Count( collection );

			Analysis::Validate( count );

			return Implementation::Analysis<CollectionType>::Maximum( collection , 0 , count , converter , comparator );
		}

		public: template<typename CollectionType, typename ConverterType, typename DataType = DeduceCollectionContainedType<CollectionType>, typename ConvertResultType = DeduceReturnType<ConverterType, DataType>>
		ConvertResultType Maximum( const CollectionType&& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ConverterType converter, const Comparator<DataType> comparator = Default::Comparator )
		{
			Analysis::Validate( collection , inclusiveFrom , exclusiveTo );

			return Implementation::Analysis<CollectionType>::Maximum( collection, inclusiveFrom, exclusiveTo, converter, comparator );
		}		

		public: template<typename CollectionType, typename IteratorType = DeduceConstBeginIteratorType<CollectionType>, typename DataType = DeduceCollectionContainedType<CollectionType>>
		IteratorType MaximumBy( const CollectionType&& collection, const Comparator<DataType> comparator = Default::Comparator )
		{
			const unsigned int count = CountAdapter<CollectionType>::Count( collection );
			
			Analysis::Validate( count );

			return Implementation::Analysis<CollectionType>::MaximumBy( collection, 0, count, comparator );
		}
	
		public: template<typename CollectionType, typename IteratorType = DeduceConstBeginIteratorType<CollectionType>, typename DataType = DeduceCollectionContainedType<CollectionType>>
		IteratorType MaximumBy( const CollectionType&& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const Comparator<DataType> comparator = Default::Comparator )
		{
			Analysis::Validate( collection , inclusiveFrom , exclusiveTo );

			return Implementation::Analysis<CollectionType>::MaximumBy( collection, inclusiveFrom, exclusiveTo, comparator );
		}

		public: template<typename CollectionType, typename ConverterType, typename IteratorType = DeduceConstBeginIteratorType<CollectionType>, typename DataType = DeduceCollectionContainedType<CollectionType>>
		IteratorType MaximumBy( const CollectionType&& collection, const ConverterType converter, const Comparator<DataType> comparator = Default::Comparator )
		{
			const unsigned int count = CountAdapter<CollectionType>::Count( collection );
			
			Analysis::Validate( count );

			return Implementation::Analysis<CollectionType>::MaximumBy( collection, 0,count, converter, comparator );
		}
		
		public: template<typename CollectionType, typename ConverterType, typename IteratorType = DeduceConstBeginIteratorType<CollectionType>, typename DataType = DeduceCollectionContainedType<CollectionType>>
		IteratorType MaximumBy( const CollectionType&& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ConverterType converter, const Comparator<DataType> comparator = Default::Comparator )
		{
			Analysis::Validate( collection , inclusiveFrom , exclusiveTo );

			return Implementation::Analysis<CollectionType>::MaximumBy( collection, inclusiveFrom, exclusiveTo, converter, comparator );
		}

		public: template<typename CollectionType, typename DataType = DeduceCollectionContainedType<CollectionType>>
		DataType Minimum( const CollectionType&& collection, const Comparator<DataType> comparator = Default::Comparator )
		{
			const unsigned int count = CountAdapter<CollectionType>::Count( collection );

			Analysis::Validate( count );

			return Implementation::Analysis<CollectionType>::Minimumn( collection, 0, count, comparator );
		}
		
		public: template<typename CollectionType , typename DataType = DeduceCollectionContainedType<CollectionType>>
		DataType Minimum( const CollectionType&& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const Comparator<DataType> comparator = Default::Comparator )
		{
			Analysis::Validate( collection , inclusiveFrom , exclusiveTo );

			return Implementation::Analysis<CollectionType>::Minimumn( collection, inclusiveFrom, exclusiveTo, comparator );
		}

		public: template<typename CollectionType, typename ConverterType, typename DataType = DeduceCollectionContainedType<CollectionType>, typename ConvertResultType = DeduceReturnType<ConverterType, DataType>>
		ConvertResultType Minimumn( const CollectionType&& collection, const ConverterType converter, const Comparator<DataType> comparator = Default::Comparator )
		{
			const unsigned int count = CountAdapter<CollectionType>::Count( collection );

			Analysis::Validate( count );

			return Implementation::Analysis<CollectionType>::Minimumn( collection, 0, count, converter, comparator );
		}
		
		public: template<typename CollectionType , typename ConverterType , typename DataType = DeduceCollectionContainedType<CollectionType> , typename ConvertResultType = DeduceReturnType<ConverterType , DataType>>
		ConvertResultType Minimumn( const CollectionType&& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ConverterType converter, const Comparator<DataType> comparator = Default::Comparator )
		{
			Analysis::Validate( collection , inclusiveFrom , exclusiveTo );

			return Implementation::Analysis<CollectionType>::Minimumn( collection, inclusiveFrom, exclusiveTo, converter, comparator );
		}

		public: template<typename CollectionType, typename IteratorType = DeduceConstBeginIteratorType<CollectionType>, typename DataType = DeduceCollectionContainedType<CollectionType>>
		IteratorType MinimumBy( const CollectionType&& collection, const Comparator<DataType> comparator = Default::Comparator )
		{
			const unsigned int count = CountAdapter<CollectionType>::Count( collection );

			Analysis::Validate( count );

			return Implementation::Analysis<CollectionType>::MinimumBy( collection, 0, count, comparator );
		}
	
		public: template<typename CollectionType , typename IteratorType = DeduceConstBeginIteratorType<CollectionType> , typename DataType = DeduceCollectionContainedType<CollectionType>>
		IteratorType MinimumBy( const CollectionType&& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const Comparator<DataType> comparator = Default::Comparator )
		{
			Analysis::Validate( collection , inclusiveFrom , exclusiveTo );

			return Implementation::Analysis<CollectionType>::MinimumBy( collection, inclusiveFrom, exclusiveTo, comparator );
		}

		public: template<typename CollectionType, typename ConverterType, typename IteratorType = DeduceConstBeginIteratorType<CollectionType>, typename DataType = DeduceCollectionContainedType<CollectionType>>
		IteratorType MinimumBy( const CollectionType&& collection, const ConverterType converter, const Comparator<DataType> comparator = Default::Comparator )
		{
			const unsigned int count = CountAdapter<CollectionType>::Count( collection );

			Analysis::Validate( count );

			return Implementation::Analysis<CollectionType>::MinimumBy( collection, 0, count, converter, comparator );
		}
		
		public: template<typename CollectionType , typename ConverterType , typename IteratorType = DeduceConstBeginIteratorType<CollectionType> , typename DataType = DeduceCollectionContainedType<CollectionType>>
		IteratorType MinimumBy( const CollectionType&& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ConverterType converter, const Comparator<DataType> comparator = Default::Comparator )
		{
			Analysis::Validate( collection , inclusiveFrom , exclusiveTo );

			return Implementation::Analysis<CollectionType>::MinimumBy( collection, inclusiveFrom, exclusiveTo, converter, comparator );
		}

		public: template<typename CollectionType, typename DataType = DeduceCollectionContainedType<CollectionType>>
		DataType Sum( const CollectionType&& collection )
		{
			const unsigned int count = CountAdapter<CollectionType>::Count( collection );

			Analysis::Validate( count );

			return Implementation::Analysis<CollectionType>::Sum( collection, 0, count);
		}
		
		public: template<typename CollectionType , typename DataType = DeduceCollectionContainedType<CollectionType>>
		DataType Sum( const CollectionType&& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo )
		{
			Analysis::Validate( collection , inclusiveFrom , exclusiveTo );

			return Implementation::Analysis<CollectionType>::Sum( collection, inclusiveFrom, exclusiveTo );
		}

		public: template<typename CollectionType, typename ConverterType, typename DataType = DeduceCollectionContainedType<CollectionType>, typename ConvertResultType = DeduceReturnType<ConverterType, DataType>>
		ConvertResultType Sum( const CollectionType&& collection, const ConverterType converter )
		{
			const unsigned int count = CountAdapter<CollectionType>::Count( collection );

			Analysis::Validate( count );

			return Implementation::Analysis<CollectionType>::Sum( collection, 0, count, converter );
		}
		
		public: template<typename CollectionType , typename ConverterType , typename DataType = DeduceCollectionContainedType<CollectionType> , typename ConvertResultType = DeduceReturnType<ConverterType , DataType>>
		ConvertResultType Sum( const CollectionType&& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const Comparator<DataType> converter )
		{
			Analysis::Validate( collection , inclusiveFrom , exclusiveTo );

			return Implementation::Analysis<CollectionType>::Sum( collection, inclusiveFrom, exclusiveTo, converter );
		}

		public: template<typename CollectionType, typename DataType = DeduceCollectionContainedType<CollectionType>>
		DataType Average( const CollectionType&& collection )
		{
			const unsigned int count = CountAdapter<CollectionType>::Count( collection );

			Analysis::Validate( count );

			return Implementation::Analysis<CollectionType>::Average( collection, 0, count );
		}
		
		public: template<typename CollectionType , typename DataType = DeduceCollectionContainedType<CollectionType>>
		DataType Average( const CollectionType&& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo )
		{
			Analysis::Validate( collection , inclusiveFrom , exclusiveTo );

			return Implementation::Analysis<CollectionType>::Average( collection, inclusiveFrom, exclusiveTo );
		}

		public: template<typename CollectionType, typename ConverterType, typename DataType = DeduceCollectionContainedType<CollectionType>, typename ConvertResultType = DeduceReturnType<ConverterType, DataType>>
		ConvertResultType Average( const CollectionType&& collection, const ConverterType converter )
		{
			const unsigned int count = CountAdapter<CollectionType>::Count( collection );

			Analysis::Validate( count );

			return Implementation::Analysis<CollectionType>::Average( collection, 0, count, converter );
		}
		
		public: template<typename CollectionType , typename ConverterType , typename DataType = DeduceCollectionContainedType<CollectionType> , typename ConvertResultType = DeduceReturnType<ConverterType , DataType>>
		ConvertResultType Average( const CollectionType&& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo ,const Comparator<DataType> converter )
		{
			Analysis::Validate( collection , inclusiveFrom , exclusiveTo );

			return Implementation::Analysis<CollectionType>::Average( collection, inclusiveFrom, exclusiveTo, converter );
		}
	
		private: template<typename CollectionType>
		inline static void Validate( const CollectionType&& collection , const unsigned int inclusiveFrom , const unsigned int exclusiveTo )
		{
			if constexpr ( Configuration::EnableArgumentCheck )
			{
				const unsigned int count = CountAdapter<CollectionType>::Count( collection );
				Ensure::IsMore( count , 0 );
				Ensure::PositiveRange( inclusiveFrom , exclusiveTo );
				Ensure::IsLessOrEqual( exclusiveTo , count );
			}
		}

		private:
		inline static void Validate( const unsigned int count )
		{
			if constexpr ( Configuration::EnableArgumentCheck )
			{
				Ensure::IsMore( count , 0 );
			}
		}

    };
}