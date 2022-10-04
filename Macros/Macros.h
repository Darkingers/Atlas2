#pragma once
#include <assert.h>
#include <iostream>
#define MAKEDLL

#ifdef MAKEDLL
#  define DLLApi __declspec(dllexport)
#else
#  define DLLApi __declspec(dllimport)
#endif
