module;

#include <string>

#include "../../../Macros/Macros.h"

export module AtlasConverters:StringConverter;

import AtlasTypeInfo;
import AtlasConcepts;
import AtlasDefinitions;

import :Converter;

export namespace Atlas::Converters
{
	template<typename SourceType>
	class DLLApi Converter<SourceType* , std::string> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = noexcept( std::to_string( std::declval<unsigned long long>( ) ) );

			
		public:
		inline static std::string Convert( const SourceType data ) 
			noexcept( IsNoexcept )
		{
			return std::to_string( reinterpret_cast<unsigned long long>( data ) );
		}
	};

	template<typename SourceType>
		requires Concept::HasToString<SourceType>
	class DLLApi Converter<SourceType , std::string> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = noexcept( std::declval<SourceType>( ).ToString( ));

		
		public:
		inline static std::string Convert( const SourceType& data ) 
			noexcept( IsNoexcept )
		{
			return data.ToString( );
		}
	};

	template<>
	class DLLApi Converter<void* , std::string> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = noexcept( std::to_string( std::declval<unsigned long long>( )) );
		

		public:
		inline static std::string Convert( const void* data ) 
			noexcept( IsNoexcept )
		{
			return std::to_string( reinterpret_cast<unsigned long long>( data ) );
		}
	};

	template<>
	class DLLApi Converter<int, std::string> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = noexcept( std::to_string( std::declval<int>( ) ) );

		public:
		inline static std::string Convert( const int& data )
			noexcept( IsNoexcept )
		{
			return std::to_string( data );
		}
	};

	template<>
	class DLLApi Converter<unsigned int, std::string> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = noexcept( std::to_string( std::declval<unsigned int>( ) ));
		

		public:
		inline static std::string Convert( const unsigned int& data )
			noexcept( IsNoexcept )
		{
			return std::to_string( data );
		}
	};

	template<>
	class DLLApi Converter<long , std::string> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = noexcept( std::to_string( std::declval<long>( ) ));
		

		public:
		inline static std::string Convert( const long& data )
			noexcept( IsNoexcept )
		{
			return std::to_string( data );
		}
	};

	template<>
	class DLLApi Converter<unsigned long , std::string> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = noexcept( std::to_string( std::declval<unsigned long>( ) ) );
		

		public:
		inline static std::string Convert( const unsigned long& data )
			noexcept( IsNoexcept )
		{
			return std::to_string( data );
		}
	};

	template<>
	class DLLApi Converter<long long , std::string> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = noexcept( std::to_string( std::declval<long long>( ) ) );
		

		public:
		inline static std::string Convert( const long long& data )
			noexcept( IsNoexcept )
		{
			return std::to_string( data );
		}
	};

	template<>
	class DLLApi Converter<unsigned long long , std::string> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = noexcept( std::to_string( std::declval<unsigned long long>( ) ) );
		

		public:
		inline static std::string Convert( const unsigned long long& data )
			noexcept( IsNoexcept )
		{
			return std::to_string( data );
		}
	};
	
	template<>
	class DLLApi Converter<float , std::string> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = noexcept( std::to_string( std::declval<float>( ) ) );
		

		public:
		inline static std::string Convert( const float& data ) 
			noexcept( IsNoexcept )
		{
			return std::to_string( data );
		}
	};

	template<>
	class DLLApi Converter<double , std::string> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = noexcept( std::to_string( std::declval<double>( ) ) );
		

		public:
		inline static std::string Convert( const double& data ) 
			noexcept( IsNoexcept )
		{
			return std::to_string( data );
		}
	};
	
	template<>
	class DLLApi Converter<long double , std::string> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = noexcept( std::to_string( std::declval<long double>( ) ) );

		
		public:
		inline static std::string Convert( const long double& data ) 
			noexcept( IsNoexcept )
		{
			return std::to_string( data );
		}
	};

	template<>
	class DLLApi Converter<bool, std::string> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = noexcept( std::to_string( std::declval<bool>( ) ) );
		

		public:
		inline static std::string Convert( const bool data ) 
			noexcept( IsNoexcept )
		{
			return std::to_string( data );
		}
	};

	template<>
	class DLLApi Converter<char*, std::string> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = noexcept( std::string( std::declval<char*>( ) ) );

		
		public:
		inline static std::string Convert( const char* data )
			noexcept( IsNoexcept )
		{
			return data;
		}
	};

}