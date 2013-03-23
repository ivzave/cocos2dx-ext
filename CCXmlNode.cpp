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

#include <stdarg.h>
#include <vector>
#include <algorithm>

#define LIBXML_SCHEMAS_ENABLED

#include "libxml/parser.h"
#include "libxml/tree.h"
#include "libxml/xmlschemas.h"

#include "CCFileUtils.h"

#include "CCCommonExtended.h"

#include "CCXmlNode.h"

USING_NS_CC;

#define CC_CAST (const char*)

void logXmlError(void* pCtx, const char* pMsg, ...)
{
	CC_UNUSED_PARAM(pCtx);

	char pBuf[kMaxLogLen + 1];
	va_list tArgs;
	va_start(tArgs, pMsg);
	vsprintf(pBuf, pMsg, tArgs);
	va_end(tArgs);
	CCLOG(pBuf);
}

// CCXmlSession

class CCXmlSession : private CCObject
{
public:
	static CCXmlSession* sharedSession();

	void retain();
	void release();

	void registerNode(xmlNodePtr pNode);
	void registerDocument(xmlDocPtr pDoc);
	void registerSchema(xmlSchemaPtr pSchema);

	void unregisterNode(xmlNodePtr pNode);

private:
	CCXmlSession();
	~CCXmlSession();

	std::vector<xmlNodePtr> m_tNodes;
	std::vector<xmlDocPtr> m_tDocuments;
	std::vector<xmlSchemaPtr> m_tSchemas;

	static CCXmlSession* s_pSharedXmlSession;
};

CCXmlSession* CCXmlSession::s_pSharedXmlSession = NULL;

void CCXmlSession::registerNode(xmlNodePtr pNode)
{
	m_tNodes.push_back(pNode);
}

void CCXmlSession::registerDocument(xmlDocPtr pDoc)
{
	m_tDocuments.push_back(pDoc);
}

void CCXmlSession::registerSchema(xmlSchemaPtr pSchema)
{
	m_tSchemas.push_back(pSchema);
}

void CCXmlSession::unregisterNode(xmlNodePtr pNode)
{
	std::vector<xmlNodePtr>::iterator pNodeIt = std::find(m_tNodes.begin(), m_tNodes.end(), pNode);
	CCDebugEnsure(pNodeIt != m_tNodes.end());
	m_tNodes.erase(pNodeIt);
}

CCXmlSession* CCXmlSession::sharedSession()
{
	if (s_pSharedXmlSession == NULL)
	{
		s_pSharedXmlSession = new CCXmlSession();
	}

	return s_pSharedXmlSession;
}

void CCXmlSession::retain()
{
	if (s_pSharedXmlSession == NULL)
	{
		s_pSharedXmlSession = new CCXmlSession();
	}

	s_pSharedXmlSession->CCObject::retain();
}

void CCXmlSession::release()
{
	s_pSharedXmlSession->CCObject::release();

	if (s_pSharedXmlSession->retainCount() == 1)
	{
		for (std::vector<xmlNodePtr>::iterator it = s_pSharedXmlSession->m_tNodes.begin(); it != s_pSharedXmlSession->m_tNodes.end(); ++it)
		{
			xmlFreeNode(*it);
		}
		for (std::vector<xmlDocPtr>::iterator it = s_pSharedXmlSession->m_tDocuments.begin(); it != s_pSharedXmlSession->m_tDocuments.end(); ++it)
		{
			xmlFreeDoc(*it);
		}
		for (std::vector<xmlSchemaPtr>::iterator it = s_pSharedXmlSession->m_tSchemas.begin(); it != s_pSharedXmlSession->m_tSchemas.end(); ++it)
		{
			xmlSchemaFree(*it);
		}
		s_pSharedXmlSession->CCObject::release();
		s_pSharedXmlSession = NULL;
	}
}

CCXmlSession::CCXmlSession()
{
	LIBXML_TEST_VERSION;
	xmlSetGenericErrorFunc(NULL, logXmlError);
}

CCXmlSession::~CCXmlSession()
{
	xmlCleanupParser();
}

//

struct cocos2d::CCXmlNodeData
{
	xmlNodePtr pNode;
};

struct cocos2d::CCXmlDocumentData
{
	xmlDocPtr pDoc;
};

struct cocos2d::CCXmlSchemaData
{
	xmlSchemaPtr pSchema;
};

// CCXmlNode

