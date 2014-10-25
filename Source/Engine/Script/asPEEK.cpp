/*
Copyright (c) 2012 Muhammed Ikbal Akpaca

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.

* Alterations in 2014 by Jonathan Sandusky:
- Removal of Boost dependency
- Replace websocketpp with civetweb
*/

#include "Precompiled.h"

#include "asPEEK.h"
#include "Component.h"
#include "Context.h"
#include "Controls.h"
#include "FileSystem.h"
#include "Input.h"
#include "Node.h"
#include "Plane.h"
#include "Ray.h"
#include "Scene.h"
#include "Script.h"
#include "ScriptFile.h"
#include "Sphere.h"
#include "StringUtils.h"
#include "Variant.h"
#include <iostream>
#include <fstream>
#include <math.h>

namespace Urho3D {


/*JSandusky: I had considered including the full definition in the header so I could just
pass a reference to the variable for the MEMBER_QUERY_METHOD  */
class asPEEK::Variable 
{
public:
	Variable() : 
		tid(0), address(0x0) 
	{
	}
	Variable(void* addr, int typeID) : 
		tid(typeID), address(addr) 
	{
	}

	bool IsValid() const 
	{
		return address != 0x0;
	}

	bool IsCPPObject() const 
	{
		return (tid & asTYPEID_APPOBJECT) != 0 || cTypeName.Length() > 0;
	}

	String GetTypeName(asIScriptEngine* angelScript) const
	{
		if (cTypeName.Length() > 0)
			return cTypeName;
		return angelScript->GetTypeDeclaration(tid);
	}

	bool IsPrimitive()
	{
		return tid > 0 && tid <= asTYPEID_DOUBLE;
	}

	Variable GetMemberVariable(const String& name)
	{
		if (!IsPrimitive())
		{
			if (tid & asTYPEID_SCRIPTOBJECT)
			{
				asIScriptObject* obj = 0;
				if (tid & asTYPEID_OBJHANDLE)
					obj = (asIScriptObject*)*(void**)address;
				else
					obj = (asIScriptObject*)address;
				if (obj)
				{
					const unsigned int propCt = obj->GetPropertyCount();
					for (unsigned int i = 0; i < propCt; ++i)
					{
						String propName = obj->GetPropertyName(i);
						if (propName.Compare(name) == 0)
						{
							int tid = obj->GetPropertyTypeId(i);
							void* addr = obj->GetAddressOfProperty(i);
							return Variable(addr, tid);
						}
					}
				}
			}
		}
		return Variable();
	}

	/// attempts to resolve piece of a variable path in regards to an assignment
	asPEEK::QueryResult Resolve(asIScriptEngine* angelScript, const String& name, const String& value, HashMap<String,MEMBER_QUERY_METHOD>& queryMethods)
	{
		if (!address)
			return FAILED;
		if (IsPrimitive())
		{
			// it's a primitive we can't query further
			return FAILED;
		}
		if (tid & asTYPEID_APPOBJECT)
		{
			void* obj = 0;
			if (tid & asTYPEID_OBJHANDLE) 
				obj = *(void**)address;
			else
				obj = address;

			// it's a C++ type bound to script
			String typeName = GetTypeName(angelScript);
			if (queryMethods.Contains(typeName) && obj)
			{
				QueryResult result = queryMethods[typeName](&obj, &tid, &cTypeName, name, value);
				if (result != FAILED)
				{
					if (tid & asTYPEID_OBJHANDLE)
						tid = tid & ~asTYPEID_OBJHANDLE;
					address = obj;
				}
				return result;
			}
		}
		else if (tid & asTYPEID_SCRIPTOBJECT)
		{
			// it's an angelscript class/thing
			asIScriptObject* obj = 0;
			if (tid & asTYPEID_OBJHANDLE) 
				obj = (asIScriptObject*)*(void**)address;
			else 
				obj = (asIScriptObject*)address;
			if (obj)
			{
				int propCt = obj->GetPropertyCount();
				for (int i = 0; i < propCt; ++i)
				{
					String propName = obj->GetPropertyName(i);
					if (propName.Compare(name) == 0)
					{
						tid = obj->GetPropertyTypeId(i);
						address = obj->GetAddressOfProperty(i);
						return FOUND;
					}
				}
			}
		}
		return FAILED;
	}

	int tid;
	void* address;
	String cTypeName;
};


//==================================================================
//
//		CONVERSION METHODS (to JSON) FOR DISPLAYING TYPES
//
//==================================================================
/// presently only used for displaying resource file sizes
String ToFileSize(unsigned bytes)
{
	String prefix = "KMGTPE";
	if (bytes < 1024) 
	    return bytes + " B";
	int exp = (int) (log(bytes) / log(1024));
	String ret = "";
	ret += (float)(bytes / pow(1024, exp));
	const unsigned decimalPosition = ret.Find(".");
	if (decimalPosition != String::NPOS)
		ret.Erase(decimalPosition+2, ret.Length() - (decimalPosition+2));
	ret += " ";
	ret += prefix[exp-1];
	ret += "i";
	ret += "B";
	return ret;
}

/* utility macro for less painfully binding types whose methods follow convention */
#define REGISTER_TYPE(TYPE) RegisterConversion(#TYPE, Convert ## TYPE, Assign ## TYPE, Query ## TYPE)

#define REGISTER_RESOURCE(TYPE) RegisterConversion(#TYPE, ConvertResource, 0, 0)

#define REGISTER_COMPONENT(TYPE) RegisterConversion(#TYPE, ConvertComponent, 0, QueryComponent)

/* This macro generates a quick type convertor that just calls ToString */
#define GENERIC_CONVERSION(TYPE) String Convert ## TYPE (void* in) { \
	String ret = "{\"_\":\""; \
	ret += #TYPE ; \
	ret += "\",\"Address\":\"0x"; \
	ret += ToString(in); \
	ret += "\",\"value\":\""; \
	ret += ((TYPE *)in)->ToString(); \
	ret += "\"}"; \
	return ret; }	

#define PODVECTOR_CONVERSION(NAME, TYPE) String Convert ## NAME (void* in) { \
	TYPE* var = (TYPE *)in; \
	String ret = "{"; \
	for (int i = 0; var->Size(); ++i) { \
		ret += "\""; \
		ret += i; \
		ret += "\":\""; \
		ret += (*var)[i]; \
		ret += "\""; \
		if (i <= var->Size()) ret += ","; \
	} \
	ret += "}"; \
	return ret; }

// Generic conversions for quite a few of the basic Urho3D types
GENERIC_CONVERSION(IntVector2)
GENERIC_CONVERSION(Vector2)
GENERIC_CONVERSION(Vector3)
GENERIC_CONVERSION(Vector4)
GENERIC_CONVERSION(Quaternion)
GENERIC_CONVERSION(Matrix3)
GENERIC_CONVERSION(Matrix3x4)
GENERIC_CONVERSION(Matrix4)
GENERIC_CONVERSION(Color)
GENERIC_CONVERSION(Variant)
GENERIC_CONVERSION(IntRect)
GENERIC_CONVERSION(Rect)

PODVECTOR_CONVERSION(PODVectorFloat,PODVector<float>)
PODVECTOR_CONVERSION(PODVectorBool,PODVector<bool>)
PODVECTOR_CONVERSION(PODVectorInt,PODVector<int>)

String ConvertString(void* in)
{
	String ret = "{\"_\":\"String\",\"value\":\"";
	ret += *(String*)in;
	ret += "\"}";
	return ret;
}

String ConvertBoundingBox(void* in)
{
	String ret = "{\"_\":\"BoundingBox\",";
	ret += "\"min_\":";
	ret += ConvertVector3(&((BoundingBox*)in)->min_);
	ret += ",\"max_\":";
	ret += ConvertVector3(&((BoundingBox*)in)->max_);
	ret += "}";
	return ret;
}

String ConvertPlane(void* in)
{
	String ret = "{\"_\":\"Plane\",\"normal_\":";
	ret += ConvertVector3(&((Plane*)in)->normal_);
	ret += ",\"d_\":\"";
	ret += ((Plane*)in)->d_;
	ret += "\"}";
	return ret;
}

String ConvertRay(void* in)
{
	String ret = "{\"_\":\"Ray\",\"origin_\":";
	ret += ConvertVector3(&((Ray*)in)->origin_);
	ret += ",\"direction_\":";
	ret += ConvertVector3(&((Ray*)in)->direction_);
	ret += "}";
	return ret;
}

String ConvertSphere(void* in)
{
	String ret = "{\"_\":\"Sphere\",\"center_\":";
	ret += ConvertVector3(&((Sphere*)in)->center_);
	ret += ",\"radius_\":\"";
	ret += ((Sphere*)in)->radius_;
	ret += "\"";
	ret += "}";
	return ret;
}

String ConvertStringHash(void* in)
{
	String ret = "{\"_\":\"StringHash\",\"value\":\"";
	ret += ((StringHash*)in)->ToString();
	ret += "\"}";
	return ret;
}

String ConvertVariantMap(void* in)
{
	String ret = "{\"_\":\"VariantMap\"";
	VariantMap* map = (VariantMap*)in;
	Vector<StringHash> keys = map->Keys();
	for (unsigned int i = 0; i < keys.Size(); ++i)
	{
		if (i == 0) //Need a comma if we're not empty
			ret += ",";
		ret += "\"";
		ret += keys[i].ToString();
		ret += "\":{\"";
		ret += (*map)[keys[i]].GetTypeName();
		ret += "\":\"";
		ret += (*map)[keys[i]].ToString();
		ret += "\"}";
		if (i < keys.Size() - 1)
			ret += ",";
	}
	ret += "}";
	return ret;
}

String ConvertComponentData(void* in)
{
	Component* c = (Component*)in;
	String ret = "{\"_\":\"";
	ret += c->GetTypeName();
	ret += "\",";
	ret += "\"Component\":\"";
	ret += c->GetTypeName();
	ret += "\",\"Address\":\"0x";
	ret += ToString(in);
	ret += "\",";
	const Vector<AttributeInfo>* info = c->GetAttributes();
	for (unsigned int i = 0; i < info->Size(); ++i) {
		Variant v = c->GetAttribute((*info)[i].name_);
		ret += "\"";
		ret += (*info)[i].name_;
		ret += "\":\"";
		ret += v.ToString();
		ret += "\"";
		if (i < info->Size() - 1)
			ret += ",";
	}
	ret += "}";
	return ret;
}

