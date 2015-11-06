#include "TailGenerator.h"

TailGenerator::TailGenerator(Context* context) : 
                Drawable(context, DRAWABLE_GEOMETRY)
{

    matchNode_ = false;

    geometry_ = SharedPtr<Geometry>(new Geometry(context));
	vertexBuffer_ = SharedPtr<VertexBuffer>(new VertexBuffer(context));
	indexBuffer_ = SharedPtr<IndexBuffer>(new IndexBuffer(context));

    geometry_->SetVertexBuffer(0, vertexBuffer_, MASK_POSITION | MASK_COLOR | MASK_TEXCOORD1);
    geometry_->SetIndexBuffer(indexBuffer_);

    indexBuffer_->SetShadowed(false);
	
	transforms_[0] = Matrix3x4::IDENTITY;
	transforms_[1] = Matrix3x4(Vector3::ZERO, Quaternion(0, 0, 0), Vector3::ONE);
	
    batches_.Resize(1);
    batches_[0].geometry_ = geometry_;
    batches_[0].geometryType_ = GEOM_BILLBOARD;
    batches_[0].worldTransform_ = &transforms_[0];
	batches_[0].numWorldTransforms_ = 2;

    forceUpdateVertexBuffer_ = false;
    previousPosition_ = Vector3::ZERO;

    tailNum_ = 10;
    // for debug
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    SetMaterial(cache->GetResource<Material>("Materials/TailGenerator.xml"));
    tailLength_ = 0.25f;
    scale_ = 1.0f; // default side scale
    tailTipColor = Color(1.0f, 1.0f, 1.0f, 1.0f);
    tailHeadColor = Color(1.0f, 1.0f, 1.0f, 1.0f);

    forceUpdateVertexBuffer_ = false;

    bbmax = Vector3::ZERO;
    bbmin = Vector3::ZERO;
    vertical_ = horizontal_ = true;
    
}

TailGenerator::~TailGenerator()
{
}

void TailGenerator::RegisterObject(Context* context)
{
    context->RegisterFactory<TailGenerator>();

    URHO3D_COPY_BASE_ATTRIBUTES(Drawable);
	URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Material", GetMaterialAttr, SetMaterialAttr, ResourceRef, ResourceRef(Material::GetTypeStatic()), AM_DEFAULT);
	URHO3D_ACCESSOR_ATTRIBUTE("Segments", GetNumTails, SetNumTails, unsigned int, 10, AM_DEFAULT);
	URHO3D_ACCESSOR_ATTRIBUTE("Length", GetTailLength, SetTailLength, float, 0.25f, AM_DEFAULT);
	URHO3D_ACCESSOR_ATTRIBUTE("Width", GetWidthScale, SetWidthScale, float, 1.0f, AM_DEFAULT);
	URHO3D_ACCESSOR_ATTRIBUTE("Start Color", GetColorForHead, SetColorForHead, Color, Color::WHITE, AM_DEFAULT);
	URHO3D_ACCESSOR_ATTRIBUTE("End Color", GetColorForTip, SetColorForTip, Color, Color::WHITE, AM_DEFAULT);
	URHO3D_ACCESSOR_ATTRIBUTE("Draw Vertical", GetDrawVertical, SetDrawVertical, bool, true, AM_DEFAULT);
	URHO3D_ACCESSOR_ATTRIBUTE("Draw Horizontal", GetDrawHorizontal, SetDrawHorizontal, bool, true, AM_DEFAULT);
	URHO3D_ACCESSOR_ATTRIBUTE("Match Node Rotation", GetMatchNodeOrientation, SetMatchNodeOrientation, bool, false, AM_DEFAULT);
}

void TailGenerator::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results)
{
    // If no billboard-level testing, use the Drawable test
    if (query.level_ < RAY_TRIANGLE)
    {
        Drawable::ProcessRayQuery(query, results);
        return;
    }
}

void TailGenerator::Update(const FrameInfo &frame)
{
	Drawable::Update(frame);
}

void TailGenerator::UpdateTail()
{
    Vector3 wordPosition = node_->GetWorldPosition();
    float path = (previousPosition_ - wordPosition).Length();

    if (path > tailLength_) 
    {
        // новая точка пути
        Tail newPoint;
        newPoint.position = wordPosition;
        
        Vector3 forwardmotion = matchNode_ ? GetNode()->GetWorldDirection() : (previousPosition_ - wordPosition).Normalized();
        Vector3 rightmotion = matchNode_ ? GetNode()->GetWorldRight() : forwardmotion.CrossProduct(Vector3::UP);
        rightmotion.Normalize();
        newPoint.worldRight = rightmotion;
        newPoint.forward = forwardmotion;
        
        //forceBuildMeshInWorkerThread_ = true;
        forceUpdateVertexBuffer_ = true;
        previousPosition_ = wordPosition;
        fullPointPath.Push(newPoint);    // Весь путь, все точки за все время работы компонента.
        //knots.Push(wordPosition);        // Для сплайна опорные
    }
}

