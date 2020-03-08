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

/// \file

#pragma once

#include "../Container/Ptr.h"
#include "../Container/RefCounted.h"
#include "../Graphics/GraphicsDefs.h"
#include "../Math/Color.h"
#include "../Math/Vector4.h"

namespace Urho3D
{

class XMLElement;
class XMLFile;

/// Rendering path command types.
enum RenderCommandType
{
    CMD_NONE = 0,
    CMD_CLEAR,
    CMD_SCENEPASS,
    CMD_QUAD,
    CMD_FORWARDLIGHTS,
    CMD_LIGHTVOLUMES,
    CMD_RENDERUI,
    CMD_SENDEVENT
};

/// Rendering path sorting modes.
enum RenderCommandSortMode
{
    SORT_FRONTTOBACK = 0,
    SORT_BACKTOFRONT
};

/// Rendertarget size mode.
enum RenderTargetSizeMode
{
    SIZE_ABSOLUTE = 0,
    SIZE_VIEWPORTDIVISOR,
    SIZE_VIEWPORTMULTIPLIER
};

/// Rendertarget definition.
struct URHO3D_API RenderTargetInfo
{
    /// Read from an XML element.
    void Load(const XMLElement& element);

    /// Name.
    String name_;
    /// Tag name.
    String tag_;
    /// Texture format.
    unsigned format_{};
    /// Absolute size or multiplier.
    Vector2 size_;
    /// Size mode.
    RenderTargetSizeMode sizeMode_{SIZE_ABSOLUTE};
    /// Multisampling level (1 = no multisampling).
    int multiSample_{1};
    /// Multisampling autoresolve flag.
    bool autoResolve_{true};
    /// Enabled flag.
    bool enabled_{true};
    /// Cube map flag.
    bool cubemap_{};
    /// Filtering flag.
    bool filtered_{};
    /// sRGB sampling/writing mode flag.
    bool sRGB_{};
    /// Should be persistent and not shared/reused between other buffers of same size.
    bool persistent_{};
};

/// Rendering path command.
struct URHO3D_API RenderPathCommand
{
    /// Read from an XML element.
    void Load(const XMLElement& element);
    /// Set a texture resource name. Can also refer to a rendertarget defined in the rendering path.
    void SetTextureName(TextureUnit unit, const String& name);
    /// Set a shader parameter.
    void SetShaderParameter(const String& name, const Variant& value);
    /// Remove a shader parameter.
    void RemoveShaderParameter(const String& name);
    /// Set number of output rendertargets.
    void SetNumOutputs(unsigned num);
    /// Set output rendertarget name and face index for cube maps.
    void SetOutput(unsigned index, const String& name, CubeMapFace face = FACE_POSITIVE_X);
    /// Set output rendertarget name.
    void SetOutputName(unsigned index, const String& name);
    /// Set output rendertarget face index for cube maps.
    void SetOutputFace(unsigned index, CubeMapFace face);
    /// Set depth-stencil output name. When empty, will assign a depth-stencil buffer automatically.
    void SetDepthStencilName(const String& name);

    /// Return texture resource name.
    const String& GetTextureName(TextureUnit unit) const;
    /// Return shader parameter.
    const Variant& GetShaderParameter(const String& name) const;

    /// Return number of output rendertargets.
    unsigned GetNumOutputs() const { return outputs_.Size(); }

    /// Return output rendertarget name.
    const String& GetOutputName(unsigned index) const;
    /// Return output rendertarget face index.
    CubeMapFace GetOutputFace(unsigned index) const;

    /// Return depth-stencil output name.
    const String& GetDepthStencilName() const { return depthStencilName_; }

