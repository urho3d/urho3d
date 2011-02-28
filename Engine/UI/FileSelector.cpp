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
#include "DropDownList.h"
#include "Exception.h"
#include "File.h"
#include "FileSelector.h"
#include "InputEvents.h"
#include "LineEdit.h"
#include "ListView.h"
#include "ProcessUtils.h"
#include "Text.h"
#include "UI.h"
#include "UIEvents.h"
#include "Window.h"

#include <algorithm>

#include "DebugNew.h"

static bool compareEntries(const FileSelectorEntry& lhs, const FileSelectorEntry& rhs)
{
    if ((lhs.mDirectory) && (!rhs.mDirectory))
        return true;
    if ((!lhs.mDirectory) && (rhs.mDirectory))
        return false;
    return lhs.mName < rhs.mName;
}

FileSelector::FileSelector(UI* ui) :
    mUI(ui),
    mIgnoreEvents(false)
{
    if (!mUI)
        EXCEPTION("Null UI for FileSelector");
    
    mWindow = new Window();
    mWindow->setLayout(LM_VERTICAL);
    
    mTitleText = new Text();
    mWindow->addChild(mTitleText);
    
    mPathEdit = new LineEdit();
    mWindow->addChild(mPathEdit);
    
    mFileList = new ListView();
    mWindow->addChild(mFileList);
    
    mFileNameLayout = new UIElement();
    mFileNameLayout->setLayout(LM_HORIZONTAL);
    
    mFileNameEdit = new LineEdit();
    mFileNameLayout->addChild(mFileNameEdit);
    
    mFilterList = new DropDownList();
    mFileNameLayout->addChild(mFilterList);
    
    mWindow->addChild(mFileNameLayout);
    
    mButtonLayout = new UIElement();
    mButtonLayout->setLayout(LM_HORIZONTAL);
    
    mButtonLayout->addChild(new UIElement()); // Add spacer
    
    mOKButton = new Button();
    mOKButtonText = new Text();
    mOKButtonText->setAlignment(HA_CENTER, VA_CENTER);
    mOKButton->addChild(mOKButtonText);
    mButtonLayout->addChild(mOKButton);
    
    mButtonLayout->addChild(new UIElement()); // Add spacer
    
    mCancelButton = new Button();
    mCancelButtonText = new Text();
    mCancelButtonText->setAlignment(HA_CENTER, VA_CENTER);
    mCancelButton->addChild(mCancelButtonText);
    mButtonLayout->addChild(mCancelButton);
    
    mButtonLayout->addChild(new UIElement()); // Add spacer
    
    mWindow->addChild(mButtonLayout);
    
    mUI->getRootElement()->addChild(mWindow);
    mWindow->bringToFront();
    
    std::vector<std::string> defaultFilters;
    defaultFilters.push_back("*.*");
    setFilters(defaultFilters, 0);
    setPath(getCurrentDirectory());
    
    subscribeToEvent(mFilterList, EVENT_ITEMSELECTED, EVENT_HANDLER(FileSelector, handleFilterChanged));
    subscribeToEvent(mPathEdit, EVENT_TEXTFINISHED, EVENT_HANDLER(FileSelector, handlePathChanged));
    subscribeToEvent(mFileList, EVENT_ITEMSELECTED, EVENT_HANDLER(FileSelector, handleFileSelected));
    subscribeToEvent(mFileList, EVENT_ITEMDOUBLECLICKED, EVENT_HANDLER(FileSelector, handleFileDoubleClicked));
    subscribeToEvent(mFileList, EVENT_LISTVIEWKEY, EVENT_HANDLER(FileSelector, handleFileListKey));
    subscribeToEvent(mOKButton, EVENT_PRESSED, EVENT_HANDLER(FileSelector, handleOKPressed));
    subscribeToEvent(mCancelButton, EVENT_PRESSED, EVENT_HANDLER(FileSelector, handleCancelPressed));
}

FileSelector::~FileSelector()
{
    mUI->getRootElement()->removeChild(mWindow);
}

