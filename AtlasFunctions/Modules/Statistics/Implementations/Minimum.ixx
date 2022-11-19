
module;

#include "../../../../Macros/Macros.h"

export module AtlasStatistics:Minimum;

import AtlasTypeInfo;
import AtlasIntegration;
import AtlasValidation;
import AtlasConfiguration;

export namespace Atlas
{
	template<typename CollectionType>
	class DLLApi Minimum
	{
		public:
		constexpr static auto Calculate( const CollectionType& collection )
			noexcept( !Configuration::EnableStatisticsMinimumCheck && Concept::HasNoexceptConstIterator<CollectionType> )
		{
			auto current = Adapter::ConstBegin( collection );
			auto end = Adapter::ConstEnd( collection );

			Validate<Configuration::EnableStatisticsMinimumCheck>::IsNotSame( current , end );

			auto minimum = Adapter::CurrentValue( current );
			decltype( minimum ) currentValue;
			
			for ( Adapter::Iterate( current ); current != end; Adapter::Iterate( current ) )
			{
				currentValue = Adapter::CurrentValue( current );
				if ( currentValue < minimum )
				{
					minimum = currentValue
				}
			}

			return minimum;
		}
	};
}
