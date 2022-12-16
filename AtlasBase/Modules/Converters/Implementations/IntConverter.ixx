module;

#include <string>

#include "../../../../Macros/Macros.h"

export module AtlasConverters:IntConverter;

import AtlasConcepts;
import AtlasConfiguration;
import AtlasValidation;
import AtlasDefinitions;

export namespace Atlas
{
	template<typename TSource> requires 
		Concept::IsConvertibleTo<TSource , int>
	class DLLApi TypeConverter<TSource , int> :
		public std::true_type
	{
		
	public:
		
		constexpr static inline int Convert( const TSource& data )
			noexcept( Concept::IsNoexceptConvertibleTo<TSource , int> )
		{
			return data;
		}
	};

	template<>
	class DLLApi TypeConverter<std::string , int> :
		public std::true_type
	{
		
	public:
		
		constexpr static inline int Convert( const std::string& data ) 
			noexcept( !Configuration::EnableIntConverterCheck )
		{
			int integer = 0;

			int i = 0;
			int sign = 1;
			auto length = data.length( );
			char current;

			if ( data[0] == '-' )
			{
				sign = -1;
				i = 1;
			}

			Validate<Configuration::EnableIntConverterCheck>::IsMore( length , i );

			for ( ; i < length;)
			{
				current = data[i++];
				
				Validate<Configuration::EnableIntConverterCheck>::IsInInclusiveRange( current , '0' , '9' );

				integer = integer * 10 + ( current - '0' );
			}

			return sign * integer;
		}
	};

	template<>
	class DLLApi TypeConverter<const char* , int> :
		public std::true_type
	{
	
	private:
			
		constexpr static bool IsNoexcept = !Configuration::EnableIntConverterCheck;
		
	public:
		
		constexpr static inline int Convert( const char* data )
			noexcept( !Configuration::EnableIntConverterCheck )
		{
			int integer = 0;

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
				Validate<Configuration::EnableIntConverterCheck>::IsInInclusiveRange( current , '0' , '9' );

				integer = integer * 10 + ( current - '0' );
			}

			return sign * integer;
		}
	};
}