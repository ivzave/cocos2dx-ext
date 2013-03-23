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

#ifndef CCPLAY_H_
#define CCPLAY_H_

#include <string>

#include "actions/CCActionInstant.h"

NS_CC_BEGIN

/** Action which plays a sound effect using SimpleAudioEngine. Is a CCActionInstant because there's no way to get effect duration */

class CCPlay : public CCActionInstant
{
public:
	static CCPlay* create(const std::string& tSample);

	bool init(const std::string& tSample);

	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual void startWithTarget(CCNode* pTarget);

private:
	std::string m_tSample;
};

NS_CC_END

#endif /* CCPLAY_H_ */
