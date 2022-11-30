
module;

#include "../../../../Macros/Macros.h"

export module AtlasStatistics:Deviation;

import AtlasTypeInfo;
import AtlasIntegration;
import AtlasValidation;
import AtlasConfiguration;

export namespace Atlas
{
	template<typename TCollection>
	class DLLApi Deviation
	{
		public:
		constexpr static auto Calculate( const TCollection& collection )
			noexcept( !Configuration::EnableStatisticsDeviationCheck && Concept::HasNoexceptConstIterator<TCollection> )
		{
			auto current = Adapter::ConstBegin( collection );
			auto end = Adapter::ConstEnd( collection );

			Validate<Configuration::EnableStatisticsDeviationCheck>::IsNotSame( current , end );

			auto sum = Adapter::CurrentValue( current );
			auto count = 1;

			for ( Adapter::Iterate( current ); current != end; Adapter::Iterate( current ) )
			{
				sum += Adapter::CurrentValue( current );
				++count;
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

			return deviation / count;
		}
	};
}
