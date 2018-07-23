
#include "2d/CCClippingRectangleNode.h"

#include <cocos/base/CCDirector.h>
#include <cocos/math/Vec2.h>
#include <cocos/platform/CCGLView.h>
#include <cocos/renderer/CCRenderer.h>

NS_CC_BEGIN

ClippingRectangleNode* ClippingRectangleNode::create(const Rect& clippingRegion)
{
    ClippingRectangleNode* node = new (std::nothrow) ClippingRectangleNode();
    if (node && node->init())
    {
        node->setClippingRegion(clippingRegion);
        node->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(node);
    }

    return node;
}

ClippingRectangleNode* ClippingRectangleNode::create()
{
    ClippingRectangleNode* node = new (std::nothrow) ClippingRectangleNode();
    if (node && node->init())
    {
        node->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(node);
    }

    return node;
}

void ClippingRectangleNode::setClippingRegion(const Rect& clippingRegion)
{
    _clippingRegion = clippingRegion;
}

void ClippingRectangleNode::onBeforeVisitScissor()
{
    if (_clippingEnabled)
    {
        glEnable(GL_SCISSOR_TEST);

        float scaleX = _scaleX;
        float scaleY = _scaleY;
        Node* parent = this->getParent();
        while (parent)
        {
            scaleX *= parent->getScaleX();
            scaleY *= parent->getScaleY();
            parent = parent->getParent();
        }

        const Point pos = convertToWorldSpace(Point(_clippingRegion.origin.x, _clippingRegion.origin.y));
        GLView* glView = Director::getInstance()->getOpenGLView();
        glView->setScissorInPoints(pos.x, pos.y, _clippingRegion.size.width * scaleX, _clippingRegion.size.height * scaleY);
    }
}

void ClippingRectangleNode::onAfterVisitScissor()
{
    if (_clippingEnabled)
    {
        glDisable(GL_SCISSOR_TEST);
    }
}

void ClippingRectangleNode::visit(Renderer* renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
    _beforeVisitCmdScissor.init(_globalZOrder);
    _beforeVisitCmdScissor.setFunc([this]() { onBeforeVisitScissor(); });
    renderer->addCommand(&_beforeVisitCmdScissor);

    Node::visit(renderer, parentTransform, parentFlags);

    _afterVisitCmdScissor.init(_globalZOrder);
    _afterVisitCmdScissor.setFunc([this]() { onAfterVisitScissor(); });
    renderer->addCommand(&_afterVisitCmdScissor);
}

NS_CC_END
