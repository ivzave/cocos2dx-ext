#include "draw_nodes/CCDrawingPrimitives.h"

#include "CCCommonExtended.h"
#include "CCGeometryExtended.h"

#include "CCPrimitiveNodes.h"

USING_NS_CC;

CCRectNode* CCRectNode::createWithSize(const CCSize& tSize, const ccColor4F& tColor, bool bFill)
{
	return createWithRect(ccRectMakeWithPointAndSize(CCPointZero, tSize), tColor, bFill);
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
	const CCSize& tContentSize = getContentSize();

	if (m_bFill)
    {
    	ccDrawSolidRect(CCPointZero, ccPointFromSize(tContentSize), ccc4FFromccc3B(getColor()));
    }
    else
    {
    	const ccColor3B& tColor(getColor());
    	ccDrawColor4B(tColor.r, tColor.g, tColor.b, getOpacity());
    	ccDrawRect(CCPointZero, ccPointFromSize(tContentSize));
    }
}

CCLineNode* CCLineNode::createWithPoints(const CCPoint& tBeginPoint, const CCPoint& tEndPoint, const ccColor4F& tColor)
{
	CCLineNode* pRet = new CCLineNode();

	return pRet->initWithPoints(tBeginPoint, tEndPoint, tColor) ? (CCLineNode*)pRet->autorelease() : (delete pRet, pRet = NULL);
}

bool CCLineNode::initWithPoints(const CCPoint& tBeginPoint, const CCPoint& tEndPoint, const ccColor4F& tColor)
{
	setPosition(tBeginPoint);
	setContentSize(ccPointDiff(tBeginPoint, tEndPoint));
	setColor(ccc3(tColor.r * 255, tColor.b * 255, tColor.g * 255));

	return true;
}

void CCLineNode::draw()
{
	const ccColor3B& tColor(getColor());
	ccDrawColor4B(tColor.r, tColor.g, tColor.b, getOpacity());
	ccDrawLine(CCPointZero, ccPointFromSize(getContentSize()));
}


CCDotNode* CCDotNode::createWithPoint(const CCPoint& tPoint, const ccColor4F& tColor)
{
	CCDotNode* pRet = new CCDotNode();

	return pRet->initWithPoint(tPoint, tColor) ? (CCDotNode*)pRet->autorelease() : (delete pRet, pRet = NULL);
}

bool CCDotNode::initWithPoint(const CCPoint& tPoint, const ccColor4F& tColor)
{
	setPosition(tPoint);
	setColor(ccc3(tColor.r * 255, tColor.b * 255, tColor.g * 255));

	return true;
}

void CCDotNode::draw()
{
	const ccColor3B& tColor(getColor());
	ccDrawColor4B(tColor.r, tColor.g, tColor.b, getOpacity());
	ccDrawPoint(CCPointZero);
}
