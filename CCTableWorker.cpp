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

#include "base_nodes/CCNode.h"

#include "CCCommonExtended.h"
#include "CCGeometryExtended.h"

#include "CCTableWorker.h"

USING_NS_CC;

CCTableWorker* CCTableWorker::create(const CCRect& tWindowRect, int nWindowColumnCount, int nWindowRowCount, bool bFillDirectionHorizontal, bool bLayerDirectionHorizontal)
{
	CCTableWorker* pRet = new CCTableWorker();

	return pRet->init(tWindowRect, nWindowColumnCount, nWindowRowCount, bFillDirectionHorizontal, bLayerDirectionHorizontal) ? (CCTableWorker*)pRet->autorelease() : (delete pRet, pRet = NULL);
}

CCTableWorker::CCTableWorker() :
		m_nWindowColumnCount(1),
		m_nWindowRowCount(1),
		m_bFillDirectionHorizontal(true),
		m_bLayerDirectionHorizontal(false)
{
}

bool CCTableWorker::init(const CCRect& tWindowRect, int nWindowColumnCount, int nWindowRowCount, bool bFillDirectionHorizontal, bool bLayerDirectionHorizontal)
{
	m_tWindowRect = tWindowRect;
	m_nWindowColumnCount = nWindowColumnCount;
	m_nWindowRowCount = nWindowRowCount;
	m_bFillDirectionHorizontal = bFillDirectionHorizontal;
	m_bLayerDirectionHorizontal = bLayerDirectionHorizontal;
	m_tCellSize = cczNormalizeTo(m_tWindowRect.size, ccz(m_nWindowColumnCount, m_nWindowRowCount));

	return true;
}

void CCTableWorker::registerNode(CCNode* pNode)
{
	m_tNodes.addObject(pNode);
}

void CCTableWorker::clearNodes()
{
	m_tNodes.removeAllObjects();
}

CCNode* CCTableWorker::createCellNode()
{
	CCNode* pRet = CCNode::create();

	pRet->setContentSize(m_tCellSize);
	registerNode(pRet);

	return pRet;
}

void CCTableWorker::arrangeItems()
{
	unsigned int nItemCount = m_tNodes.count();
	int nColumnCount = (m_bLayerDirectionHorizontal ?
			nItemCount / m_nWindowRowCount + (int)(nItemCount % m_nWindowRowCount > 0) :
			m_nWindowColumnCount);
	int nRowCount = (m_bLayerDirectionHorizontal ?
			m_nWindowRowCount :
			nItemCount / m_nWindowColumnCount + (int)(nItemCount % m_nWindowColumnCount > 0));
	m_tLayerSize = cczDenormalizeTo(ccz((float)nColumnCount, (float)nRowCount), m_tCellSize);

	int nItemNum = 0;
	CCARRAY_FOREACH_OBJECT(&m_tNodes, CCNode*, pNode)
	{
		pNode->setPosition(ccpShift(m_tWindowRect.origin,
				cczDenormalizeTo(
						ccz(
								m_bFillDirectionHorizontal ? nItemNum % nColumnCount : nItemNum / nRowCount,
										nRowCount - 1 - (m_bFillDirectionHorizontal ? nItemNum / nColumnCount : nItemNum % nRowCount)),
						m_tCellSize)));
		++nItemNum;
	}
}
