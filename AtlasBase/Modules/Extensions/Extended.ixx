module;

#include <tuple>
#include <type_traits>

#include "../../../Macros/Macros.h"

export module AtlasExtensions:Extended;

import AtlasDefinitions;
import AtlasConcepts;
import AtlasConverters;

import :Tuple;

export namespace Atlas::Extensions
{
	namespace Marker
	{
		class ExtendedType{};
	}

	template<typename Type , typename... ExtendedArgs>
	class DLLApi ExtendedBaseType :
		public Marker::ExtendedType ,
		public Type
	{
		private: using ActualType = ExtendedBaseType < Type , ExtendedArgs...>;
		private: using PropertyHolder = std::tuple<ExtendedArgs...>;

		public: PropertyHolder ExtendedProperties;


		public: template<typename... BaseArgs>
		constexpr ExtendedBaseType( ExtendedArgs&&... extendedArgs , BaseArgs&&... baseArgs ) :
			ExtendedProperties( std::forward<ExtendedArgs&&>( extendedArgs )... ) ,
			Type( std::forward<BaseArgs&&>( baseArgs )... )
		{

		}

		public: template<unsigned int Index>
		constexpr auto GetExtended( )
		{
			return Tuple::Get<Index>( ExtendedProperties );
		}

		public: template<unsigned int Index>
		constexpr void SetExtended( Deduce::TupleIndexedType<Index, PropertyHolder>&& value )
		{
			Tuple::Set<Index>( ExtendedProperties , value );
		}

		public: template<unsigned int Index>
		constexpr Tuple::ElementType<Index , ActualType>& get( )
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

	template<typename Type , typename... ExtendedArgs>
	class DLLApi ExtendedType :
		public ExtendedBaseType<Type , ExtendedArgs...>
	{
		public: template<typename... BaseArgs>
		constexpr ExtendedType( ExtendedArgs&&... extendedArgs , BaseArgs&&... baseArgs ) :
			ExtendedBaseType<Type , ExtendedArgs...>( std::forward<ExtendedArgs&&>( extendedArgs )... , std::forward<BaseArgs&&>( baseArgs )... )
		{

		}

		public:
		~ExtendedType( )
		{}
	};

	template<typename Type , typename... ExtendedArgs>
		requires Concept::HasToString<Type>
	class DLLApi ExtendedType<Type, ExtendedArgs...> :
		public ExtendedBaseType<Type , ExtendedArgs...>
	{

		public: template<typename... BaseArgs>
		constexpr ExtendedType( ExtendedArgs&&... extendedArgs , BaseArgs&&... baseArgs ) :
			ExtendedBaseType<Type , ExtendedArgs...>( std::forward<ExtendedArgs&&>( extendedArgs )... , std::forward<BaseArgs&&>( baseArgs )... )
		{

		}

		public:
		~ExtendedType( )
		{}
			
		public:
		std::string ToString( ) const final
		{
			return Type::ToString( ) + "{" + Convert<std::string>::From( this->ExtendedProperties ) + "}";
		}
	};
}

export namespace Atlas
{
	template<typename BaseType , typename... BaseArgs>
	class Extended
	{
		public: template<typename... ExtendedArgs>
		constexpr inline static auto Construct( BaseArgs&&... bArgs , ExtendedArgs&&... eArgs )
		{
			return Extensions::ExtendedType<BaseType , ExtendedArgs...>( std::forward<ExtendedArgs&&>( eArgs )... , std::forward<BaseArgs&&>( bArgs )... );
		}

		public: template<typename... ExtendedArgs>
		constexpr inline static auto Allocate( BaseArgs&&... bArgs , ExtendedArgs&&... eArgs )
		{
			return new Extensions::ExtendedType<BaseType , ExtendedArgs...>( std::forward<ExtendedArgs&&>( eArgs )... , std::forward<BaseArgs&&>( bArgs )... );
		}
	};
}

namespace std
{
	template<unsigned int Index, typename Type>
		requires Atlas::Concept::IsDerivedFrom<Type , Atlas::Extensions::Marker::ExtendedType>
	struct tuple_element<Index , Type>
	{
		using type = typename decltype( std::declval<Type>( ).GetExtended<Index-1>( ) );
	};

	template<typename Type>
		requires Atlas::Concept::IsDerivedFrom<Type , Atlas::Extensions::Marker::ExtendedType>
	struct tuple_element<0 , Type>
	{
		using type = Type;
	};
}