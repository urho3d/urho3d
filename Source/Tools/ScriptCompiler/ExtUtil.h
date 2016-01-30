#pragma once
#include <Urho3D/Math/Matrix3x4.h>
#include <Urho3D/Math/Matrix4.h>
#include <Urho3D/Math/Vector4.h>
#include <Urho3D/Math/MathDefs.h>
#include <Urho3D/Container/Vector.h>
#include <Urho3D/Scene/Node.h>
#include <stdio.h>

namespace Urho3D
{
inline Vector3 TransformVec3(const Matrix3x4& m, const Vector3& pos)
{
    return m * pos;
}

inline Vector3 InvTransformVec3(const Matrix3x4& m, const Vector3& pos)
{
    return m.Inverse() * pos;
}

inline Vector3 TransformPoint(const Vector3& point, Node* node)
{
    return node->LocalToWorld(point);
}

inline Vector3 InverseTransformPoint(const Vector3& point, Node* node)
{
    return node->WorldToLocal(point);
}

inline Vector3 TransformDirection(const Vector3& dir, Node* node)
{
    Vector3 ret = node->GetWorldRotation() * dir;
    ret.Normalize();
    return ret;
}

inline Vector3 InverseTransformDirection(const Vector3& dir, Node* node)
{
    Vector3 ret = node->GetWorldRotation().Inverse() * dir;
    ret.Normalize();
    return ret;
}

	/* Removed from Vector4 and made a non-member here because otherwise
       OgreMatrix4.h and OgreVector4.h have to try to include and inline each 
       other, which frankly doesn't work ;)
   */
    inline Vector4 operator * (const Vector4& v, const Matrix4& mat)
    {
        return Vector4(
            v.x_*mat.m00_ + v.y_*mat.m10_ + v.z_*mat.m20_ + v.w_*mat.m30_,
            v.x_*mat.m01_ + v.y_*mat.m11_ + v.z_*mat.m21_ + v.w_*mat.m31_,
            v.x_*mat.m02_ + v.y_*mat.m12_ + v.z_*mat.m22_ + v.w_*mat.m32_,
            v.x_*mat.m03_ + v.y_*mat.m13_ + v.z_*mat.m23_ + v.w_*mat.m33_
            );
    }



    inline Quaternion SetLookRotation(const Vector3& lookAt, const Vector3& upDirection)
    {
		Vector3 targetZ = lookAt.Normalized();
		Vector3 targetX = upDirection.CrossProduct(targetZ).Normalized();
		Vector3 targetY = targetZ.CrossProduct(targetX).Normalized();
		return Quaternion(targetX, targetY, targetZ);
    }


	inline float Distance(const Vector3& start, const Vector3& end)
	{
		return (start - end).Length();
	}

	inline float DistanceNode(Node* startNode, Node* endNode)
	{
		return Distance(startNode->GetWorldPosition(),
					    endNode->GetWorldPosition());
	}

	inline float AngleBetween(const Vector3& start, const Vector3& end)
	{
		float lenProduct = start.Length() * end.Length();
		// Divide by zero check
		if(lenProduct < 1e-6f)
			lenProduct = 1e-6f;
		float f = start.DotProduct(end) / lenProduct;
		return  M_RADTODEG * acosf(Clamp(f, -1.0f, 1.0f));
	}

	inline Color SaturateColor(const Color& color)
	{
		Color c;
		c.r_ = Clamp(color.r_, 0.0f, 1.0f);
		c.g_ = Clamp(color.g_, 0.0f, 1.0f);
		c.b_ = Clamp(color.b_, 0.0f, 1.0f);
		c.a_ = Clamp(color.a_, 0.0f, 1.0f);
		return c;
	}

	inline Color SubColor(const Color& colorA, const Color& colorB)
	{
		return Color(colorA.r_ - colorB.r_, 
					 colorA.g_ - colorB.g_,
					 colorA.b_ - colorB.b_,
					 colorA.a_ - colorB.a_);
	}

    inline float LagrangeInterpolatingPolynomial ( float* pArrayX,
                                                   float* pArrayY,
                                                   int iDegree,
                                                   float fDesiredX )
    {
        float fResult = 0;
        for ( int i = 0; i < iDegree; ++i )
        {
            float fWeight = 1;
            for ( int j = 0; j < iDegree; ++j )
            {
                // The i-th term has to be skipped
                if (j != i)
                {
                    fWeight *= (fDesiredX - pArrayX[j]) / (pArrayX[i] - pArrayX[j]);
                }
            }
            fResult += fWeight * pArrayY[i];
        }
        return fResult;
    }


    inline Vector3 WorldToLocal( Matrix4& m, const Vector3& v )
    {
        Vector3 tmp = v;

        tmp.x_ -= m.m03_;
        tmp.y_ -= m.m13_;
        tmp.z_ -= m.m23_;

        return Vector3(
            m.m00_*tmp.x_ + m.m10_*tmp.y_ + m.m20_*tmp.z_,
            m.m01_*tmp.x_ + m.m11_*tmp.y_ + m.m21_*tmp.z_,
            m.m02_*tmp.x_ + m.m12_*tmp.y_ + m.m22_*tmp.z_
            );
    }

