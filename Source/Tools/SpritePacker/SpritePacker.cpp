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

#include <Urho3D/Core/Context.h>
#include <Urho3D/Core/ProcessUtils.h>
#include <Urho3D/Core/StringUtils.h>
#include <Urho3D/IO/File.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Resource/Image.h>
#include <Urho3D/Resource/XMLElement.h>
#include <Urho3D/Resource/XMLFile.h>

#ifdef WIN32
#include <windows.h>
#endif

#define STBRP_LARGE_RECTS
#define STB_RECT_PACK_IMPLEMENTATION
#include <STB/stb_rect_pack.h>

#include <Urho3D/DebugNew.h>

using namespace Urho3D;

// number of nodes allocated to each packer info.  since this packer is not suited for real time purposes we can over allocate.
const int PACKER_NUM_NODES = 4096;
const int MAX_TEXTURE_SIZE = 2048;

int main(int argc, char** argv);
void Run(Vector<String>& arguments);

class PackerInfo : public RefCounted
{
public:
    String path;
    String name;
    int x{};
    int y{};
    int offsetX{};
    int offsetY{};
    int width{};
    int height{};
    int frameWidth{};
    int frameHeight{};

    PackerInfo(const String& path_, const String& name_) :
        path(path_),
        name(name_)
    {
    }

    ~PackerInfo() override = default;
};

void Help()
{
    ErrorExit("Usage: SpritePacker -options <input file> <input file> <output png file>\n"
        "\n"
        "Options:\n"
        "-h Shows this help message.\n"
        "-px Adds x pixels of padding per image to width.\n"
        "-py Adds y pixels of padding per image to height.\n"
        "-ox Adds x pixels to the horizontal position per image.\n"
        "-oy Adds y pixels to the horizontal position per image.\n"
        "-frameHeight Sets a fixed height for image and centers within frame.\n"
        "-frameWidth Sets a fixed width for image and centers within frame.\n"
        "-trim Trims excess transparent space from individual images offsets by frame size.\n"
        "-xml \'path\' Generates an SpriteSheet xml file at path.\n"
        "-debug Draws allocation boxes on sprite.\n");
}

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

