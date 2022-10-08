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
			Validate::IsNotNull( data );
			Validate::IsPositive( size );
		}

		Package( unsigned int size)  :
			Data( new DataType[size] ) ,
			Size( size ) ,
			DeleteData( true )
		{
			Validate::IsPositive( size );
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
		Validate::IsPositive( size );
		Validate::IsNotNull( location );

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