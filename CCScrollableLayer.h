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

#ifndef CCSCROLLABLELAYER_H_
#define CCSCROLLABLELAYER_H_

#include "layers_scenes_transitions_nodes/CCLayer.h"

NS_CC_BEGIN

const int kCCScrollableLayerTouchPriority = -256;

enum CCScrollableLayerBinding
{
	kCCScrollableLayerBindingBottomLeft,
	kCCScrollableLayerBindingBottomRight,
	kCCScrollableLayerBindingUpperLeft,
	kCCScrollableLayerBindingUpperRight
};

/** @addtogroup nodes */
/** @{ */

/** Node representing area where scrolling can appear limited to the size of underlying layer */

class CCScrollableLayer : public CCLayer
{
public:
	static CCScrollableLayer* create(const CCSize& tWindowSize, const CCSize& tLayerSize, CCScrollableLayerBinding eBinding = kCCScrollableLayerBindingBottomLeft);

	CCScrollableLayer();
	bool init(const CCSize& tWindowSize, const CCSize& tLayerSize, CCScrollableLayerBinding eBinding = kCCScrollableLayerBindingBottomLeft);

	void setShift(const CCSize& tShift);

	void setLayerSize(const CCSize& tSize);

	virtual void registerWithTouchDispatcher();

	virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
	virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
	virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);
	virtual void ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent);

private:
	CCScrollableLayerBinding m_eBinding;
	CCSize m_tMinShift;
	CCSize m_tMaxShift;

	bool m_bScrolling;
	CCPoint m_tBeginTouchPoint;
};

/** @} */

NS_CC_END

#endif /* CCSCROLLABLELAYER_H_ */
