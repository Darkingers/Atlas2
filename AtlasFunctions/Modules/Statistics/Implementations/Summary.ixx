
module;

#include "../../../../Macros/Macros.h"

export module AtlasStatistics:Sum;

import AtlasTypeInfo;
import AtlasIntegration;
import AtlasValidation;
import AtlasConfiguration;

export namespace Atlas
{
	class DLLApi StatisticsSummary
	{
		public: unsigned int Count;
		public: double Average;
		public: double Deviation;
		public: double Minimum;
		public: double Maximum;
		public: double Sum;
	
			
		public: StatisticsSummary( const unsigned int count , const double average , const double deviation , const double minimum , const double maximum , const double sum )
			noexcept
			: Count( count )
			, Average( average )
			, Deviation( deviation )
			, Minimum( minimum )
			, Maximum( maximum )
			, Sum( sum )
		{}
	};

	template<typename CollectionType>
	class DLLApi Summary
	{
		public:
		constexpr static auto Calculate( const CollectionType& collection )
			noexcept( !Configuration::EnableStatisticsSummaryCheck&& Concept::HasNoexceptConstIterator<CollectionType> )
		{
			auto current = Adapter::ConstBegin( collection );
			auto end = Adapter::ConstEnd( collection );

			Validate<Configuration::EnableStatisticsSummaryCheck>::IsNotSame( current , end );
			
			auto sum = Adapter::CurrentValue( current );
			auto count = 1;
			
			auto minimum = sum;
			auto maximum = sum;
			
			for ( Adapter::Iterate( current ); current != end; Adapter::Iterate( current ) )
			{
				auto currentValue = Adapter::CurrentValue( current );
				sum += currentValue;
				++count;

				if ( currentValue < minimum )
				{
					minimum = currentValue;
				}
				else if ( currentValue > maximum )
				{
					maximum = currentValue;
				}
			}

			auto average = sum / count;
			decltype( sum ) deviation = 0;
			decltype( sum ) currentValue = 0;
			
			current = Adapter::ConstBegin( collection );
			for ( Adapter::Iterate( current ); current != end; Adapter::Iterate( current ) )
			{
				currentValue = Adapter::CurrentValue( current );
				deviation += ( currentValue - average ) * ( currentValue - average );
			}
			
			return StatisticsSummary( count , average , deviation / count , minimum , maximum , sum );
		}
	};
}
