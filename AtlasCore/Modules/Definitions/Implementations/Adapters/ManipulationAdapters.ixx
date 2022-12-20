module;

#include "../../../../../Macros/Macros.h"

export module AtlasDefinitions:ManipulationAdapters;

export namespace Atlas
{
	template<typename TCollection>
	class DLLApi ClearAdapter :
		public std::false_type
	{

	public:

		consteval static inline auto Clear( TCollection instance )
		{
			throw "ClearAdapter::Clear is not implemented for this type";
		}
	};

	template<typename... TArgs>
	class DLLApi ReplaceFromAdapter :
		public std::false_type
	{

	public:

		consteval static inline void ReplaceFrom( TArgs... args )
		{
			throw "ReplaceFromAdapter::ReplaceFrom is not implemented for this type";
		}
	};

	template<typename... TArgs>
	class DLLApi CopyAdapter :
		public std::false_type
	{

	public:

		consteval static inline void Copy( TArgs... args )
		{
			throw "CopyAdapter::Copy is not implemented for this type";
		}
	};

	template<typename... TArgs>
	class DLLApi ShiftAdapter
	{

	public:

		consteval static inline auto Shift( TArgs... args )
		{
			throw "ShiftAdapter::Shift is not implemented for this type";
		}
	};

	template<typename TCollection>
	class DLLApi ResizeAdapter
	{

	public:

		consteval static inline void Resize( TCollection instance , const unsigned int newSize )
		{
			throw "ResizeAdapter::Resize is not implemented for this type";
		}
	};
}
