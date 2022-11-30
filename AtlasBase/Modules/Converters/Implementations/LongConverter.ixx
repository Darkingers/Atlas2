module;

#include <string>

#include "../../../../Macros/Macros.h"

export module AtlasConverters:LongConverter;

import AtlasConcepts;
import AtlasConfiguration;
import AtlasValidation;
import AtlasIntegration;

export namespace Atlas
{
	template<typename TSource>
		requires Concept::IsConvertibleTo<TSource , long>
	class DLLApi Converter<TSource , long> :
		public std::true_type
	{
		public:
		constexpr static inline long Convert( const TSource& data ) 
			noexcept( Concept::IsNoexceptConvertibleTo<TSource, long> )
		{
			return data;
		}
	};

	template<>
	class DLLApi Converter<std::string , long> :
		public std::true_type
	{
		public:
		constexpr static inline long Convert( const std::string& data )
			noexcept( !Configuration::EnableLongConverterCheck )
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
				
				Validate<Configuration::EnableLongConverterCheck>::InclusiveRange( current , '0' , '9' );

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
		constexpr static inline long Convert( const char* data ) 
			noexcept( !Configuration::EnableLongConverterCheck )
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
				Validate<Configuration::EnableLongConverterCheck>::InclusiveRange( current , '0' , '9' );

				integer = integer * 10 + ( current - '0' );
			}

			return sign * integer;
		}
	};
}