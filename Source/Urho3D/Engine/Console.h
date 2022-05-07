// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Core/Object.h"

namespace Urho3D
{

class Button;
class BorderImage;
class DropDownList;
class Engine;
class Font;
class LineEdit;
class ListView;
class Text;
class UIElement;
class XMLFile;

/// %Console window with log history and command line prompt.
class URHO3D_API Console : public Object
{
    URHO3D_OBJECT(Console, Object);

public:
    /// Construct.
    explicit Console(Context* context);
    /// Destruct.
    ~Console() override;

    /// Set UI elements' style from an XML file.
    /// @property
    void SetDefaultStyle(XMLFile* style);
    /// Show or hide.
    /// @property
    void SetVisible(bool enable);
    /// Toggle visibility.
    void Toggle();

    /// Automatically set console to visible when receiving an error log message.
    /// @property
    void SetAutoVisibleOnError(bool enable) { autoVisibleOnError_ = enable; }

    /// Set the command interpreter.
    /// @property
    void SetCommandInterpreter(const String& interpreter) { commandInterpreter_ = interpreter; }

    /// Set number of buffered rows.
    /// @property
    void SetNumBufferedRows(unsigned rows);
    /// Set number of displayed rows.
    /// @property
    void SetNumRows(unsigned rows);
    /// Set command history maximum size, 0 disables history.
    /// @property
    void SetNumHistoryRows(unsigned rows);
    /// Set whether to automatically focus the line edit when showing. Default true on desktops and false on mobile devices, as on mobiles it would pop up the screen keyboard.
    /// @property
    void SetFocusOnShow(bool enable);
    /// Add auto complete option.
    void AddAutoComplete(const String& option);
    /// Remove auto complete option.
    void RemoveAutoComplete(const String& option);
    /// Update elements to layout properly. Call this after manually adjusting the sub-elements.
    void UpdateElements();

    /// Return the UI style file.
    /// @property
    XMLFile* GetDefaultStyle() const;

    /// Return the background element.
    /// @property
    BorderImage* GetBackground() const { return background_; }

    /// Return the line edit element.
    /// @property
    LineEdit* GetLineEdit() const { return lineEdit_; }

    /// Return the close butoon element.
    /// @property
    Button* GetCloseButton() const { return closeButton_; }

    /// Return whether is visible.
    /// @property
    bool IsVisible() const;

    /// Return true when console is set to automatically visible when receiving an error log message.
    /// @property
    bool IsAutoVisibleOnError() const { return autoVisibleOnError_; }

    /// Return the last used command interpreter.
    /// @property
    const String& GetCommandInterpreter() const { return commandInterpreter_; }

    /// Return number of buffered rows.
    /// @property
    unsigned GetNumBufferedRows() const;

    /// Return number of displayed rows.
    /// @property
    unsigned GetNumRows() const { return displayedRows_; }

    /// Copy selected rows to system clipboard.
    void CopySelectedRows() const;

    /// Return history maximum size.
    /// @property
    unsigned GetNumHistoryRows() const { return historyRows_; }

    /// Return current history position.
    /// @property
    unsigned GetHistoryPosition() const { return historyPosition_; }

    /// Return history row at index.
    /// @property
    const String& GetHistoryRow(unsigned index) const;

    /// Return whether automatically focuses the line edit when showing.
    /// @property
    bool GetFocusOnShow() const { return focusOnShow_; }

private:
    /// Populate the command line interpreters that could handle the console command.
    bool PopulateInterpreter();
    /// Handle interpreter being selected on the drop down list.
    void HandleInterpreterSelected(StringHash eventType, VariantMap& eventData);
    /// Handle text change in the line edit.
    void HandleTextChanged(StringHash eventType, VariantMap& eventData);
    /// Handle enter pressed on the line edit.
    void HandleTextFinished(StringHash eventType, VariantMap& eventData);
    /// Handle unhandled key on the line edit for scrolling the history.
    void HandleLineEditKey(StringHash eventType, VariantMap& eventData);
    /// Handle close button being pressed.
    void HandleCloseButtonPressed(StringHash eventType, VariantMap& eventData);
    /// Handle UI root resize.
    void HandleRootElementResized(StringHash eventType, VariantMap& eventData);
    /// Handle a log message.
    void HandleLogMessage(StringHash eventType, VariantMap& eventData);
    /// Handle the application post-update.
    void HandlePostUpdate(StringHash eventType, VariantMap& eventData);

    /// Auto visible on error flag.
    bool autoVisibleOnError_;
    /// Background.
    SharedPtr<BorderImage> background_;
    /// Container for text rows.
    ListView* rowContainer_;
    /// Container for the command line.
    UIElement* commandLine_;
    /// Interpreter drop down list.
    DropDownList* interpreters_;
    /// Line edit.
    LineEdit* lineEdit_;
    /// Close button.
    SharedPtr<Button> closeButton_;
    /// Last used command interpreter.
    String commandInterpreter_;

    /// Command history.
    Vector<String> history_;
    /// Pending log message rows.
    Vector<Pair<int, String> > pendingRows_;
    /// Current row being edited.
    String currentRow_;
    /// Maximum displayed rows.
    unsigned displayedRows_{};
    /// Command history maximum rows.
    unsigned historyRows_;
    /// Command history current position.
    unsigned historyPosition_;

    /**
    Command auto complete options.

    down arrow key
    Unless currently going through history options, will loop through next auto complete options.

    up arrow key
    Unless currently going through history options, will go through previous auto complete options.
    When no previous options are left will start going through history options.
    */
    Vector<String> autoComplete_;
    /// Command auto complete current position.
    unsigned autoCompletePosition_;
    /// Store the original line which is being auto-completed.
    String autoCompleteLine_;

    /// Flag when printing messages to prevent endless loop.
    bool printing_;
    /// Flag for automatically focusing the line edit on showing the console.
    bool focusOnShow_;
    /// Internal flag whether currently in an autocomplete or history change.
    bool historyOrAutoCompleteChange_;
};

}
