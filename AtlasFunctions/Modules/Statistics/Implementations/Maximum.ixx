
module;

#include "../../../../Macros/Macros.h"

export module AtlasStatistics:Maximum;

import AtlasTypeInfo;
import AtlasIntegration;
import AtlasValidation;
import AtlasConfiguration;

export namespace Atlas
{
	template<typename TCollection>
	class DLLApi Maximum
	{		
		public:
		constexpr static auto Calculate( const TCollection& collection )
			noexcept( !Configuration::EnableStatisticsMaximumCheck && Concept::HasNoexceptConstIterator<TCollection> )
		{
			auto current = Adapter::ConstBegin( collection );
			auto end = Adapter::ConstEnd( collection );

			Validate<Configuration::EnableStatisticsMaximumCheck>::IsNotSame( current , end );

			auto maximum = Adapter::CurrentValue( current );
			decltype( maximum ) currentValue;

			for ( Adapter::Iterate( current ); current != end; Adapter::Iterate( current ) )
			{
				currentValue = Adapter::CurrentValue( current );
				if ( maximum < currentValue )
				{
					maximum = currentValue;
				}
			}

			return maximum;
		}
		
	};
}
