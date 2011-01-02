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
#include "File.h"
#include "Image.h"
#include "StringUtils.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <stb_image.h>
#include <stb_image_write.h>

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
    if (arguments.size() < 1)
        errorExit("Usage: NormalMapTool <input image file>");
    
    File source(arguments[0]);
    Image image;
    image.load(source);
    
    unsigned comp = image.getComponents();
    if ((comp < 3) && (comp > 4))
        errorExit("Image must contain 3 or 4 components");
    
    SharedArrayPtr<unsigned char> buffer(new unsigned char[image.getWidth() * image.getHeight() * 4]);
    unsigned char* srcData = image.getData();
    unsigned char* destData = buffer.getPtr();
    
    for (int y = 0; y < image.getHeight(); ++y)
    {
        for (int x = 0; x < image.getWidth(); ++x)
        {
            unsigned char r = *srcData++;
            unsigned char g = *srcData++;
            unsigned char b = *srcData++;
            if (comp == 4)
                srcData++;
            
            // Store X as alpha, and Y as color. Z can be reconstructed
            *destData++ = g;
            *destData++ = g;
            *destData++ = g;
            *destData++ = r;
        }
    }
    
    std::string tempDestName = split(arguments[0], '.')[0] + ".tga";
    stbi_write_tga(tempDestName.c_str(), image.getWidth(), image.getHeight(), 4, buffer.getPtr());
    
    std::string command = "texconv -f DXT5 -ft DDS -if NONE " + tempDestName;
    int ret = system(command.c_str());
    
    if (ret)
        errorExit("Failed to convert to DXT5");
    
    remove(tempDestName.c_str());
}
void errorExit(const std::string& error)
{
    throw Exception(error);
}
