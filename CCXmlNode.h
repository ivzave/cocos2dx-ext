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

#ifndef CCXMLNODE_H_
#define CCXMLNODE_H_

#include <string>

#include "cocoa/CCObject.h"

NS_CC_BEGIN

class CCXmlDocument;

struct CCXmlNodeData;

/** @defgroup xml XML */
/** @{ */

/** CCObject representing XML node */

class CCXmlNode : public CCObject
{
public:
	static CCXmlNode* createWithName(const std::string& tName);

	CCXmlNode();
	~CCXmlNode();

	bool initWithName(const std::string& tName);

	CCXmlDocument* getDocument() const;

	std::string getName() const;
	CCXmlNode* setName(const std::string& tName);

	bool hasParent() const;
	CCXmlNode* getParent() const;
	CCXmlNode* setParent(CCXmlNode* pParent);
	CCXmlNode* unlinkFromParent();

	unsigned long getChildCount() const;
	bool hasChildWithName(const std::string& tName) const;
	CCXmlNode* getChildWithName(const std::string& tName) const;
	CCXmlNode* getFirstChild() const;
	CCXmlNode* getNextSibling() const;
	CCXmlNode* addChild(CCXmlNode* pChild);
	CCXmlNode* addSibling(CCXmlNode* pSibling);
	CCXmlNode* createChildWithName(const std::string& tName);
	CCXmlNode* createSiblingWithName(const std::string& tName);

	bool hasAttribute(const std::string& tName) const;
	std::string getAttribute(const std::string& tName) const;
	CCXmlNode* setAttribute(const std::string& tName, const std::string& tValue);

private:
	CCXmlNodeData* m_pData;

	friend class CCXmlDocument;
};

struct CCXmlDocumentData;

/** CCObject representing XML document */

class CCXmlDocument : public CCObject
{
public:
	static CCXmlDocument* createWithFile(const std::string& tFileName);
	static CCXmlDocument* create();

	CCXmlDocument();
	~CCXmlDocument();

	bool initWithFile(const std::string& tFileName);
	bool init();

	CCXmlNode* getRoot() const;
	CCXmlDocument* setRoot(CCXmlNode* pRoot);
	CCXmlDocument* clearRoot();

	CCXmlDocument* saveToFile(const std::string& tFileName);

private:
	CCXmlDocumentData* m_pData;

	friend class CCXmlNode;
	friend class CCXmlSchema;
};

struct CCXmlSchemaData;

/** CCObject representing XML schema */

class CCXmlSchema : public CCObject
{
public:
	static CCXmlSchema* createWithFile(const std::string& tFileName);

	CCXmlSchema();
	~CCXmlSchema();

	bool initWithFile(const std::string& tFileName);

	bool validateDocument(CCXmlDocument* pDocument) const;

private:
	CCXmlSchemaData* m_pData;
};

NS_CC_END

/** Iteration macro for CCXmlNode children which does declare current child pointer in a block */

#define CCXML_FOREACH_CHILD(pNode, pChild) \
if (cocos2d::CCXmlNode* __pParent = (pNode)) \
	for(cocos2d::CCXmlNode* pChild = __pParent->getFirstChild(); pChild != NULL; pChild = pChild->getNextSibling())

/** @} */

#endif /* CCXMLNODE_H_ */
