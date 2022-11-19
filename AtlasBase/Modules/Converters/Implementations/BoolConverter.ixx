module;

#include <string>

#include "../../../../Macros/Macros.h"

export module AtlasConverters:BoolConverter;

import AtlasConcepts;
import AtlasConfiguration;
import AtlasValidation;
import AtlasIntegration;

export namespace Atlas
{
	template<typename SourceType>
		requires Concept::IsConvertibleTo<SourceType , bool>
	class DLLApi Converter<SourceType , bool> :
		public std::true_type
	{
		public:
		constexpr static inline bool Convert( const SourceType& data )
			noexcept( Concept::IsNoexceptConvertibleTo<SourceType, bool> )
		{
			return data;
		}
	};

	template<>
	class DLLApi Converter<std::string , bool> :
		public std::true_type
	{
		public:
		constexpr static inline bool Convert( const std::string& data ) 
			noexcept( !Configuration::EnableBoolConverterCheck)
		{
			bool isTrue = data == Configuration::TrueString;
			
			if constexpr ( Configuration::EnableBoolConverterCheck )
			{
				if ( !isTrue )
				{
					Validate::IsSame( data , Configuration::FalseString );
				}
			}

			return isTrue;
		}
	};

	template<>
	class DLLApi Converter<const char* , bool> :
		public std::true_type
	{
		public:
		constexpr static inline bool Convert( const char* data )
			noexcept ( !Configuration::EnableBoolConverterCheck )
		{
			bool isTrue = data == Configuration::TrueString;

			if constexpr ( Configuration::EnableBoolConverterCheck )
			{
				if(!isTrue )
				{
					Validate::IsSame( data , Configuration::FalseString );
				}
			}

			return isTrue;
		}
	};
}