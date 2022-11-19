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


		public: template<typename... BaseConstructorArguments>
		constexpr ExtendedBaseType( PropertyHolder&& propertyHolder , BaseConstructorArguments&&... baseArguments )
			noexcept ( Type<BaseType>::template IsNoexceptConstructible<BaseConstructorArguments&&...> ) :
			ExtendedProperties( std::move( propertyHolder ) ) ,
			BaseType( std::forward<BaseConstructorArguments&&>( baseArguments )... )
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
		public: template<typename... BaseConstructorArguments>
		constexpr ExtendedType( PropertyHolder&& propertyHolder , BaseConstructorArguments&&... baseArguments )
			noexcept ( Type<BaseType>::template IsNoexceptConstructible<BaseConstructorArguments&&...> ) :
			ExtendedBaseType<BaseType , PropertyHolder>( std::move(propertyHolder) , std::forward<BaseConstructorArguments&&>( baseArguments )... )
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
	
		public: template<typename... BaseConstructorArguments>
		constexpr ExtendedType( PropertyHolder&& propertyHolder , BaseConstructorArguments&&... baseArguments )
			noexcept ( Type<BaseType>::template IsNoexceptConstructible<BaseConstructorArguments&&...> ) :
			ExtendedBaseType<BaseType , PropertyHolder>( std::move( propertyHolder ) , std::forward<BaseConstructorArguments&&>( baseArguments )... )
		{}

		public:
		~ExtendedType( ) final = default;
			
		public:
		auto ToString( ) const final
		{
			return BaseType::ToString( ) + "{" + Convert<std::string>::From( this->ExtendedProperties ) + "}";
		}
	};

	template<typename ConstructedType, typename... BaseConstructorArguments>
	class DLLApi Constructor
	{
		public: template<typename CurrentType, typename... ExtendedArguments>
		constexpr static auto Construct( BaseConstructorArguments&&... bArguments, CurrentType&& current, ExtendedArguments&&... eArguments )
		{
			if constexpr ( Type<ConstructedType>::template IsConstructible<BaseConstructorArguments...> )
			{
				return Implementation::ExtendedType<ConstructedType, std::tuple<CurrentType, ExtendedArguments...>>(std::make_tuple( std::forward<CurrentType&&>( current ), std::forward<ExtendedArguments&&>( eArguments )...) , std::forward<BaseConstructorArguments&&>( bArguments )... );
			} 
			else if constexpr( sizeof...( eArguments )>0 )
			{
				return Constructor<ConstructedType , BaseConstructorArguments... , CurrentType>::Construct( std::forward<BaseConstructorArguments&&>( bArguments )... , std::forward<CurrentType&&>( current ) , std::forward<ExtendedArguments&&>( eArguments )... );
			}
			else
			{
				static_assert( sizeof...( eArguments ) == 0 , "No constructor found for type" );
			}
		}	

		public: template<typename CurrentType , typename... ExtendedArguments>
		constexpr static auto Construct( BaseConstructorArguments&&... bArguments , const CurrentType& current , ExtendedArguments&&... eArguments )
		{
			if constexpr ( Type<ConstructedType>::template IsConstructible<BaseConstructorArguments...> )
			{
				return Implementation::ExtendedType<ConstructedType ,std::tuple<const CurrentType&, ExtendedArguments...>>(std::make_tuple( std::forward<const CurrentType&>( current ) , std::forward<ExtendedArguments&&>( eArguments )...) , std::forward<BaseConstructorArguments&&>( bArguments )... );
			}
			else if constexpr ( sizeof...( eArguments ) > 0 )
			{
				return Constructor<ConstructedType , BaseConstructorArguments... , const CurrentType&>::Construct( std::forward<BaseConstructorArguments&&>( bArguments )... , std::forward<const CurrentType&>( current ) , std::forward<ExtendedArguments&&>( eArguments )... );
			}
			else
			{
				static_assert( sizeof...( eArguments ) == 0 , "No constructor found for type" );
			}
		}

		public: template<typename CurrentType , typename... ExtendedArguments>
		constexpr static auto Allocate( BaseConstructorArguments&&... bArguments , CurrentType&& current , ExtendedArguments&&... eArguments )
		{
			if constexpr ( Type<ConstructedType>::template IsConstructible<BaseConstructorArguments...> )
			{
				return new Implementation::ExtendedType<ConstructedType , std::tuple<CurrentType , ExtendedArguments...>>( std::make_tuple( std::forward<CurrentType&&>( current ) , std::forward<ExtendedArguments&&>( eArguments )... ) , std::forward<BaseConstructorArguments&&>( bArguments )... );
			}
			else if constexpr ( sizeof...( eArguments ) > 0 )
			{
				return Constructor<ConstructedType , BaseConstructorArguments... , CurrentType>::Construct( std::forward<BaseConstructorArguments&&>( bArguments )... , std::forward<CurrentType&&>( current ) , std::forward<ExtendedArguments&&>( eArguments )... );
			}
			else
			{
				static_assert( sizeof...( eArguments ) == 0 , "No constructor found for type" );
			}
		}

		public: template<typename CurrentType , typename... ExtendedArguments>
		constexpr static auto Allocate( BaseConstructorArguments&&... bArguments , const CurrentType& current , ExtendedArguments&&... eArguments )
		{
			if constexpr ( Type<ConstructedType>::template IsConstructible<BaseConstructorArguments...> )
			{
				return new Implementation::ExtendedType<ConstructedType , std::tuple<const CurrentType& , ExtendedArguments...>>( std::make_tuple( std::forward<const CurrentType&>( current ) , std::forward<ExtendedArguments&&>( eArguments )... ) , std::forward<BaseConstructorArguments&&>( bArguments )... );
			}
			else if constexpr ( sizeof...( eArguments ) > 0 )
			{
				return Constructor<ConstructedType , BaseConstructorArguments... , const CurrentType&>::Construct( std::forward<BaseConstructorArguments&&>( bArguments )... , std::forward<const CurrentType&>( current ) , std::forward<ExtendedArguments&&>( eArguments )... );
			}
			else
			{
				static_assert( sizeof...( eArguments ) == 0 , "No constructor found for type" );
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
		constexpr static inline auto Construct( Arguments&&... args )
		{
			return Implementation::Constructor<BaseType>::Construct( std::forward<Arguments&&>( args )... );
		}

		public:  template<typename... Arguments>
		constexpr static inline auto Allocate( Arguments&&... args )
		{
			return Implementation::Constructor<BaseType>::Allocate( std::forward<Arguments&&>( args )... );
		}
	};
}
