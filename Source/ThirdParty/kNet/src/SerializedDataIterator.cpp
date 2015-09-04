/* Copyright The kNet Project.

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

#include <cassert>

#include "kNet/DebugMemoryLeakCheck.h"

#include "kNet/SerializedDataIterator.h"

namespace kNet
{

BasicSerializedDataType SerializedDataIterator::NextElementType() const
{
	if (currentElementStack.empty())
		return SerialInvalid;

	assert(currentElementStack.back().elem);

	// If we don't know how many instances there are of the next element, it's the next field 
	// to be filled - our iterator is pointing to the dynamicCount property of that field.
	if (currentElementStack.back().elem->varyingCount && currentElementStack.back().dynamicCountSpecified == false)
		return SerialDynamicCount;

	return currentElementStack.back().elem->type;
}

const SerializedElementDesc *SerializedDataIterator::NextElementDesc() const
{
	return currentElementStack.empty() ? 0 : currentElementStack.back().elem;
}

void SerializedDataIterator::ProceedToNextVariable()
{
	if (currentElementStack.empty())
		return;

	ElemInfo &nextVar = currentElementStack.back();

	if (nextVar.elem->type == SerialStruct)
	{
		++nextVar.nextElem;
		if (nextVar.nextElem >= (int)nextVar.elem->elements.size())
		{
			nextVar.nextElem = 0;
			++nextVar.nextIndex;
			if (nextVar.nextIndex >= nextVar.count)
			{
				currentElementStack.pop_back();
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
			currentElementStack.pop_back();
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
	ElemInfo &nextVar = currentElementStack.back();

	++nextVar.nextElem;
	if (nextVar.nextElem >= (int)nextVar.elem->elements.size())
	{
		nextVar.nextElem = 0;
		++nextVar.nextIndex;
		if (nextVar.nextIndex >= nextVar.count)
		{
			currentElementStack.pop_back();
			ProceedToNextElement();
		}
	}
	else
	{
/*		currentElementStack.push_back(ElemInfo());
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
	ElemInfo &nextVar = currentElementStack.back();
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
	ElemInfo &nextVar = currentElementStack.back();

	if (nextVar.dynamicCountSpecified == false && nextVar.elem->varyingCount == true)
		return;
	if (nextVar.nextElem >= (int)nextVar.elem->elements.size())
		return;

	ElemInfo newVar;
	newVar.elem = nextVar.elem->elements[nextVar.nextElem];
	newVar.nextIndex = 0;
	newVar.nextElem = 0;
 	newVar.count = (newVar.elem->varyingCount ? 0 : newVar.elem->count); // A varying block? Then the user has to supply multiplicity.
	newVar.dynamicCountSpecified = false;
	currentElementStack.push_back(newVar);

	// Descend again in case we have a struct-in-struct-in-struct...
	DescendIntoStructure();
}

void SerializedDataIterator::ResetTraversal()
{
	currentElementStack.clear();

	ElemInfo newVar;
	newVar.elem = desc.data;
	newVar.nextIndex = 0;
	newVar.nextElem = 0;
 	newVar.count = (newVar.elem->varyingCount ? 0 : newVar.elem->count); // A varying block? Then the user has to supply multiplicity.
	newVar.dynamicCountSpecified = false;
	currentElementStack.push_back(newVar);

	// Descend again in case we have a struct-in-struct-in-struct...
	DescendIntoStructure();
}

} // ~kNet