CCXmlNode* CCXmlNode::createWithName(const std::string& tName)
{
	CCXmlNode* pRet = new CCXmlNode();

	return pRet->initWithName(tName) ? (CCXmlNode*)pRet->autorelease() : (delete pRet, pRet = NULL);
}

CCXmlNode::CCXmlNode() :
		m_pData(NULL)
{
	CCXmlSession::sharedSession()->retain();
}

CCXmlNode::~CCXmlNode()
{
	CC_SAFE_DELETE(m_pData);
	CCXmlSession::sharedSession()->release();
}

bool CCXmlNode::initWithName(const std::string& tName)
{
	m_pData = new CCXmlNodeData();
	m_pData->pNode = xmlNewNode(NULL, BAD_CAST tName.c_str());
	CCXmlSession::sharedSession()->registerNode(m_pData->pNode);
	return true;
}

CCXmlDocument* CCXmlNode::getDocument() const
{
	if (m_pData->pNode->doc != NULL)
	{
		CCXmlDocument* pRet = new CCXmlDocument();
		pRet->m_pData = new CCXmlDocumentData();
		pRet->m_pData->pDoc = m_pData->pNode->doc;
		return (CCXmlDocument*)pRet->autorelease();
	}
	return NULL;
}

std::string CCXmlNode::getName() const
{
	return std::string(CC_CAST m_pData->pNode->name);
}

CCXmlNode* CCXmlNode::setName(const std::string& tName)
{
	xmlNodeSetName(m_pData->pNode, BAD_CAST tName.c_str());
	return this;
}

bool CCXmlNode::hasParent() const
{
	return m_pData->pNode->parent != NULL && m_pData->pNode->parent->type == XML_ELEMENT_NODE;
}

CCXmlNode* CCXmlNode::getParent() const
{
	CCDebugEnsureCustom(m_pData->pNode->parent != NULL && m_pData->pNode->parent->type == XML_ELEMENT_NODE, "parent not found");
	CCXmlNode* pRet = new CCXmlNode();
	pRet->m_pData = new CCXmlNodeData();
	pRet->m_pData->pNode = m_pData->pNode->parent;
	return (CCXmlNode*)pRet->autorelease();
}

CCXmlNode* CCXmlNode::setParent(CCXmlNode* pParent)
{
	CCDebugEnsureCustom(pParent != NULL, "no parent to set");
	if (xmlAddChild(pParent->m_pData->pNode, m_pData->pNode) == m_pData->pNode)
	{
		CCXmlSession::sharedSession()->unregisterNode(m_pData->pNode);
		return this;
	}
	CCUnreachableCustom("set parent failure");
	return NULL;
}

CCXmlNode* CCXmlNode::unlinkFromParent()
{
	if (m_pData->pNode->parent != NULL && m_pData->pNode->parent->type == XML_ELEMENT_NODE)
	{
		xmlUnlinkNode(m_pData->pNode);
		CCXmlSession::sharedSession()->registerNode(m_pData->pNode);
	}
	return this;
}

unsigned long CCXmlNode::getChildCount() const
{
	return xmlChildElementCount(m_pData->pNode);
}

bool CCXmlNode::hasChildWithName(const std::string& tName) const
{
	for (xmlNodePtr pChild = xmlFirstElementChild(m_pData->pNode); pChild != NULL; pChild = xmlNextElementSibling(pChild))
	{
		if (xmlStrEqual(pChild->name, BAD_CAST tName.c_str()))
		{
			return true;
		}
	}
	return false;
}

CCXmlNode* CCXmlNode::getChildWithName(const std::string& tName) const
{
	for (xmlNodePtr pChild = xmlFirstElementChild(m_pData->pNode); pChild != NULL; pChild = xmlNextElementSibling(pChild))
	{
		if (xmlStrEqual(pChild->name, BAD_CAST tName.c_str()))
		{
			CCXmlNode* pRet = new CCXmlNode();
			pRet->m_pData = new CCXmlNodeData();
			pRet->m_pData->pNode = pChild;
			return (CCXmlNode*)pRet->autorelease();
		}
	}
	CCUnreachableCustom("child not found : %s", tName.c_str());
	return NULL;
}

CCXmlNode* CCXmlNode::getFirstChild() const
{
	xmlNodePtr pChild = xmlFirstElementChild(m_pData->pNode);
	if (pChild != NULL)
	{
		CCXmlNode* pRet = new CCXmlNode();
		pRet->m_pData = new CCXmlNodeData();
		pRet->m_pData->pNode = pChild;
		return (CCXmlNode*)pRet->autorelease();
	}
	return NULL;
}

