module;

#include <tuple>
#include <type_traits>

#include "../../../Macros/Macros.h"

export module AtlasExtensions:Extended;

import AtlasDefinitions;
import AtlasConcepts;
import AtlasConverters;
import AtlasTypeInfo;

import :Tuple;

export namespace Atlas::Implementation
{
	namespace Marker
	{
		class ExtendedType{};
	}

	template<typename BaseType , typename... ExtendedArgs>
	class DLLApi ExtendedBaseType :
		public Marker::ExtendedType ,
		public BaseType
	{
		private: using ActualType = ExtendedBaseType<BaseType , ExtendedArgs...>;
		private: using PropertyHolder = std::tuple<ExtendedArgs...>;
		private: template<unsigned int Index>
		using PropertyType = Deduce::TupleIndexedType<Index , PropertyHolder>;

			
		private:  template<unsigned int Index>
		constexpr static bool IsNoexceptGet = noexcept( Tuple::Get<Index>( std::declval<PropertyHolder>( ) ) );
		private:  template<unsigned int Index>
		constexpr static bool IsNoexceptSet = noexcept( Tuple::Set<Index>( std::declval<PropertyHolder>( ) , std::declval<PropertyType<Index>>( ) ) );
		
			
		public: PropertyHolder ExtendedProperties;


		public: template<typename... BaseArgs>
		constexpr ExtendedBaseType( ExtendedArgs&&... extendedArgs , BaseArgs&&... baseArgs ) 
			noexcept ( Type<BaseType>::template IsNoexceptConstructible<BaseArgs&&...> ) :
			ExtendedProperties( std::forward<ExtendedArgs&&>( extendedArgs )... ) ,
			BaseType( std::forward<BaseArgs&&>( baseArgs )... )
		{

		}

		public:
		~ExtendedBaseType( ) override
		{}

		public: template<unsigned int Index>
		constexpr auto GetExtended( ) 
			noexcept( IsNoexceptGet<Index> )
		{
			return Tuple::Get<Index>( ExtendedProperties );
		}

		public: template<unsigned int Index, typename SetType = PropertyType<Index>>
		constexpr void SetExtended( SetType&& value ) 
			noexcept( IsNoexceptSet<Index> )
		{
			Tuple::Set<Index>( ExtendedProperties , value );
		}

		public: template<unsigned int Index>
		constexpr Tuple::ElementType<Index , ActualType>& get( )
			noexcept( IsNoexceptGet<Index> )
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

	template<typename BaseType , typename... ExtendedArgs>
	class DLLApi ExtendedType :
		public ExtendedBaseType<BaseType , ExtendedArgs...>
	{
		private: constexpr static bool IsNoexceptConstructible = Type<BaseType>::template IsNoexceptConstructible<ExtendedArgs&&...>;

			
		public: template<typename... BaseArgs>
		constexpr ExtendedType( ExtendedArgs&&... extendedArgs , BaseArgs&&... baseArgs )
			noexcept ( IsNoexceptConstructible ) :
			ExtendedBaseType<BaseType , ExtendedArgs...>( std::forward<ExtendedArgs&&>( extendedArgs )... , std::forward<BaseArgs&&>( baseArgs )... )
		{}

		public:
		~ExtendedType( ) final
		{}
	};

	template<typename BaseType, typename... ExtendedArgs>
		requires Concept::HasToString<BaseType>
	class DLLApi ExtendedType<BaseType, ExtendedArgs...> :
		public ExtendedBaseType<BaseType , ExtendedArgs...>
	{
		private: constexpr static bool IsNoexceptToString = noexcept( std::declval<BaseType>( ).ToString( ) );
		private: constexpr static bool IsNoexceptExtendedToString = noexcept( Convert<std::string>::From( std::declval<std::tuple<ExtendedArgs...>>() ) );
		private: constexpr static bool IsNoexceptConstructible = Type<BaseType>::template IsNoexceptConstructible<ExtendedArgs&&...>;
			
			
		public: template<typename... BaseArgs>
		constexpr ExtendedType( ExtendedArgs&&... extendedArgs , BaseArgs&&... baseArgs )
			noexcept ( IsNoexceptConstructible ) :
			ExtendedBaseType<BaseType , ExtendedArgs...>( std::forward<ExtendedArgs&&>( extendedArgs )... , std::forward<BaseArgs&&>( baseArgs )... )
		{}

		public:
		 ~ExtendedType()  final
		{}
			
		public:
		auto ToString( ) const final
		{
			return BaseType::ToString( ) /*+ "{" + Convert<std::string>::From( this->ExtendedProperties ) + "}"*/;
		}
	};
}

export namespace Atlas
{
	template<typename BaseType , typename... BaseArgs>
	class DLLApi Extended
	{
		public: template<typename... ExtendedArgs>
		constexpr inline static auto Construct( BaseArgs&&... bArgs , ExtendedArgs&&... eArgs )
			noexcept( Type<Implementation::ExtendedType<BaseType , ExtendedArgs...>>::template IsNoexceptConstructible<ExtendedArgs...,BaseArgs...>)
		{
			return Implementation::ExtendedType<BaseType , ExtendedArgs...>( std::forward<ExtendedArgs&&>( eArgs )... , std::forward<BaseArgs&&>( bArgs )... );
		}

		public: template<typename... ExtendedArgs>
		constexpr inline static auto Allocate( BaseArgs&&... bArgs , ExtendedArgs&&... eArgs ) 
			noexcept( Type<Implementation::ExtendedType<BaseType , ExtendedArgs...>>::template IsNoexceptConstructible<ExtendedArgs... , BaseArgs...> )
		{
			return new Implementation::ExtendedType<BaseType , ExtendedArgs...>( std::forward<ExtendedArgs&&>( eArgs )... , std::forward<BaseArgs&&>( bArgs )... );
		}
	};
}

namespace std
{
	/*template<unsigned int Index, typename Type>
		requires Atlas::Concept::IsDerivedFrom<Type , Atlas::Implementation::Marker::ExtendedType>
	struct tuple_element<Index , Type>
	{
		using type = typename decltype( std::declval<Type>( ).GetExtended<Index-1>( ) );
	};

	template<typename Type>
		requires Atlas::Concept::IsDerivedFrom<Type , Atlas::Implementation::Marker::ExtendedType>
	struct tuple_element<0 , Type>
	{
		using type = Type;
	};*/
}