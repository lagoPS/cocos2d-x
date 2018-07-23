/****************************************************************************
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

#include <cocos/renderer/CCPrimitiveCommand.h>

#include <cocos/base/CCDirector.h>
#include <cocos/base/ccMacros.h>
#include <cocos/renderer/CCGLProgramState.h>
#include <cocos/renderer/CCPrimitive.h>
#include <cocos/renderer/CCRenderer.h>
#include <cocos/renderer/ccGLStateCache.h>

NS_CC_BEGIN

PrimitiveCommand::PrimitiveCommand()
: RenderCommand(RenderCommand::Type::PRIMITIVE_COMMAND)
{
}

PrimitiveCommand::~PrimitiveCommand()
{
}

void PrimitiveCommand::init(float globalOrder, GLuint textureID, GLProgramState* glProgramState, BlendFunc blendType, Primitive* primitive, const Mat4& mv,
                            uint32_t flags)
{
    CCASSERT(glProgramState, "Invalid GLProgramState");
    CCASSERT(glProgramState->getVertexAttribsFlags() == 0, "No custom attributes are supported in PrimitiveCommand");
    CCASSERT(primitive != nullptr, "Could not render null primitive");

    RenderCommand::init(globalOrder, mv, flags);

    _primitive = primitive;

    _mv = mv;

    if (_textureID != textureID || _blendType.src != blendType.src || _blendType.dst != blendType.dst || _glProgramState != glProgramState)
    {
        _textureID = textureID;
        _blendType = blendType;
        _glProgramState = glProgramState;
    }
}

void PrimitiveCommand::init(float globalOrder, GLuint textureID, GLProgramState* glProgramState, BlendFunc blendType, Primitive* primitive, const Mat4& mv)
{
    init(globalOrder, textureID, glProgramState, blendType, primitive, mv, 0);
}

void PrimitiveCommand::execute() const
{
    // Set texture
    GL::bindTexture2D(_textureID);

    // set blend mode
    GL::blendFunc(_blendType.src, _blendType.dst);

    _glProgramState->apply(_mv);

    _primitive->draw();
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _primitive->getCount());
}

NS_CC_END
