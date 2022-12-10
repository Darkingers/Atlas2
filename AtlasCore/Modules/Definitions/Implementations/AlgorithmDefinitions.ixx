module;

#include "../../../../Macros/Macros.h"

export module AtlasDefinitions:DataAlgorithmDefinitions;

export namespace Atlas
{
	template<typename TTarget , typename... TSource>
	class DLLApi CopyAdapter
	{
		public:
		constexpr void Copy( TTarget& target , const TSource&... source )
			const noexcept
		{
			throw "CopyAlgorythm::Copy is not implemented for this type";
		}
	};
}