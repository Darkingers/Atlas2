module;

#include "../../../../Macros/Macros.h"

export module AtlasCoreInterfaces:IException;

export namespace Atlas
{
	/// <summary>
	/// A base class for all exceptions
	/// </summary>
	class DLLApi IException 
	{
		public:
		virtual ~IException( ) = default;
		
		/// <summary>
		/// Returns the details of the exception
		/// </summary>
		public:
		virtual const char* ToString( ) const noexcept = 0;
	};
}