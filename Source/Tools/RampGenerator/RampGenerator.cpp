//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include <Urho3D/Container/ArrayPtr.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/IO/File.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/Core/ProcessUtils.h>
#include <Urho3D/Core/StringUtils.h>

#ifdef WIN32
#include <windows.h>
#endif

#include <STB/stb_image_write.h>

#include <Urho3D/DebugNew.h>

using namespace Urho3D;

// Kernel used for blurring IES lights
static const float sigma3Kernel9x9[9 * 9] = {
    0.00401f, 0.005895f, 0.007763f, 0.009157f, 0.009675f, 0.009157f, 0.007763f, 0.005895f, 0.00401f,
    0.005895f, 0.008667f, 0.011412f, 0.013461f, 0.014223f, 0.013461f, 0.011412f, 0.008667f, 0.005895f,
    0.007763f, 0.011412f, 0.015028f, 0.017726f, 0.018729f, 0.017726f, 0.015028f, 0.011412f, 0.007763f,
    0.009157f, 0.013461f, 0.017726f, 0.020909f, 0.022092f, 0.020909f, 0.017726f, 0.013461f, 0.009157f,
    0.009675f, 0.014223f, 0.018729f, 0.022092f, 0.023342f, 0.022092f, 0.018729f, 0.014223f, 0.009675f,
    0.009157f, 0.013461f, 0.017726f, 0.020909f, 0.022092f, 0.020909f, 0.017726f, 0.013461f, 0.009157f,
    0.007763f, 0.011412f, 0.015028f, 0.017726f, 0.018729f, 0.017726f, 0.015028f, 0.011412f, 0.007763f,
    0.005895f, 0.008667f, 0.011412f, 0.013461f, 0.014223f, 0.013461f, 0.011412f, 0.008667f, 0.005895f,
    0.00401f, 0.005895f, 0.007763f, 0.009157f, 0.009675f, 0.009157f, 0.007763f, 0.005895f, 0.00401f
};

int main(int argc, char** argv);
void Run(const Vector<String>& arguments);

bool ReadIES(File* data, PODVector<float>& vertical, PODVector<float>& horizontal, PODVector<float>& luminance);
void WriteIES(unsigned char* data, unsigned width, unsigned height, PODVector<float>& horizontal, PODVector<float>& vertical, PODVector<float>& luminance);
void Blur(unsigned char* data, unsigned width, unsigned height, const float* kernel, unsigned kernelWidth);

int main(int argc, char** argv)
{
    Vector<String> arguments;

    #ifdef WIN32
    arguments = ParseArguments(GetCommandLineW());
    #else
    arguments = ParseArguments(argc, argv);
    #endif

    Run(arguments);
    return 0;
}

void Run(const Vector<String>& arguments)
{
    if (arguments.Size() < 3)
        ErrorExit("Usage: RampGenerator <output png file> <width> <power> [dimensions]\n"
                  "IES Usage: RampGenerator <input file> <output png file> <width> [dimensions]");

    if (GetExtension(arguments[0]) == ".ies") // Generate an IES light derived ramp
    {
        String inputFile = arguments[0];
        String ouputFile = arguments[1];
        int width = ToInt(arguments[2]);
        int dim = 1;
        if (arguments.Size() > 3)
            dim = ToInt(arguments[3]);
        int blurLevel = 0;
        if (arguments.Size() > 4)
            blurLevel = ToInt(arguments[4]);

        const int height = dim == 2 ? width : 1;

        Context context;
        File file(&context);
        file.Open(inputFile);

        PODVector<float> horizontal;
        PODVector<float> vertical;
        PODVector<float> luminance;
        ReadIES(&file, vertical, horizontal, luminance);

        SharedArrayPtr<unsigned char> data(new unsigned char[width * height]);
        WriteIES(data, width, height, vertical, horizontal, luminance);

        // Apply a blur, simpler than interpolating through the 2 dimensions of coarse samples
        Blur(data, width, height, sigma3Kernel9x9, 9);

        stbi_write_png(arguments[1].CString(), width, height, 1, data.Get(), 0);
    }
    else // Generate a regular power based ramp
    {
        int width = ToInt(arguments[1]);
        float power = ToFloat(arguments[2]);

        int dimensions = 1;
        if (arguments.Size() > 3)
            dimensions = ToInt(arguments[3]);

        if (width < 2)
            ErrorExit("Width must be at least 2");

        if (dimensions < 1 || dimensions > 2)
            ErrorExit("Dimensions must be 1 or 2");

        if (dimensions == 1)
        {
            SharedArrayPtr<unsigned char> data(new unsigned char[width]);

            for (int i = 0; i < width; ++i)
            {
                float x = ((float)i) / ((float)(width - 1));

                data[i] = (unsigned char)((1.0f - Pow(x, power)) * 255.0f);
            }

            // Ensure start is full bright & end is completely black
            data[0] = 255;
            data[width - 1] = 0;

            stbi_write_png(arguments[0].CString(), width, 1, 1, data.Get(), 0);
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

                    data[i] = (unsigned char)((1.0f - Pow(dist, power)) * 255.0f);
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

            stbi_write_png(arguments[0].CString(), width, width, 1, data.Get(), 0);
        }
    }
}

