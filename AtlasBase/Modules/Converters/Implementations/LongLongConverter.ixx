module;

#include <string>

#include "../../../../Macros/Macros.h"

export module AtlasConverters:LongLongConverter;

import AtlasConcepts;
import AtlasConfiguration;
import AtlasValidation;
import AtlasIntegration;

export namespace Atlas
{

	template<typename TSource>
		requires Concept::IsConvertibleTo<TSource , long long>
	class DLLApi Converter<TSource , long long> :
		public std::true_type
	{
		public:
		constexpr static inline long long Convert( const TSource& data ) 
			noexcept( Concept::IsNoexceptConvertibleTo<TSource, long long> )
		{
			return data;
		}
	};

	template<>
	class DLLApi Converter<std::string , long long> :
		public std::true_type
	{
		public:
		constexpr static inline long long Convert( const std::string& data )
			noexcept( !Configuration::EnableLongLongConverterCheck )
		{
			long long integer = 0;

			int i = 0;
			int sign = 1;
			auto length = data.length( );
			char current;

			if ( data[0] == '-' )
			{
				sign = -1;
				i = 1;
			}

			Validate<Configuration::EnableLongLongConverterCheck>::IsMore( length , i );

			for ( ; i < length;)
			{
				current = data[i++];
				
				Validate<Configuration::EnableLongLongConverterCheck>::InclusiveRange( current , '0' , '9' );
				
				integer = integer * 10 + ( current - '0' );
			}

			return sign * integer;
		}
	};

	template<>
	class DLLApi Converter<const char* , long long> :
		public std::true_type
	{
		public:
		constexpr static inline long long Convert( const char* data ) 
			noexcept( !Configuration::EnableLongLongConverterCheck )
		{
			long long integer = 0;

			int i = 0;
			int sign = 1;
			char current;

			if ( data[0] == '-' )
			{
				sign = -1;
				i = 1;
			}

			while ( ( current = data[i++] ) != '\0' )
			{
				Validate<Configuration::EnableLongLongConverterCheck>::InclusiveRange( current , '0' , '9' );

				integer = integer * 10 + ( current - '0' );
			}

			return sign * integer;
		}
	};
}