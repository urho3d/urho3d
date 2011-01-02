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

#include "Exception.h"
#include "MathDefs.h"
#include "SharedArrayPtr.h"
#include "StringUtils.h"

#include <stb_image.h>
#include <stb_image_write.h>
#include <iostream>
#include <string>

#include "DebugNew.h"

int main(int argc, char** argv);
void run(const std::vector<std::string>& arguments);
void errorExit(const std::string& error);

int main(int argc, char** argv)
{
    std::vector<std::string> arguments;
    
    for (int i = 1; i < argc; ++i)
        arguments.push_back(std::string(argv[i]));
    
    try
    {
        run(arguments);
    }
    catch (Exception& e)
    {
        std::cout << e.whatStr() << std::endl;
        return 1;
    }
    
    return 0;
}

void run(const std::vector<std::string>& arguments)
{
    if (arguments.size() < 3)
        errorExit("Usage: RampGenerator <output file> <width> <power> [dimensions]");
    
    int width = toInt(arguments[1]);
    float power = toFloat(arguments[2]);
    
    int dimensions = 1;
    if (arguments.size() > 3)
        dimensions = toInt(arguments[3]);
        
    if (width < 2)
        errorExit("Width must be at least 2");
    
    if ((dimensions < 1) || (dimensions > 2))
        errorExit("Dimensions must be 1 or 2");
    
    std::string tempDestName = split(arguments[0], '.')[0] + ".tga";
    
    if (dimensions == 1)
    {
        SharedArrayPtr<unsigned char> data(new unsigned char[width]);
        
        for (int i = 0; i < width; ++i)
        {
            float x = ((float)i) / ((float)(width - 1));
            
            data[i] = (unsigned char)((1.0f - pow(x, power)) * 255.0f);
        }
        
        // Ensure start is full bright & end is completely black
        data[0] = 255;
        data[width - 1] = 0;
        
        stbi_write_tga(tempDestName.c_str(), width, 1, 1, data.getPtr());
    }
    
    if (dimensions == 2)
    {
        SharedArrayPtr<unsigned char> data(new unsigned char[width * width]);
        
        for (int y = 0; y < width; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                unsigned i = y * width + x;
                
                float halfWidth = width * 0.5f;
                float xf = (x - halfWidth + 0.5f) / (halfWidth - 0.5f);
                float yf = (y - halfWidth + 0.5f) / (halfWidth - 0.5f);
                float dist = sqrtf(xf * xf + yf * yf);
                if (dist > 1.0f)
                    dist = 1.0f;
                
                data[i] = (unsigned char)((1.0f - pow(dist, power)) * 255.0f);
            }
        }
        
        // Ensure the border is completely black
        for (int x = 0; x < width; ++x)
        {
            data[x] = 0;
            data[(width - 1) * width + x] = 0;
            data[x * width] = 0;
            data[x * width + (width - 1)] = 0;
        }
        
        stbi_write_tga(tempDestName.c_str(), width, width, 1, data.getPtr());
    }
    
    std::string command = "texconv -f R8G8B8 -ft PNG -if NONE " + tempDestName;
    int ret = system(command.c_str());
    
    if (ret)
        errorExit("Failed to convert to PNG");
    
    remove(tempDestName.c_str());
}

void errorExit(const std::string& error)
{
    throw Exception(error);
}
