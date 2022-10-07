module;

#include "../../../Macros/Macros.h"
#include <string>

export module AtlasConverters:BoolConverter;
import AtlasConcepts;
import :Converter;

export namespace Atlas::Converters
{
	template<typename SourceType>
		requires Concept::IsConvertibleTo<SourceType , bool>
	class DLLApi Converter<SourceType , bool> :
		public std::true_type
	{
		public:
		inline static bool Convert( const SourceType& data )
		{
			return data;
		}
	};

	template<>
	class DLLApi Converter<std::string , bool> :
		public std::true_type
	{
		public:
		inline static bool Convert( const std::string& data )
		{
			return std::stoi( data );
		}
	};

	template<>
	class DLLApi Converter<const char* , bool> :
		public std::true_type
	{
		public:
		inline static bool Convert( const char* data )
		{
			return std::atoi( data );
		}
	};
}