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

#pragma once

#include "Object.h"

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

/// File selector's list entry (file or directory)
struct FileSelectorEntry
{
    /// Name
    String name_;
    /// Directory flag
    bool directory_;
};

/// File selector dialog
class FileSelector : public Object
{
    OBJECT(FileSelector);
    
public:
    /// Construct
    FileSelector(Context* context);
    /// Destruct
    virtual ~FileSelector();
    /// Register object factory
    static void RegisterObject(Context* context);
    
    /// Set fileselector UI style
    void SetStyle(XMLFile* style);
    /// Set title text
    void SetTitle(const String& text);
    /// Set button texts
    void SetButtonTexts(const String& okText, const String& cancelText);
    /// Set current path
    void SetPath(const String& path);
    /// Set current filename
    void SetFileName(const String& fileName);
    /// Set filters
    void SetFilters(const std::vector<String>& filters, unsigned defaultIndex);
    /// Set directory selection mode. Default false
    void SetDirectoryMode(bool enable);
    /// Update elements to layout properly. Call this after manually adjusting the sub-elements
    void UpdateElements();
    
    /// Return the UI style file
    XMLFile* GetStyle() const { return style_; }
    /// Return fileselector window
    Window* GetWindow() const { return window_; }
    /// Return window title text
    Text* GetTitleText() const { return titleText_; }
    /// Return file list
    ListView* GetFileList() const { return fileList_; }
    /// Return path editor
    LineEdit* GetPathEdit() const { return pathEdit_; }
    /// Return filename editor
    LineEdit* GetFileNameEdit() const { return fileNameEdit_; }
    /// Return filter dropdown
    DropDownList* GetFilterList() const { return filterList_; }
    /// Return OK button
    Button* GetOKButton() const { return okButton_; }
    /// Return cancel button
    Button* GetCancelButton() const { return cancelButton_; }
    /// Return close button
    Button* GetCloseButton() const { return closeButton_; }
    /// Return current path
    const String& GetPath() const { return path_; }
    /// Return current filename
    const String& GetFileName() const;
    /// Return current filter
    const String& GetFilter() const;
    /// Return current filter index
    unsigned GetFilterIndex() const;
    /// Return directory mode flag
    bool GetDirectoryMode() const { return directoryMode_; }
    
private:
    /// Set the text of an edit field and ignore the resulting event
    void SetLineEditText(LineEdit* edit, const String& text);
    /// Refresh the directory listing
    void RefreshFiles();
    /// Enter a directory or confirm a file. Return true if a directory entered
    bool EnterFile();
    /// Handle filter changed
    void HandleFilterChanged(StringHash eventType, VariantMap& eventData);
    /// Handle path edited
    void HandlePathChanged(StringHash eventType, VariantMap& eventData);
    /// Handle file selected from the list
    void HandleFileSelected(StringHash eventType, VariantMap& eventData);
    /// Handle file doubleclicked from the list (enter directory / OK the file selection)
    void HandleFileDoubleClicked(StringHash eventType, VariantMap& eventData);
    /// Handle file list key pressed
    void HandleFileListKey(StringHash eventType, VariantMap& eventData);
    /// Handle OK button pressed
    void HandleOKPressed(StringHash eventType, VariantMap& eventData);
    /// Handle cancel button pressed
    void HandleCancelPressed(StringHash eventType, VariantMap& eventData);
    
    /// UI subsystem
    SharedPtr<UI> ui_;
    /// UI style file
    SharedPtr<XMLFile> style_;
    /// Fileselector window
    SharedPtr<Window> window_;
    /// Title layout
    SharedPtr<UIElement> titleLayout;
    /// Window title text
    SharedPtr<Text> titleText_;
    /// File list
    SharedPtr<ListView> fileList_;
    /// Path editor
    SharedPtr<LineEdit> pathEdit_;
    /// Filename editor
    SharedPtr<LineEdit> fileNameEdit_;
    /// Filter dropdown
    SharedPtr<DropDownList> filterList_;
    /// OK button
    SharedPtr<Button> okButton_;
    /// OK button text
    SharedPtr<Text> okButtonText_;
    /// Cancel button
    SharedPtr<Button> cancelButton_;
    /// Cancel button text
    SharedPtr<Text> cancelButtonText_;
    /// Close button
    SharedPtr<Button> closeButton_;
    /// Filename and filter layout
    SharedPtr<UIElement> fileNameLayout_;
    /// Button layout
    SharedPtr<UIElement> buttonLayout_;
    /// Current path
    String path_;
    /// Filters
    std::vector<String> filters_;
    /// File entries
    std::vector<FileSelectorEntry> fileEntries_;
    /// Filter used to get the file list
    String lastUsedFilter_;
    /// Directory mode flag
    bool directoryMode_;
    /// Ignore events flag, used when changing line edits manually
    bool ignoreEvents_;
};
