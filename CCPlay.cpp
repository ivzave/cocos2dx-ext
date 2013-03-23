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
#include "SimpleAudioEngine.h"

#include "CCCommonExtended.h"

#include "CCPlay.h"

USING_NS_CC;
USING_NS_CD;

CCPlay* CCPlay::create(const std::string& tSample)
{
	CCPlay* pRet = new CCPlay();

	return pRet->init(tSample) ? (CCPlay*)pRet->autorelease() : (delete pRet, pRet = NULL);
}

bool CCPlay::init(const std::string& tSample)
{
	m_tSample = tSample;
	return true;
}

CCObject* CCPlay::copyWithZone(CCZone* pZone)
{
	CCZone* pNewZone = NULL;
	CCPlay* pRet = NULL;

	if (pZone != NULL && pZone->m_pCopyObject != NULL)
	{
		pRet = (CCPlay*)(pZone->m_pCopyObject);
	}
	else
	{
		pRet = new CCPlay();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInstant::copyWithZone(pZone);
	pRet->m_tSample = m_tSample;

	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

void CCPlay::startWithTarget(CCNode* pTarget)
{
	CCActionInstant::startWithTarget(pTarget);
	SimpleAudioEngine::sharedEngine()->playEffect(m_tSample.c_str());
}
