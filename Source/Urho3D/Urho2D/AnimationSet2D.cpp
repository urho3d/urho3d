//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../Container/ArrayPtr.h"
#include "../Core/Context.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/Texture2D.h"
#include "../IO/FileSystem.h"
#include "../IO/Log.h"
#include "../Math/AreaAllocator.h"
#include "../Resource/Image.h"
#include "../Resource/ResourceCache.h"
#include "../Resource/XMLFile.h"
#include "../Urho2D/AnimationSet2D.h"
#include "../Urho2D/Sprite2D.h"
#include "../Urho2D/SpriterData2D.h"
#include "../Urho2D/SpriteSheet2D.h"

#include "../DebugNew.h"

#ifdef URHO3D_SPINE
#include <spine/spine.h>
#include <spine/extension.h>
#endif

#ifdef URHO3D_SPINE
// Current animation set
static Urho3D::AnimationSet2D* currentAnimationSet = 0;

void _spAtlasPage_createTexture(spAtlasPage* self, const char* path)
{
    using namespace Urho3D;
    if (!currentAnimationSet)
        return;

    ResourceCache* cache = currentAnimationSet->GetSubsystem<ResourceCache>();
    Sprite2D* sprite = cache->GetResource<Sprite2D>(path);
    // Add reference
    if (sprite)
        sprite->AddRef();

    self->width = sprite->GetTexture()->GetWidth();
    self->height = sprite->GetTexture()->GetHeight();

    self->rendererObject = sprite;
}

void _spAtlasPage_disposeTexture(spAtlasPage* self)
{
    using namespace Urho3D;
    Sprite2D* sprite = static_cast<Sprite2D*>(self->rendererObject);
    if (sprite)
        sprite->ReleaseRef();

    self->rendererObject = 0;
}

char* _spUtil_readFile(const char* path, int* length)
{
    using namespace Urho3D;
    
    if (!currentAnimationSet)
        return 0;

    ResourceCache* cache = currentAnimationSet->GetSubsystem<ResourceCache>();
    SharedPtr<File> file = cache->GetFile(path);
    if (!file)
        return 0;

    unsigned size = file->GetSize();

    char* data = MALLOC(char, size + 1);
    file->Read(data, size);
    data[size] = '\0';
    
    file.Reset();
    *length = size;

    return data;
}
#endif

