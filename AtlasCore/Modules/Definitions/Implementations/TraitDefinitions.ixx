module;

#include "../../../../Macros/Macros.h"

export module AtlasDefinitions:TraitDefinitions;

export namespace Atlas
{
	template<typename T>
	class DLLApi TypeTraits
	{
	};

	template<typename T>
	class DLLApi IteratorTraits :
		public std::false_type
	{
	
	public:
		
		using IteratedType = void;

		constexpr static inline bool BiDirectional = false;
		constexpr static inline bool RandomAccess = false;
	};

	template<typename T>
	class DLLApi CollectionTraits :
		public std::false_type
	{
		
	public:
		
		using ConstIteratorType = void;
		using IteratorType = void;
		using ElementType = void;

		constexpr static inline bool HasIterator = false;
	};
}