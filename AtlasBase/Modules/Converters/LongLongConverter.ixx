module;

#include <string>

#include "../../../Macros/Macros.h"

export module AtlasConverters:LongLongConverter;

import AtlasTypeInfo;
import AtlasConcepts;
import AtlasConfiguration;
import AtlasValidation;

import :Converter;

export namespace Atlas::Converters
{
	template<typename SourceType>
		requires Concept::IsConvertibleTo<SourceType , long long>
	class DLLApi Converter<SourceType , long long> :
		public std::true_type
	{
		public: constexpr static bool IsNoexcept = Type<SourceType>::template IsNoexceptConvertibleTo<long long>;
		

		public:
		constexpr inline static long long Convert( const SourceType& data ) 
			noexcept( IsNoexcept )
		{
			return data;
		}
	};

	template<>
	class DLLApi Converter<std::string , long long> :
		public std::true_type
	{
		public: constexpr static bool IsNoexcept = !Configuration::EnableLongLongConverterCheck;
		
		
		public:
		constexpr inline static long long Convert( const std::string& data )
			noexcept( IsNoexcept )
		{
			long long integer = 0;

			int i = 0;
			int sign = 1;
			int length = data.length( );
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
				
				Validate<Configuration::EnableLongLongConverterCheck>::IsMoreOrEqual( current , '0' );
				Validate<Configuration::EnableLongLongConverterCheck>::IsLessOrEqual( current , '9' );

				integer = integer * 10 + ( current - '0' );
			}

			return sign * integer;
		}
	};

	template<>
	class DLLApi Converter<const char* , long long> :
		public std::true_type
	{
		public: constexpr static bool IsNoexcept = !Configuration::EnableLongLongConverterCheck;
		

		public:
		constexpr inline static long long Convert( const char* data ) 
			noexcept( IsNoexcept )
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
				Validate<Configuration::EnableLongLongConverterCheck > ::IsMoreOrEqual( current , '0' );
				Validate<Configuration::EnableLongLongConverterCheck>::IsLessOrEqual( current , '9' );

				integer = integer * 10 + ( current - '0' );
			}

			return sign * integer;
		}
	};
}