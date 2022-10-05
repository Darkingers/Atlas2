module;

#include "../../Macros/Macros.h"
#include <algorithm>

export module AtlasConverters;
import AtlasTypeInfo;
import AtlasDefinitions;

export import :BoolConverter;
export import :Converter;
export import :DoubleConverter;
export import :FloatConverter;
export import :IntConverter;
export import :LongConverter;
export import :LongLongConverter;
export import :StringConverter;

export namespace Atlas
{
	template<typename ConvertedType>
	class DLLApi Convert
	{
		public: template<typename TargetType>
		inline static TargetType To( const ConvertedType& data )
		{
			return Converters::Converter<Simplify<ConvertedType> , Simplify<TargetType>>::Convert( data );
		}

		public: template<typename SourceType>
		inline static ConvertedType From( const SourceType& data )
		{
			return Converters::Converter<Simplify<SourceType> , Simplify<ConvertedType>>::Convert( data );
		}
	};
}

//export namespace Atlas::Converters
//{
//	template<typename SourceType>
//		requires Type<SourceType>::IsTuple
//	class DLLApi Converter<SourceType , std::string> :
//		public std::true_type
//	{
//		public:
//		inline static std::string Convert( const SourceType& data , const std::string& delimiter = "," )
//		{
//			std::string result;
//
//			std::for_each( data , [ &result ]( auto& s )
//			{
//					result += Converters::Converter<Simplify<decltype( data )> , std::string>::Convert( data ) + delimiter;
//			} );
//
//			return result;
//		}
//
//		/*private: template<unsigned int Current, unsigned int End>
//		inline static void ConvertRemainingToString( const SourceType& data , std::string& result , const std::string& delimiter )
//		{
//			result += delimiter + Atlas::Convert<std::string>::From( std::get<Current>( data ) );
//
//			if constexpr ( std::tuple_size<SourceType>::value > 1 )
//			{
//				ConvertRemainingToString<Current + 1 , End>( data , result , delimiter );
//			}
//		}*/
//	};
//}