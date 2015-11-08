// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_OBJECT_H
#define TB_OBJECT_H

#include "tb_core.h"
#include "tb_linklist.h"

namespace tb {

typedef void* TB_TYPE_ID;

/*  TBTypedObject implements custom RTTI so we can get type safe casts,
	and the class name at runtime.

	Each subclass is expected to define TBOBJECT_SUBCLASS to get the
	necessary implementations, instead of implementing those manually. */
class TBTypedObject
{
public:
	virtual ~TBTypedObject() {}

	/** A static template method that returns a unique id for each type. */
	template<class T> static TB_TYPE_ID GetTypeId() { static char type_id; return &type_id; }

	/** Returns true if the class or the base class matches the type id */
	virtual bool IsOfTypeId(const TB_TYPE_ID type_id) const { return type_id == GetTypeId<TBTypedObject>(); }

	/** Returns this object as the given type or nullptr if it's not that type. */
	template<class T> T *SafeCastTo() const { return (T*) (IsOfTypeId(GetTypeId<T>()) ? this : nullptr); }

	/** Return true if this object can safely be casted to the given type. */
	template<class T> bool IsOfType() const { return SafeCastTo<T>() ? true : false; }

	/** Get the classname of the object. */
	virtual const char *GetClassName() const { return "TBTypedObject"; }
};

/** Returns the given object as the given type, or nullptr if it's not that type
	or if the object is nullptr. */
template<class T> T *TBSafeCast(TBTypedObject *obj) {
	return obj ? obj->SafeCastTo<T>() : nullptr;
}

/** Returns the given object as the given type, or nullptr if it's not that type
	or if the object is nullptr. */
template<class T> const T *TBSafeCast(const TBTypedObject *obj) {
	return obj ? obj->SafeCastTo<T>() : nullptr;
}

/** Implement the methods for safe typecasting without requiring RTTI. */
#define TBOBJECT_SUBCLASS(clazz, baseclazz) \
	virtual const char *GetClassName() const { return #clazz; } \
	virtual bool IsOfTypeId(const tb::TB_TYPE_ID type_id) const \
		{ return GetTypeId<clazz>() == type_id ? true : baseclazz::IsOfTypeId(type_id); }

}; // namespace tb

#endif // TB_OBJECT_H
