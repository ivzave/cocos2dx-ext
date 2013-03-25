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

#ifndef CCPOINTER_H_
#define CCPOINTER_H_

#include "CCCommonExtended.h"

NS_CC_BEGIN

/** @defgroup smartptr Smart pointer */
/** @{ */

/** Smart pointer class for use with Cocos2d-x */

template<typename T>
class CCPointer
{
public:
	CCPointer() :
		m_pObject(NULL)
	{
	}

	CCPointer(T* pObject) :
		m_pObject(pObject)
	{
		CC_SAFE_RETAIN(m_pObject);
	}

	template<typename U>
	CCPointer(U* pObject) :
		m_pObject(pObject)
	{
		CC_SAFE_RETAIN(m_pObject);
	}

	CCPointer(const CCPointer& tPointer) :
		m_pObject(tPointer.m_pObject)
	{
		CC_SAFE_RETAIN(m_pObject);
	}

	template<typename U>
	CCPointer(const CCPointer<U>& tPointer) :
		m_pObject(tPointer.m_pObject)
	{
		CC_SAFE_RETAIN(m_pObject);
	}

	~CCPointer()
	{
		CC_SAFE_RELEASE(m_pObject);
	}

	template<typename U>
	CCPointer& operator=(U* pObject)
	{
		if (m_pObject != pObject)
		{
			CC_SAFE_RELEASE(m_pObject);
			m_pObject = pObject;
			CC_SAFE_RETAIN(m_pObject);
		}
		return *this;
	}

	CCPointer& operator=(const CCPointer& tPointer)
	{
		if (m_pObject != tPointer.m_pObject)
		{
			CC_SAFE_RELEASE(m_pObject);
			m_pObject = tPointer.m_pObject;
			CC_SAFE_RETAIN(m_pObject);
		}
		return *this;
	}

	template<typename U>
	CCPointer& operator=(const CCPointer<U>& tPointer)
	{
		if (m_pObject != tPointer.m_pObject)
		{
			CC_SAFE_RELEASE(m_pObject);
			m_pObject = tPointer.m_pObject;
			CC_SAFE_RETAIN(m_pObject);
		}
		return *this;
	}

	T* operator->()
	{
		CCDebugEnsureCustom(m_pObject != NULL, "dereferencing null pointer");
		return m_pObject;
	}

	const T* operator->() const
	{
		CCDebugEnsureCustom(m_pObject != NULL, "dereferencing null pointer");
		return m_pObject;
	}

	bool operator==(T* pObject) const
	{
		return m_pObject == pObject;
	}

	bool operator!= (T* pObject) const
	{
		return m_pObject != pObject;
	}

	operator T*() const
	{
		return m_pObject;
	}

	template<typename U>
	operator U*() const
	{
		return static_cast<U*>(m_pObject);
	}

private:
	T* m_pObject;

	template <typename U>
	friend class CCPointer;
};

/** Helper function for CCPointer. Use it to create smart pointers to objects which need to be released (e.g. created with operator "new") */

template<typename T>
CCPointer<T> CCPointerGrab(T* pObject)
{
	CCPointer<T> tRet(pObject);
	pObject->release();
	return tRet;
}

NS_CC_END

/** Declare protected smart pointer member variable with public getter */

#define CC_PROPERTY_READONLY_SMART(varType, varName, funName) \
protected: \
	cocos2d::CCPointer<varType> varName; \
public: \
	virtual varType* get##funName() const;

/** Declare protected smart pointer member variable with public getter and setter */

#define CC_PROPERTY_SMART(varType, varName, funName) \
protected: \
	cocos2d::CCPointer<varType> varName; \
public: \
	virtual varType* get##funName(); \
	virtual void set##funName(varType* var);

/** Declare protected smart pointer member variable with generated public getter */

#define CC_SYNTHESIZE_READONLY_SMART(varType, varName, funName) \
protected: \
	cocos2d::CCPointer<varType> varName; \
public: \
	virtual varType* get##funName() const { return varName; }

/** Declare protected smart pointer member variable with generated public getter and setter */

#define CC_SYNTHESIZE_SMART(varType, varName, funName) \
protected: \
	cocos2d::CCPointer<varType> varName; \
public: \
	virtual varType* get##funName() const { return varName; } \
	virtual void set##funName(varType* var) { varName = var; }

/** @} */

#endif /* CCPOINTER_H_ */
