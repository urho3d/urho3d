#include <Urho3D/Container/List.h>
#include "CustomMesh.h"

namespace Urho3D
{
class TailGenerator : public CustomMesh
{
    URHO3D_OBJECT(TailGenerator, Drawable);
public:
    TailGenerator(Context* context);
    ~TailGenerator();
    static void RegisterObject(Context *context);

    void SetEndNodeName(const String& name);
    void SetWidth(float width);
    void SetTailNum(int num);
    void SetStartColor(const Color& startInitColor, const Color& startDeltaColor);
    void SetEndColor(const Color& endInitColor, const Color&endDeltaColor);
    void SetArcValue(float arcInc, float maxArc);
    void SetRelativePosition(bool b);

private:
    void Update(float dt);
    void HandleScenePostUpdate(StringHash eventType, VariantMap& eventData);
    void UpdateGeometry();
    void UpdateSegmentColour( const float dt );
    void UpdateSegmentCount( const float dt );
    void AddSegment( const Vector3& vStart, const Vector3& vEnd );
    void UpdatePosition(bool bReset);
    void MarkDirty();
    void ClearTrail();

    virtual void UpdateVertexBuffer(const FrameInfo& frame);
    virtual void OnWorldBoundingBoxUpdate();
	virtual void OnSetEnabled();
	virtual void OnSceneSet(Scene* scene);

private:
    /// public attributes
    float                           width_;

    /// a trail segment
    struct TrailSegment
    {
        /// start position
        Vector3 segmentStart;
        /// end position
        Vector3 segmentEnd;
        /// current segment start color
        Color segmentStartColor;
        /// current segment end color
        Color segmentEndColor;
        TrailSegment() {};
        TrailSegment( const Vector3& v1,
                      const Vector3& v2,
                      const Color& ssc,
                      const Color& sec )
                    :
                    segmentStart(v1),
                    segmentEnd(v2),
                    segmentStartColor(ssc),
                    segmentEndColor(sec)
                {
                };
    }; // end TrailSegment struct declaration
    /// typedef for a list of trail segments
    typedef List<TrailSegment> TrailSegmentList;

    ///!< the maximum number of segments the trail will consist of
    size_t                      maxSegmentCount_;
    /// the list of currently active trail segments
    TrailSegmentList            segmentList_;

    /// the initial color of start segments
    Color segmentStartInitialColor_;
    /// the initial color of end segments
    Color segmentEndInitialColor_;
    /// how the color of start segments will change over time
    Color segmentStartColorChange_;
    /// how the color of end segments will change over time
    Color segmentEndColorChange_;

    ///when to add another segment
    float   rNextSegmentUpdate_;
    ///our arc-length rollover from the previous frame
    float   rCurrentArcLength_;

    ///weapon start two frames ago ( for lagrange poly )
    Vector3 vLastLastStart_;
    Vector3 vLastLastEnd_;
    int     iNumIterations_;

    float   rArcInc_;
    float   rMaxArc_;


    Vector3 vStartPosition_;
    Vector3 vEndPosition_;
    Vector3 vLastStartPosition_;
    Vector3 vLastEndPosition_;

    WeakPtr<Node>       endNode_;
    String              endNodeName_;
};
}
