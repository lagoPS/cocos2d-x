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
#include <cocos/extensions/Particle3D/PU/CCPUEventHandler.h>
#include <cocos/math/CCMath.h>
#include <string>
#include <vector>

NS_CC_BEGIN

struct PUParticle3D;
class PUObserver;
class PUParticleSystem3D;

class CC_DLL PUDoAffectorEventHandler : public PUEventHandler
{
public:
    // Constants
    static const bool DEFAULT_PRE_POST;

    static PUDoAffectorEventHandler* create();

    /** Get the indication whether pre- and postprocessing must be done.
     */
    inline bool getPrePost() const noexcept { return _prePost; }

    /** Set the indication whether pre- and postprocessing must be done.
     */
    inline void setPrePost(const bool prePost) noexcept { _prePost = prePost; }

    /** Get the name of the affector that must be enabled or disabled.
     */
    inline const std::string& getAffectorName() const noexcept { return _affectorName; }

    /** Set the name of the affector.
     */
    inline void setAffectorName(const std::string& affectorName) noexcept { _affectorName = affectorName; }

    /** If the _handle() function of this class is invoked (by an Observer), it searches the
        ParticleAffector defined by the its name.
        The ParticleAffector is either part of the ParticleTechnique in which the
        DoAffectorEventHandler is defined, or if the Affector is not found, other
        ParticleTechniques are searched.
    */
    void handle(PUParticleSystem3D* particleSystem, PUParticle3D* particle, float timeElapsed) override;

    void copyAttributesTo(PUEventHandler* eventHandler) override;

    CC_CONSTRUCTOR_ACCESS : PUDoAffectorEventHandler();
    ~PUDoAffectorEventHandler() override = default;

protected:
    // Identifies the name of affector
    std::string _affectorName;

    // Determines whether the pre- and post processing activities must be executed also
    bool _prePost;
};

NS_CC_END
