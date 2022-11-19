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
		private: template<unsigned int Current , unsigned int End , typename... Args>
		struct IsNoexceptReassign
		{
			public:
			constexpr static bool NoexceptCheck( )
			{
				bool result = noexcept( Tuple::Set<Current>( std::tuple<Args...>( ) , Deduce::IndexedArgumentType<Current , Args...>( ) ) );

				if constexpr ( End > Current -1)
				{
					result = result && IsNoexceptReassign<Current + 1 , End , Args...>::value;
				}

				return result;
			}

			public: constexpr static bool value = NoexceptCheck( );
		};

		public: template <unsigned int InclusiveFrom, unsigned int ExclusiveTo, typename TupleType>
		using SliceType = decltype( Tuple::Slice<InclusiveFrom , ExclusiveTo>( TupleType {} ) );

		public: template <unsigned int Index , typename TupleType>
		using ElementType = std::tuple_element_t<Index , TupleType>;
		
		public: template<typename... Args>
		constexpr static inline void Reassign( std::tuple<Args...>& tuple , Args&&... arguments )
			noexcept ( IsNoexceptReassign<0 , sizeof...( Args ) , Args...>::value )
		{
			Tuple::Reassign<0, sizeof...(Args)>( tuple , std::forward<Args&&>( arguments )... );
		}
			
		private: template<unsigned int InclusiveFrom , unsigned int ExclusiveTo,typename TupleType, typename CurrentType, typename... Args>
		constexpr static inline void Reassign( TupleType& tuple , CurrentType&& current, Args&&... arguments )
			noexcept ( IsNoexceptReassign<InclusiveFrom , ExclusiveTo , Args...>::value )
		{
			Tuple::Set<InclusiveFrom>( tuple , std::forward<CurrentType&&>(current) );
		
			if constexpr ( InclusiveFrom < ExclusiveTo )
			{
				Tuple::Reassign<InclusiveFrom + 1 , ExclusiveTo>( tuple , std::forward<Args&&>( arguments )... );
			}
		}

		public: template<typename... Args>
		constexpr static inline auto Make(Args&&... arguments )
			noexcept( Type<std::tuple<Args...>>::template IsNoexceptConstructible<Args&&...> )
		{
			return std::tuple<Args...>( std::forward<Args&&>( arguments )... );
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

		public: template<unsigned int Index , typename... Args>
		constexpr static inline void Set( std::tuple<Args...>& tuple , Deduce::IndexedArgumentType<Index,Args...> value )
			noexcept ( noexcept ( std::get<Index>( std::tuple<Args...>() ) = Deduce::IndexedArgumentType<Index , Args...>( ) ) )
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