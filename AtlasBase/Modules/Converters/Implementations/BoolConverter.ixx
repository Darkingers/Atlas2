module;

#include <string>

#include "../../../../Macros/Macros.h"

export module AtlasConverters:BoolConverter;

import AtlasConcepts;
import AtlasConfiguration;
import AtlasValidation;
import AtlasDefinitions;

export namespace Atlas
{
	template<typename TSource> requires 
		Concept::IsConvertibleTo<TSource , bool>
	class DLLApi TypeConverter<TSource , bool> :
		public std::true_type
	{
		
	public:
		
		constexpr static inline bool Convert( const TSource& data )
		{
			return data;
		}
	};

	template<>
	class DLLApi TypeConverter<std::string , bool> :
		public std::true_type
	{
		
	public:
		
		constexpr static inline bool Convert( const std::string& data ) 
		{
			const bool isTrue = data == Configuration::TrueString;
			
			if constexpr ( Configuration::EnableBoolConverterCheck )
			{
				if ( !isTrue )
				{
					Validate<Configuration::EnableBoolConverterCheck>::IsSame( data , Configuration::FalseString );
				}
			}

			return isTrue;
		}
	};

	template<>
	class DLLApi TypeConverter<const char* , bool> :
		public std::true_type
	{
		
	public:
		
		constexpr static inline bool Convert(const char* data)
		{
			const bool isTrue = data == Configuration::TrueString;

			if constexpr ( Configuration::EnableBoolConverterCheck )
			{
				if(!isTrue )
				{
					Validate<Configuration::EnableBoolConverterCheck>::IsSame( data , Configuration::FalseString );
				}
			}

			return isTrue;
		}
	};
}