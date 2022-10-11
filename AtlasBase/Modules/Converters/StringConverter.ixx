module;

#include <string>
#include <tuple>
#include <vector>

#include "../../../Macros/Macros.h"

export module AtlasConverters:StringConverter;

import AtlasTypeInfo;
import AtlasConcepts;
import AtlasDefinitions;

import :Converter;
import :Convert;

export namespace Atlas::Converters
{
	template<typename SourceType>
	class DLLApi Converter<SourceType* , std::string> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = noexcept( std::to_string( Type<unsigned long long>::Instance( ) ) );

			
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
		private: constexpr static bool IsNoexcept = noexcept( std::to_string( unsigned long long( )) );
		

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
		private: constexpr static bool IsNoexcept = noexcept( std::to_string( int( ) ) );

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
		private: constexpr static bool IsNoexcept = noexcept( std::to_string( unsigned int( ) ));
		

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
		private: constexpr static bool IsNoexcept = noexcept( std::to_string( long( ) ));
		

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
		private: constexpr static bool IsNoexcept = noexcept( std::to_string( unsigned long( ) ));
		

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
		private: constexpr static bool IsNoexcept = noexcept( std::to_string( long long( ) ));
		

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
		private: constexpr static bool IsNoexcept = noexcept( std::to_string( unsigned long long( ) ));
		

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
		private: constexpr static bool IsNoexcept = noexcept( std::to_string( float( ) ));
		

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
		private: constexpr static bool IsNoexcept = noexcept( std::to_string( double( ) ));
		

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
		private: constexpr static bool IsNoexcept = noexcept( std::to_string( long double( ) ));

		
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
		private: constexpr static bool IsNoexcept = noexcept( std::to_string( bool( )));
		

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
		private: constexpr static bool IsNoexcept = noexcept( std::string( std::declval<char*>( ) ));

		
		public:
		inline static std::string Convert( const char* data )
			noexcept( IsNoexcept )
		{
			return data;
		}
	};
	
	template<typename SourceType>
		requires Type<SourceType>::IsTuple
	class DLLApi Converter<SourceType , std::string> :
		public std::true_type
	{
		private: template<unsigned int Current , unsigned int End>
		struct IsNoexceptConvertable
		{
			public:
			constexpr static bool NoexceptCheck( )
			{
				using IndexedType = Deduce::TupleIndexedType<Current,SourceType>;

				bool result = noexcept( Atlas::Convert<std::string>::From( std::declval<IndexedType>( ) ));

				if constexpr ( End > Current - 1 )
				{
					result = result && IsNoexceptConvertable<Current + 1 , End>::value;
				}

				return result;
			}

			public: constexpr static bool value = NoexceptCheck( );
		};

		public: constexpr static bool IsNoexcept = IsNoexceptConvertable<0 , std::tuple_size_v<SourceType>>::value;


		public:
		constexpr inline static std::string Convert( const SourceType& data , const std::string& delimiter = "," )
			noexcept ( IsNoexceptConvertable<0 , std::tuple_size_v<SourceType>>::value )
		{
			std::string result = Atlas::Convert<std::string>::From( std::get<0>( data) );

			ConvertRemainingToString<1 , std::tuple_size<SourceType>::value>( data , result , delimiter );

			return result;
		}

		private: template<unsigned int Current , unsigned int End>
		constexpr inline static void ConvertRemainingToString( const SourceType& data , std::string& result , const std::string& delimiter )
		{
			if constexpr ( End > Current )
			{
				result += delimiter + Atlas::Convert<std::string>::From( std::get<Current>( data ) );

				ConvertRemainingToString<Current + 1 , End>( data , result , delimiter );
			}
		}
	};

	template<typename SourceType>
		requires Concept::IsIterable<SourceType>
	class DLLApi Converter<SourceType , std::string> :
		public std::true_type
	{
		private: using DataType = Deduce::CollectionContainedType<SourceType>;
		private: constexpr static bool IsNoexceptBegin = Concept::IsNoexceptBegin<SourceType>;
		private: constexpr static bool IsNoexceptEnd = Concept::IsNoexceptConstEnd<SourceType>;
		private: constexpr static bool IsNoexceptConvert = noexcept( Converter<DataType , std::string>::Convert( DataType( ) ));
		private: constexpr static bool IsNoexcept = IsNoexceptBegin && IsNoexceptEnd && IsNoexceptConvert;

		public:
		constexpr inline static std::string Convert( const SourceType& data , const std::string& delimiter = "," )
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