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

#include "actions/CCActionInstant.h"
#include "actions/CCActionInterval.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "CCDirector.h"

#include "CCCommonExtended.h"
#include "CCGeometryExtended.h"
#include "CCNodeExtended.h"

#include "CCButton.h"

USING_NS_CC;

CCButton* CCButton::create(const CCSize& tSize, CCObject* pTarget, SEL_MenuHandler pSelector)
{
	CCButton* pRet = new CCButton();

	return pRet->init(tSize, pTarget, pSelector) ? (CCButton*)pRet->autorelease() : (delete pRet, pRet = NULL);
}

CCButton::CCButton() :
		m_bIsEnabled(true),
		m_bIsSelected(false),
		m_fDelay(0.0f),
		m_pTarget(NULL),
		m_pSelector(NULL)
{
}

bool CCButton::init(const CCSize& tSize, CCObject* pTarget, SEL_MenuHandler pSelector)
{
	do
	{
		CCEnsureElseBreak(CCLayer::init());

		m_pTarget = pTarget;
		m_pSelector = pSelector;

		ignoreAnchorPointForPosition(false);
		setContentSize(tSize);
		setTouchEnabled(true);

		return true;
	} while (false);

	return false;
}

void CCButton::addNodeWithActions(CCNode* pNode, int nZOrder, CCFiniteTimeAction* pSelectAction, CCFiniteTimeAction* pUnselectAction)
{
	m_tComponents.resize(m_tComponents.size() + 1);
	CCButtonComponent& tComponent = m_tComponents.back();
	tComponent.pNode = pNode;
	tComponent.pSelectAction = pSelectAction;
	tComponent.pUnselectAction = pUnselectAction;

	if (pUnselectAction != NULL)
	{
		if (pUnselectAction->getDuration() > m_fDelay)
		{
			m_fDelay = pUnselectAction->getDuration();
		}
	}
	addChild(pNode, nZOrder);
}

void CCButton::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCButtonTouchPriority, true);
}

bool CCButton::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	CC_UNUSED_PARAM(pEvent);

	do
	{
		CC_BREAK_IF_NOT(CCNodeIsVisibleRecursive(this));

		CC_BREAK_IF_NOT(!m_bIsSelected);
		CC_BREAK_IF_NOT(m_bIsEnabled);
		CC_BREAK_IF_NOT(CCNodeGetLocalBoundingBox(this).containsPoint(convertTouchToNodeSpaceAR(pTouch)));

		select();

		return true;
	} while (false);

	return false;
}

void CCButton::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{
	CC_UNUSED_PARAM(pEvent);

	bool bTouchInNodeRect(CCNodeGetLocalBoundingBox(this).containsPoint(convertTouchToNodeSpaceAR(pTouch)));
	if (m_bIsSelected && !bTouchInNodeRect)
	{
		unselect();
	}
	else if (!m_bIsSelected && bTouchInNodeRect)
	{
		select();
	}
}

void CCButton::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
	CC_UNUSED_PARAM(pTouch);
	CC_UNUSED_PARAM(pEvent);

	if (m_bIsSelected)
	{
		unselect();

		activate();
	}

}

void CCButton::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent)
{
	CC_UNUSED_PARAM(pTouch);
	CC_UNUSED_PARAM(pEvent);

	if (m_bIsSelected)
	{
		unselect();
	}
}

void CCButton::select(bool bImmediate)
{
	if (!m_bIsSelected)
	{
		for (std::vector<CCButtonComponent>::iterator pComponent = m_tComponents.begin(); pComponent != m_tComponents.end(); ++pComponent)
		{
			if (pComponent->pRunningAction != NULL )
			{
				pComponent->pNode->stopAction(pComponent->pRunningAction);
			}
			pComponent->pRunningAction = (CCFiniteTimeAction*)pComponent->pNode->runAction((CCFiniteTimeAction*)pComponent->pSelectAction->copy()->autorelease());
			if (bImmediate)
			{
				pComponent->pRunningAction->update(1.0f);
				pComponent->pNode->stopAction(pComponent->pRunningAction);
			}
		}

		m_bIsSelected = true;
	}
}

void CCButton::unselect()
{
	if (m_bIsSelected) // TODO remove double check
	{
		for (std::vector<CCButtonComponent>::iterator pComponent = m_tComponents.begin(); pComponent != m_tComponents.end(); ++pComponent)
		{
			if (pComponent->pRunningAction != NULL )
			{
				pComponent->pNode->stopAction(pComponent->pRunningAction);
			}
			pComponent->pRunningAction = (CCFiniteTimeAction*)pComponent->pNode->runAction((CCFiniteTimeAction*)pComponent->pUnselectAction->copy()->autorelease());
		}

		m_bIsSelected = false;
	}
}

void CCButton::activate()
{
	runAction(CCSequence::create(
			CCDelayTime::create(m_fDelay),
			CCCallFunc::create(this, callfunc_selector(CCNode::cleanup)),
			CCCallFuncO::create(m_pTarget, m_pSelector, this),
			NULL));
	// TODO important: double click bug
	// TODO important: another button clicked before activation happens follows to crash
}

//

// TODO activate sound (action?)

CCButtonToggle* CCButtonToggle::create(const CCSize& tSize, CCObject* pTarget, SEL_MenuHandler pSelector)
{
	CCButtonToggle* pRet = new CCButtonToggle();

	return pRet->init(tSize, pTarget, pSelector) ? (CCButtonToggle*)pRet->autorelease() : (delete pRet, pRet = NULL);
}

void CCButtonToggle::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
	CC_UNUSED_PARAM(pTouch);
	CC_UNUSED_PARAM(pEvent);

	if (getIsSelected())
	{
		activate();
	}
}

void CCButtonToggle::activate()
{
	runAction(CCCallFuncO::create(getTarget(), getSelector(), this));
}
