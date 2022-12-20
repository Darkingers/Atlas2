module;

#include "../../../../../Macros/Macros.h"

export module AtlasDefinitions:QueryAdapters;

export namespace Atlas
{
	
	template<typename TExpected , typename TActual>
	class DLLApi CountTypeAdapter :
		public std::false_type
	{

	public:

		consteval static inline auto Count( TActual instance )
		{
			throw "CountAdapter::Count is not implemented for this type";
		}
	};

	template<typename... TArgs>
	class DLLApi LengthAdapter :
		public std::false_type
	{

	public:

		consteval static inline auto Length( TArgs... args )
		{
			throw "LengthAdapter::Length is not implemented for this type";
		}
	};

	template<typename... TArgs>
	class DLLApi ContainAdapter :
		public std::false_type
	{

		public:

		consteval static inline auto Contain( TArgs... args )
		{
			throw "ContainAdapter::Contain is not implemented for this type";
		}
	};

	template<typename... TArgs>
	class DLLApi CountElementAdapter :
		public std::false_type
	{

	public:

		consteval static inline auto Count( TArgs... args )
		{
			throw "ContainAdapter::Contain is not implemented for this type";
		}
	};

	template<typename... TArgs>
	class DLLApi MatchAdapter :
		public std::false_type
	{

	public:

		consteval static inline auto Match( TArgs... args )
		{
			throw "MatchAdapter::Match is not implemented for this type";
		}
	};

	template<typename... TArgs>
	class DLLApi ContainPatternAdapter :
		public std::false_type
	{
		public:

		consteval static inline auto ContainsPattern( TArgs... args )
		{
			throw "ContainPatternAdapter::ContainsPattern is not implemented for this type";
		}
	};

	template<typename... TArgs>
	class DLLApi CountPatternAdapter :
		public std::false_type
	{
		public:

		consteval static inline auto CountPattern( TArgs... args )
		{
			throw "CountPatternAdapter::CountPattern is not implemented for this type";
		}
	};

	template<typename... TArgs>
	class DLLApi AnyAdapter :
		public std::false_type
	{
		public:

		consteval static inline auto Any( TArgs... args )
		{
			throw "AnyAdapter::Any is not implemented for this type";
		}
	};

	template<typename... TArgs>
	class DLLApi AllAdapter :
		public std::false_type
	{
		public:

		consteval static inline auto All( TArgs... args )
		{
			throw "AllAdapter::All is not implemented for this type";
		}
	};
}