void Run(Vector<String>& arguments)
{
    if (arguments.Size() < 2)
        Help();

    SharedPtr<Context> context(new Context());
    context->RegisterSubsystem(new FileSystem(context));
    context->RegisterSubsystem(new Log(context));
    auto* fileSystem = context->GetSubsystem<FileSystem>();

    Vector<String> inputFiles;
    String outputFile;
    String spriteSheetFileName;
    bool debug = false;
    unsigned padX = 0;
    unsigned padY = 0;
    unsigned offsetX = 0;
    unsigned offsetY = 0;
    unsigned frameWidth = 0;
    unsigned frameHeight = 0;
    bool help = false;
    bool trim = false;

    while (arguments.Size() > 0)
    {
        String arg = arguments[0];
        arguments.Erase(0);

        if (arg.Empty())
            continue;

        if (arg.StartsWith("-"))
        {
            if (arg == "-px")      { padX = ToUInt(arguments[0]); arguments.Erase(0); }
            else if (arg == "-py") { padY = ToUInt(arguments[0]); arguments.Erase(0); }
            else if (arg == "-ox") { offsetX = ToUInt(arguments[0]); arguments.Erase(0); }
            else if (arg == "-oy") { offsetY = ToUInt(arguments[0]); arguments.Erase(0); }
            else if (arg == "-frameWidth") { frameWidth = ToUInt(arguments[0]); arguments.Erase(0); }
            else if (arg == "-frameHeight") { frameHeight = ToUInt(arguments[0]); arguments.Erase(0); }
            else if (arg == "-trim") { trim = true; }
            else if (arg == "-xml")  { spriteSheetFileName = arguments[0]; arguments.Erase(0); }
            else if (arg == "-h")  { help = true; break; }
            else if (arg == "-debug")  { debug = true; }
        }
        else
            inputFiles.Push(arg);
    }

    if (help)
        Help();

    if (inputFiles.Size() < 2)
        ErrorExit("An input and output file must be specified.");

    if (frameWidth ^ frameHeight)
        ErrorExit("Both frameHeight and frameWidth must be omitted or specified.");

    // take last input file as output
    if (inputFiles.Size() > 1)
    {
        outputFile = inputFiles[inputFiles.Size() - 1];
        URHO3D_LOGINFO("Output file set to " + outputFile + ".");
        inputFiles.Erase(inputFiles.Size() - 1);
    }

    // set spritesheet name to outputfile.xml if not specified
    if (spriteSheetFileName.Empty())
        spriteSheetFileName = ReplaceExtension(outputFile, ".xml");

    if (GetParentPath(spriteSheetFileName) != GetParentPath(outputFile))
        ErrorExit("Both output xml and png must be in the same folder");

    // check all input files exist
    for (unsigned i = 0; i < inputFiles.Size(); ++i)
    {
        URHO3D_LOGINFO("Checking " + inputFiles[i] + " to see if file exists.");
        if (!fileSystem->FileExists(inputFiles[i]))
            ErrorExit("File " + inputFiles[i] + " does not exist.");
    }

    // Set the max offset equal to padding to prevent images from going out of bounds
    offsetX = Min((int)offsetX, (int)padX);
    offsetY = Min((int)offsetY, (int)padY);

    Vector<SharedPtr<PackerInfo > > packerInfos;

    for (unsigned i = 0; i < inputFiles.Size(); ++i)
    {
        String path = inputFiles[i];
        String name = ReplaceExtension(GetFileName(path), "");
        File file(context, path);
        Image image(context);

        if (!image.Load(file))
            ErrorExit("Could not load image " + path + ".");

        if (image.IsCompressed())
            ErrorExit(path + " is compressed. Compressed images are not allowed.");

        SharedPtr<PackerInfo> packerInfo(new PackerInfo(path, name));
        int imageWidth = image.GetWidth();
        int imageHeight = image.GetHeight();
        int trimOffsetX = 0;
        int trimOffsetY = 0;
        int adjustedWidth = imageWidth;
        int adjustedHeight = imageHeight;

        if (trim)
        {
            int minX = imageWidth;
            int minY = imageHeight;
            int maxX = 0;
            int maxY = 0;

            for (int y = 0; y < imageHeight; ++y)
            {
                for (int x = 0; x < imageWidth; ++x)
                {
                    bool found = (image.GetPixelInt(x, y) & 0x000000ffu) != 0;
                    if (found) {
                        minX = Min(minX, x);
                        minY = Min(minY, y);
                        maxX = Max(maxX, x);
                        maxY = Max(maxY, y);
                    }
                }
            }

            trimOffsetX = minX;
            trimOffsetY = minY;
            adjustedWidth = maxX - minX + 1;
            adjustedHeight = maxY - minY + 1;
        }

        if (trim)
        {
            packerInfo->frameWidth = imageWidth;
            packerInfo->frameHeight = imageHeight;
        }
        else if (frameWidth || frameHeight)
        {
            packerInfo->frameWidth = frameWidth;
            packerInfo->frameHeight = frameHeight;
        }
        packerInfo->width = adjustedWidth;
        packerInfo->height = adjustedHeight;
        packerInfo->offsetX -= trimOffsetX;
        packerInfo->offsetY -= trimOffsetY;
        packerInfos.Push(packerInfo);
    }

    int packedWidth = MAX_TEXTURE_SIZE;
    int packedHeight = MAX_TEXTURE_SIZE;
    {
        // fill up an list of tries in increasing size and take the first win
        Vector<IntVector2> tries;
        for(unsigned x=2; x<11; ++x)
        {
            for(unsigned y=2; y<11; ++y)
                tries.Push(IntVector2((1u<<x), (1u<<y)));
        }

        // load rectangles
        auto* packerRects = new stbrp_rect[packerInfos.Size()];
        for (unsigned i = 0; i < packerInfos.Size(); ++i)
        {
            PackerInfo* packerInfo = packerInfos[i];
            stbrp_rect* packerRect = &packerRects[i];
            packerRect->id = i;
            packerRect->h = packerInfo->height + padY;
            packerRect->w = packerInfo->width + padX;
        }

        bool success = false;
        while (tries.Size() > 0)
        {
            IntVector2 size = tries[0];
            tries.Erase(0);
            bool fit = true;
            int textureHeight = size.y_;
            int textureWidth = size.x_;
            if (success && textureHeight * textureWidth > packedWidth * packedHeight)
                continue;

            stbrp_context packerContext;
            stbrp_node packerMemory[PACKER_NUM_NODES];
            stbrp_init_target(&packerContext, textureWidth, textureHeight, packerMemory, PACKER_NUM_NODES);
            if (!stbrp_pack_rects(&packerContext, packerRects, packerInfos.Size()))
            {
                // check to see if everything fit
                fit = false;
            }

            if (fit)
            {
                success = true;
                // distribute values to packer info
                for (unsigned i = 0; i < packerInfos.Size(); ++i)
                {
                    stbrp_rect* packerRect = &packerRects[i];
                    PackerInfo* packerInfo = packerInfos[packerRect->id];
                    packerInfo->x = packerRect->x;
                    packerInfo->y = packerRect->y;
                }
                packedWidth = size.x_;
                packedHeight = size.y_;
            }
        }
        delete[] packerRects;
        if (!success)
            ErrorExit("Could not allocate for all images.  The max sprite sheet texture size is " + String(MAX_TEXTURE_SIZE) + "x" + String(MAX_TEXTURE_SIZE) + ".");
    }

    // create image for spritesheet
    Image spriteSheetImage(context);
    spriteSheetImage.SetSize(packedWidth, packedHeight, 4);

    // zero out image
    spriteSheetImage.SetData(nullptr);

    XMLFile xml(context);
    XMLElement root = xml.CreateRoot("TextureAtlas");
    root.SetAttribute("imagePath", GetFileNameAndExtension(outputFile));

    for (unsigned i = 0; i < packerInfos.Size(); ++i)
    {
        SharedPtr<PackerInfo> packerInfo = packerInfos[i];
        XMLElement subTexture = root.CreateChild("SubTexture");
        subTexture.SetString("name", packerInfo->name);
        subTexture.SetInt("x", packerInfo->x + offsetX);
        subTexture.SetInt("y", packerInfo->y + offsetY);
        subTexture.SetInt("width", packerInfo->width);
        subTexture.SetInt("height", packerInfo->height);

        if (packerInfo->frameWidth || packerInfo->frameHeight)
        {
            subTexture.SetInt("frameWidth", packerInfo->frameWidth);
            subTexture.SetInt("frameHeight", packerInfo->frameHeight);
            subTexture.SetInt("offsetX", packerInfo->offsetX);
            subTexture.SetInt("offsetY", packerInfo->offsetY);
        }

        URHO3D_LOGINFO("Transferring " + packerInfo->path + " to sprite sheet.");

        File file(context, packerInfo->path);
        Image image(context);
        if (!image.Load(file))
            ErrorExit("Could not load image " + packerInfo->path + ".");

        for (int y = 0; y < packerInfo->height; ++y)
        {
            for (int x = 0; x < packerInfo->width; ++x)
            {
                unsigned color = image.GetPixelInt(x - packerInfo->offsetX, y - packerInfo->offsetY);
                spriteSheetImage.SetPixelInt(
                    packerInfo->x + offsetX + x,
                    packerInfo->y + offsetY + y, color);
            }
        }
    }

    if (debug)
    {
        unsigned OUTER_BOUNDS_DEBUG_COLOR = Color::BLUE.ToUInt();
        unsigned INNER_BOUNDS_DEBUG_COLOR = Color::GREEN.ToUInt();

        URHO3D_LOGINFO("Drawing debug information.");
        for (unsigned i = 0; i < packerInfos.Size(); ++i)
        {
            SharedPtr<PackerInfo> packerInfo = packerInfos[i];

            // Draw outer bounds
            for (int x = 0; x < packerInfo->frameWidth; ++x)
            {
                spriteSheetImage.SetPixelInt(packerInfo->x + x, packerInfo->y, OUTER_BOUNDS_DEBUG_COLOR);
                spriteSheetImage.SetPixelInt(packerInfo->x + x, packerInfo->y + packerInfo->frameHeight, OUTER_BOUNDS_DEBUG_COLOR);
            }
            for (int y = 0; y < packerInfo->frameHeight; ++y)
            {
                spriteSheetImage.SetPixelInt(packerInfo->x, packerInfo->y + y, OUTER_BOUNDS_DEBUG_COLOR);
                spriteSheetImage.SetPixelInt(packerInfo->x + packerInfo->frameWidth, packerInfo->y + y, OUTER_BOUNDS_DEBUG_COLOR);
            }

            // Draw inner bounds
            for (int x = 0; x < packerInfo->width; ++x)
            {
                spriteSheetImage.SetPixelInt(packerInfo->x + offsetX + x, packerInfo->y + offsetY, INNER_BOUNDS_DEBUG_COLOR);
                spriteSheetImage.SetPixelInt(packerInfo->x + offsetX + x, packerInfo->y + offsetY + packerInfo->height, INNER_BOUNDS_DEBUG_COLOR);
            }
            for (int y = 0; y < packerInfo->height; ++y)
            {
                spriteSheetImage.SetPixelInt(packerInfo->x + offsetX, packerInfo->y + offsetY + y, INNER_BOUNDS_DEBUG_COLOR);
                spriteSheetImage.SetPixelInt(packerInfo->x + offsetX + packerInfo->width, packerInfo->y + offsetY + y, INNER_BOUNDS_DEBUG_COLOR);
            }
        }
    }

    URHO3D_LOGINFO("Saving output image.");
    spriteSheetImage.SavePNG(outputFile);

    URHO3D_LOGINFO("Saving SpriteSheet xml file.");
    File spriteSheetFile(context);
    spriteSheetFile.Open(spriteSheetFileName, FILE_WRITE);
    xml.Save(spriteSheetFile);
}
