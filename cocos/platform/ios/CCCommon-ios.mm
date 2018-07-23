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

#include <cocos/platform/CCPlatformConfig.h>
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#include <cocos/platform/CCCommon.h>

#include <cocos/platform/CCPlatformMacros.h>

#include <Foundation/NSString.h>
#include <UIKit/UIAlertView.h>

#include <cstdio>

NS_CC_BEGIN

// ios no MessageBox, use log instead
void MessageBox(const char* msg, const char* title)
{
    // only enable it on iOS.
    // FIXME: Implement it for tvOS
#    if !defined(CC_TARGET_OS_TVOS)
    NSString* tmpTitle = (title) ? [NSString stringWithUTF8String:title] : nil;
    NSString* tmpMsg = (msg) ? [NSString stringWithUTF8String:msg] : nil;
    UIAlertView* messageBox = [[UIAlertView alloc] initWithTitle:tmpTitle message:tmpMsg delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
    [messageBox autorelease];
    [messageBox show];
#    endif
}

void LuaLog(const char* format)
{
    puts(format);
}

NS_CC_END

#endif // CC_PLATFORM_IOS
