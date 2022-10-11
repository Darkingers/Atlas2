module;

#include <algorithm>
#include <functional>
#include <type_traits>
#include <typeinfo>
#include "../../../Macros/Macros.h"

export module AtlasTypeInfo:Type;

import AtlasConcepts;
import AtlasDefinitions;

export namespace Atlas
{
	template<typename DataType>
	class DLLApi Type
	{
		public: inline static const char* Name = typeid( DataType ).name( );	
		public: constexpr inline static bool IsFundamental = Concept::IsFundamental<DataType>;
		public: constexpr inline static bool IsConst = Concept::IsConst<DataType>;
		public: constexpr inline static bool IsReference = Concept::IsReference<DataType>;
		public: constexpr inline static bool IsPointer = Concept::IsPointer<DataType>;
		public: constexpr inline static bool IsValue = Concept::IsValue<DataType>;
		public: constexpr inline static bool IsTuple = Concept::IsTuple<DataType>;

		public: template<typename CastedType>
		constexpr inline static bool IsConvertibleTo = Concept::IsConvertibleTo<DataType , CastedType>;
			
		public: template<typename CastedType>
		constexpr inline static bool IsNoexceptConvertibleTo = Concept::IsNoexceptConvertibleTo<DataType , CastedType>;

		public: template<typename... ConstructorArgs>
		constexpr inline static bool IsConstructible = Concept::IsConstructible<DataType , ConstructorArgs...>;

		public: template<typename... ConstructorArgs>
		constexpr inline static bool IsNoexceptConstructible = Concept::IsNoexceptConstructible<DataType , ConstructorArgs...>;

		public: template<typename ComparedType>
		constexpr inline static bool IsSame = Concept::IsSame<DataType , ComparedType>;

		public: template<typename... ComparedType>
		constexpr inline static bool IsAll = Concept::IsAll<DataType , ComparedType...>;

		public: template<typename... ComparedType>
		constexpr inline static bool IsAny = Concept::IsAny<DataType , ComparedType...>;

		public: template<typename... ComparedType>
		constexpr inline static bool IsNone = Concept::IsNone<DataType , ComparedType...>;

		public: template<typename DerivedType>
		constexpr inline static bool IsBaseOf = Concept::IsBaseOf<DataType , DerivedType>;

		public: template<typename BaseType>
		constexpr inline static bool IsDerivedFrom = Concept::IsDerivedFrom<DataType , BaseType>;

		public: template<typename AssignedType>
		constexpr inline static bool IsAssignableFrom = Concept::IsAssignableFrom<DataType , AssignedType>;


		public: using BaseType = typename Deduce::SimpleType<DataType>;
		public: using ConstType = const BaseType;

		public: using ReferenceType = BaseType&;
		public: using ConstReferenceType = const ReferenceType;

		public: using PointerType = BaseType*;
		public: using ConstPointerType = const PointerType*;
	
		public: template<typename... ConstructorArgs>
			requires Concept::IsConstructible<DataType , ConstructorArgs...>
		constexpr inline static auto Instance( )
		{
			return std::declval<DataType>( std::declval<ConstructorArgs>()...);
		}

		
	};
}