void FileSelector::setStyle(XMLFile* style)
{
    if (!style)
        return;
    
    mStyle = style;
    ResourceCache* cache = mUI->getResourceCache();
    
    mWindow->setStyleAuto(style, cache);
    XMLElement windowElem = UIElement::getStyleElement(style, "FileSelector");
    if (windowElem)
        mWindow->setStyle(windowElem, cache);
    
    XMLElement titleElem = UIElement::getStyleElement(style, "FileSelectorTitleText");
    if (titleElem)
        mTitleText->setStyle(titleElem, cache);
    
    XMLElement textElem = UIElement::getStyleElement(style, "FileSelectorButtonText");
    if (textElem)
    {
        mOKButtonText->setStyle(textElem, cache);
        mCancelButtonText->setStyle(textElem, cache);
    }
    
    XMLElement layoutElem = UIElement::getStyleElement(style, "FileSelectorLayout");
    if (layoutElem)
    {
        mFileNameLayout->setStyle(layoutElem, cache);
        mButtonLayout->setStyle(layoutElem, cache);
    }
    
    mFileList->setStyleAuto(style, cache);
    mFileNameEdit->setStyleAuto(style, cache);
    mPathEdit->setStyleAuto(style, cache);
    
    mFilterList->setStyleAuto(style, cache);
    XMLElement dropDownElem = UIElement::getStyleElement(style, "FileSelectorFilterList");
    if (dropDownElem)
        mFilterList->setStyle(dropDownElem, cache);
    
    mOKButton->setStyleAuto(style, cache);
    mCancelButton->setStyleAuto(style, cache);
    XMLElement buttonElem = UIElement::getStyleElement(style, "FileSelectorButton");
    if (buttonElem)
    {
        mOKButton->setStyle(buttonElem, cache);
        mCancelButton->setStyle(buttonElem, cache);
    }
    
    textElem = UIElement::getStyleElement(style, "FileSelectorFilterText");
    if (textElem)
    {
        std::vector<UIElement*> listTexts = mFilterList->getListView()->getContentElement()->getChildren();
        for (unsigned i = 0; i < listTexts.size(); ++i)
            listTexts[i]->setStyle(textElem, cache);
    }
    
    textElem = UIElement::getStyleElement(style, "FileSelectorListText");
    if (textElem)
    {
        std::vector<UIElement*> listTexts = mFileList->getContentElement()->getChildren();
        for (unsigned i = 0; i < listTexts.size(); ++i)
            listTexts[i]->setStyle(textElem, cache);
    }
    
    updateElements();
}

void FileSelector::setTitle(const std::string& text)
{
    mTitleText->setText(text);
}

void FileSelector::setButtonTexts(const std::string& okText, const std::string& cancelText)
{
    mOKButtonText->setText(okText);
    mCancelButtonText->setText(cancelText);
}

void FileSelector::setPath(const std::string& path)
{
    if (directoryExists(path))
    {
        mPath = fixPath(path);
        mIgnoreEvents = true;
        mPathEdit->setText(mPath);
        mIgnoreEvents = false;
        refreshFiles();
    }
    else
    {
        // If path was invalid, restore the old path to the line edit
        if (mPathEdit->getText() != mPath)
        {
            mIgnoreEvents = true;
            mPathEdit->setText(mPath);
            mIgnoreEvents = false;
        }
    }
}

void FileSelector::setFileName(const std::string& fileName)
{
    mIgnoreEvents = true;
    mFileNameEdit->setText(fileName);
    mIgnoreEvents = false;
}

void FileSelector::setFilters(const std::vector<std::string>& filters, unsigned defaultIndex)
{
    if (filters.empty())
        return;
    
    mIgnoreEvents = true;
    mFilters = filters;
    mFilterList->removeAllItems();
    for (unsigned i = 0; i < mFilters.size(); ++i)
    {
        Text* filterText = new Text();
        filterText->setText(mFilters[i]);
        XMLElement textElem = UIElement::getStyleElement(mStyle, "FileSelectorFilterText");
        if (textElem)
            filterText->setStyle(textElem, mUI->getResourceCache());
        mFilterList->addItem(filterText);
    }
    mFilterList->setSelection(defaultIndex);
    mIgnoreEvents = false;
    if (getFilter() != mLastUsedFilter)
        refreshFiles();
}

void FileSelector::updateElements()
{
    {
        const IntRect& clipBorder = mPathEdit->getClipBorder();
        mPathEdit->setFixedHeight(mPathEdit->getTextElement()->getRowHeight() + clipBorder.mTop + clipBorder.mBottom);
    }
    
    {
        const IntRect& clipBorder = mFileNameEdit->getClipBorder();
        int fileNameHeight = mFileNameEdit->getTextElement()->getRowHeight() + clipBorder.mTop + clipBorder.mBottom;
        mFileNameEdit->setFixedHeight(fileNameHeight);
        mFilterList->setFixedHeight(fileNameHeight);
        mFileNameLayout->setFixedHeight(fileNameHeight);
    }
    
    mButtonLayout->setFixedHeight(max(mOKButton->getHeight(), mCancelButton->getHeight()));
}

const std::string& FileSelector::getFileName() const
{
    return mFileNameEdit->getText();
}

const std::string& FileSelector::getFilter() const
{
    static std::string emptyFilter;
    
    Text* selectedFilter = static_cast<Text*>(mFilterList->getSelectedItem());
    if (selectedFilter)
        return selectedFilter->getText();
    
    return emptyFilter;
}

