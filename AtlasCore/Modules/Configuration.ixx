export module AtlasConfiguration;

#if __has_include(<Atlas.Configuration.h>)
import  <Atlas.Configuration.h>
#endif

export namespace Atlas::Configuration
{
#ifndef ATLAS_ENSURE
#define ATLAS_ENSURE true
#endif

#ifndef ATLAS_ARGUMENT_CHECK
#define ATLAS_ARGUMENT_CHECK false
#endif

#ifndef ATLAS_COMPILETIME_ADAPTER_CHECK
#define ATLAS_COMPILETIME_ADAPTER_CHECK false
#endif

	constexpr bool EnableEnsure = ATLAS_ENSURE;
	constexpr bool EnableArgumentCheck = ATLAS_ARGUMENT_CHECK;
	constexpr bool DoCompiletimeAdapterCheck = ATLAS_COMPILETIME_ADAPTER_CHECK;
}

