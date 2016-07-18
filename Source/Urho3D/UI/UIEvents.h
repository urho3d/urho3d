//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../Core/Object.h"

namespace Urho3D
{

/// Global mouse click in the UI. Sent by the UI subsystem.
URHO3D_EVENT(E_UIMOUSECLICK, UIMouseClick)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_X, X);                          // int
    URHO3D_PARAM(P_Y, Y);                          // int
    URHO3D_PARAM(P_BUTTON, Button);                // int
    URHO3D_PARAM(P_BUTTONS, Buttons);              // int
    URHO3D_PARAM(P_QUALIFIERS, Qualifiers);        // int
}

/// Global mouse click end in the UI. Sent by the UI subsystem.
URHO3D_EVENT(E_UIMOUSECLICKEND, UIMouseClickEnd)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_BEGINELEMENT, BeginElement);    // UIElement pointer
    URHO3D_PARAM(P_X, X);                          // int
    URHO3D_PARAM(P_Y, Y);                          // int
    URHO3D_PARAM(P_BUTTON, Button);                // int
    URHO3D_PARAM(P_BUTTONS, Buttons);              // int
    URHO3D_PARAM(P_QUALIFIERS, Qualifiers);        // int
}

/// Global mouse double click in the UI. Sent by the UI subsystem.
URHO3D_EVENT(E_UIMOUSEDOUBLECLICK, UIMouseDoubleClick)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_X, X);                          // int
    URHO3D_PARAM(P_Y, Y);                          // int
    URHO3D_PARAM(P_BUTTON, Button);                // int
    URHO3D_PARAM(P_BUTTONS, Buttons);              // int
    URHO3D_PARAM(P_QUALIFIERS, Qualifiers);        // int
}

/// Mouse click on a UI element. Parameters are same as in UIMouseClick event, but is sent by the element.
URHO3D_EVENT(E_CLICK, Click)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_X, X);                          // int
    URHO3D_PARAM(P_Y, Y);                          // int
    URHO3D_PARAM(P_BUTTON, Button);                // int
    URHO3D_PARAM(P_BUTTONS, Buttons);              // int
    URHO3D_PARAM(P_QUALIFIERS, Qualifiers);        // int
}

/// Mouse click end on a UI element. Parameters are same as in UIMouseClickEnd event, but is sent by the element.
URHO3D_EVENT(E_CLICKEND, ClickEnd)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_BEGINELEMENT, BeginElement);    // UIElement pointer
    URHO3D_PARAM(P_X, X);                          // int
    URHO3D_PARAM(P_Y, Y);                          // int
    URHO3D_PARAM(P_BUTTON, Button);                // int
    URHO3D_PARAM(P_BUTTONS, Buttons);              // int
    URHO3D_PARAM(P_QUALIFIERS, Qualifiers);        // int
}

/// Mouse double click on a UI element. Parameters are same as in UIMouseDoubleClick event, but is sent by the element.
URHO3D_EVENT(E_DOUBLECLICK, DoubleClick)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_X, X);                          // int
    URHO3D_PARAM(P_Y, Y);                          // int
    URHO3D_PARAM(P_BUTTON, Button);                // int
    URHO3D_PARAM(P_BUTTONS, Buttons);              // int
    URHO3D_PARAM(P_QUALIFIERS, Qualifiers);        // int
}

/// Drag and drop test.
URHO3D_EVENT(E_DRAGDROPTEST, DragDropTest)
{
    URHO3D_PARAM(P_SOURCE, Source);                // UIElement pointer
    URHO3D_PARAM(P_TARGET, Target);                // UIElement pointer
    URHO3D_PARAM(P_ACCEPT, Accept);                // bool
};

/// Drag and drop finish.
URHO3D_EVENT(E_DRAGDROPFINISH, DragDropFinish)
{
    URHO3D_PARAM(P_SOURCE, Source);                // UIElement pointer
    URHO3D_PARAM(P_TARGET, Target);                // UIElement pointer
    URHO3D_PARAM(P_ACCEPT, Accept);                // bool
};

/// Focus element changed.
URHO3D_EVENT(E_FOCUSCHANGED, FocusChanged)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_CLICKEDELEMENT, ClickedElement); // UIElement pointer
}

/// UI element name changed.
URHO3D_EVENT(E_NAMECHANGED, NameChanged)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
}

/// UI element resized.
URHO3D_EVENT(E_RESIZED, Resized)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_WIDTH, Width);                  // int
    URHO3D_PARAM(P_HEIGHT, Height);                // int
}

