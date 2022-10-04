module;

#include "../../../Macros/Macros.h"
#include <tuple>
#include <utility>

export module AtlasExtensions:Tuple;
import AtlasDefinitions;
import AtlasConcepts;

export namespace Atlas::Extensions
{
	class DLLApi Tuple
	{
		public: template <unsigned int InclusiveFrom, unsigned int ExclusiveTo, typename TupleType>
		using SliceType = decltype( Tuple::Slice<InclusiveFrom , ExclusiveTo>( TupleType {} ) );

		public: template <unsigned int Index , typename TupleType>
		using ElementType = std::tuple_element_t<Index , TupleType>;
		
		public: template<typename... Args>
		constexpr inline static void Reassign( std::tuple<Args...>& tuple , Args&&... arguments )
		{
			Tuple::Reassign<0, sizeof...(Args)>( tuple , std::forward<Args&&>( arguments )... );
		}
			
		public: template<unsigned int InclusiveFrom , unsigned int ExclusiveTo , typename... Args>
		constexpr inline static void Reassign( std::tuple<Args...>& tuple , Args&&... arguments )
		{
			if constexpr ( InclusiveFrom < ExclusiveTo )
			{
				Tuple::Reassign<InclusiveFrom + 1 , ExclusiveTo>( tuple , std::forward<Args&&>( arguments )... );
			}
		}
			
		public: template<typename... Args>
		constexpr inline static auto Make(Args&&... arguments )
		{
			return std::tuple<Args...>( std::forward<Args&&>( arguments )... );
		}
			
		public: template<unsigned int Index, typename TupleType>
		constexpr inline static auto Get( TupleType& tuple )
		{
			return std::get<Index>( tuple );
		}

		private: template<unsigned int... Indexes , typename TupleType>
		constexpr inline static auto Get( TupleType&& tuple , std::index_sequence<Indexes...> )
		{
			return std::make_tuple( std::get<Indexes>( std::forward<TupleType&&>( tuple ) )... );
		}

		public: template<unsigned int Index , typename... Args>
		constexpr inline static void Set( std::tuple<Args...>& tuple , Deduce::IndexedArgumentType<Index,Args...> value )
		{
			std::get<Index>( tuple ) = value;
		}

		public: template<unsigned int InclusiveFrom, unsigned int ExclusiveTo, typename TupleType>
		constexpr inline static auto Slice( TupleType&& tuple )
		{
			return Tuple::SliceImpl<InclusiveFrom>( std::forward<TupleType&&>( tuple ) , std::make_index_sequence<ExclusiveTo - InclusiveFrom>{} );
		}

		private: template<unsigned int Index , unsigned int End , typename CurrentType , typename... Args>
			requires Concept::IsSame<CurrentType , typename std::tuple_element<Index , std::tuple<Args...>>::type>
		constexpr void Reassign( std::tuple<Args...>& tuple , CurrentType&& current , Args&&... arguments )
		{
			Tuple::Set<Index>( tuple, std::forward<CurrentType&&>( current ));

			if constexpr ( sizeof...( arguments ) > 0 && Index < End - 1 )
			{
				Tuple::Reassign<Index + 1 , End>( tuple , std::forward<Args&&>( arguments )... );
			}
		}

		public: template<unsigned int Start, unsigned int... Indexes, typename TupleType>
		constexpr inline static auto SliceImpl( TupleType&& tuple , std::index_sequence<Indexes...> )
		{
			return std::make_tuple( std::get<Start + Indexes>( std::forward<TupleType&&>( tuple ) )... );
		}
	};
}
