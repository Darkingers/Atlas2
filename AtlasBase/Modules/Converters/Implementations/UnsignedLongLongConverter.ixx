module;

#include <string>

#include "../../../../Macros/Macros.h"

export module AtlasConverters:UnsignedLongLongConverter;

import AtlasConcepts;
import AtlasConfiguration;
import AtlasValidation;
import AtlasIntegration;

export namespace Atlas
{
	template<typename SourceType>
		requires Concept::IsConvertibleTo<SourceType , unsigned long long>
	class DLLApi Converter<SourceType , unsigned long long> :
		public std::true_type
	{

		public:
		constexpr static inline unsigned long long Convert( const SourceType& data )  
			noexcept( Concept::IsNoexceptConvertibleTo<SourceType ,unsigned long long> )
		{
			return data;
		}
	};

	template<>
	class DLLApi Converter<std::string , unsigned long long> :
		public std::true_type
	{
		public:
		constexpr static inline unsigned long long Convert( const std::string& data )
			noexcept( !Configuration::EnableUnsignedLongLongConverterCheck )
		{
			unsigned long long integer = 0;

			int i = 0;
			auto length = data.length( );
			char current;

			Validate<Configuration::EnableUnsignedLongLongConverterCheck>::IsMore( length , 0 );

			for ( ; i < length;)
			{
				current = data[i++];
				
				Validate<Configuration::EnableUnsignedLongLongConverterCheck>::InclusiveRange( current , '0' , '9' );

				integer = integer * 10 + ( current - '0' );
			}

			return integer;
		}
	};

	template<>
	class DLLApi Converter<const char* , unsigned long long> :
		public std::true_type
	{
		public:
		constexpr static inline unsigned long long Convert( const char* data ) 
			noexcept( !Configuration::EnableUnsignedLongLongConverterCheck )
		{
			unsigned long long integer = 0;

			int i = 0;
			char current;

			while ( ( current = data[i++] ) != '\0' )
			{
				Validate<Configuration::EnableUnsignedLongLongConverterCheck>::InclusiveRange( current , '0' , '9' );

				integer = integer * 10 + ( current - '0' );
			}
			
			return integer;
		}
	};
}