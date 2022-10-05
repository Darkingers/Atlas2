module;

#include "../../../Macros/Macros.h"
#include <string>

export module AtlasConverters:StringConverter;
import AtlasConcepts;
import AtlasDefinitions;
import :Converter;

export namespace Atlas::Converters
{
	template<typename SourceType>
		requires Concept::IsConvertibleTo<SourceType , std::string>
	class DLLApi Converter<SourceType , std::string> :
		public std::true_type
	{
		public:
		constexpr inline static std::string Convert( const SourceType& data )
		{
			return data;
		}
	};

	template<>
	class DLLApi Converter<int, std::string> :
		public std::true_type
	{
		public:
		inline static std::string Convert( const int& data )
		{
			return std::to_string( data );
		}
	};

	template<>
	class DLLApi Converter<unsigned int, std::string> :
		public std::true_type
	{
		public:
		inline static std::string Convert( const unsigned int& data )
		{
			return std::to_string( data );
		}
	};

	template<>
	class DLLApi Converter<long , std::string> :
		public std::true_type
	{
		public:
		inline static std::string Convert( const long& data )
		{
			return std::to_string( data );
		}
	};

	template<>
	class DLLApi Converter<unsigned long , std::string> :
		public std::true_type
	{
		public:
		inline static std::string Convert( const unsigned long& data )
		{
			return std::to_string( data );
		}
	};

	template<>
	class DLLApi Converter<long long , std::string> :
		public std::true_type
	{
		public:
		inline static std::string Convert( const long long& data )
		{
			return std::to_string( data );
		}
	};

	template<>
	class DLLApi Converter<unsigned long long , std::string> :
		public std::true_type
	{
		public:
		inline static std::string Convert( const unsigned long long& data )
		{
			return std::to_string( data );
		}
	};
	
	template<>
	class DLLApi Converter<float , std::string> :
		public std::true_type
	{
		public:
		inline static std::string Convert( const float& data )
		{
			return std::to_string( data );
		}
	};

	template<>
	class DLLApi Converter<double , std::string> :
		public std::true_type
	{
		public:
		inline static std::string Convert( const double& data )
		{
			return std::to_string( data );
		}
	};
	
	template<>
	class DLLApi Converter<long double , std::string> :
		public std::true_type
	{
		public:
		inline static std::string Convert( const long double& data )
		{
			return std::to_string( data );
		}
	};

	template<>
	class DLLApi Converter<bool, std::string> :
		public std::true_type
	{
		public:
		inline static std::string Convert( const bool& data )
		{
			return std::to_string( data );
		}
	};

	template<typename SourceType>
		requires Concept::IsPointer<SourceType>
	class DLLApi Converter<SourceType, std::string> :
		public std::true_type
	{
		public:
		inline static std::string Convert( const SourceType* data )
		{
			return std::to_string( reinterpret_cast<unsigned long long>( data ) );
		}
	};

	template<typename SourceType>
		requires Concept::HasToString<SourceType>
	class DLLApi Converter<SourceType , std::string> :
		public std::true_type
	{
		public:
		constexpr inline static std::string Convert( const SourceType& data )
		{
			return data.ToString( );
		}
	};
}