String ConvertComponent(void* in)
{
	if (!in)
		return "";
	return ConvertComponentData(in);
}

String ConvertNode(void* in)
{
	Node* node = (Node*)in;
	String ret = "{\"_\":\"Node\",";
	const Vector<AttributeInfo>* attrs = node->GetAttributes();
	if (attrs)
	{
		if (node->GetID() < Urho3D::FIRST_LOCAL_ID)
			ret += "\"Mode\":\"Networked\",";
		else
			ret += "\"Mode\":\"Local\",";
		ret += "\"Address\":\"0x";
		ret += ToString(in);
		ret += "\",";

		for (unsigned int i = 0; i < attrs->Size(); ++i)
		{
			ret += "\"";
			ret += (*attrs)[i].name_;
			ret += "\":\"";
			ret += node->GetAttribute(i).ToString();
			ret += "\"";
				ret += ",";
		}
	}

	ret += "\"Components\":{";
	Vector<SharedPtr<Component> > comps = node->GetComponents();
	for (unsigned int i = 0; i < comps.Size(); ++i) 
	{
		ret += "\"";
		ret += comps[i].Get()->GetTypeName();
		ret += " [";
		ret += i;
		ret += "]\":";
		ret += ConvertComponentData(comps[i].Get());
		if (i < comps.Size() - 1)
			ret += ",";
	}

	ret += "}}";

	return ret;
}

String ConvertResource(void* resource)
{
	String ret = "{\"_\":\"";
	ret += ((Resource*)resource)->GetTypeName();
	ret += "\",\"File\":\"";
	ret += ((Resource*)resource)->GetName();
	ret += "\",\"Memory\":\"";
	ret += ToFileSize(((Resource*)resource)->GetMemoryUse());
	ret += "\",\"Last Used\":\"";
	ret += ((Resource*)resource)->GetUseTimer();
	ret += "\"}";
	return ret;
}

String ConvertTouchState(void* in)
{
	String ret = "{\"_\":\"TouchState\",";
	ret += "\"touchID_\":\"";
	ret += ((TouchState*)in)->touchID_;
	ret += "\",";

	ret += "\"position_\":\"";
	ret += ((TouchState*)in)->position_.ToString();
	ret += "\",";

	ret += "\"lastPosition_\":\"";
	ret += ((TouchState*)in)->lastPosition_.ToString();
	ret += "\",";

	ret += "\"delta_\":\"";
	ret += ((TouchState*)in)->delta_.ToString();
	ret += "\",";

	ret += "\"pressure_\":\"";
	ret += ((TouchState*)in)->pressure_;
	ret += "\"}";

	return ret;
}

String ConvertJoystickState(void* in)
{
	JoystickState* joystick = (JoystickState*)in;
	String ret = "{\"_\":\"JoystickState\",";
		
	ret += "\"axes_\":";
	for (unsigned int i = 0; i < joystick->axes_.Size(); ++i)
	{
		ret += "\"Axis ";
		ret += i;
		ret += "\":";
		ret += ConvertPODVectorFloat(&joystick->axes_);
	}
	ret += ",";
		
	ret += "\"buttons_\":";
	for (unsigned int i = 0; i < joystick->buttons_.Size(); ++i)
	{
		ret += ConvertPODVectorBool(&joystick->buttons_);
	}
	ret += ",";
		
	ret += "\"hats_\":";
	for (unsigned int i = 0; i < joystick->hats_.Size(); ++i)
	{
		ret += ConvertPODVectorInt(&joystick->hats_);
	}
	ret += "}";
	return ret;
}

String ConvertControls(void* in)
{
	String ret = "{\"_\":\"Controls\",\"Address\":\"0x";
	ret += ToString(in);
	ret += "\",\"pitch_\":\"";
	ret += ((Controls*)in)->pitch_;
	ret += "\",\"yaw_\":\"";
	ret += ((Controls*)in)->yaw_;
	ret += "\",\"buttons_\":\"";
	ret += ((Controls*)in)->buttons_;
	ret += "\",\"extraData_\":";
	ret += ConvertVariantMap(&((Controls*)in)->extraData_);
	ret += "}";
	return ret;
}


//==================================================================
//
//		ASSIGNMENT METHODS (from string) FOR SETTING THINGS FROM THE CLIENT
//
//==================================================================

/* this macro generates a quick and dirty usage of To____ from StringUtils.h */
#define GENERIC_ASSIGNMENT(TYPE) void Assign ## TYPE (void* out, String txt) { \
	*(TYPE*)out = To ## TYPE (txt); } 

GENERIC_ASSIGNMENT(IntVector2)
GENERIC_ASSIGNMENT(Vector2)
GENERIC_ASSIGNMENT(Vector3)
GENERIC_ASSIGNMENT(Vector4)
GENERIC_ASSIGNMENT(Quaternion)
GENERIC_ASSIGNMENT(Matrix3)
GENERIC_ASSIGNMENT(Matrix3x4)
GENERIC_ASSIGNMENT(Matrix4)
GENERIC_ASSIGNMENT(Rect)
GENERIC_ASSIGNMENT(IntRect)
GENERIC_ASSIGNMENT(Color)

void AssignString(void* out, String txt)
{
	*((String*)out) = txt;
}

void AssignVariant(void* out, String txt)
{
	Variant* var = (Variant*)out;
	switch (var->GetType())
	{
	case VAR_INT:
		*var = ToInt(txt);
		return;
	case VAR_BOOL:
		*var = ToBool(txt);
		return;
	case VAR_FLOAT:
		*var = ToFloat(txt);
		return;
	case VAR_VECTOR2:
		*var = ToVector2(txt);
		return;
	case VAR_VECTOR3:
		*var = ToVector3(txt);
		return;
	case VAR_VECTOR4:
		*var = ToVector4(txt);
		return;
	case VAR_QUATERNION:
		*var = ToQuaternion(txt);
		return;
	case VAR_COLOR:
		*var = ToColor(txt);
		return;
	case VAR_STRING:
		*var = txt;
		return;
	case VAR_BUFFER:
		//???
		return;
	case VAR_VOIDPTR:
		//???
		return;
	case VAR_RESOURCEREF:
		//???
		return;
	case VAR_RESOURCEREFLIST:
		//???
		return;
	case VAR_VARIANTVECTOR:
		//???
		return;
	case VAR_VARIANTMAP:
		//???
		return;
	case VAR_INTRECT:
		*var = ToIntRect(txt);
		return;
	case VAR_INTVECTOR2:
		*var = ToIntVector2(txt);
		return;
	case VAR_PTR:
		//??
		return;
	case VAR_MATRIX3:
		*var = ToMatrix3(txt);
		return;
	case VAR_MATRIX3X4:
		*var = ToMatrix3x4(txt);
		return;
	case VAR_MATRIX4:
		*var = ToMatrix4(txt);
		return;
	}
}

//==================================================================
//
//		QUERY METHODS FOR GETTING C++ MEMBERS
//
//==================================================================
/* generic query that sets the typename and just returns the current ptr (e.g. "value" case where  where already at the type 

The string we got from the client is

vec2Variable~value~1.05 1.990 ... but what that really means is vec2Variable~1.05 1.990

the JSON we send looks like
vec2Variable : { <------- we've already gotten here
"Type" : "Vector2",
"value":"0.5 0.75 0.99" <-------- but we're here, so we return the guy up above us
}

This is all a bit of a hack but it keeps things pleasant to look at on the client
*/
#define GENERIC_QUERY(TYPE) asPEEK::QueryResult Query ## TYPE (void** addr, int* tid, String* typeName, const String& name, const String& value) { \
	if (name.Compare("value", false) == 0) { \
		*typeName = #TYPE ; \
		return asPEEK::FOUND; } \
	return asPEEK::QueryResult::FAILED; }

//this wont work with char
#define PODVECTOR_QUERY(TYPE, TITLE) asPEEK::QueryResult QueryPODVector ## TITLE (void** addr, int* tid, String* typeName, const String& name, const String& value) \
{ \
	PODVector < TYPE >* var = (PODVector < TYPE >*)addr; \
	int sub = ToInt(name); \
	if (sub > 0 && sub < var->Size()) { \
		(*var)[sub] = To ## TITLE (value); \
		return asPEEK::FOUND_AND_SET; \
	} \
	return asPEEK::FAILED; \
}

GENERIC_QUERY(Vector2)
GENERIC_QUERY(Vector3)
GENERIC_QUERY(Vector4)
GENERIC_QUERY(Quaternion)
GENERIC_QUERY(Matrix3)
GENERIC_QUERY(Matrix3x4)
GENERIC_QUERY(Matrix4)
GENERIC_QUERY(Color)
GENERIC_QUERY(Rect)
GENERIC_QUERY(IntVector2)
GENERIC_QUERY(IntRect)

/** These macros are sort of like slightly more violent MFC message maps, 
basically they create a bunch of if statements
see the examples of use below */
#define START_QUERY(TYPE) asPEEK::QueryResult Query ## TYPE (void** addr, int* tid, String* typeName, const String& name, const String& value) { \
	TYPE * var = (TYPE *)(*addr);

/// queries on something that's a C++ class/struct
#define QUERY_CLASS(NAME, VARTYPE) if (name.Compare( #NAME , false) == 0) {\
	*typeName =  #VARTYPE; \
	*tid = asTYPEID_APPOBJECT; \
	(*addr) = &(var->NAME); \
	return asPEEK::QueryResult::FOUND; }

/// queries on something that's an int,float,char,etc
#define QUERY_PRIMITIVE(NAME, VARTYPE, TID) if (name.Compare( #NAME, false) == 0) {\
	(*typeName).Clear(); \
	*tid = TID; \
	(*addr) = &(var->NAME); \
	return asPEEK::QueryResult::FOUND; }

/// self referencing return, see above on GENERIC_QUERY
#define QUERY_REPEAT(NAME) if (name.Compare( #NAME, false) == 0) {\
	return asPEEK::QueryResult::FOUND; }

#define QUERY_ATTRIBUTE() Variant v = var->GetAttribute(name); \
	if (!v.IsEmpty()) { \
		v.FromString(v.GetType(), value); \
		var->SetAttribute(name, v); \
		return asPEEK::FOUND_AND_SET; }

#define END_QUERY() return asPEEK::QueryResult::FAILED; }

