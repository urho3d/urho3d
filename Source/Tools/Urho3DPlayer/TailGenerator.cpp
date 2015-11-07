#include "TailGenerator.h"
#include "ExtUtil.h"
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/DebugNew.h>

namespace Urho3D
{
TailGenerator::TailGenerator(Context *context)
    :CustomMesh(context)
    ,width_(2.0f)
    ,maxSegmentCount_(50)
    ,rNextSegmentUpdate_(0)
    ,rCurrentArcLength_(0)
    ,vLastLastStart_(Vector3::ZERO)
    ,vLastLastEnd_(Vector3::ZERO)
    ,iNumIterations_(0)
    ,rArcInc_(0.5f)
    ,rMaxArc_(5.0f)
{
    segmentStartInitialColor_ = Color(0.6f,0.5f,0.8f,1);
    segmentEndInitialColor_ = Color(1.0f,0.2f,1.0f,1);
    segmentStartColorChange_ = Color(5.0f,5.0f,5.0f,20.0f);
    segmentEndColorChange_ = Color(5.0f,5.0f,5.0f,20.0f);
    relativePosition_ = false;
}

TailGenerator::~TailGenerator()
{

}

void TailGenerator::RegisterObject(Context *context)
{
    context->RegisterFactory<TailGenerator>();
    URHO3D_COPY_BASE_ATTRIBUTES(Drawable);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Material", GetMaterialAttr, SetMaterialAttr, ResourceRef, ResourceRef(Material::GetTypeStatic()), AM_DEFAULT);
#if 0
    URHO3D_ATTRIBUTE("Width", float, width_, 0.8f, AM_DEFAULT);
    URHO3D_ATTRIBUTE("MaxSegmentCount", int, maxSegmentCount_, 50, AM_DEFAULT);
    URHO3D_ATTRIBUTE("StartInitColor", Color, segmentStartInitialColor_, Color(0.8f,0.8f,0.8f,1), AM_DEFAULT);
    URHO3D_ATTRIBUTE("EndInitColor", Color, segmentEndInitialColor_, Color(0.6f,0.5f,0.0f,1), AM_DEFAULT);
    URHO3D_ATTRIBUTE("StartColorDelta", float, segmentStartColorChange_, Color(5.0f,5.0f,5.0f,20.0f), AM_DEFAULT);
    URHO3D_ATTRIBUTE("EndColorDelta", float, segmentEndColorChange_, Color(5.0f,5.0f,5.0f,20.0f), AM_DEFAULT);
    URHO3D_ATTRIBUTE("ArcIncrement", float, rArcInc_, 0.1f, AM_DEFAULT);
    URHO3D_ATTRIBUTE("MaxArc", float, rMaxArc_, 10.0f, AM_DEFAULT);
#endif
}


void TailGenerator::HandleScenePostUpdate(StringHash eventType, VariantMap &eventData)
{
    using namespace ScenePostUpdate;
    Update(eventData[P_TIMESTEP].GetFloat());
}

void TailGenerator::Update(float dt)
{
    if(!IsEnabledEffective() && segmentList_.Empty())
        return;

    UpdatePosition(false);
    UpdateSegmentColour(dt);
    UpdateSegmentCount(dt);
    MarkDirty();
}

void TailGenerator::OnSceneSet(Scene* scene)
{
	if (scene && IsEnabledEffective())
		SubscribeToEvent(scene, E_SCENEPOSTUPDATE, URHO3D_HANDLER(TailGenerator, HandleScenePostUpdate));
	else if (!scene)
		UnsubscribeFromEvent(E_SCENEPOSTUPDATE);
    CustomMesh::OnSceneSet(scene);
}


void TailGenerator::OnSetEnabled()
{
	Scene* scene = GetScene();
	if (scene)
	{
		if (IsEnabledEffective())
        {
            UpdatePosition(true);
			SubscribeToEvent(scene, E_SCENEPOSTUPDATE, URHO3D_HANDLER(TailGenerator, HandleScenePostUpdate));
        }
		else
        {
            ClearTrail();
			UnsubscribeFromEvent(scene, E_SCENEPOSTUPDATE);
        }
	}
    CustomMesh::OnSetEnabled();
}

void TailGenerator::UpdateSegmentColour(const float dt)
{
    // iterate over the current segments, apply alpha change
    for(TrailSegmentList::Iterator it = segmentList_.Begin();
        it != segmentList_.End();)
    {
        TrailSegment& seg = (*it);
        seg.segmentStartColor = SubColor(seg.segmentStartColor, segmentStartColorChange_ * dt);
        seg.segmentEndColor = SubColor(seg.segmentEndColor, segmentEndColorChange_ * dt);
        seg.segmentStartColor = SaturateColor(seg.segmentStartColor);
        seg.segmentEndColor = SaturateColor(seg.segmentEndColor);
        if(seg.segmentStartColor == Color(0,0,0,0)
          && seg.segmentEndColor == Color(0,0,0,0))
        {
            it = segmentList_.Erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void TailGenerator::UpdateSegmentCount(const float dt)
{
    const Vector3& vStart0 = vLastStartPosition_;
    const Vector3& vEnd0 = vLastEndPosition_;

    const Vector3& vStart1 = vStartPosition_;
    const Vector3& vEnd1 = vEndPosition_;

    //in the first two ierations we do not have sufficient information
    //about the path of the weapon, ignore curve-fitting
    if ( iNumIterations_ <= 1 )
    {
        AddSegment( vStart1, vEnd1 );
        rCurrentArcLength_ = 0.0f;
        vLastLastStart_ = vStart0;
        vLastLastEnd_ = vEnd0;
        ++iNumIterations_;
        return;
    }

    //compute the direction of the weapon ( from hilt to tip )
    //for both this and last frame
    Vector3 vDir0 = vEnd0 - vStart0;
    Vector3 vDir1 = vEnd1 - vStart1;
    float rRadius = width_;
    float rInvRadius = 1/rRadius;

    //normalize directions
    vDir0 *= rInvRadius;
    vDir1 *= rInvRadius;

    //compute vector from last tip position to current
    Vector3 vMoveEnd = vEnd1 - vEnd0;

    //compute the distance the tip is going to move this frame
    float rMoveEndDistance = vMoveEnd.Length();

    //temp store our prev arc distance
    float rPrevArcLength = rCurrentArcLength_;
    //compute rough estimate of arc distance
    rCurrentArcLength_ += rMoveEndDistance;

    //if we exceed the max arc length, draw normally
    if ( rCurrentArcLength_ > rMaxArc_ )
    {
        AddSegment( vStart1, vEnd1 );
        vLastLastStart_ = vStart0;
        vLastLastEnd_ = vEnd0;
        ++iNumIterations_;
        return;
    }

    //****pre-compute local parabola of movement
    // for lagrange interpolating polynomial****

    //compute the distance and direction the tip moved in the last 2 frames
    // ( = base of triangle )

    Vector3 vMoveEndBaseDir = vEnd1 - vLastLastEnd_;

    vMoveEndBaseDir.Normalize();
    //compute length of projection of vEnd0 onto vMoveEndBase
    float rMidBaseLength = (vMoveEndBaseDir).DotProduct( vMoveEnd );
    //Real rMidBaseLength = (-vMoveEndBaseDir).dotProduct( -vMoveEnd );

    //project point vEnd0 onto vMoveEndBase
    Vector3 vMidBase = vEnd1 + vMoveEndBaseDir * -rMidBaseLength;

    //compute local up vector
    Vector3 vMidBaseUp = vEnd0 - vMidBase;

    vMidBaseUp.Normalize();

    //compute local right vector
    // right = forward x up
    Vector3 vMidBaseRight = vMoveEndBaseDir.CrossProduct( vMidBaseUp );
    vMidBaseRight.Normalize(); //TODO: is norm necessary?

    //compute local curve-space matrix
    Matrix3 xCurveRot;
    xCurveRot.m00_ = vMoveEndBaseDir.x_;
    xCurveRot.m10_ = vMoveEndBaseDir.y_;
    xCurveRot.m20_ = vMoveEndBaseDir.z_;

    xCurveRot.m01_ = vMidBaseUp.x_;
    xCurveRot.m11_ = vMidBaseUp.y_;
    xCurveRot.m21_ = vMidBaseUp.z_;

    xCurveRot.m02_ = vMidBaseRight.x_;
    xCurveRot.m12_ = vMidBaseRight.y_;
    xCurveRot.m22_ = vMidBaseRight.z_;

    Matrix4 xCurveSpace = Matrix4( xCurveRot );
    xCurveSpace.SetTranslation(vMidBase );

    //transform points of the parabola into local space
    //( because the parabola MUST be a 1-to-1 function for Lagrange interp )
    Vector3 vLocalEnd0 = WorldToLocal( xCurveSpace, vLastLastEnd_ );
    Vector3 vLocalEnd1 = WorldToLocal( xCurveSpace, vEnd0 );
    Vector3 vLocalEnd2 = WorldToLocal( xCurveSpace, vEnd1 );

    //store parabola so lagrange function can easily access the data
    float pArrayX[3], pArrayY[3];
    pArrayX[0] = vLocalEnd0.x_;
    pArrayX[1] = vLocalEnd1.x_;
    pArrayX[2] = vLocalEnd2.x_;

    pArrayY[0] = vLocalEnd0.y_;
    pArrayY[1] = vLocalEnd1.y_;
    pArrayY[2] = vLocalEnd2.y_;

    float rCurArcInc = rArcInc_ - rPrevArcLength;

    while ( rCurrentArcLength_ >= rArcInc_ )
    {
        //compute the ratio that we have moved along the approximated arc
        float rMoveRatio = rCurArcInc / rMoveEndDistance;

        //compute the local x movement along the parabola
        float rMoveX = rMoveRatio * rMidBaseLength;

        //compute the local y movement along the parabola
        float rMoveY = LagrangeInterpolatingPolynomial( pArrayX, pArrayY, 3, rMoveX );

        if ( rMoveY > rMoveEndDistance ) return;

        //compute the point of the motion trail at the tip
        Vector3 vEndPoint = vMidBase
                            +   vMoveEndBaseDir * rMoveX
                            +   vMidBaseUp * rMoveY;

        //interp between the direction of our weapon last frame and this frame
        Vector3 vDir = vDir0 + ( vDir1 - vDir0 ) * rMoveRatio;

        //compute the point of the motion trail at the hilt
        Vector3 vStartPoint = vEndPoint - vDir * rRadius;

        //add the segment
        AddSegment( vStartPoint, vEndPoint );

        //decrement our current arc length value
        rCurrentArcLength_ -= rArcInc_;

        //increment our arc interpolation value
        rCurArcInc += rArcInc_;
    }

    //store prev position data
    vLastLastStart_ = vStart0;
    vLastLastEnd_ = vEnd0;

    //increment iteration count
    ++iNumIterations_;
}

void TailGenerator::AddSegment(const Vector3 &vStart, const Vector3 &vEnd)
{
    // throw away the last element if the maximum number of segments is used
    if( segmentList_.Size() >= maxSegmentCount_ )
    {
        segmentList_.Pop();
    }

    //add the segment
    TrailSegment pNewSegment(   vEnd,
                                vStart,
                                segmentStartInitialColor_,
                                segmentEndInitialColor_ );
    segmentList_.PushFront(pNewSegment );
}

void TailGenerator::ClearTrail()
{
    segmentList_.Clear();
    rCurrentArcLength_ = 0;
    iNumIterations_ = 0;
    bufferDirty_ = false;
}

void TailGenerator::UpdatePosition(bool bReset)
{
    if(bReset)
    {
        vStartPosition_ = node_->GetWorldPosition();
        if(endNode_.NotNull())
        {
            vEndPosition_ = endNode_->GetWorldPosition();
        }
        else
        {
            vEndPosition_ = node_->LocalToWorld(Vector3(0,width_,0));
        }
        vLastStartPosition_ = vStartPosition_;
        vLastEndPosition_ = vEndPosition_;
    }
    else
    {
        vLastStartPosition_ = vStartPosition_;
        vLastEndPosition_ = vEndPosition_;
        vStartPosition_ = node_->GetWorldPosition();
        if(endNode_.NotNull())
        {
            vEndPosition_ = endNode_->GetWorldPosition();
        }
        else
        {
            vEndPosition_ = node_->LocalToWorld(Vector3(0,width_,0));
        }
    }
}

void TailGenerator::MarkDirty()
{
    bufferDirty_ = true;
    MarkForUpdate();
}

void TailGenerator::UpdateVertexBuffer( const FrameInfo& frame )
{
    UpdateGeometry();
}

void TailGenerator::OnWorldBoundingBoxUpdate()
{
    if (IsEnabledEffective())
    {
        Sphere sphere(node_->GetWorldPosition(), 5.0f);
        worldBoundingBox_.Define(sphere);
    }
    else {
        worldBoundingBox_.Clear();
        worldBoundingBox_.Merge(node_->GetWorldPosition());
    }
}

void TailGenerator::UpdateGeometry()
{
    bufferDirty_ = false;
    bufferSizeDirty_ = false;

    if(!IsEnabledEffective())
        return;

    unsigned    iSegmentCount = 0;
    unsigned    iSegmentSize = segmentList_.Size();
    float       rInvSegmentSize = 1/(float)(iSegmentSize);
    if(iSegmentSize < 2)
        return;

    unsigned vNum = iSegmentSize * 2;
    unsigned iNum = (iSegmentSize - 1) * 2 * 3;
    if (vertexBuffer_->GetVertexCount() != vNum)
        vertexBuffer_->SetSize(vNum, MASK_POSITION | MASK_COLOR | MASK_TEXCOORD1 , true);
    if (indexBuffer_->GetIndexCount() != iNum)
        indexBuffer_->SetSize(iNum, false);

    batches_[0].geometry_->SetDrawRange(TRIANGLE_LIST, 0, iNum, false);

    float* dest = (float*)vertexBuffer_->Lock(0, vNum, true);
    if (!dest)
        return;

    unsigned vertexSize = vertexBuffer_->GetVertexSize();

    for (TrailSegmentList::Iterator iter = segmentList_.Begin();
        iter != segmentList_.End();
        ++iter)
    {
        TrailSegment& seg = *iter;
        float u = iSegmentCount * rInvSegmentSize;

        float* v0 = dest + (2*iSegmentCount+0)*vertexSize/4;
        float* v1 = dest + (2*iSegmentCount+1)*vertexSize/4;

        Vector3 worldPt0 = seg.segmentStart;
        Vector3 worldPt1 = seg.segmentEnd;
        Vector3 pt0 = relativePosition_ ? InverseTransformPoint(worldPt0, node_) : worldPt0;
        Vector3 pt1 = relativePosition_ ? InverseTransformPoint(worldPt1, node_) : worldPt1;
        Vector2 uv0(u, 0);
        *v0++ = pt0.x_;
        *v0++ = pt0.y_;
        *v0++ = pt0.z_;
        *((unsigned*)v0) = seg.segmentStartColor.ToUInt(); v0++;
        *v0++ = uv0.x_;
        *v0++ = uv0.y_;

        Vector2 uv1(u, 1);
        *v1++ = pt1.x_;
        *v1++ = pt1.y_;
        *v1++ = pt1.z_;
        *((unsigned*)v1) = seg.segmentEndColor.ToUInt(); v1++;
        *v1++ = uv1.x_;
        *v1++ = uv1.y_;

        ++iSegmentCount;
    }

    vertexBuffer_->Unlock();
    vertexBuffer_->ClearDataLost();


    unsigned short* iDest = (unsigned short*)indexBuffer_->Lock(0, iNum, true);
    if (!iDest)
        return;

    for (unsigned i=0;i<iNum/6;++i)
    {
        iDest[i * 6 + 0] = i * 2;
        iDest[i * 6 + 1] = i * 2 + 1;
        iDest[i * 6 + 2] = i * 2 + 2;
        iDest[i * 6 + 3] = i * 2 + 2;
        iDest[i * 6 + 4] = i * 2 + 1;
        iDest[i * 6 + 5] = i * 2 + 3;
    }

    indexBuffer_->Unlock();
    indexBuffer_->ClearDataLost();

}

void TailGenerator::SetEndNodeName(const String& name)
{
    endNode_ = node_->GetChild(name, true);
}

void TailGenerator::SetWidth(float width)
{
    width_ = width;
}

void TailGenerator::SetTailNum(int num)
{
    maxSegmentCount_ = num;
}

void TailGenerator::SetStartColor(const Color& startInitColor, const Color& startDeltaColor)
{
    segmentStartInitialColor_ = startInitColor;
    segmentStartColorChange_ = startDeltaColor;
}

void TailGenerator::SetEndColor(const Color& endInitColor, const Color& endDeltaColor)
{
    segmentEndInitialColor_ = endInitColor;
    segmentEndColorChange_ = endDeltaColor;
}

void TailGenerator::SetArcValue(float arcInc, float maxArc)
{
    rArcInc_ = arcInc;
    rMaxArc_ = maxArc;
}

void TailGenerator::SetRelativePosition(bool b)
{
    relativePosition_ = b;
}

}



















