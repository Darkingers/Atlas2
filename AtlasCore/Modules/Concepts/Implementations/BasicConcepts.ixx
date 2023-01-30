module;

#include <algorithm>
#include <functional>
#include <type_traits>
#include <typeinfo>

export module AtlasConcepts:BasicConcepts;

import AtlasDefinitions;

namespace Atlas::Concept::Implementation
{
	template <typename T>
	class IsTuple :
		public std::false_type
	{};

	template <typename ...T>
	class IsTuple<std::tuple<T...>> :
		public std::true_type
	{};
}

export namespace Atlas::Concept
{
	template<typename T>
	concept IsPointer = std::is_pointer<T>::value;

	template<typename T>
	concept IsReference = std::is_reference<T>::value;

	template<typename T>
	concept IsValue = !IsPointer<T> && !IsReference<T>;

	template<typename T>
	concept IsFundamental = std::is_fundamental<T>::value;

	template<typename T>
	concept IsConst = std::is_const<T>::value;

	template<typename T>
	concept IsFloat = std::is_floating_point<std::remove_reference<T>>::value;

	template<typename T>
	concept IsBoolean = std::_Boolean_testable<std::remove_reference<T>>;

	template<typename T>
	concept IsInteger = std::is_integral<std::remove_reference<T>>::value;

	template<typename T>
	concept IsTuple = Implementation::IsTuple<T>::value;

	template<typename TCollection>
	concept IsArray = std::is_array<TCollection>::value;

	template<typename TCollection, typename TElement>
	concept IsArrayOf = IsArray<TCollection> && std::is_same_v<std::remove_all_extents_t<TCollection> , TElement>;

	template<typename TCollection>
	concept IsCollection = CollectionTraits<TCollection>::value;
	
	template<typename TCollection , typename TElement>
	concept IsCollectionOf = IsCollection<TCollection> && std::is_same_v<typename CollectionTraits<TCollection>::ElementType , TElement>;

	template<typename TCollectionA , typename TCollectionB>
	concept AreCompatibleCollections = IsCollection<TCollectionA> && IsCollection<TCollectionB> && std::is_same_v<typename CollectionTraits<TCollectionA>::ElementType , typename CollectionTraits<TCollectionB>::ElementType>;
}