START_QUERY(Sphere)
	QUERY_CLASS(center_, Vector3)
	QUERY_PRIMITIVE(radius_, float, asTYPEID_FLOAT)
END_QUERY()

START_QUERY(BoundingBox)
	QUERY_CLASS(min_, Vector3)
	QUERY_CLASS(max_, Vector3)
END_QUERY()

START_QUERY(Ray)
	QUERY_CLASS(origin_, Vector3)
	QUERY_CLASS(direction_, Vector3)
END_QUERY()

START_QUERY(Plane)
	QUERY_CLASS(normal_, Vector3)
	QUERY_PRIMITIVE(d_, float, asTYPEID_FLOAT)
END_QUERY()

START_QUERY(TouchState)
	QUERY_PRIMITIVE(touchID_, int, asTYPEID_INT32)
	QUERY_PRIMITIVE(pressure_, float, asTYPEID_FLOAT)
	QUERY_CLASS(delta_, IntVector2)
	QUERY_CLASS(lastPosition_, IntVector2)
	QUERY_CLASS(position_, IntVector2)
END_QUERY()

START_QUERY(JoystickState)
	QUERY_CLASS(buttons_, PODVector<bool>)
	QUERY_CLASS(hats_, PODVector<int>)
	QUERY_CLASS(axes_, PODVector<float>)
END_QUERY()

START_QUERY(Controls)
	QUERY_PRIMITIVE(pitch_,float, asTYPEID_FLOAT)
	QUERY_PRIMITIVE(yaw_,float, asTYPEID_FLOAT)
	QUERY_PRIMITIVE(buttons_,unsigned, asTYPEID_UINT32)
	QUERY_CLASS(extraData_, VariantMap)
END_QUERY()

PODVECTOR_QUERY(int,Int)
PODVECTOR_QUERY(float,Float)
PODVECTOR_QUERY(bool,Bool)

asPEEK::QueryResult QueryVariant(void** addr, int* tid, String* typeName, const String& name, const String& value)
{
	/* we sent them
	STRINGHASH : {
		TYPENAME : VALUE
	} */
	Variant* var = (Variant*)*addr;
	if (var->GetTypeName().Compare(name, false) == 0) {
		var->FromString(var->GetType(), value);
		return asPEEK::FOUND_AND_SET; //not necessarilly entirely true ... but it's close enough
	}
	return asPEEK::FAILED;
}

asPEEK::QueryResult QueryVariantMap(void** addr, int* tid, String* typeName, const String& name, const String& value)
{
	VariantMap* map = (VariantMap*)*addr;
	if (map->Contains(name))
	{
		Variant& v = (*map)[name];
		(*addr) = &v;
		*tid = asTYPEID_APPOBJECT;
		*typeName = "Variant";
	}
	return asPEEK::FAILED;
}

asPEEK::QueryResult QueryComponent(void** addr, int* tid, String* typeName, const String& name, const String& value)
{
	Component* c = ((Component*)*addr);
	Variant v = c->GetAttribute(name);
	if (!v.IsEmpty())
	{
		/* reason for FOUND_AND_SET, no way to get pointer to a variant */
		v.FromString(v.GetType(), value);
		c->SetAttribute(name, v);
		return asPEEK::FOUND_AND_SET;
	}
	return asPEEK::FAILED;
}
	
asPEEK::QueryResult QueryNode(void** addr, int* tid, String* typeName, const String& name, const String& value)
{
	Node* node = (Node*)*addr;

	// dirty hack, just return out for handling "Components"->"RigidBody [0]"
	if (name.Compare("components",false) == 0)
		return asPEEK::FOUND;

	if (name.Contains('['))
	{
		// it's a component we're querying for
		/* this is a hack, each component of a node sends it's titles as ComponentTypeName (INDEX)
		so that it can be reconstructed here, this hack is necessary because you can have multiple of the same component
		so using just the component type name isn't enough */
		const int startIndex = name.Find('[') + 1;
		const int endIndex = name.Find(']') - 1;
		const int sub = ToInt(name.Substring(startIndex, endIndex - startIndex + 1));

		const Vector< SharedPtr<Component> >& comps = node->GetComponents();
		if (sub < comps.Size())
		{
			*addr = comps[sub].Get();
			*tid = asTYPEID_APPOBJECT;
			*typeName = comps[sub]->GetTypeName();
			return asPEEK::FOUND;
		}
	}
	else
	{
		// it's an attribute we're after
		Variant v = node->GetAttribute(name);
		if (!v.IsEmpty())
		{
			/* this is why there's a FOUND_AND_SET option 
			no way to return a pointer to an attribute */
			v.FromString(v.GetType(), value);
			node->SetAttribute(name, v);
			return asPEEK::FOUND_AND_SET;
		}
	}

	return asPEEK::FAILED;
}


//==================================================================
//
//		actual asPEEK methods
//
//==================================================================
asPEEK::asPEEK(Context* ctx, int port) : 
	engine_(0x0) 
{
	ctx_ = ctx;

	struct mg_callbacks callbacks;
	memset(&callbacks, 0, sizeof(callbacks)); //seriously ugly
	callbacks.websocket_connect = websocket_connect_handler;
	callbacks.websocket_ready = websocket_ready_handler;
	callbacks.websocket_data = websocket_data_handler;
	callbacks.connection_close = websocket_close_handler;

	const char *options[] = {
		"listening_ports", "9002",
		"document_root", "docroot",//??
		NULL
	};

	debuggingLine_ = 0;
	debuggingSection_ = 0;
	debuggingContext_ = 0x0;
	debuggingStartedFunction_ = 0x0;
	debuggingEndedFunction_ = 0x0;
	loadSectionFunction_ = (asPEEK::DefaultLoadSectionFunction);
	restartFunction_ = 0x0; //TODO: implement as restart? probably not
	saveSectionFunction_ = (asPEEK::DefaultSaveSectionFunction);//0x0; //TODO: implement section saving

	sectionCount_ = 1;

	this->context_ = mg_start(&callbacks, this, options);

	debugInterrupt_ = false;
	nextDebugCommand_ = CONTINUE;

	// Math types
	REGISTER_TYPE(IntVector2);
	REGISTER_TYPE(Vector2);
	REGISTER_TYPE(Vector2);
	REGISTER_TYPE(Vector3);
	REGISTER_TYPE(Vector4);
	REGISTER_TYPE(Quaternion);
	REGISTER_TYPE(Matrix3);
	REGISTER_TYPE(Matrix3x4);
	REGISTER_TYPE(Matrix4);
	RegisterConversion("Plane", ConvertPlane, 0, QueryPlane);
	RegisterConversion("BoundingBox", ConvertBoundingBox, 0, QueryBoundingBox);
	RegisterConversion("Ray", ConvertRay, 0, QueryRay);
	RegisterConversion("Sphere", ConvertSphere, 0, QuerySphere);
	REGISTER_TYPE(Color);
	REGISTER_TYPE(Rect);
	REGISTER_TYPE(IntRect);

	// General types
	RegisterConversion("Controls",ConvertControls, 0, 0);
	RegisterConversion("JoystickState", ConvertJoystickState, 0, 0);
	RegisterConversion("TouchState", ConvertTouchState, 0, 0);

	// core/container types
	RegisterConversion("Node", ConvertNode, 0, QueryNode);
	RegisterConversion("String", ConvertString, AssignString, 0);
	RegisterConversion("Variant", ConvertVariant, AssignVariant, QueryVariant);
	RegisterConversion("VariantMap", ConvertVariantMap, 0, QueryVariantMap);
	RegisterConversion("StringHash", ConvertStringHash, 0, 0);
	RegisterConversion("PODVector<float>", ConvertPODVectorFloat, 0, QueryPODVectorFloat);
	RegisterConversion("PODVector<bool>", ConvertPODVectorBool, 0, QueryPODVectorBool);
	RegisterConversion("PODVector<int>", ConvertPODVectorInt, 0, QueryPODVectorInt);

	// Resources
	REGISTER_RESOURCE(Sound);
    REGISTER_RESOURCE(Animation);
    REGISTER_RESOURCE(Material);
    REGISTER_RESOURCE(Model);
    REGISTER_RESOURCE(ParticleEffect);
    REGISTER_RESOURCE(Shader);
    REGISTER_RESOURCE(Technique);
    REGISTER_RESOURCE(D3D9Texture);
    REGISTER_RESOURCE(OGLTexture);
	REGISTER_RESOURCE(Texture);
	REGISTER_RESOURCE(Texture2D);
	REGISTER_RESOURCE(Texture3D);
	REGISTER_RESOURCE(TextureCube);
    REGISTER_RESOURCE(LuaFile);
    REGISTER_RESOURCE(Image);
    REGISTER_RESOURCE(JSONFile);
    REGISTER_RESOURCE(PListFile);
    REGISTER_RESOURCE(XMLFile);
    REGISTER_RESOURCE(ObjectAnimation);
    REGISTER_RESOURCE(ValueAnimation);
    REGISTER_RESOURCE(ScriptFile);
    REGISTER_RESOURCE(Font);
    REGISTER_RESOURCE(AnimationSet2D);
    REGISTER_RESOURCE(Sprite2D);
    REGISTER_RESOURCE(SpriteSheet2D);
    REGISTER_RESOURCE(TmxFile2D);
        
	// scripting
	REGISTER_COMPONENT(ScriptInstance);

	// audio
	REGISTER_COMPONENT(SoundListener);
	REGISTER_COMPONENT(SoundSource);
	REGISTER_COMPONENT(SoundSource3D);

	// graphics
	REGISTER_COMPONENT(AnimatedModel);
	REGISTER_COMPONENT(AnimationController);
	REGISTER_COMPONENT(BillboardSet);
	REGISTER_COMPONENT(Camera);
	REGISTER_COMPONENT(StaticModel);
	REGISTER_COMPONENT(DecalSet);
	REGISTER_COMPONENT(Light);
	REGISTER_COMPONENT(CustomGeometry);
	REGISTER_COMPONENT(Zone);
	REGISTER_COMPONENT(Octree);
	REGISTER_COMPONENT(Terrain);

	// networking
	REGISTER_COMPONENT(NetworkPriority);

	// physics
	REGISTER_COMPONENT(CollisionShape);
	REGISTER_COMPONENT(Constraint);
	REGISTER_COMPONENT(RigidBody);

	// UI
	REGISTER_COMPONENT(BorderImage);
	REGISTER_COMPONENT(Button);
	REGISTER_COMPONENT(CheckBox);
	REGISTER_COMPONENT(Cursor);
	REGISTER_COMPONENT(DropDownList);
	REGISTER_COMPONENT(FileSelector);
	REGISTER_COMPONENT(LineEdit);
	REGISTER_COMPONENT(ListView);
	REGISTER_COMPONENT(Menu);
	REGISTER_COMPONENT(MessageBox);
	REGISTER_COMPONENT(ScrollBar);
	REGISTER_COMPONENT(ScrollView);
	REGISTER_COMPONENT(Slider);
	REGISTER_COMPONENT(Sprite);
	REGISTER_COMPONENT(Text);
	REGISTER_COMPONENT(Text3D);
	REGISTER_COMPONENT(View3D);
	REGISTER_COMPONENT(Window);

	// Urho 2D
	REGISTER_COMPONENT(AnimatedSprite2D);
	REGISTER_COMPONENT(CollisionBox2D);
	REGISTER_COMPONENT(CollisionCircle2D);
	REGISTER_COMPONENT(CollisionEdge2D);
	REGISTER_COMPONENT(CollisionPolygon2D);
	REGISTER_COMPONENT(CollisionShape2D);
	REGISTER_COMPONENT(Constraint2D);
	REGISTER_COMPONENT(ConstraintDistance2D);
	REGISTER_COMPONENT(ConstraintFriction2D);
	REGISTER_COMPONENT(ConstraintGear2D);
	REGISTER_COMPONENT(ConstraintMotor2D);
	REGISTER_COMPONENT(ConstraintMouse2D);
	REGISTER_COMPONENT(ConstraintPrismatic2D);
	REGISTER_COMPONENT(ConstraintPulley2D);
	REGISTER_COMPONENT(ConstraintRevolute2D);
	REGISTER_COMPONENT(ConstraintWeld2D);
	REGISTER_COMPONENT(ConstraintWheel2D);
	REGISTER_COMPONENT(Drawable2D);
	REGISTER_COMPONENT(ParticleEmitter2D);
	REGISTER_COMPONENT(RigidBody2D);
	REGISTER_COMPONENT(StaticSprite2D);
	REGISTER_COMPONENT(TileMap2D);
}

