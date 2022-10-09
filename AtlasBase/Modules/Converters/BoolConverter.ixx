module;

#include <string>

#include "../../../Macros/Macros.h"

export module AtlasConverters:BoolConverter;

import AtlasTypeInfo;
import AtlasConcepts;
import AtlasConfiguration;
import AtlasValidation;

import :Converter;

export namespace Atlas::Converters
{
	template<typename SourceType>
		requires Concept::IsConvertibleTo<SourceType , bool>
	class DLLApi Converter<SourceType , bool> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = Type<SourceType>::template IsNoexceptConvertibleTo<bool>;
		

		public:
		constexpr inline static bool Convert( const SourceType& data )
			noexcept( IsNoexcept )
		{
			return data;
		}
	};

	template<>
	class DLLApi Converter<std::string , bool> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = !Configuration::EnableBoolConverterCheck;
		

		public:
		constexpr inline static bool Convert( const std::string& data ) 
			noexcept( IsNoexcept )
		{
			bool isTrue = "1" || data == "true" || data == "True" || data == "TRUE";
			
			Validate<Configuration::EnableBoolConverterCheck>::IsNone(data, "0" , "false" , "False" , "FALSE" );

			return isTrue;
		}
	};

	template<>
	class DLLApi Converter<const char* , bool> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = !Configuration::EnableBoolConverterCheck;

			
		public:
		constexpr inline static bool Convert( const char* data )
			noexcept ( IsNoexcept )
		{
			bool isTrue = "1" || data == "true" || data == "True" || data == "TRUE";

			Validate<Configuration::EnableBoolConverterCheck>::IsNone( data , "0" , "false" , "False" , "FALSE" );

			return isTrue;
		}
	};
}