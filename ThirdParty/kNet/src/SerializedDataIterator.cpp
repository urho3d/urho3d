/* Copyright 2010 Jukka Jylänki

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */

/** @file SerializedDataIterator.cpp
	@brief */

// Modified by Lasse Öörni for Urho3D

#include <cassert>

#include "kNet/DebugMemoryLeakCheck.h"

#include "kNet/SerializedDataIterator.h"

namespace kNet
{

BasicSerializedDataType SerializedDataIterator::NextElementType() const
{
	if (currentElementStack.Size() == 0)
		return SerialInvalid;

	assert(currentElementStack.Back().elem);

	// If we don't know how many instances there are of the next element, it's the next field 
	// to be filled - our iterator is pointing to the dynamicCount property of that field.
	if (currentElementStack.Back().elem->varyingCount && currentElementStack.Back().dynamicCountSpecified == false)
		return SerialDynamicCount;

	return currentElementStack.Back().elem->type;
}

const SerializedElementDesc *SerializedDataIterator::NextElementDesc() const
{
	return currentElementStack.Size() > 0 ? currentElementStack.Back().elem : 0;
}

void SerializedDataIterator::ProceedToNextVariable()
{
	if (currentElementStack.Size() == 0)
		return;

	ElemInfo &nextVar = currentElementStack.Back();

	if (nextVar.elem->type == SerialStruct)
	{
		++nextVar.nextElem;
		if (nextVar.nextElem >= (int)nextVar.elem->elements.Size())
		{
			nextVar.nextElem = 0;
			++nextVar.nextIndex;
			if (nextVar.nextIndex >= nextVar.count)
			{
				currentElementStack.Pop();
				ProceedToNextVariable();
				return;
			}
		}

		DescendIntoStructure();
	}
	else
	{
		++nextVar.nextIndex;
		if (nextVar.nextIndex >= nextVar.count)
		{
			currentElementStack.Pop();
			ProceedToNextVariable();
		}
	}
}

void SerializedDataIterator::ProceedNVariables(int count)
{
	///\todo Can optimize a great deal here.
	for(int i = 0; i < count; ++i) 
		ProceedToNextVariable();
}

void SerializedDataIterator::ProceedToNextElement()
{
	ElemInfo &nextVar = currentElementStack.Back();

	++nextVar.nextElem;
	if (nextVar.nextElem >= (int)nextVar.elem->elements.Size())
	{
		nextVar.nextElem = 0;
		++nextVar.nextIndex;
		if (nextVar.nextIndex >= nextVar.count)
		{
			currentElementStack.Pop();
			ProceedToNextElement();
		}
	}
	else
	{
/*		currentElementStack.Push(ElemInfo());
		ElemInfo &newVar = currentElementStack.back();
		newVar.elem = nextVar.elem->elements[nextVar.nextElem];
		newVar.nextIndex = 0;
		newVar.nextElem = 0;
		newVar.count = (newVar.elem->multiplicity == ElemVarying) ? 0 : newVar.elem->count;
*/
		DescendIntoStructure();
	}
}

void SerializedDataIterator::SetVaryingElemSize(u32 count)
{
	ElemInfo &nextVar = currentElementStack.Back();
	assert(nextVar.dynamicCountSpecified == false);
	assert(nextVar.elem->varyingCount == true);
	assert(nextVar.nextIndex == 0);
	nextVar.count = count;
	nextVar.dynamicCountSpecified = true;

	// If this was a varying-arity structure node, descend down into filling the struct.
	DescendIntoStructure();
}

void SerializedDataIterator::DescendIntoStructure()
{
	ElemInfo &nextVar = currentElementStack.Back();

	if (nextVar.dynamicCountSpecified == false && nextVar.elem->varyingCount == true)
		return;
	if (nextVar.nextElem >= (int)nextVar.elem->elements.Size())
		return;

	ElemInfo newVar;
	newVar.elem = nextVar.elem->elements[nextVar.nextElem];
	newVar.nextIndex = 0;
	newVar.nextElem = 0;
 	newVar.count = (newVar.elem->varyingCount ? 0 : newVar.elem->count); // A varying block? Then the user has to supply multiplicity.
	newVar.dynamicCountSpecified = false;
	currentElementStack.Push(newVar);

	// Descend again in case we have a struct-in-struct-in-struct...
	DescendIntoStructure();
}

void SerializedDataIterator::ResetTraversal()
{
	currentElementStack.Clear();

	ElemInfo newVar;
	newVar.elem = desc.data;
	newVar.nextIndex = 0;
	newVar.nextElem = 0;
 	newVar.count = (newVar.elem->varyingCount ? 0 : newVar.elem->count); // A varying block? Then the user has to supply multiplicity.
	newVar.dynamicCountSpecified = false;
	currentElementStack.Push(newVar);

	// Descend again in case we have a struct-in-struct-in-struct...
	DescendIntoStructure();
}

} // ~kNet
