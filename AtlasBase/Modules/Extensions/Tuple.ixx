module;

#include "../../../Macros/Macros.h"
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
				bool result = noexcept( Tuple::Set<Current>( std::declval<std::tuple<Args...>>( ) , std::declval<Deduce::IndexedArgumentType<Current , Args...>>( ) ) );

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
		constexpr inline static void Reassign( std::tuple<Args...>& tuple , Args&&... arguments )
			noexcept ( IsNoexceptReassign<0 , sizeof...( Args ) , Args...>::value )
		{
			Tuple::Reassign<0, sizeof...(Args)>( tuple , std::forward<Args&&>( arguments )... );
		}
			
		private: template<unsigned int InclusiveFrom , unsigned int ExclusiveTo,typename TupleType, typename CurrentType, typename... Args>
		constexpr inline static void Reassign( TupleType& tuple , CurrentType&& current, Args&&... arguments )
			noexcept ( IsNoexceptReassign<InclusiveFrom , ExclusiveTo , Args...>::value )
		{
			Tuple::Set<InclusiveFrom>( tuple , std::forward<CurrentType&&>(current) );
		
			if constexpr ( InclusiveFrom < ExclusiveTo )
			{
				Tuple::Reassign<InclusiveFrom + 1 , ExclusiveTo>( tuple , std::forward<Args&&>( arguments )... );
			}
		}

		public: template<typename... Args>
		constexpr inline static auto Make(Args&&... arguments )
			noexcept( Type<std::tuple<Args...>>::template IsNoexceptConstructible<Args&&...> )
		{
			return std::tuple<Args...>( std::forward<Args&&>( arguments )... );
		}
			
		public: template<unsigned int Index, typename TupleType>
		constexpr inline static auto Get( TupleType& tuple ) 
			noexcept(std::get<Index>(std::declval<TupleType>() ) ) 
		{
			return std::get<Index>( tuple );
		}

		private: template<unsigned int... Indexes , typename TupleType>
		constexpr inline static auto Get( TupleType&& tuple , std::index_sequence<Indexes...> )
			noexcept ( noexcept ( std::make_tuple( std::get<Indexes>( std::declval<TupleType>() )... ) ) )
		{
			return std::make_tuple( std::get<Indexes>( std::forward<TupleType&&>( tuple ) )... );
		}

		public: template<unsigned int Index , typename... Args>
		constexpr inline static void Set( std::tuple<Args...>& tuple , Deduce::IndexedArgumentType<Index,Args...> value )
			noexcept ( noexcept ( std::get<Index>( std::declval<std::tuple<Args...>>() ) = std::declval<Deduce::IndexedArgumentType<Index , Args...>>( ) ) )
		{
			std::get<Index>( tuple ) = value;
		}

		public: template<unsigned int InclusiveFrom, unsigned int ExclusiveTo, typename TupleType>
		constexpr inline static auto Slice( TupleType&& tuple )
			noexcept( noexcept ( Tuple::SliceImpl<InclusiveFrom>( std::declval<TupleType>( ) , std::make_index_sequence<ExclusiveTo - InclusiveFrom>{} ) ) )
		{
			return Tuple::SliceImpl<InclusiveFrom>( std::forward<TupleType&&>( tuple ) , std::make_index_sequence<ExclusiveTo - InclusiveFrom>{} );
		}

		public: template<unsigned int Start, unsigned int... Indexes, typename TupleType>
		constexpr inline static auto SliceImpl( TupleType&& tuple , std::index_sequence<Indexes...> )
			noexcept ( noexcept ( std::make_tuple( std::get<Start + Indexes>( std::declval<TupleType>( ) )... )) )
		{
			return std::make_tuple( std::get<Start + Indexes>( std::forward<TupleType&&>( tuple ) )... );
		}
	};
}

export namespace Atlas::Converters
{
	template<typename SourceType>
		requires Type<SourceType>::IsTuple
	class DLLApi Converter<SourceType , std::string> :
		public std::true_type
	{
		private: template<unsigned int Current , unsigned int End>
		struct IsNoexceptConvertable
		{
		

			public:
			constexpr static bool NoexceptCheck( )
			{
				bool result = noexcept( Atlas::Convert<std::string>::From( std::declval<Deduce::TupleIndexedType<Current,SourceType>>( ) ) );
				
				if constexpr ( End > Current - 1 )
				{
					result = result && IsNoexceptConvertable<Current + 1 , End>::value;
				}

				return result;
			}

			public: constexpr static bool value = NoexceptCheck( );
		};

		public:
		inline static std::string Convert( const SourceType& data , const std::string& delimiter = "," )
			noexcept ( IsNoexceptConvertable<0 , std::tuple_size_v<SourceType>>::value )
		{
			std::string result = Atlas::Convert<std::string>::From( Tuple::Get<0>( data ) );
	
			Converter<SourceType , std::string>::ConvertRemainingToString<1 , std::tuple_size<SourceType>::value>( data , result , delimiter );
	
			return result;
		}
	
		private: template<unsigned int Current, unsigned int End>
		inline static void ConvertRemainingToString( const SourceType& data , std::string& result , const std::string& delimiter )
		{
			if constexpr ( End > Current )
			{
				result += delimiter + Atlas::Convert<std::string>::From( Tuple::Get<0><Current>( data ) );

				Converter<SourceType , std::string>::ConvertRemainingToString<Current + 1 , End>( data , result , delimiter );
			}
		}
	};
}