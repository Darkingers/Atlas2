module;

#include <string>
#include "../../../Macros/Macros.h"

export module AtlasMeta:String;
import AtlasDefinitions;
import AtlasConcepts;

export namespace Atlas::Meta
{
	namespace Implementation
	{
		template<unsigned int Index , typename CurrentType , typename... Args>
		constexpr void ConvertFrom( std::string result[] , const CurrentType& current , const Args&... arguments )
		{
			std::stringstream stream;
			stream << current;

			result[Index] = stream.str( );

			if constexpr ( sizeof...( arguments ) > 0 )
			{
				ConvertFrom<Index + 1>( result , std::forward<const Args&>( arguments )... );
			}
		}
	}

	class String
	{
		public: template<typename... Args>
		constexpr inline static auto Create( const std::string& current , const Args&... arguments )
		{
			if constexpr ( sizeof...( arguments ) > 0 )
			{
				return current + String::Create( std::forward<const Args&>( arguments )... );
			}
			else
			{
				return current;
			}
		}

		public: template<typename... Args>
		constexpr inline static auto Create( const char* current, const Args&... arguments )
		{
			if constexpr ( sizeof...( arguments ) > 0 )
			{
				return current + String::Create( std::forward<const Args&>( arguments )... );
			}
			else
			{
				return current;
			}
		}

		public: template<typename CurrentType , typename... Args>
		constexpr inline static auto Create( const CurrentType& current , const Args&... arguments )
		{
			std::stringstream stream;
			stream << current;

			if constexpr ( sizeof...( arguments ) > 0 )
			{
				return stream.str( ) + String::Create( std::forward<const Args&>( arguments )... );
			}
			else
			{
				return stream.str( );
			}
		}

		public: template<typename... Args>
		constexpr inline static auto CreateArrayFrom( const Args&... arguments )
		{
			std::string strings[sizeof...( arguments )];

			Implementation::ConvertFrom<0>( strings , std::forward<const Args&>( arguments )... );

			return strings;
		}

		public: template<typename... Args>
		constexpr static auto Replace( const std::string& string , const Args&... arguments )
		{
			const unsigned int stringLength = string.length( );
			if ( stringLength < 3 )
			{
				return string;
			}

			std::string replaceArray[sizeof...( arguments )];
			Implementation::ConvertFrom<0>( replaceArray , std::forward<const Args&>( arguments )... );

			std::string result;

			unsigned int length;
			unsigned int j;
			unsigned int index;

			for ( unsigned int i = 0; i < stringLength - 2;)
			{
				if ( string[i] == '{' )
				{
					for ( length = 0 , j = i + 1; j < stringLength && string[j] != '}'; j++ )
					{
						length++;
					}

					result += replaceArray[std::stoul( string.substr( i + 1 , length ) , nullptr , 10 )];

					i += length + 2;
				}
				else
				{
					result += string[i++];
				}
			}

			return result.c_str( );
		}
	};
}
