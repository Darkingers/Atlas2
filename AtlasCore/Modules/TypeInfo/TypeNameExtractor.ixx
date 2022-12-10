module;

#include "../../../Macros/Macros.h"
#include <string>
#include <string_view>
#include <array>   
#include <utility> 

export module AtlasTypeInfo:TypeNameExtractor;

export namespace Atlas::Implementation
{
	/// <summary>
	/// Helper class to extract a compile-time compatible type name
	/// </summary>
	template<typename T>
	class DLLApi TypeName
	{
		template <std::size_t...Idxs>
		constexpr static inline auto SliceString( std::string_view str , std::index_sequence<Idxs...> )
		{
			return std::array { str[Idxs]..., '\n' };
		}

		template <typename T>
		constexpr static inline auto CreateTypename( )
		{
#if defined(__clang__)
			constexpr auto prefix = std::string_view { "[T = " };
			constexpr auto suffix = std::string_view { "]" };
			constexpr auto function = std::string_view { __PRETTY_FUNCTION__ };
#elif defined(__GNUC__)
			constexpr auto prefix = std::string_view { "with T = " };
			constexpr auto suffix = std::string_view { "]" };
			constexpr auto function = std::string_view { __PRETTY_FUNCTION__ };
#elif defined(_MSC_VER)
			constexpr auto prefix = std::string_view { "type_name_array<" };
			constexpr auto suffix = std::string_view { ">(void)" };
			constexpr auto function = std::string_view { __FUNCSIG__ };
#else
# error Unsupported compiler
#endif

			constexpr auto start = function.find( prefix ) + prefix.size( );
			constexpr auto end = function.rfind( suffix );

			static_assert( start < end );

			constexpr auto name = function.substr( start , ( end - start ) );
			return SliceString( name , std::make_index_sequence<name.size( )>{} );
		}

		template <typename T>
		struct TypenameHolder
		{
			static inline constexpr auto value = CreateTypename<T>( );
		};

		template <typename T>
		constexpr static inline auto Extract( ) -> std::string_view
		{
			constexpr auto& value = TypenameHolder<T>::value;
			return std::string_view { value.data( ), value.size( ) };
		}
	};
}