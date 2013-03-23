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

#ifndef CCTABLEWORKER_H_
#define CCTABLEWORKER_H_

#include "cocoa/CCArray.h"
#include "ccTypes.h"

NS_CC_BEGIN

class CCNode;

/** Class to arrange nodes in table-like style */

class CCTableWorker : public CCObject
{
public:
	static CCTableWorker* create(const CCRect& tWindowRect, int nWindowColumnCount, int nWindowRowCount, bool bFillDirectionHorizontal, bool bLayerDirectionHorizontal);

	CCTableWorker();
	bool init(const CCRect& tWindowRect, int nWindowColumnCount, int nWindowRowCount, bool bFillDirectionHorizontal, bool bLayerDirectionHorizontal);

	void registerNode(CCNode* pNode);
	void clearNodes();

	CCNode* createCellNode();

	void arrangeItems();

	CC_SYNTHESIZE_READONLY_PASS_BY_REF(CCSize, m_tCellSize, CellSize);
	CC_SYNTHESIZE_READONLY_PASS_BY_REF(CCSize, m_tLayerSize, LayerSize);

private:
	CCRect m_tWindowRect;
	int m_nWindowColumnCount;
	int m_nWindowRowCount;
	bool m_bFillDirectionHorizontal;
	bool m_bLayerDirectionHorizontal;

	CCArray m_tNodes;
};

NS_CC_END

#endif /* CCTABLEWORKER_H_ */