/// UI element positioned.
URHO3D_EVENT(E_POSITIONED, Positioned)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_X, X);                          // int
    URHO3D_PARAM(P_Y, Y);                          // int
}

/// UI element visibility changed.
URHO3D_EVENT(E_VISIBLECHANGED, VisibleChanged)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_VISIBLE, Visible);              // bool
}

/// UI element focused.
URHO3D_EVENT(E_FOCUSED, Focused)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_BYKEY, ByKey);                  // bool
}

/// UI element defocused.
URHO3D_EVENT(E_DEFOCUSED, Defocused)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
}

/// UI element layout updated.
URHO3D_EVENT(E_LAYOUTUPDATED, LayoutUpdated)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
}

/// UI button pressed.
URHO3D_EVENT(E_PRESSED, Pressed)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
}

/// UI button was pressed, then released.
URHO3D_EVENT(E_RELEASED, Released)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
}

/// UI checkbox toggled.
URHO3D_EVENT(E_TOGGLED, Toggled)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_STATE, State);                  // bool
}

/// UI slider value changed
URHO3D_EVENT(E_SLIDERCHANGED, SliderChanged)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_VALUE, Value);                  // float
}

/// UI slider being paged.
URHO3D_EVENT(E_SLIDERPAGED, SliderPaged)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_OFFSET, Offset);                // int
    URHO3D_PARAM(P_PRESSED, Pressed);              // bool
}

/// UI scrollbar value changed.
URHO3D_EVENT(E_SCROLLBARCHANGED, ScrollBarChanged)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_VALUE, Value);                  // float
}

/// UI scrollview position changed.
URHO3D_EVENT(E_VIEWCHANGED, ViewChanged)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_X, X);                          // int
    URHO3D_PARAM(P_Y, Y);                          // int
}

/// UI modal changed (currently only Window has modal flag).
URHO3D_EVENT(E_MODALCHANGED, ModalChanged)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_MODAL, Modal);                  // bool
}

/// Text entry into a LineEdit. The char can be modified in the event data.
URHO3D_EVENT(E_TEXTENTRY, CharEntry)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_TEXT, Text);                    // String
    URHO3D_PARAM(P_BUTTONS, Buttons);              // int
    URHO3D_PARAM(P_QUALIFIERS, Qualifiers);        // int
}

/// Editable text changed
URHO3D_EVENT(E_TEXTCHANGED, TextChanged)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_TEXT, Text);                    // String
}

/// Text editing finished (enter pressed on a LineEdit)
URHO3D_EVENT(E_TEXTFINISHED, TextFinished)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_TEXT, Text);                    // String
    URHO3D_PARAM(P_VALUE, Value);                 // Float
}

/// Menu selected.
URHO3D_EVENT(E_MENUSELECTED, MenuSelected)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
}

/// Listview or DropDownList item selected.
URHO3D_EVENT(E_ITEMSELECTED, ItemSelected)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_SELECTION, Selection);          // int
}

/// Listview item deselected.
URHO3D_EVENT(E_ITEMDESELECTED, ItemDeselected)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_SELECTION, Selection);          // int
}

/// Listview selection change finished.
URHO3D_EVENT(E_SELECTIONCHANGED, SelectionChanged)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
}

/// Listview item clicked. If this is a left-click, also ItemSelected event will be sent. If this is a right-click, only this event is sent.
URHO3D_EVENT(E_ITEMCLICKED, ItemClicked)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_ITEM, Item);                    // UIElement pointer
    URHO3D_PARAM(P_SELECTION, Selection);          // int
    URHO3D_PARAM(P_BUTTON, Button);                // int
    URHO3D_PARAM(P_BUTTONS, Buttons);              // int
    URHO3D_PARAM(P_QUALIFIERS, Qualifiers);        // int
}

/// Listview item double clicked.
URHO3D_EVENT(E_ITEMDOUBLECLICKED, ItemDoubleClicked)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_ITEM, Item);                    // UIElement pointer
    URHO3D_PARAM(P_SELECTION, Selection);          // int
    URHO3D_PARAM(P_BUTTON, Button);                // int
    URHO3D_PARAM(P_BUTTONS, Buttons);              // int
    URHO3D_PARAM(P_QUALIFIERS, Qualifiers);        // int
}

/// LineEdit or ListView unhandled key pressed.
URHO3D_EVENT(E_UNHANDLEDKEY, UnhandledKey)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_KEY, Key);                      // int
    URHO3D_PARAM(P_BUTTONS, Buttons);              // int
    URHO3D_PARAM(P_QUALIFIERS, Qualifiers);        // int
}

