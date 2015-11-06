#pragma once
#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Graphics/OctreeQuery.h>
#include <Urho3D/Graphics/VertexBuffer.h>
#include <Urho3D/Graphics/IndexBuffer.h>
#include <Urho3D/Graphics/Geometry.h>
#include <Urho3D/Graphics/Drawable.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Material.h>

using namespace Urho3D;

/// Vertex struct for tail  
struct URHO3D_API TailVertex
{
    Vector3 position_;
    unsigned color_;
    Vector2  uv_;
};

/// One billboard in the billboard set.
struct URHO3D_API Tail
{
    /// Position.
    Vector3 position;
    Vector3 worldRight;
    Vector3 forward;
};

static const unsigned MAX_TAILS = 65536 / 6;

/// Custom component that creates a tail
class URHO3D_API TailGenerator : public Drawable
{
	URHO3D_OBJECT(TailGenerator, Drawable);
public:
    /// Construct.
    TailGenerator(Context* context);
    /// Destruct.
    virtual ~TailGenerator();
    /// Register object factory.
    static void RegisterObject(Context* context);
    /// Process octree raycast. May be called from a worker thread.
    virtual void ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results);
    ///
    virtual void Update(const FrameInfo &frame);
    /// Calculate distance and prepare batches for rendering. May be called from worker thread(s), possibly re-entrantly.
    virtual void UpdateBatches(const FrameInfo& frame);
    /// Prepare geometry for rendering. Called from a worker thread if possible (no GPU update.)
    virtual void UpdateGeometry(const FrameInfo& frame);
    /// Return whether a geometry update is necessary, and if it can happen in a worker thread.
    virtual UpdateGeometryType GetUpdateGeometryType();

    virtual void  DrawDebugGeometry(DebugRenderer *debug, bool depthTest);

    /// Set material.
    void SetMaterial(Material* material);
    /// Set tail segment length
    void SetTailLength(float length);
    /// Get tail segment length
    float GetTailLength();
    /// Set count segments of all tail 
    void SetNumTails(unsigned num);
    /// Get count segments of all tail 
    unsigned GetNumTails();
    /// Set width scale of the tail
    void SetWidthScale(float scale);
    /// Set vertex blended color for tip of all tail. The alpha-value of new color resets by default to zero.
    void SetColorForTip(const Color& c);
    // Set vertex blended color for head of all tail. The alpha-value of new color resets by default to one.
    void SetColorForHead(const Color& c);
    /// Set material attribute.
    void SetMaterialAttr(const ResourceRef& value);
    /// Return material attribute.
    ResourceRef GetMaterialAttr() const;
    
    /// Get whether to draw the vertical strip or not
    bool GetDrawVertical() const { return vertical_; }
    /// Get whether to draw the horizontal strip or not
    bool GetDrawHorizontal() const { return horizontal_; }
    /// Get whether or not this tail is matching node direction vectors
    bool GetMatchNodeOrientation() const { return matchNode_; }
    /// Set whether to draw the vertical strip or not
    void SetDrawVertical(bool value);
    /// Set whether to draw the horizontal strip or not
    void SetDrawHorizontal(bool value);
    /// Set whether or not this tail is matching node direction vectors
    void SetMatchNodeOrientation(bool value);
	///
    float GetWidthScale() const { return scale_; }
    unsigned  GetNumTails() const { return tailNum_; }
    float GetTailLength() const { return tailLength_;  }
    const Color& GetColorForHead() const { return tailHeadColor; }
    const Color& GetColorForTip() const { return tailTipColor;  }

protected:
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
    /// Recalculate the world-space bounding box.
    virtual void OnWorldBoundingBoxUpdate();
    /// Mark vertex buffer to need an update.
    void MarkPositionsDirty();
    /// Tails.
    PODVector<Tail> tails_;
    PODVector<Tail> fullPointPath;

private:
    /// Resize TailGenerator vertex and index buffers.
    void UpdateBufferSize();
    /// Rewrite TailGenerator vertex buffer.
    void UpdateVertexBuffer(const FrameInfo& frame);
	/// Update/Rebuild tail mesh only if position changed (called by UpdateBatches())
	void UpdateTail();
    /// Geometry.
    SharedPtr<Geometry> geometry_;
    /// Vertex buffer.
    SharedPtr<VertexBuffer> vertexBuffer_;
    /// Index buffer.
    SharedPtr<IndexBuffer> indexBuffer_;
    /// Transform matrices for position and orientation.
    Matrix3x4 transforms_[2];
    /// Buffers need resize flag.
    bool bufferSizeDirty_;
    /// Vertex buffer needs rewrite flag.
    bool bufferDirty_;
	///
	bool forceUpdateVertexBuffer_;
	///
	bool vertical_;
	///
	bool matchNode_;
	///
	bool horizontal_;
    /// Previous position of tail
    Vector3 previousPosition_;
    ///
	float tailLength_;
    ///
	float scale_;
	///
	unsigned tailNum_;
	///
    Vector<TailVertex> tailMesh;
    ///
	Vector<Tail> activeTails;
	///
	Vector3 bbmin;
	///
	Vector3 bbmax;
	///
    Color tailTipColor;
    ///
	Color tailHeadColor;
};