    /// Tag name.
    String tag_;
    /// Command type.
    RenderCommandType type_{};
    /// Sorting mode.
    RenderCommandSortMode sortMode_{};
    /// Scene pass name.
    String pass_;
    /// Scene pass index. Filled by View.
    unsigned passIndex_{};
    /// Command/pass metadata.
    String metadata_;
    /// Vertex shader name.
    String vertexShaderName_;
    /// Pixel shader name.
    String pixelShaderName_;
    /// Vertex shader defines.
    String vertexShaderDefines_;
    /// Pixel shader defines.
    String pixelShaderDefines_;
    /// Textures.
    String textureNames_[MAX_TEXTURE_UNITS];
    /// %Shader parameters.
    HashMap<StringHash, Variant> shaderParameters_;
    /// Output rendertarget names and faces.
    Vector<Pair<String, CubeMapFace> > outputs_;
    /// Depth-stencil output name.
    String depthStencilName_;
    /// Clear flags. Affects clear command only.
    ClearTargetFlags clearFlags_{};
    /// Clear color. Affects clear command only.
    Color clearColor_;
    /// Clear depth. Affects clear command only.
    float clearDepth_{};
    /// Clear stencil value. Affects clear command only.
    unsigned clearStencil_{};
    /// Blend mode. Affects quad command only.
    BlendMode blendMode_{BLEND_REPLACE};
    /// Enabled flag.
    bool enabled_{true};
    /// Use fog color for clearing.
    bool useFogColor_{};
    /// Mark to stencil flag.
    bool markToStencil_{};
    /// Use lit base pass optimization for forward per-pixel lights.
    bool useLitBase_{true};
    /// Vertex lights flag.
    bool vertexLights_{};
    /// Event name.
    String eventName_;
};

/// Rendering path definition. A sequence of commands (e.g. clear screen, draw objects with specific pass) that yields the scene rendering result.
class URHO3D_API RenderPath : public RefCounted
{
public:
    /// Construct.
    RenderPath();
    /// Destruct.
    ~RenderPath() override;

    /// Clone the rendering path.
    SharedPtr<RenderPath> Clone();
    /// Clear existing data and load from an XML file. Return true if successful.
    bool Load(XMLFile* file);
    /// Append data from an XML file. Return true if successful.
    bool Append(XMLFile* file);
    /// Enable/disable commands and rendertargets by tag.
    void SetEnabled(const String& tag, bool active);
    /// Return true of any of render targets or commands with specified tag are enabled.
    bool IsEnabled(const String& tag) const;
    /// Return true if renderpath or command with given tag exists.
    bool IsAdded(const String& tag) const;
    /// Toggle enabled state of commands and rendertargets by tag.
    void ToggleEnabled(const String& tag);
    /// Assign rendertarget at index.
    void SetRenderTarget(unsigned index, const RenderTargetInfo& info);
    /// Add a rendertarget.
    void AddRenderTarget(const RenderTargetInfo& info);
    /// Remove a rendertarget by index.
    void RemoveRenderTarget(unsigned index);
    /// Remove a rendertarget by name.
    void RemoveRenderTarget(const String& name);
    /// Remove rendertargets by tag name.
    void RemoveRenderTargets(const String& tag);
    /// Assign command at index.
    void SetCommand(unsigned index, const RenderPathCommand& command);
    /// Add a command to the end of the list.
    void AddCommand(const RenderPathCommand& command);
    /// Insert a command at a position.
    void InsertCommand(unsigned index, const RenderPathCommand& command);
    /// Remove a command by index.
    void RemoveCommand(unsigned index);
    /// Remove commands by tag name.
    void RemoveCommands(const String& tag);
    /// Set a shader parameter in all commands that define it.
    void SetShaderParameter(const String& name, const Variant& value);

    /// Return number of rendertargets.
    unsigned GetNumRenderTargets() const { return renderTargets_.Size(); }

    /// Return number of commands.
    unsigned GetNumCommands() const { return commands_.Size(); }

    /// Return command at index, or null if does not exist.
    RenderPathCommand* GetCommand(unsigned index) { return index < commands_.Size() ? &commands_[index] : nullptr; }

    /// Return a shader parameter (first appearance in any command.)
    const Variant& GetShaderParameter(const String& name) const;

    /// Rendertargets.
    Vector<RenderTargetInfo> renderTargets_;
    /// Rendering commands.
    Vector<RenderPathCommand> commands_;
};

}
