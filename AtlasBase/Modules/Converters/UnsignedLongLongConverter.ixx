module;

#include <string>

#include "../../../Macros/Macros.h"

export module AtlasConverters:UnsignedLongLongConverter;

import AtlasTypeInfo;
import AtlasConcepts;
import AtlasConfiguration;
import AtlasValidation;

import :Converter;

export namespace Atlas::Converters
{
	template<typename SourceType>
		requires Concept::IsConvertibleTo<SourceType , unsigned long long>
	class DLLApi Converter<SourceType , unsigned long long> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = noexcept( static_cast<unsigned long long>( Type<SourceType>::Instance( ) ) );

		
		public:
		constexpr inline static unsigned long long Convert( const SourceType& data )  
			noexcept( IsNoexcept )
		{
			return data;
		}
	};

	template<>
	class DLLApi Converter<std::string , unsigned long long> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = noexcept( std::stoull( Type<std::string>::Instance( ) ));

		
		public:
		constexpr inline static unsigned long long Convert( const std::string& data )
			noexcept( IsNoexcept )
		{
			unsigned long long integer = 0;

			int i = 0;
			auto length = data.length( );
			char current;

			Validate<Configuration::EnableUnsignedLongLongConverterCheck>::IsMore( length , 0 );

			for ( ; i < length;)
			{
				current = data[i++];
				
				Validate<Configuration::EnableUnsignedLongLongConverterCheck > ::IsMoreOrEqual( current , '0' );
				Validate<Configuration::EnableUnsignedLongLongConverterCheck>::IsLessOrEqual( current , '9' );

				integer = integer * 10 + ( current - '0' );
			}

			return integer;
		}
	};

	template<>
	class DLLApi Converter<const char* , unsigned long long> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = noexcept( std::stoull( Type<const char*>::Instance( ) ) );
		

		public:
		constexpr inline static unsigned long long Convert( const char* data ) 
			noexcept( IsNoexcept )
		{
			unsigned long long integer = 0;

			int i = 0;
			char current;

			while ( ( current = data[i++] ) != '\0' )
			{
				Validate<Configuration::EnableUnsignedLongLongConverterCheck > ::IsMoreOrEqual( current , '0' );
				Validate<Configuration::EnableUnsignedLongLongConverterCheck>::IsLessOrEqual( current , '9' );

				integer = integer * 10 + ( current - '0' );
			}

			return integer;
		}
	};
}