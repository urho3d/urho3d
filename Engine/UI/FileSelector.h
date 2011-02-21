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

#include "EventListener.h"
#include "SharedPtr.h"

class Button;
class DropDownList;
class Font;
class LineEdit;
class ListView;
class ResourceCache;
class Text;
class UI;
class UIElement;
class Window;
class XMLFile;

//! File selector entry
struct FileSelectorEntry
{
    //! Name
    std::string mName;
    //! Directory flag
    bool mDirectory;
};

//! File selector dialog
class FileSelector : public RefCounted, public EventListener
{
public:
    //! Construct
    FileSelector(UI* ui);
    //! Destruct
    virtual ~FileSelector();
    
    //! Set fileselector UI style
    void setStyle(XMLFile* style);
    //! Set title text
    void setTitle(const std::string& text);
    //! Set button texts
    void setButtonTexts(const std::string& okText, const std::string& cancelText);
    //! Set current path
    void setPath(const std::string& path);
    //! Set current filename
    void setFileName(const std::string& fileName);
    //! Set filters
    void setFilters(const std::vector<std::string>& filters, unsigned defaultIndex);
    //! Update elements to layout properly. Call this after manually adjusting the sub-elements
    void updateElements();
    
    //! Return the UI style file
    XMLFile* getStyle() const { return mStyle; }
    //! Return fileselector window
    Window* getWindow() const { return mWindow; }
    //! Return window title text
    Text* getTitleText() const { return mTitleText; }
    //! Return file list
    ListView* getFileList() const { return mFileList; }
    //! Return path editor
    LineEdit* getPathEdit() const { return mPathEdit; }
    //! Return filename editor
    LineEdit* getFileNameEdit() const { return mFileNameEdit; }
    //! Return filter dropdown
    DropDownList* getFilterList() const { return mFilterList; }
    //! Return OK button
    Button* getOKButton() const { return mOKButton; }
    //! Return cancel button
    Button* getCancelButton() const { return mCancelButton; }
    //! Return current path
    const std::string& getPath() const { return mPath; }
    //! Return current filename
    const std::string& getFileName() const;
    //! Return current filter
    const std::string& getFilter() const;
    
private:
    //! Refresh the directory listing
    void refreshFiles();
    //! Handle filter changed
    void handleFilterChanged(StringHash eventType, VariantMap& eventData);
    //! Handle path edited
    void handlePathChanged(StringHash eventType, VariantMap& eventData);
    //! Handle file selected from the list
    void handleFileSelected(StringHash eventType, VariantMap& eventData);
    //! Handle file doubleclicked from the list (enter directory / OK the file selection)
    void handleFileDoubleClicked(StringHash eventType, VariantMap& eventData);
    //! Handle OK button pressed
    void handleOKPressed(StringHash eventType, VariantMap& eventData);
    //! Handle cancel button pressed
    void handleCancelPressed(StringHash eventType, VariantMap& eventData);
    
    //! UI subsystem
    SharedPtr<UI> mUI;
    //! UI style file
    SharedPtr<XMLFile> mStyle;
    //! Fileselector window
    SharedPtr<Window> mWindow;
    //! Window title text
    SharedPtr<Text> mTitleText;
    //! File list
    SharedPtr<ListView> mFileList;
    //! Path editor
    SharedPtr<LineEdit> mPathEdit;
    //! Filename editor
    SharedPtr<LineEdit> mFileNameEdit;
    //! Filter dropdown
    SharedPtr<DropDownList> mFilterList;
    //! OK button
    SharedPtr<Button> mOKButton;
    //! OK button text
    SharedPtr<Text> mOKButtonText;
    //! Cancel button
    SharedPtr<Button> mCancelButton;
    //! Cancel button text
    SharedPtr<Text> mCancelButtonText;
    //! Filename and filter layout
    SharedPtr<UIElement> mFileNameLayout;
    //! Button layout
    SharedPtr<UIElement> mButtonLayout;
    //! Current path
    std::string mPath;
    //! Filters
    std::vector<std::string> mFilters;
    //! File entries
    std::vector<FileSelectorEntry> mFileEntries;
    //! Filter used to get the file list
    std::string mLastUsedFilter;
    //! Ignore event flag (used when changing the edit fields programmatically)
    bool mIgnoreEvents;
};
