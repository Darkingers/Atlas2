module;

#include "../../../../Macros/Macros.h"

export module AtlasDefinitions:TypeDetails;

export namespace Atlas::Definition
{
	template<typename T>
	class DLLApi TypeTraits
	{
		static_assert( false , "Type traits are not implemented for this type!" );
	};

	template<typename T>
	class DLLApi IteratorTraits
	{
		static_assert( false , "Iterator traits are not implemented for this type!" );
		public: using IteratedType = void;
	};

	template<typename T>
	class DLLApi CollectionTraits
	{
		static_assert( false , "Collection traits are not implemented for this type!" );
		public: using IteratorType = void;
		public: using ElementType = void;
	};
}