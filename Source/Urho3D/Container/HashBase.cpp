//
// Copyright (c) 2008-2014 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "../Container/HashBase.h"

#include "../DebugNew.h"

namespace Urho3D
{

void HashBase::AllocateBuckets(unsigned size, unsigned numBuckets)
{
    if (ptrs_)
        delete[] ptrs_;
    
    HashNodeBase** ptrs = new HashNodeBase*[numBuckets + 2];
    unsigned* data = reinterpret_cast<unsigned*>(ptrs);
    data[0] = size;
    data[1] = numBuckets;
    ptrs_ = ptrs;
    
    ResetPtrs();
}

void HashBase::ResetPtrs()
{
    // Reset bucket pointers
    if (!ptrs_)
        return;
    
    unsigned numBuckets = NumBuckets();
    HashNodeBase** ptrs = Ptrs();
    for (unsigned i = 0; i < numBuckets; ++i)
        ptrs[i] = 0;
}

}
