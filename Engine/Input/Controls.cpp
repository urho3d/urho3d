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

#include "Controls.h"
#include "Deserializer.h"
#include "Serializer.h"
#include "XMLElement.h"

void Controls::write(Serializer& dest) const
{
    dest.writeUInt(mButtons);
    dest.writeFloat(mYaw);
    dest.writeFloat(mPitch);
    dest.writeVariantMap(mExtraData);
}

void Controls::read(Deserializer& source)
{
    mButtons = source.readUInt();
    mYaw = source.readFloat();
    mPitch = source.readFloat();
    mExtraData = source.readVariantMap();
}

void Controls::writeXML(XMLElement& dest) const
{
    dest.setInt("buttons", mButtons);
    dest.setFloat("yaw", mYaw);
    dest.setFloat("pitch", mPitch);
    dest.setVariantMap(mExtraData);
}

void Controls::readXML(const XMLElement& source)
{
    mButtons = source.getInt("buttons");
    mYaw = source.getFloat("yaw");
    mPitch = source.getFloat("pitch");
    mExtraData = source.getVariantMap();
}