void  TailGenerator::DrawDebugGeometry(DebugRenderer *debug, bool depthTest)
{
    Drawable::DrawDebugGeometry(debug, depthTest);
    
    debug->AddNode(node_);

    for (unsigned i = 0; i < tails_.Size()-1; i++)
    {
        debug->AddLine(tails_[i].position, tails_[i+1].position, Color(1,1,1).ToUInt(), false );      
    }
}

void TailGenerator::UpdateBatches(const FrameInfo& frame) 
{
	// Update tail's mesh if needed
	UpdateTail(); 

	// Update information for renderer about this drawable 
    distance_ = frame.camera_->GetDistance(GetWorldBoundingBox().Center());
    batches_[0].distance_ = distance_;

    //batches_[0].numWorldTransforms_ = 2;

    // TailGenerator positioning
    //transforms_[0] = Matrix3x4::IDENTITY;
    // TailGenerator rotation
    //transforms_[1] = Matrix3x4(Vector3::ZERO, Quaternion(0, 0, 0), Vector3::ONE);
}

void TailGenerator::UpdateGeometry(const FrameInfo& frame)
{
    if (bufferSizeDirty_ || indexBuffer_->IsDataLost())
        UpdateBufferSize();

    if (bufferDirty_ || vertexBuffer_->IsDataLost() || forceUpdateVertexBuffer_)
        UpdateVertexBuffer(frame);
}

UpdateGeometryType TailGenerator::GetUpdateGeometryType()
{	
    if (bufferDirty_ || bufferSizeDirty_ || vertexBuffer_->IsDataLost() || indexBuffer_->IsDataLost()|| forceUpdateVertexBuffer_)
        return UPDATE_MAIN_THREAD;
    else
        return UPDATE_NONE;
}

void TailGenerator::SetMaterial(Material* material)
{
    batches_[0].material_ = material;
    MarkNetworkUpdate();
}

void TailGenerator::OnNodeSet(Node* node)
{
    Drawable::OnNodeSet(node);
}

void TailGenerator::OnWorldBoundingBoxUpdate() 
{
    //worldBoundingBox_.Define(-M_LARGE_VALUE, M_LARGE_VALUE);
    worldBoundingBox_.Merge(bbmin);
    worldBoundingBox_.Merge(bbmax);
    worldBoundingBox_.Merge(node_->GetWorldPosition());
    
}

/// Resize TailGenerator vertex and index buffers.
void TailGenerator::UpdateBufferSize() 
{
    unsigned numTails = tailNum_;

    if (!numTails)
        return;

    int vertsPerSegment = (vertical_ && horizontal_ ? 4 : (!vertical_ && !horizontal_ ? 0 : 2));
    int degenerateVertCt = 0;
    if (vertsPerSegment > 2)
        degenerateVertCt += 2; //requires two degenerate triangles

    if (vertexBuffer_->GetVertexCount() != (numTails * vertsPerSegment))
    {
        vertexBuffer_->SetSize((numTails * vertsPerSegment), MASK_POSITION | MASK_COLOR | MASK_TEXCOORD1, true);

    }
    if (indexBuffer_->GetIndexCount() != (numTails * vertsPerSegment) + degenerateVertCt)
    {
        indexBuffer_->SetSize((numTails * vertsPerSegment) + degenerateVertCt, false);
    }

    bufferSizeDirty_ = false;
    bufferDirty_ = true;

    // Indices do not change for a given tail generator capacity
    unsigned short* dest = (unsigned short*)indexBuffer_->Lock(0, (numTails * vertsPerSegment) + degenerateVertCt, true);
    if (!dest)
        return;

    unsigned vertexIndex = 0;
    if (horizontal_)
    {
        unsigned stripsLen = numTails;
        while (stripsLen--)
        {

            dest[0] = vertexIndex;
            dest[1] = vertexIndex + 1;
            dest += 2;
            
            // degenerate triangle vert on horizontal
            if (vertical_ && stripsLen == 0)
            {
                dest[0] = vertexIndex + 1;
                dest += 1;
            }
            vertexIndex += 2;
        }
    }
    if (vertical_)
    {
        unsigned stripsLen = numTails;
        while (stripsLen--)
        {
            // degenerate triangle vert on vertical
            if (horizontal_ && stripsLen == (numTails - 1))
            {
                dest[0] = vertexIndex;
                dest += 1;
            }

            dest[0] = vertexIndex;
            dest[1] = vertexIndex + 1;
            dest += 2;
            vertexIndex += 2;
        }
    }

    indexBuffer_->Unlock();
    indexBuffer_->ClearDataLost();


}

