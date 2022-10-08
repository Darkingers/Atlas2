module;

#include <string>
#include "../../../Macros/Macros.h"

export module AtlasConverters:DoubleConverter;

import AtlasTypeInfo;
import AtlasConcepts;
import AtlasConfiguration;
import AtlasValidation;

import :Converter;

export namespace Atlas::Converters
{
	template<typename SourceType>
		requires Concept::IsConvertibleTo<SourceType,double>
	class DLLApi Converter<SourceType,double> :
		public std::true_type
	{
		public: constexpr static bool IsNoexcept = Type<SourceType>::template IsNoexceptConvertibleTo<double>;
		

		public:
		constexpr inline static double Convert( const SourceType& data ) 
			noexcept( IsNoexcept )
		{
			return data;
		}
	};

	template<>
	class DLLApi Converter<std::string, double> :
		public std::true_type
	{
		public: constexpr static bool IsNoexcept = !Configuration::EnableDoubleConverterCheck;
		private: constexpr inline static double DecimalMultipliers[] = {
			0.1,
			0.01,
			0.001,
			0.0001,
			0.00001,
			0.000001,
			0.0000001,
			0.00000001,
			0.000000001,
			0.0000000001,
			0.00000000001,
			0.000000000001,
			0.0000000000001,
			0.00000000000001,
			0.000000000000001,
			0.0000000000000001,
			0.00000000000000001,
			0.000000000000000001,
			0.0000000000000000001,
			0.00000000000000000001,
			0.000000000000000000001,
			0.0000000000000000000001,
			0.00000000000000000000001,
			0.000000000000000000000001,
			0.0000000000000000000000001,
			0.00000000000000000000000001,
			0.000000000000000000000000001,
			0.0000000000000000000000000001,
			0.00000000000000000000000000001,
			0.000000000000000000000000000001,
			0.0000000000000000000000000000001,
			0.00000000000000000000000000000001,
			0.000000000000000000000000000000001,
			0.0000000000000000000000000000000001,
			0.00000000000000000000000000000000001,
			0.000000000000000000000000000000000001,
			0.0000000000000000000000000000000000001,
			0.00000000000000000000000000000000000001,
			0.000000000000000000000000000000000000001,
			0.0000000000000000000000000000000000000001,
			0.00000000000000000000000000000000000000001,
			0.000000000000000000000000000000000000000001,
			0.0000000000000000000000000000000000000000001,
			0.00000000000000000000000000000000000000000001,
			0.000000000000000000000000000000000000000000001,
			0.0000000000000000000000000000000000000000000001,
			0.00000000000000000000000000000000000000000000001,
			0.000000000000000000000000000000000000000000000001,
			0.0000000000000000000000000000000000000000000000001,
			0.00000000000000000000000000000000000000000000000001,
			0.000000000000000000000000000000000000000000000000001,
		};
		
			
		public:
		constexpr inline static double Convert( const std::string& data )
			noexcept( IsNoexcept )
		{
			double integer = 0;
			double decimal = 0;

			int i = 0;
			int decimalLength = 1;
			int sign = 1;
			int length = data.length( );
			char current;

			if ( data[0] == '-' )
			{
				sign = -1;
				i = 1;
			}

			Validate<Configuration::EnableDoubleConverterCheck>::IsMore( length , i);

			for ( ; i < length;)
			{
				if ( ( current = data[i++] ) == '.' )
				{
					break;
				}
				else
				{
					Validate<Configuration::EnableDoubleConverterCheck>::IsMoreOrEqual( current , '0' );
					Validate<Configuration::EnableDoubleConverterCheck>::IsLessOrEqual( current , '9' );

					integer = integer * 10 + ( current - '0' );
				}
			}

			decimalLength = length - i - 1;

			for ( ; i < length;)
			{
				current = data[i++];
				
				Validate<Configuration::EnableDoubleConverterCheck>::IsMoreOrEqual( current , '0' );
				Validate<Configuration::EnableDoubleConverterCheck>::IsLessOrEqual( current , '9' );

				decimal = decimal * 10 + ( current - '0' );
			}

			return sign * ( integer + decimal * DecimalMultipliers[decimalLength] );
		}
	};

	template<>
	class DLLApi Converter<const char*, double> :
		public std::true_type
	{
		public: constexpr static bool IsNoexcept = !Configuration::EnableDoubleConverterCheck;
		private:  inline static double DecimalMultipliers[] = {
			0.1,
			0.01,
			0.001,
			0.0001,
			0.00001,
			0.000001,
			0.0000001,
			0.00000001,
			0.000000001,
			0.0000000001,
			0.00000000001,
			0.000000000001,
			0.0000000000001,
			0.00000000000001,
			0.000000000000001,
			0.0000000000000001,
			0.00000000000000001,
			0.000000000000000001,
			0.0000000000000000001,
			0.00000000000000000001,
			0.000000000000000000001,
			0.0000000000000000000001,
			0.00000000000000000000001,
			0.000000000000000000000001,
			0.0000000000000000000000001,
			0.00000000000000000000000001,
			0.000000000000000000000000001,
			0.0000000000000000000000000001,
			0.00000000000000000000000000001,
			0.000000000000000000000000000001,
			0.0000000000000000000000000000001,
			0.00000000000000000000000000000001,
			0.000000000000000000000000000000001,
			0.0000000000000000000000000000000001,
			0.00000000000000000000000000000000001,
			0.000000000000000000000000000000000001,
			0.0000000000000000000000000000000000001,
			0.00000000000000000000000000000000000001,
			0.000000000000000000000000000000000000001,
			0.0000000000000000000000000000000000000001,
			0.00000000000000000000000000000000000000001,
			0.000000000000000000000000000000000000000001,
			0.0000000000000000000000000000000000000000001,
			0.00000000000000000000000000000000000000000001,
			0.000000000000000000000000000000000000000000001,
			0.0000000000000000000000000000000000000000000001,
			0.00000000000000000000000000000000000000000000001,
			0.000000000000000000000000000000000000000000000001,
			0.0000000000000000000000000000000000000000000000001,
			0.00000000000000000000000000000000000000000000000001,
			0.000000000000000000000000000000000000000000000000001,
		};
	
			
		public:
		constexpr inline static double Convert( const char* data )
			noexcept( IsNoexcept )
		{
			double integer = 0;
			double decimal = 0;

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
					Validate<Configuration::EnableDoubleConverterCheck>::IsMoreOrEqual( current , '0' );
					Validate<Configuration::EnableDoubleConverterCheck>::IsLessOrEqual( current , '9' );
					
					integer = integer * 10 + ( current - '0' );
				}
			}

			decimalLength = i + 2;

			while ( ( current = data[i++] ) != '\0' )
			{
				Validate<Configuration::EnableDoubleConverterCheck>::IsMoreOrEqual( current , '0' );
				Validate<Configuration::EnableDoubleConverterCheck>::IsLessOrEqual( current , '9' );
				
				decimal = decimal * 10 + ( current - '0' );
			}

			return sign * ( integer + decimal * DecimalMultipliers[i - decimalLength] );
		}
	};
}