module;

#include <string>
#include <tuple>
#include <vector>

#include "../../../../Macros/Macros.h"

export module AtlasConverters:StringConverter;

import AtlasDefinitions;
import AtlasConcepts;
import AtlasTypeInfo;
import AtlasAPI;

export namespace Atlas
{
	template<typename TSource>
	class DLLApi TypeConverter<TSource* , std::string> :
		public std::true_type
	{
		
	public:

		inline static std::string Convert( const TSource data ) 
			noexcept( noexcept( std::to_string( static_cast<unsigned long long>(data) ) ) )
		{
			return std::to_string( reinterpret_cast<unsigned long long>( data ) );
		}
	};

	template<typename TSource> requires 
		Concept::HasToString<TSource>
	class DLLApi TypeConverter<TSource , std::string> :
		public std::true_type
	{
		
	public:
		
		inline static std::string Convert( const TSource& data ) 
			noexcept( noexcept( data.ToString( ) ) )
		{
			return data.ToString( );
		}
	};

	template<>
	class DLLApi TypeConverter<int, std::string> :
		public std::true_type
	{
		
	public:
		
		inline static std::string Convert( const int& data )
			noexcept( noexcept( std::to_string( data ) ) )
		{
			return std::to_string( data );
		}
	};

	template<>
	class DLLApi TypeConverter<unsigned int, std::string> :
		public std::true_type
	{
		
	public:
		
		inline static std::string Convert( const unsigned int& data )
			noexcept( noexcept( std::to_string( data ) ) )
		{
			return std::to_string( data );
		}
	};

	template<>
	class DLLApi TypeConverter<long , std::string> :
		public std::true_type
	{
		
	public:
		
		inline static std::string Convert( const long& data )
			noexcept( noexcept( std::to_string( data ) ) )
		{
			return std::to_string( data );
		}
	};

	template<>
	class DLLApi TypeConverter<unsigned long , std::string> :
		public std::true_type
	{
		
	public:
		
		inline static std::string Convert( const unsigned long& data )
			noexcept( noexcept( std::to_string( data ) ) )
		{
			return std::to_string( data );
		}
	};

	template<>
	class DLLApi TypeConverter<long long , std::string> :
		public std::true_type
	{
		
	public:
		
		inline static std::string Convert( const long long& data )
			noexcept( noexcept( std::to_string( data ) ) )
		{
			return std::to_string( data );
		}
	};

	template<>
	class DLLApi TypeConverter<unsigned long long , std::string> :
		public std::true_type
	{
		
	public:
		
		inline static std::string Convert( const unsigned long long& data )
			noexcept( noexcept( std::to_string( data ) ) )
		{
			return std::to_string( data );
		}
	};
	
	template<>
	class DLLApi TypeConverter<float , std::string> :
		public std::true_type
	{
		
	public:
		
		inline static std::string Convert( const float& data ) 
			noexcept( noexcept( std::to_string( data ) ) )
		{
			return std::to_string( data );
		}
	};

	template<>
	class DLLApi TypeConverter<double , std::string> :
		public std::true_type
	{
		
	public:
		
		inline static std::string Convert( const double& data ) 
			noexcept( noexcept( std::to_string( data ) ) )
		{
			return std::to_string( data );
		}
	};
	
	template<>
	class DLLApi TypeConverter<long double , std::string> :
		public std::true_type
	{
		
	public:
		
		inline static std::string Convert( const long double& data ) 
			noexcept( noexcept( std::to_string( data ) ) )
		{
			return std::to_string( data );
		}
	};

	template<>
	class DLLApi TypeConverter<bool, std::string> :
		public std::true_type
	{
		
	public:
		
		inline static std::string Convert( const bool data ) 
			noexcept( noexcept( std::to_string( data ) ) )
		{
			return std::to_string( data );
		}
	};

	template<>
	class DLLApi TypeConverter<char*, std::string> :
		public std::true_type
	{
		
	public:
		
		inline static std::string Convert( const char* data )
			noexcept( noexcept( std::string( data ) ) )
		{
			return data;
		}
	};

	template<typename TSource> requires 
		Concept::HasIterator<TSource>
	class DLLApi TypeConverter<TSource , std::string> :
		public std::true_type
	{
	
	private: 
		
		using DataType = CollectionTraits<TSource>::ElementType;

	public:
		
		constexpr static inline std::string Convert( const TSource& data , const std::string& delimiter = "," )
			noexcept ( Concept::HasNoexceptConstIterator<const TSource&> )
		{
			auto current = std::begin( data );
			const auto end = std::cend( data );
			std::string result = ConvertAPI<std::string>::From( *current );

			for ( std::advance( current , 1 ); current != end; std::advance(current,1) )
			{
				result += delimiter + ConvertAPI<std::string>::From( *current );
			}

			return result;
		}
	};
}