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

CCSize ccSizeDenormalizeInterval(const CCSize& tSize, const CCSize& tNorm1, const CCSize& tNorm2);

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