unsigned GetSample(float position, PODVector<float>& inputs)
{
    unsigned pos = 0;
    // Early outs
    if (position < inputs[0])
        return 0;
    else if (position > inputs.Back())
        return inputs.Size() - 1;

    // Find best candidate
    float closestVal = M_INFINITY;
    unsigned samplePos = -1;
    for (unsigned i = 0; i < inputs.Size(); ++i)
    {
        float val = inputs[i];
        float diff = Abs(val - position);
        if (diff < closestVal)
        {
            closestVal = diff;
            samplePos = i;
        }
    }

    return samplePos;
}

bool IsWhitespace(const String& string)
{
    bool anyNot = false;
    for (unsigned i = 0; i < string.Length(); ++i)
    {
        if (!::isspace(string[i]))
            anyNot = true;
    }
    return !anyNot;
}

float PopFirstFloat(Vector<String>& words)
{
    if (words.Size() > 0)
    {
        float ret = ToFloat(words[0]);
        words.Erase(0);
        return ret;
    }
    return -1.0f; // is < 0 ever valid?
}

int PopFirstInt(Vector<String>& words)
{
    if (words.Size() > 0)
    {
        int ret = ToInt(words[0]);
        words.Erase(0);
        return ret;
    }
    return -1; // < 0 ever valid?
}

bool ReadIES(File* data, PODVector<float>& vertical, PODVector<float>& horizontal, PODVector<float>& luminance)
{
    String line = data->ReadLine();
    if (!line.Contains("IESNA:LM-63-1995") && !line.Contains("IESNA:LM-63-2002"))
        ErrorExit("Unsupported format: " + line);

    // Skip over the misc data
    while (!data->IsEof())
    {
        line = data->ReadLine();
        if (line.Contains("TILT=NONE"))
            break;
        else if (line.Contains("TILT=")) // tilt is a whole different ballgame
            ErrorExit("Unsupported tilt: " + line);
        else if (line.Contains("[")) // eat this line, it's metadata
            continue;
    }

    // Collect everything into a a list to process, we're now reading actual values
    Vector<String> lines;
    while (!data->IsEof())
        lines.Push(data->ReadLine());
    Vector<String> words;
    for (unsigned i = 0; i < lines.Size(); ++i)
        words.Push(lines[i].Split(' '));

    // Prune any 'junk' collected
    for (unsigned i = 0; i < words.Size(); ++i)
    {
        if (words[i].Empty() || IsWhitespace(words[i]))
        {
            words.Erase(i);
            --i;
        }
    }

    const int sampleCount = PopFirstInt(words);
    const float lumens = PopFirstFloat(words);
    const float multiplier = PopFirstFloat(words); // Scales the candelas, used below
    const int verticalCount = PopFirstInt(words); //longitude
    const int horizontalCount = PopFirstInt(words); //latitude
    const int photometricType = PopFirstInt(words);
    const int measureType = PopFirstInt(words); // feet or meters
    const float width = PopFirstFloat(words);
    const float length = PopFirstFloat(words);
    const float height = PopFirstFloat(words);
    const float ballast = PopFirstFloat(words);
    PopFirstFloat(words); // Junk, called 'reserved' spot in spec
    PopFirstFloat(words); // Watts, unused

    for (int i = 0; i < verticalCount; ++i)
    {
        float value = PopFirstFloat(words);
        vertical.Push(value);
    }

    for (int i = 0; i < horizontalCount; ++i)
    {
        float value = PopFirstFloat(words);
        horizontal.Push(value);
    }

    for (int x = 0; x < horizontalCount; ++x)
    {
        for (int y = 0; y < verticalCount; ++y)
            luminance.Push(PopFirstFloat(words) * multiplier);
    }

    return true;
}

