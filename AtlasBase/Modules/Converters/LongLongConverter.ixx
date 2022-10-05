module;

#include "../../../Macros/Macros.h"
#include <string>

export module AtlasConverters:LongLongConverter;
import AtlasConcepts;
import :Converter;

export namespace Atlas::Converters
{
	template<typename SourceType>
		requires Concept::IsConvertibleTo<SourceType , long long>
	class DLLApi Converter<SourceType , long long> :
		public std::true_type
	{
		public:
		constexpr inline static long long Convert( const SourceType& data )
		{
			return data;
		}
	};

	template<>
	class DLLApi Converter<std::string , long long> :
		public std::true_type
	{
		public:
		inline static long long Convert( const std::string& data )
		{
			return std::stoll( data );
		}
	};

	template<>
	class DLLApi Converter<const char* , long long> :
		public std::true_type
	{
		public:
		inline static long long Convert( const char* data )
		{
			return std::atoll( data );
		}
	};
}