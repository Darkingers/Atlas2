module;

#include <algorithm>
#include <functional>
#include <type_traits>
#include <typeinfo>
#include "../../../Macros/Macros.h"

export module AtlasTypeInfo:Type;

import :BasicTypeInfo;
import :RelationalTypeInfo;
import :VariadicTypeInfo;

export namespace Atlas
{
	template<typename DataType>
	class DLLApi Type
	{
		public: inline static const char* Name = typeid( DataType ).name( );	
		public: constexpr inline static bool IsFundamental = Fulfills::IsFundamental<DataType>::value;
		public: constexpr inline static bool IsConst = Fulfills::IsConst<DataType>::value;
		public: constexpr inline static bool IsReference = Fulfills::IsReference<DataType>::value;
		public: constexpr inline static bool IsPointer = Fulfills::IsPointer<DataType>::value;
		public: constexpr inline static bool IsValue = Fulfills::IsValue<DataType>::value;
		public: constexpr inline static bool IsTuple = Fulfills::IsTuple<DataType>::value;

		public: template<typename CastedType>
		constexpr inline static bool IsNoexceptConvertibleTo = noexcept( (CastedType)std::declval<DataType>( ));

		public: template<typename... Args>
		constexpr inline static bool IsNoexceptConstructible = noexcept( std::declval<DataType>( std::declval<Args>( )... ) );

		public: template<typename ComparedType>
		constexpr inline static bool IsSame = Fulfills::IsSame<DataType , ComparedType>::value;

		public: template<typename... ComparedType>
		constexpr inline static bool IsAll = Fulfills::IsAll<DataType , ComparedType...>::value;

		public: template<typename... ComparedType>
		constexpr inline static bool IsAny = Fulfills::IsAny<DataType , ComparedType...>::value;

		public: template<typename... ComparedType>
		constexpr inline static bool IsNone = Fulfills::IsNone<DataType , ComparedType...>::value;

		public: template<typename DerivedType>
		constexpr inline static bool IsBaseOf = Fulfills::IsBaseOf<DataType , DerivedType>::value;

		public: template<typename BaseType>
		constexpr inline static bool IsDerivedFrom = Fulfills::IsDerivedFrom<DataType , BaseType>::value;

		public: template<typename AssignedType>
		constexpr inline static bool IsAssignableFrom = Fulfills::IsAssignableFrom<DataType , AssignedType>::value;


		public: using MutableType = typename std::remove_const_t<DataType>;
		public: using ConstType = const MutableType;

		public: using ReferenceType =typename std::remove_reference_t<MutableType>&;
		public: using ConstReferenceType = const ReferenceType;

		public: using PointerType = typename std::remove_reference_t<MutableType>*;
		public: using ConstPointerType = const PointerType*;
	};
}