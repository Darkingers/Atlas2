module;

#include <string>

#include "../../../../Macros/Macros.h"

export module AtlasConverters:UnsignedIntConverter;

import AtlasConcepts;
import AtlasConfiguration;
import AtlasValidation;
import AtlasDefinitions;

export namespace Atlas
{
	template<typename TSource> requires 
		Concept::IsConvertibleTo<TSource ,unsigned int>
	class DLLApi TypeConverter<TSource , unsigned int> :
		public std::true_type
	{
		
	public:
		
		constexpr static inline int Convert( const TSource& data )
			noexcept( Concept::IsNoexceptConvertibleTo<TSource , unsigned int> )
		{
			return data;
		}
	};

	template<>
	class DLLApi TypeConverter<std::string , unsigned int> :
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
				
				Validate<Configuration::EnableUnsignedIntConverterCheck>::IsInInclusiveRange( current , '0' , '9' );

				integer = integer * 10 + ( current - '0' );
			}

			return integer;
		}
	};

	template<>
	class DLLApi TypeConverter<const char* , unsigned int> :
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
				Validate<Configuration::EnableUnsignedIntConverterCheck>::IsInInclusiveRange( current , '0' , '9' );

				integer = integer * 10 + ( current - '0' );
			}

			return integer;
		}
	};
}