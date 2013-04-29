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
#include "Context.h"
#include "DrawableEvents.h"
#include "Geometry.h"
#include "Image.h"
#include "IndexBuffer.h"
#include "Log.h"
#include "Material.h"
#include "Node.h"
#include "Octree.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "ResourceEvents.h"
#include "Scene.h"
#include "StringUtils.h"
#include "Terrain.h"
#include "TerrainPatch.h"
#include "VertexBuffer.h"

#include "DebugNew.h"

namespace Urho3D
{

extern const char* ENVIRONMENT_CATEGORY;

OBJECTTYPESTATIC(Terrain);

static const Vector3 DEFAULT_SPACING(1.0f, 0.25f, 1.0f);
static const unsigned MAX_LOD_LEVELS = 4;
static const int DEFAULT_PATCH_SIZE = 32;
static const int MIN_PATCH_SIZE = 4;
static const int MAX_PATCH_SIZE = 128;
static const unsigned STITCH_NORTH = 1;
static const unsigned STITCH_SOUTH = 2;
static const unsigned STITCH_WEST = 4;
static const unsigned STITCH_EAST = 8;

Terrain::Terrain(Context* context) :
    Component(context),
    indexBuffer_(new IndexBuffer(context)),
    spacing_(DEFAULT_SPACING),
    patchWorldOrigin_(Vector2::ZERO),
    patchWorldSize_(Vector2::ZERO),
    numVertices_(IntVector2::ZERO),
    numPatches_(IntVector2::ZERO),
    patchSize_(DEFAULT_PATCH_SIZE),
    numLodLevels_(1),
    visible_(true),
    castShadows_(false),
    occluder_(false),
    occludee_(true),
    viewMask_(DEFAULT_VIEWMASK),
    lightMask_(DEFAULT_LIGHTMASK),
    shadowMask_(DEFAULT_SHADOWMASK),
    zoneMask_(DEFAULT_ZONEMASK),
    drawDistance_(0.0f),
    shadowDistance_(0.0f),
    lodBias_(1.0f),
    maxLights_(0),
    recreateTerrain_(false)
{
    indexBuffer_->SetShadowed(true);
}

Terrain::~Terrain()
{
}

void Terrain::RegisterObject(Context* context)
{
    context->RegisterFactory<Terrain>(ENVIRONMENT_CATEGORY);

    ACCESSOR_ATTRIBUTE(Terrain, VAR_BOOL, "Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Terrain, VAR_RESOURCEREF, "Height Map", GetHeightMapAttr, SetHeightMapAttr, ResourceRef, ResourceRef(Image::GetTypeStatic()), AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Terrain, VAR_RESOURCEREF, "Material", GetMaterialAttr, SetMaterialAttr, ResourceRef, ResourceRef(Material::GetTypeStatic()), AM_DEFAULT);
    ATTRIBUTE(Terrain, VAR_VECTOR3, "Vertex Spacing", spacing_, DEFAULT_SPACING, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Terrain, VAR_INT, "Patch Size", GetPatchSize, SetPatchSizeAttr, int, DEFAULT_PATCH_SIZE, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Terrain, VAR_BOOL, "Is Occluder", IsOccluder, SetOccluder, bool,  false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Terrain, VAR_BOOL, "Can Be Occluded", IsOccludee, SetOccludee, bool, true, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Terrain, VAR_BOOL, "Cast Shadows", GetCastShadows, SetCastShadows, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Terrain, VAR_FLOAT, "Draw Distance", GetDrawDistance, SetDrawDistance, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Terrain, VAR_FLOAT, "Shadow Distance", GetShadowDistance, SetShadowDistance, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Terrain, VAR_FLOAT, "LOD Bias", GetLodBias, SetLodBias, float, 1.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Terrain, VAR_INT, "Max Lights", GetMaxLights, SetMaxLights, unsigned, 0, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Terrain, VAR_INT, "View Mask", GetViewMask, SetViewMask, unsigned, DEFAULT_VIEWMASK, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Terrain, VAR_INT, "Light Mask", GetLightMask, SetLightMask, unsigned, DEFAULT_LIGHTMASK, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Terrain, VAR_INT, "Shadow Mask", GetShadowMask, SetShadowMask, unsigned, DEFAULT_SHADOWMASK, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Terrain, VAR_INT, "Zone Mask", GetZoneMask, SetZoneMask, unsigned, DEFAULT_ZONEMASK, AM_DEFAULT);
}

void Terrain::OnSetAttribute(const AttributeInfo& attr, const Variant& src)
{
    Component::OnSetAttribute(attr, src);

    // Change of any non-accessor attribute requires recreation of the terrain
    if (!attr.accessor_)
        recreateTerrain_ = true;
}

void Terrain::ApplyAttributes()
{
    if (recreateTerrain_)
        CreateGeometry();
}

void Terrain::OnSetEnabled()
{
    bool enabled = IsEnabledEffective();

    for (unsigned i = 0; i < patches_.Size(); ++i)
    {
        if (patches_[i])
            patches_[i]->SetEnabled(enabled);
    }
}

void Terrain::SetSpacing(const Vector3& spacing)
{
    if (spacing != spacing_)
    {
        spacing_ = spacing;

        CreateGeometry();
        MarkNetworkUpdate();
    }
}

void Terrain::SetPatchSize(int size)
{
    if (size < MIN_PATCH_SIZE || size > MAX_PATCH_SIZE || !IsPowerOfTwo(size))
        return;

    if (size != patchSize_)
    {
        patchSize_ = size;

        CreateGeometry();
        MarkNetworkUpdate();
    }
}

bool Terrain::SetHeightMap(Image* image)
{
    bool success = SetHeightMapInternal(image, true);

    MarkNetworkUpdate();
    return success;
}

void Terrain::SetMaterial(Material* material)
{
    material_ = material;
    for (unsigned i = 0; i < patches_.Size(); ++i)
    {
        if (patches_[i])
            patches_[i]->SetMaterial(material);
    }

    MarkNetworkUpdate();
}

void Terrain::SetDrawDistance(float distance)
{
    drawDistance_ = distance;
    for (unsigned i = 0; i < patches_.Size(); ++i)
    {
        if (patches_[i])
            patches_[i]->SetDrawDistance(distance);
    }

    MarkNetworkUpdate();
}

void Terrain::SetShadowDistance(float distance)
{
    shadowDistance_ = distance;
    for (unsigned i = 0; i < patches_.Size(); ++i)
    {
        if (patches_[i])
            patches_[i]->SetShadowDistance(distance);
    }

    MarkNetworkUpdate();
}

void Terrain::SetLodBias(float bias)
{
    lodBias_ = bias;
    for (unsigned i = 0; i < patches_.Size(); ++i)
    {
        if (patches_[i])
            patches_[i]->SetLodBias(bias);
    }

    MarkNetworkUpdate();
}

void Terrain::SetViewMask(unsigned mask)
{
    viewMask_ = mask;
    for (unsigned i = 0; i < patches_.Size(); ++i)
    {
        if (patches_[i])
            patches_[i]->SetViewMask(mask);
    }

    MarkNetworkUpdate();
}

void Terrain::SetLightMask(unsigned mask)
{
    lightMask_ = mask;
    for (unsigned i = 0; i < patches_.Size(); ++i)
    {
        if (patches_[i])
            patches_[i]->SetLightMask(mask);
    }

    MarkNetworkUpdate();
}

void Terrain::SetShadowMask(unsigned mask)
{
    shadowMask_ = mask;
    for (unsigned i = 0; i < patches_.Size(); ++i)
    {
        if (patches_[i])
            patches_[i]->SetShadowMask(mask);
    }

    MarkNetworkUpdate();
}

void Terrain::SetZoneMask(unsigned mask)
{
    zoneMask_ = mask;
    for (unsigned i = 0; i < patches_.Size(); ++i)
    {
        if (patches_[i])
            patches_[i]->SetZoneMask(mask);
    }

    MarkNetworkUpdate();
}

void Terrain::SetMaxLights(unsigned num)
{
    maxLights_ = num;
    for (unsigned i = 0; i < patches_.Size(); ++i)
    {
        if (patches_[i])
            patches_[i]->SetMaxLights(num);
    }

    MarkNetworkUpdate();
}

void Terrain::SetCastShadows(bool enable)
{
    castShadows_ = enable;
    for (unsigned i = 0; i < patches_.Size(); ++i)
    {
        if (patches_[i])
            patches_[i]->SetCastShadows(enable);
    }

    MarkNetworkUpdate();
}

void Terrain::SetOccluder(bool enable)
{
    occluder_ = enable;
    for (unsigned i = 0; i < patches_.Size(); ++i)
    {
        if (patches_[i])
            patches_[i]->SetOccluder(enable);
    }

    MarkNetworkUpdate();
}

void Terrain::SetOccludee(bool enable)
{
    occluder_ = enable;
    for (unsigned i = 0; i < patches_.Size(); ++i)
    {
        if (patches_[i])
            patches_[i]->SetOccludee(enable);
    }

    MarkNetworkUpdate();
}

Image* Terrain::GetHeightMap() const
{
    return heightMap_;
}

Material* Terrain::GetMaterial() const
{
    return material_;
}

TerrainPatch* Terrain::GetPatch(unsigned index) const
{
    return index < patches_.Size() ? patches_[index] : (TerrainPatch*)0;
}

TerrainPatch* Terrain::GetPatch(int x, int z) const
{
    if (x < 0 || x >= numPatches_.x_ || z < 0 || z >= numPatches_.y_)
        return 0;
    else
        return GetPatch(z * numPatches_.x_ + x);
}

float Terrain::GetHeight(const Vector3& worldPosition) const
{
    if (node_)
    {
        Vector3 position = node_->GetWorldTransform().Inverse() * worldPosition;
        float xPos = (position.x_ - patchWorldOrigin_.x_) / spacing_.x_;
        float zPos = (position.z_ - patchWorldOrigin_.y_) / spacing_.z_;
        float xFrac = xPos - floorf(xPos);
        float zFrac = zPos - floorf(zPos);
        float h1, h2, h3;

        if (xFrac + zFrac >= 1.0f)
        {
            h1 = GetRawHeight((unsigned)xPos + 1, (unsigned)zPos + 1);
            h2 = GetRawHeight((unsigned)xPos, (unsigned)zPos + 1);
            h3 = GetRawHeight((unsigned)xPos + 1, (unsigned)zPos);
            xFrac = 1.0f - xFrac;
            zFrac = 1.0f - zFrac;
        }
        else
        {
            h1 = GetRawHeight((unsigned)xPos, (unsigned)zPos);
            h2 = GetRawHeight((unsigned)xPos + 1, (unsigned)zPos);
            h3 = GetRawHeight((unsigned)xPos, (unsigned)zPos + 1);
        }

        float h = h1 * (1.0f - xFrac - zFrac) + h2 * xFrac + h3 * zFrac;
        /// \todo This assumes that the terrain scene node is upright
        return node_->GetWorldScale().y_ * h + node_->GetWorldPosition().y_;
    }
    else
        return 0.0f;
}

Vector3 Terrain::GetNormal(const Vector3& worldPosition) const
{
    if (node_)
    {
        Vector3 position = node_->GetWorldTransform().Inverse() * worldPosition;
        float xPos = (position.x_ - patchWorldOrigin_.x_) / spacing_.x_;
        float zPos = (position.z_ - patchWorldOrigin_.y_) / spacing_.z_;
        float xFrac = xPos - floorf(xPos);
        float zFrac = zPos - floorf(zPos);
        Vector3 n1, n2, n3;

        if (xFrac + zFrac >= 1.0f)
        {
            n1 = GetRawNormal((unsigned)xPos + 1, (unsigned)zPos + 1);
            n2 = GetRawNormal((unsigned)xPos, (unsigned)zPos + 1);
            n3 = GetRawNormal((unsigned)xPos + 1, (unsigned)zPos);
            xFrac = 1.0f - xFrac;
            zFrac = 1.0f - zFrac;
        }
        else
        {
            n1 = GetRawNormal((unsigned)xPos, (unsigned)zPos);
            n2 = GetRawNormal((unsigned)xPos + 1, (unsigned)zPos);
            n3 = GetRawNormal((unsigned)xPos, (unsigned)zPos + 1);
        }

        Vector3 n = (n1 * (1.0f - xFrac - zFrac) + n2 * xFrac + n3 * zFrac).Normalized();
        return node_->GetWorldRotation() * n;
    }
    else
        return Vector3::UP;
}

void Terrain::CreatePatchGeometry(TerrainPatch* patch)
{
    PROFILE(CreatePatchGeometry);

    unsigned row = patchSize_ + 1;
    VertexBuffer* vertexBuffer = patch->GetVertexBuffer();
    Geometry* geometry = patch->GetGeometry();
    Geometry* maxLodGeometry = patch->GetMaxLodGeometry();
    Geometry* minLodGeometry = patch->GetMinLodGeometry();

    if (vertexBuffer->GetVertexCount() != row * row)
        vertexBuffer->SetSize(row * row, MASK_POSITION | MASK_NORMAL | MASK_TEXCOORD1 | MASK_TANGENT);

    SharedArrayPtr<unsigned char> cpuVertexData(new unsigned char[row * row * sizeof(Vector3)]);

    float* vertexData = (float*)vertexBuffer->Lock(0, vertexBuffer->GetVertexCount());
    float* positionData = (float*)cpuVertexData.Get();
    BoundingBox box;

    if (vertexData)
    {
        const IntVector2& coords = patch->GetCoordinates();

        for (int z1 = 0; z1 <= patchSize_; ++z1)
        {
            for (int x1 = 0; x1 <= patchSize_; ++x1)
            {
                int xPos = coords.x_ * patchSize_ + x1;
                int zPos = coords.y_ * patchSize_ + z1;

                // Position
                Vector3 position((float)x1 * spacing_.x_, GetRawHeight(xPos, zPos), (float)z1 * spacing_.z_);
                *vertexData++ = position.x_;
                *vertexData++ = position.y_;
                *vertexData++ = position.z_;
                *positionData++ = position.x_;
                *positionData++ = position.y_;
                *positionData++ = position.z_;

                box.Merge(position);

                // Normal
                Vector3 normal = GetRawNormal(xPos, zPos);
                *vertexData++ = normal.x_;
                *vertexData++ = normal.y_;
                *vertexData++ = normal.z_;

                // Texture coordinate
                Vector2 texCoord((float)xPos / (float)numVertices_.x_, 1.0f - (float)zPos / (float)numVertices_.y_);
                *vertexData++ = texCoord.x_;
                *vertexData++ = texCoord.y_;

                // Tangent
                Vector3 xyz = (Vector3::RIGHT - normal * normal.DotProduct(Vector3::RIGHT)).Normalized();
                *vertexData++ = xyz.x_;
                *vertexData++ = xyz.y_;
                *vertexData++ = xyz.z_;
                *vertexData++ = 1.0f;
            }
        }

        vertexBuffer->Unlock();
        vertexBuffer->ClearDataLost();
    }

    patch->SetBoundingBox(box);

    if (drawRanges_.Size())
    {
        unsigned lastDrawRange = drawRanges_.Size() - 1;

        geometry->SetIndexBuffer(indexBuffer_);
        geometry->SetDrawRange(TRIANGLE_LIST, drawRanges_[0].first_, drawRanges_[0].second_, false);
        geometry->SetRawVertexData(cpuVertexData, sizeof(Vector3), MASK_POSITION);
        maxLodGeometry->SetIndexBuffer(indexBuffer_);
        maxLodGeometry->SetDrawRange(TRIANGLE_LIST, drawRanges_[0].first_, drawRanges_[0].second_, false);
        maxLodGeometry->SetRawVertexData(cpuVertexData, sizeof(Vector3), MASK_POSITION);
        minLodGeometry->SetIndexBuffer(indexBuffer_);
        minLodGeometry->SetDrawRange(TRIANGLE_LIST, drawRanges_[lastDrawRange].first_, drawRanges_[lastDrawRange].second_, false);
        minLodGeometry->SetRawVertexData(cpuVertexData, sizeof(Vector3), MASK_POSITION);
    }

    // Offset the occlusion geometry by vertex spacing to reduce possibility of over-aggressive occlusion
    patch->SetOcclusionOffset(-0.5f * (spacing_.x_ + spacing_.z_));
    patch->ResetLod();
}

void Terrain::UpdatePatchLod(TerrainPatch* patch)
{
    Geometry* geometry = patch->GetGeometry();

    // All LOD levels except the coarsest have 16 versions for stitching
    unsigned lodLevel = patch->GetLodLevel();
    unsigned drawRangeIndex = lodLevel << 4;
    if (lodLevel < numLodLevels_ - 1)
    {
        TerrainPatch* north = patch->GetNorthPatch();
        TerrainPatch* south = patch->GetSouthPatch();
        TerrainPatch* west = patch->GetWestPatch();
        TerrainPatch* east = patch->GetEastPatch();

        if (north && north->GetLodLevel() > lodLevel)
            drawRangeIndex |= STITCH_NORTH;
        if (south && south->GetLodLevel() > lodLevel)
            drawRangeIndex |= STITCH_SOUTH;
        if (west && west->GetLodLevel() > lodLevel)
            drawRangeIndex |= STITCH_WEST;
        if (east && east->GetLodLevel() > lodLevel)
            drawRangeIndex |= STITCH_EAST;
    }

    if (drawRangeIndex < drawRanges_.Size())
        geometry->SetDrawRange(TRIANGLE_LIST, drawRanges_[drawRangeIndex].first_, drawRanges_[drawRangeIndex].second_, false);
}

void Terrain::SetMaterialAttr(ResourceRef value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    SetMaterial(cache->GetResource<Material>(value.id_));
}

void Terrain::SetHeightMapAttr(ResourceRef value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    Image* image = cache->GetResource<Image>(value.id_);
    SetHeightMapInternal(image, false);
}

void Terrain::SetPatchSizeAttr(int value)
{
    if (value < MIN_PATCH_SIZE || value > MAX_PATCH_SIZE || !IsPowerOfTwo(value))
        return;

    if (value != patchSize_)
    {
        patchSize_ = value;
        recreateTerrain_ = true;
    }
}

ResourceRef Terrain::GetMaterialAttr() const
{
    return GetResourceRef(material_, Material::GetTypeStatic());
}

ResourceRef Terrain::GetHeightMapAttr() const
{
    return GetResourceRef(heightMap_, Image::GetTypeStatic());
}

void Terrain::CreateGeometry()
{
    recreateTerrain_ = false;

    if (!node_)
        return;

    PROFILE(CreateTerrainGeometry);

    unsigned prevNumPatches = patches_.Size();

    // Determine number of LOD levels
    unsigned lodSize = patchSize_;
    numLodLevels_ = 1;
    while (lodSize > MIN_PATCH_SIZE && numLodLevels_ < MAX_LOD_LEVELS)
    {
        lodSize >>= 1;
        ++numLodLevels_;
    }

    // Determine total terrain size
    patchWorldSize_ = Vector2(spacing_.x_ * (float)patchSize_, spacing_.z_ * (float)patchSize_);
    if (heightMap_)
    {
        numPatches_ = IntVector2((heightMap_->GetWidth() - 1) / patchSize_, (heightMap_->GetHeight() - 1) / patchSize_);
        numVertices_ = IntVector2(numPatches_.x_ * patchSize_ + 1, numPatches_.y_ * patchSize_ + 1);
        patchWorldOrigin_ = Vector2(-0.5f * (float)numPatches_.x_ * patchWorldSize_.x_, -0.5f * (float)numPatches_.y_ *
            patchWorldSize_.y_);
        heightData_ = new float[numVertices_.x_ * numVertices_.y_];
    }
    else
    {
        numPatches_ = IntVector2::ZERO;
        numVertices_ = IntVector2::ZERO;
        patchWorldOrigin_ = Vector2::ZERO;
        heightData_.Reset();
    }

    // Remove old patch nodes which are not needed
    PODVector<Node*> oldPatchNodes;
    node_->GetChildrenWithComponent<TerrainPatch>(oldPatchNodes);
    for (PODVector<Node*>::Iterator i = oldPatchNodes.Begin(); i != oldPatchNodes.End(); ++i)
    {
        bool nodeOk = false;
        Vector<String> coords = (*i)->GetName().Substring(6).Split('_');
        if (coords.Size() == 2)
        {
            int x = ToInt(coords[0]);
            int z = ToInt(coords[1]);
            if (x < numPatches_.x_ && z < numPatches_.y_)
                nodeOk = true;
        }

        if (!nodeOk)
            node_->RemoveChild(*i);
    }

    patches_.Clear();

    if (heightMap_)
    {
        // Copy heightmap data
        const unsigned char* src = heightMap_->GetData();
        float* dest = heightData_;
        unsigned imgComps = heightMap_->GetComponents();
        unsigned imgRow = heightMap_->GetWidth() * imgComps;

        if (imgComps == 1)
        {
            for (int z = 0; z < numVertices_.y_; ++z)
            {
                for (int x = 0; x < numVertices_.x_; ++x)
                    *dest++ = (float)src[imgRow * (numVertices_.y_ - 1 - z) + x] * spacing_.y_;
            }
        }
        else
        {
            // If more than 1 component, use the green channel for more accuracy
            for (int z = 0; z < numVertices_.y_; ++z)
            {
                for (int x = 0; x < numVertices_.x_; ++x)
                    *dest++ = ((float)src[imgRow * (numVertices_.y_ - 1 - z) + imgComps * x] + (float)src[imgRow *
                        (numVertices_.y_ - 1 - z) + imgComps * x + 1] / 256.0f) * spacing_.y_;
            }
        }

        patches_.Reserve(numPatches_.x_ * numPatches_.y_);

        bool enabled = IsEnabledEffective();

        // Create patches and set node transforms
        for (int z = 0; z < numPatches_.y_; ++z)
        {
            for (int x = 0; x < numPatches_.x_; ++x)
            {
                String nodeName = "Patch_" + String(x) + "_" + String(z);
                Node* patchNode = node_->GetChild(nodeName);
                if (!patchNode)
                    patchNode = node_->CreateChild(nodeName, LOCAL);

                patchNode->SetPosition(Vector3(patchWorldOrigin_.x_ + (float)x * patchWorldSize_.x_, 0.0f, patchWorldOrigin_.y_ +
                    (float)z * patchWorldSize_.y_));

                TerrainPatch* patch = patchNode->GetOrCreateComponent<TerrainPatch>();
                patch->SetOwner(this);
                patch->SetCoordinates(IntVector2(x, z));

                // Copy initial drawable parameters
                patch->SetEnabled(enabled);
                patch->SetMaterial(material_);
                patch->SetDrawDistance(drawDistance_);
                patch->SetShadowDistance(shadowDistance_);
                patch->SetLodBias(lodBias_);
                patch->SetViewMask(viewMask_);
                patch->SetLightMask(lightMask_);
                patch->SetShadowMask(shadowMask_);
                patch->SetZoneMask(zoneMask_);
                patch->SetMaxLights(maxLights_);
                patch->SetCastShadows(castShadows_);
                patch->SetOccluder(occluder_);
                patch->SetOccludee(occludee_);

                patches_.Push(WeakPtr<TerrainPatch>(patch));
            }
        }

        // Create the shared index data
        CreateIndexData();

        // Create vertex data for patches
        for (Vector<WeakPtr<TerrainPatch> >::Iterator i = patches_.Begin(); i != patches_.End(); ++i)
        {
            CreatePatchGeometry(*i);
            CalculateLodErrors(*i);
            SetNeighbors(*i);
        }
    }

    // Send event only if new geometry was generated, or the old was cleared
    if (patches_.Size() || prevNumPatches)
    {
        using namespace TerrainCreated;

        VariantMap eventData;
        eventData[P_NODE] = (void*)node_;
        node_->SendEvent(E_TERRAINCREATED, eventData);
    }
}

void Terrain::CreateIndexData()
{
    PROFILE(CreateIndexData);

    PODVector<unsigned short> indices;
    drawRanges_.Clear();
    unsigned row = patchSize_ + 1;

    for (unsigned i = 0; i < numLodLevels_; ++i)
    {
        unsigned combinations = (i < numLodLevels_ - 1) ? 16 : 1;
        int skip = 1 << i;

        for (unsigned j = 0; j < combinations; ++j)
        {
            unsigned indexStart = indices.Size();

            int zStart = 0;
            int xStart = 0;
            int zEnd = patchSize_;
            int xEnd = patchSize_;

            if (j & STITCH_NORTH)
                zEnd -= skip;
            if (j & STITCH_SOUTH)
                zStart += skip;
            if (j & STITCH_WEST)
                xStart += skip;
            if (j & STITCH_EAST)
                xEnd -= skip;

            // Build the main grid
            for (int z = zStart; z < zEnd; z += skip)
            {
                for (int x = xStart; x < xEnd; x += skip)
                {
                    indices.Push((z + skip) * row + x);
                    indices.Push(z * row + x + skip);
                    indices.Push(z * row + x);
                    indices.Push((z + skip) * row + x);
                    indices.Push((z + skip) * row + x + skip);
                    indices.Push(z * row + x + skip);
                }
            }

            // Build the north edge
            if (j & STITCH_NORTH)
            {
                int z = patchSize_ - skip;
                for (int x = 0; x < patchSize_; x += skip * 2)
                {
                    if (x > 0 || (j & STITCH_WEST) == 0)
                    {
                        indices.Push((z + skip) * row + x);
                        indices.Push(z * row + x + skip);
                        indices.Push(z * row + x);
                    }
                    indices.Push((z + skip) * row + x);
                    indices.Push((z + skip) * row + x + 2 * skip);
                    indices.Push(z * row + x + skip);
                    if (x < patchSize_ - skip * 2 || (j & STITCH_EAST) == 0)
                    {
                        indices.Push((z + skip) * row + x + 2 * skip);
                        indices.Push(z * row + x + 2 * skip);
                        indices.Push(z * row + x + skip);
                    }
                }
            }

            // Build the south edge
            if (j & STITCH_SOUTH)
            {
                int z = 0;
                for (int x = 0; x < patchSize_; x += skip * 2)
                {
                    if (x > 0 || (j & STITCH_WEST) == 0)
                    {
                        indices.Push((z + skip) * row + x);
                        indices.Push((z + skip) * row + x + skip);
                        indices.Push(z * row + x);
                    }
                    indices.Push(z * row + x);
                    indices.Push((z + skip) * row + x + skip);
                    indices.Push(z * row + x + 2 * skip);
                    if (x < patchSize_ - skip * 2 || (j & STITCH_EAST) == 0)
                    {
                        indices.Push((z + skip) * row + x + skip);
                        indices.Push((z + skip) * row + x + 2 * skip);
                        indices.Push(z * row + x + 2 * skip);
                    }
                }
            }

            // Build the west edge
            if (j & STITCH_WEST)
            {
                int x = 0;
                for (int z = 0; z < patchSize_; z += skip * 2)
                {
                    if (z > 0 || (j & STITCH_SOUTH) == 0)
                    {
                        indices.Push(z * row + x);
                        indices.Push((z + skip) * row + x + skip);
                        indices.Push(z * row + x + skip);
                    }
                    indices.Push((z + 2 * skip) * row + x);
                    indices.Push((z + skip) * row + x + skip);
                    indices.Push(z * row + x);
                    if (x < patchSize_ - skip * 2 || (j & STITCH_NORTH) == 0)
                    {
                        indices.Push((z + 2 * skip) * row + x);
                        indices.Push((z + 2 * skip) * row + x + skip);
                        indices.Push((z + skip) * row + x + skip);
                    }
                }
            }

            // Build the east edge
            if (j & STITCH_EAST)
            {
                int x = patchSize_ - skip;
                for (int z = 0; z < patchSize_; z += skip * 2)
                {
                    if (z > 0 || (j & STITCH_SOUTH) == 0)
                    {
                        indices.Push(z * row + x);
                        indices.Push((z + skip) * row + x);
                        indices.Push(z * row + x + skip);
                    }
                    indices.Push((z + skip) * row + x);
                    indices.Push((z + 2 * skip) * row + x + skip);
                    indices.Push(z * row + x + skip);
                    if (z < patchSize_ - skip * 2 || (j & STITCH_NORTH) == 0)
                    {
                        indices.Push((z + skip) * row + x);
                        indices.Push((z + 2 * skip) * row + x);
                        indices.Push((z + 2 * skip) * row + x + skip);
                    }
                }
            }

            drawRanges_.Push(MakePair(indexStart, indices.Size() - indexStart));
        }
    }

    indexBuffer_->SetSize(indices.Size(), false);
    unsigned short* indexData = (unsigned short*)indexBuffer_->Lock(0, indices.Size());
    if (indexData)
    {
        memcpy(indexData, &indices[0], indices.Size() * sizeof(unsigned short));
        indexBuffer_->Unlock();
    }
}

float Terrain::GetRawHeight(int x, int z) const
{
    if (!heightData_)
        return 0.0f;

    x = Clamp(x, 0, numVertices_.x_ - 1);
    z = Clamp(z, 0, numVertices_.y_ - 1);
    return heightData_[z * numVertices_.x_ + x];
}

float Terrain::GetLodHeight(int x, int z, unsigned lodLevel) const
{
    unsigned offset = 1 << lodLevel;
    float divisor = (float)offset;
    float xFrac = (float)(x % offset) / divisor;
    float zFrac = (float)(z % offset) / divisor;
    float h1, h2, h3;

    if (xFrac + zFrac >= 1.0f)
    {
        h1 = GetRawHeight(x + offset, z + offset);
        h2 = GetRawHeight(x, z + offset);
        h3 = GetRawHeight(x + offset, z);
        xFrac = 1.0f - xFrac;
        zFrac = 1.0f - zFrac;
    }
    else
    {
        h1 = GetRawHeight(x, z);
        h2 = GetRawHeight(x + offset, z);
        h3 = GetRawHeight(x, z + offset);
    }

    return h1 * (1.0f - xFrac - zFrac) + h2 * xFrac + h3 * zFrac;
}

Vector3 Terrain::GetRawNormal(int x, int z) const
{
    float baseHeight = GetRawHeight(x, z);
    float nSlope = GetRawHeight(x, z - 1) - baseHeight;
    float neSlope = GetRawHeight(x + 1, z - 1) - baseHeight;
    float eSlope = GetRawHeight(x + 1, z) - baseHeight;
    float seSlope = GetRawHeight(x + 1, z + 1) - baseHeight;
    float sSlope = GetRawHeight(x, z + 1) - baseHeight;
    float swSlope = GetRawHeight(x - 1, z + 1) - baseHeight;
    float wSlope = GetRawHeight(x - 1, z) - baseHeight;
    float nwSlope = GetRawHeight(x - 1, z - 1) - baseHeight;
    float up = 0.5f * (spacing_.x_ + spacing_.z_);

    return (Vector3(0.0f, up, nSlope) +
        Vector3(-neSlope, up, neSlope) +
        Vector3(-eSlope, up, 0.0f) +
        Vector3(-seSlope, up, -seSlope) +
        Vector3(0.0f, up, -sSlope) +
        Vector3(swSlope, up, -swSlope) +
        Vector3(wSlope, up, 0.0f) +
        Vector3(nwSlope, up, nwSlope)).Normalized();
}

void Terrain::CalculateLodErrors(TerrainPatch* patch)
{
    PROFILE(CalculateLodErrors);

    const IntVector2& coords = patch->GetCoordinates();
    PODVector<float>& lodErrors = patch->GetLodErrors();
    lodErrors.Clear();
    lodErrors.Reserve(numLodLevels_);

    int xStart = coords.x_ * patchSize_;
    int zStart = coords.y_ * patchSize_;
    int xEnd = xStart + patchSize_;
    int zEnd = zStart + patchSize_;

    for (unsigned i = 0; i < numLodLevels_; ++i)
    {
        float maxError = 0.0f;
        int divisor = 1 << i;

        if (i > 0)
        {
            for (int z = zStart; z <= zEnd; ++z)
            {
                for (int x = xStart; x <= xEnd; ++x)
                {
                    if (x % divisor || z % divisor)
                    {
                        float error = Abs(GetLodHeight(x, z, i) - GetRawHeight(x, z));
                        maxError = Max(error, maxError);
                    }
                }
            }

            // Set error to be at least same as (half vertex spacing x LOD) to prevent horizontal stretches getting too inaccurate
            maxError = Max(maxError, 0.25f * (spacing_.x_ + spacing_.z_) * (float)(1 << i));
        }

        lodErrors.Push(maxError);
    }
}

void Terrain::SetNeighbors(TerrainPatch* patch)
{
    const IntVector2& coords = patch->GetCoordinates();
    patch->SetNeighbors(GetPatch(coords.x_, coords.y_ + 1), GetPatch(coords.x_, coords.y_ - 1),
        GetPatch(coords.x_ - 1, coords.y_), GetPatch(coords.x_ + 1, coords.y_));
}

bool Terrain::SetHeightMapInternal(Image* image, bool recreateNow)
{
    if (image && image->IsCompressed())
    {
        LOGERROR("Can not use a compressed image as a terrain heightmap");
        return false;
    }

    // Unsubscribe from the reload event of previous image (if any), then subscribe to the new
    if (heightMap_)
        UnsubscribeFromEvent(heightMap_, E_RELOADFINISHED);
    if (image)
        SubscribeToEvent(image, E_RELOADFINISHED, HANDLER(Terrain, HandleHeightMapReloadFinished));

    heightMap_ = image;

    if (recreateNow)
        CreateGeometry();
    else
        recreateTerrain_ = true;

    return true;
}

void Terrain::HandleHeightMapReloadFinished(StringHash eventType, VariantMap& eventData)
{
    CreateGeometry();
}

}
