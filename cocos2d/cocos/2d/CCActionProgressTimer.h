/****************************************************************************
Copyright (C) 2010      Lam Pham
Copyright (c) 2010-2012 cocos2d-x.org
CopyRight (c) 2013-2016 Chukong Technologies Inc.

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

#include <cocos/2d/CCActionInterval.h>
#include <cocos/base/ccConfig.h>
#include <cocos/platform/CCPlatformDefine.h>
#include <cocos/platform/CCPlatformMacros.h>

#include <chrono>

NS_CC_BEGIN

class Node;

/**
 * @addtogroup actions
 * @{
 */

/**
@brief Progress to percentage.
@details This action show the target node from current percentage to the specified percentage.
        You should specify the destination percentage when creating the action.
@since v0.99.1
*/
class CC_DLL ProgressTo : public ActionInterval
{
public:
    /**
     * @brief Create and initializes with a duration and a destination percentage.
     * @param duration Specify the duration of the ProgressTo action. It's a value in seconds.
     * @param percent Specify the destination percentage.
     * @return If the creation success, return a pointer of ProgressTo action; otherwise, return nil.
     */
    static ProgressTo* create(std::chrono::milliseconds duration, float percent);

    //
    // Overrides
    //
    ProgressTo* clone() const override;
    ProgressTo* reverse() const override;
    void startWithTarget(Node* target) override;
    void update(float time) override;

    CC_CONSTRUCTOR_ACCESS : ProgressTo() {}
    ~ProgressTo() override {}

    /**
     * @brief Initializes with a duration and destination percentage.
     * @param duration Specify the duration of the ProgressTo action. It's a value in seconds.
     * @param percent Specify the destination percentage.
     * @return If the creation success, return true; otherwise, return false.
     */
    bool initWithDuration(std::chrono::milliseconds duration, float percent);

protected:
    float _to;
    float _from;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ProgressTo)
};

/**
@brief Progress from a percentage to another percentage.
@since v0.99.1
*/
class CC_DLL ProgressFromTo : public ActionInterval
{
public:
    /**
     * @brief Create and initializes the action with a duration, a "from" percentage and a "to" percentage.
     * @param duration Specify the duration of the ProgressFromTo action. It's a value in seconds.
     * @param fromPercentage Specify the source percentage.
     * @param toPercentage Specify the destination percentage.
     * @return If the creation success, return a pointer of ProgressFromTo action; otherwise, return nil.
     */
    static ProgressFromTo* create(std::chrono::milliseconds duration, float fromPercentage, float toPercentage);

    //
    // Overrides
    //
    ProgressFromTo* clone() const override;
    ProgressFromTo* reverse() const override;
    void startWithTarget(Node* target) override;
    void update(float time) override;

    CC_CONSTRUCTOR_ACCESS : ProgressFromTo() {}
    ~ProgressFromTo() override {}

    /**
     * @brief Initializes the action with a duration, a "from" percentage and a "to" percentage.
     * @param duration Specify the duration of the ProgressFromTo action. It's a value in seconds.
     * @param fromPercentage Specify the source percentage.
     * @param toPercentage Specify the destination percentage.
     * @return If the creation success, return true; otherwise, return false.
     */
    bool initWithDuration(std::chrono::milliseconds duration, float fromPercentage, float toPercentage);

protected:
    float _to;
    float _from;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ProgressFromTo)
};

// end of actions group
/// @}

NS_CC_END
