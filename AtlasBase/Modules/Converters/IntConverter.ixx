module;

#include <string>

#include "../../../Macros/Macros.h"

export module AtlasConverters:IntConverter;

import AtlasTypeInfo;
import AtlasConcepts;
import AtlasConfiguration;
import AtlasValidation;

import :Converter;

export namespace Atlas::Converters
{
	template<typename SourceType>
		requires Concept::IsConvertibleTo<SourceType , int>
	class DLLApi Converter<SourceType , int> :
		public std::true_type
	{
		public: constexpr static bool IsNoexcept = Type<SourceType>::template IsNoexceptConvertibleTo<int>;
		

		public:
		constexpr inline static int Convert( const SourceType& data )
			noexcept( IsNoexcept )
		{
			return data;
		}
	};

	template<>
	class DLLApi Converter<std::string , int> :
		public std::true_type
	{
		public: constexpr static bool IsNoexcept = !Configuration::EnableIntConverterCheck;
		

		public:
		constexpr inline static int Convert( const std::string& data ) 
			noexcept( IsNoexcept )
		{
			int integer = 0;

			int i = 0;
			int sign = 1;
			int length = data.length( );
			char current;

			if ( data[0] == '-' )
			{
				sign = -1;
				i = 1;
			}

			Validate<Configuration::EnableIntConverterCheck>::IsMore( length , i );

			for ( ; i < length;)
			{
				current = data[i++];
				
				Validate<Configuration::EnableIntConverterCheck>::IsMoreOrEqual( current , '0' );
				Validate<Configuration::EnableIntConverterCheck>::IsLessOrEqual( current , '9' );

				integer = integer * 10 + ( current - '0' );
			}

			return sign * integer;
		}
	};

	template<>
	class DLLApi Converter<const char* , int> :
		public std::true_type
	{
		public: constexpr static bool IsNoexcept = !Configuration::EnableIntConverterCheck;
		

		public:
		constexpr inline static int Convert( const char* data )
			noexcept( IsNoexcept )
		{
			int integer = 0;

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
				Validate<Configuration::EnableIntConverterCheck>::IsMoreOrEqual( current , '0' );
				Validate<Configuration::EnableIntConverterCheck>::IsLessOrEqual( current , '9' );

				integer = integer * 10 + ( current - '0' );
			}

			return sign * integer;
		}
	};
}