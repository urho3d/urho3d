//
// Copyright (c) 2008-2013 the Urho3D project.
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

#pragma once

#include "Object.h"

namespace Urho3D
{

/// Mouse click in the UI.
EVENT(E_UIMOUSECLICK, UIMouseClick)
{
    PARAM(P_ELEMENT, Element);              // UIElement pointer
    PARAM(P_X, X);                          // int
    PARAM(P_Y, Y);                          // int
    PARAM(P_BUTTON, Button);                // int
    PARAM(P_BUTTONS, Buttons);              // int
    PARAM(P_QUALIFIERS, Qualifiers);        // int
}

/// Drag and drop test.
EVENT(E_DRAGDROPTEST, DragDropTest)
{
    PARAM(P_SOURCE, Source);                // UIElement pointer
    PARAM(P_TARGET, Target);                // UIElement pointer
    PARAM(P_ACCEPT, Accept);                // bool
};

/// Drag and drop finish.
EVENT(E_DRAGDROPFINISH, DragDropFinish)
{
    PARAM(P_SOURCE, Source);                // UIElement pointer
    PARAM(P_TARGET, Target);                // UIElement pointer
    PARAM(P_ACCEPT, Accept);                // bool
};

/// Focus element changed.
EVENT(E_FOCUSCHANGED, FocusChanged)
{
    PARAM(P_ELEMENT, Element);              // UIElement pointer
    PARAM(P_CLICKEDELEMENT, ClickedElement); // UIElement pointer
}

/// UI element name changed.
EVENT(E_NAMECHANGED, NameChanged)
{
    PARAM(P_ELEMENT, Element);              // UIElement pointer
}

/// UI element resized.
EVENT(E_RESIZED, Resized)
{
    PARAM(P_ELEMENT, Element);              // UIElement pointer
    PARAM(P_WIDTH, Width);                  // int
    PARAM(P_HEIGHT, Height);                // int
}

/// UI element visibility changed.
EVENT(E_VISIBLECHANGED, VisibleChanged)
{
    PARAM(P_ELEMENT, Element);              // UIElement pointer
    PARAM(P_VISIBLE, Visible);              // bool
}

/// UI element focused.
EVENT(E_FOCUSED, Focused)
{
    PARAM(P_ELEMENT, Element);              // UIElement pointer
}

/// UI element defocused.
EVENT(E_DEFOCUSED, Defocused)
{
    PARAM(P_ELEMENT, Element);              // UIElement pointer
}

/// UI element layout updated.
EVENT(E_LAYOUTUPDATED, LayoutUpdated)
{
    PARAM(P_ELEMENT, Element);              // UIElement pointer
}

/// UI button pressed.
EVENT(E_PRESSED, Pressed)
{
    PARAM(P_ELEMENT, Element);              // UIElement pointer
}

/// UI button was pressed, then released.
EVENT(E_RELEASED, Released)
{
    PARAM(P_ELEMENT, Element);              // UIElement pointer
}

/// UI checkbox toggled.
EVENT(E_TOGGLED, Toggled)
{
    PARAM(P_ELEMENT, Element);              // UIElement pointer
    PARAM(P_STATE, State);                  // bool
}

/// UI slider value changed
EVENT(E_SLIDERCHANGED, SliderChanged)
{
    PARAM(P_ELEMENT, Element);              // UIElement pointer
    PARAM(P_VALUE, Value);                  // float
}

/// UI slider being paged.
EVENT(E_SLIDERPAGED, SliderPaged)
{
    PARAM(P_ELEMENT, Element);              // UIElement pointer
    PARAM(P_OFFSET, Offset);                // int
    PARAM(P_BUTTONS, Buttons);              // int
    PARAM(P_QUALIFIERS, Qualifiers);        // int
}

/// UI scrollbar value changed.
EVENT(E_SCROLLBARCHANGED, ScrollBarChanged)
{
    PARAM(P_ELEMENT, Element);              // UIElement pointer
    PARAM(P_VALUE, Value);                  // float
}

/// UI scrollview position changed.
EVENT(E_VIEWCHANGED, ViewChanged)
{
    PARAM(P_ELEMENT, Element);              // UIElement pointer
    PARAM(P_X, X);                          // int
    PARAM(P_Y, Y);                          // int
}

/// Editable text changed
EVENT(E_TEXTCHANGED, TextChanged)
{
    PARAM(P_ELEMENT, Element);              // UIElement pointer
    PARAM(P_TEXT, Text);                    // String
}

/// Text editing finished (enter pressed on a LineEdit)
EVENT(E_TEXTFINISHED, TextFinished)
{
    PARAM(P_ELEMENT, Element);              // UIElement pointer
    PARAM(P_TEXT, Text);                    // String
}

/// Menu selected.
EVENT(E_MENUSELECTED, MenuSelected)
{
    PARAM(P_ELEMENT, Element);              // UIElement pointer
}

/// Listview or DropDownList item selected.
EVENT(E_ITEMSELECTED, ItemSelected)
{
    PARAM(P_ELEMENT, Element);              // UIElement pointer
    PARAM(P_SELECTION, Selection);          // int
}

/// Listview item deselected.
EVENT(E_ITEMDESELECTED, ItemDeselected)
{
    PARAM(P_ELEMENT, Element);              // UIElement pointer
    PARAM(P_SELECTION, Selection);          // int
}

/// Listview selection change finished.
EVENT(E_SELECTIONCHANGED, SelectionChanged)
{
    PARAM(P_ELEMENT, Element);              // UIElement pointer
}

/// Listview item doubleclicked.
EVENT(E_ITEMDOUBLECLICKED, ItemDoubleClicked)
{
    PARAM(P_ELEMENT, Element);              // UIElement pointer
    PARAM(P_SELECTION, Selection);          // int
}

/// LineEdit or ListView unhandled key pressed.
EVENT(E_UNHANDLEDKEY, UnhandledKey)
{
    PARAM(P_ELEMENT, Element);              // UIElement pointer
    PARAM(P_KEY, Key);                      // int
    PARAM(P_BUTTONS, Buttons);              // int
    PARAM(P_QUALIFIERS, Qualifiers);        // int
}

/// Fileselector choice.
EVENT(E_FILESELECTED, FileSelected)
{
    PARAM(P_FILENAME, FileName);            // String
    PARAM(P_OK, Ok);                        // bool
}

/// A child element has been added to an element. Sent by the UI root element.
EVENT(E_ELEMENTADDED, ElementAdded)
{
    PARAM(P_ROOT, Root);                    // UIElement pointer
    PARAM(P_PARENT, Parent);                // UIElement pointer
    PARAM(P_ELEMENT, Element);              // UIElement pointer
}

/// A child element is about to be removed from an element. Sent by the UI root element.
EVENT(E_ELEMENTREMOVED, ElementRemoved)
{
    PARAM(P_ROOT, Root);                    // UIElement pointer
    PARAM(P_PARENT, Parent);                // UIElement pointer
    PARAM(P_ELEMENT, Element);              // UIElement pointer
}

}
