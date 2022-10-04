module;

#include "../../../Macros/Macros.h"
#include <string>

export module AtlasConverters:IntConverter;
import :Converter;

export namespace Atlas
{
	template<>
	class DLLApi Converter<int>
	{
		public: template<typename DataType>
			requires std::is_convertible_v<DataType , int>
		inline static int Convert( const DataType& data )
		{
			return data;
		}

		public:
		inline static int Convert( const std::string& data )
		{
			return std::stoi( data );
		}

		public:
		inline static int Convert( const char* data )
		{
			return std::atoi( data );
		}
	};
}