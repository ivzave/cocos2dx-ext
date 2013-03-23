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

#include "cocoa/CCZone.h"
#include "misc_nodes/CCProgressTimer.h"
#include "textures/CCTextureCache.h"

#include "CCCommonExtended.h"

#include "CCActionExtended.h"

USING_NS_CC;

CCNone* CCNone::create()
{
	return (CCNone*)(new CCNone())->autorelease();
}

CCObject* CCNone::copyWithZone(CCZone* pZone)
{
	CCZone* pNewZone = NULL;
	CCNone* pRet = NULL;

	if (pZone != NULL && pZone->m_pCopyObject != NULL)
	{
		pRet = (CCNone*)(pZone->m_pCopyObject);
	}
	else
	{
		pRet = new CCNone();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInstant::copyWithZone(pZone);

	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

//

CCReorder* CCReorder::create(int nZOrder)
{
	CCReorder* pRet = new CCReorder();

	return pRet->init(nZOrder) ? (CCReorder*)pRet->autorelease() : (delete pRet, pRet = NULL);
}

bool CCReorder::init(int nZOrder)
{
	m_nZOrder = nZOrder;
	return true;
}

void CCReorder::startWithTarget(CCNode* pTarget)
{
	CCActionInstant::startWithTarget(pTarget);
	m_pTarget->setZOrder(m_nZOrder);
}

CCObject* CCReorder::copyWithZone(CCZone* pZone)
{
	CCZone* pNewZone = NULL;
	CCReorder* pRet = NULL;

	if (pZone != NULL && pZone->m_pCopyObject != NULL)
	{
		pRet = (CCReorder*)(pZone->m_pCopyObject);
	}
	else
	{
		pRet = new CCReorder();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInstant::copyWithZone(pZone);

	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

//

CCRemove* CCRemove::create()
{
	return (CCRemove*)(new CCRemove())->autorelease();
}

void CCRemove::startWithTarget(CCNode* pTarget)
{
	CCActionInstant::startWithTarget(pTarget);
	m_pTarget->removeFromParentAndCleanup(true);
}

CCObject* CCRemove::copyWithZone(CCZone* pZone)
{
	CCZone* pNewZone = NULL;
	CCRemove* pRet = NULL;

	if (pZone != NULL && pZone->m_pCopyObject != NULL)
	{
		pRet = (CCRemove*)(pZone->m_pCopyObject);
	}
	else
	{
		pRet = new CCRemove();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInstant::copyWithZone(pZone);

	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

//

CCSetParent* CCSetParent::create(CCNode* pParent)
{
	CCSetParent* pRet = new CCSetParent();

	return pRet->init(pParent) ? (CCSetParent*)pRet->autorelease() : (delete pRet, pRet = NULL);
}

bool CCSetParent::init(CCNode* pParent)
{
	m_pParent = pParent;
	return m_pParent != NULL;
}

void CCSetParent::startWithTarget(CCNode* pTarget)
{
	CCActionInstant::startWithTarget(pTarget);
	pTarget->setPosition(m_pParent->convertToNodeSpace(pTarget->convertToWorldSpace(CCPointZero))); // TODO AR? check other transforms
	if (pTarget->getParent() != NULL)
	{
		pTarget->removeFromParentAndCleanup(false);
	}
	m_pParent->addChild(pTarget);
}

CCObject* CCSetParent::copyWithZone(CCZone* pZone)
{
	CCZone* pNewZone = NULL;
	CCSetParent* pRet = NULL;

	if (pZone != NULL && pZone->m_pCopyObject != NULL)
	{
		pRet = (CCSetParent*)(pZone->m_pCopyObject);
	}
	else
	{
		pRet = new CCSetParent();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInstant::copyWithZone(pZone);
	pRet->m_pParent = m_pParent;

	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

//

CCProgressBy* CCProgressBy::create(float fDuration, float fByPercentage)
{
	CCProgressBy* pRet = new CCProgressBy();

	return pRet->init(fDuration, fByPercentage) ? (CCProgressBy*)pRet->autorelease() : (delete pRet, pRet = NULL);
}

bool CCProgressBy::init(float fDuration, float fByPercentage)
{
	m_fByPercentage = fByPercentage;
	m_fAddedPercentage = 0.0f;
	return CCActionInterval::initWithDuration(fDuration);
}

CCObject* CCProgressBy::copyWithZone(CCZone* pZone)
{
	CCZone* pNewZone = NULL;
	CCProgressBy* pRet = NULL;

	if (pZone != NULL && pZone->m_pCopyObject != NULL)
	{
		pRet = (CCProgressBy*)(pZone->m_pCopyObject);
	}
	else
	{
		pRet = new CCProgressBy();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInterval::copyWithZone(pZone);
	pRet->m_fByPercentage = m_fByPercentage;
	pRet->m_fAddedPercentage = m_fAddedPercentage;

	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

void CCProgressBy::update(float fTime)
{
	do
	{
		CCProgressTimer* pTarget = NULL;
		CCEnsureElseBreakCustom(pTarget = dynamic_cast<CCProgressTimer*>(getTarget()), "target doesn't support CCProgressBy action");
		pTarget->setPercentage(pTarget->getPercentage() + m_fByPercentage * fTime - m_fAddedPercentage);
		m_fAddedPercentage = m_fByPercentage * fTime;
	} while (false);
}

//

CCSetTexture* CCSetTexture::create(const char* pTextureName)
{
	CCSetTexture* pRet = new CCSetTexture();

	return pRet->initWithTexture(pTextureName) ? (CCSetTexture*)pRet->autorelease() : (delete pRet, pRet = NULL);
}

bool CCSetTexture::initWithTexture(const char* pTextureName)
{
	m_tTextureName = pTextureName;
	return true;
}

void CCSetTexture::startWithTarget(CCNode* pTarget)
{
	CCActionInstant::startWithTarget(pTarget);
	do
	{
		CCTextureProtocol* pTargetTextureProtocol = NULL;
		CCEnsureElseBreakCustom(pTargetTextureProtocol = dynamic_cast<CCTextureProtocol*>(getTarget()), "target doesn't support CCSetTexture action");
		pTargetTextureProtocol->setTexture(m_tTextureName.empty() ? NULL : CCTextureCache::sharedTextureCache()->addImage(m_tTextureName.c_str()));
	} while (false);
}

CCObject* CCSetTexture::copyWithZone(CCZone* pZone)
{
	CCZone* pNewZone = NULL;
	CCSetTexture* pRet = NULL;

	if (pZone != NULL && pZone->m_pCopyObject != NULL)
	{
		pRet = (CCSetTexture*)(pZone->m_pCopyObject);
	}
	else
	{
		pRet = new CCSetTexture();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInstant::copyWithZone(pZone);
	pRet->m_tTextureName = m_tTextureName;

	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

//

CCSetText* CCSetText::create(const char* pText)
{
	CCSetText* pRet = new CCSetText();

	return pRet->initWithText(pText) ? (CCSetText*)pRet->autorelease() : (delete pRet, pRet = NULL);
}

bool CCSetText::initWithText(const char* pText)
{
	m_tText = pText;
	return true;
}

void CCSetText::startWithTarget(CCNode* pTarget)
{
	CCActionInstant::startWithTarget(pTarget);
	do
	{
		CCLabelProtocol* pTargetLabelProtocol = NULL;
		CCEnsureElseBreakCustom(pTargetLabelProtocol = dynamic_cast<CCLabelProtocol*>(getTarget()), "target doesn't support CCSetText action");
		pTargetLabelProtocol->setString(m_tText.empty() ? "" : m_tText.c_str());
	} while (false);
}

CCObject* CCSetText::copyWithZone(CCZone* pZone)
{
	CCZone* pNewZone = NULL;
	CCSetText* pRet = NULL;

	if (pZone != NULL && pZone->m_pCopyObject != NULL)
	{
		pRet = (CCSetText*)(pZone->m_pCopyObject);
	}
	else
	{
		pRet = new CCSetText();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInstant::copyWithZone(pZone);
	pRet->m_tText = m_tText;

	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

//

CCForward* CCForward::create(CCFiniteTimeAction* pAction, float fTime)
{
	CCForward* pRet = new CCForward();

	return pRet->init(pAction, fTime) ? (CCForward*)pRet->autorelease() : (delete pRet, pRet = NULL);
}

bool CCForward::init(CCFiniteTimeAction* pAction, float fTime)
{
	do
	{
		CCEnsureElseBreak(m_pAction = pAction);
		m_fTime = fTime;
		CCEnsureElseBreak(CCActionInterval::initWithDuration(m_pAction->getDuration() * (1.0f - m_fTime)));

		return true;
	} while (false);

	return false;
}

void CCForward::startWithTarget(CCNode* pTarget)
{
	CCActionInterval::startWithTarget(pTarget);
	m_pAction->startWithTarget(pTarget);
	m_pAction->update(m_fTime);
}

CCObject* CCForward::copyWithZone(CCZone* pZone)
{
	CCZone* pNewZone = NULL;
	CCForward* pRet = NULL;

	if (pZone != NULL && pZone->m_pCopyObject != NULL)
	{
		pRet = (CCForward*)(pZone->m_pCopyObject);
	}
	else
	{
		pRet = new CCForward();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInterval::copyWithZone(pZone);
	pRet->m_pAction = (CCFiniteTimeAction*)m_pAction->copy()->autorelease();
	pRet->m_fTime = m_fTime;

	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

void CCForward::stop()
{
	m_pAction->stop();
	CCActionInterval::stop();
}

void CCForward::update(float fTime)
{
	m_pAction->update(m_fTime + fTime * getDuration() / m_pAction->getDuration());
}

bool CCForward::isDone()
{
	return m_pAction->isDone();
}

//

CCRepeatDuration* CCRepeatDuration::create(float fDuration, CCFiniteTimeAction* pAction)
{
	CCRepeatDuration* pRet = new CCRepeatDuration();

	return pRet->init(fDuration, pAction) ? (CCRepeatDuration*)pRet->autorelease() : (delete pRet, pRet = NULL);
}

bool CCRepeatDuration::init(float fDuration, CCFiniteTimeAction* pAction)
{
	do
	{
		CCEnsureElseBreak(CCActionInterval::initWithDuration(fDuration));
		CCEnsureElseBreak(m_pAction = pAction);
		m_fStage = 0.0f;

		return true;
	} while (false);

	return false;
}

void CCRepeatDuration::startWithTarget(CCNode* pTarget)
{
	CCActionInterval::startWithTarget(pTarget);
	m_pAction->startWithTarget(pTarget);
}

CCObject* CCRepeatDuration::copyWithZone(CCZone* pZone)
{
	CCZone* pNewZone = NULL;
	CCRepeatDuration* pRet = NULL;

	if (pZone != NULL && pZone->m_pCopyObject != NULL)
	{
		pRet = (CCRepeatDuration*)(pZone->m_pCopyObject);
	}
	else
	{
		pRet = new CCRepeatDuration();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInterval::copyWithZone(pZone);
	pRet->m_pAction = (CCFiniteTimeAction*)m_pAction->copy()->autorelease();
	pRet->m_fStage = m_fStage;

	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

void CCRepeatDuration::stop()
{
	m_pAction->stop();
	CCActionInterval::stop();
}

void CCRepeatDuration::update(float fTime)
{
	float fTimes = getDuration() / m_pAction->getDuration();
	m_pAction->update(fTime * fTimes - (int)(fTime * fTimes));
	m_fStage = fTime;
}

bool CCRepeatDuration::isDone()
{
	return m_fStage == 1.0f;
}
