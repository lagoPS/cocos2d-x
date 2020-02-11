/****************************************************************************
 Copyright (c) 2014-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#include <cocos/3d/CCAnimate3D.h>
#include <cocos/3d/CCSprite3D.h>
#include <cocos/3d/CCSkeleton3D.h>
#include <cocos/platform/CCFileUtils.h>
#include <cocos/base/CCConfiguration.h>
#include <cocos/base/CCEventCustom.h>
#include <cocos/base/CCDirector.h>
#include <cocos/base/CCEventDispatcher.h>

NS_CC_BEGIN

using namespace std::chrono_literals;

std::unordered_map<Node*, Animate3D*> Animate3D::s_fadeInAnimates;
std::unordered_map<Node*, Animate3D*> Animate3D::s_fadeOutAnimates;
std::unordered_map<Node*, Animate3D*> Animate3D::s_runningAnimates;
std::chrono::milliseconds Animate3D::_transTime = 100ms;

//create Animate3D using Animation.
Animate3D* Animate3D::create(Animation3D* animation)
{
    auto animate = new (std::nothrow) Animate3D();
    animate->init(animation);
    animate->autorelease();
    
    return animate;
}

Animate3D* Animate3D::create(Animation3D* animation, std::chrono::milliseconds fromTime, std::chrono::milliseconds duration)
{
    auto animate = new (std::nothrow) Animate3D();
    animate->init(animation, fromTime, duration);
    animate->autorelease();
    
    return  animate;
}

Animate3D* Animate3D::createWithFrames(Animation3D* animation, int startFrame, int endFrame, float frameRate)
{
    auto animate = new (std::nothrow) Animate3D();
    animate->initWithFrames(animation, startFrame, endFrame, frameRate);
    animate->autorelease();
    
    return  animate;
}

bool Animate3D::init(Animation3D* animation)
{
    _animation = animation;
    animation->retain();
    setDuration(animation->getDuration());
    setOriginInterval(animation->getDuration());
    setQuality(Configuration::getInstance()->getAnimate3DQuality());
    return true;
}

bool Animate3D::init(Animation3D* animation, std::chrono::milliseconds fromTime, std::chrono::milliseconds duration)
{
    auto fullDuration = animation->getDuration();
    if (duration > fullDuration - fromTime)
        duration = fullDuration - fromTime;
    
    _start = 1.0f * fromTime.count() / fullDuration.count();
    _last = 1.0f * duration.count() / fullDuration.count();
    setDuration(duration);
    setOriginInterval(duration);
    _animation = animation;
    animation->retain();
    setQuality(Configuration::getInstance()->getAnimate3DQuality());
    return true;
}

bool Animate3D::initWithFrames(Animation3D* animation, int startFrame, int endFrame, float frameRate)
{
    float perFrameTime = 1.f / frameRate;
    auto fromTime = std::chrono::milliseconds(static_cast<std::size_t>(startFrame * perFrameTime * 1000.f));
    auto duration = std::chrono::milliseconds(static_cast<std::size_t>((endFrame - startFrame) * perFrameTime * 1000.f));
    _frameRate = frameRate;
    init(animation, fromTime, duration);
    return true;
}

/** returns a clone of action */
Animate3D* Animate3D::clone() const
{
    auto animate = const_cast<Animate3D*>(this);
    auto copy = Animate3D::create(animate->_animation);
    
    copy->_absSpeed = _absSpeed;
    copy->_weight = _weight;
    copy->_elapsed = _elapsed;
    copy->_start = _start;
    copy->_last = _last;
    copy->_playReverse = _playReverse;
    copy->setDuration(animate->getDuration());
    copy->setOriginInterval(animate->getOriginInterval());
    return copy;
}

/** returns a new action that performs the exactly the reverse action */
Animate3D* Animate3D::reverse() const
{
    auto animate = clone();
    animate->_playReverse = !animate->_playReverse;
    return animate;
}

Node* findChildByNameRecursively(Node* node, const std::string &childName)
{
    const std::string& name = node->getName();
    if (name == childName)
        return node;
    
    const Vector<Node*>& children = node->getChildren();
    for (const auto& child : children)
    {
        Node* findNode = findChildByNameRecursively(child, childName);
        if (findNode)
            return findNode;
    }
    return nullptr;
}

