export module AtlasConfiguration;

#if __has_include(<Atlas.Configuration.h>)
import  <Atlas.Configuration.h>
#endif

export namespace Atlas::Configuration
{
#ifndef ATLAS_TRUE_STRING
#define ATLAS_TRUE_STRING "true"
#endif

#ifndef ATLAS_FALSE_STRING
#define ATLAS_FALSE_STRING "false"
#endif

#ifndef ATLAS_CONVERTER_CHECK
#define ATLAS_CONVERTER_CHECK true
#endif

#ifndef ATLAS_BOOL_CONVERTER_CHECK
#define ATLAS_BOOL_CONVERTER_CHECK true
#endif

#ifndef ATLAS_DOUBLE_CONVERTER_CHECK
#define ATLAS_DOUBLE_CONVERTER_CHECK true
#endif

#ifndef ATLAS_FLOAT_CONVERTER_CHECK
#define ATLAS_FLOAT_CONVERTER_CHECK true
#endif

#ifndef ATLAS_INT_CONVERTER_CHECK
#define ATLAS_INT_CONVERTER_CHECK true
#endif

#ifndef ATLAS_LONG_CONVERTER_CHECK
#define ATLAS_LONG_CONVERTER_CHECK true
#endif

#ifndef ATLAS_LONGLONG_CONVERTER_CHECK
#define ATLAS_LONGLONG_CONVERTER_CHECK true
#endif
	
#ifndef ATLAS_STRING_CONVERTER_CHECK
#define ATLAS_STRING_CONVERTER_CHECK true
#endif

#ifndef ATLAS_UNSIGNEDINT_CONVERTER_CHECK
#define ATLAS_UNSIGNEDINT_CONVERTER_CHECK true
#endif
	
#ifndef ATLAS_UNSIGNEDLONG_CONVERTER_CHECK
#define ATLAS_UNSIGNEDLONG_CONVERTER_CHECK true
#endif

#ifndef ATLAS_UNSIGNEDLONGLONG_CONVERTER_CHECK
#define ATLAS_UNSIGNEDLONGLONG_CONVERTER_CHECK true
#endif
	
	constexpr const char* TrueString = ATLAS_TRUE_STRING;
	constexpr const char* FalseString = ATLAS_FALSE_STRING;
		
	constexpr bool EnableConverterCheck = ATLAS_CONVERTER_CHECK;
	constexpr bool EnableBoolConverterCheck = EnableConverterCheck && ATLAS_BOOL_CONVERTER_CHECK;
	constexpr bool EnableDoubleConverterCheck = EnableConverterCheck && ATLAS_DOUBLE_CONVERTER_CHECK;
	constexpr bool EnableFloatConverterCheck = EnableConverterCheck && ATLAS_FLOAT_CONVERTER_CHECK;
	constexpr bool EnableIntConverterCheck = EnableConverterCheck && ATLAS_INT_CONVERTER_CHECK;
	constexpr bool EnableLongConverterCheck = EnableConverterCheck && ATLAS_LONG_CONVERTER_CHECK;
	constexpr bool EnableLongLongConverterCheck = EnableConverterCheck && ATLAS_LONGLONG_CONVERTER_CHECK;
	constexpr bool EnableStringConverterCheck = EnableConverterCheck && ATLAS_STRING_CONVERTER_CHECK;
	constexpr bool EnableUnsignedIntConverterCheck = EnableConverterCheck && ATLAS_UNSIGNEDINT_CONVERTER_CHECK;
	constexpr bool EnableUnsignedLongConverterCheck = EnableConverterCheck && ATLAS_UNSIGNEDLONG_CONVERTER_CHECK;
	constexpr bool EnableUnsignedLongLongConverterCheck = EnableConverterCheck && ATLAS_UNSIGNEDLONGLONG_CONVERTER_CHECK;

}

