module;

#include <string>

#include "../../../Macros/Macros.h"

export module AtlasConverters:LongConverter;

import AtlasConcepts;

import :Converter;

export namespace Atlas::Converters
{
	template<typename SourceType>
		requires Concept::IsConvertibleTo<SourceType , long>
	class DLLApi Converter<SourceType , long> :
		public std::true_type
	{
		public:
		inline static long Convert( const SourceType& data )
		{
			return data;
		}
	};

	template<>
	class DLLApi Converter<std::string , long> :
		public std::true_type
	{
		public:
		inline static long Convert( const std::string& data )
		{
			return std::stol( data );
		}
	};

	template<>
	class DLLApi Converter<const char* , long> :
		public std::true_type
	{
		public:
		inline static long Convert( const char* data )
		{
			return std::atol( data );
		}
	};
}