asPEEK::~asPEEK() 
{
	::mg_stop(context_);
}

int asPEEK::websocket_connect_handler(const mg_connection *conn) 
{
	mg_request_info* info = mg_get_request_info(const_cast<mg_connection*>(conn));
	asPEEK* inst = (asPEEK*)info->user_data;
	inst->debugInterrupt_ = false;
	if (inst->tracked_context_.Size() > 0) 
	{
		for (HashMap<int,asIScriptContext*>::Iterator it = inst->tracked_context_.Begin(); it != inst->tracked_context_.End(); ++it)
			it->second_->SetLineCallback(asMETHOD(asPEEK, LineCallback), inst, asCALL_THISCALL);
	}
	return 0; //??err just assume everything's okeydokey?
}

void asPEEK::websocket_ready_handler(mg_connection *conn) 
{
	mg_request_info* info = mg_get_request_info(conn);
	asPEEK* inst = (asPEEK*)info->user_data;

	inst->connectionList_.Push(conn);
	if (inst->engine_ == 0x0) 
	{
		const FileSystem* fs = inst->ctx_->GetSubsystem<FileSystem>();
		Script* scripting = inst->ctx_->GetSubsystem<Script>();
		inst->currentDir_ = fs->GetCurrentDir().CString();
		inst->engine_ = scripting->GetScriptEngine();
		inst->AddContext(scripting->GetScriptFileContext());
		inst->AddContext(scripting->GetImmediateContext());
		inst->UpdateAngelScriptBindings();
	} 
	else 
		inst->UpdateAngelScriptBindings();
		
	inst->NewClient(conn);
}

void asPEEK::websocket_close_handler(mg_connection *conn) 
{
	mg_request_info* info = mg_get_request_info(conn);
	
	asPEEK* instance = (asPEEK*)info->user_data;
	instance->connectionList_.Remove(conn);

	/* the code below removes all breakpoints, stops debugging, and interrupts any active debugging
	it's commented out because the client loses connection randomly and dumping everything is frustrating */
	/*
	if (instance->connectionList_.Size() == 0) 
	{
		for (HashMap<int,SectionData>::Iterator it = instance->sections_.Begin(); it != instance->sections_.End(); ++it)
			it->second_.breakpoints.Clear();
	}
	if (instance->debuggingContext_ != 0x0 && instance->connectionList_.Size() == 0) {
		instance->EndDebugging();
	}
	if (instance->connectionList_.Size() == 0) 
	{
		instance->debugInterrupt_ = true;
	}*/
}

int asPEEK::websocket_data_handler(mg_connection *conn, int flags, char *data, size_t data_len) 
{
	//if (flags & 0x80) {
	mg_request_info* info = mg_get_request_info(conn);
	asPEEK* instance = (asPEEK*)info->user_data;

	flags &= 0x7f;
	switch (flags) 
	{
	case WEBSOCKET_OPCODE_CONTINUATION: //shouldn't need
		fprintf(stderr, "CONTINUATION...\n");
		break;
	case WEBSOCKET_OPCODE_TEXT: 
		{
			Message msg(conn, String(data,data_len));
			instance->ProcessMessage(msg);
		}
		break;
	case WEBSOCKET_OPCODE_BINARY: //shouldn't need
		break;
	case WEBSOCKET_OPCODE_CONNECTION_CLOSE:
		/* If client initiated close, respond with close message in acknowlegement */
		mg_websocket_write(conn, WEBSOCKET_OPCODE_CONNECTION_CLOSE, data, data_len);
		//TODO: perhaps place the code from the disconnect handler here
		return 0; /* time to close the connection */
		break;
	case WEBSOCKET_OPCODE_PING:
		mg_websocket_write(conn, WEBSOCKET_OPCODE_PONG, data, data_len);
		break;
	case WEBSOCKET_OPCODE_PONG:
		{ //we'll get pong'ed if we take too long, which is a little weird
			Message msg(conn, String(data,data_len));
			instance->ProcessMessage(msg);
		}
		break;
	default:
		fprintf(stderr, "Unknown flags: %02x\n", flags);
		break;
	}
	//}

	return 1;   /* keep connection open */
}

void asPEEK::UpdateAngelScriptBindings()
{
	Script* scripting = ctx_->GetSubsystem<Script>();
	String modName;
	for (unsigned int i = 0; i < engine_->GetModuleCount(); ++i) 
	{
		asIScriptModule* mod = engine_->GetModuleByIndex(i);
		AddModule(mod);
		AddScriptSection(mod->GetName(), mod->GetName());
		modName = mod->GetName();
	}
			
	ScriptFile* file = scripting->GetDefaultScriptFile();
	if (file != 0x0) 
	{
		HashSet<String>& includes = file->includeFiles_;
		for (HashSet<String>::Iterator it = includes.Begin(); it != includes.End(); ++it)
			AddScriptSection((*it), modName);
	}
	UpdateTypeConversions();
}

bool asPEEK::CheckBreakpoint(int line, SectionData* sectionData) 
{
	if (!sectionData || sectionData->breakpoints.Size() == 0)
		return false;
	return sectionData->breakpoints.Contains(line);
}

void asPEEK::LineCallback(asIScriptContext* ctx) 
{
	if (debugInterrupt_)
		return;
	if (ctx->GetState() != asEXECUTION_ACTIVE)
		return;

	if (debuggingContext_ != 0x0 && debuggingContext_->GetState() != asEXECUTION_ACTIVE) 
	{
		EndDebugging();
		return;
	}

	const char* section = 0x0;
	int line = ctx->GetLineNumber(0, 0, &section);
	if (line <= 0)
		return;
	if (!section)
		return;
	SectionData *d = GetSectionData(section);
	if (!d)
		return;

	// if command is continue (default) check breakpoint 
	if (nextDebugCommand_ == CONTINUE) 
	{
		if (d->breakpoints.Size() > 0 && CheckBreakpoint(line, d)) 
		{ // hit a breakpoint
			if (debuggingStartedFunction_)
				debuggingStartedFunction_();

			//boost::mutex::scoped_lock lock(debugging_mutex);
			debuggingLine_ = line;
			debuggingSection_ = d->id;
			// this thread is now being debugged
			debuggingContext_ = ctx;
			//lock.unlock();

			Debug(ctx, line, d);
		} 
		else if (ctx == debuggingContext_) 
		{
				EndDebugging();
		}

	} 
	else 
	{ 
		int ssize = ctx->GetCallstackSize();
			
		switch (nextDebugCommand_) 
		{
		case asPEEK::STEPOUT:
			if (ctx->GetCallstackSize() < debuggingStackLevel_) 
			{
				//The stack has gotten smaller, that should mean that we've stepped out
				debuggingLine_ = line;
				debuggingSection_ = d->id;
				debuggingContext_ = ctx;
				Debug(ctx, line, d);
			} 
			else 
			{
				if (d->breakpoints.Size() > 0 && CheckBreakpoint(line,d)) 
				{ // hit a breakpoint
					debuggingLine_ = line;
					debuggingSection_ = d->id;
					debuggingContext_ = ctx;
					Debug(ctx, line, d);
				}
			}
			break;
		case asPEEK::STEPIN:
			{
				//We we step in we allow the next bit of code to execute, and then report back
				debuggingLine_ = line;
				debuggingSection_ = d->id;
				debuggingContext_ = ctx;
				Debug(ctx, line, d);
			}
			break;
		case asPEEK::STEPOVER:
			if (ctx->GetCallstackSize() <= debuggingStackLevel_) 
			{
				debuggingLine_ = line;
				debuggingSection_ = d->id;
				debuggingContext_ = ctx;
				Debug(ctx, line, d);
			} 
			else if (d->breakpoints.Size() > 0 && CheckBreakpoint(line,d)) // hit a breakpoint
			{
				debuggingLine_ = line;
				debuggingSection_ = d->id;
				debuggingContext_ = ctx;
				Debug(ctx, line, d);
			}
			break;
		default:
			break;
		}
	}
}

