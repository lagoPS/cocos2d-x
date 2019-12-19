/*
 * Copyright (c) 2012 cocos2d-x.org
 * http://www.cocos2d-x.org
 *
 *
 * Copyright 2012 Stewart Hamilton-Arrandale.
 * http://creativewax.co.uk
 *
 * Modified by Yannick Loriot.
 * http://yannickloriot.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *
 * Converted to c++ / cocos2d-x by Angus C
 */

#pragma once

#include <cocos/base/CCRef.h>
#include <cocos/base/ccTypes.h>
#include <cocos/extensions/ExtensionExport.h>
#include <cocos/extensions/ExtensionMacros.h>
#include <cocos/math/CCGeometry.h>
#include <cocos/math/Vec2.h>

namespace cocos2d
{
    class Node;
    class Sprite;
} // namespace cocos2d

NS_CC_EXT_BEGIN

typedef struct
{
    double r; // percent
    double g; // percent
    double b; // percent
    double a; // percent
} RGBA;

typedef struct
{
    double h; // angle in degrees
    double s; // percent
    double v; // percent
} HSV;

/**
 * @addtogroup GUI
 * @{
 * @addtogroup control_extension
 * @{
 */

// helper class to store Color3B's in mutable arrays
class CC_EX_DLL Color3bObject final : public Ref
{
public:
    Color3B value;

    Color3bObject() = default;
    Color3bObject(Color3B const& s_value);
    Color3bObject(Color3bObject const&) = default;
    Color3bObject& operator=(Color3bObject const&) = default;
    Color3bObject(Color3bObject&&) noexcept = default;
    Color3bObject& operator=(Color3bObject&&) noexcept = default;
    ~Color3bObject() final;
};

class CC_EX_DLL ControlUtils
{
public:
    /**
     * @js NA
     * @lua NA
     */
    static Sprite* addSpriteToTargetWithPosAndAnchor(const char* spriteName, Node* target, Vec2 pos, Vec2 anchor);
    /**
     * @js NA
     * @lua NA
     */
    static HSV HSVfromRGB(RGBA value);
    /**
     * @js NA
     * @lua NA
     */
    static RGBA RGBfromHSV(HSV value);
    /**
     * @js NA
     * @lua NA
     */
    static Rect RectUnion(const Rect& src1, const Rect& src2);
};

// end of GUI group
/// @}
/// @}

NS_CC_EXT_END