/// Rewrite TailGenerator vertex buffer.
void TailGenerator::UpdateVertexBuffer(const FrameInfo& frame) 
{
    unsigned fullPointPathSize = fullPointPath.Size();
    unsigned currentVisiblePathSize = tailNum_;

    // Clear previous mesh data
    tailMesh.Clear();

    // build tail

    // if tail path is short and nothing to draw, exit
    if (fullPointPathSize < 2) return;

    activeTails.Clear();

    unsigned min_i = fullPointPathSize < currentVisiblePathSize ? 0 : fullPointPathSize - currentVisiblePathSize;
    // Step 1 : collect actual point's info for build tail path
    for (unsigned i = min_i; i < fullPointPathSize - 1; i++)
    {
        activeTails.Push(fullPointPath[i]);

        Vector3 &p = fullPointPath[i].position;

        // Math BoundingBox based on actual point
        if (p.x_ < bbmin.x_) bbmin.x_ = p.x_;
        if (p.y_ < bbmin.y_) bbmin.y_ = p.y_;
        if (p.z_ < bbmin.z_) bbmin.z_ = p.z_;

        if (p.x_ > bbmax.x_) bbmax.x_ = p.x_;
        if (p.y_ > bbmax.y_) bbmax.y_ = p.y_;
        if (p.z_ > bbmax.z_) bbmax.z_ = p.z_;

    }

    if (activeTails.Size() < 2) return;

    Vector<Tail> &t = activeTails;

    // generate strips of tris
    TailVertex v;

    float mixFactor = 1.0f / activeTails.Size();


    // Forward part of tail (strip in xz plane)
    if (horizontal_)
    {
        for (unsigned i = 0; i < activeTails.Size() || i < tailNum_; ++i)
        {
            unsigned sub = i < activeTails.Size() ? i : activeTails.Size() - 1;
            Color c = tailTipColor.Lerp(tailHeadColor, mixFactor * i);
            v.color_ = c.ToUInt();
            v.uv_ = Vector2(1.0f, 0.0f);
            v.position_ = t[sub].position + t[sub].worldRight * scale_;
            tailMesh.Push(v);

            //v.color_ = c.ToUInt();
            v.uv_ = Vector2(0.0f, 1.0f);
            v.position_ = t[sub].position - t[sub].worldRight * scale_;
            tailMesh.Push(v);
        }
    }

    // Upper part of tail (strip in xy-plane)
    if (vertical_)
    {
        for (unsigned i = 0; i < activeTails.Size() || i < tailNum_; ++i)
        {
            unsigned sub = i < activeTails.Size() ? i : activeTails.Size() - 1;
            Color c = tailTipColor.Lerp(tailHeadColor, mixFactor * i);
            v.color_ = c.ToUInt();
            v.uv_ = Vector2(1.0f, 0.0f);
            Vector3 up = t[sub].forward.CrossProduct(t[sub].worldRight);
            up.Normalize();
            v.position_ = t[sub].position + up * scale_;
            tailMesh.Push(v);

            //v.color_ = c.ToUInt();
            v.uv_ = Vector2(0.0f, 1.0f);
            v.position_ = t[sub].position - up * scale_;
            tailMesh.Push(v);

        }
    }


    // copy new mesh to vertex buffer
    unsigned meshVertexCount = tailMesh.Size();
    batches_[0].geometry_->SetDrawRange(TRIANGLE_STRIP, 0, meshVertexCount + (horizontal_ && vertical_ ? 2 : 0), false);
    // get pointer
    TailVertex* dest = (TailVertex*)vertexBuffer_->Lock(0, meshVertexCount, true);
    if (!dest)
        return;
    // copy to vertex buffer
    memcpy(dest, &tailMesh[0], tailMesh.Size() * sizeof(TailVertex));

    vertexBuffer_->Unlock();
    vertexBuffer_->ClearDataLost();

    bufferDirty_ = false;

    // unmark flag
    forceUpdateVertexBuffer_ = false;
}


void TailGenerator::SetTailLength(float length) 
{
    
    tailLength_ = length;
}

void TailGenerator::SetColorForTip(const Color& c)
{
    tailTipColor = Color(c.r_, c.g_, c.b_, 0.0f);
}

void TailGenerator::SetColorForHead(const Color& c)
{
    tailHeadColor = Color(c.r_, c.g_, c.b_, 1.0f);
}

void TailGenerator::SetNumTails(unsigned num) 
{
    // Prevent negative value being assigned from the editor
    if (num > M_MAX_INT)
        num = 0;

    if (num > MAX_TAILS)
        num = MAX_TAILS;

    bufferSizeDirty_ = true;
    tailNum_ = num;
}

unsigned TailGenerator::GetNumTails() 
{
    return tailNum_;
}

void TailGenerator::SetDrawVertical(bool value)
{
    vertical_ = value;
    //SetupBatches();
}

void TailGenerator::SetDrawHorizontal(bool value)
{
    horizontal_ = value;
    //SetupBatches();
}

void TailGenerator::SetMatchNodeOrientation(bool value)
{
    matchNode_ = value;
}

void TailGenerator::MarkPositionsDirty()
{
    Drawable::OnMarkedDirty(node_);
    bufferDirty_ = true;
}

void TailGenerator::SetMaterialAttr(const ResourceRef& value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    SetMaterial(cache->GetResource<Material>(value.name_));
}

ResourceRef TailGenerator::GetMaterialAttr() const
{
    return GetResourceRef(batches_[0].material_, Material::GetTypeStatic());
}

void TailGenerator::SetWidthScale(float scale)
{
    scale_ = scale;
}