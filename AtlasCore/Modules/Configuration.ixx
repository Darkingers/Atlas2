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

#ifndef ATLAS_STATIC_STRING_BUFFER_SIZE
#define ATLAS_STATIC_STRING_BUFFER_SIZE 1024
#endif

#ifndef ATLAS_STATIC_ARRAY_BUFFER_SIZE
#define ATLAS_STATIC_ARRAY_BUFFER_SIZE 1024
#endif

#ifndef ATLAS_STATIC_STRING_CHECK
#define ATLAS_STATIC_STRING_CHECK true
#endif

#ifndef ATLAS_STATIC_ARRAY_CHECK
#define ATLAS_STATIC_ARRAY_CHECK true
#endif

#ifndef ATLAS_MATH_PI
#define ATLAS_MATH_PI 3.141592653589793238462643383279502884197169
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


#ifndef ATLAS_STATISTICS_CHECK
#define ATLAS_STATISTICS_CHECK true
#endif

#ifndef ATLAS_STATISTICS_AVERAGE_CHECK
#define ATLAS_STATISTICS_AVERAGE_CHECK true
#endif

#ifndef ATLAS_STATISTICS_DEVIATION_CHECK
#define ATLAS_STATISTICS_DEVIATION_CHECK true
#endif

#ifndef ATLAS_STATISTICS_MAXIMUM_CHECK
#define ATLAS_STATISTICS_MAXIMUM_CHECK true
#endif

#ifndef ATLAS_STATISTICS_MINIMUM_CHECK
#define ATLAS_STATISTICS_MINIMUM_CHECK true
#endif

#ifndef ATLAS_STATISTICS_SUM_CHECK
#define ATLAS_STATISTICS_SUM_CHECK true
#endif

#ifndef ATLAS_STATISTICS_SUMMARY_CHECK
#define ATLAS_STATISTICS_SUMMARY_CHECK true
#endif

#ifndef ATLAS_MATH_COS_PRECISION
#define ATLAS_MATH_COS_PRECISION 1
#endif

#ifndef ATLAS_MATH_SIN_PRECISION
#define ATLAS_MATH_SIN_PRECISION 1
#endif


#ifndef ATLAS_MANIPULATION_API_CHECK
#define ATLAS_MANIPULATION_API_CHECK true
#endif

#ifndef ATLAS_MANIPULATION_API_CLEAR_CHECK
#define ATLAS_MANIPULATION_API_CLEAR_CHECK true
#endif

#ifndef ATLAS_MANIPULATION_API_COPY_CHECK
#define ATLAS_MANIPULATION_API_COPY_CHECK true
#endif

#ifndef ATLAS_MANIPULATION_API_REPLACEFROM_CHECK
#define ATLAS_MANIPULATION_API_REPLACEFROM_CHECK true
#endif

#ifndef ATLAS_MANIPULATION_API_SHIFT_CHECK
#define ATLAS_MANIPULATION_API_SHIFT_CHECK true
#endif

	constexpr const char* TrueString = ATLAS_TRUE_STRING;
	constexpr const char* FalseString = ATLAS_FALSE_STRING;
	constexpr double PI = ATLAS_MATH_PI;
	constexpr unsigned int StaticStringBufferSize = ATLAS_STATIC_STRING_BUFFER_SIZE;
	constexpr unsigned int StaticArrayBufferSize = ATLAS_STATIC_ARRAY_BUFFER_SIZE;

	constexpr bool EnableStaticStringCheck = ATLAS_STATIC_STRING_CHECK;
	constexpr bool EnableStaticArrayCheck = ATLAS_STATIC_ARRAY_CHECK;

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

	constexpr bool EnableStatisticsCheck = ATLAS_STATISTICS_CHECK;
	constexpr bool EnableStatisticsAverageCheck = EnableStatisticsCheck && ATLAS_STATISTICS_AVERAGE_CHECK;
	constexpr bool EnableStatisticsDeviationCheck = EnableStatisticsCheck && ATLAS_STATISTICS_DEVIATION_CHECK;
	constexpr bool EnableStatisticsMaximumCheck = EnableStatisticsCheck && ATLAS_STATISTICS_MAXIMUM_CHECK;
	constexpr bool EnableStatisticsMinimumCheck = EnableStatisticsCheck && ATLAS_STATISTICS_MINIMUM_CHECK;
	constexpr bool EnableStatisticsSumCheck = EnableStatisticsCheck && ATLAS_STATISTICS_SUM_CHECK;
	constexpr bool EnableStatisticsSummaryCheck = EnableStatisticsCheck && ATLAS_STATISTICS_SUMMARY_CHECK;

	constexpr int CosPrecision = ATLAS_MATH_COS_PRECISION;
	constexpr int SinPrecision = ATLAS_MATH_SIN_PRECISION;

	constexpr bool EnableManipulationAPICheck = ATLAS_MANIPULATION_API_CHECK;
	constexpr bool EnableManipulationAPIClearCheck = EnableManipulationAPICheck && ATLAS_MANIPULATION_API_CLEAR_CHECK;
	constexpr bool EnableManipulationAPICopyCheck = EnableManipulationAPICheck && ATLAS_MANIPULATION_API_COPY_CHECK;
	constexpr bool EnableManipulationAPIReplaceFromCheck = EnableManipulationAPICheck && ATLAS_MANIPULATION_API_REPLACEFROM_CHECK;
	constexpr bool EnableManipulationAPIShiftCheck = EnableManipulationAPICheck && ATLAS_MANIPULATION_API_SHIFT_CHECK;
}

