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
		template<unsigned int Index,typename CurrentType, typename... Args>
		void Convert(std::string* result, CurrentType current , const Args&... arguments )
		{
			std::stringstream stream;
			stream << current;

			result[Index] = stream.str( );

			if constexpr ( sizeof...( arguments ) > 0 )
			{
				Convert<Index + 1>( std::forward<const Args&>( arguments )... );
			}
		}
	}

	class DLLApi String
	{
		template<typename... Args>
		consteval static std::string ConstConcat( const Args&... arguments )
		{
			requires "" + ... + arguments;
		}

		template<typename... Args>
		inline static std::string* CreateArrayFrom( const Args&... arguments )
		{
			std::string strings[sizeof...( arguments )];

			Implementation::Convert<0>( strings , std::forward<const Args&>( arguments )... );

			return strings;
		}
		
		template<typename... Args>
		inline static std::string Replace( std::string string, const Args&... arguments )
		{
			const unsigned int stringLength = string.length( );
			if ( stringLength < 3 )
			{
				return string;
			}

			auto replaceArray = String::CreateArrayFrom( std::forward<const Args&>( arguments )... );

			std::string result;
			
			unsigned int length;
			unsigned int j;
			unsigned int index;

			for ( unsigned int i = 0; i < stringLength - 2;)
			{
				if ( string[i++] == '{' )
				{
					for ( length = 0, j = i ; j < stringLength && string[j] != '}'; j++ )
					{
						length++;
					}

					result += replaceArray[std::stoul( string.substr(i, length ) , nullptr , 10 )];
				}
				else
				{
					result += string[i++];
				}
			}

			return result;
		}
	};
}