void asPEEK::SendModuleNames(mg_connection* conn) 
{
	String ss;
	ss += "MODL [";
	for (HashSet<asIScriptModule*>::Iterator it = tracked_modules_.Begin(); it != tracked_modules_.End();) 
	{
		ss += "\"";
		ss += (*it)->GetName();
		ss += "\"";
		++it;
		if (it != tracked_modules_.End())
			ss += ",";
	}
	ss += "]";

	//con->send(modules);

	SendMessage(conn, ss);
}

void asPEEK::SendSectionNames(mg_connection* conn) 
{
	String ss;
	ss += "SCLS [";

	for (HashMap<int, SectionData>::ConstIterator it = sections_.Begin(); it != sections_.End(); ) 
	{  
		ss += "{";
		ss += "\"id\":";
		ss += it->first_;
		ss += ",\"name\":\"";
		ss += it->second_.name.CString(); ss += "\",";
		ss += "\"mod\":\""; ss += it->second_.mod.CString(); ss += "\"";
		ss += "}";

		++it;
		if (it != sections_.End())
			ss += ",";
	}

	ss += "]";
	SendMessage(conn, ss);

	for (HashMap<int, SectionData>::ConstIterator it = sections_.Begin(); it != sections_.End(); ++it) 
	{
		for (HashSet<int>::ConstIterator it2 = it->second_.breakpoints.Begin(); it2 != it->second_.breakpoints.End(); ++it2) 
		{
			String ss2;
			ss2 += "BSET ";
			ss2 += it->first_;
			ss2 += " ";
			ss2 += *(it2);
			SendMessage(conn, ss2);
		}
	}
}

void asPEEK::SendContexts(mg_connection* conn) {
	String ss;
	ss += "CTXL";
	for (HashMap<int, asIScriptContext*>::ConstIterator it = tracked_context_.Begin(); it != tracked_context_.End(); ++it) 
	{
		ss += " ";
		ss += it->first_;
	}
	SendMessage(conn, ss);
}

void asPEEK::SendCurrentLine(mg_connection* conn) 
{
	if (debuggingContext_ && debuggingSection_ && debuggingLine_) 
	{
		String ss;
		ss += "HITL ";
		ss += debuggingSection_;
		ss += " ";
		ss += debuggingLine_;

		SendMessage(conn, ss);
	}
}

void asPEEK::SendFile(const Vector<String>& words, mg_connection* conn) 
{
	if (loadSectionFunction_) 
	{
		String fileContents;
		int secID = Urho3D::ToInt(words[1]);
		if (secID != 0) 
		{
			if (sections_.Contains(secID)) 
			{
				loadSectionFunction_(sections_[secID].name, fileContents);
				String msg = "FILE ";
				msg += words[1];
				msg += " ";
				msg += fileContents;
				SendMessage(conn, msg);
			}
		} 
		else 
		{
			SendMessage(conn, String("LOGE You did not define a load section function. Can not send section."));
		}
	}
}

void asPEEK::FromString(const Variable& var, String value, HashSet<void*>* previous)
{
	if (var.tid & asTYPEID_SCRIPTOBJECT) 
	{
		if (var.tid & asTYPEID_OBJHANDLE) 
		{
			//?? do nothing
		} 
		else 
		{
			//?? do nothing
		}
	} 
	else if (var.tid & asTYPEID_TEMPLATE) 
	{
		//??do nothing
	} 
	else if (var.tid & asTYPEID_APPOBJECT) 
	{
		int tid = var.tid;
		bool isHandle = false;

		if (var.tid & asTYPEID_OBJHANDLE) 
		{
			tid |= asTYPEID_OBJHANDLE;
			isHandle = true;
		}

		if (var.address && assignmentMethods_.Contains(tid)) {
			void* target = 0x0;
			if (isHandle) {
				target = *(void**)var.address;
			} else {
				target = var.address;
			}
			if (target)
				assignmentMethods_[tid](target, value);
			return;
		} 
	} 
	else 
	{
		return PrimitiveFromString(var, value);
	}
}

String asPEEK::ToString(const Variable& var, HashSet<void*> *previous)
{
	if (var.tid & asTYPEID_SCRIPTOBJECT) 
	{
		if (var.tid & asTYPEID_OBJHANDLE) 
		{
			String ss;
			ScriptObjectToString(*(asIScriptObject**)(var.address), ss, previous);
			return ss;
		} 
		else 
		{
			String ss;
			ScriptObjectToString((asIScriptObject*)(var.address), ss, previous);
			return ss;
		}
	} 
	else if (var.tid & asTYPEID_TEMPLATE) 
	{
		String ss;
		ss += "{\"addr\":\"0x";
		if (var.tid & asTYPEID_OBJHANDLE)
			ss += (int)(*(void**)var.address);
		else
			ss += (int)(var.address);
		ss += "\"}";
		return ss;
	} 
	else if (var.tid & asTYPEID_APPOBJECT) 
	{
		int tid = var.tid;
		bool isHandle = false;

		if (var.tid & asTYPEID_OBJHANDLE) 
		{
			tid |= asTYPEID_OBJHANDLE;
			isHandle = true;
		}
		if (var.address && conversionMethods_.Contains(tid)) {
			String s;
			String name = engine_->GetTypeDeclaration(tid);
			void* target = 0x0;
			if (isHandle) {
				target = *(void**)var.address;
			} else {
				target = var.address;
			}
			if (target)
				s += conversionMethods_[tid](target);
			else
			{
				s += "{\"addr\":\"null ";
				s += name;
				s += "\"}";
			}
			return s;
		} 
		else 
		{
			String ss;
			ss += "{\"addr\":\"0x";
			if (isHandle)
				ss += (int)(*(void**)(var.address));
			else
				ss += (int)var.address;
			ss += " ";
			ss += engine_->GetTypeDeclaration(tid);
			ss += "\"}";
			return ss;
		}
	} 
	else 
	{
		return PrimitiveToString(var);
	}
}

void asPEEK::ProcessMessage(Message& msg)
{
	String command = msg.messageContents.Substring(0,4);
	if (command.Compare("SETT") == 0) 
	{
		//set the value of the "THIS" object
		Vector<String> words;
		String ss(msg.messageContents);

		//bloody tilde delimitter, back to dbase we go
		words = ss.Substring(5).Split('~');
			
		//extract the stack depth from the tree
		words[0].Replace("Stack Level ","");
		const int stackLevel = ToInt(words[0]);
		words.Erase(0);

		asIScriptObject* thisObject = (asIScriptObject*)debuggingContext_->GetThisPointer(stackLevel);
		if (thisObject)
		{
			Variable v(thisObject, thisObject->GetTypeId());
			while (words.Size() > 1)
			{
				QueryResult result = v.Resolve(engine_, words.Front(), words.Back(), queryMethods_);
				if (result == FAILED)
					return;
				if (result == FOUND_AND_SET)
					return;
				words.Erase(0);
			}

			if (v.address && words.Size() == 1)
			{
				FromString(v, words[0]);
			}
		}
	} 
	else if (command.Compare("SETS") == 0)
	{
		//set the value of something on the stack
		Vector<String> words;
		String ss(msg.messageContents);
		words = ss.Substring(5).Split('~');
		int stackLevel = ToInt(words[0]);
		words.Erase(0);
		int varct = debuggingContext_->GetVarCount(stackLevel);
		for (int i = 0; i < varct; ++i)
		{
			String name = debuggingContext_->GetVarName(i, stackLevel);
			if (name.Compare(words[0]) == 0)
			{
				words.Erase(0);
				int tid = debuggingContext_->GetVarTypeId(i, stackLevel);
				void* addr = debuggingContext_->GetAddressOfVar(i, stackLevel);
				Variable v(addr, tid);

				//resolve the variable path
				while (words.Size() > 1)
				{
					QueryResult res = v.Resolve(engine_, words.Front(), words.Back(), queryMethods_);
					if (res == FAILED)
						break;
					if (res == FOUND_AND_SET)
						return;
					words.Erase(0);
				}

				//found it, now set the value
				if (v.address && words.Size() == 1)
				{
					FromString(v,words[0]);
				}
			}
		}
	}
	else if (command.Compare("REQV") == 0) 
	{
		Vector<String> words;
		String ss(msg.messageContents);
		words = ss.Split(' ');

		if (words.Size() == 3) 
		{
			int id;
			id = Urho3D::ToInt(words[1]);
			if (id == 0)
				return;
			if (!sections_.Contains(id))
				return;

			String modName = sections_[id].mod;
			asIScriptModule* module = engine_->GetModule(modName.CString());

			if (module != 0x0 && tracked_modules_.Contains(module))
				SendVariable(words[2], module, msg.conn);
		}

	} 
	else if (command.Compare("GETV") == 0)
	{
		Vector<String> words;
		words = msg.messageContents.Split('?');
		if (words.Size() < 3) 
		{
			SendMessage(msg.conn, String("ERRO Missing variable name"));
			return;
		}

		Variable v = GetGlobalVariable(words);
		if (v.IsValid()) 
		{
			if (v.tid & asTYPEID_SCRIPTOBJECT) 
			{
				HashSet<void*> previous;

				if (v.tid & asTYPEID_OBJHANDLE)
					previous.Insert(*(void**)(v.address));
				else
					previous.Insert(v.address);

				String ss2;
				ss2 += "VARV {";
				ss2 += "\"mod\":\""; ss2 += words[1]; ss2 += "\",";
				ss2 += "\"name\":\""; ss2 += words[2]; ss2 += "\", \"val\":";
				SendMessage(msg.conn, ss2 + ToString(v, &previous) + "}");
			} 
			else 
			{
				String ss2;
				ss2 += "VARV {";
				ss2 += "\"mod\":\""; ss2 += words[1]; ss2 += "\",";
				ss2 += "\"name\":\""; ss2 += words[2]; ss2 += "\", \"val\":";
				SendMessage(msg.conn, ss2 + ToString(v) + "}");
			}
		} 
		else 
		{
			SendMessage(msg.conn, String("LOGW Could not find variable ") + words[2].CString());
		}

	} 
	else if (command == "GETF") 
	{
		Vector<String> words;
		String ss(msg.messageContents);
		words = ss.Split(' ');

		if (words.Size() == 2)
			SendFile(words, msg.conn);

	} 
	else if (command == "BRKS") 
	{

		Vector<String> words;
		String ss(msg.messageContents);
		words = ss.Split(' ');

		if (words.Size() == 3)
		{
			SetBreakpoint(words);
		}

	} 
	else if (command == "BRKR") 
	{

		Vector<String> words;
		String ss(msg.messageContents);
		words = ss.Split(' ');

		if (words.Size() == 3)
		{
			RemoveBreakpoint(words);
		}

	} 
	else if (command == "STOV" || command == "STIN" || command == "CONT" || command == "STOU") 
	{
		Vector<String> words;
		words = msg.messageContents.Split(' ');

		if (debuggingContext_)
			debugCommands_.Push(words[0]);
	} 
	else if (command == "SAVE") 
	{
		// strip command and script section
		int spaceCount = 0;
		unsigned int i = 0;
		unsigned size = msg.messageContents.Length();
		for (; i < size; ++i) 
		{
			if (msg.messageContents[i] == ' ')
				spaceCount++;

			if (spaceCount == 2)
				break;
		}

		int sectionId = Urho3D::ToInt(msg.messageContents.Substring(5,i-5));
		// get section id
		if (sectionId != 0) 
		{
			SendMessage(msg.conn, "LOGE Unable to parse section id: "+ msg.messageContents.Substring(5, i-5));
			return;
		}

		if (!sections_.Contains(sectionId)) 
		{
			SendMessage(msg.conn, String("LOGE Section does not exist id: " + sectionId));
			return;
		}

		msg.messageContents.Erase((size_t)0, (size_t)i+1);
		SectionData *d = &sections_[sectionId];
			
		if (saveSectionFunction_ != 0x0)
			saveSectionFunction_(d->name, msg.messageContents);
		else 
		{
			SendMessage(msg.conn, String("LOGE Save section function is not defined"));
			return;
		}

		String ss;
		ss += "SECM ";
		ss += sectionId;
		SendMessageToAll(ss);

	} 
	else if (command == "EXCT") 
	{

		if (tracked_modules_.Empty())
			return;

		// strip command and script section
		unsigned int moduleEnd = 0;
		unsigned int i = 0;
		unsigned size = msg.messageContents.Length();
		for (; i < size; ++i) 
		{
			if (msg.messageContents[i] == '?')
				moduleEnd = i;
		}

		if (moduleEnd == 0)
			return;

		String moduleName;
		// get module id
		moduleName  = msg.messageContents.Substring(5, moduleEnd-5);

		asIScriptModule *module = 0;
		if (moduleName == "Any") 
		{
			module = *tracked_modules_.Begin();
		} 
		else 
		{
			for (HashSet<asIScriptModule*>::Iterator it = tracked_modules_.Begin(); it != tracked_modules_.End(); ++it) 
			{
				if (moduleName == (*it)->GetName()) 
					module = *it;
			}
		}
		if (msg.messageContents.Length() > moduleEnd+1)
			ExecuteScript(msg.conn, module, msg.messageContents.Substring(moduleEnd+1, msg.messageContents.Length()));

	} 
	else if (command == "RSTR") 
	{
		if (restartFunction_) 
		{
			if (debuggingContext_)
				SendMessage(msg.conn, String("LOGE Currently debugging, can not restart."));
		} 
		else 
		{
			SendMessage(msg.conn, String("LOGE Restart function is not defined"));
		}
	}
}

