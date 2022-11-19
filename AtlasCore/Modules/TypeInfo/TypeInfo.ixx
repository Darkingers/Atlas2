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
	template<typename Type>
	class DLLApi TypeDetails
	{
		public:
	};
	
	template<typename Type>
	class DLLApi TypeInfo
	{
		public: inline static const char* Name = typeid( Type ).name( );	
		public: constexpr static inline bool IsFundamental = Concept::IsFundamental<Type>;
		public: constexpr static inline bool IsConst = Concept::IsConst<Type>;
		public: constexpr static inline bool IsReference = Concept::IsReference<Type>;
		public: constexpr static inline bool IsPointer = Concept::IsPointer<Type>;
		public: constexpr static inline bool IsValue = Concept::IsValue<Type>;
		public: constexpr static inline bool IsTuple = Concept::IsTuple<Type>;

		public: template<typename CastedType>
		constexpr static inline bool IsConvertibleTo = Concept::IsConvertibleTo<Type , CastedType>;
			
		public: template<typename CastedType>
		constexpr static inline bool IsNoexceptConvertibleTo = Concept::IsNoexceptConvertibleTo<Type , CastedType>;

		public: template<typename... ConstructorArgs>
		constexpr static inline bool IsConstructible = Concept::IsConstructible<Type , ConstructorArgs...>;

		public: template<typename... ConstructorArgs>
		constexpr static inline bool IsNoexceptConstructible = Concept::IsNoexceptConstructible<Type , ConstructorArgs...>;

		public: template<typename ComparedType>
		constexpr static inline bool IsSame = Concept::IsSame<Type , ComparedType>;

		public: template<typename... ComparedType>
		constexpr static inline bool IsAll = Concept::IsAll<Type , ComparedType...>;

		public: template<typename... ComparedType>
		constexpr static inline bool IsAny = Concept::IsAny<Type , ComparedType...>;

		public: template<typename... ComparedType>
		constexpr static inline bool IsNone = Concept::IsNone<Type , ComparedType...>;

		public: template<typename DerivedType>
		constexpr static inline bool IsBaseOf = Concept::IsBaseOf<Type , DerivedType>;

		public: template<typename BaseType>
		constexpr static inline bool IsDerivedFrom = Concept::IsDerivedFrom<Type , BaseType>;

		public: template<typename AssignedType>
		constexpr static inline bool IsAssignableFrom = Concept::IsAssignableFrom<Type , AssignedType>;


		public: using BaseType = typename Deduce::SimpleType<Type>;
		public: using ConstType = const BaseType;

		public: using ReferenceType = BaseType&;
		public: using ConstReferenceType = const ReferenceType;

		public: using PointerType = BaseType*;
		public: using ConstPointerType = const PointerType*;
	};
}