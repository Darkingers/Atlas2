module;

#include "../../../Macros/Macros.h"

export module AtlasCollections:Package;
import AtlasValidation;
import AtlasConfiguration;
import AtlasDataFunctions;

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


	template<typename DataType>
	Package<DataType> CreatePackage( const DataType* location , const unsigned int size , bool copy )
	{
		if constexpr ( Configuration::EnableArgumentCheck )
		{
			Ensure::IsPositive( size );
			Ensure::IsNotNull( location );
		}

		if constexpr ( copy )
		{
			Package<DataType> package( size );

			DataFunctions::Copy( location , size , package.Data );

			return package;
		}
		else
		{
			return Package<DataType>( location , size , false );
		}
	}
}