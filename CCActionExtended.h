#ifndef CCACTIONEXTENDED_H_
#define CCACTIONEXTENDED_H_

#include "actions/CCActionInstant.h"
#include "actions/CCActionInterval.h"

#include "CCPointer.h"

NS_CC_BEGIN

/** Action that does nothing. Just a stub */

class CCNone : public CCActionInstant
{
public:
	static CCNone* create();

	virtual CCObject* copyWithZone(CCZone* pZone);
};

/** Action that removes the node from its parent (with cleanup) */

class CCRemove : public CCActionInstant
{
public:
	static CCRemove* create();

	virtual void startWithTarget(CCNode* pTarget);
	virtual CCObject* copyWithZone(CCZone* pZone);
};

/** Action that modifies the Z-order of the node */

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

/** Action that changes nodes parent. Modifies the position so the node won't move */

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

/** Action that changes the progress of CCProgressTimer by given value */

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

/** Action that sets the texture of the node. Requires CCTextureProtocol */

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

/** Action that changes the text label of the node. Requires CCLabelProtocol */

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

NS_CC_END

#endif /* CCACTIONEXTENDED_H_ */