asPEEK::Variable asPEEK::GetGlobalVariable(Vector<String>& msg)
{
	Vector<String> words;
	words = msg[2].Split(' ');
	String ns = "";
		
	int pos = words[0].Find(":");
	if (pos != String::NPOS) 
	{
		ns = words[0].Substring(0, pos);
		if (ns == " ") 
		{
			ns = "::";
		}
	}

	if (words.Empty()) 
	{
		return Variable();
	} 
	else if (words.Size() == 1) 
	{
		if (ns.Empty()) 
		{
			return GetGlobalVariable(words[0], msg[1], ns);
		} 
		else 
		{
			return GetGlobalVariable(words[0].Substring(pos+2, words[0].Length()), msg[1], ns);
		}
	} 
	else 
	{
		Variable parent;
		if (ns.Empty())
			parent = GetGlobalVariable(words[0], msg[1], ns);
		else
			parent = GetGlobalVariable(words[0].Substring(pos+2, words[0].Length()), msg[1], ns);
			
		if (parent.IsValid()) 
		{
			if (!parent.IsCPPObject()) 
			{
				for (unsigned int i = 1; i < words.Size(); ++i)
					parent = parent.GetMemberVariable(words[i]);
			} 
			else 
			{
				return Variable();
			}
		}
		return parent;
	}
}

asPEEK::Variable asPEEK::GetGlobalVariable(const String& msg, String& modName, const String& ns)
{
	if (modName.Empty()) 
	{
		for (HashSet<asIScriptModule*>::ConstIterator it = tracked_modules_.Begin(); it != tracked_modules_.End(); ++it) 
		{
			if (!ns.Empty())
				(*it)->SetDefaultNamespace(ns.CString());
				
			const int idx = (*it)->GetGlobalVarIndexByName(msg.CString());
			if (idx >= 0) 
			{
				Variable v;
				(*it)->GetGlobalVar(idx, 0, 0, &v.tid, 0);
				v.address = (*it)->GetAddressOfGlobalVar(idx);
				modName = (*it)->GetName();

				if (!ns.Empty())
					(*it)->SetDefaultNamespace("");
				return v;
			}
			if (!ns.Empty())
				(*it)->SetDefaultNamespace("");
		}
	} 
	else 
	{
		asIScriptModule* mod = engine_->GetModule(modName.CString());

		if (mod) 
		{
			if (!ns.Empty())
				mod->SetDefaultNamespace(ns.CString());

			const int idx = mod->GetGlobalVarIndexByName(msg.CString());
			Variable v;
			mod->GetGlobalVar(idx, 0, 0, &v.tid, 0);
			v.address = mod->GetAddressOfGlobalVar(idx);

			if (!ns.Empty())
				mod->SetDefaultNamespace("");

			return v;

		}
	}
	return Variable();
}

asPEEK::Variable asPEEK::GetMemberVariable(const String& varname, asIScriptObject* obj) {
	const unsigned int mcount = obj->GetPropertyCount();

	for (unsigned int i= 0; i < mcount; ++i) 
	{
		if (varname == obj->GetPropertyName(i)) 
			return Variable( obj->GetAddressOfProperty(i), obj->GetPropertyTypeId(i) ); 
	}

	return Variable();
}

String asPEEK::PrimitiveToString(const Variable& var){
	if (var.tid > asTYPEID_DOUBLE) 
	{ // this is enumeration
		String ss;
		ss += "\"";
		ss += *(asUINT*) var.address;

		bool found = false;
		int ecount = engine_->GetEnumCount();
		for (int i = 0; i < ecount; ++i) 
		{
			int tid;
			engine_->GetEnumByIndex(i, &tid);
			if (var.tid == tid) 
			{
				found  = true;
				const char *c = engine_->GetEnumValueByIndex(tid, i, 0);
				if (c) 
				{
					ss += " ("; 
					ss += c;
					ss += ")";
				}
			}
		}

		//TODO, this part needs improvent, we are looping over all modules' enums to find a name.
		// would be good if we knew beforehand which module we look it in
		if (!found) 
		{
			for (HashSet<asIScriptModule*>::Iterator it = tracked_modules_.Begin(); it != tracked_modules_.End(); ++it) 
			{
				ecount = (*it)->GetEnumCount();

				for (int i = 0; i < ecount; ++i) 
				{
					int tid;
					(*it)->GetEnumByIndex(i, &tid);
					if (var.tid == tid) 
					{
						const char *c = (*it)->GetEnumValueByIndex(tid, i, 0);
						if (c) 
						{
							ss += " (";
							ss += c;
							ss += ")";
						}
					}
				}
			}
		}
		ss += "\"";
		return ss;
	} 
	else 
	{
		switch (var.tid) 
		{
		case asTYPEID_BOOL:
			if (*(bool*)var.address)
				return "true";
			else
				return "false";
		case asTYPEID_FLOAT:
			{
				String ss;
				ss += *(float*)var.address;
				return ss;
			}
		case asTYPEID_DOUBLE:
			{
				String ss;
				ss += (float)(*(double*)var.address);
				return ss;
			}
		case asTYPEID_INT8:
			{
				String ss;
				ss += *(char*)var.address;
				return ss;
			}
		case asTYPEID_INT16:
			{
				String ss;
				ss += *(short*)var.address;
				return ss;
			}
		case asTYPEID_INT32:
			{
				String ss;
				ss += *(int*)var.address;
				return ss;
			}
		case asTYPEID_INT64:
			{
				String ss;
				ss += (int)(*(long*)var.address);
				return ss;
			}
		case asTYPEID_UINT8:
			{
				String ss;
				ss += (unsigned short)(*(unsigned char*)var.address);
				return ss;
			}
		case asTYPEID_UINT16:
			{
				String ss;
				ss += *(unsigned short*)var.address;
				return ss;
			}
		case asTYPEID_UINT32:
			{
				String ss;
				ss += *(unsigned int*)var.address;
				return ss;
			}
		case asTYPEID_UINT64:
			{
				String ss;
				ss += (int)(*(unsigned long*)var.address);
				return ss;
			}
		default:
			return "\"Primitive?\"";
			break;
		}
	}
}

void asPEEK::PrimitiveFromString(const Variable& var, const String& value)
{
	switch (var.tid) 
	{
	case asTYPEID_BOOL:
		*(bool*)var.address = ToBool(value);
		return;
	case asTYPEID_FLOAT:
		*(float*)var.address = ToFloat(value);
		return;
	case asTYPEID_DOUBLE:
		*(double*)var.address = (double)ToFloat(value);
		return;
	case asTYPEID_INT8:
		*(char*)var.address = value[0];
		return;
	case asTYPEID_INT16:
		*(short*)var.address = (short)ToInt(value);
		return;
	case asTYPEID_INT32:
		*(int*)var.address = ToInt(value);
		return;
	case asTYPEID_INT64:
		*(long*)var.address = (long)ToInt(value);
		return;
	case asTYPEID_UINT8:
		*(unsigned char*)var.address = value[0];
		return;
	case asTYPEID_UINT16:
		*(unsigned short*)var.address = (unsigned short)ToUInt(value);
		return;
	case asTYPEID_UINT32:
		*(unsigned int*)var.address = ToUInt(value);
		return;
	case asTYPEID_UINT64:
			*(unsigned long*)var.address = (unsigned long)ToUInt(value);
			return;
	}
}

