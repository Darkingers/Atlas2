module;

#include "../../../Macros/Macros.h"
#include <string>

export module AtlasConverters:IntConverter;
import AtlasConcepts;
import :Converter;

export namespace Atlas::Converters
{
	template<typename SourceType>
		requires Concept::IsConvertibleTo<SourceType , int>
	class DLLApi Converter<SourceType , int> :
		public std::true_type
	{
		public:
		constexpr inline static int Convert( const SourceType& data )
		{
			return data;
		}
	};

	template<>
	class DLLApi Converter<std::string , int> :
		public std::true_type
	{
		public:
		inline static int Convert( const std::string& data )
		{
			return std::stoi( data );
		}
	};

	template<>
	class DLLApi Converter<const char* , int> :
		public std::true_type
	{
		public:
		inline static int Convert( const char* data )
		{
			return std::atoi( data );
		}
	};
}