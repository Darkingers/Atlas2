module;

#include "../../../../Macros/Macros.h"

export module AtlasSearching:Binary;

import AtlasTypeInfo;
import AtlasIntegration;
import AtlasValidation;
import AtlasConfiguration;

export namespace Atlas
{
	template<typename CollectionType>
	class DLLApi BinarySearch
	{
		private: using DataType = TypeDetails<CollectionType>::ElementType;

		public: 
		constexpr static auto Search( const CollectionType& collection , const DataType& value )
			noexcept( !Configuration::EnableSearchingBinaryCheck && Concept::HasNoexceptConstIterator<CollectionType> )
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
