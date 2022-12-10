module;

#include "../../../../Macros/Macros.h"
#include <tuple>
#include <utility>
#include <algorithm>

export module AtlasExtensions:Tuple;
import AtlasDefinitions;
import AtlasConcepts;
import AtlasConverters;
import AtlasTypeInfo;

export namespace Atlas
{
	class DLLApi Tuple
	{
		private: template<unsigned int Current , unsigned int End , typename... TArgs>
		struct IsNoexceptReassign
		{
			public:
			constexpr static bool NoexceptCheck( )
			{
				bool result = noexcept( Tuple::Set<Current>( std::tuple<TArgs...>( ) , Deduce::IndexedArgumentType<Current , TArgs...>( ) ) );

				if constexpr ( End > Current -1)
				{
					result = result && IsNoexceptReassign<Current + 1 , End , TArgs...>::value;
				}

				return result;
			}

			public: constexpr static bool value = NoexceptCheck( );
		};

		public: template <unsigned int inclusiveStart, unsigned int exclusiveEnd, typename TupleType>
		using SliceType = decltype( Tuple::Slice<inclusiveStart , exclusiveEnd>( TupleType {} ) );

		public: template <unsigned int Index , typename TupleType>
		using TElement = std::tuple_element_t<Index , TupleType>;
		
		public: template<typename... TArgs>
		constexpr static inline void Reassign( std::tuple<TArgs...>& tuple , TArgs&&... args )
			noexcept ( IsNoexceptReassign<0 , sizeof...( TArgs ) , TArgs...>::value )
		{
			Tuple::Reassign<0, sizeof...(TArgs)>( tuple , std::forward<TArgs&&>( TArgs )... );
		}
			
		private: template<unsigned int inclusiveStart , unsigned int exclusiveEnd,typename TupleType, typename CurrentType, typename... TArgs>
		constexpr static inline void Reassign( TupleType& tuple , CurrentType&& current, TArgs&&... args )
			noexcept ( IsNoexceptReassign<inclusiveStart , exclusiveEnd , TArgs...>::value )
		{
			Tuple::Set<inclusiveStart>( tuple , std::forward<CurrentType&&>(current) );
		
			if constexpr ( inclusiveStart < exclusiveEnd )
			{
				Tuple::Reassign<inclusiveStart + 1 , exclusiveEnd>( tuple , std::forward<TArgs&&>( TArgs )... );
			}
		}

		public: template<typename... TArgs>
		constexpr static inline auto Make(TArgs&&... args )
			noexcept( Type<std::tuple<TArgs...>>::template IsNoexceptConstructible<TArgs&&...> )
		{
			return std::tuple<TArgs...>( std::forward<TArgs&&>( TArgs )... );
		}
			
		public: template<unsigned int Index, typename TupleType>
		constexpr static inline auto Get( TupleType& tuple ) 
			noexcept( noexcept( std::get<Index>( TupleType()) ) )
		{
			return std::get<Index>( tuple );
		}

		private: template<unsigned int... Indexes , typename TupleType>
		constexpr static inline auto Get( TupleType&& tuple , std::index_sequence<Indexes...> )
			noexcept ( noexcept ( std::make_tuple( std::get<Indexes>( TupleType() )... ) ) )
		{
			return std::make_tuple( std::get<Indexes>( std::forward<TupleType&&>( tuple ) )... );
		}

		public: template<unsigned int Index , typename... TArgs>
		constexpr static inline void Set( std::tuple<TArgs...>& tuple , Deduce::IndexedArgumentType<Index,TArgs...> value )
			noexcept ( noexcept ( std::get<Index>( std::tuple<TArgs...>() ) = Deduce::IndexedArgumentType<Index , TArgs...>( ) ) )
		{
			std::get<Index>( tuple ) = value;
		}

		public: template<unsigned int inclusiveStart, unsigned int exclusiveEnd, typename TupleType>
		constexpr static inline auto Slice( TupleType&& tuple )
			noexcept( noexcept ( Tuple::SliceImpl<inclusiveStart>( TupleType( ) , std::make_index_sequence<exclusiveEnd - inclusiveStart>{} ) ) )
		{
			return Tuple::SliceImpl<inclusiveStart>( std::forward<TupleType&&>( tuple ) , std::make_index_sequence<exclusiveEnd - inclusiveStart>{} );
		}

		public: template<unsigned int Start, unsigned int... Indexes, typename TupleType>
		constexpr static inline auto SliceImpl( TupleType&& tuple , std::index_sequence<Indexes...> )
			noexcept ( noexcept ( std::make_tuple( std::get<Start + Indexes>( TupleType( ) )... )) )
		{
			return std::make_tuple( std::get<Start + Indexes>( std::forward<TupleType&&>( tuple ) )... );
		}
	};
}