namespace Urho3D
{

AnimationSet2D::AnimationSet2D(Context* context) :
    Resource(context),
#ifdef URHO3D_SPINE
    skeletonData_(0),
    atlas_(0),
#endif
    spriterData_(0),
    hasSpriteSheet_(false)
{
}

AnimationSet2D::~AnimationSet2D()
{
    Dispose();
}

void AnimationSet2D::RegisterObject(Context* context)
{
    context->RegisterFactory<AnimationSet2D>();
}

bool AnimationSet2D::BeginLoad(Deserializer& source)
{
    Dispose();

    if (GetName().Empty())
        SetName(source.GetName());

    String extension = GetExtension(source.GetName());
#ifdef URHO3D_SPINE
    if (extension == ".json")
        return BeginLoadSpine(source);
#endif
    if (extension == ".scml")
        return BeginLoadSpriter(source);

    URHO3D_LOGERROR("Unsupport animation set file: " + source.GetName());

    return false;
}

bool AnimationSet2D::EndLoad()
{
#ifdef URHO3D_SPINE
    if (jsonData_)
        return EndLoadSpine();
#endif
    if (spriterData_)
        return EndLoadSpriter();

    return false;
}

unsigned AnimationSet2D::GetNumAnimations() const
{
#ifdef URHO3D_SPINE
    if (skeletonData_)
        return (unsigned)skeletonData_->animationsCount;
#endif
    if (spriterData_ && !spriterData_->entities_.Empty())
        return (unsigned)spriterData_->entities_[0]->animations_.Size();
    return 0;
}

String AnimationSet2D::GetAnimation(unsigned index) const
{
    if (index >= GetNumAnimations())
        return String::EMPTY;

#ifdef URHO3D_SPINE
    if (skeletonData_)
        return skeletonData_->animations[index]->name;
#endif
    if (spriterData_ && !spriterData_->entities_.Empty())
        return spriterData_->entities_[0]->animations_[index]->name_;

    return String::EMPTY;
}

bool AnimationSet2D::HasAnimation(const String& animationName) const
{
#ifdef URHO3D_SPINE
    if (skeletonData_)
    {
        for (int i = 0; i < skeletonData_->animationsCount; ++i)
        {
            if (animationName == skeletonData_->animations[i]->name)
                return true;
        }
    }
#endif    
    if (spriterData_ && !spriterData_->entities_.Empty())
    {
        const PODVector<Spriter::Animation*>& animations = spriterData_->entities_[0]->animations_;
        for (size_t i = 0; i < animations.Size(); ++i)
        {
            if (animationName == animations[i]->name_)
                return true;
        }
    }

    return false;
}

Sprite2D* AnimationSet2D::GetSprite() const
{
    return sprite_;
}

Sprite2D* AnimationSet2D::GetSpriterFileSprite(int folderId, int fileId) const
{
    int key = (folderId << 16) + fileId;
    HashMap<int, SharedPtr<Sprite2D> >::ConstIterator i = spriterFileSprites_.Find(key);
    if (i != spriterFileSprites_.End())
        return i->second_;

    return 0;
}

#ifdef URHO3D_SPINE
bool AnimationSet2D::BeginLoadSpine(Deserializer& source)
{
    if (GetName().Empty())
        SetName(source.GetName());

    unsigned size = source.GetSize();
    jsonData_ = new char[size + 1];
    source.Read(jsonData_, size);
    jsonData_[size] = '\0';
    SetMemoryUse(size);
    return true;
}

bool AnimationSet2D::EndLoadSpine()
{
    currentAnimationSet = this;

    String atlasFileName = ReplaceExtension(GetName(), ".atlas");
    atlas_ = spAtlas_createFromFile(atlasFileName.CString(), 0);
    if (!atlas_)
    {
        URHO3D_LOGERROR("Create spine atlas failed");
        return false;
    }

    int numAtlasPages = 0;
    spAtlasPage* atlasPage = atlas_->pages;
    while (atlasPage)
    {
        ++numAtlasPages;
        atlasPage = atlasPage->next;
    }

    if (numAtlasPages > 1)
    {
        URHO3D_LOGERROR("Only one page is supported in Urho3D");
        return false;
    }

    sprite_ = static_cast<Sprite2D*>(atlas_->pages->rendererObject);

    spSkeletonJson* skeletonJson = spSkeletonJson_create(atlas_);
    if (!skeletonJson)
    {
        URHO3D_LOGERROR("Create skeleton Json failed");
        return false;
    }

    skeletonJson->scale = 0.01f; // PIXEL_SIZE;
    skeletonData_ = spSkeletonJson_readSkeletonData(skeletonJson, &jsonData_[0]);

    spSkeletonJson_dispose(skeletonJson);
    jsonData_.Reset();

    currentAnimationSet = 0;

    return true;
}
#endif

bool AnimationSet2D::BeginLoadSpriter(Deserializer& source)
{
    unsigned dataSize = source.GetSize();
    if (!dataSize && !source.GetName().Empty())
    {
        URHO3D_LOGERROR("Zero sized XML data in " + source.GetName());
        return false;
    }

    SharedArrayPtr<char> buffer(new char[dataSize]);
    if (source.Read(buffer.Get(), dataSize) != dataSize)
        return false;

    spriterData_ = new Spriter::SpriterData();
    if (!spriterData_->Load(buffer.Get(), dataSize))
    {
        URHO3D_LOGERROR("Could not spriter data from " + source.GetName());
        return false;
    }

    // Check has sprite sheet
    String parentPath = GetParentPath(GetName());
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    spriteSheetFilePath_ = parentPath + GetFileName(GetName()) + ".xml";
    hasSpriteSheet_ = cache->Exists(spriteSheetFilePath_);
    if (!hasSpriteSheet_)
    {
        spriteSheetFilePath_ = parentPath + GetFileName(GetName()) + ".plist";
        hasSpriteSheet_ = cache->Exists(spriteSheetFilePath_);
    }

    if (GetAsyncLoadState() == ASYNC_LOADING)
    {
        if (hasSpriteSheet_)
            cache->BackgroundLoadResource<SpriteSheet2D>(spriteSheetFilePath_, true, this);
        else
        {
            for (size_t i = 0; i < spriterData_->folders_.Size(); ++i)
            {
                Spriter::Folder* folder = spriterData_->folders_[i];
                for (size_t j = 0; j < folder->files_.Size(); ++j)
                {
                    Spriter::File* file = folder->files_[j];
                    String imagePath = parentPath + file->name_;
                    cache->BackgroundLoadResource<Image>(imagePath, true, this);
                }
            }
        }
    }

    // Note: this probably does not reflect internal data structure size accurately
    SetMemoryUse(dataSize);

    return true;
}

struct SpriteInfo
{
    int x;
    int y;
    Spriter::File* file_;
    SharedPtr<Image> image_;
};

bool AnimationSet2D::EndLoadSpriter()
{
    if (!spriterData_)
        return false;
    
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    if (hasSpriteSheet_)
    {
        spriteSheet_ = cache->GetResource<SpriteSheet2D>(spriteSheetFilePath_);
        if (!spriteSheet_)
            return false;

        for (unsigned i = 0; i < spriterData_->folders_.Size(); ++i)
        {
            Spriter::Folder* folder = spriterData_->folders_[i];
            for (unsigned j = 0; j < folder->files_.Size(); ++j)
            {
                Spriter::File* file = folder->files_[j];
                SharedPtr<Sprite2D> sprite(spriteSheet_->GetSprite(GetFileName(file->name_)));
                if (!sprite)
                {
                    URHO3D_LOGERROR("Could not load sprite " + file->name_);
                    return false;
                }

                Vector2 hotSpot(file->pivotX_, file->pivotY_);

                // If sprite is trimmed, recalculate hot spot
                const IntVector2& offset = sprite->GetOffset();
                if (offset != IntVector2::ZERO)
                {
                    float pivotX = file->width_ * hotSpot.x_;
                    float pivotY = file->height_ * (1.0f - hotSpot.y_);

                    const IntRect& rectangle = sprite->GetRectangle();
                    hotSpot.x_ = (offset.x_ + pivotX) / rectangle.Width();
                    hotSpot.y_ = 1.0f - (offset.y_ + pivotY) / rectangle.Height();
                }

                sprite->SetHotSpot(hotSpot);

                if (!sprite_)
                    sprite_ = sprite;

                int key = (folder->id_ << 16) + file->id_;
                spriterFileSprites_[key] = sprite;
            }
        }
    }
    else
    {
        Vector<SpriteInfo> spriteInfos;
        String parentPath = GetParentPath(GetName());

        for (unsigned i = 0; i < spriterData_->folders_.Size(); ++i)
        {
            Spriter::Folder* folder = spriterData_->folders_[i];
            for (unsigned j = 0; j < folder->files_.Size(); ++j)
            {
                Spriter::File* file = folder->files_[j];
                String imagePath = parentPath + file->name_;
                SharedPtr<Image> image(cache->GetResource<Image>(imagePath));
                if (!image)
                {
                    URHO3D_LOGERROR("Could not load image");
                    return false;
                }
                if (image->IsCompressed())
                {
                    URHO3D_LOGERROR("Compressed image is not support");
                    return false;
                }
                if (image->GetComponents() != 4)
                {
                    URHO3D_LOGERROR("Only support image with 4 components");
                    return false;
                }

                SpriteInfo def;
                def.x = 0;
                def.y = 0;
                def.file_ = file;
                def.image_ = image;
                spriteInfos.Push(def);
            }
        }

        if (spriteInfos.Empty())
            return false;

        if (spriteInfos.Size() > 1)
        {
            AreaAllocator allocator(128, 128, 2048, 2048);
            for (unsigned i = 0; i < spriteInfos.Size(); ++i)
            {
                SpriteInfo& info = spriteInfos[i];
                Image* image = info.image_;
                if (!allocator.Allocate(image->GetWidth() + 1, image->GetHeight() + 1, info.x, info.y))
                {
                    URHO3D_LOGERROR("Could not allocate area");
                    return false;
                }
            }

            SharedPtr<Texture2D> texture(new Texture2D(context_));
            texture->SetMipsToSkip(QUALITY_LOW, 0);
            texture->SetNumLevels(1);
            texture->SetSize(allocator.GetWidth(), allocator.GetHeight(), Graphics::GetRGBAFormat());

            unsigned textureDataSize = allocator.GetWidth() * allocator.GetHeight() * 4;
            SharedArrayPtr<unsigned char> textureData(new unsigned char[textureDataSize]);
            memset(textureData.Get(), 0, textureDataSize);

            sprite_ = new Sprite2D(context_);
            sprite_->SetTexture(texture);

            for (unsigned i = 0; i < spriteInfos.Size(); ++i)
            {
                SpriteInfo& info = spriteInfos[i];
                Image* image = info.image_;

                for (int y = 0; y < image->GetHeight(); ++y)
                {
                    memcpy(textureData.Get() + ((info.y + y) * allocator.GetWidth() + info.x) * 4,
                        image->GetData() + y * image->GetWidth() * 4, image->GetWidth() * 4);
                }

                SharedPtr<Sprite2D> sprite(new Sprite2D(context_));
                sprite->SetTexture(texture);
                sprite->SetRectangle(IntRect(info.x, info.y, info.x + image->GetWidth(), info.y + image->GetHeight()));
                sprite->SetHotSpot(Vector2(info.file_->pivotX_, info.file_->pivotY_));

                int key = (info.file_->folder_->id_ << 16) + info.file_->id_;
                spriterFileSprites_[key] = sprite;
            }

            texture->SetData(0, 0, 0, allocator.GetWidth(), allocator.GetHeight(), textureData.Get());
        }
        else
        {
            SharedPtr<Texture2D> texture(new Texture2D(context_));
            texture->SetMipsToSkip(QUALITY_LOW, 0);
            texture->SetNumLevels(1);

            SpriteInfo& info = spriteInfos[0];        
            texture->SetData(info.image_, true);

            sprite_ = new Sprite2D(context_);
            sprite_->SetTexture(texture);
            sprite_->SetRectangle(IntRect(info.x, info.y, info.x + info.image_->GetWidth(), info.y + info.image_->GetHeight()));
            sprite_->SetHotSpot(Vector2(info.file_->pivotX_, info.file_->pivotY_));

            int key = (info.file_->folder_->id_ << 16) + info.file_->id_;
            spriterFileSprites_[key] = sprite_;
        }
    }

    return true;
}

void AnimationSet2D::Dispose()
{
#ifdef URHO3D_SPINE
    if (skeletonData_)
    {
        spSkeletonData_dispose(skeletonData_);
        skeletonData_ = 0;
    }

    if (atlas_)
    {
        spAtlas_dispose(atlas_);
        atlas_ = 0;
    }
#endif

    if (spriterData_)
    {
        delete spriterData_;
        spriterData_ = 0;
    }

    sprite_.Reset();
    spriteSheet_.Reset();
    spriterFileSprites_.Clear();
}

}
