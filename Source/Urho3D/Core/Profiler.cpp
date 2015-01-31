//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Core/CoreEvents.h"
#include "../Core/Profiler.h"

#include <cstdio>
#include <cstring>

#include "../DebugNew.h"

namespace Urho3D
{

static const int LINE_MAX_LENGTH = 256;
static const int NAME_MAX_LENGTH = 30;

Profiler::Profiler(Context* context) :
    Object(context),
    current_(0),
    root_(0),
    intervalFrames_(0),
    totalFrames_(0)
{
    root_ = new ProfilerBlock(0, "Root");
    current_ = root_;
}

Profiler::~Profiler()
{
    delete root_;
    root_ = 0;
}

void Profiler::BeginFrame()
{
    // End the previous frame if any
    EndFrame();
    
    BeginBlock("RunFrame");
}

void Profiler::EndFrame()
{
    if (current_ != root_)
    {
        EndBlock();
        ++intervalFrames_;
        ++totalFrames_;
        if (!totalFrames_)
            ++totalFrames_;
        root_->EndFrame();
        current_ = root_;
    }
}

void Profiler::BeginInterval()
{
    root_->BeginInterval();
    intervalFrames_ = 0;
}

String Profiler::GetData(bool showUnused, bool showTotal, unsigned maxDepth) const
{
    String output;
    
    if (!showTotal)
        output += String("Block                            Cnt     Avg      Max     Frame     Total\n\n");
    else
    {
        output += String("Block                                       Last frame                       Whole execution time\n\n");
        output += String("                                 Cnt     Avg      Max      Total      Cnt      Avg       Max        Total\n\n");
    }
    
    if (!maxDepth)
        maxDepth = 1;
    
    GetData(root_, output, 0, maxDepth, showUnused, showTotal);
    
    return output;
}

void Profiler::GetData(ProfilerBlock* block, String& output, unsigned depth, unsigned maxDepth, bool showUnused, bool showTotal) const
{
    char line[LINE_MAX_LENGTH];
    char indentedName[LINE_MAX_LENGTH];
    
    unsigned intervalFrames = Max(intervalFrames_, 1);
    
    if (depth >= maxDepth)
        return;
    
    // Do not print the root block as it does not collect any actual data
    if (block != root_)
    {
        if (showUnused || block->intervalCount_ || (showTotal && block->totalCount_))
        {
            memset(indentedName, ' ', NAME_MAX_LENGTH);
            indentedName[depth] = 0;
            strcat(indentedName, block->name_);
            indentedName[strlen(indentedName)] = ' ';
            indentedName[NAME_MAX_LENGTH] = 0;
            
            if (!showTotal)
            {
                float avg = (block->intervalCount_ ? block->intervalTime_ / block->intervalCount_ : 0.0f) / 1000.0f;
                float max = block->intervalMaxTime_ / 1000.0f;
                float frame = block->intervalTime_ / intervalFrames / 1000.0f;
                float all = block->intervalTime_ / 1000.0f;
        
                sprintf(line, "%s %5u %8.3f %8.3f %8.3f %9.3f\n", indentedName, Min(block->intervalCount_, 99999),
                    avg, max, frame, all);
            }
            else
            {
                float avg = (block->frameCount_ ? block->frameTime_ / block->frameCount_ : 0.0f) / 1000.0f;
                float max = block->frameMaxTime_ / 1000.0f;
                float all = block->frameTime_ / 1000.0f;
                
                float totalAvg = (block->totalCount_ ? block->totalTime_ / block->totalCount_ : 0.0f) / 1000.0f;
                float totalMax = block->totalMaxTime_ / 1000.0f;
                float totalAll = block->totalTime_ / 1000.0f;
                
                sprintf(line, "%s %5u %8.3f %8.3f %9.3f  %7u %9.3f %9.3f %11.3f\n", indentedName, Min(block->frameCount_, 99999),
                    avg, max, all, Min(block->totalCount_, 99999), totalAvg, totalMax, totalAll);
            }
            
            output += String(line);
        }
        
        ++depth;
    }
    
    for (PODVector<ProfilerBlock*>::ConstIterator i = block->children_.Begin(); i != block->children_.End(); ++i)
        GetData(*i, output, depth, maxDepth, showUnused, showTotal);
}

}