void asPEEK::ScriptObjectToString(asIScriptObject* obj, String& ss, HashSet<void*> *previous)
{
	if (!obj) 
	{ 
		ss += "{\"addr\":\"null\"}";
		return;
	}
	ss += "{"; // every object starts with curly open
	ss += "\"_\":\"";
	ss += obj->GetObjectType()->GetName();
	ss += "\"";

	unsigned int pcount = obj->GetPropertyCount();

	if (pcount)
		ss += ",";

	for (unsigned int i = 0; i < pcount; ++i) 
	{
		ss += "\"";
		ss += obj->GetPropertyName(i);
		ss += "\":";
		int tid = obj->GetPropertyTypeId(i);

		if (tid & asTYPEID_SCRIPTOBJECT) 
		{
			if (previous) 
			{
				void *v = 0;
				void *t = obj->GetAddressOfProperty(i);
				if (tid & asTYPEID_OBJHANDLE)
					v = *(void**)obj->GetAddressOfProperty(i);
				else
					v = obj->GetAddressOfProperty(i);

				if (!v) 
				{
					ss += "{\"addr\":\"null\"}";

					if (i != (pcount - 1) )
						ss += ","; // comma between each member, but not to last one

					continue;
				} 
				else
				{
					if (previous->Contains(v)) 
					{		
						ss += "{\"[REPEAT]\":\"0x";
						ss += (int)v;
						ss += "\"}";

						if (i != (pcount - 1) )
							ss += ","; // comma between each member, but not to last one 

						continue;
					} 
					else 
					{
						previous->Insert(v);  
					}
				}
			}
		}

		Variable v(obj->GetAddressOfProperty(i), tid);

		ss += ToString(v, previous).CString();

		if (i != (pcount - 1) )
			ss += ","; // comma between each member, but not to last one 

	}

	ss += "}"; // every object ends with curly close
}

void asPEEK::SetBreakpoint(const Vector<String>& words)
{
	int secId = Urho3D::ToInt(words[1]);
	int line = Urho3D::ToInt(words[2]);
	bool isSet = false;

	if (sections_.Contains(secId)) 
	{
		if (!sections_[secId].breakpoints.Contains(line)) 
		{
			sections_[secId].breakpoints.Insert(line);
			isSet = true;
		}
	}

	if (isSet) 
	{
		String ss;
		ss += "BSET ";
		ss += secId;
		ss += " ";
		ss += line;
		SendMessageToAll(ss);
	}
}

void asPEEK::RemoveBreakpoint(const Vector<String>& words)
{
	int secId = Urho3D::ToInt(words[1]);
	int line = Urho3D::ToInt(words[2]);
	bool isRemoved = false;

	if (sections_.Contains(secId)) 
	{// section should exist
		if (sections_[secId].breakpoints.Contains(line)) 
		{
			sections_[secId].breakpoints.Erase(line);
			isRemoved = true;
		}
	}

	if (isRemoved) 
	{
		String ss;
		ss += "BREM ";
		ss += secId;
		ss += " ";
		ss += line;
		SendMessageToAll(ss);
	}
}

void asPEEK::SendDebugData(asIScriptContext* ctx, int line, SectionData* section) {
	for (unsigned int i = 0; i < connectionList_.Size(); ++i) {
		mg_connection* conn = connectionList_[i];
		SendThisObject(conn, ctx);
		SendGlobalVariables(conn,ctx);
		SendLocalVariables(conn, ctx);
		SendCurrentLine(conn);
		SendStack(conn, ctx);
	}
}

void asPEEK::Debug(asIScriptContext* ctx, int line, SectionData* section)
{
	SendDebugData(ctx,line,section);

	while (!debugInterrupt_) 
	{// wait commands from client

		String command = "";
		if (!debugCommands_.Empty())
		{
			command = debugCommands_[0];
			debugCommands_.Erase(0);
		}

		if (command != "") 
		{
			if (command == "STOV") 
			{
				nextDebugCommand_ = STEPOVER;
				debuggingStackLevel_ = ctx->GetCallstackSize();
				break; // break out of wait cycle
			} 
			else if ( command == "CONT") 
			{
				nextDebugCommand_ = CONTINUE;
				break; // break out of wait cycle
			} 
			else if (command == "STIN") 
			{
				nextDebugCommand_ = STEPIN;
				debuggingStackLevel_ = ctx->GetCallstackSize();
				break; // break out of wait cycle
			} 
			else if (command == "STOU") 
			{
				nextDebugCommand_ = STEPOUT;
				debuggingStackLevel_ = ctx->GetCallstackSize();
				break; // break out of wait cycle
			}
		}
	}
}

void asPEEK::SendGlobalVariables(mg_connection* conn, asIScriptContext* ctx) 
{
	String ss;
	ss += "GLOV [";
	unsigned int ssize = engine_->GetGlobalPropertyCount();
	for (unsigned int i = 0; i < ssize; ++i) 
	{
		ss += "{";

		int tid = 0;
		const char* name = 0;
		void* addr = 0x0;
		engine_->GetGlobalPropertyByIndex(i, &name, 0, &tid, 0x0 /*isConst*/, 0x0 /*configGroup*/, &addr);
		ss += "\"";
		ss += name;
		ss += "\"";
		ss += ":";

		if (tid & asTYPEID_SCRIPTOBJECT) 
		{
			HashSet<void*> previous;
			if (tid & asTYPEID_OBJHANDLE)
				previous.Insert(*(void**)addr);
			else
				previous.Insert(addr);
			ss += ToString(Variable(addr, tid), &previous).CString();
		} else
			ss += ToString(Variable(addr, tid)).CString();

		ss += "}";
		if (i != ssize - 1)
			ss += ",";
	}
	ss += "]";
	SendMessage(conn, ss);
}

void asPEEK::SendLocalVariables(mg_connection* conn, asIScriptContext* ctx)
{
	String ss;
	ss += "LOCV [";
	unsigned int ssize = ctx->GetCallstackSize();
	for (unsigned int i = 0; i < ssize; ++i) 
	{
		ss += "{";
		int varCount = ctx->GetVarCount(i);

		for (int i2 = 0; i2 < varCount; ++i2) 
		{
			void *addr = ctx->GetAddressOfVar(i2, i);

			int tid = ctx->GetVarTypeId(i2, i);
			ss += "\"";
			ss += ctx->GetVarName(i2, i);
			ss += "\"";
			ss += ":";

			if (!addr) 
			{
				ss += "\"undefined\"";
			} 
			else 
			{
				if (tid & asTYPEID_SCRIPTOBJECT) 
				{
					HashSet<void*> previous;
					if (tid & asTYPEID_OBJHANDLE)
						previous.Insert(*(void**)addr);
					else
						previous.Insert(addr);
					ss += ToString(Variable(addr, tid), &previous).CString();
				} 
				else
					ss += ToString(Variable(addr, tid)).CString();
			}
			if (i2 != (varCount - 1))
				ss += ",";
		}
		ss += "}";
		if (i != ssize - 1)
			ss += ",";
	}
	ss += "]";
	SendMessage(conn, ss);
}

void asPEEK::SendThisObject(mg_connection* conn, asIScriptContext* ctx)
{
	asIScriptObject *obj = (asIScriptObject*) ctx->GetThisPointer();
	if (obj) 
	{
		String ss;
		ss += "THIS ";
		ss += ctx->GetCallstackSize()-1;
		ss += " {";
		unsigned int pcount = obj->GetPropertyCount();
		for (unsigned int i = 0; i< pcount; ++i) 
		{
			int tid = obj->GetPropertyTypeId(i);
			ss += "\"";
			ss += obj->GetPropertyName(i);
			ss += "\"";
			ss += ":";

			void *v = obj->GetAddressOfProperty(i);
			if (!v) 
			{
				ss += "{\"addr\":\"null\"}";
			} 
			else 
			{
				if (tid & asTYPEID_SCRIPTOBJECT) 
				{
					HashSet<void*> previous;
					previous.Insert(obj);
					if (tid & asTYPEID_OBJHANDLE)
						previous.Insert(*(void**)v);
					else
						previous.Insert(v);

					ss += ToString(Variable(v, tid), &previous).CString();
				} 
				else 
				{
					ss += ToString(Variable(v, tid)).CString();
				}
			}

			if (i < (pcount-1))
				ss += ",";
		}
		ss += "}";
		SendMessage(conn, ss);
	}
}

void asPEEK::SendStack(mg_connection* conn, asIScriptContext* ctx)
{
	const unsigned int ssize = ctx->GetCallstackSize();
	String ss;
	ss += "STCK [";
	for (unsigned int i = 0; i < ssize; ++i) 
	{
		const char *sectionName;
		int column;
		int lineNumber = ctx->GetLineNumber(i, &column, &sectionName);

		if (!sectionName)
			continue;
		if (!sectionIds_.Contains(sectionName))
			continue;

		ss += "{";
		ss += "\"l\":"; ss += lineNumber; ss += ",";
		ss += "\"c\":"; ss += column; ss += ",";
		ss += "\"s\":"; ss += sectionIds_[sectionName]; ss += ",";
		ss += "\"f\":\""; ss += ctx->GetFunction(i)->GetDeclaration(); ss += "\"";
		ss += "}";

		if (i != ssize -1) {
			ss += ",";
		}
	}
	ss += "]";
	SendMessage(conn, ss);
}

void asPEEK::NewClient(mg_connection* conn)
{
	SendModuleNames(conn);
	SendSectionNames(conn);
	SendContexts(conn);
	if (debuggingContext_) 
	{
		SendLocalVariables(conn, debuggingContext_);
		SendThisObject(conn, debuggingContext_);
		SendCurrentLine(conn);
		SendStack(conn, debuggingContext_);
	}
}