CCXmlNode* CCXmlNode::getNextSibling() const
{
	xmlNodePtr pSibling = xmlNextElementSibling(m_pData->pNode);
	if (pSibling != NULL)
	{
		CCXmlNode* pRet = new CCXmlNode();
		pRet->m_pData = new CCXmlNodeData();
		pRet->m_pData->pNode = pSibling;
		return (CCXmlNode*)pRet->autorelease();
	}
	return NULL;
}

CCXmlNode* CCXmlNode::addChild(CCXmlNode* pChild)
{
	CCDebugEnsureCustom(pChild != NULL, "no child to add");
	if (pChild->m_pData->pNode->parent == NULL)
	{
		CCXmlSession::sharedSession()->unregisterNode(pChild->m_pData->pNode);
	}
	if (xmlAddChild(m_pData->pNode, pChild->m_pData->pNode) == pChild->m_pData->pNode)
	{
		return this;
	}
	CCUnreachableCustom("add child failure");
	return NULL;
}

CCXmlNode* CCXmlNode::addSibling(CCXmlNode* pSibling)
{
	CCDebugEnsureCustom(pSibling != NULL, "no sibling to add");
	if (pSibling->m_pData->pNode->parent == NULL)
	{
		CCXmlSession::sharedSession()->unregisterNode(pSibling->m_pData->pNode);
	}
	if (xmlAddSibling(m_pData->pNode, pSibling->m_pData->pNode) == pSibling->m_pData->pNode)
	{
		return this;
	}
	CCUnreachableCustom("add sibling failure");
	return NULL;
}

CCXmlNode* CCXmlNode::createChildWithName(const std::string& tName)
{
	CCXmlNode* pChild = createWithName(tName);
	if (xmlAddChild(m_pData->pNode, pChild->m_pData->pNode) == pChild->m_pData->pNode)
	{
		CCXmlSession::sharedSession()->unregisterNode(pChild->m_pData->pNode);
		return pChild;
	}
	CCUnreachableCustom("add child failure : %s", tName.c_str());
	return NULL;
}

CCXmlNode* CCXmlNode::createSiblingWithName(const std::string& tName)
{
	CCXmlNode* pSibling = createWithName(tName);
	if (xmlAddSibling(m_pData->pNode, pSibling->m_pData->pNode) == pSibling->m_pData->pNode)
	{
		CCXmlSession::sharedSession()->unregisterNode(pSibling->m_pData->pNode);
		return pSibling;
	}
	CCUnreachableCustom("add sibling failure : %s", tName.c_str());
	return NULL;
}

bool CCXmlNode::hasAttribute(const std::string& tName) const
{
	return xmlHasProp(m_pData->pNode, BAD_CAST tName.c_str()) != NULL;
}

std::string CCXmlNode::getAttribute(const std::string& tName) const
{
	xmlChar* pValue = xmlGetProp(m_pData->pNode, BAD_CAST tName.c_str());
	if (pValue != NULL)
	{
		std::string tRet(CC_CAST pValue);
		xmlFree(pValue);
		return tRet;
	}
	CCUnreachableCustom("attribute not found : %s", tName.c_str());
	return std::string();
}

CCXmlNode* CCXmlNode::setAttribute(const std::string& tName, const std::string& pValue)
{
	xmlSetProp(m_pData->pNode, BAD_CAST tName.c_str(), BAD_CAST pValue.c_str());
	return this;
}

// CCXmlDocument

CCXmlDocument* CCXmlDocument::createWithFile(const std::string& tFileName)
{
	CCXmlDocument* pRet = new CCXmlDocument();

	return pRet->initWithFile(tFileName) ? (CCXmlDocument*)pRet->autorelease() : (delete pRet, pRet = NULL);
}

CCXmlDocument* CCXmlDocument::create()
{
	CCXmlDocument* pRet = new CCXmlDocument();

	return pRet->init() ? (CCXmlDocument*)pRet->autorelease() : (delete pRet, pRet = NULL);
}

CCXmlDocument::CCXmlDocument() :
		m_pData(NULL)
{
	CCXmlSession::sharedSession()->retain();
}

CCXmlDocument::~CCXmlDocument()
{
	CC_SAFE_DELETE(m_pData);
	CCXmlSession::sharedSession()->release();
}

