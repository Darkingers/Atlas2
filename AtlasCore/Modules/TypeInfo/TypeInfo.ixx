module;

#include <algorithm>
#include <functional>
#include <type_traits>
#include <typeinfo>
#include "../../../Macros/Macros.h"

export module AtlasTypeInfo;
import :TypeNameExtractor;

import AtlasConcepts;
import AtlasDefinitions;

export namespace Atlas
{
	/// <summary>
	/// Compile-time evaulation compatible traits of the given type
	/// </summary>
	template<typename T>
	class DLLApi Type
	{
		public: constexpr static inline auto Name = Implementation::TypeName::Extract<T>( );
		public: constexpr static inline bool IsFundamental = Concept::IsFundamental<T>;
		public: constexpr static inline bool IsConst = Concept::IsConst<T>;
		public: constexpr static inline bool IsReference = Concept::IsReference<T>;
		public: constexpr static inline bool IsPointer = Concept::IsPointer<T>;
		public: constexpr static inline bool IsValue = Concept::IsValue<T>;
		public: constexpr static inline bool IsTuple = Concept::IsTuple<T>;

		public: template<typename CastedType>
		constexpr static inline bool IsConvertibleTo = Concept::IsConvertibleTo<T , CastedType>;
			
		public: template<typename CastedType>
		constexpr static inline bool IsNoexceptConvertibleTo = Concept::IsNoexceptConvertibleTo<T , CastedType>;

		public: template<typename... ConstructorTArgs>
		constexpr static inline bool IsConstructible = Concept::IsConstructible<T , ConstructorTArgs...>;

		public: template<typename... ConstructorTArgs>
		constexpr static inline bool IsNoexceptConstructible = Concept::IsNoexceptConstructible<T , ConstructorTArgs...>;

		public: template<typename ComparedType>
		constexpr static inline bool IsSame = Concept::IsSame<T , ComparedType>;

		public: template<typename... ComparedType>
		constexpr static inline bool IsAll = Concept::IsAll<T , ComparedType...>;

		public: template<typename... ComparedType>
		constexpr static inline bool IsAny = Concept::IsAny<T , ComparedType...>;

		public: template<typename... ComparedType>
		constexpr static inline bool IsNone = Concept::IsNone<T , ComparedType...>;

		public: template<typename DerivedType>
		constexpr static inline bool IsBaseOf = Concept::IsBaseOf<T , DerivedType>;

		public: template<typename BaseType>
		constexpr static inline bool IsDerivedFrom = Concept::IsDerivedFrom<T , BaseType>;

		public: template<typename AssignedType>
		constexpr static inline bool IsAssignable = Concept::IsAssignable<T , AssignedType>;


		public: using BaseType = typename Deduce::SimpleType<T>;
		public: using ConstType = const BaseType;

		public: using ReferenceType = BaseType&;
		public: using ConstReferenceType = const ReferenceType;

		public: using PointerType = BaseType*;
		public: using ConstPointerType = const PointerType*;
	};
}