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
#pragma once

/** @file SerializedDataIterator.h
	@brief The SerializedDataIterator class. */

#include "SharedPtr.h"
#include "MessageListParser.h"

namespace kNet
{

class SerializedDataIterator : public RefCountable
{
public:
	SerializedDataIterator(const SerializedMessageDesc &desc_)
	:desc(desc_)
	{
		ResetTraversal();
	}

	BasicSerializedDataType NextElementType() const;

	const SerializedElementDesc *NextElementDesc() const;

	void ProceedToNextVariable();

	void ProceedNVariables(int count);

	/// Sets the number of instances in a varying element. When iterating over
	/// the message to insert data into serialized form, this information needs
	/// to be passed to this iterator in order to continue.
	void SetVaryingElemSize(u32 count);

	void ResetTraversal();

private:
	struct ElemInfo
	{
		/// The element we are accessing next.
		SerializedElementDesc *elem;
		/// The index of the elem we are accessing next.
		int nextElem;
		/// The index of the instance we are accessing next.
		int nextIndex;
		/// The total number of instances of this element we are accessing.
		int count;
		/// If this element is a dynamic count -one, then this tracks whether the count has been passed in.
		bool dynamicCountSpecified;
	};

	void ProceedToNextElement();
	void DescendIntoStructure();

	/// Stores the tree traversal progress.
	std::vector<ElemInfo> currentElementStack;
	/// The type of the message we are building.
	const SerializedMessageDesc &desc;

	void operator =(const SerializedDataIterator&);
	SerializedDataIterator(const SerializedDataIterator&);
};

} // ~kNet
