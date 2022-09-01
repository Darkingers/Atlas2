module;

#include "../../../Macros/Macros.h"

export module AtlasCollections:Package;
import AtlasValidation;
import AtlasConfiguration;

export namespace Atlas
{
	template<typename DataType>
	struct DLLApi Package
	{
		DataType* Data;
		unsigned int Size;
		bool DeleteData;

		Package( DataType* data, unsigned int size, bool deleteData = false )  :
			Data( data ),
			Size( size ),
			DeleteData( deleteData )
		{
			if constexpr ( Configuration::EnableArgumentCheck )
			{
				Ensure::IsNotNull( data );
				Ensure::IsPositive( size );
			}
		}

		Package( unsigned int size)  :
			Data( new DataType[size] ) ,
			Size( size ) ,
			DeleteData( true )
		{
			if constexpr ( Configuration::EnableArgumentCheck )
			{
				Ensure::IsPositive( size );
			}
		}

		~Package()
		{
			if ( DeleteData && Size > 0 )
			{
				delete[] Data;
			}
		}
	};
}