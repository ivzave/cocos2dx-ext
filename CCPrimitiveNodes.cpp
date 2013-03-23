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

#include "draw_nodes/CCDrawingPrimitives.h"

#include "CCCommonExtended.h"
#include "CCGeometryExtended.h"

#include "CCPrimitiveNodes.h"

USING_NS_CC;

CCRectNode* CCRectNode::createWithSize(const CCSize& tSize, const ccColor4F& tColor, bool bFill)
{
	return createWithRect(CCRectMakeWithOriginAndSize(CCPointZero, tSize), tColor, bFill);
}

CCRectNode* CCRectNode::createWithRect(const CCRect& tRect, const ccColor4F& tColor, bool bFill)
{
	CCRectNode* pRet = new CCRectNode();

	return pRet->initWithRect(tRect, tColor, bFill) ? (CCRectNode*)pRet->autorelease() : (delete pRet, pRet = NULL);
}

bool CCRectNode::initWithSize(const CCSize& tSize, const ccColor4F& tColor, bool bFill)
{
	setContentSize(tSize);
	setColor(ccc3(tColor.r * 255, tColor.b * 255, tColor.g * 255));
	setOpacity(tColor.a * 255);
	m_bFill = bFill;

	return true;
}

bool CCRectNode::initWithRect(const CCRect& tRect, const ccColor4F& tColor, bool bFill)
{
	setPosition(tRect.origin);

	return initWithSize(tRect.size, tColor, bFill);
}

void CCRectNode::draw()
{
	const ccColor3B& tColor(getColor());
	CCPoint tOrigin(isIgnoreAnchorPointForPosition() ? CCPointZero : getAnchorPointInPoints());
	CCPoint tDestination(ccpShift(tOrigin, getContentSize()));

	if (m_bFill)
    {
		ccColor4F tColor4F(ccc4FFromccc3B(tColor));
		tColor4F.a = getOpacity() / 255.0f;
    	ccDrawSolidRect(tOrigin, tDestination, tColor4F);
    }
    else
    {
    	ccDrawColor4B(tColor.r, tColor.g, tColor.b, getOpacity());
    	ccDrawRect(tOrigin, tDestination);
    }
}

//

CCLineNode* CCLineNode::createWithPoints(const CCPoint& tBeginPoint, const CCPoint& tEndPoint, const ccColor4F& tColor)
{
	CCLineNode* pRet = new CCLineNode();

	return pRet->initWithPoints(tBeginPoint, tEndPoint, tColor) ? (CCLineNode*)pRet->autorelease() : (delete pRet, pRet = NULL);
}

bool CCLineNode::initWithPoints(const CCPoint& tBeginPoint, const CCPoint& tEndPoint, const ccColor4F& tColor)
{
	setPosition(tBeginPoint);
	setContentSize(ccpDiff(tEndPoint, tBeginPoint));
	setColor(ccc3(tColor.r * 255, tColor.b * 255, tColor.g * 255));
	setOpacity(tColor.a * 255);

	return true;
}

void CCLineNode::draw()
{
	const ccColor3B& tColor(getColor());
	ccDrawColor4B(tColor.r, tColor.g, tColor.b, getOpacity());
	CCPoint tOrigin(isIgnoreAnchorPointForPosition() ? CCPointZero : getAnchorPointInPoints());
	ccDrawLine(tOrigin, ccpShift(tOrigin, getContentSize()));
}

//

CCDotNode* CCDotNode::createWithPoint(const CCPoint& tPoint, const ccColor4F& tColor)
{
	CCDotNode* pRet = new CCDotNode();

	return pRet->initWithPoint(tPoint, tColor) ? (CCDotNode*)pRet->autorelease() : (delete pRet, pRet = NULL);
}

bool CCDotNode::initWithPoint(const CCPoint& tPoint, const ccColor4F& tColor)
{
	setPosition(tPoint);
	setColor(ccc3(tColor.r * 255, tColor.b * 255, tColor.g * 255));
	setOpacity(tColor.a * 255);

	return true;
}

void CCDotNode::draw()
{
	const ccColor3B& tColor(getColor());
	ccDrawColor4B(tColor.r, tColor.g, tColor.b, getOpacity());
	ccDrawPoint(CCPointZero);
}