	inline Node* FindNearstNode(const Vector3& worldPos, Node* root)
	{
		PODVector<Node*> nodeList;
		root->GetChildren(nodeList, true);
		nodeList.Push(root);
		float minLength = 99999;
		Node* nearestNode = NULL;
		for (unsigned i=0;i<nodeList.Size();++i)
		{
			Node* node = nodeList[i];
			Vector3 nodeWorldPos = node->GetWorldPosition();
			float length = (nodeWorldPos - worldPos).LengthSquared();
			if(length < minLength)
			{
				length = minLength;
				nearestNode = node;
			}
		}
		return nearestNode;
	}

	inline void UpdateTree(Node* nd)
	{
		nd->MarkDirty();
		nd->GetWorldTransform();
		for(unsigned i=0;i<nd->GetNumChildren(false);++i)
		{
			UpdateTree(nd->GetChild(i));
		}
	}

	inline Vector3 Cross(const Vector3& a, const Vector3& b)
	{
		return a.CrossProduct(b);
	}

	inline float Dot(const Vector3& a, const Vector3& b)
	{
		return a.DotProduct(b);
	}

	inline bool IsNan(float a)
	{
		return a != a;
	}

	inline float Hermite(float start, float end, float value)
	{
		return Lerp(start, end, value * value * (3.0f - 2.0f * value));
	}

	inline float Sinerp(float start, float end, float value)
	{
		return Lerp(start, end, sinf(value * M_PI * 0.5f));
	}

	inline float Coserp(float start, float end, float value)
	{
		return Lerp(start, end, 1.0f - cosf(value * M_PI * 0.5f));
	}

	inline float Berp(float start, float end, float value)
	{
		value = Clamp(value,0.0f,1.0f);
		value = (sinf(value * M_PI * (0.2f + 2.5f * value * value * value)) * powf(1.0f - value, 2.2f) + value) * (1.0f + (1.2f * (1.0f - value)));
		return start + (end - start) * value;
	}

	inline Vector3 NearestPoint(const Vector3& lineStart, const Vector3& lineEnd, const Vector3& point)
	{
		Vector3 lineDirection = (lineEnd-lineStart).Normalized();
		float closestPoint = Dot((point-lineStart),lineDirection)/Dot(lineDirection,lineDirection);
		return lineStart+(closestPoint*lineDirection);
	}

	inline Vector3 NearestPointStrict(const Vector3& lineStart, const Vector3& lineEnd, const Vector3& point)
	{
		Vector3 fullDirection = lineEnd-lineStart;
		Vector3 lineDirection = fullDirection.Normalized();
		float closestPoint = Dot((point-lineStart),lineDirection)/Dot(lineDirection,lineDirection);
		return lineStart+(Clamp(closestPoint,0.0f,fullDirection.Length())*lineDirection);
	}

	inline float Bounce(float x) 
	{
		return Abs(sinf(6.28f*(x+1.0f)*(x+1.0f)) * (1.0f-x));
	}

	// test for value that is near specified float (due to floating point inprecision)
	// all thanks to Opless for this!
	inline bool Approx(float val, float about, float range) {
		return ( ( Abs(val - about) < range) );
	}

	// test if a Vector3 is close to another Vector3 (due to floating point inprecision)
	// compares the square of the distance to the square of the range as this 
	// avoids calculating a square root which is much slower than squaring the range
	inline bool Approx(const Vector3& val, const Vector3& about, float range) {
		return ( (val - about).LengthSquared() < range*range);
	}

	/*
	* CLerp - Circular Lerp - is like lerp but handles the wraparound from 0 to 360.
	* This is useful when interpolating eulerAngles and the object
	* crosses the 0/360 boundary.  The standard Lerp function causes the object
	* to rotate in the wrong direction and looks stupid. Clerp fixes that.
	*/
	inline float Clerp(float start , float end, float value){
		float min = 0.0f;
		float max = 360.0f;
		float half = Abs((max - min)/2.0f);//half the distance between min and max
		float retval = 0.0f;
		float diff = 0.0f;

		if((end - start) < -half){
			diff = ((max - start)+end)*value;
			retval =  start+diff;
		}
		else if((end - start) > half){
			diff = -((max - end)+start)*value;
			retval =  start+diff;
		}
		else retval =  start+(end-start)*value;
		return retval;
	}

	/*
	  Low Pass Filter Function
	 */
	inline float LPF(float src, int gap)
	{
		int index = 10 * gap;
		int iValue = static_cast<int>(src * index);
		return static_cast<float>(iValue/index);
	}

	inline Vector3 LPF(const Vector3& src, int gap)
	{
		return Vector3(LPF(src.x_,gap),
					   LPF(src.y_,gap),
					   LPF(src.z_,gap));
	}
}

