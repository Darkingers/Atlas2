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
		private: template<unsigned int Current , unsigned int End , typename... Arguments>
		struct IsNoexceptReassign
		{
			public:
			constexpr static bool NoexceptCheck( )
			{
				bool result = noexcept( Tuple::Set<Current>( std::tuple<Arguments...>( ) , Deduce::IndexedArgumentType<Current , Arguments...>( ) ) );

				if constexpr ( End > Current -1)
				{
					result = result && IsNoexceptReassign<Current + 1 , End , Arguments...>::value;
				}

				return result;
			}

			public: constexpr static bool value = NoexceptCheck( );
		};

		public: template <unsigned int InclusiveFrom, unsigned int ExclusiveTo, typename TupleType>
		using SliceType = decltype( Tuple::Slice<InclusiveFrom , ExclusiveTo>( TupleType {} ) );

		public: template <unsigned int Index , typename TupleType>
		using ElementType = std::tuple_element_t<Index , TupleType>;
		
		public: template<typename... Arguments>
		constexpr static inline void Reassign( std::tuple<Arguments...>& tuple , Arguments&&... arguments )
			noexcept ( IsNoexceptReassign<0 , sizeof...( Arguments ) , Arguments...>::value )
		{
			Tuple::Reassign<0, sizeof...(Arguments)>( tuple , std::forward<Arguments&&>( arguments )... );
		}
			
		private: template<unsigned int InclusiveFrom , unsigned int ExclusiveTo,typename TupleType, typename CurrentType, typename... Arguments>
		constexpr static inline void Reassign( TupleType& tuple , CurrentType&& current, Arguments&&... arguments )
			noexcept ( IsNoexceptReassign<InclusiveFrom , ExclusiveTo , Arguments...>::value )
		{
			Tuple::Set<InclusiveFrom>( tuple , std::forward<CurrentType&&>(current) );
		
			if constexpr ( InclusiveFrom < ExclusiveTo )
			{
				Tuple::Reassign<InclusiveFrom + 1 , ExclusiveTo>( tuple , std::forward<Arguments&&>( arguments )... );
			}
		}

		public: template<typename... Arguments>
		constexpr static inline auto Make(Arguments&&... arguments )
			noexcept( Type<std::tuple<Arguments...>>::template IsNoexceptConstructible<Arguments&&...> )
		{
			return std::tuple<Arguments...>( std::forward<Arguments&&>( arguments )... );
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

		public: template<unsigned int Index , typename... Arguments>
		constexpr static inline void Set( std::tuple<Arguments...>& tuple , Deduce::IndexedArgumentType<Index,Arguments...> value )
			noexcept ( noexcept ( std::get<Index>( std::tuple<Arguments...>() ) = Deduce::IndexedArgumentType<Index , Arguments...>( ) ) )
		{
			std::get<Index>( tuple ) = value;
		}

		public: template<unsigned int InclusiveFrom, unsigned int ExclusiveTo, typename TupleType>
		constexpr static inline auto Slice( TupleType&& tuple )
			noexcept( noexcept ( Tuple::SliceImpl<InclusiveFrom>( TupleType( ) , std::make_index_sequence<ExclusiveTo - InclusiveFrom>{} ) ) )
		{
			return Tuple::SliceImpl<InclusiveFrom>( std::forward<TupleType&&>( tuple ) , std::make_index_sequence<ExclusiveTo - InclusiveFrom>{} );
		}

		public: template<unsigned int Start, unsigned int... Indexes, typename TupleType>
		constexpr static inline auto SliceImpl( TupleType&& tuple , std::index_sequence<Indexes...> )
			noexcept ( noexcept ( std::make_tuple( std::get<Start + Indexes>( TupleType( ) )... )) )
		{
			return std::make_tuple( std::get<Start + Indexes>( std::forward<TupleType&&>( tuple ) )... );
		}
	};
}
