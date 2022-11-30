
module;

#include "../../../../Macros/Macros.h"

export module AtlasStatistics:Average;

import AtlasTypeInfo;
import AtlasIntegration;
import AtlasValidation;
import AtlasConfiguration;

export namespace Atlas
{
	template<typename TCollection>
	class DLLApi Average
	{
		public:
		constexpr static auto Calculate( const TCollection& collection )
			noexcept(  !Configuration::EnableStatisticsAverageCheck && Concept::HasNoexceptConstIterator<TCollection>)
		{
			auto current = Adapter::ConstBegin( collection );
			auto end = Adapter::ConstEnd( collection );

			Validate<Configuration::EnableStatisticsAverageCheck>::IsNotSame( current , end );

			auto sum = Adapter::CurrentValue( current );
			auto count = 1;
			
			for ( Adapter::Iterate( current ); current != end; Adapter::Iterate( current ) )
			{
				sum += Adapter::CurrentValue( current );
				++count;
			}

			return sum / count;
		}
	};
}