//! called before the action start. It will also set the target.
void Animate3D::startWithTarget(Node *target)
{
    bool needReMap = (_target != target);
    ActionInterval::startWithTarget(target);
    
    if (needReMap)
    {
        _boneCurves.clear();
        _nodeCurves.clear();
        
        bool hasCurve = false;
        Sprite3D* sprite = dynamic_cast<Sprite3D*>(target);
        
        if(sprite)
        {
            if (_animation)
            {
                const std::unordered_map<std::string, Animation3D::Curve*>& boneCurves = _animation->getBoneCurves();
                for (const auto& iter: boneCurves)
                {
                    const std::string& boneName = iter.first;
                    auto skin = sprite->getSkeleton();
                    if(skin)
                    {
                        auto bone = skin->getBoneByName(boneName);
                        if (bone)
                        {
                            auto curve = _animation->getBoneCurveByName(boneName);
                            _boneCurves[bone] = curve;
                            hasCurve = true;
                        }
                        else
                        {
                            Node* node = nullptr;
                            if (target->getName() == boneName)
                                node = target;
                            else
                                node = findChildByNameRecursively(target, boneName);
                            
                            if (node)
                            {
                                auto curve = _animation->getBoneCurveByName(boneName);
                                if (curve)
                                {
                                    _nodeCurves[node] = curve;
                                    hasCurve = true;
                                }
                            }
                        }
                    }
                }
            }
        }
        else
        {
            const std::unordered_map<std::string, Animation3D::Curve*>& boneCurves = _animation->getBoneCurves();
            for (const auto& iter: boneCurves)
            {
                const std::string& boneName = iter.first;
                Node* node = nullptr;
                if (target->getName() == boneName)
                    node = target;
                else
                    node = findChildByNameRecursively(target, boneName);
                
                if (node)
                {
                    auto curve = _animation->getBoneCurveByName(boneName);
                    if (curve)
                    {
                        _nodeCurves[node] = curve;
                        hasCurve = true;
                    }
                }
                
            }
        }
        
        if (!hasCurve)
        {
            CCLOG("warning: no animation found for the skeleton");
        }
    }
    
    auto runningAction = s_runningAnimates.find(target);
    if (runningAction != s_runningAnimates.end())
    {
        //make the running action fade out
        auto action = (*runningAction).second;
        if (action != this)
        {
            if (_transTime < 1ms)
            {
                s_runningAnimates[target] = this;
                _state = Animate3D::Animate3DState::Running;
                _weight = 1.0f;
            }
            else
            {
                s_fadeOutAnimates[target] = action;
                action->_state = Animate3D::Animate3DState::FadeOut;
                action->_accTransTime = 0ms;
                action->_weight = 1.0f;
                action->_lastTime = 0ms;
                s_runningAnimates.erase(target);
                s_fadeInAnimates[target] = this;
                _accTransTime = 0ms;
                _state = Animate3D::Animate3DState::FadeIn;
                _weight = 0.f;
                _lastTime = 0ms;
            }
        }
    }
    else
    {
        auto it = s_fadeInAnimates.find(target);
        if (it != s_fadeInAnimates.end())
        {
            s_fadeInAnimates.erase(it);
        }
        s_runningAnimates[target] = this;
        _state = Animate3D::Animate3DState::Running;
        _weight = 1.0f;
    }
}

void Animate3D::stop()
{
    removeFromMap();
    
    ActionInterval::stop();
}

//! called every frame with it's delta time. DON'T override unless you know what you are doing.
void Animate3D::step(float dt)
{
    ActionInterval::step(dt);
}

bool cmpEventInfoAsc(Animate3D::Animate3DDisplayedEventInfo* info1, Animate3D::Animate3DDisplayedEventInfo* info2)
{
    return info1->frame < info2->frame;
}

bool cmpEventInfoDes(Animate3D::Animate3DDisplayedEventInfo* info1, Animate3D::Animate3DDisplayedEventInfo* info2)
{
    return info1->frame > info2->frame;
}