void WriteIES(unsigned char* data, unsigned width, unsigned height, PODVector<float>& horizontal, PODVector<float>& vertical, PODVector<float>& luminance)
{
    // Find maximum luminance value
    float maximum = -1;
    for (unsigned i = 0; i < luminance.Size(); ++i)
        maximum = Max(maximum, luminance[i]);

    // Find maximum radial slice
    float maxVert = 0;
    for (unsigned i = 0; i < vertical.Size(); ++i)
        maxVert = Max(maxVert, vertical[i]);

    // Find maximum altitude value
    float maxHoriz = 0;
    for (unsigned i = 0; i < horizontal.Size(); ++i)
        maxHoriz = Max(maxHoriz, horizontal[i]);

    const float inverseLightValue = 1.0f / maximum;
    const float inverseWidth = 1.0f / width;
    const float inverseHeight = 1.0f / height;

    float dirY = -1.0f;
    const float stepX = 2.0f / width;
    const float stepY = 2.0f / height;
    Vector3 centerVec(0, 0, 0);
    centerVec.Normalize();

    // Fitting to 90 degrees for better image usage
    // otherwise the space used would fit the light's traits and potentially incude a lot of wasted black space
    const float angularFactor = 90.0f;
    const float fraction = angularFactor / ((float)width);
    ::memset(data, 0, (size_t)width * height);

    for (unsigned y = 0; y < height; ++y)
    {
        float dirX = -1.0f;
        for (unsigned x = 0; x < width; ++x)
        {
            Vector3 dirVec(dirX * width, dirY * height, 0);
            const float len = dirVec.Length();
            const float weight = height > 1 ? Abs(1.0f - Cos(dirVec.Length() * fraction)) : x * inverseWidth;

            unsigned vert = GetSample(weight * angularFactor, horizontal);
            if (vert == -1)
                continue;

            float value = 0.0f;
            if (weight > 0.0f)
            {
                if (vertical.Size() == 1) // easy case
                    value = luminance[vert];
                else
                {
                    if (height > 1)
                    {
                        Vector3 normalized = dirVec.Normalized();
                        float angle = Atan2(normalized.x_, normalized.y_) - maxHoriz;
                        while (angle < 0)
                            angle += 360.0f;
                        const float moddedAngle = fmodf(angle, maxVert);
                        unsigned horiz = GetSample(moddedAngle, vertical);
                        value = luminance[vert + horizontal.Size() * horiz];
                    }
                    else
                    {
                        // Accumulate for an average across the radial slices
                        for (unsigned i = 0; i < vertical.Size(); ++i)
                            value += luminance[vert + i * vertical.Size()];
                        value /= vertical.Size();
                    }
                }
            }
            *data = (unsigned char)(inverseLightValue * value * 255.0f);
            ++data;

            dirX += stepX;
        }

        dirY += stepY;
    }
}

void Blur(unsigned char* data, unsigned width, unsigned height, const float* kernel, unsigned kernelWidth)
{
    const int kernelDim = (kernelWidth / 2);
    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            float average = 0.0f;
            for (int filterX = 0; filterX < kernelWidth; ++filterX)
            {
                for (int filterY = 0; filterY < kernelWidth; ++filterY)
                {
                    const int xSample = (x - kernelWidth / 2 + filterX + width) % width;
                    const int ySample = (y - kernelWidth / 2 + filterY + height) % height;
                    const float value = data[ySample + xSample * height] / 255.0f;
                    average += value * kernel[filterY + filterX * kernelWidth];
                }
            }
            data[y + x * height] = average * 255.0f;
        }
    }
}
