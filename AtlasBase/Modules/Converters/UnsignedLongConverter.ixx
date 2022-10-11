module;

#include <string>

#include "../../../Macros/Macros.h"

export module AtlasConverters:UnsignedLongConverter;

import AtlasTypeInfo;
import AtlasConcepts;
import AtlasConfiguration;
import AtlasValidation;

import :Converter;

export namespace Atlas::Converters
{
	template<typename SourceType>
		requires Concept::IsConvertibleTo<SourceType , unsigned long>
	class DLLApi Converter<SourceType , unsigned long> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = noexcept( static_cast<unsigned long>( SourceType( ) ) );
		

		public:
		constexpr inline static unsigned long Convert( const SourceType& data )
			noexcept( IsNoexcept )
		{
			return data;
		}
	};

	template<>
	class DLLApi Converter<std::string , unsigned long> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = noexcept( std::stoul( std::string( ) ) );
		

		public:
		constexpr inline static unsigned long Convert( const std::string& data ) 
			noexcept( IsNoexcept )
		{
			unsigned long integer = 0;

			int i = 0;
			auto length = data.length( );
			char current;

			Validate<Configuration::EnableLongConverterCheck>::IsMore( length , 0 );

			for ( ; i < length;)
			{
				current = data[i++];
				
				Validate<Configuration::EnableLongConverterCheck> ::IsMoreOrEqual( current , '0' );
				Validate<Configuration::EnableLongConverterCheck>::IsLessOrEqual( current , '9' );

				integer = integer * 10 + ( current - '0' );
			}

			return integer;
		}
	};

	template<>
	class DLLApi Converter<const char* , unsigned long> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = noexcept( std::stoul( std::declval<const char*>( ) ) );
		

		public:
		constexpr inline static unsigned long Convert( const char* data ) 
			noexcept( IsNoexcept )
		{
			unsigned long integer = 0;

			int i = 0;
			char current;

			while ( ( current = data[i++] ) != '\0' )
			{
				Validate<Configuration::EnableLongConverterCheck> ::IsMoreOrEqual( current , '0' );
				Validate<Configuration::EnableLongConverterCheck>::IsLessOrEqual( current , '9' );

				integer = integer * 10 + ( current - '0' );
			}

			return integer;
		}
	};
}