//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../IO/File.h"
#include "../IO/FileSystem.h"
#include "../Input/InputEvents.h"
#include "../UI/DropDownList.h"
#include "../UI/FileSelector.h"
#include "../UI/LineEdit.h"
#include "../UI/ListView.h"
#include "../UI/Text.h"
#include "../UI/UI.h"
#include "../UI/UIEvents.h"
#include "../UI/Window.h"

#include "../DebugNew.h"

namespace Urho3D
{

static bool CompareEntries(const FileSelectorEntry& lhs, const FileSelectorEntry& rhs)
{
    if (lhs.directory_ && !rhs.directory_)
        return true;
    if (!lhs.directory_ && rhs.directory_)
        return false;
    return lhs.name_.Compare(rhs.name_, false) < 0;
}

FileSelector::FileSelector(Context* context) :
    Object(context),
    directoryMode_(false),
    ignoreEvents_(false)
{
    window_ = new Window(context_);
    window_->SetLayout(LM_VERTICAL);

    titleLayout = new UIElement(context_);
    titleLayout->SetLayout(LM_HORIZONTAL);
    window_->AddChild(titleLayout);

    titleText_ = new Text(context_);
    titleLayout->AddChild(titleText_);

    closeButton_ = new Button(context_);
    titleLayout->AddChild(closeButton_);

    pathEdit_ = new LineEdit(context_);
    window_->AddChild(pathEdit_);

    fileList_ = new ListView(context_);
    window_->AddChild(fileList_);

    fileNameLayout_ = new UIElement(context_);
    fileNameLayout_->SetLayout(LM_HORIZONTAL);

    fileNameEdit_ = new LineEdit(context_);
    fileNameLayout_->AddChild(fileNameEdit_);

    filterList_ = new DropDownList(context_);
    fileNameLayout_->AddChild(filterList_);

    window_->AddChild(fileNameLayout_);

    separatorLayout_ = new UIElement(context_);
    window_->AddChild(separatorLayout_);

    buttonLayout_ = new UIElement(context_);
    buttonLayout_->SetLayout(LM_HORIZONTAL);

    buttonLayout_->AddChild(new UIElement(context_)); // Add spacer

    cancelButton_ = new Button(context_);
    cancelButtonText_ = new Text(context_);
    cancelButtonText_->SetAlignment(HA_CENTER, VA_CENTER);
    cancelButton_->AddChild(cancelButtonText_);
    buttonLayout_->AddChild(cancelButton_);

    okButton_ = new Button(context_);
    okButtonText_ = new Text(context_);
    okButtonText_->SetAlignment(HA_CENTER, VA_CENTER);
    okButton_->AddChild(okButtonText_);
    buttonLayout_->AddChild(okButton_);

    window_->AddChild(buttonLayout_);

    Vector<String> defaultFilters;
    defaultFilters.Push("*.*");
    SetFilters(defaultFilters, 0);
    FileSystem* fileSystem = GetSubsystem<FileSystem>();
    SetPath(fileSystem->GetCurrentDir());

    // Focus the fileselector's filelist initially when created, and bring to front
    UI* ui = GetSubsystem<UI>();
    ui->GetRoot()->AddChild(window_);
    ui->SetFocusElement(fileList_);
    window_->SetModal(true);

    SubscribeToEvent(filterList_, E_ITEMSELECTED, URHO3D_HANDLER(FileSelector, HandleFilterChanged));
    SubscribeToEvent(pathEdit_, E_TEXTFINISHED, URHO3D_HANDLER(FileSelector, HandlePathChanged));
    SubscribeToEvent(fileNameEdit_, E_TEXTFINISHED, URHO3D_HANDLER(FileSelector, HandleOKPressed));
    SubscribeToEvent(fileList_, E_ITEMSELECTED, URHO3D_HANDLER(FileSelector, HandleFileSelected));
    SubscribeToEvent(fileList_, E_ITEMDOUBLECLICKED, URHO3D_HANDLER(FileSelector, HandleFileDoubleClicked));
    SubscribeToEvent(fileList_, E_UNHANDLEDKEY, URHO3D_HANDLER(FileSelector, HandleFileListKey));
    SubscribeToEvent(okButton_, E_RELEASED, URHO3D_HANDLER(FileSelector, HandleOKPressed));
    SubscribeToEvent(cancelButton_, E_RELEASED, URHO3D_HANDLER(FileSelector, HandleCancelPressed));
    SubscribeToEvent(closeButton_, E_RELEASED, URHO3D_HANDLER(FileSelector, HandleCancelPressed));
    SubscribeToEvent(window_, E_MODALCHANGED, URHO3D_HANDLER(FileSelector, HandleCancelPressed));
}

FileSelector::~FileSelector()
{
    window_->Remove();
}

void FileSelector::RegisterObject(Context* context)
{
    context->RegisterFactory<FileSelector>();
}

void FileSelector::SetDefaultStyle(XMLFile* style)
{
    if (!style)
        return;

    window_->SetDefaultStyle(style);
    window_->SetStyle("FileSelector");

    titleText_->SetStyle("FileSelectorTitleText");
    closeButton_->SetStyle("CloseButton");

    okButtonText_->SetStyle("FileSelectorButtonText");
    cancelButtonText_->SetStyle("FileSelectorButtonText");

    titleLayout->SetStyle("FileSelectorLayout");
    fileNameLayout_->SetStyle("FileSelectorLayout");
    buttonLayout_->SetStyle("FileSelectorLayout");
    separatorLayout_->SetStyle("EditorSeparator");

    fileList_->SetStyle("FileSelectorListView");
    fileNameEdit_->SetStyle("FileSelectorLineEdit");
    pathEdit_->SetStyle("FileSelectorLineEdit");

    filterList_->SetStyle("FileSelectorFilterList");

    okButton_->SetStyle("FileSelectorButton");
    cancelButton_->SetStyle("FileSelectorButton");

    const Vector<SharedPtr<UIElement> >& filterTexts = filterList_->GetListView()->GetContentElement()->GetChildren();
    for (unsigned i = 0; i < filterTexts.Size(); ++i)
        filterTexts[i]->SetStyle("FileSelectorFilterText");

    const Vector<SharedPtr<UIElement> >& listTexts = fileList_->GetContentElement()->GetChildren();
    for (unsigned i = 0; i < listTexts.Size(); ++i)
        listTexts[i]->SetStyle("FileSelectorListText");

    UpdateElements();
}

void FileSelector::SetTitle(const String& text)
{
    titleText_->SetText(text);
}

void FileSelector::SetButtonTexts(const String& okText, const String& cancelText)
{
    okButtonText_->SetText(okText);
    cancelButtonText_->SetText(cancelText);
}

void FileSelector::SetPath(const String& path)
{
    FileSystem* fileSystem = GetSubsystem<FileSystem>();
    if (fileSystem->DirExists(path))
    {
        path_ = AddTrailingSlash(path);
        SetLineEditText(pathEdit_, path_);
        RefreshFiles();
    }
    else
    {
        // If path was invalid, restore the old path to the line edit
        if (pathEdit_->GetText() != path_)
            SetLineEditText(pathEdit_, path_);
    }
}

void FileSelector::SetFileName(const String& fileName)
{
    SetLineEditText(fileNameEdit_, fileName);
}

void FileSelector::SetFilters(const Vector<String>& filters, unsigned defaultIndex)
{
    if (filters.Empty())
        return;

    ignoreEvents_ = true;

    filters_ = filters;
    filterList_->RemoveAllItems();
    for (unsigned i = 0; i < filters_.Size(); ++i)
    {
        Text* filterText = new Text(context_);
        filterList_->AddItem(filterText);
        filterText->SetText(filters_[i]);
        filterText->SetStyle("FileSelectorFilterText");
    }
    if (defaultIndex > filters.Size())
        defaultIndex = 0;
    filterList_->SetSelection(defaultIndex);

    ignoreEvents_ = false;

    if (GetFilter() != lastUsedFilter_)
        RefreshFiles();
}

void FileSelector::SetDirectoryMode(bool enable)
{
    directoryMode_ = enable;
}

void FileSelector::UpdateElements()
{
    buttonLayout_->SetFixedHeight(Max(okButton_->GetHeight(), cancelButton_->GetHeight()));
}

XMLFile* FileSelector::GetDefaultStyle() const
{
    return window_->GetDefaultStyle(false);
}

const String& FileSelector::GetTitle() const
{
    return titleText_->GetText();
}

const String& FileSelector::GetFileName() const
{
    return fileNameEdit_->GetText();
}

const String& FileSelector::GetFilter() const
{
    Text* selectedFilter = static_cast<Text*>(filterList_->GetSelectedItem());
    if (selectedFilter)
        return selectedFilter->GetText();
    else
        return String::EMPTY;
}

unsigned FileSelector::GetFilterIndex() const
{
    return filterList_->GetSelection();
}

void FileSelector::SetLineEditText(LineEdit* edit, const String& text)
{
    ignoreEvents_ = true;
    edit->SetText(text);
    ignoreEvents_ = false;
}

void FileSelector::RefreshFiles()
{
    FileSystem* fileSystem = GetSubsystem<FileSystem>();

    ignoreEvents_ = true;

    fileList_->RemoveAllItems();
    fileEntries_.Clear();

    Vector<String> directories;
    Vector<String> files;
    fileSystem->ScanDir(directories, path_, "*", SCAN_DIRS, false);
    fileSystem->ScanDir(files, path_, GetFilter(), SCAN_FILES, false);

    fileEntries_.Reserve(directories.Size() + files.Size());

    for (unsigned i = 0; i < directories.Size(); ++i)
    {
        FileSelectorEntry newEntry;
        newEntry.name_ = directories[i];
        newEntry.directory_ = true;
        fileEntries_.Push(newEntry);
    }

    for (unsigned i = 0; i < files.Size(); ++i)
    {
        FileSelectorEntry newEntry;
        newEntry.name_ = files[i];
        newEntry.directory_ = false;
        fileEntries_.Push(newEntry);
    }

    // Sort and add to the list view
    // While items are being added, disable layout update for performance optimization
    Sort(fileEntries_.Begin(), fileEntries_.End(), CompareEntries);
    UIElement* listContent = fileList_->GetContentElement();
    listContent->DisableLayoutUpdate();
    for (unsigned i = 0; i < fileEntries_.Size(); ++i)
    {
        String displayName;
        if (fileEntries_[i].directory_)
            displayName = "<DIR> " + fileEntries_[i].name_;
        else
            displayName = fileEntries_[i].name_;

        Text* entryText = new Text(context_);
        fileList_->AddItem(entryText);
        entryText->SetText(displayName);
        entryText->SetStyle("FileSelectorListText");
    }
    listContent->EnableLayoutUpdate();
    listContent->UpdateLayout();

    ignoreEvents_ = false;

    // Clear filename from the previous dir so that there is no confusion
    SetFileName(String::EMPTY);
    lastUsedFilter_ = GetFilter();
}

bool FileSelector::EnterFile()
{
    unsigned index = fileList_->GetSelection();
    if (index >= fileEntries_.Size())
        return false;

    if (fileEntries_[index].directory_)
    {
        // If a directory double clicked, enter it. Recognize . and .. as a special case
        const String& newPath = fileEntries_[index].name_;
        if ((newPath != ".") && (newPath != ".."))
            SetPath(path_ + newPath);
        else if (newPath == "..")
        {
            String parentPath = GetParentPath(path_);
            SetPath(parentPath);
        }

        return true;
    }
    else
    {
        // Double clicking a file is the same as pressing OK
        if (!directoryMode_)
        {
            using namespace FileSelected;

            VariantMap& eventData = GetEventDataMap();
            eventData[P_FILENAME] = path_ + fileEntries_[index].name_;
            eventData[P_FILTER] = GetFilter();
            eventData[P_OK] = true;
            SendEvent(E_FILESELECTED, eventData);
        }
    }

    return false;
}

void FileSelector::HandleFilterChanged(StringHash eventType, VariantMap& eventData)
{
    if (ignoreEvents_)
        return;

    if (GetFilter() != lastUsedFilter_)
        RefreshFiles();
}

void FileSelector::HandlePathChanged(StringHash eventType, VariantMap& eventData)
{
    if (ignoreEvents_)
        return;

    // Attempt to set path. Restores old if does not exist
    SetPath(pathEdit_->GetText());
}

void FileSelector::HandleFileSelected(StringHash eventType, VariantMap& eventData)
{
    if (ignoreEvents_)
        return;

    unsigned index = fileList_->GetSelection();
    if (index >= fileEntries_.Size())
        return;
    // If a file selected, update the filename edit field
    if (!fileEntries_[index].directory_)
        SetFileName(fileEntries_[index].name_);
}

void FileSelector::HandleFileDoubleClicked(StringHash eventType, VariantMap& eventData)
{
    if (ignoreEvents_)
        return;

    if (eventData[ItemDoubleClicked::P_BUTTON] == MOUSEB_LEFT)
        EnterFile();
}

void FileSelector::HandleFileListKey(StringHash eventType, VariantMap& eventData)
{
    if (ignoreEvents_)
        return;

    using namespace UnhandledKey;

    int key = eventData[P_KEY].GetInt();
    if (key == KEY_RETURN || key == KEY_RETURN2 || key == KEY_KP_ENTER)
    {
        bool entered = EnterFile();
        // When a key is used to enter a directory, select the first file if no selection
        if (entered && !fileList_->GetSelectedItem())
            fileList_->SetSelection(0);
    }
}

void FileSelector::HandleOKPressed(StringHash eventType, VariantMap& eventData)
{
    if (ignoreEvents_)
        return;

    const String& fileName = GetFileName();

    if (!directoryMode_)
    {
        if (!fileName.Empty())
        {
            using namespace FileSelected;

            VariantMap& newEventData = GetEventDataMap();
            newEventData[P_FILENAME] = path_ + GetFileName();
            newEventData[P_FILTER] = GetFilter();
            newEventData[P_OK] = true;
            SendEvent(E_FILESELECTED, newEventData);
        }
    }
    else if (eventType == E_RELEASED && !path_.Empty())
    {
        using namespace FileSelected;

        VariantMap& newEventData = GetEventDataMap();
        newEventData[P_FILENAME] = path_;
        newEventData[P_FILTER] = GetFilter();
        newEventData[P_OK] = true;
        SendEvent(E_FILESELECTED, newEventData);
    }
}

void FileSelector::HandleCancelPressed(StringHash eventType, VariantMap& eventData)
{
    if (ignoreEvents_)
        return;

    if (eventType == E_MODALCHANGED && eventData[ModalChanged::P_MODAL].GetBool())
        return;

    using namespace FileSelected;

    VariantMap& newEventData = GetEventDataMap();
    newEventData[P_FILENAME] = String::EMPTY;
    newEventData[P_FILTER] = GetFilter();
    newEventData[P_OK] = false;
    SendEvent(E_FILESELECTED, newEventData);
}

}
