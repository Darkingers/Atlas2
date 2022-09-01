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
		public: inline static constexpr bool IsFundamental = FulfillsIsFundamental<DataType>::value;
		public: inline static constexpr bool IsConst = FulfillsIsConst<DataType>::value;
		public: inline static constexpr bool IsReference = FulfillsIsReference<DataType>::value;
		public: inline static constexpr bool IsPointer = FulfillsIsPointer<DataType>::value;
		public: inline static constexpr bool IsValue = FulfillsIsValue<DataType>::value;

		public: template<typename ComparedType>
		inline static constexpr bool IsSame = FulfillsIsSame<DataType , ComparedType>::value;

		public: template<typename... ComparedType>
		inline static constexpr bool IsAll = FulfillsIsAll<DataType , ComparedType...>::value;

		public: template<typename... ComparedType>
		inline static constexpr bool IsAny = FulfillsIsAny<DataType , ComparedType...>::value;

		public: template<typename... ComparedType>
		inline static constexpr bool IsNone = FulfillsIsNone<DataType , ComparedType...>::value;

		public: template<typename DerivedType>
		inline static constexpr bool IsBaseOf = FulfillsIsBaseOf<DataType , DerivedType>::value;

		public: template<typename BaseType>
		inline static constexpr bool IsDerivedFrom = FulfillsIsDerivedFrom<DataType , BaseType>::value;

		public: template<typename AssignedType>
		inline static constexpr bool IsAssignableFrom = FulfillsIsAssignableFrom<DataType , AssignedType>::value;


		public: using ConstType = std::conditional<IsConst , DataType , const DataType>;

		public: using ValueType = typename std::remove_const_t<typename std::remove_reference_t<DataType>>;
		public: using ConstValueType = const ValueType;

		public: using ReferenceType = ValueType&;
		public: using ConstReferenceType = const ReferenceType;

		public: using PointerType = ValueType*;
		public: using ConstPointerType = const PointerType;
	};
}