void Animate3D::update(float ft)
{
    std::chrono::milliseconds t{static_cast<int>(1000.0f * ft)};
    if (_target)
    {
        if (_state == Animate3D::Animate3DState::FadeIn && _lastTime > 0ms)
        {
            _accTransTime += (t - _lastTime).count() * getDuration() / 1000;
            
            _weight = _accTransTime / _transTime;
            if (_weight >= 1.0f)
            {
                _accTransTime = _transTime;
                _weight = 1.0f;
                _state = Animate3D::Animate3DState::Running;
                s_fadeInAnimates.erase(_target);
                s_runningAnimates[_target] = this;
            }
        }
        else if (_state == Animate3D::Animate3DState::FadeOut && _lastTime > 0ms)
        {
            _accTransTime += (t - _lastTime).count() * getDuration() / 1000;
            
            _weight = 1 - _accTransTime / _transTime;
            if (_weight <= 0.0f)
            {
                _accTransTime = _transTime;
                _weight = 0.0f;
                
                s_fadeOutAnimates.erase(_target);
                _target->stopAction(this);
                return;
            }
        }
        auto lastTime = _lastTime;
        _lastTime = t;
        
        if (_quality != Animate3DQuality::QUALITY_NONE)
        {
            if (_weight > 0.0f)
            {
                float transDst[3], rotDst[4], scaleDst[3];
                float* trans = nullptr, *rot = nullptr, *scale = nullptr;
                if (_playReverse){
                    t = 1s - t;
                    lastTime = 1s - lastTime;
                }
                
                t = std::chrono::milliseconds{static_cast<int>(1000.0f * (_start + t.count() / 1000.0f * _last))};
                lastTime = std::chrono::milliseconds{static_cast<int>(1000.0f * (_start + lastTime.count() / 1000.0f * _last))};
                
                for (const auto& it : _boneCurves) {
                    auto bone = it.first;
                    auto curve = it.second;
                    if (curve->translateCurve)
                    {
                        curve->translateCurve->evaluate(t.count() / 1000.0f, transDst, _translateEvaluate);
                        trans = &transDst[0];
                    }
                    if (curve->rotCurve)
                    {
                        curve->rotCurve->evaluate(t.count() / 1000.0f, rotDst, _roteEvaluate);
                        rot = &rotDst[0];
                    }
                    if (curve->scaleCurve)
                    {
                        curve->scaleCurve->evaluate(t.count() / 1000.0f, scaleDst, _scaleEvaluate);
                        scale = &scaleDst[0];
                    }
                    bone->setAnimationValue(trans, rot, scale, this, _weight);
                }
                
                for (const auto& it : _nodeCurves)
                {
                    auto node = it.first;
                    auto curve = it.second;
                    Mat4 transform;
                    if (curve->translateCurve)
                    {
                        curve->translateCurve->evaluate(t.count() / 1000.0f, transDst, _translateEvaluate);
                        transform.translate(transDst[0], transDst[1], transDst[2]);
                    }
                    if (curve->rotCurve)
                    {
                        curve->rotCurve->evaluate(t.count() / 1000.0f, rotDst, _roteEvaluate);
                        Quaternion qua(rotDst[0], rotDst[1], rotDst[2], rotDst[3]);
                        transform.rotate(qua);
                    }
                    if (curve->scaleCurve)
                    {
                        curve->scaleCurve->evaluate(t.count() / 1000.0f, scaleDst, _scaleEvaluate);
                        transform.scale(scaleDst[0], scaleDst[1], scaleDst[2]);
                    }
                    node->setAdditionalTransform(&transform);
                }
                if (!_keyFrameUserInfos.empty()){
                    auto prekeyTime = lastTime.count() / 1000.0f * getDuration().count() / 1000.0f * _frameRate;
                    auto keyTime = t.count() / 1000.0f * getDuration().count() / 1000.0f * _frameRate;
                    std::vector<Animate3DDisplayedEventInfo*> eventInfos;
                    for (const auto& keyFrame : _keyFrameUserInfos)
                    {
                        if ((!_playReverse && keyFrame.first >= prekeyTime && keyFrame.first < keyTime)
                            || (_playReverse && keyFrame.first >= keyTime && keyFrame.first < prekeyTime))
                            {
                                auto& frameEvent = _keyFrameEvent[keyFrame.first];
                                if (frameEvent == nullptr)
                                    frameEvent = new (std::nothrow) EventCustom(Animate3DDisplayedNotification);
                                auto eventInfo = &_displayedEventInfo[keyFrame.first];
                                eventInfo->target = _target;
                                eventInfo->frame = keyFrame.first;
                                eventInfo->userInfo = &_keyFrameUserInfos[keyFrame.first];
                                eventInfos.push_back(eventInfo);
                                frameEvent->setUserData((void*)eventInfo);
                            }
                    }
                    std::sort(eventInfos.begin(), eventInfos.end(), _playReverse ? cmpEventInfoDes : cmpEventInfoAsc);
                    for (auto eventInfo : eventInfos) {
                        Director::getInstance()->getEventDispatcher()->dispatchEvent(_keyFrameEvent[eventInfo->frame]);
                    }
                }
            }
        }
    }
}

