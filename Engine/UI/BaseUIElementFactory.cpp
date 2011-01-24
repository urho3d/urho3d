//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "Precompiled.h"
#include "BaseUIElementFactory.h"
#include "Button.h"
#include "CheckBox.h"
#include "Cursor.h"
#include "LineEdit.h"
#include "MenuItem.h"
#include "ScrollView.h"
#include "Slider.h"
#include "Text.h"
#include "Window.h"

UIElement* BaseUIElementFactory::createElement(ShortStringHash type, const std::string& name)
{
    if (type == BorderImage::getTypeStatic())
        return new BorderImage(name);
    if (type == Button::getTypeStatic())
        return new Button(name);
    if (type == CheckBox::getTypeStatic())
        return new CheckBox(name);
    if (type == Cursor::getTypeStatic())
        return new Cursor(name);
    if (type == LineEdit::getTypeStatic())
        return new LineEdit(std::string(), name);
    if (type == MenuItem::getTypeStatic())
        return new MenuItem(name);
    if (type == ScrollView::getTypeStatic())
        return new ScrollView(name);
    if (type == Slider::getTypeStatic())
        return new Slider(name);
    if (type == Text::getTypeStatic())
        return new Text(std::string(), name);
    if (type == UIElement::getTypeStatic())
        return new UIElement(name);
    if (type == Window::getTypeStatic())
        return new Window(name);
    
    return 0;
}
