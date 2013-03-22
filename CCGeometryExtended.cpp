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

#include "CCStdC.h"

#include "CCGeometryExtended.h"

NS_CC_BEGIN

CCSize ccpDiff(const CCPoint& tPoint1, const CCPoint& tPoint2)
{
	return ccz(tPoint1.x - tPoint2.x, tPoint1.y - tPoint2.y);
}

CCPoint ccpShift(const CCPoint& tPoint, const CCSize& tSize)
{
	return ccp(tPoint.x + tSize.width, tPoint.y + tSize.height);
}

CCPoint ccpNormalizeTo(const CCPoint& tPoint, const CCSize& tNorm)
{
	return ccp(tPoint.x / tNorm.width, tPoint.y / tNorm.height);
}

CCPoint ccpDenormalizeTo(const CCPoint& tPoint, const CCSize& tNorm)
{
	return ccp(tPoint.x * tNorm.width, tPoint.y * tNorm.height);
}

CCSize cczFromPoint(const CCPoint& tPoint)
{
	return ccz(tPoint.x, tPoint.y);
}

float cczLength(const CCSize& tSize)
{
	return sqrtf(tSize.width * tSize.width + tSize.height * tSize.height);
}

CCSize cczAdd(const CCSize& tSize1, const CCSize& tSize2)
{
	return ccz(tSize1.width + tSize2.width, tSize1.height + tSize2.height);
}

CCSize cczSub(const CCSize& tSize1, const CCSize& tSize2)
{
	return ccz(tSize1.width - tSize2.width, tSize1.height - tSize2.height);
}

CCSize cczNormalizeTo(const CCSize& tSize, const CCSize& tNorm)
{
	return ccz(tSize.width / tNorm.width, tSize.height / tNorm.height);
}

CCSize cczDenormalizeTo(const CCSize& tSize, const CCSize& tNorm)
{
	return ccz(tSize.width * tNorm.width, tSize.height * tNorm.height);
}

CCSize ccSizeDenormalizeInterval(const CCSize& tSize, const CCSize& tNorm1, const CCSize& tNorm2)
{
	return cczAdd(tNorm1, cczDenormalizeTo(tSize, cczSub(tNorm2, tNorm1)));
}

CCSize cczClamp(const CCSize& tSize, const CCSize& tLimit1, const CCSize& tLimit2)
{
	return ccz(clampf(tSize.width, tLimit1.width, tLimit2.width), clampf(tSize.height, tLimit1.height, tLimit2.height));
}

CCSize cczMin(const CCSize& tSize1, const CCSize& tSize2)
{
	return ccz(MIN(tSize1.width, tSize2.width), MIN(tSize1.height, tSize2.height));
}

CCSize cczMax(const CCSize& tSize1, const CCSize& tSize2)
{
	return ccz(MAX(tSize1.width, tSize2.width), MAX(tSize1.height, tSize2.height));
}

CCRect CCRectMakeWithCenterAndSize(const CCPoint& tCenter, const CCSize& tSize)
{
	return CCRectMake(tCenter.x - 0.5f * tSize.width, tCenter.y - 0.5f * tSize.height, tSize.width, tSize.height);
}

CCRect CCRectMakeWithOriginAndSize(const CCPoint& tOrigin, const CCSize& tSize)
{
	return CCRectMake(tOrigin.x, tOrigin.y, tSize.width, tSize.height);
}

CCPoint CCRectGetCenter(const CCRect& tRect)
{
	return ccp(tRect.getMidX(), tRect.getMidY());
}

NS_CC_END