/// Fileselector choice.
URHO3D_EVENT(E_FILESELECTED, FileSelected)
{
    URHO3D_PARAM(P_FILENAME, FileName);            // String
    URHO3D_PARAM(P_FILTER, Filter);                // String
    URHO3D_PARAM(P_OK, Ok);                        // bool
}

/// MessageBox acknowlegement.
URHO3D_EVENT(E_MESSAGEACK, MessageACK)
{
    URHO3D_PARAM(P_OK, Ok);                        // bool
}

/// A child element has been added to an element. Sent by the UI root element, or element-event-sender if set.
URHO3D_EVENT(E_ELEMENTADDED, ElementAdded)
{
    URHO3D_PARAM(P_ROOT, Root);                    // UIElement pointer
    URHO3D_PARAM(P_PARENT, Parent);                // UIElement pointer
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
}

/// A child element is about to be removed from an element. Sent by the UI root element, or element-event-sender if set.
URHO3D_EVENT(E_ELEMENTREMOVED, ElementRemoved)
{
    URHO3D_PARAM(P_ROOT, Root);                    // UIElement pointer
    URHO3D_PARAM(P_PARENT, Parent);                // UIElement pointer
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
}

/// Hovering on an UI element has started
URHO3D_EVENT(E_HOVERBEGIN, HoverBegin)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_X, X);                          // int
    URHO3D_PARAM(P_Y, Y);                          // int
    URHO3D_PARAM(P_ELEMENTX, ElementX);            // int
    URHO3D_PARAM(P_ELEMENTY, ElementY);            // int
}

/// Hovering on an UI element has ended
URHO3D_EVENT(E_HOVEREND, HoverEnd)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
}

/// Drag behavior of a UI Element has started
URHO3D_EVENT(E_DRAGBEGIN, DragBegin)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_X, X);                          // int
    URHO3D_PARAM(P_Y, Y);                          // int
    URHO3D_PARAM(P_ELEMENTX, ElementX);            // int
    URHO3D_PARAM(P_ELEMENTY, ElementY);            // int
    URHO3D_PARAM(P_BUTTONS, Buttons);              // int
    URHO3D_PARAM(P_NUMBUTTONS, NumButtons);        // int
}

/// Drag behavior of a UI Element when the input device has moved
URHO3D_EVENT(E_DRAGMOVE, DragMove)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_X, X);                          // int
    URHO3D_PARAM(P_Y, Y);                          // int
    URHO3D_PARAM(P_DX, DX);                        // int
    URHO3D_PARAM(P_DY, DY);                        // int
    URHO3D_PARAM(P_ELEMENTX, ElementX);            // int
    URHO3D_PARAM(P_ELEMENTY, ElementY);            // int
    URHO3D_PARAM(P_BUTTONS, Buttons);              // int
    URHO3D_PARAM(P_NUMBUTTONS, NumButtons);        // int
}

/// Drag behavior of a UI Element has finished
URHO3D_EVENT(E_DRAGEND, DragEnd)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_X, X);                          // int
    URHO3D_PARAM(P_Y, Y);                          // int
    URHO3D_PARAM(P_ELEMENTX, ElementX);            // int
    URHO3D_PARAM(P_ELEMENTY, ElementY);            // int
    URHO3D_PARAM(P_BUTTONS, Buttons);              // int
    URHO3D_PARAM(P_NUMBUTTONS, NumButtons);        // int
}

/// Drag of a UI Element was canceled by pressing ESC
URHO3D_EVENT(E_DRAGCANCEL, DragCancel)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_X, X);                          // int
    URHO3D_PARAM(P_Y, Y);                          // int
    URHO3D_PARAM(P_ELEMENTX, ElementX);            // int
    URHO3D_PARAM(P_ELEMENTY, ElementY);            // int
    URHO3D_PARAM(P_BUTTONS, Buttons);              // int
    URHO3D_PARAM(P_NUMBUTTONS, NumButtons);        // int
}

/// A file was drag-dropped into the application window. Includes also coordinates and UI element if applicable
URHO3D_EVENT(E_UIDROPFILE, UIDropFile)
{
    URHO3D_PARAM(P_FILENAME, FileName);            // String
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_X, X);                          // int
    URHO3D_PARAM(P_Y, Y);                          // int
    URHO3D_PARAM(P_ELEMENTX, ElementX);            // int (only if element is non-null)
    URHO3D_PARAM(P_ELEMENTY, ElementY);            // int (only if element is non-null)
}

}
