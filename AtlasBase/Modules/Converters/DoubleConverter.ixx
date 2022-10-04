module;

#include "../../../Macros/Macros.h"
#include <string>

export module AtlasConverters:DoubleConverter;
import :Converter;

export namespace Atlas
{
	template<>
	class DLLApi Converter<double>
	{
		public: template<typename DataType>
			requires std::is_convertible_v<DataType , double>
		inline static double Convert( const DataType& data )
		{
			return data;
		}

		public:
		inline static double Convert( const std::string& data )
		{
			return std::stof( data );
		}

		public:
		inline static double Convert( const char* data )
		{
			return std::atof( data );
		}
	};
}