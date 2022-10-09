module;

#include <string>

#include "../../../Macros/Macros.h"

export module AtlasConverters:UnsignedIntConverter;

import AtlasTypeInfo;
import AtlasConcepts;
import AtlasConfiguration;
import AtlasValidation;

import :Converter;

export namespace Atlas::Converters
{
	template<typename SourceType>
		requires Concept::IsConvertibleTo<SourceType ,unsigned int>
	class DLLApi Converter<SourceType , unsigned int> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = Type<SourceType>::template IsNoexceptConvertibleTo<unsigned int>;
		

		public:
		constexpr inline static int Convert( const SourceType& data )
			noexcept( IsNoexcept )
		{
			return data;
		}
	};

	template<>
	class DLLApi Converter<std::string , unsigned int> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = !Configuration::EnableUnsignedIntConverterCheck;
		

		public:
		constexpr inline static int Convert( const std::string& data ) 
			noexcept( IsNoexcept )
		{
			unsigned int integer = 0;

			int i = 0;
			auto length = data.length( );
			char current;

			Validate<Configuration::EnableUnsignedIntConverterCheck>::IsMore( length , 0 );

			for ( ; i < length;)
			{
				current = data[i++];
				
				Validate<Configuration::EnableUnsignedIntConverterCheck > ::IsMoreOrEqual( current , '0' );
				Validate<Configuration::EnableUnsignedIntConverterCheck>::IsLessOrEqual( current , '9' );

				integer = integer * 10 + ( current - '0' );
			}

			return integer;
		}
	};

	template<>
	class DLLApi Converter<const char* , unsigned int> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = !Configuration::EnableUnsignedIntConverterCheck;
		

		public:
		constexpr inline static int Convert( const char* data ) 
			noexcept( IsNoexcept )
		{
			unsigned int integer = 0;

			int i = 0;
			char current;
			
			while ( ( current = data[i++] ) != '\0' )
			{
				Validate<Configuration::EnableUnsignedIntConverterCheck > ::IsMoreOrEqual( current , '0' );
				Validate<Configuration::EnableUnsignedIntConverterCheck>::IsLessOrEqual( current , '9' );

				integer = integer * 10 + ( current - '0' );
			}

			return integer;
		}
	};
}