void FileSelector::refreshFiles()
{
    mIgnoreEvents = true;
    
    mFileList->removeAllItems();
    mFileEntries.clear();

    std::vector<std::string> directories;
    std::vector<std::string> files;
    scanDirectory(directories, mPath, "*.*", SCAN_DIRECTORIES, false);
    scanDirectory(files, mPath, getFilter(), SCAN_FILES, false);
    
    for (unsigned i = 0; i < directories.size(); ++i)
    {
        FileSelectorEntry newEntry;
        newEntry.mName = directories[i];
        newEntry.mDirectory = true;
        mFileEntries.push_back(newEntry);
    }
    
    for (unsigned i = 0; i < files.size(); ++i)
    {
        FileSelectorEntry newEntry;
        newEntry.mName = files[i];
        newEntry.mDirectory = false;
        mFileEntries.push_back(newEntry);
    }
    
    // Sort and add to the list view
    // While items are being added, disable layout update for performance optimization
    std::sort(mFileEntries.begin(), mFileEntries.end(), compareEntries);
    UIElement* listContent = mFileList->getContentElement();
    listContent->disableLayoutUpdate();
    for (unsigned i = 0; i < mFileEntries.size(); ++i)
    {
        std::string displayName;
        if (mFileEntries[i].mDirectory)
            displayName = "<DIR> " + mFileEntries[i].mName;
        else
            displayName = mFileEntries[i].mName;
        
        Text* entryText = new Text();
        entryText->setText(displayName);
        XMLElement textElem = UIElement::getStyleElement(mStyle, "FileSelectorListText");
        if (textElem)
            entryText->setStyle(textElem, mUI->getResourceCache());
        mFileList->addItem(entryText);
    }
    listContent->enableLayoutUpdate();
    listContent->updateLayout();
    
    mIgnoreEvents = false;
    
    // Clear filename from the previous dir so that there is no confusion
    setFileName(std::string());
    mLastUsedFilter = getFilter();
}

bool FileSelector::enterFile()
{
    unsigned index = mFileList->getSelection();
    if (index >= mFileEntries.size())
        return false;
    
    if (mFileEntries[index].mDirectory)
    {
        // If a directory doubleclicked, enter it. Recognize . and .. as a special case
        const std::string& newPath = mFileEntries[index].mName;
        if ((newPath != ".") &&  (newPath != ".."))
            setPath(mPath + newPath);
        else if (newPath == "..")
        {
            unsigned pos = unfixPath(mPath).rfind('/');
            if (pos != std::string::npos)
                setPath(mPath.substr(0, pos));
        }
    }
    else
    {
        // Doubleclicking a file is the same as pressing OK
        using namespace FileSelected;
        
        VariantMap eventData;
        eventData[P_FILENAME] = mPath + mFileEntries[index].mName;
        eventData[P_OK] = true;
        sendEvent(EVENT_FILESELECTED, eventData);
    }
    
    return true;
}

void FileSelector::handleFilterChanged(StringHash eventType, VariantMap& eventData)
{
    if (mIgnoreEvents)
        return;
    
    if (getFilter() != mLastUsedFilter)
        refreshFiles();
}

void FileSelector::handlePathChanged(StringHash eventType, VariantMap& eventData)
{
    if (mIgnoreEvents)
        return;
    
    // Attempt to set path. Restores old if does not exist
    setPath(mPathEdit->getText());
}

void FileSelector::handleFileSelected(StringHash eventType, VariantMap& eventData)
{
    if (mIgnoreEvents)
        return;
    
    unsigned index = mFileList->getSelection();
    if (index >= mFileEntries.size())
        return;
    // If a file selected, update the filename edit field
    if (!mFileEntries[index].mDirectory)
        setFileName(mFileEntries[index].mName);
}

void FileSelector::handleFileDoubleClicked(StringHash eventType, VariantMap& eventData)
{
    if (mIgnoreEvents)
        return;
    
    enterFile();
}

void FileSelector::handleFileListKey(StringHash eventType, VariantMap& eventData)
{
    if (mIgnoreEvents)
        return;
    
    using namespace ListViewKey;
    
    if (eventData[P_KEY].getInt() == KEY_RETURN)
    {
        bool entered = enterFile();
        // When a key is used to enter a directory, select the first file if no selection
        if ((entered) && (!mFileList->getSelectedItem()))
            mFileList->setSelection(0);
    }
}

void FileSelector::handleOKPressed(StringHash eventType, VariantMap& eventData)
{
    if (mIgnoreEvents)
        return;
    
    const std::string& fileName = getFileName();
    if (!fileName.empty())
    {
        using namespace FileSelected;
        
        VariantMap newEventData;
        newEventData[P_FILENAME] = mPath + getFileName();
        newEventData[P_OK] = true;
        sendEvent(EVENT_FILESELECTED, newEventData);
    }
}

void FileSelector::handleCancelPressed(StringHash eventType, VariantMap& eventData)
{
    if (mIgnoreEvents)
        return;
    
    using namespace FileSelected;
    
    VariantMap newEventData;
    newEventData[P_FILENAME] = std::string();
    newEventData[P_OK] = false;
    sendEvent(EVENT_FILESELECTED, newEventData);
}
