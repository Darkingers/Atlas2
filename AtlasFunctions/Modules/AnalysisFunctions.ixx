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
			private: using IteratorType = Deduce::ConstBeginIteratorType<CollectionType>;
			private: using DataType = Deduce::CollectionContainedType<CollectionType>;
			private: using ComparatorType = Definition::Comparator<DataType>;


			public: 
			constexpr inline static DataType Maximum( const CollectionType& collection, const unsigned int inclusiveFrom, const unsigned int exclusiveTo, const ComparatorType& comparator )
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
			constexpr inline static ConvertResultType Maximum( const CollectionType& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ConverterType& converter, const ComparatorType& comparator )
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
			constexpr inline static IteratorType MaximumBy( const CollectionType& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ComparatorType& comparator )
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
			public: template<typename ConverterType, typename ConvertResultType = Deduce::ReturnType<ConverterType,DataType>>
			constexpr inline static IteratorType MaximumBy( const CollectionType& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ConverterType& converter, const ComparatorType& comparator )
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
			constexpr inline static DataType Minimum( const CollectionType& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ComparatorType& comparator )
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
			constexpr inline static ConvertResultType Minimum( const CollectionType& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ConverterType& converter, const ComparatorType& comparator )
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
			constexpr inline static IteratorType MinimumBy( const CollectionType& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ComparatorType& comparator )
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
			constexpr inline static IteratorType MinimumBy( const CollectionType& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ConverterType& converter, const ComparatorType& comparator )
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
			constexpr inline static DataType Sum( const CollectionType& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo )
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
			constexpr inline static ConvertResultType Sum( const CollectionType& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ConverterType& converter )
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
			constexpr inline static DataType Average( const CollectionType&& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo )
			{
				return Analysis<CollectionType>::Sum(collection, inclusiveFrom, exclusiveTo) / (exclusiveTo - inclusiveFrom + 1);
			}
			public: template<typename ConverterType, typename ConvertResultType> 
			constexpr inline static ConvertResultType Average( const CollectionType& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ConverterType& converter )
			{
				return Analysis<CollectionType>::Sum( collection, inclusiveFrom, exclusiveTo, converter ) / ( exclusiveTo - inclusiveFrom + 1 );
			}	
		};
	}

	class DLLApi Analysis
	{
		public: template<typename CollectionType, typename DataType = Deduce::CollectionContainedType<CollectionType>>
		constexpr inline static DataType Maximum( const CollectionType& collection, const Definition::Comparator<DataType>& comparator = Default::Comparator )
		{
			const unsigned int count = Adapter::Count( collection );

			Argument::IsMore( count, 0 );

			return Implementation::Analysis<CollectionType>::Maximum( collection, 0, count, comparator );
		}
		
		public: template<typename CollectionType, typename DataType = Deduce::CollectionContainedType<CollectionType>>
		constexpr inline static DataType Maximum( const CollectionType& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const Definition::Comparator<DataType>& comparator = Default::Comparator )
		{
			Analysis::Validate( collection , inclusiveFrom , exclusiveTo );

			return Implementation::Analysis<CollectionType>::Maximum( collection, inclusiveFrom, exclusiveTo, comparator );
		}

		public: template<typename CollectionType, typename ConverterType, typename DataType = Deduce::CollectionContainedType<CollectionType>, typename ConvertResultType = Deduce::ReturnType<ConverterType,DataType>>
		constexpr inline static ConvertResultType Maximum( const CollectionType& collection , const ConverterType& converter , const Definition::Comparator<DataType>& comparator = Default::Comparator )
		{
			const unsigned int count = Adapter::Count( collection );

			Argument::IsMore( count , 0 );

			return Implementation::Analysis<CollectionType>::Maximum( collection , 0 , count , converter , comparator );
		}

		public: template<typename CollectionType, typename ConverterType, typename DataType = Deduce::CollectionContainedType<CollectionType>, typename ConvertResultType = Deduce::ReturnType<ConverterType, DataType>>
		constexpr inline static ConvertResultType Maximum( const CollectionType& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ConverterType& converter, const Definition::Comparator<DataType>& comparator = Default::Comparator )
		{
			Analysis::Validate( collection , inclusiveFrom , exclusiveTo );

			return Implementation::Analysis<CollectionType>::Maximum( collection, inclusiveFrom, exclusiveTo, converter, comparator );
		}		

		public: template<typename CollectionType, typename IteratorType = Deduce::ConstBeginIteratorType<CollectionType>, typename DataType = Deduce::CollectionContainedType<CollectionType>>
		constexpr inline static IteratorType MaximumBy( const CollectionType& collection, const Definition::Comparator<DataType>& comparator = Default::Comparator )
		{
			const unsigned int count = Adapter::Count( collection );
			
			Argument::IsMore( count , 0 );

			return Implementation::Analysis<CollectionType>::MaximumBy( collection, 0, count, comparator );
		}
	
		public: template<typename CollectionType, typename IteratorType = Deduce::ConstBeginIteratorType<CollectionType>, typename DataType = Deduce::CollectionContainedType<CollectionType>>
		constexpr inline static IteratorType MaximumBy( const CollectionType& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const Definition::Comparator<DataType>& comparator = Default::Comparator )
		{
			Analysis::Validate( collection , inclusiveFrom , exclusiveTo );

			return Implementation::Analysis<CollectionType>::MaximumBy( collection, inclusiveFrom, exclusiveTo, comparator );
		}

		public: template<typename CollectionType, typename ConverterType, typename IteratorType = Deduce::ConstBeginIteratorType<CollectionType>, typename DataType = Deduce::CollectionContainedType<CollectionType>>
		constexpr inline static IteratorType MaximumBy( const CollectionType& collection, const ConverterType& converter, const Definition::Comparator<DataType>& comparator = Default::Comparator )
		{
			const unsigned int count = Adapter::Count( collection );
			
			Argument::IsMore( count, 0 );

			return Implementation::Analysis<CollectionType>::MaximumBy( collection, 0,count, converter, comparator );
		}
		
		public: template<typename CollectionType, typename ConverterType, typename IteratorType = Deduce::ConstBeginIteratorType<CollectionType>, typename DataType = Deduce::CollectionContainedType<CollectionType>>
		constexpr inline static IteratorType MaximumBy( const CollectionType& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ConverterType& converter, const Definition::Comparator<DataType>& comparator = Default::Comparator )
		{
			Analysis::Validate( collection , inclusiveFrom , exclusiveTo );

			return Implementation::Analysis<CollectionType>::MaximumBy( collection, inclusiveFrom, exclusiveTo, converter, comparator );
		}

		public: template<typename CollectionType, typename DataType = Deduce::CollectionContainedType<CollectionType>>
		constexpr inline static DataType Minimum( const CollectionType& collection, const Definition::Comparator<DataType>& comparator = Default::Comparator )
		{
			const unsigned int count = Adapter::Count( collection );

			Argument::IsMore( count, 0 );

			return Implementation::Analysis<CollectionType>::Minimumn( collection, 0, count, comparator );
		}
		
		public: template<typename CollectionType , typename DataType = Deduce::CollectionContainedType<CollectionType>>
		constexpr inline static DataType Minimum( const CollectionType& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const Definition::Comparator<DataType>& comparator = Default::Comparator )
		{
			Analysis::Validate( collection , inclusiveFrom , exclusiveTo );

			return Implementation::Analysis<CollectionType>::Minimumn( collection, inclusiveFrom, exclusiveTo, comparator );
		}

		public: template<typename CollectionType, typename ConverterType, typename DataType = Deduce::CollectionContainedType<CollectionType>, typename ConvertResultType = Deduce::ReturnType<ConverterType, DataType>>
		constexpr inline static ConvertResultType Minimumn( const CollectionType& collection, const ConverterType& converter, const Definition::Comparator<DataType>& comparator = Default::Comparator )
		{
			const unsigned int count = Adapter::Count( collection );

			Argument::IsMore( count, 0 );

			return Implementation::Analysis<CollectionType>::Minimumn( collection, 0, count, converter, comparator );
		}
		
		public: template<typename CollectionType , typename ConverterType , typename DataType = Deduce::CollectionContainedType<CollectionType> , typename ConvertResultType = Deduce::ReturnType<ConverterType , DataType>>
		constexpr inline static ConvertResultType Minimumn( const CollectionType& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ConverterType& converter, const Definition::Comparator<DataType>& comparator = Default::Comparator )
		{
			Analysis::Validate( collection , inclusiveFrom , exclusiveTo );

			return Implementation::Analysis<CollectionType>::Minimumn( collection, inclusiveFrom, exclusiveTo, converter, comparator );
		}

		public: template<typename CollectionType, typename IteratorType = Deduce::ConstBeginIteratorType<CollectionType>, typename DataType = Deduce::CollectionContainedType<CollectionType>>
		constexpr inline static IteratorType MinimumBy( const CollectionType& collection, const Definition::Comparator<DataType>& comparator = Default::Comparator )
		{
			const unsigned int count = Adapter::Count( collection );

			Argument::IsMore( count, 0 );

			return Implementation::Analysis<CollectionType>::MinimumBy( collection, 0, count, comparator );
		}
	
		public: template<typename CollectionType , typename IteratorType = Deduce::ConstBeginIteratorType<CollectionType> , typename DataType = Deduce::CollectionContainedType<CollectionType>>
		constexpr inline static IteratorType MinimumBy( const CollectionType&& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const Definition::Comparator<DataType>& comparator = Default::Comparator )
		{
			Analysis::Validate( collection , inclusiveFrom , exclusiveTo );

			return Implementation::Analysis<CollectionType>::MinimumBy( collection, inclusiveFrom, exclusiveTo, comparator );
		}

		public: template<typename CollectionType, typename ConverterType, typename IteratorType = Deduce::ConstBeginIteratorType<CollectionType>, typename DataType = Deduce::CollectionContainedType<CollectionType>>
		constexpr inline static IteratorType MinimumBy( const CollectionType& collection, const ConverterType& converter, const Definition::Comparator<DataType>& comparator = Default::Comparator )
		{
			const unsigned int count = Adapter::Count( collection );

			Argument::IsMore( count, 0 );

			return Implementation::Analysis<CollectionType>::MinimumBy( collection, 0, count, converter, comparator );
		}
		
		public: template<typename CollectionType , typename ConverterType , typename IteratorType = Deduce::ConstBeginIteratorType<CollectionType> , typename DataType = Deduce::CollectionContainedType<CollectionType>>
		constexpr inline static IteratorType MinimumBy( const CollectionType& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ConverterType& converter, const Definition::Comparator<DataType>& comparator = Default::Comparator )
		{
			Analysis::Validate( collection , inclusiveFrom , exclusiveTo );

			return Implementation::Analysis<CollectionType>::MinimumBy( collection, inclusiveFrom, exclusiveTo, converter, comparator );
		}

		public: template<typename CollectionType, typename DataType = Deduce::CollectionContainedType<CollectionType>>
		constexpr inline static DataType Sum( const CollectionType& collection )
		{
			const unsigned int count = Adapter::Count( collection );

			Argument::IsMore( count, 0 );

			return Implementation::Analysis<CollectionType>::Sum( collection, 0, count);
		}
		
		public: template<typename CollectionType , typename DataType = Deduce::CollectionContainedType<CollectionType>>
		constexpr inline static DataType Sum( const CollectionType& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo )
		{
			Analysis::Validate( collection , inclusiveFrom , exclusiveTo );

			return Implementation::Analysis<CollectionType>::Sum( collection, inclusiveFrom, exclusiveTo );
		}

		public: template<typename CollectionType, typename ConverterType, typename DataType = Deduce::CollectionContainedType<CollectionType>, typename ConvertResultType = Deduce::ReturnType<ConverterType, DataType>>
		constexpr inline static ConvertResultType Sum( const CollectionType& collection, const ConverterType& converter )
		{
			const unsigned int count = Adapter::Count( collection );

			Argument::IsMore( count, 0 );

			return Implementation::Analysis<CollectionType>::Sum( collection, 0, count, converter );
		}
		
		public: template<typename CollectionType , typename ConverterType , typename DataType = Deduce::CollectionContainedType<CollectionType> , typename ConvertResultType = Deduce::ReturnType<ConverterType , DataType>>
		constexpr inline static ConvertResultType Sum( const CollectionType& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const Definition::Comparator<DataType>& converter )
		{
			Analysis::Validate( collection , inclusiveFrom , exclusiveTo );

			return Implementation::Analysis<CollectionType>::Sum( collection, inclusiveFrom, exclusiveTo, converter );
		}

		public: template<typename CollectionType, typename DataType = Deduce::CollectionContainedType<CollectionType>>
		constexpr inline static DataType Average( const CollectionType& collection )
		{
			const unsigned int count = Adapter::Count( collection );

			Argument::IsMore( count, 0 );

			return Implementation::Analysis<CollectionType>::Average( collection, 0, count );
		}
		
		public: template<typename CollectionType , typename DataType = Deduce::CollectionContainedType<CollectionType>>
		constexpr inline static DataType Average( const CollectionType& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo )
		{
			Analysis::Validate( collection , inclusiveFrom , exclusiveTo );

			return Implementation::Analysis<CollectionType>::Average( collection, inclusiveFrom, exclusiveTo );
		}

		public: template<typename CollectionType, typename ConverterType, typename DataType = Deduce::CollectionContainedType<CollectionType>, typename ConvertResultType = Deduce::ReturnType<ConverterType, DataType>>
		constexpr inline static ConvertResultType Average( const CollectionType& collection, const ConverterType& converter )
		{
			const unsigned int count = Adapter::Count( collection );

			Argument::IsMore( count, 0 );

			return Implementation::Analysis<CollectionType>::Average( collection, 0, count, converter );
		}
		
		public: template<typename CollectionType , typename ConverterType , typename DataType = Deduce::CollectionContainedType<CollectionType> , typename ConvertResultType = Deduce::ReturnType<ConverterType , DataType>>
		constexpr inline static ConvertResultType Average( const CollectionType& collection, const unsigned int inclusiveFrom , const unsigned int exclusiveTo ,const Definition::Comparator<DataType>& converter )
		{
			Analysis::Validate( collection , inclusiveFrom , exclusiveTo );

			return Implementation::Analysis<CollectionType>::Average( collection, inclusiveFrom, exclusiveTo, converter );
		}
	
		private: template<typename CollectionType>
		constexpr inline static void Validate( const CollectionType& collection , const unsigned int inclusiveFrom , const unsigned int exclusiveTo )
		{
			const auto count = Adapter::Count( collection );
			Argument::IsMore( count , 0 );
			Argument::PositiveRange( inclusiveFrom , exclusiveTo );
			Argument::IsLessOrEqual( exclusiveTo , count );
		}
    };
}