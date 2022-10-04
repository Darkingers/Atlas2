module;

#include "../../../Macros/Macros.h"
#include <string>

export module AtlasConverters:FloatConverter;
import :Converter;

export namespace Atlas
{
	template<>
	class DLLApi Converter<float>
	{
		public: template<typename DataType>
			requires std::is_convertible_v<DataType , float>
		inline static double Convert( const DataType& data )
		{
			return data;
		}

		public:
		inline static float Convert( const std::string& data )
		{
			return std::stof( data );
		}

		public:
		inline static float Convert( const char* data )
		{
			return std::atof( data );
		}
	};
}