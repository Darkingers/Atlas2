module;

#include <tuple>
#include "../../../Macros/Macros.h"

export module AtlasMeta:Extended;
import AtlasDefinitions;

export namespace Atlas::Meta
{
	template<typename Type , typename... ExtendedArgs>
	class DLLApi ExtendedType :
		public Type
	{
		private: using PropertyHolder = std::tuple<ExtendedArgs...>;

		public: PropertyHolder ExtendedProperties;


		public: template<typename... BaseArgs>
			ExtendedType( ExtendedArgs&&... extendedArgs , BaseArgs&&... baseArgs ) :
			ExtendedProperties( std::forward<ExtendedArgs&&>( extendedArgs )... ) ,
			Type( std::forward<BaseArgs&&>( baseArgs )... )
		{

		}

		public: template<unsigned int Index>
		constexpr auto GetExtended( )
		{
			return std::get<Index>( ExtendedProperties );
		}

		public: template<unsigned int Index>
		constexpr void SetExtended( auto value )
		{
			std::get<Index>( ExtendedProperties ) = value;
		}
	};

	template<typename BaseType , typename... BaseArgs>
	class Extended
	{
		public: template<typename... ExtendedArgs>
		inline static constexpr auto Create( BaseArgs... bArgs , ExtendedArgs... eArgs )
		{
			return ExtendedType<BaseType , ExtendedArgs...>( std::forward<ExtendedArgs>( eArgs )... , std::forward<BaseArgs>( bArgs )... );
		}
	};
}