// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Core/Context.h"
#include "../Resource/JSONValue.h"

namespace Urho3D
{

/// %Localization subsystem. Stores all the strings in all languages.
class URHO3D_API Localization : public Object
{
    URHO3D_OBJECT(Localization, Object);

public:
    /// Construct.
    explicit Localization(Context* context);
    /// Destruct. Free all resources.
    ~Localization() override;

    /// Return the number of languages.
    /// @property
    int GetNumLanguages() const { return (int)languages_.Size(); }

    /// Return the index number of current language. The index is determined by the order of loading.
    /// @property
    int GetLanguageIndex() const { return languageIndex_; }

    /// Return the index number of language. The index is determined by the order of loading.
    int GetLanguageIndex(const String& language);
    /// Return the name of current language.
    /// @property
    String GetLanguage();
    /// Return the name of language.
    String GetLanguage(int index);
    /// Set current language.
    void SetLanguage(int index);
    /// Set current language.
    void SetLanguage(const String& language);
    /// Return a string in the current language. Returns String::EMPTY if id is empty. Returns id if translation is not found and logs a warning.
    String Get(const String& id);
    /// Clear all loaded strings.
    void Reset();
    /// Load strings from JSONFile. The file should be UTF8 without BOM.
    void LoadJSONFile(const String& name, const String& language = String::EMPTY);
    /// Load strings from JSONValue.
    void LoadMultipleLanguageJSON(const JSONValue& source);
    /// Load strings from JSONValue for specific language.
    void LoadSingleLanguageJSON(const JSONValue& source, const String& language = String::EMPTY);

private:
    /// Language names.
    Vector<String> languages_;
    /// Index of current language.
    int languageIndex_;
    /// Storage strings: <Language <StringId, Value> >.
    HashMap<StringHash, HashMap<StringHash, String> > strings_;
};

}
