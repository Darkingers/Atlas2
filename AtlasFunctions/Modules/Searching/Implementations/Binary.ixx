module;

#include "../../../../Macros/Macros.h"

export module AtlasSearching:Binary;

import AtlasTypeInfo;
import AtlasIntegration;
import AtlasValidation;
import AtlasConfiguration;

export namespace Atlas
{
	template<typename TCollection>
	class DLLApi BinarySearch
	{
		private: using DataType = TypeDetails<TCollection>::TElement;

		public: 
		constexpr static auto Search( const TCollection& collection , const DataType& value )
			noexcept( !Configuration::EnableSearchingBinaryCheck && Concept::HasNoexceptConstIterator<TCollection> )
		{
			auto current = Adapter::ConstBegin( collection );
			auto end = Adapter::ConstEnd( collection );

			Validate<Configuration::EnableSearchingBinaryCheck>::IsNotSame( current , end );

			auto middle = Adapter::ConstMiddle( current , end );
			decltype( middle ) middleValue;

			while ( current != end )
			{
				middleValue = Adapter::CurrentValue( middle );
				if ( middleValue == value ) 
				{
					return middle;
				}
				else if ( middleValue < value )
				{
					current = Adapter::ConstNext( middle );
				}
				else
				{
					end = Adapter::ConstPrevious( middle );
				}
				middle = Adapter::ConstMiddle( current , end );
			}

			return end;
		}
	};
}
