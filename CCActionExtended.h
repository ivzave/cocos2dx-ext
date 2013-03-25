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

#ifndef CCACTIONEXTENDED_H_
#define CCACTIONEXTENDED_H_

#include "actions/CCActionInstant.h"
#include "actions/CCActionInterval.h"

#include "CCPointer.h"

NS_CC_BEGIN

/** @defgroup actions Actions
 *  Additional actions */
/** @{ */

/** Instant action that does nothing.
 *  Just a stub. */

class CCNone : public CCActionInstant
{
public:
	static CCNone* create();

	virtual CCObject* copyWithZone(CCZone* pZone);
};

/** Instant action that removes the node from its parent (with cleanup) */

class CCRemove : public CCActionInstant
{
public:
	static CCRemove* create();

	virtual void startWithTarget(CCNode* pTarget);
	virtual CCObject* copyWithZone(CCZone* pZone);
};

/** Instant action that modifies the Z-order of the node */

class CCReorder : public CCActionInstant
{
public:
	static CCReorder* create(int nZOrder);

	bool init(int nZOrder);

	virtual void startWithTarget(CCNode* pTarget);
	virtual CCObject* copyWithZone(CCZone* pZone);

private:
	int m_nZOrder;
};

/** Instant action that changes nodes parent.
 *  Modifies the position so the node won't move. */

class CCSetParent : public CCActionInstant
{
public:
	static CCSetParent* create(CCNode* pParent);

	bool init(CCNode* pParent);

	virtual void startWithTarget(CCNode* pTarget);
	virtual CCObject* copyWithZone(CCZone* pZone);

private:
	CCNode* m_pParent;
};

/** Instant action that changes the progress of CCProgressTimer by given value */

class CCProgressBy : public CCActionInterval
{
public:
	static CCProgressBy* create(float fDuration, float fByPercentage);

	bool init(float fDuration, float fByPercentage);

	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual void update(float fTime);

private:
	float m_fByPercentage;
	float m_fAddedPercentage;
};

/** Instant action that sets the texture of the node.
 *  Requires CCTextureProtocol. */

class CCSetTexture : public CCActionInstant
{
public:
	static CCSetTexture* create(const char* pTextureName);

	bool initWithTexture(const char* pTextureName);

	virtual void startWithTarget(CCNode* pTarget);
	virtual CCObject* copyWithZone(CCZone* pZone);

private:
	std::string m_tTextureName;
};

/** Instant action that changes the text label of the node.
 *  Requires CCLabelProtocol. */

class CCSetText : public CCActionInstant
{
public:
	static CCSetText* create(const char* pText);

	bool initWithText(const char* pText);

	virtual void startWithTarget(CCNode* pTarget);
	virtual CCObject* copyWithZone(CCZone* pZone);

private:
	std::string m_tText;
};

/** Action that runs given action starting from given time until the end */

class CCForward : public CCActionInterval
{
public:
	static CCForward* create(CCFiniteTimeAction* pAction, float fTime);

	bool init(CCFiniteTimeAction* pAction, float fTime);

	virtual void startWithTarget(CCNode* pTarget);
	virtual CCObject* copyWithZone(CCZone* pZone);

    virtual void stop();
    virtual void update(float fTime);
    virtual bool isDone(void);

private:
	CCPointer<CCFiniteTimeAction> m_pAction;
	float m_fTime;
};

/** Action that repeats given action for given time interval */

class CCRepeatDuration : public CCActionInterval
{
public:
	static CCRepeatDuration* create(float fDuration, CCFiniteTimeAction* pAction);

	bool init(float fDuration, CCFiniteTimeAction* pAction);

	virtual void startWithTarget(CCNode* pTarget);
	virtual CCObject* copyWithZone(CCZone* pZone);

    virtual void stop();
    virtual void update(float fTime);
    virtual bool isDone(void);

private:
	CCPointer<CCFiniteTimeAction> m_pAction;
	float m_fStage;
};

/** @} */

NS_CC_END

#endif /* CCACTIONEXTENDED_H_ */
