module;

#include <string>

#include "../../../../Macros/Macros.h"

export module AtlasConverters:UnsignedLongLongConverter;

import AtlasConcepts;
import AtlasConfiguration;
import AtlasValidation;
import AtlasDefinitions;

export namespace Atlas
{
	template<typename TSource> requires 
		Concept::IsConvertibleTo<TSource , unsigned long long>
	class DLLApi TypeConverter<TSource , unsigned long long> :
		public std::true_type
	{

	public:
		
		constexpr static inline unsigned long long Convert( const TSource& data )  
			noexcept( Concept::IsNoexceptConvertibleTo<TSource ,unsigned long long> )
		{
			return data;
		}
	};

	template<>
	class DLLApi TypeConverter<std::string , unsigned long long> :
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
				
				Validate<Configuration::EnableUnsignedLongLongConverterCheck>::IsInInclusiveRange( current , '0' , '9' );

				integer = integer * 10 + ( current - '0' );
			}

			return integer;
		}
	};

	template<>
	class DLLApi TypeConverter<const char* , unsigned long long> :
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
				Validate<Configuration::EnableUnsignedLongLongConverterCheck>::IsInInclusiveRange( current , '0' , '9' );

				integer = integer * 10 + ( current - '0' );
			}
			
			return integer;
		}
	};
}