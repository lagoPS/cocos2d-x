/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 James Chen

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

#ifndef CC_UI_EDITBOX_EDITBOXIMPL_H
#define CC_UI_EDITBOX_EDITBOXIMPL_H

#include <cocos/ui/UIEditBox/UIEditBox.h>

namespace cocos2d
{
    namespace ui
    {
        class CC_GUI_DLL EditBoxImpl
        {
        public:
            /**
             * @js NA
             */
            EditBoxImpl(EditBox* pEditBox)
            : _delegate(nullptr)
            , _editBox(pEditBox)
            {
            }
            /**
             * @js NA
             * @lua NA
             */
            virtual ~EditBoxImpl();

            virtual bool initWithSize(const Size& size) = 0;
            virtual void setFont(const char* pFontName, int fontSize) = 0;
            virtual void setFontColor(const Color4B& color) = 0;
            virtual void setPlaceholderFont(const char* pFontName, int fontSize) = 0;
            virtual void setPlaceholderFontColor(const Color4B& color) = 0;
            virtual void setInputMode(EditBox::InputMode inputMode) = 0;
            virtual void setInputFlag(EditBox::InputFlag inputFlag) = 0;
            virtual void setMaxLength(int maxLength) = 0;
            virtual int getMaxLength() = 0;
            virtual void setReturnType(EditBox::KeyboardReturnType returnType) = 0;
            virtual bool isEditing() = 0;

            virtual void setText(const char* pText) = 0;
            virtual const char* getText(void) = 0;
            virtual void setPlaceHolder(const char* pText) = 0;
            virtual void doAnimationWhenKeyboardMove(float duration, float distance) = 0;

            virtual void openKeyboard() = 0;
            virtual void closeKeyboard() = 0;

            virtual void setPosition(const Vec2& pos) = 0;
            virtual void setVisible(bool visible) = 0;
            virtual void setContentSize(const Size& size) = 0;
            virtual void setAnchorPoint(const Vec2& anchorPoint) = 0;

            /**
             * check the editbox's position, update it when needed
             */
            virtual void updatePosition(std::chrono::milliseconds dt) {}
            /**
             * @js NA
             * @lua NA
             */
            virtual void draw(cocos2d::Renderer* renderer, cocos2d::Mat4 const& transform, uint32_t flags) = 0;
            /**
             * @js NA
             * @lua NA
             */
            virtual void onEnter(void) = 0;

            void setDelegate(EditBoxDelegate* pDelegate) { _delegate = pDelegate; }
            EditBoxDelegate* getDelegate() { return _delegate; }
            EditBox* getEditBox() { return _editBox; }

        protected:
            EditBoxDelegate* _delegate;
            EditBox* _editBox;
        };

        // This method must be implemented at each subclass of EditBoxImpl.
        extern EditBoxImpl* __createSystemEditBox(EditBox* pEditBox);

    } // namespace ui
} // namespace cocos2d

#endif // CC_UI_EDITBOX_EDITBOXIMPL_H
