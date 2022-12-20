module;

#include <string>

#include "../../../../Macros/Macros.h"

export module AtlasConverters:FloatConverter;

import AtlasConcepts;
import AtlasConfiguration;
import AtlasValidation;
import AtlasDefinitions;

export namespace Atlas
{
	template<typename TSource> requires 
		Concept::IsConvertibleTo<TSource , float>
	class DLLApi TypeConverter<TSource , float> :
		public std::true_type
	{	
		
	public:
		
		constexpr static inline float Convert( const TSource& data )
			noexcept( Concept::IsNoexceptConvertibleTo<TSource , float> )
		{
			return data;
		}
	};

	template<>
	class DLLApi TypeConverter<std::string , float> :
		public std::true_type
	{
	
	private:

		constexpr static inline float DecimalMultipliers[] = {
			0.1f,
			0.01f,
			0.001f,
			0.0001f,
			0.00001f,
			0.000001f,
			0.0000001f,
			0.00000001f,
			0.000000001f,
			0.0000000001f,
			0.00000000001f,
			0.000000000001f,
			0.0000000000001f,
			0.00000000000001f,
			0.000000000000001f,
			0.0000000000000001f,
			0.00000000000000001f,
			0.000000000000000001f,
			0.0000000000000000001f,
			0.00000000000000000001f,
			0.000000000000000000001f,
			0.0000000000000000000001f,
			0.00000000000000000000001f,
			0.000000000000000000000001f,
			0.0000000000000000000000001f,
			0.00000000000000000000000001f,
			0.000000000000000000000000001f,
			0.0000000000000000000000000001f,
			0.00000000000000000000000000001f,
			0.000000000000000000000000000001f,
			0.0000000000000000000000000000001f,
			0.00000000000000000000000000000001f,
			0.000000000000000000000000000000001f,
			0.0000000000000000000000000000000001f,
			0.00000000000000000000000000000000001f,
			0.000000000000000000000000000000000001f,
			0.0000000000000000000000000000000000001f,
			0.00000000000000000000000000000000000001f,
			0.000000000000000000000000000000000000001f,
			0.0000000000000000000000000000000000000001f,
			0.00000000000000000000000000000000000000001f,
			0.000000000000000000000000000000000000000001f,
			0.0000000000000000000000000000000000000000001f,
			0.00000000000000000000000000000000000000000001f,
			0.000000000000000000000000000000000000000000001f,
			0.0000000000000000000000000000000000000000000001f,
			0.00000000000000000000000000000000000000000000001f,
			0.000000000000000000000000000000000000000000000001f,
			0.0000000000000000000000000000000000000000000000001f,
			0.00000000000000000000000000000000000000000000000001f,
			0.000000000000000000000000000000000000000000000000001f
		};
			
	public:
		
		constexpr static inline float Convert( const std::string& data ) 
			noexcept( !Configuration::EnableFloatConverterCheck )
		{
			float integer = 0;
			float decimal = 0;

			int i = 0;
			unsigned int decimalLength = 1;
			int sign = 1;
			auto length = data.length( );
			char current;

			if ( data[0] == '-' )
			{
				sign = -1;
				i = 1;
			}

			Validate<Configuration::EnableFloatConverterCheck>::IsMore( length , i );

			for ( ; i < length;)
			{		
				if ( (current = data[i++]) == '.' )
				{
					break;
				}
				else
				{
					Validate<Configuration::EnableFloatConverterCheck>::IsInInclusiveRange( current , '0' , '9' );
					
					integer = integer * 10 + ( current - '0' );
				}
			}

			decimalLength = length - i - 1;

			for ( ; i < length;)
			{
				current = data[i++];
				
				Validate<Configuration::EnableFloatConverterCheck>::IsInInclusiveRange( current , '0' , '9' );
				
				decimal = decimal * 10 + ( current - '0' );
			}

			return sign * ( integer + decimal * DecimalMultipliers[decimalLength] );
		}
	};

	template<>
	class DLLApi TypeConverter<const char* , float> :
		public std::true_type
	{

	private:
	
		constexpr static inline float DecimalMultipliers[] = {
			0.1f,
			0.01f,
			0.001f,
			0.0001f,
			0.00001f,
			0.000001f,
			0.0000001f,
			0.00000001f,
			0.000000001f,
			0.0000000001f,
			0.00000000001f,
			0.000000000001f,
			0.0000000000001f,
			0.00000000000001f,
			0.000000000000001f,
			0.0000000000000001f,
			0.00000000000000001f,
			0.000000000000000001f,
			0.0000000000000000001f,
			0.00000000000000000001f,
			0.000000000000000000001f,
			0.0000000000000000000001f,
			0.00000000000000000000001f,
			0.000000000000000000000001f,
			0.0000000000000000000000001f,
			0.00000000000000000000000001f,
			0.000000000000000000000000001f,
			0.0000000000000000000000000001f,
			0.00000000000000000000000000001f,
			0.000000000000000000000000000001f,
			0.0000000000000000000000000000001f,
			0.00000000000000000000000000000001f,
			0.000000000000000000000000000000001f,
			0.0000000000000000000000000000000001f,
			0.00000000000000000000000000000000001f,
			0.000000000000000000000000000000000001f,
			0.0000000000000000000000000000000000001f,
			0.00000000000000000000000000000000000001f,
			0.000000000000000000000000000000000000001f,
			0.0000000000000000000000000000000000000001f,
			0.00000000000000000000000000000000000000001f,
			0.000000000000000000000000000000000000000001f,
			0.0000000000000000000000000000000000000000001f,
			0.00000000000000000000000000000000000000000001f,
			0.000000000000000000000000000000000000000000001f,
			0.0000000000000000000000000000000000000000000001f,
			0.00000000000000000000000000000000000000000000001f,
			0.000000000000000000000000000000000000000000000001f,
			0.0000000000000000000000000000000000000000000000001f,
			0.00000000000000000000000000000000000000000000000001f,
			0.000000000000000000000000000000000000000000000000001f
		};
					
	public:
		
		constexpr static inline float Convert( const char* data )
			noexcept( !Configuration::EnableFloatConverterCheck )
		{
			float integer = 0;
			float decimal = 0;

			int i = 0;
			int decimalLength = 1;
			int sign = 1;
			char current;

			if ( data[0] == '-' )
			{
				sign = -1;
				i = 1;
			}

			while ( ( current = data[i++] ) != '\0' )
			{
				if ( current == '.' )
				{
					break;
				}
				else
				{
					Validate<Configuration::EnableFloatConverterCheck>::IsInInclusiveRange( current , '0' , '9' );
					
					integer = integer * 10 + ( current - '0' );
				}
			}

			decimalLength = i + 2;

			while ( ( current = data[i++] ) != '\0' )
			{
				Validate<Configuration::EnableFloatConverterCheck>::IsInInclusiveRange( current , '0' , '9' );
				
				decimal = decimal * 10 + ( current - '0' );
			}

			return sign * ( integer + decimal * DecimalMultipliers[i - decimalLength] );
		}
	};
}