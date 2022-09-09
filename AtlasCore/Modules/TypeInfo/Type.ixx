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
		public: inline static constexpr bool IsFundamental = Fulfills::IsFundamental<DataType>::value;
		public: inline static constexpr bool IsConst = Fulfills::IsConst<DataType>::value;
		public: inline static constexpr bool IsReference = Fulfills::IsReference<DataType>::value;
		public: inline static constexpr bool IsPointer = Fulfills::IsPointer<DataType>::value;
		public: inline static constexpr bool IsValue = Fulfills::IsValue<DataType>::value;

		public: template<typename ComparedType>
		inline static constexpr bool IsSame = Fulfills::IsSame<DataType , ComparedType>::value;

		public: template<typename... ComparedType>
		inline static constexpr bool IsAll = Fulfills::IsAll<DataType , ComparedType...>::value;

		public: template<typename... ComparedType>
		inline static constexpr bool IsAny = Fulfills::IsAny<DataType , ComparedType...>::value;

		public: template<typename... ComparedType>
		inline static constexpr bool IsNone = Fulfills::IsNone<DataType , ComparedType...>::value;

		public: template<typename DerivedType>
		inline static constexpr bool IsBaseOf = Fulfills::IsBaseOf<DataType , DerivedType>::value;

		public: template<typename BaseType>
		inline static constexpr bool IsDerivedFrom = Fulfills::IsDerivedFrom<DataType , BaseType>::value;

		public: template<typename AssignedType>
		inline static constexpr bool IsAssignableFrom = Fulfills::IsAssignableFrom<DataType , AssignedType>::value;


		public: using MutableType = typename std::remove_const_t<DataType>;
		public: using ConstType = const MutableType;

		public: using ReferenceType = MutableType&;
		public: using ConstReferenceType = ConstType&;

		public: using PointerType = MutableType*;
		public: using ConstPointerType = ConstType*;
	};
}