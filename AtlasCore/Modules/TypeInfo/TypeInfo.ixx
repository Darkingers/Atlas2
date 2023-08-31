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
	template<typename T>
	class DLLApi Type
	{
		
	public:

		constexpr static inline auto Name = Implementation::TypeName::Extract<T>( );
		constexpr static inline bool IsFundamental = Concept::IsFundamental<T>;
		constexpr static inline bool IsConst = Concept::IsConst<T>;
		constexpr static inline bool IsReference = Concept::IsReference<T>;
		constexpr static inline bool IsPointer = Concept::IsPointer<T>;
		constexpr static inline bool IsValue = Concept::IsValue<T>;
		constexpr static inline bool IsTuple = Concept::IsTuple<T>;

		template<typename CastedType>
		constexpr static inline bool IsConvertibleTo = Concept::IsConvertibleTo<T , CastedType>;
			
		template<typename CastedType>
		constexpr static inline bool IsNoexceptConvertibleTo = Concept::IsNoexceptConvertibleTo<T , CastedType>;

		template<typename... ConstructorTArgs>
		constexpr static inline bool IsConstructible = Concept::IsConstructible<T , ConstructorTArgs...>;

		template<typename... ConstructorTArgs>
		constexpr static inline bool IsNoexceptConstructible = Concept::IsNoexceptConstructible<T , ConstructorTArgs...>;

		template<typename ComparedType>
		constexpr static inline bool IsSame = Concept::IsSame<T , ComparedType>;

		template<typename... ComparedType>
		constexpr static inline bool IsAll = Concept::IsAll<T , ComparedType...>;

		template<typename... ComparedType>
		constexpr static inline bool IsAny = Concept::IsAny<T , ComparedType...>;

		template<typename... ComparedType>
		constexpr static inline bool IsNone = Concept::IsNone<T , ComparedType...>;

		template<typename DerivedType>
		constexpr static inline bool IsBaseOf = Concept::IsBaseOf<T , DerivedType>;

		template<typename BaseType>
		constexpr static inline bool IsDerivedFrom = Concept::IsDerivedFrom<T , BaseType>;

		template<typename AssignedType>
		constexpr static inline bool IsAssignable = Concept::IsAssignable<T , AssignedType>;


		using BaseType = typename Deduce::SimpleType<T>;
		using ConstType = const BaseType;

		using ReferenceType = BaseType&;
		using ConstReferenceType = const ReferenceType;

		using PointerType = BaseType*;
		using ConstPointerType = const PointerType*;
	};
}