float Animate3D::getSpeed() const
{
    return _playReverse ? -_absSpeed : _absSpeed;
}
void Animate3D::setSpeed(float speed)
{
    _absSpeed = fabsf(speed);
    _playReverse = speed < 0;
    _duration = std::chrono::milliseconds{static_cast<int>(_originInterval.count() / _absSpeed)};
}

void Animate3D::setWeight(float weight)
{
    CCASSERT(weight >= 0.0f, "invalid weight");
    _weight = fabsf(weight);
}

void Animate3D::setOriginInterval(std::chrono::milliseconds interval)
{
    _originInterval = interval;
}

void Animate3D::setQuality(Animate3DQuality quality)
{
    if (quality == Animate3DQuality::QUALITY_HIGH)
    {
        _translateEvaluate = EvaluateType::INT_LINEAR;
        _roteEvaluate = EvaluateType::INT_QUAT_SLERP;
        _scaleEvaluate = EvaluateType::INT_LINEAR;
    }
    else if(quality == Animate3DQuality::QUALITY_LOW)
    {
        _translateEvaluate = EvaluateType::INT_NEAR;
        _roteEvaluate = EvaluateType::INT_NEAR;
        _scaleEvaluate = EvaluateType::INT_NEAR;
    }
    _quality = quality;
}

Animate3DQuality Animate3D::getQuality() const
{
    return _quality;
}

const ValueMap* Animate3D::getKeyFrameUserInfo(int keyFrame) const
{
    auto iter = _keyFrameUserInfos.find(keyFrame);
    if (iter != _keyFrameUserInfos.end())
        return &iter->second;

    return nullptr;
}

ValueMap* Animate3D::getKeyFrameUserInfo(int keyFrame)
{
    auto iter = _keyFrameUserInfos.find(keyFrame);
    if (iter != _keyFrameUserInfos.end())
        return &iter->second;

    return nullptr;
}

void Animate3D::setKeyFrameUserInfo(int keyFrame, const ValueMap &userInfo)
{
    _keyFrameUserInfos[keyFrame] = userInfo;
}

Animate3D::Animate3D()
: _state(Animate3D::Animate3DState::Running)
, _animation(nullptr)
, _absSpeed(1.f)
, _weight(1.f)
, _start(0.f)
, _last(1.f)
, _playReverse(false)
, _accTransTime(0ms)
, _lastTime(0ms)
, _originInterval(0ms)
, _frameRate(30.0f)
{
    setQuality(Animate3DQuality::QUALITY_HIGH);
}
Animate3D::~Animate3D()
{
    removeFromMap();
    
    for (auto& it : _keyFrameEvent) {
        delete it.second;
    }
    _keyFrameEvent.clear();
    
    CC_SAFE_RELEASE(_animation);
}

void Animate3D::removeFromMap()
{
    //remove this action from map
    if (_target)
    {
        auto it = s_fadeInAnimates.find(_target);
        if (it != s_fadeInAnimates.end() && it->second == this)
            s_fadeInAnimates.erase(it);
        
        it = s_fadeOutAnimates.find(_target);
        if (it != s_fadeOutAnimates.end() && it->second == this)
            s_fadeOutAnimates.erase(it);
        
        it = s_runningAnimates.find(_target);
        if (it != s_runningAnimates.end() && it->second == this)
            s_runningAnimates.erase(it);
    }
}

NS_CC_END