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
		public: constexpr inline static char* Name = typeid( DataType ).name( );	
		public: constexpr inline static bool IsFundamental = Fulfills::IsFundamental<DataType>::value;
		public: constexpr inline static bool IsConst = Fulfills::IsConst<DataType>::value;
		public: constexpr inline static bool IsReference = Fulfills::IsReference<DataType>::value;
		public: constexpr inline static bool IsPointer = Fulfills::IsPointer<DataType>::value;
		public: constexpr inline static bool IsValue = Fulfills::IsValue<DataType>::value;

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

		public: using ReferenceType = MutableType&;
		public: using ConstReferenceType = ConstType&;

		public: using PointerType = MutableType*;
		public: using ConstPointerType = ConstType*;
	};
}