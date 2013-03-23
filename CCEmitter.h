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

#ifndef CCEMITTER_H_
#define CCEMITTER_H_

#include <vector>

#include "cocoa/CCObject.h"

NS_CC_BEGIN

/** Observer pattern implementation for Cocos2d-x. Should be used as part of observable objects */

class CCEmitter : public CCObject
{
public:
	void addListener(CCObject* pListener, SEL_CallFuncO pCallback);
	void removeListener(CCObject* pListener, SEL_CallFuncO pCallback);
	void removeAllListeners();
	void notifyWithSender(CCObject* pSender);

private:
	std::vector<std::pair<CCObject*, SEL_CallFuncO> > m_tListeners;
};

/** Class representing subscription. Should be used for automatical unsubscription from observable on observer destruction */

class CCSubscription : public CCObject
{
public:
	static CCSubscription* create(CCEmitter* pEmitter, CCObject* pListener, SEL_CallFuncO pCallback);

	CCSubscription();
	virtual ~CCSubscription();

	bool init(CCEmitter* pEmitter, CCObject* pListener, SEL_CallFuncO pCallback);

private:
	CCEmitter* m_pEmitter;
	CCObject* m_pListener;
	SEL_CallFuncO m_pCallback;
};

NS_CC_END

#endif /* CCEMITTER_H_ */