void asPEEK::SendVariable(const String& varname, asIScriptModule* mod, mg_connection* conn) 
{
	Vector<String> words;
	words = varname.Split('.');

	if (words.Empty())
		return;

	// this gets the most parent object
	Variable var = GetVariableByName(words, mod);

	if (!var.address)
		return;

	if (words.Size() > 1) 
	{
		// should be an object type or else client sent a mangled string
		if (var.tid & asTYPEID_SCRIPTOBJECT) 
		{
			// remove most parent
			words.Erase(0);
			if (var.tid & asTYPEID_OBJHANDLE)
				var = GetChildOfObject(words, *(asIScriptObject**) var.address);
			else
				var = GetChildOfObject(words, (asIScriptObject*) var.address);

			// send value
		}
	}
		
	String ss;
	ss += "REQV ";
	ss += varname.CString();
	ss += " ";

	if (var.tid & asTYPEID_SCRIPTOBJECT) 
	{
		HashSet<void*> previous;

		if (var.tid & asTYPEID_OBJHANDLE)
			previous.Insert(*(void**)var.address);
		else
			previous.Insert(var.address);

		ss += ToString(var, &previous).CString();
	}
	else
		ss += ToString(var).CString();

	SendMessage(conn, ss);
}

asPEEK::Variable asPEEK::GetVariableAtLocalStack(const String& varname)
{
	if (!debuggingContext_)
		return Variable();

	unsigned int ssize = debuggingContext_->GetCallstackSize();

	for (unsigned int i = 0; i < ssize; ++i)
	{
		int vcount = debuggingContext_->GetVarCount(i);

		for (int j = 0; j < vcount ; ++j)
		{
			if (varname == debuggingContext_->GetVarName(j, i))
			{
				return Variable(debuggingContext_->GetAddressOfVar(j, i), debuggingContext_->GetVarTypeId(j, i));
			}
		}
	}

	return Variable();
}

asPEEK::Variable asPEEK::GetVariableByName(const Vector<String>& name, asIScriptModule* mod)
{
	// we should first determine if this object is local/global/member
	Variable var;
	String ns = ""; // namespace

	int pos = name[0].Find("::");

	if (pos != String::NPOS) 
	{
		ns = name[0].Substring(0, pos);

		if (ns == "") // user might want global scope ::Myint
			ns = "::";
	}

	// only if it doesn't have namespace. only global variables have namespaces
	if (ns == "") 
	{
		var = GetVariableAtLocalStack(name[0]);

		if (var.address)
			return var;


		//boost::mutex::scoped_lock lock(debugging_mutex);
		if (debuggingContext_) 
		{
			if (debuggingContext_->GetThisPointer()) 
			{
				asIScriptObject *t = (asIScriptObject*) debuggingContext_->GetThisPointer();
				//lock.unlock();
				var = GetMemberVariable(name[0].CString(), t);

				if (var.address)
					return var;
			}
		}
	}

	String modName = mod->GetName(); // look in all modules
	if (ns == "")
		var = GetGlobalVariable(name[0], modName, ns.CString()); // see if this is a global variable
	else
		var = GetGlobalVariable((name[0].Substring(pos+2, name[0].Length())).CString(), modName, ns.CString()); // see if this is a global variable

	if (var.address)
		return var;

	return Variable();
}

asPEEK::Variable asPEEK::GetChildOfObject(Vector<String>& member, asIScriptObject* obj)
{
	Variable v;
	for (unsigned int i = 0; i < member.Size(); ++i) 
	{
		v = GetMemberVariable(member[i].CString(), obj);

		if (!v.address)
			return Variable(); // we failed sorry :(

		if (v.tid & asTYPEID_SCRIPTOBJECT)
		{
			if (v.tid & asTYPEID_OBJHANDLE)
				obj = *(asIScriptObject**)v.address;
			else
				obj = (asIScriptObject*)v.address;
		}
		else // only acceptable if loop is over
		{
			if (i == member.Size() -1)
				return v;
			else
				return Variable();
		}
	}

	return v;
}

void asPEEK::ExecuteScript(mg_connection* conn, asIScriptModule* mod, const String& script)
{
	if (mod) 
	{
		String funcCode = "void asPEEK_Execute() {\n";
		funcCode += script;
		funcCode += "\n;}";

		// Compile the function that can be executed
		asIScriptFunction *func = 0;
		if (!ctx_->GetSubsystem<Script>()->Execute(script)) 
		{
			SendMessage(conn, String("EXCT Was not able to compile"));
			return;
		}

		SendMessage(conn, String("EXCT Execution Successful."));
	}
}

void asPEEK::EndDebugging()
{
	debuggingLine_ = 0;
	debuggingSection_ = 0;
	nextDebugCommand_ = CONTINUE;
	debuggingContext_ = 0;

	if (debuggingEndedFunction_)
		debuggingEndedFunction_();

	SendMessageToAll("CONT");
}

void asPEEK::AddContext(asIScriptContext* ctx)
{
	ctx->SetLineCallback(asMETHOD(asPEEK, LineCallback), this, asCALL_THISCALL);
	tracked_context_[contextCount_] = ctx;
	contextCount_++;
	for (unsigned int i = 0; i < this->connectionList_.Size(); ++i)
		SendContexts(connectionList_[i]);
}

void asPEEK::ContextIsInactive(asIScriptContext* ctx){
	if (ctx == debuggingContext_)
		EndDebugging();
}

void asPEEK::RemoveContext(asIScriptContext* ctx)
{
	for (HashMap<int, asIScriptContext*>::Iterator it = tracked_context_.Begin(); it != tracked_context_.End() ; ++it) 
	{
		if (it->second_ == ctx) 
		{
			ContextIsInactive(ctx);
			tracked_context_.Erase(it);
			break;
		}
	}
	for (unsigned int i = 0; i < this->connectionList_.Size(); ++i)
		this->SendContexts(connectionList_[i]);
}

void asPEEK::AddModule(asIScriptModule* mod)
{
	//make sure we haven't already tracked it
    if (tracked_modules_.Contains(mod))
		return;
	tracked_modules_.Insert(mod);
	for (unsigned int i = 0; i < this->connectionList_.Size(); ++i)
		SendModuleNames(connectionList_[i]);
}

void asPEEK::RemoveModule(asIScriptModule* mod)
{
	tracked_modules_.Erase(mod);
	for (unsigned int i = 0; i < this->connectionList_.Size(); ++i)
		SendModuleNames(connectionList_[i]);
}

void asPEEK::AddScriptSection(const String& name, const String& mod)
{
	// check for existing script section
	for (unsigned int i = 0; i < sections_.Size(); ++i)
	{
		if (sections_[i].name == name)
			return;
	}
	SectionData d;
	d.id = sectionCount_;
	d.name = name;
	d.mod = mod;
	sectionIds_[name] = sectionCount_;
	sections_[d.id] = d;
	sectionCount_++;
	for (unsigned int i = 0; i < this->connectionList_.Size(); ++i)
		SendSectionNames(connectionList_[i]);
}

void asPEEK::RemoveScriptSection(const String &name){ // UNTESTED
	if (sectionIds_.Contains(name)) 
	{
		const int id = sectionIds_[name];
		sectionIds_.Erase(name);
		sections_.Erase(id);
	}
	for (unsigned int i = 0; i < this->connectionList_.Size(); ++i)
		SendSectionNames(connectionList_[i]);
}

void asPEEK::SendLogMessageToAll(const String &msg)
{
	SendMessageToAll("LOGI " + msg);
}

void asPEEK::SendMessageToAll(const String &msg)
{
	for (unsigned int i = 0; i < connectionList_.Size(); ++i) 
	{
		if (connectionList_[i])
			::mg_websocket_write(connectionList_[i], WEBSOCKET_OPCODE_TEXT, msg.CString(), msg.Length());
	}
}

void asPEEK::SendMessage(mg_connection* conn, String& msg) 
{
	::mg_websocket_write(conn, WEBSOCKET_OPCODE_TEXT, msg.CString(), msg.Length());
}

bool asPEEK::AddBreakpoint(const String& section, int line)
{
	if (!sectionIds_.Contains(section))
		return false;
	SectionData* d = &sections_[sectionIds_[section]];
	if (d->breakpoints.Contains(line))
		return false;
	d->breakpoints.Insert(line);
	return true;
}

bool asPEEK::RemoveBreakpoint(const String& section, int line) 
{
	if (!sectionIds_.Contains(section))
		return false;
	SectionData* d = &sections_[sectionIds_[section]];
	if (d->breakpoints.Contains(line)) 
	{
		d->breakpoints.Erase(line);
		return true;
	}
	return false;
}

asPEEK::SectionData* asPEEK::GetSectionData(const String& section) 
{
	asPEEK::SectionData *d = 0;
	// check if that section is added to asPEEK
	HashMap<String, int>::Iterator s = sectionIds_.Find(section);
	if (s == sectionIds_.End())
		return 0;
	d = &sections_[s->second_];

	return d;

}

void asPEEK::DefaultLoadSectionFunction(const String &filename, String &script) 
{
	std::ifstream ifs;
	String ss = "Data/";
	ss += filename;
	ifs.open(ss.CString(), std::ifstream::in);

	int ch = ifs.get();
	while (ifs.good()) 
	{
		script += (char) ch;
		ch = ifs.get();
	}

	ifs.close();

}

void asPEEK::DefaultSaveSectionFunction(const String& filename, String& code) 
{
	std::ofstream ofs;
	String fl = "Data/";
	fl += filename;
	ofs.open(fl.CString(), std::ofstream::out);
	ofs.write(code.CString(),code.Length());
	ofs.close();
}

void asPEEK::RegisterConversion(const String& typeName, TYPE_CONVERTER method, ASSIGNMENT_METHOD assigner, MEMBER_QUERY_METHOD query)
{
	tempConversionMap_[typeName] = method;
	tempConversionMap_[typeName + "@"] = method; //add node handle conversion

	if (assigner)
	{
		tempAssignmentsMap_[typeName] = assigner;
		tempAssignmentsMap_[typeName + "@"] = assigner;
	}

	if (query)
	{
		queryMethods_[typeName] = query;
		queryMethods_[typeName + "@"] = query;
	}
}

void asPEEK::UpdateTypeConversions() 
{
	Vector<String> keys = tempConversionMap_.Keys();
	for (unsigned int i = 0; i < keys.Size(); ++i) 
	{
		int tid = engine_->GetTypeIdByDecl(keys[i].CString());
		if (tid != 0) 
		{
			conversionMethods_[tid] = tempConversionMap_[keys[i]];
		}
	}
	keys = tempAssignmentsMap_.Keys();
	for (unsigned int i = 0; i < keys.Size(); ++i)
	{
		int tid = engine_->GetTypeIdByDecl(keys[i].CString());
		if (tid != 0)
			assignmentMethods_[tid] = tempAssignmentsMap_[keys[i]];
	}
}


}