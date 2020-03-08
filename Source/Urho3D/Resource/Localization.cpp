//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Resource/Localization.h"
#include "../Resource/ResourceCache.h"
#include "../Resource/JSONFile.h"
#include "../Resource/ResourceEvents.h"
#include "../IO/Log.h"

#include "../DebugNew.h"

namespace Urho3D
{

Localization::Localization(Context* context) :
    Object(context),
    languageIndex_(-1)
{
}

Localization::~Localization() = default;

int Localization::GetLanguageIndex(const String& language)
{
    if (language.Empty())
    {
        URHO3D_LOGWARNING("Localization::GetLanguageIndex(language): language name is empty");
        return -1;
    }
    if (GetNumLanguages() == 0)
    {
        URHO3D_LOGWARNING("Localization::GetLanguageIndex(language): no loaded languages");
        return -1;
    }
    for (int i = 0; i < GetNumLanguages(); i++)
    {
        if (languages_[i] == language)
            return i;
    }
    return -1;
}

String Localization::GetLanguage()
{
    if (languageIndex_ == -1)
    {
        URHO3D_LOGWARNING("Localization::GetLanguage(): no loaded languages");
        return String::EMPTY;
    }
    return languages_[languageIndex_];
}

String Localization::GetLanguage(int index)
{
    if (GetNumLanguages() == 0)
    {
        URHO3D_LOGWARNING("Localization::GetLanguage(index): no loaded languages");
        return String::EMPTY;
    }
    if (index < 0 || index >= GetNumLanguages())
    {
        URHO3D_LOGWARNING("Localization::GetLanguage(index): index out of range");
        return String::EMPTY;
    }
    return languages_[index];
}

void Localization::SetLanguage(int index)
{
    if (GetNumLanguages() == 0)
    {
        URHO3D_LOGWARNING("Localization::SetLanguage(index): no loaded languages");
        return;
    }
    if (index < 0 || index >= GetNumLanguages())
    {
        URHO3D_LOGWARNING("Localization::SetLanguage(index): index out of range");
        return;
    }
    if (index != languageIndex_)
    {
        languageIndex_ = index;
        VariantMap& eventData = GetEventDataMap();
        SendEvent(E_CHANGELANGUAGE, eventData);
    }
}

void Localization::SetLanguage(const String& language)
{
    if (language.Empty())
    {
        URHO3D_LOGWARNING("Localization::SetLanguage(language): language name is empty");
        return;
    }
    if (GetNumLanguages() == 0)
    {
        URHO3D_LOGWARNING("Localization::SetLanguage(language): no loaded languages");
        return;
    }
    int index = GetLanguageIndex(language);
    if (index == -1)
    {
        URHO3D_LOGWARNING("Localization::SetLanguage(language): language not found");
        return;
    }
    SetLanguage(index);
}

String Localization::Get(const String& id)
{
    if (id.Empty())
        return String::EMPTY;
    if (GetNumLanguages() == 0)
    {
        URHO3D_LOGWARNING("Localization::Get(id): no loaded languages");
        return id;
    }
    String result = strings_[StringHash(GetLanguage())][StringHash(id)];
    if (result.Empty())
    {
        URHO3D_LOGWARNING("Localization::Get(\"" + id + "\") not found translation, language=\"" + GetLanguage() + "\"");
        return id;
    }
    return result;
}

void Localization::Reset()
{
    languages_.Clear();
    languageIndex_ = -1;
    strings_.Clear();
}

void Localization::LoadJSONFile(const String& name, const String language)
{
    auto* cache = GetSubsystem<ResourceCache>();
    auto* jsonFile = cache->GetResource<JSONFile>(name);
    if (jsonFile)
    {
        if (language.Empty())
            LoadMultipleLanguageJSON(jsonFile->GetRoot());
        else
            LoadSingleLanguageJSON(jsonFile->GetRoot(), language);
    }
}


void Localization::LoadMultipleLanguageJSON(const JSONValue& source)
{
    for (JSONObject::ConstIterator i = source.Begin(); i != source.End(); ++i)
    {
        String id = i->first_;
        if (id.Empty())
        {
            URHO3D_LOGWARNING("Localization::LoadMultipleLanguageJSON(source): string ID is empty");
            continue;
        }
        const JSONValue& value = i->second_;
        if (value.IsObject())
        {
            for (JSONObject::ConstIterator j = value.Begin(); j != value.End(); ++j)
            {
                const String &lang = j->first_;
                if (lang.Empty())
                {
                    URHO3D_LOGWARNING(
                            "Localization::LoadMultipleLanguageJSON(source): language name is empty, string ID=\"" + id + "\"");
                    continue;
                }
                const String &string = j->second_.GetString();
                if (string.Empty())
                {
                    URHO3D_LOGWARNING(
                            "Localization::LoadMultipleLanguageJSON(source): translation is empty, string ID=\"" + id +
                            "\", language=\"" + lang + "\"");
                    continue;
                }
                if (strings_[StringHash(lang)][StringHash(id)] != String::EMPTY)
                {
                    URHO3D_LOGWARNING(
                            "Localization::LoadMultipleLanguageJSON(source): override translation, string ID=\"" + id +
                            "\", language=\"" + lang + "\"");
                }
                strings_[StringHash(lang)][StringHash(id)] = string;
                if (!languages_.Contains(lang))
                    languages_.Push(lang);
                if (languageIndex_ == -1)
                    languageIndex_ = 0;
            }
        }
        else
            URHO3D_LOGWARNING("Localization::LoadMultipleLanguageJSON(source): failed to load values, string ID=\"" + id + "\"");
    }
}

void Localization::LoadSingleLanguageJSON(const JSONValue& source, const String& language)
{
    for (JSONObject::ConstIterator i = source.Begin(); i != source.End(); ++i)
    {
        String id = i->first_;
        if (id.Empty())
        {
            URHO3D_LOGWARNING("Localization::LoadSingleLanguageJSON(source, language): string ID is empty");
            continue;
        }
        const JSONValue& value = i->second_;
        if (value.IsString())
        {
            if (value.GetString().Empty())
            {
                URHO3D_LOGWARNING(
                        "Localization::LoadSingleLanguageJSON(source, language): translation is empty, string ID=\"" + id +
                        "\", language=\"" + language + "\"");
                continue;
            }
            if (strings_[StringHash(language)][StringHash(id)] != String::EMPTY)
            {
                URHO3D_LOGWARNING(
                        "Localization::LoadSingleLanguageJSON(source, language): override translation, string ID=\"" + id +
                        "\", language=\"" + language + "\"");
            }
            strings_[StringHash(language)][StringHash(id)] = value.GetString();
            if (!languages_.Contains(language))
                languages_.Push(language);
        }
        else
            URHO3D_LOGWARNING(
                    "Localization::LoadSingleLanguageJSON(source, language): failed to load value, string ID=\"" + id +
                    "\", language=\"" + language + "\"");
    }
}

}
