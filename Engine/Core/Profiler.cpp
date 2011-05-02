//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#include "Precompiled.h"
#include "CoreEvents.h"
#include "Profiler.h"

#include <cstdio>
#include <cstring>
#include <ctype.h>

#include "DebugNew.h"

static const int LINE_MAX_LENGTH = 256;
static const int NAME_MAX_LENGTH = 30;

OBJECTTYPESTATIC(Profiler);

Profiler::Profiler(Context* context) :
    Object(context),
    root_(0),
    current_(0),
    accumulatedFrames_(0),
    totalFrames_(0)
{
    root_ = new ProfilerBlock(0, "Root");
    current_ = root_;
    
    SubscribeToEvent(E_BEGINFRAME, HANDLER(Profiler, HandleBeginFrame));
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
        ++accumulatedFrames_;
        ++totalFrames_;
        if (!totalFrames_)
            ++totalFrames_;
        root_->EndFrame();
        current_ = root_;
    }
}

void Profiler::ClearAccumulated()
{
    root_->ClearAccumulated();
    accumulatedFrames_ = 0;
}

std::string Profiler::GetData(bool showUnused, bool showAccumulated, bool showTotal) const
{
    std::string output;
    
    if (!showTotal)
        output += std::string("Block                          Count   Average   Total\n \n");
    else
        output += std::string("Block                             Frame average (msec)      Accumulated total (sec)\n \n");
    
    GetData(root_, output, 0, showUnused, showAccumulated, showTotal);
    
    return output;
}

void Profiler::GetData(ProfilerBlock* block, std::string& output, unsigned indent, bool showUnused, bool showAccumulated, bool showTotal) const
{
    char line[LINE_MAX_LENGTH];
    char indentedName[LINE_MAX_LENGTH];
    
    unsigned frames = Max(totalFrames_, 1);
    unsigned accumulatedFrames = Max(accumulatedFrames_, 1);
    
    // Do not print the root block as it does not collect any actual data
    if (block != root_)
    {
        // Output data in milliseconds
        float frameTime = block->GetFrameTime() / 1000.0f;
        float accumulatedTime = block->GetAccumulatedTime() / 1000.0f;
        float totalTime = block->GetTotalTime() / 1000.0f;
        unsigned frameCount = block->GetFrameCount();
        unsigned accumulatedCount = block->GetAccumulatedCount();
        unsigned totalCount = block->GetTotalCount();
        
        float avgFrameTime = 0.0f;
        float avgAccumulatedTime = 0.0f;
        float avgTotalTime = 0.0f;
        
        if (frameCount)
            avgFrameTime = frameTime / frameCount;
        if (accumulatedCount)
            avgAccumulatedTime = accumulatedTime / accumulatedCount;
        if (totalCount)
            avgTotalTime = totalTime / totalCount;
        
        if ((showUnused) || (frameCount) || ((showAccumulated) && (accumulatedCount)))
        {
            memset(indentedName, ' ', NAME_MAX_LENGTH);
            indentedName[indent] = 0;
            strcat(indentedName, block->GetName());
            indentedName[strlen(indentedName)] = ' ';
            indentedName[NAME_MAX_LENGTH] = 0;
            
            if (!showTotal)
            {
                if (!showAccumulated)
                    sprintf(line, "%s %5u %8.3f %8.3f\n", indentedName, frameCount, avgFrameTime, frameTime);
                else
                    sprintf(line, "%s %5u %8.3f %8.3f\n", indentedName, 
                        (unsigned)((float)accumulatedCount / accumulatedFrames + 0.5f),
                        avgAccumulatedTime, accumulatedTime / accumulatedFrames);
            }
            else
            {
                unsigned avgFrameCount = (unsigned)((float)totalCount / frames + 0.5f);
                float avgFrameTime = avgTotalTime;
                float avgFrameTotalTime = totalTime / frames;
                if (!avgFrameCount)
                {
                    avgFrameTime = 0.0f;
                    avgFrameTotalTime = 0.0f;
                }
                
                sprintf(line, "%s %5u %8.3f %8.3f %10u %8.3f %8.3f\n",
                    indentedName, avgFrameCount, avgFrameTime, avgFrameTotalTime,
                    totalCount, avgTotalTime / 1000.0f, totalTime / 1000.0);
            }
            output += std::string(line);
            
            indent++;
        }
    }
    
    const std::vector<ProfilerBlock*>& children = block->GetChildren();
    for (std::vector<ProfilerBlock*>::const_iterator i = children.begin(); i != children.end(); ++i)
        GetData(*i, output, indent, showUnused, showAccumulated, showTotal);
}

void Profiler::HandleBeginFrame(StringHash eventType, VariantMap& eventData)
{
    BeginFrame();
}
