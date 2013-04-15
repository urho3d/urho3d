//
// Copyright (c) 2008-2013 the Urho3D project.
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
#include "Camera.h"
#include "Context.h"
#include "Geometry.h"
#include "Material.h"
#include "Node.h"
#include "Technique.h"
#include "Text.h"
#include "Text3D.h"
#include "VertexBuffer.h"

namespace Urho3D
{

static const float TEXT_SCALING = 1.0f / 128.0f;

OBJECTTYPESTATIC(Text3D);

Text3D::Text3D(Context* context) :
    Drawable(context, DRAWABLE_GEOMETRY),
    text_(new Text(context)),
    vertexBuffer_(new VertexBuffer(context_)),
    faceCamera_(false),
    textDirty_(true),
    geometryDirty_(true)
{
}

Text3D::~Text3D()
{
}

void Text3D::RegisterObject(Context* context)
{
    context->RegisterFactory<Text3D>();
}

void Text3D::UpdateBatches(const FrameInfo& frame)
{
    const Matrix3x4& worldTransform = node_->GetWorldTransform();
    distance_ = frame.camera_->GetDistance(GetWorldBoundingBox().Center());
    
    if (faceCamera_)
    {
        customWorldTransform_ = Matrix3x4(node_->GetWorldPosition(), frame.camera_->GetNode()->GetWorldRotation(), node_->GetWorldScale());
        worldBoundingBoxDirty_ = true;
    }
    
    for (unsigned i = 0; i < batches_.Size(); ++i)
    {
        batches_[i].distance_ = distance_;
        batches_[i].worldTransform_ = faceCamera_ ? &customWorldTransform_ : &worldTransform;
    }
}

void Text3D::UpdateGeometry(const FrameInfo& frame)
{
    for (unsigned i = 0; i < batches_.Size(); ++i)
    {
        Geometry* geometry = geometries_[i];
        geometry->SetDrawRange(TRIANGLE_LIST, 0, 0, uiBatches_[i].vertexStart_, uiBatches_[i].vertexEnd_ - uiBatches_[i].vertexStart_);
    }
    
    if (uiVertexData_.Size())
    {
        unsigned vertexCount = uiVertexData_.Size() / UI_VERTEX_SIZE;
        if (vertexBuffer_->GetVertexCount() != vertexCount)
            vertexBuffer_->SetSize(vertexCount, MASK_POSITION | MASK_COLOR | MASK_TEXCOORD1);
        
        vertexBuffer_->SetData(&uiVertexData_[0]);
    }
    
    geometryDirty_ = false;
}

UpdateGeometryType Text3D::GetUpdateGeometryType()
{
    if (geometryDirty_ || vertexBuffer_->IsDataLost())
        return UPDATE_MAIN_THREAD;
    else
        return UPDATE_NONE;
}

bool Text3D::SetFont(const String& fontName, int size)
{
    bool success = text_->SetFont(fontName, size);
    
    // Changing font requires materials to be re-evaluated. Material evaluation can not be done in worker threads,
    // so UI batches must be brought up-to-date immediately
    MarkTextDirty();
    UpdateTextBatches();
    UpdateTextMaterials();
    
    return success;
}

bool Text3D::SetFont(Font* font, int size)
{
    bool success = text_->SetFont(font, size);
    
    MarkTextDirty();
    UpdateTextBatches();
    UpdateTextMaterials();
    
    return success;
}

void Text3D::SetText(const String& text)
{
    text_->SetText(text);
    
    // Changing text requires materials to be re-evaluated, in case the font is multi-page
    MarkTextDirty();
    UpdateTextBatches();
    UpdateTextMaterials();
}

void Text3D::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign)
{
    text_->SetAlignment(hAlign, vAlign);
    
    MarkTextDirty();
}

void Text3D::SetHorizontalAlignment(HorizontalAlignment align)
{
    text_->SetHorizontalAlignment(align);
    
    MarkTextDirty();
}

void Text3D::SetVerticalAlignment(VerticalAlignment align)
{
    text_->SetVerticalAlignment(align);
    
    MarkTextDirty();
}

void Text3D::SetTextAlignment(HorizontalAlignment align)
{
    text_->SetTextAlignment(align);
    
    MarkTextDirty();
}

void Text3D::SetRowSpacing(float spacing)
{
    text_->SetRowSpacing(spacing);
    
    MarkTextDirty();
}

void Text3D::SetWordwrap(bool enable)
{
    text_->SetWordwrap(enable);
    
    MarkTextDirty();
}

void Text3D::SetMaxWidth(int width)
{
    text_->SetMaxWidth(width);
    
    MarkTextDirty();
}

void Text3D::SetColor(const Color& color)
{
    text_->SetColor(color);
    
    MarkTextDirty();
}

void Text3D::SetColor(Corner corner, const Color& color)
{
    text_->SetColor(corner, color);
    
    MarkTextDirty();
}

