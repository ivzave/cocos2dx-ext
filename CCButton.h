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

#ifndef CCBUTTON_H_
#define CCBUTTON_H_

#include <vector>

#include "actions/CCAction.h"
#include "layers_scenes_transitions_nodes/CCLayer.h"

#include "CCPointer.h"

NS_CC_BEGIN

const int kCCButtonTouchPriority = -128;

/** @addtogroup nodes */
/** @{ */

/** Composite UI button.
 *  Can be composed of any number of elements with programmable behavior */

class CCButton : public CCLayer
{
public:
	static CCButton* create(const CCSize& tSize, CCObject* pTarget, SEL_MenuHandler pSelector);

	CCButton();
	bool init(const CCSize& tSize, CCObject* pTarget, SEL_MenuHandler pSelector);

	void addNodeWithActions(CCNode* pNode, int nZOrder, CCFiniteTimeAction* pSelectAction, CCFiniteTimeAction* pUnselectAction);

	virtual void registerWithTouchDispatcher();

	virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
	virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
	virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);
	virtual void ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent);

	virtual void select(bool bImmediate = false);
	virtual void unselect();
	virtual void activate();

	CC_SYNTHESIZE(bool, m_bIsEnabled, IsEnabled);
	CC_SYNTHESIZE_READONLY(bool, m_bIsSelected, IsSelected);
	CC_SYNTHESIZE_READONLY(float, m_fDelay, Delay);
	CC_SYNTHESIZE_READONLY(CCObject*, m_pTarget, Target);
	CC_SYNTHESIZE_READONLY(SEL_MenuHandler, m_pSelector, Selector);

private:
	struct CCButtonComponent
	{
		CCNode* pNode;
		CCPointer<CCFiniteTimeAction> pSelectAction;
		CCPointer<CCFiniteTimeAction> pUnselectAction;
		CCPointer<CCFiniteTimeAction> pRunningAction;
	};

private:
	std::vector<CCButtonComponent> m_tComponents;
};

/** Composite UI toggle button.
 *  Can be composed of any number of elements with programmable behavior */

class CCButtonToggle : public CCButton
{
public:
	static CCButtonToggle* create(const CCSize& tSize, CCObject* pTarget, SEL_MenuHandler pSelector);

	virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);

	virtual void activate();
};

/** @} */

NS_CC_END

#endif /* CCBUTTON_H_ */
