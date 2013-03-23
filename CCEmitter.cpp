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

#include <algorithm>

#include "CCCommonExtended.h"

#include "CCEmitter.h"

USING_NS_CC;

void CCEmitter::addListener(CCObject* pListener, SEL_CallFuncO pCallback)
{
	CCDebugEnsureCustom(std::find(m_tListeners.begin(), m_tListeners.end(), std::make_pair(pListener, pCallback)) == m_tListeners.end(), "listener already added");
	m_tListeners.push_back(std::make_pair(pListener, pCallback));
}

void CCEmitter::removeListener(CCObject* pListener, SEL_CallFuncO pCallback)
{
	std::vector<std::pair<CCObject*, SEL_CallFuncO> >::iterator pFoundEntry = std::find(m_tListeners.begin(), m_tListeners.end(), std::make_pair(pListener, pCallback));
	CCDebugEnsureCustom(pFoundEntry != m_tListeners.end(), "listener not found");
	m_tListeners.erase(pFoundEntry);
}

void CCEmitter::removeAllListeners()
{
	m_tListeners.clear();
}

void CCEmitter::notifyWithSender(CCObject* pSender)
{
	for (std::vector<std::pair<CCObject*, SEL_CallFuncO> >::iterator it = m_tListeners.begin(); it != m_tListeners.end(); ++it)
	{
		(it->first->*it->second)(pSender);
	}
}

//

CCSubscription* CCSubscription::create(CCEmitter* pEmitter, CCObject* pListener, SEL_CallFuncO pCallback)
{
	CCSubscription* pRet = new CCSubscription();

	return pRet->init(pEmitter, pListener, pCallback) ? (CCSubscription*)pRet->autorelease() : (delete pRet, pRet = NULL);
}

CCSubscription::CCSubscription() :
		m_pEmitter(NULL),
		m_pListener(NULL),
		m_pCallback(NULL)
{
}

CCSubscription::~CCSubscription()
{
	if (m_pEmitter != NULL)
	{
		m_pEmitter->removeListener(m_pListener, m_pCallback);
	}
}

bool CCSubscription::init(CCEmitter* pEmitter, CCObject* pListener, SEL_CallFuncO pCallback)
{
	CCDebugEnsureCustom(m_pEmitter == NULL, "already subscribed");
	m_pEmitter = pEmitter;
	m_pListener = pListener;
	m_pCallback = pCallback;
	m_pEmitter->addListener(m_pListener, m_pCallback);

	return true;
}