void Text3D::SetOpacity(float opacity)
{
    text_->SetOpacity(opacity);
    
    MarkTextDirty();
}

void Text3D::SetFaceCamera(bool enable)
{
    faceCamera_ = enable;
}

Font* Text3D::GetFont() const
{
    return text_->GetFont();
}

int Text3D::GetFontSize() const
{
    return text_->GetFontSize();
}

const String& Text3D::GetText() const
{
    return text_->GetText();
}

HorizontalAlignment Text3D::GetHorizontalAlignment() const
{
    return text_->GetHorizontalAlignment();
}

VerticalAlignment Text3D::GetVerticalAlignment() const
{
    return text_->GetVerticalAlignment();
}

HorizontalAlignment Text3D::GetTextAlignment() const
{
    return text_->GetTextAlignment();
}

float Text3D::GetRowSpacing() const
{
    return text_->GetRowSpacing();
}

bool Text3D::GetWordwrap() const
{
    return text_->GetWordwrap();
}

int Text3D::GetMaxWidth() const
{
    return text_->GetMaxWidth();
}

int Text3D::GetRowHeight() const
{
    return text_->GetRowHeight();
}

unsigned Text3D::GetNumRows() const
{
    return text_->GetNumRows();
}

const PODVector<int>& Text3D::GetRowWidths() const
{
    return text_->GetRowWidths();
}

const Color& Text3D::GetColor(Corner corner) const
{
    return text_->GetColor(corner);
}

float Text3D::GetOpacity() const
{
    return text_->GetOpacity();
}

void Text3D::OnNodeSet(Node* node)
{
    Drawable::OnNodeSet(node);
    
    if (node)
        customWorldTransform_ = node->GetWorldTransform();
}

void Text3D::OnWorldBoundingBoxUpdate()
{
    if (textDirty_)
        UpdateTextBatches();
    
    worldBoundingBox_ = faceCamera_ ? boundingBox_.Transformed(customWorldTransform_) :
        boundingBox_.Transformed(node_->GetWorldTransform());
}

void Text3D::MarkTextDirty()
{
    textDirty_ = true;
    
    OnMarkedDirty(node_);
    MarkNetworkUpdate();
}

void Text3D::UpdateTextBatches()
{
    uiBatches_.Clear();
    uiVertexData_.Clear();
    
    text_->GetBatches(uiBatches_, uiVertexData_, IntRect::ZERO);
    
    Vector3 offset(Vector3::ZERO);
    
    switch (text_->GetHorizontalAlignment())
    {
    case HA_LEFT:
        break;
        
    case HA_CENTER:
        offset.x_ -= (float)text_->GetWidth() * 0.5f;
        break;
        
    case HA_RIGHT:
        offset.x_ -= (float)text_->GetWidth();
        break;
    }
    
    switch (text_->GetVerticalAlignment())
    {
    case VA_TOP:
        break;
        
    case VA_CENTER:
        offset.y_ -= (float)text_->GetHeight() * 0.5f;
        break;
        
    case VA_BOTTOM:
        offset.y_ -= (float)text_->GetHeight();
        break;
    }
    
    boundingBox_.defined_ = false;
    boundingBox_.min_ = boundingBox_.max_ = Vector3::ZERO;
    
    for (unsigned i = 0; i < uiVertexData_.Size(); i += UI_VERTEX_SIZE)
    {
        Vector3& position = *(reinterpret_cast<Vector3*>(&uiVertexData_[i]));
        position += offset;
        position *= TEXT_SCALING;
        position.y_ = -position.y_;
        boundingBox_.Merge(position);
    }
    
    textDirty_ = false;
    geometryDirty_ = true;
}

void Text3D::UpdateTextMaterials()
{
    batches_.Resize(uiBatches_.Size());
    geometries_.Resize(uiBatches_.Size());
    
    for (unsigned i = 0; i < batches_.Size(); ++i)
    {
        if (!geometries_[i])
        {
            Geometry* geometry = new Geometry(context_);
            geometry->SetVertexBuffer(0, vertexBuffer_, MASK_POSITION | MASK_COLOR | MASK_TEXCOORD1);
            batches_[i].geometry_ = geometries_[i] = geometry;
        }
        
        if (!batches_[i].material_)
        {
            Material* material = new Material(context_);
            Technique* tech = new Technique(context_);
            Pass* pass = tech->CreatePass(PASS_ALPHA);
            pass->SetVertexShader("Basic_DiffVCol");
            pass->SetPixelShader("Basic_AlphaVCol");
            material->SetTechnique(0, tech);
            material->SetCullMode(CULL_NONE);
            batches_[i].material_ = material;
        }
        
        Material* material = batches_[i].material_;
        material->SetTexture(TU_DIFFUSE, uiBatches_[i].texture_);
        Pass* pass = material->GetTechnique(0)->GetPass(PASS_ALPHA);
        pass->SetBlendMode(uiBatches_[i].blendMode_);
    }
}


}
