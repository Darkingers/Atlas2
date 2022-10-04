module;

#include "../../../Macros/Macros.h"
#include <string>

export module AtlasConverters:LongLongConverter;
import :Converter;

export namespace Atlas
{
	template<>
	class DLLApi Converter<long long>
	{
		public: template<typename DataType>
			requires std::is_convertible_v<DataType , long long>
		inline static long long Convert( const DataType& data )
		{
			return data;
		}

		public:
		inline static long long Convert( const std::string& data )
		{
			return std::stoll( data );
		}

		public:
		inline static long long Convert( const char* data )
		{
			return std::atoll( data );
		}
	};
}