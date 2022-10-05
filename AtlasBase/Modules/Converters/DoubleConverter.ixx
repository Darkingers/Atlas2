module;

#include "../../../Macros/Macros.h"
#include <string>

export module AtlasConverters:DoubleConverter;
import AtlasConcepts;
import :Converter;

export namespace Atlas::Converters
{
	template<typename SourceType>
		requires Concept::IsConvertibleTo<SourceType, double>
	class DLLApi Converter<SourceType,double> :
		public std::true_type
	{
		public:
		constexpr inline static double Convert( const SourceType& data )
		{
			return data;
		}
	};

	template<>
	class DLLApi Converter<std::string, double> :
		public std::true_type
	{
		public:
		inline static double Convert( const std::string& data )
		{
			return std::stod( data );
		}
	};

	template<>
	class DLLApi Converter<const char*, double> :
		public std::true_type
	{
		public:
		inline static double Convert( const char* data )
		{
			return std::atof( data );
		}
	};
}