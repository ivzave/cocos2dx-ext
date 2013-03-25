/****************************************************************************
Copyright (c) 2012-2013 Igor Zavorotkin <ivzave@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef CCCOMMONEXTENDED_H_
#define CCCOMMONEXTENDED_H_

#include "ccMacros.h"

#define USING_NS_CD using namespace CocosDenshion;

#if (defined __GNUC__)
#define CC_FUNCTION __PRETTY_FUNCTION__
#elif (defined _MSC_VER)
#define CC_FUNCTION __FUNCSIG__
#else
#define CC_FUNCTION "unknown function"
#endif

#define CC_BREAK_IF_NOT(cond) \
if (!(cond)) \
	break;

#if defined(COCOS2D_DEBUG) && COCOS2D_DEBUG > 0
#define CC_DEBUG_IF_NOT(cond) if (!(cond))
#else
#define CC_DEBUG_IF_NOT(cond) if (false)
#endif /* COCOS2D_DEBUG */


/** @defgroup error_handling Error handling
 *  Improved error handling functionality to replace CCAssert */
/** @{ */

/** Unconditional failure in DEBUG */

#define CCUnreachable() CCUnreachableCustom("%s", "error")

/** Unconditional failure with custom formatted message in DEBUG */

#define CCUnreachableCustom(format, ...) \
{ \
	CCLOG("%s : " format, CC_FUNCTION, ##__VA_ARGS__); \
	fflush(NULL); \
	CC_ASSERT(false); \
}

/** Unconditional failure in DEBUG, break in RELEASE.
 *  Should be used in do...while(false) loops. */

#define CCUnreachableWithBreak() CCUnreachableWithBreakCustom("%s", "error")

/** Unconditional failure with custom formatted message in DEBUG, break in RELEASE.
 *  Should be used in do...while(false) loops. */

#define CCUnreachableWithBreakCustom(format, ...) \
{ \
	CCLOG("%s : " format, CC_FUNCTION, ##__VA_ARGS__); \
	fflush(NULL); \
	CC_ASSERT(false); \
	break; \
}

/** Calculate condition configuration-independantly and fail if false in DEBUG */

#define CCEnsure(cond) CCEnsureCustom(cond, "%s", #cond " failed")

/** Calculate condition configuration-independantly and fail with custom formatted message if false in DEBUG */

#define CCEnsureCustom(cond, format, ...) \
if (!(cond)) \
CCUnreachableCustom(format, ##__VA_ARGS__)

/** Calculate condition configuration-independantly and fail if false in DEBUG, break in RELEASE.
 *  Should be used in do...while(false) loops. */

#define CCEnsureElseBreak(cond) CCEnsureElseBreakCustom(cond, "%s", #cond " failed")

/** Calculate condition configuration-independantly and fail with custom formatted message if false in DEBUG, break in RELEASE.
 *  Should be used in do...while(false) loops. */

#define CCEnsureElseBreakCustom(cond, format, ...) \
if (!(cond)) \
CCUnreachableWithBreakCustom(format, ##__VA_ARGS__)

/** Calculate condition in DEBUG and fail if false */

#define CCDebugEnsure(cond) CCDebugEnsureCustom(cond, "%s", #cond " failed")

/** Calculate condition in DEBUG and fail with custom formatted message if false */

#define CCDebugEnsureCustom(cond, format, ...) \
CC_DEBUG_IF_NOT(cond) \
CCUnreachableCustom(format, ##__VA_ARGS__)

/** @} */

/** @defgroup collections Collections
 *  Iteration macros to replace original ones */
/** @{ */

/** Improved iteration macro for CCArray which does declare pointer to provided type in a block */

#define CCARRAY_FOREACH_OBJECT(pArr, ObjectType, pObject) \
if (CCArray* __pArray = (pArr)) \
	for (unsigned int __idx = 0; __idx < __pArray->data->num; ++__idx) \
		if (ObjectType pObject = (ObjectType)*(__pArray->data->arr + __idx))

/** Improved iteration macro for CCDictionary which does declare pointer to CCDictElement in a block */

#define CCDICT_FOREACH_ELEM(pDict, pElement) \
if (cocos2d::CCDictElement* pElement = NULL) ; else \
	if (cocos2d::CCDictElement* __pTmpElement = NULL) ; else \
		if (cocos2d::CCDictionary* __pDictionary = (pDict)) \
			HASH_ITER(hh, __pDictionary->m_pElements, pElement, __pTmpElement)

/** Improved iteration macro for CCDictionary which does declare pObject pointer to provided type in a block */

#define CCDICT_FOREACH_OBJECT(pDict, ObjectType, pObject) \
CCDICT_FOREACH_ELEM(pDict, __pElement) \
	if (ObjectType pObject = (ObjectType)__pElement->getObject())

/** Improved iteration macro for CCDictionary which does declare string key and pointer to provided type in a block */

#define CCDICT_FOREACH_STR_KEY_AND_OBJECT(pDict, tKey, ObjectType, pObject) \
CCDICT_FOREACH_OBJECT(pDict, ObjectType, pObject) \
	if (const char* tKey = __pElement->getStrKey())

/** Improved iteration macro for CCDictionary which does declare integer key and pointer to provided type in a block */

#define CCDICT_FOREACH_INT_KEY_AND_OBJECT(pDict, nKey, ObjectType, pObject) \
CCDICT_FOREACH_OBJECT(pDict, ObjectType, pObject) \
	if (int nKey = __pElement->getIntKey())

/** @} */

#endif /* CCCOMMONEXTENDED_H_ */
