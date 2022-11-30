module;

#include "../../../../Macros/Macros.h"

export module AtlasDefinitions:TraitDefinitions;

export namespace Atlas::Definition
{
	template<typename T>
	class DLLApi TypeTraits
	{
	};

	template<typename T>
	class DLLApi IteratorTraits
	{
		public: using IteratedType = void;
	};

	template<typename T>
	class DLLApi CollectionTraits
	{
		public: using ConstIteratorType = void;
		public: using IteratorType = void;
		public: using ElementType = void;
	};
}