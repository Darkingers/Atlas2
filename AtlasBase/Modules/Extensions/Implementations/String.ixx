module;

#include <string>
#include <regex>

#include "../../../../Macros/Macros.h"

export module AtlasExtensions:String;

import AtlasDefinitions;
import AtlasConcepts;
import AtlasConverters;

export namespace Atlas
{
	class String
	{	
		private: template<typename CurrentType , typename... TArgs>
		struct IsNoexceptConvertible
		{
			public:
			constexpr static bool NoexceptCheck( )
			{
				bool result = noexcept( Convert<std::string>::From( CurrentType() ) );

				if constexpr ( sizeof ...( TArgs ) > 0 )
				{
					result = result && IsNoexceptConvertible<TArgs...>::value;
				}

				return result;
			}

			public: constexpr static bool value = NoexceptCheck( );
		};

		public: template<typename... TArgs>
		constexpr static inline std::string Concat( const std::string& current , const TArgs&... args)
			noexcept ( IsNoexceptConvertible<TArgs...>::value )
		{
			if constexpr ( sizeof...( TArgs ) > 0 )
			{
				return current + String::Concat( std::forward<const TArgs&>( TArgs )... );
			}
			else
			{
				return current;
			}
		}

		public: template<typename... TArgs>
		constexpr static inline std::string Concat( const char* current, const TArgs&... args ) 
			noexcept ( IsNoexceptConvertible<TArgs...>::value )
		{
			if constexpr ( sizeof...( TArgs ) > 0 )
			{
				return current + String::Concat( std::forward<const TArgs&>( TArgs )... );
			}
			else
			{
				return current;
			}
		}

		public: template<typename CurrentType , typename... TArgs>
		constexpr static inline std::string Concat( const CurrentType& current , const TArgs&... args )
			noexcept ( IsNoexceptConvertible<TArgs...>::value )
		{
			std::string data = Convert<std::string>::From( current );

			if constexpr ( sizeof...( TArgs ) > 0 )
			{
				return data + String::Concat( std::forward<const TArgs&>( TArgs )... );
			}
			else
			{
				return data;
			}
		}

		public: template<typename... TArgs>
		constexpr static inline std::string* CreateArrayFrom( const TArgs&... args )
			noexcept ( IsNoexceptConvertible<TArgs...>::value )
		{
			std::string strings[sizeof...( TArgs )];

			String::ConvertFrom<0>( strings , std::forward<const TArgs&>( TArgs )... );

			return strings;
		}

		public:
		constexpr static bool StartsWith( const std::string& source , const std::string& checked )
			noexcept
		{
			if ( source.length( ) < checked.length( ) )
			{
				return false;
			}

			for ( unsigned int i = 0; i < checked.length( ); i++ )
			{
				if ( source[i] != checked[i] )
				{
					return false;
				}
			}

			return true;
		}

		public:
		constexpr static bool EndsWith( const std::string& source, const std::string& checked )
			noexcept
		{
			if ( source.length( ) < checked.length( ) )
			{
				return false;
			}

			for ( unsigned int i = 0; i < checked.length( ); i++ )
			{
				if ( source[source.length( ) - i - 1] != checked[checked.length( ) - i - 1] )
				{
					return false;
				}
			}

			return true;
		}

		public:
		constexpr static bool Contains( const std::string& source , const std::string& checked )
			noexcept
		{
			if ( source.length( ) < checked.length( ) )
			{
				return false;
			}

			for ( unsigned int i = 0; i < source.length( ) - checked.length( ) + 1; i++ )
			{
				bool found = true;

				for ( unsigned int j = 0; j < checked.length( ); j++ )
				{
					if ( source[i + j] != checked[j] )
					{
						found = false;
						break;
					}
				}

				if ( found )
				{
					return true;
				}
			}

			return false;
		}

		public:
		constexpr static int Occurence( const std::string& source , const std::string& checked )
			noexcept
		{
			if ( source.length( ) < checked.length( ) )
			{
				return 0;
			}

			int occurence = 0;

			for ( unsigned int i = 0; i < source.length( ) - checked.length( ) + 1; i++ )
			{
				bool found = true;

				for ( unsigned int j = 0; j < checked.length( ); j++ )
				{
					if ( source[i + j] != checked[j] )
					{
						found = false;
						break;
					}
				}

				if ( found )
				{
					occurence++;
				}
			}

			return occurence;
		}

		public:
		constexpr static std::vector<std::string> Split( const std::string& source , const std::string& separator )
			noexcept
		{
			std::vector<std::string> result;

			if ( source.length( ) < separator.length( ) )
			{
				result.push_back( source );
				return result;
			}

			for ( unsigned int i = 0; i < source.length( ) - separator.length( ) + 1; i++ )
			{
				bool found = true;

				for ( unsigned int j = 0; j < separator.length( ); j++ )
				{
					if ( source[i + j] != separator[j] )
					{
						found = false;
						break;
					}
				}

				if ( found )
				{
					result.push_back( source.substr( 0 , i ) );
					result.push_back( source.substr( i + separator.length( ) , source.length( ) - i - separator.length( ) ) );
					return result;
				}
			}

			result.push_back( source );
			return result;
		}

		public:
		static bool Match(const std::string& source, const std::string& regex )
			noexcept( noexcept( std::regex_match(std::string(), std::regex() ) ) )
		{
			std::regex reg( regex );
			return std::regex_match( source , reg );
		}
		
		public:
		constexpr static std::string Replace( const std::string& source , const std::string& replaced , const std::string& replacedWith ) 
			noexcept
		{			
			if ( replaced.length( ) == 0 )
			{
				return std::string( source );
			}
			
			std::string result;
			auto iterationEnd = source.length( ) - replaced.length( ) + 1;	
			bool replace;

			for ( int i = 0; i < iterationEnd; ++i )
			{
				if ( source[i] == replaced[0] )
				{
					replace = true;
					
					for ( int j = 1; j< replaced.length(); ++j )
					{
						if ( source[i + j] != replaced[j] )
						{
							replace = false;
							break;
						}
					}

					if ( replace )
					{
						result += replacedWith;
					}
					else
					{
						result += source[i];
					}
				}
				else
				{
					result += source[i];
				}
			}

			return result;
		}

		public: template<typename... TArgs>
		constexpr static std::string ReplaceSymbols( const std::string& string , const TArgs&... args )
			noexcept ( IsNoexceptConvertible<TArgs...>::value && noexcept( Convert<int>::From( std::string() )) )
		{
			const unsigned int stringLength = string.length( );
			if ( stringLength < 3 )
			{
				return string;
			}

			std::string replaceArray[sizeof...( TArgs )];
			String::ConvertFrom<0>( replaceArray , std::forward<const TArgs&>( TArgs )... );

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

					result += replaceArray[Convert<int>::From( string.substr( i + 1 , length ) , nullptr , 10 )];

					i += length + 2;
				}
				else
				{
					result += string[i++];
				}
			}

			return result;
		}

		private: template<unsigned int Index , typename CurrentType , typename... TArgs>
		constexpr void ConvertFrom( std::string result[] , const CurrentType& current , const TArgs&... args ) 
			noexcept ( noexcept( Convert<std::string>::From( CurrentType() ) ) && IsNoexceptConvertible<TArgs...>::value )
		{
			result[Index] = Convert<std::string>::From( current );

			if constexpr ( sizeof...( TArgs ) > 0 )
			{
				String::ConvertFrom<Index + 1>( result , std::forward<const TArgs&>( TArgs )... );
			}
		}
	};
}
