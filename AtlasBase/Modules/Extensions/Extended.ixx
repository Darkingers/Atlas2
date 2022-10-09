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

	template<typename BaseType ,typename PropertyHolder>
	class DLLApi ExtendedBaseType :
		public Marker::ExtendedType ,
		public BaseType
	{
		private: using ActualType = ExtendedBaseType<BaseType , PropertyHolder>;
		private: template<unsigned int Index>
		using PropertyType = Deduce::TupleIndexedType<Index , PropertyHolder>;

			
		private:  template<unsigned int Index>
		constexpr static bool IsNoexceptGet = noexcept( Tuple::Get<Index>( std::declval<PropertyHolder>( ) ) );
		private:  template<unsigned int Index>
		constexpr static bool IsNoexceptSet = noexcept( Tuple::Set<Index>( std::declval<PropertyHolder>( ) , std::declval<PropertyType<Index>>( ) ) );
		
			
		public: PropertyHolder ExtendedProperties;


		public: template<typename... BaseArgs>
		constexpr ExtendedBaseType( PropertyHolder&& propertyHolder , BaseArgs&&... baseArgs )
			noexcept ( Type<BaseType>::template IsNoexceptConstructible<BaseArgs&&...> ) :
			ExtendedProperties( std::move( propertyHolder ) ) ,
			BaseType( std::forward<BaseArgs&&>( baseArgs )... )
		{

		}

		public:
		~ExtendedBaseType( ) override = default;

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

	template<typename BaseType , typename PropertyHolder>
	class DLLApi ExtendedType :
		public ExtendedBaseType<BaseType , PropertyHolder>
	{			
		public: template<typename... BaseArgs>
		constexpr ExtendedType( PropertyHolder&& propertyHolder , BaseArgs&&... baseArgs )
			noexcept ( Type<BaseType>::template IsNoexceptConstructible<BaseArgs&&...> ) :
			ExtendedBaseType<BaseType , PropertyHolder>( std::move(propertyHolder) , std::forward<BaseArgs&&>( baseArgs )... )
		{}

		public:
		~ExtendedType( ) final = default;
	};

	template<typename BaseType, typename PropertyHolder>
		requires Concept::HasToString<BaseType>
	class DLLApi ExtendedType<BaseType, PropertyHolder> :
		public ExtendedBaseType<BaseType , PropertyHolder>
	{
		private: constexpr static bool IsNoexceptToString = noexcept( std::declval<BaseType>( ).ToString( ) );
		private: constexpr static bool IsNoexceptExtendedToString = noexcept( Convert<std::string>::From( std::declval<PropertyHolder>() ) );
	
		public: template<typename... BaseArgs>
		constexpr ExtendedType( PropertyHolder&& propertyHolder , BaseArgs&&... baseArgs )
			noexcept ( Type<BaseType>::template IsNoexceptConstructible<BaseArgs&&...> ) :
			ExtendedBaseType<BaseType , PropertyHolder>( std::move( propertyHolder ) , std::forward<BaseArgs&&>( baseArgs )... )
		{}

		public:
		~ExtendedType( ) final = default;
			
		public:
		auto ToString( ) const final
		{
			return BaseType::ToString( ) + "{" + Convert<std::string>::From( this->ExtendedProperties ) + "}";
		}
	};

	template<typename ConstructedType, typename... BaseArgs>
	class DLLApi Constructor
	{
		public: template<typename CurrentType, typename... ExtendedArgs>
		constexpr static auto Construct(BaseArgs&&... bArgs, CurrentType&& current, ExtendedArgs&&... eArgs )
		{
			if constexpr ( std::is_constructible<ConstructedType , BaseArgs...>::value )
			{
				return Implementation::ExtendedType<ConstructedType, std::tuple<CurrentType, ExtendedArgs...>>(std::make_tuple( std::forward<CurrentType&&>( current ), std::forward<ExtendedArgs&&>( eArgs )...) , std::forward<BaseArgs&&>( bArgs )... );
			} 
			else if constexpr( sizeof...( eArgs )>0 )
			{
				return Constructor<ConstructedType , BaseArgs... , CurrentType>::Construct( std::forward<BaseArgs&&>( bArgs )... , std::forward<CurrentType&&>( current ) , std::forward<ExtendedArgs&&>( eArgs )... );
			}
			else
			{
				static_assert( sizeof...( eArgs ) == 0 , "No constructor found for type" );
			}
		}	

		public: template<typename CurrentType , typename... ExtendedArgs>
		constexpr static auto Construct( BaseArgs&&... bArgs , const CurrentType& current , ExtendedArgs&&... eArgs )
		{
			if constexpr ( std::is_constructible<ConstructedType , BaseArgs...>::value )
			{
				return Implementation::ExtendedType<ConstructedType ,std::tuple<const CurrentType&, ExtendedArgs...>>(std::make_tuple( std::forward<const CurrentType&>( current ) , std::forward<ExtendedArgs&&>( eArgs )...) , std::forward<BaseArgs&&>( bArgs )... );
			}
			else if constexpr ( sizeof...( eArgs ) > 0 )
			{
				return Constructor<ConstructedType , BaseArgs... , const CurrentType&>::Construct( std::forward<BaseArgs&&>( bArgs )... , std::forward<const CurrentType&>( current ) , std::forward<ExtendedArgs&&>( eArgs )... );
			}
			else
			{
				static_assert( sizeof...( eArgs ) == 0 , "No constructor found for type" );
			}
		}
	};
}

export namespace Atlas
{
	template<typename BaseType>
	class DLLApi Extended
	{
		public: template<typename... Arguments>
			constexpr inline static auto Construct( Arguments&&... args )
		{
			return Implementation::Constructor<BaseType>::Construct( std::forward<Arguments&&>( args )... );
		}

		public:  template<typename... Arguments>
			constexpr inline static auto Allocate( Arguments&&... args )
		{
			return new Implementation::Constructor<BaseType>::Construct( std::forward<Arguments&&>( args )... );
		}
	};
}
