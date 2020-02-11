/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015 Chukong Technologies Inc.

 http://www.cocos2d-x.org

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


#pragma once

#include <cocos/base/CCRef.h>
#include <cocos/extensions/Particle3D/PU/CCPUObserver.h>
#include <cocos/math/CCMath.h>
#include <string>
#include <vector>

NS_CC_BEGIN

struct PUParticle3D;
class PUParticleSystem3D;
class CC_DLL PUOnQuotaObserver : public PUObserver
{
public:
    static PUOnQuotaObserver* create();

    /** @copydoc ParticleObserver::_notifyStart */
    bool observe(PUParticle3D* particle, float timeElapsed) override;

    /** @copydoc ParticleObserver::_notifyStart */
    void postUpdateObserver(float deltaTime) override;

    CC_CONSTRUCTOR_ACCESS : PUOnQuotaObserver()
    : PUObserver()
    , _result(false)
    {
    }
    ~PUOnQuotaObserver() override = default;

protected:
    bool _result;
};

NS_CC_END