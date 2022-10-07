module;

#include "../../../Macros/Macros.h"
#include <string>

export module AtlasConverters:FloatConverter;
import AtlasConcepts;
import :Converter;

export namespace Atlas::Converters
{
	template<typename SourceType>
		requires Concept::IsConvertibleTo<SourceType , float>
	class DLLApi Converter<SourceType , float> :
		public std::true_type
	{
		public:
		inline static float Convert( const SourceType& data )
		{
			return data;
		}
	};

	template<>
	class DLLApi Converter<std::string , float> :
		public std::true_type
	{
		public:
		inline static float Convert( const std::string& data )
		{
			return std::stof( data );
		}
	};

	template<>
	class DLLApi Converter<const char* , float> :
		public std::true_type
	{
		public:
		inline static float Convert( const char* data )
		{
			return std::atof( data );
		}
	};
}