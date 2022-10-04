module;

#include "../../../Macros/Macros.h"
#include <string>

export module AtlasConverters:StringConverter;
import AtlasConcepts;
import :Converter;

export namespace Atlas
{
	template<>
	class DLLApi Converter<std::string>
	{
		public: template<typename DataType>
			requires std::is_convertible_v<DataType , std::string>
		inline static std::string Convert( const DataType& data )
		{
			return data;
		}

		public:
		inline static std::string Convert( const int data )
		{
			return std::to_string( data );
		}

		public:
		inline static std::string Convert( const unsigned int data )
		{
			return std::to_string( data );
		}

		public:
		inline static std::string Convert( const long data )
		{
			return std::to_string( data );
		}

		public:
		inline static std::string Convert( const unsigned long data )
		{
			return std::to_string( data );
		}
		
		public:
		inline static std::string Convert( const unsigned long long data )
		{
			return std::to_string( data );
		}

		public:
		inline static std::string Convert( const long long data )
		{
			return std::to_string( data );
		}

		public:
		inline static std::string Convert( const double data )
		{
			return std::to_string( data );
		}

		public:
		inline static std::string Convert( const float data )
		{
			return std::to_string( data );
		}

		public:
		inline static std::string Convert( const long double data )
		{
			return std::to_string( data );
		}

		public: template<typename ConvertedType>
			requires Concept::HasToString<ConvertedType>
		inline static std::string Convert( const ConvertedType& data )
		{
			return data.ToString( );	
		}
		
		public: template<typename... Args>
		inline static std::string Convert( const std::tuple<Args...>& arguments, const std::string delimiter = "," )
		{			
			std::string data = std::get<0>( arguments );

			Converter<std::string>::ConvertImplElement<0>( data , arguments , delimiter );
			
			return data;
		}	

		private: template<unsigned int Index, typename... Args>
		inline static void ConvertImplElement( std::string& data , const std::tuple<Args...>& arguments , const std::string& delimiter )
		{
			data += delimiter + Converter<std::string>::Convert( std::get<Index>( arguments ) );

			if constexpr ( std::tuple_size<std::tuple<Args...>>::value > Index + 1 )
			{
				Converter<std::string>::ConvertImplElement<Index + 1>( data , arguments , delimiter );
			}
		}
	};
}