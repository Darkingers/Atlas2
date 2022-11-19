
module;

#include "../../../../Macros/Macros.h"

export module AtlasStatistics:Sum;

import AtlasTypeInfo;
import AtlasIntegration;
import AtlasValidation;
import AtlasConfiguration;

export namespace Atlas
{
	template<typename CollectionType>
	class DLLApi Sum
	{
		public:
		constexpr static auto Calculate( const CollectionType& collection )
			noexcept( !Configuration::EnableStatisticsSumCheck && Concept::HasNoexceptConstIterator<CollectionType> )
		{
			auto current = Adapter::ConstBegin( collection );
			auto end = Adapter::ConstEnd( collection );

			Validate<Configuration::EnableStatisticsSumCheck>::IsNotSame( current , end );

			auto sum = Adapter::CurrentValue( current );

			for ( Adapter::Iterate( current ); current != end; Adapter::Iterate( current ) )
			{
				sum += Adapter::CurrentValue( current );
			}

			return sum;
		}			
	};
}