bool CCXmlDocument::initWithFile(const std::string& tFileName)
{
	m_pData = new CCXmlDocumentData();
	m_pData->pDoc = xmlReadFile(CCFileUtils::sharedFileUtils()->fullPathForFilename(tFileName.c_str()).c_str(), NULL, XML_PARSE_PEDANTIC);
	if (m_pData->pDoc != NULL)
	{
		CCXmlSession::sharedSession()->registerDocument(m_pData->pDoc);
		return true;
	}
	CC_SAFE_DELETE(m_pData);
	return false;
}

bool CCXmlDocument::init()
{
	m_pData = new CCXmlDocumentData();
	m_pData->pDoc = xmlNewDoc(BAD_CAST "1.0");
	CCXmlSession::sharedSession()->registerDocument(m_pData->pDoc);
	return true;
}

CCXmlNode* CCXmlDocument::getRoot() const
{
	xmlNodePtr pRoot = xmlDocGetRootElement(m_pData->pDoc);
	if (pRoot != NULL)
	{
		CCXmlNode* pRet = new CCXmlNode();
		pRet->m_pData = new CCXmlNodeData();
		pRet->m_pData->pNode = pRoot;
		return (CCXmlNode*)pRet->autorelease();
	}
	return NULL;
}

CCXmlDocument* CCXmlDocument::setRoot(CCXmlNode* pRoot)
{
	CCDebugEnsureCustom(pRoot != NULL, "no root to set");
	if (pRoot->m_pData->pNode->parent == NULL)
	{
		CCXmlSession::sharedSession()->unregisterNode(pRoot->m_pData->pNode);
	}
	xmlNodePtr pRootPtr = xmlDocGetRootElement(m_pData->pDoc);
	if (pRootPtr != NULL)
	{
		CCXmlSession::sharedSession()->registerNode(pRootPtr);
	}
	xmlDocSetRootElement(m_pData->pDoc, pRoot->m_pData->pNode);
	return this;
}

CCXmlDocument* CCXmlDocument::clearRoot()
{
	xmlNodePtr pRootPtr = xmlDocGetRootElement(m_pData->pDoc);
	if (pRootPtr != NULL)
	{
		CCXmlSession::sharedSession()->registerNode(pRootPtr);
	}
	xmlUnlinkNode(pRootPtr);
	return this;
}

CCXmlDocument* CCXmlDocument::saveToFile(const std::string& tFileName)
{
	if (xmlSaveFormatFile(tFileName.c_str(), m_pData->pDoc, 4) >= 0)
	{
		return this;
	}
	return NULL;
}

// CCXmlSchema

CCXmlSchema* CCXmlSchema::createWithFile(const std::string& tFileName)
{
	CCXmlSchema* pRet = new CCXmlSchema();

	return pRet->initWithFile(tFileName) ? (CCXmlSchema*)pRet->autorelease() : (delete pRet, pRet = NULL);
}

CCXmlSchema::CCXmlSchema() :
		m_pData(NULL)
{
	CCXmlSession::sharedSession()->retain();
}

CCXmlSchema::~CCXmlSchema()
{
	CC_SAFE_DELETE(m_pData);
	CCXmlSession::sharedSession()->release();
}

bool CCXmlSchema::initWithFile(const std::string& tFileName)
{
	m_pData = new CCXmlSchemaData();
	xmlSchemaParserCtxtPtr pCtxt = xmlSchemaNewParserCtxt(CCFileUtils::sharedFileUtils()->fullPathForFilename(tFileName.c_str()).c_str());
	if (pCtxt != NULL)
	{
		m_pData->pSchema = xmlSchemaParse(pCtxt);
		xmlSchemaFreeParserCtxt(pCtxt);
		if (m_pData->pSchema != NULL)
		{
			CCXmlSession::sharedSession()->registerSchema(m_pData->pSchema);
			return true;
		}
	}
	CC_SAFE_DELETE(m_pData);
	return false;
}

bool CCXmlSchema::validateDocument(CCXmlDocument* pDocument) const
{
	CCDebugEnsureCustom(pDocument != NULL, "no document to validate");
	xmlSchemaValidCtxtPtr pCtxt = xmlSchemaNewValidCtxt(m_pData->pSchema);
	if (pCtxt != NULL)
	{
		bool bRet = xmlSchemaValidateDoc(pCtxt, pDocument->m_pData->pDoc) == 0;
		xmlSchemaFreeValidCtxt(pCtxt);
		return bRet;
	}
	return false;
}
