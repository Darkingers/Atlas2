module;

#include <algorithm>
#include <functional>
#include <type_traits>
#include <typeinfo>
#include "../../../Macros/Macros.h"

export module AtlasTypeInfo;

import AtlasConcepts;
import AtlasDefinitions;

export namespace Atlas
{
	template<typename DataType>
	class DLLApi Type
	{
		public: inline static const char* Name = typeid( DataType ).name( );	
		public: constexpr static inline bool IsFundamental = Concept::IsFundamental<DataType>;
		public: constexpr static inline bool IsConst = Concept::IsConst<DataType>;
		public: constexpr static inline bool IsReference = Concept::IsReference<DataType>;
		public: constexpr static inline bool IsPointer = Concept::IsPointer<DataType>;
		public: constexpr static inline bool IsValue = Concept::IsValue<DataType>;
		public: constexpr static inline bool IsTuple = Concept::IsTuple<DataType>;

		public: template<typename CastedType>
		constexpr static inline bool IsConvertibleTo = Concept::IsConvertibleTo<DataType , CastedType>;
			
		public: template<typename CastedType>
		constexpr static inline bool IsNoexceptConvertibleTo = Concept::IsNoexceptConvertibleTo<DataType , CastedType>;

		public: template<typename... ConstructorArgs>
		constexpr static inline bool IsConstructible = Concept::IsConstructible<DataType , ConstructorArgs...>;

		public: template<typename... ConstructorArgs>
		constexpr static inline bool IsNoexceptConstructible = Concept::IsNoexceptConstructible<DataType , ConstructorArgs...>;

		public: template<typename ComparedType>
		constexpr static inline bool IsSame = Concept::IsSame<DataType , ComparedType>;

		public: template<typename... ComparedType>
		constexpr static inline bool IsAll = Concept::IsAll<DataType , ComparedType...>;

		public: template<typename... ComparedType>
		constexpr static inline bool IsAny = Concept::IsAny<DataType , ComparedType...>;

		public: template<typename... ComparedType>
		constexpr static inline bool IsNone = Concept::IsNone<DataType , ComparedType...>;

		public: template<typename DerivedType>
		constexpr static inline bool IsBaseOf = Concept::IsBaseOf<DataType , DerivedType>;

		public: template<typename BaseType>
		constexpr static inline bool IsDerivedFrom = Concept::IsDerivedFrom<DataType , BaseType>;

		public: template<typename AssignedType>
		constexpr static inline bool IsAssignableFrom = Concept::IsAssignableFrom<DataType , AssignedType>;


		public: using BaseType = typename Deduce::SimpleType<DataType>;
		public: using ConstType = const BaseType;

		public: using ReferenceType = BaseType&;
		public: using ConstReferenceType = const ReferenceType;

		public: using PointerType = BaseType*;
		public: using ConstPointerType = const PointerType*;
	};
}