module;

#include <string>

#include "../../../Macros/Macros.h"

export module AtlasConverters:LongConverter;

import AtlasTypeInfo;
import AtlasConcepts;
import AtlasConfiguration;
import AtlasValidation;

import :Converter;

export namespace Atlas::Converters
{
	template<typename SourceType>
		requires Concept::IsConvertibleTo<SourceType , long>
	class DLLApi Converter<SourceType , long> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = Type<SourceType>::template IsNoexceptConvertibleTo<long>;
		

		public:
		constexpr inline static long Convert( const SourceType& data ) 
			noexcept( IsNoexcept )
		{
			return data;
		}
	};

	template<>
	class DLLApi Converter<std::string , long> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = !Configuration::EnableLongConverterCheck;
		

		public:
		constexpr inline static long Convert( const std::string& data )
			noexcept( IsNoexcept )
		{
			long integer = 0;

			int i = 0;
			int sign = 1;
			auto length = data.length( );
			char current;

			if ( data[0] == '-' )
			{
				sign = -1;
				i = 1;
			}

			Validate<Configuration::EnableLongConverterCheck>::IsMore( length , i );

			for ( ; i < length;)
			{
				current = data[i++];
				
				Validate<Configuration::EnableLongConverterCheck>::IsMoreOrEqual( current , '0' );
				Validate<Configuration::EnableLongConverterCheck>::IsLessOrEqual( current , '9' );

				integer = integer * 10 + ( current - '0' );
			}

			return sign * integer;
		}
	};

	template<>
	class DLLApi Converter<const char* , long> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = !Configuration::EnableLongConverterCheck;
		

		public:
		constexpr inline static long Convert( const char* data ) 
			noexcept( IsNoexcept )
		{
			long integer = 0;

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
				Validate<Configuration::EnableLongConverterCheck>::IsMoreOrEqual( current , '0' );
				Validate<Configuration::EnableLongConverterCheck>::IsLessOrEqual( current , '9' );

				integer = integer * 10 + ( current - '0' );
			}

			return sign * integer;
		}
	};
}