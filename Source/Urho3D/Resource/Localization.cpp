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

#include "../Resource/Localization.h"
#include "../Resource/ResourceCache.h"
#include "../Resource/JSONFile.h"
#include "../IO/Log.h"

#include "../DebugNew.h"

namespace Urho3D
{

Localization::Localization(Context* context) :
    Object(context),
    languageIndex_(-1)
{
}

int Localization::GetLanguageIndex(const String &language)
{
    assert(GetNumLanguages() > 0 && !language.Empty());
    for (int i = 0; i < GetNumLanguages(); i++)
    {
        if (languages_[i] == language)
            return i;
    }
    return -1;
}

String Localization::GetLanguage()
{
    assert(languageIndex_ != -1);
    return languages_[languageIndex_];
}

String Localization::GetLanguage(int index)
{
    assert(index >= 0 && index < GetNumLanguages());
    return languages_[index];
}

void Localization::SetLanguage(int index)
{
    assert(index >= 0 && index < GetNumLanguages());
    if (index != languageIndex_)
    {
        languageIndex_ = index;
        VariantMap& eventData = GetEventDataMap();
        SendEvent(E_CHANGELANGUAGE, eventData);
    }
}

void Localization::SetLanguage(const String &language)
{
    SetLanguage(GetLanguageIndex(language));
}

String Localization::Get(const String &id)
{
    assert(!id.Empty());
    String result = strings_[StringHash(GetLanguage())][StringHash(id)];
    if (result.Empty())
        LOGWARNING("Localization::Get returns empty result: language=" + GetLanguage() + ", id=" + id);
    return result;
}

void Localization::Reset()
{
    languages_.Clear();
    languageIndex_ = -1;
    strings_.Clear();
}

void Localization::LoadJSON(const JSONValue &source)
{
    Vector<String> ids = source.GetChildNames();
    for (unsigned i = 0; i < ids.Size(); i++)
    {
        String id = ids[i];
        JSONValue value = source.GetChild(id);
        Vector<String> langs = value.GetValueNames();
        for (unsigned j = 0; j < langs.Size(); j++)
        {
            String lang = langs[j];
            String string = value.GetString(lang);
            strings_[StringHash(lang)][StringHash(id)] = string;
            if (!languages_.Contains(lang))
                languages_.Push(lang);
            if (languageIndex_ == -1)
                languageIndex_ = 0;
        }
    }
}

void Localization::LoadJSONFile(const String &name)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    JSONFile* jsonFile = cache->GetResource<JSONFile>(name);
    if (jsonFile)
        LoadJSON(jsonFile->GetRoot());
}

}
