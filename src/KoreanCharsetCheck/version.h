#ifndef	_VESION_H_
#define	_VESION_H_

#include <windows.h>

#define MKSTR_(x)	#x
#define MKSTR(x)	MKSTR_(x)

#undef	COMPANY
#define COMPANY					iripple
#undef	CURRENT_YEAR
#define	CURRENT_YEAR			2018

#if defined(_AMD64_)
#	undef PLATFORM_TARGET
#	define PLATFORM_TARGET	x64
#elif defined(_X86_)
#	undef PLATFORM_TARGET
#	define PLATFORM_TARGET	x86
#endif

#ifdef _DEBUG
#	if defined(PLATFORM_TARGET)
#		define MODULE_TYPE		Debug (PLATFORM_TARGET)
#	else
#		define MODULE_TYPE		Debug
#	endif
#else
#	if defined(PLATFORM_TARGET)
#		define MODULE_TYPE		Release (PLATFORM_TARGET)
#	else
#		define MODULE_TYPE		Release
#	endif
#endif

#define MAJOR_VERSION			0	// ���� ���� Version �ƴ�.
#define MINOR_VERSION			8	// ���� ���� ������ �ƴ�.
#define YEAR_MONTH_VERSION		1807
#define HOTFIX_VERSION			0
#define SHORT_VERSION			MAJOR_VERSION.MINOR_VERSION
#define FULL_VERSION			SHORT_VERSION.YEAR_MONTH_VERSION.HOTFIX_VERSION
#define COPYRIGHT				Copyright (c) 2018-CURRENT_YEAR COMPANY

#define NAME_PRODUCT			Korean Charset Check Plug-In for Notepad++
#define NAME_FILENAME			nppKoreanCharsetCheck.dll
#define NAME_MODULE				Korean Charset Check Plug-In for Notepad++ MODULE_TYPE
#define COMMENT					Notepad++ �ѱ��� Charset Ȯ���ϱ� Plug-In for Korean Windows Only

#endif	//#ifndef	_VESION_H_ 
