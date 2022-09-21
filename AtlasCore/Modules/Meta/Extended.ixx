module;

#include <tuple>
#include <type_traits>
#include "../../../Macros/Macros.h"


export module AtlasMeta:Extended;
import AtlasDefinitions;
import AtlasConcepts;

export namespace Atlas::Meta
{
	namespace Marker
	{
		class Extended{};
	}

	template<typename Type , typename... ExtendedArgs>
	class DLLApi ExtendedType :
		public Marker::Extended,
		public Type
	{
		private: using ActualType = ExtendedType < Type , ExtendedArgs...>;
		private: using PropertyHolder = std::tuple<ExtendedArgs...>;

		public: PropertyHolder ExtendedProperties;


		public: template<typename... BaseArgs>
		constexpr ExtendedType( ExtendedArgs&&... extendedArgs , BaseArgs&&... baseArgs ) :
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

		public: template<unsigned int Index>
		constexpr std::tuple_element_t<Index , ActualType>& get( )
		{
			if constexpr ( Index == 0 )
			{
				return *this;
			}
			else
			{
				return GetExtended<Index>( );
			}
		}
	};

	template<typename BaseType , typename... BaseArgs>
	class Extended
	{
		public: template<typename... ExtendedArgs>
		constexpr inline static auto Create( BaseArgs... bArgs , ExtendedArgs... eArgs )
		{
			return ExtendedType<BaseType , ExtendedArgs...>( std::forward<ExtendedArgs>( eArgs )... , std::forward<BaseArgs>( bArgs )... );
		}

		public: template<typename... ExtendedArgs>
		constexpr inline static auto Allocate( BaseArgs... bArgs , ExtendedArgs... eArgs )
		{
			return new ExtendedType<BaseType , ExtendedArgs...>( std::forward<ExtendedArgs>( eArgs )... , std::forward<BaseArgs>( bArgs )... );
		}
	};
}

namespace std
{
	template<unsigned int Index, typename Type>
		requires Atlas::Concept::IsDerivedFrom<Type , Atlas::Meta::Marker::Extended>
	struct tuple_element<Index , Type>
	{
		using type = typename decltype( std::declval<Type>( ).GetExtended<Index-1>( ) );
	};

	template<typename Type>
		requires Atlas::Concept::IsDerivedFrom<Type , Atlas::Meta::Marker::Extended>
	struct tuple_element<0 , Type>
	{
		using type = Type;
	};
}