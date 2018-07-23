/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.

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

#ifndef CC_BASE_TOUCH_H
#define CC_BASE_TOUCH_H

#include <cocos/base/CCRef.h>
#include <cocos/math/Vec2.h>
#include <cocos/platform/CCPlatformMacros.h>
#include <cocos/platform/CCPlatformDefine.h>

NS_CC_BEGIN

/**
 * @addtogroup base
 * @{
 */

/** @class Touch
 * @brief Encapsulates the Touch information, such as touch point, id and so on,
 and provides the methods that commonly used.
 */
class CC_DLL Touch final : public Ref
{
public:
    Touch() = default;
    Touch(Touch const&) = default;
    Touch& operator=(Touch const&) = default;
    Touch(Touch&&) noexcept = default;
    Touch& operator=(Touch&&) noexcept = default;
    ~Touch() final;

    /**
     * Dispatch mode, how the touches are dispatched.
     * @js NA
     */
    enum class DispatchMode : std::uint8_t
    {
        ALL_AT_ONCE, /** All at once. */
        ONE_BY_ONE, /** One by one. */
    };

    /** Returns the current touch location in OpenGL coordinates.
     *
     * @return The current touch location in OpenGL coordinates.
     */
    Vec2 getLocation() const;
    /** Returns the previous touch location in OpenGL coordinates.
     *
     * @return The previous touch location in OpenGL coordinates.
     */
    Vec2 getPreviousLocation() const;
    /** Returns the start touch location in OpenGL coordinates.
     *
     * @return The start touch location in OpenGL coordinates.
     */
    inline Vec2 getStartLocation() const;
    /** Returns the delta of 2 current touches locations in screen coordinates.
     *
     * @return The delta of 2 current touches locations in screen coordinates.
     */
    Vec2 getDelta() const;
    /** Returns the current touch location in screen coordinates.
     *
     * @return The current touch location in screen coordinates.
     */
    inline Vec2 getLocationInView() const noexcept { return _point; }
    /** Returns the previous touch location in screen coordinates.
     *
     * @return The previous touch location in screen coordinates.
     */
    inline Vec2 getPreviousLocationInView() const noexcept { return _prevPoint; }
    /** Returns the start touch location in screen coordinates.
     *
     * @return The start touch location in screen coordinates.
     */
    inline Vec2 getStartLocationInView() const noexcept { return _startPoint; }

    /** Set the touch information. It always used to monitor touch event.
     *
     * @param id A given id
     * @param x A given x coordinate.
     * @param y A given y coordinate.
     */
    void setTouchInfo(int id, float x, float y);

    /** Set the touch information. It always used to monitor touch event.
     *
     * @param id A given id
     * @param x A given x coordinate.
     * @param y A given y coordinate.
     * @param force Current force for 3d touch.
     * @param maxForce maximum possible force for 3d touch.
     */
    void setTouchInfo(int id, float x, float y, float force, float maxForce);
    /** Get touch id.
     * @js getId
     * @lua getId
     *
     * @return The id of touch.
     */
    inline int getID() const noexcept { return _id; }
    /** Returns the current touch force for 3d touch.
     *
     * @return The current touch force for 3d touch.
     */
    inline float getCurrentForce() const noexcept { return _curForce; }
    /** Returns the maximum touch force for 3d touch.
     *
     * @return The maximum touch force for 3d touch.
     */
    inline float getMaxForce() const noexcept { return _maxForce; }

private:
    int _id = 0;
    bool _startPointCaptured = false;
    Vec2 _startPoint;
    Vec2 _point;
    Vec2 _prevPoint;
    float _curForce = 0.f;
    float _maxForce = 0.f;
};

// end of base group
/// @}

NS_CC_END

#endif // CC_BASE_TOUCH_H
