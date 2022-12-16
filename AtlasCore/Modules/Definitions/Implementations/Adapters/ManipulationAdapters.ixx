module;

#include "../../../../../Macros/Macros.h"

export module AtlasDefinitions:ManipulationAdapters;

export namespace Atlas
{
	// Code generation helper:
	// Clear<TCollection>-auto Clear(TCollection)
	// ReplaceFrom<TITerator,TSource>-auto ReplaceFrom(TIterator, TSource, unsigned int)
	// Copy<TIteratorSource,TITeratorTarget>-auto Move(TIteratorSource, TIteratorTarget, unsigned int)
	// Shift<TCollection>-auto Shift(T, int, unsigned int)
	// Resize<TCollection>-void Resize( T, unsigned int)

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

	template<typename TIterator , typename TSource>
	class DLLApi ReplaceFromAdapter :
		public std::false_type
	{

	public:

		consteval static inline void ReplaceFrom( TIterator iterator ,TSource source )
		{
			throw "ReplaceFromAdapter::ReplaceFrom is not implemented for this type";
		}
	};

	template<typename TIteratorSource , typename TITeratorTarget>
	class DLLApi CopyAdapter :
		public std::false_type
	{

	public:

		consteval static inline void Copy( TIteratorSource source , TITeratorTarget target ,const unsigned int copyLength )
		{
			throw "CopyAdapter::Copy is not implemented for this type";
		}
	};

	template<typename TCollection>
	class DLLApi ShiftAdapter
	{

	public:

		consteval static inline auto Shift( TCollection shifted ,const unsigned int shiftStart , const int shiftOffset, const unsigned int shiftLength )
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
