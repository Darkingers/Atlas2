module;

#include "../../../Macros/Macros.h"
#include <string>

export module AtlasConverters:LongConverter;
import :Converter;

export namespace Atlas
{
	template<>
	class DLLApi Converter<long>
	{
		public: template<typename DataType>
			requires std::is_convertible_v<DataType , long>
		inline static long Convert( const DataType& data )
		{
			return data;
		}

		public:
		inline static long Convert( const std::string& data )
		{
			return std::stol( data );
		}

		public:
		inline static long Convert( const char* data )
		{
			return std::atol( data );
		}
	};
}