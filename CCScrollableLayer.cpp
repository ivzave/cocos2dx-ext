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

#include "cocoa/CCSet.h"
#include "touch_dispatcher/CCTouchHandler.h"
#include "CCDirector.h"

#include "CCCommonExtended.h"
#include "CCGeometryExtended.h"
#include "CCNodeExtended.h"

#include "CCScrollableLayer.h"

USING_NS_CC;

const float kCCScrollableLayerScrollShift = 5.0f;

const int kCCScrollableLayerBindingRight = 1;
const int kCCScrollableLayerBindingUpper = 2;

CCScrollableLayer* CCScrollableLayer::create(const CCSize& tWindowSize, const CCSize& tLayerSize, CCScrollableLayerBinding eBinding)
{
	CCScrollableLayer* pRet = new CCScrollableLayer();

	return pRet->init(tWindowSize, tLayerSize, eBinding) ? (CCScrollableLayer*)pRet->autorelease() : (delete pRet, pRet = NULL);
}

CCScrollableLayer::CCScrollableLayer() :
		m_eBinding(kCCScrollableLayerBindingBottomLeft),
		m_bScrolling(false)
{
}

bool CCScrollableLayer::init(const CCSize& tWindowSize, const CCSize& tLayerSize, CCScrollableLayerBinding eBinding)
{
	do
	{
		CCEnsureElseBreak(CCLayer::init());

		m_eBinding = eBinding;
		CCSize tBinding(eBinding & kCCScrollableLayerBindingRight,
				(eBinding & kCCScrollableLayerBindingUpper) >> 1);

		CCSize tShiftSize(cczSub(tLayerSize, tWindowSize));

		// TODO find better formula
		//m_tMinShift = binding * min(dx, 0)
		//m_tMaxShift = max(dx, binding * dx)

		m_tMinShift = cczNormalizeTo(
				cczDenormalizeTo(tBinding, cczMin(tShiftSize, CCSizeZero)),
				tWindowSize);
		m_tMaxShift = cczNormalizeTo(
				cczMax(tShiftSize, cczDenormalizeTo(tBinding, tShiftSize)),
				tWindowSize);

		setContentSize(tWindowSize);
		setTouchEnabled(true);
		ignoreAnchorPointForPosition(false);
		setShift(tBinding);

		return true;
	} while (false);

	return false;
}

void CCScrollableLayer::setShift(const CCSize& tShift)
{
	setAnchorPoint(ccpShift(
			ccp(0.5f, 0.5f),
			cczAdd(m_tMinShift, cczDenormalizeTo(tShift, cczSub(m_tMaxShift, m_tMinShift)))));
}

void CCScrollableLayer::setLayerSize(const CCSize& tSize)
{
	CCSize tBinding(m_eBinding & kCCScrollableLayerBindingRight,
			(m_eBinding & kCCScrollableLayerBindingUpper) >> 1);

	CCSize tShiftSize(cczSub(tSize, getContentSize()));

	CCSize tOldMaxShift(m_tMaxShift);

	m_tMinShift = cczNormalizeTo(
			cczDenormalizeTo(tBinding, cczMin(tShiftSize, CCSizeZero)),
			getContentSize());

	m_tMaxShift = cczNormalizeTo(
			cczMax(tShiftSize, cczDenormalizeTo(tBinding, tShiftSize)),
			getContentSize());

	CCSize tPreserveShift(cczSub(
			m_tMaxShift,
			tOldMaxShift));

	setAnchorPoint(ccpShift(
			getAnchorPoint(),
			cczDenormalizeTo(tBinding, tPreserveShift)));
}

void CCScrollableLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCScrollableLayerTouchPriority, false);
}

bool CCScrollableLayer::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	CC_UNUSED_PARAM(pEvent);

	do
	{
		CC_BREAK_IF_NOT(CCNodeIsVisibleRecursive(this));

		CCPoint tTouchPoint(convertTouchToNodeSpaceAR(pTouch));

		CC_BREAK_IF_NOT(CCRectMakeWithCenterAndSize(CCPointZero, getContentSize()).containsPoint(tTouchPoint));
		m_tBeginTouchPoint = tTouchPoint;

		return true;
	} while (false);

	return false;
}

void CCScrollableLayer::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{
	CC_UNUSED_PARAM(pEvent);

	CCPoint tTouchPoint(convertTouchToNodeSpaceAR(pTouch));
	CCPoint tPrevTouchPoint(convertToNodeSpaceAR(pTouch->getPreviousLocation()));

	CCSize tShift(cczClamp(
			cczAdd(
					cczNormalizeTo(ccpDiff(tPrevTouchPoint, tTouchPoint), getContentSize()),
					ccpDiff(getAnchorPoint(), ccp(0.5f, 0.5f))),
			m_tMinShift,
			m_tMaxShift));

	if (!m_bScrolling && cczLength(ccpDiff(m_tBeginTouchPoint, tPrevTouchPoint)) >= kCCScrollableLayerScrollShift)
	{
		m_bScrolling = true;
		// TODO find workaround instead of HACK
		CCSet* pSet = new CCSet();
		pSet->addObject(pTouch);
		CCTouchDispatcher* pTouchDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
		CCTargetedTouchHandler* pHandler = (CCTargetedTouchHandler*)pTouchDispatcher->findHandler(this);
		pHandler->getClaimedTouches()->removeObject(pTouch);
		pTouchDispatcher->touchesCancelled(pSet, NULL);
		pHandler->getClaimedTouches()->addObject(pTouch);
		delete pSet;
	}

	if (m_bScrolling)
	{
		setAnchorPoint(ccpShift(ccp(0.5f, 0.5f), tShift));
	}
}

void CCScrollableLayer::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
	CC_UNUSED_PARAM(pTouch);
	CC_UNUSED_PARAM(pEvent);

	// TODO kinetic scrolling here

	m_bScrolling = false;
}

void CCScrollableLayer::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent)
{
	CC_UNUSED_PARAM(pTouch);
	CC_UNUSED_PARAM(pEvent);

	m_bScrolling = false;
}
