module;

#include <string>

#include "../../../../Macros/Macros.h"

export module AtlasConverters:UnsignedIntConverter;

import AtlasConcepts;
import AtlasConfiguration;
import AtlasValidation;
import AtlasIntegration;

export namespace Atlas
{
	template<typename SourceType>
		requires Concept::IsConvertibleTo<SourceType ,unsigned int>
	class DLLApi Converter<SourceType , unsigned int> :
		public std::true_type
	{
		public:
		constexpr static inline int Convert( const SourceType& data )
			noexcept( Concept::IsNoexceptConvertibleTo<SourceType , unsigned int> )
		{
			return data;
		}
	};

	template<>
	class DLLApi Converter<std::string , unsigned int> :
		public std::true_type
	{
		public:
		constexpr static inline int Convert( const std::string& data ) 
			noexcept( !Configuration::EnableUnsignedIntConverterCheck )
		{
			unsigned int integer = 0;

			int i = 0;
			auto length = data.length( );
			char current;

			Validate<Configuration::EnableUnsignedIntConverterCheck>::IsMore( length , 0 );

			for ( ; i < length;)
			{
				current = data[i++];
				
				Validate<Configuration::EnableUnsignedIntConverterCheck>::InclusiveRange( current , '0' , '9' );

				integer = integer * 10 + ( current - '0' );
			}

			return integer;
		}
	};

	template<>
	class DLLApi Converter<const char* , unsigned int> :
		public std::true_type
	{
		public:
		constexpr static inline int Convert( const char* data ) 
			noexcept( !Configuration::EnableUnsignedIntConverterCheck )
		{
			unsigned int integer = 0;

			int i = 0;
			char current;
			
			while ( ( current = data[i++] ) != '\0' )
			{
				Validate<Configuration::EnableUnsignedIntConverterCheck>::InclusiveRange( current , '0' , '9' );

				integer = integer * 10 + ( current - '0' );
			}

			return integer;
		}
	};
}