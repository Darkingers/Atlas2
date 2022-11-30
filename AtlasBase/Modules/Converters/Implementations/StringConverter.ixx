module;

#include <string>
#include <tuple>
#include <vector>

#include "../../../../Macros/Macros.h"

export module AtlasConverters:StringConverter;

import AtlasConcepts;
import AtlasDefinitions;
import AtlasIntegration;
import AtlasTypeInfo;

export namespace Atlas
{
	template<typename TSource>
	class DLLApi Converter<TSource* , std::string> :
		public std::true_type
	{
		public:
		inline static std::string Convert( const TSource data ) 
			noexcept( noexcept( std::to_string( static_cast<unsigned long long>(data) ) ) )
		{
			return std::to_string( reinterpret_cast<unsigned long long>( data ) );
		}
	};

	template<typename TSource>
		requires Concept::HasToString<TSource>
	class DLLApi Converter<TSource , std::string> :
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
	class DLLApi Converter<int, std::string> :
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
	class DLLApi Converter<unsigned int, std::string> :
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
	class DLLApi Converter<long , std::string> :
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
	class DLLApi Converter<unsigned long , std::string> :
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
	class DLLApi Converter<long long , std::string> :
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
	class DLLApi Converter<unsigned long long , std::string> :
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
	class DLLApi Converter<float , std::string> :
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
	class DLLApi Converter<double , std::string> :
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
	class DLLApi Converter<long double , std::string> :
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
	class DLLApi Converter<bool, std::string> :
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
	class DLLApi Converter<char*, std::string> :
		public std::true_type
	{
		public:
		inline static std::string Convert( const char* data )
			noexcept( noexcept( std::string( data ) ) )
		{
			return data;
		}
	};
	
	template<typename TSource>
		requires Type<TSource>::IsTuple
	class DLLApi Converter<TSource , std::string> :
		public std::true_type
	{
		private: template<unsigned int Current , unsigned int End>
		struct IsNoexceptConvertable
		{
			public:
			constexpr static bool NoexceptCheck( )
			{
				using IndexedType = Deduce::TupleIndexedType<Current,TSource>;

				bool result = noexcept( Atlas::Convert<std::string>::From( std::declval<IndexedType>( ) ));

				if constexpr ( End > Current - 1 )
				{
					result = result && IsNoexceptConvertable<Current + 1 , End>::value;
				}

				return result;
			}

			public: constexpr static bool value = NoexceptCheck( );
		};

		public: constexpr static bool IsNoexcept = IsNoexceptConvertable<0 , std::tuple_size_v<TSource>>::value;


		public:
		constexpr static inline std::string Convert( const TSource& data , const std::string& delimiter = "," )
			noexcept ( IsNoexceptConvertable<0 , std::tuple_size_v<TSource>>::value )
		{
			std::string result = Atlas::Convert<std::string>::From( std::get<0>( data) );

			ConvertRemainingToString<1 , std::tuple_size<TSource>::value>( data , result , delimiter );

			return result;
		}

		private: template<unsigned int Current , unsigned int End>
		constexpr static inline void ConvertRemainingToString( const TSource& data , std::string& result , const std::string& delimiter )
		{
			if constexpr ( End > Current )
			{
				result += delimiter + Atlas::Convert<std::string>::From( std::get<Current>( data ) );

				ConvertRemainingToString<Current + 1 , End>( data , result , delimiter );
			}
		}
	};

	template<typename TSource>
		requires Concept::IsIterable<TSource>
	class DLLApi Converter<TSource , std::string> :
		public std::true_type
	{
		private: using DataType = Deduce::CollectionContainedType<TSource>;
		private: constexpr static bool IsNoexceptBegin = Concept::IsNoexceptBegin<TSource>;
		private: constexpr static bool IsNoexceptEnd = Concept::IsNoexceptConstEnd<TSource>;
		private: constexpr static bool IsNoexceptConvert = noexcept( Converter<DataType , std::string>::Convert( DataType( ) ));
		private: constexpr static bool IsNoexcept = IsNoexceptBegin && IsNoexceptEnd && IsNoexceptConvert;

		public:
		constexpr static inline std::string Convert( const TSource& data , const std::string& delimiter = "," )
			noexcept ( IsNoexcept )
		{
			auto current = std::begin( data );
			const auto end = std::cend( data );
			std::string result = Atlas::Convert<std::string>::From( *current );

			for ( std::advance( current , 1 ); current != end; std::advance(current,1) )
			{
				result += delimiter + Atlas::Convert<std::string>::From( *current );
			}

			return result;
		}
	};
}