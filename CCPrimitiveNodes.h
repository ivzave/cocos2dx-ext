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

#ifndef CCPRIMITIVENODES_H_
#define CCPRIMITIVENODES_H_

#include "base_nodes/CCNode.h"
#include "ccTypes.h"

NS_CC_BEGIN

/** @defgroup nodes Nodes
 *  Additional nodes and node-related extensions */
/** @{ */

/** Node representing solid or empty colour rectangle */

class CCRectNode : public CCNodeRGBA
{
public:
	static CCRectNode* createWithSize(const CCSize& tSize, const ccColor4F& tColor, bool bFill = false);
	static CCRectNode* createWithRect(const CCRect& tRect, const ccColor4F& tColor, bool bFill = false);

	bool initWithSize(const CCSize& tSize, const ccColor4F& tColor, bool bFill = false);
	bool initWithRect(const CCRect& tRect, const ccColor4F& tColor, bool bFill = false);

	virtual void draw();

private:
	bool m_bFill;
};

/** Node representing colour line */

class CCLineNode : public CCNodeRGBA
{
public:
	static CCLineNode* createWithPoints(const CCPoint& tBeginPoint, const CCPoint& tEndPoint, const ccColor4F& tColor);

	bool initWithPoints(const CCPoint& tBeginPoint, const CCPoint& tEndPoint, const ccColor4F& tColor);

	virtual void draw();
};

/** Node representing colour dot */

class CCDotNode : public CCNodeRGBA
{
public:
	static CCDotNode* createWithPoint(const CCPoint& tPoint, const ccColor4F& tColor);

	bool initWithPoint(const CCPoint& tPoint, const ccColor4F& tColor);

	virtual void draw();
};

NS_CC_END

/** @} */

#endif /* CCPRIMITIVENODES_H_ */
