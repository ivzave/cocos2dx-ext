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

#ifndef CCGEOMETRYEXTENDED_H_
#define CCGEOMETRYEXTENDED_H_

#include "support/CCPointExtension.h"

NS_CC_BEGIN

/** @name CCPoint related extensions */
/** @{ */

/** Calculate difference of two points as a vector */
CCSize ccpDiff(const CCPoint& tPoint1, const CCPoint& tPoint2);

/** Return point shifted to given direction */
CCPoint ccpShift(const CCPoint& tPoint, const CCSize& tSize);

/** Return point normalized to given vector */
CCPoint ccpNormalizeTo(const CCPoint& tPoint, const CCSize& tNorm);

/** Return point denormalized to given vector */
CCPoint ccpDenormalizeTo(const CCPoint& tPoint, const CCSize& tNorm);

/** @} */

/** @name CCSize related extensions */
/** @{ */

/** Create a CCSize vector object */
#define ccz(x, y) CCSizeMake((float)(x), (float)(y))

/** Convert CCPoint to CCSize */
CCSize cczFromPoint(const CCPoint& tPoint);

/** Calculate length of vector */
float cczLength(const CCSize& tSize);

/** Calculate sum of two vectors */
CCSize cczAdd(const CCSize& tSize1, const CCSize& tSize2);

/** Calculate difference of two vectors */
CCSize cczSub(const CCSize& tSize1, const CCSize& tSize2);

/** Return vector normalized to given vector */
CCSize cczNormalizeTo(const CCSize& tSize, const CCSize& tNorm);

/** Return vector normalized to given vector */
CCSize cczDenormalizeTo(const CCSize& tSize, const CCSize& tNorm);

/** Clamp vector between two vectors */
CCSize cczClamp(const CCSize& tSize, const CCSize& tLimit1, const CCSize& tLimit2);

/** Return minimal of two vectors */
CCSize cczMin(const CCSize& tSize1, const CCSize& tSize2);

/** Return maximal of two vectors */
CCSize cczMax(const CCSize& tSize1, const CCSize& tSize2);

/** @} */

/** @name CCRect related extensions */
/** @{ */

/** Create a rectangle with given center point and size */
CCRect CCRectMakeWithCenterAndSize(const CCPoint& tCenter, const CCSize& tSize);

/** Create a rectangle with given origin and size */
CCRect CCRectMakeWithOriginAndSize(const CCPoint& tOrigin, const CCSize& tSize);

/** Return center point of rectangle */
CCPoint CCRectGetCenter(const CCRect& tRect);

/** @} */

NS_CC_END

#endif /* CCGEOMETRYEXTENDED_H_ */
