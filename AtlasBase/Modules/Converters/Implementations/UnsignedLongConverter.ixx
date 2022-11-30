module;

#include <string>

#include "../../../../Macros/Macros.h"

export module AtlasConverters:UnsignedLongConverter;

import AtlasConcepts;
import AtlasConfiguration;
import AtlasValidation;
import AtlasIntegration;

export namespace Atlas
{
	template<typename TSource>
		requires Concept::IsConvertibleTo<TSource , unsigned long>
	class DLLApi Converter<TSource , unsigned long> :
		public std::true_type
	{
		public:
		constexpr static inline unsigned long Convert( const TSource& data )
			noexcept( Concept::IsNoexceptConvertibleTo<TSource , unsigned long> )
		{
			return data;
		}
	};

	template<>
	class DLLApi Converter<std::string , unsigned long> :
		public std::true_type
	{
		public:
		constexpr static inline unsigned long Convert( const std::string& data ) 
			noexcept( !Configuration::EnableUnsignedLongConverterCheck )
		{
			unsigned long integer = 0;

			int i = 0;
			auto length = data.length( );
			char current;

			Validate<Configuration::EnableUnsignedLongConverterCheck>::IsMore( length , 0 );

			for ( ; i < length;)
			{
				current = data[i++];
				
				Validate<Configuration::EnableUnsignedLongConverterCheck>::InclusiveRange( current , '0' , '9' );

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
		constexpr static inline unsigned long Convert( const char* data ) 
			noexcept( !Configuration::EnableUnsignedLongConverterCheck )
		{
			unsigned long integer = 0;

			int i = 0;
			char current;

			while ( ( current = data[i++] ) != '\0' )
			{
				Validate<Configuration::EnableUnsignedLongConverterCheck>::InclusiveRange( current , '0' , '9' );

				integer = integer * 10 + ( current - '0' );
			}

			return integer;
		}
	};
}