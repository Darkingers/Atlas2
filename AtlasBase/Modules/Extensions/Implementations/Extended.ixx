module;

#include <tuple>
#include <type_traits>

#include "../../../../Macros/Macros.h"

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
		constexpr static bool IsNoexceptGet = noexcept( Tuple::Get<Index>( PropertyHolder( ) ) );
		private:  template<unsigned int Index>
		constexpr static bool IsNoexceptSet = noexcept( Tuple::Set<Index>(PropertyHolder( ) , PropertyType<Index>( ) ) );
		
			
		public: PropertyHolder ExtendedProperties;


		public: template<typename... BaseConstructorTArgs>
		constexpr ExtendedBaseType( PropertyHolder&& propertyHolder , BaseConstructorTArgs&&... baseTArgs )
			noexcept ( Type<BaseType>::template IsNoexceptConstructible<BaseConstructorTArgs&&...> ) :
			ExtendedProperties( std::move( propertyHolder ) ) ,
			BaseType( std::forward<BaseConstructorTArgs&&>( baseTArgs )... )
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
		constexpr Tuple::TElement<Index , ActualType>& get( )
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
		public: template<typename... BaseConstructorTArgs>
		constexpr ExtendedType( PropertyHolder&& propertyHolder , BaseConstructorTArgs&&... baseTArgs )
			noexcept ( Type<BaseType>::template IsNoexceptConstructible<BaseConstructorTArgs&&...> ) :
			ExtendedBaseType<BaseType , PropertyHolder>( std::move(propertyHolder) , std::forward<BaseConstructorTArgs&&>( baseTArgs )... )
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
		private: constexpr static bool IsNoexceptExtendedToString = noexcept( Convert<std::string>::From( PropertyHolder() ) );
	
		public: template<typename... BaseConstructorTArgs>
		constexpr ExtendedType( PropertyHolder&& propertyHolder , BaseConstructorTArgs&&... baseTArgs )
			noexcept ( Type<BaseType>::template IsNoexceptConstructible<BaseConstructorTArgs&&...> ) :
			ExtendedBaseType<BaseType , PropertyHolder>( std::move( propertyHolder ) , std::forward<BaseConstructorTArgs&&>( baseTArgs )... )
		{}

		public:
		~ExtendedType( ) final = default;
			
		public:
		auto ToString( ) const final
		{
			return BaseType::ToString( ) + "{" + Convert<std::string>::From( this->ExtendedProperties ) + "}";
		}
	};

	template<typename ConstructedType, typename... BaseConstructorTArgs>
	class DLLApi Constructor
	{
		public: template<typename CurrentType, typename... ExtendedTArgs>
		constexpr static auto Construct( BaseConstructorTArgs&&... bTArgs, CurrentType&& current, ExtendedTArgs&&... eTArgs )
		{
			if constexpr ( Type<ConstructedType>::template IsConstructible<BaseConstructorTArgs...> )
			{
				return Implementation::ExtendedType<ConstructedType, std::tuple<CurrentType, ExtendedTArgs...>>(std::make_tuple( std::forward<CurrentType&&>( current ), std::forward<ExtendedTArgs&&>( eTArgs )...) , std::forward<BaseConstructorTArgs&&>( bTArgs )... );
			} 
			else if constexpr( sizeof...( eTArgs )>0 )
			{
				return Constructor<ConstructedType , BaseConstructorTArgs... , CurrentType>::Construct( std::forward<BaseConstructorTArgs&&>( bTArgs )... , std::forward<CurrentType&&>( current ) , std::forward<ExtendedTArgs&&>( eTArgs )... );
			}
			else
			{
				static_assert( sizeof...( eTArgs ) == 0 , "No constructor found for type" );
			}
		}	

		public: template<typename CurrentType , typename... ExtendedTArgs>
		constexpr static auto Construct( BaseConstructorTArgs&&... bTArgs , const CurrentType& current , ExtendedTArgs&&... eTArgs )
		{
			if constexpr ( Type<ConstructedType>::template IsConstructible<BaseConstructorTArgs...> )
			{
				return Implementation::ExtendedType<ConstructedType ,std::tuple<const CurrentType&, ExtendedTArgs...>>(std::make_tuple( std::forward<const CurrentType&>( current ) , std::forward<ExtendedTArgs&&>( eTArgs )...) , std::forward<BaseConstructorTArgs&&>( bTArgs )... );
			}
			else if constexpr ( sizeof...( eTArgs ) > 0 )
			{
				return Constructor<ConstructedType , BaseConstructorTArgs... , const CurrentType&>::Construct( std::forward<BaseConstructorTArgs&&>( bTArgs )... , std::forward<const CurrentType&>( current ) , std::forward<ExtendedTArgs&&>( eTArgs )... );
			}
			else
			{
				static_assert( sizeof...( eTArgs ) == 0 , "No constructor found for type" );
			}
		}

		public: template<typename CurrentType , typename... ExtendedTArgs>
		constexpr static auto Allocate( BaseConstructorTArgs&&... bTArgs , CurrentType&& current , ExtendedTArgs&&... eTArgs )
		{
			if constexpr ( Type<ConstructedType>::template IsConstructible<BaseConstructorTArgs...> )
			{
				return new Implementation::ExtendedType<ConstructedType , std::tuple<CurrentType , ExtendedTArgs...>>( std::make_tuple( std::forward<CurrentType&&>( current ) , std::forward<ExtendedTArgs&&>( eTArgs )... ) , std::forward<BaseConstructorTArgs&&>( bTArgs )... );
			}
			else if constexpr ( sizeof...( eTArgs ) > 0 )
			{
				return Constructor<ConstructedType , BaseConstructorTArgs... , CurrentType>::Construct( std::forward<BaseConstructorTArgs&&>( bTArgs )... , std::forward<CurrentType&&>( current ) , std::forward<ExtendedTArgs&&>( eTArgs )... );
			}
			else
			{
				static_assert( sizeof...( eTArgs ) == 0 , "No constructor found for type" );
			}
		}

		public: template<typename CurrentType , typename... ExtendedTArgs>
		constexpr static auto Allocate( BaseConstructorTArgs&&... bTArgs , const CurrentType& current , ExtendedTArgs&&... eTArgs )
		{
			if constexpr ( Type<ConstructedType>::template IsConstructible<BaseConstructorTArgs...> )
			{
				return new Implementation::ExtendedType<ConstructedType , std::tuple<const CurrentType& , ExtendedTArgs...>>( std::make_tuple( std::forward<const CurrentType&>( current ) , std::forward<ExtendedTArgs&&>( eTArgs )... ) , std::forward<BaseConstructorTArgs&&>( bTArgs )... );
			}
			else if constexpr ( sizeof...( eTArgs ) > 0 )
			{
				return Constructor<ConstructedType , BaseConstructorTArgs... , const CurrentType&>::Construct( std::forward<BaseConstructorTArgs&&>( bTArgs )... , std::forward<const CurrentType&>( current ) , std::forward<ExtendedTArgs&&>( eTArgs )... );
			}
			else
			{
				static_assert( sizeof...( eTArgs ) == 0 , "No constructor found for type" );
			}
		}
	};
}

export namespace Atlas
{
	template<typename BaseType>
	class DLLApi Extended
	{
		public: template<typename... TArgs>
		constexpr static inline auto Construct( TArgs&&... args )
		{
			return Implementation::Constructor<BaseType>::Construct( std::forward<TArgs&&>( args )... );
		}

		public:  template<typename... TArgs>
		constexpr static inline auto Allocate( TArgs&&... args )
		{
			return Implementation::Constructor<BaseType>::Allocate( std::forward<TArgs&&>( args )... );
		}
	};
}
