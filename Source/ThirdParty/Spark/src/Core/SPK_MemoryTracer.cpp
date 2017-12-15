//
// SPARK particle engine
//
// Copyright (C) 2008-2011 - Julien Fryer - julienfryer@gmail.com
// Copyright (C) 2017 - Frederic Martin - fredakilla@gmail.com
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//

#include "Core/SPK_DEF.h"


#ifdef SPK_OVERRIDE_NEW
#if _win32
    #define ALIGN16_MALLOC(__data, __size)      __data = _aligned_malloc(__size, 16)
    #define ALIGN16_FREE(__data)                _aligned_free(__data)
#else
    #define ALIGN16_MALLOC(__data, __size)      posix_memalign((void**)&__data,16,__size)
    #define ALIGN16_FREE(__data)                free(__data)
#endif

void * operator new(size_t size)
{
    void * p;
    ALIGN16_MALLOC(p, size);
    if (p == NULL) throw std::bad_alloc();
    return p;
}

void operator delete(void *p)
{
    ALIGN16_FREE(p);
}

void * operator new[](size_t size)
{
    void * p;
    ALIGN16_MALLOC(p, size);
    if (p == NULL) throw std::bad_alloc();
    return p;
}

void operator delete[](void *p)
{
    ALIGN16_FREE(p);
}
#endif

#ifdef SPK_TRACE_MEMORY

#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

namespace SPK
{
    SPKMemoryTracer& SPKMemoryTracer::get()
    {
        static SPKMemoryTracer instance;
        return instance;
    }

    void* SPKMemoryTracer::registerAllocation(void* position,size_t size,const std::string& type,const std::string& file,size_t line)
    {
        if (position == NULL)
            return NULL;

        BlockInfo info(position);
        info.size = size;
        info.type = type;
        info.fileName = file;
        info.lineNb = line;
        info.time = static_cast<float>(clock()) / CLOCKS_PER_SEC;
        info.index = nextIndex++;

        blocks.insert(info);

        totalMemorySize += size;
        if (totalMemorySize > maxMemorySize)
            maxMemorySize = totalMemorySize;

        return position;
    }

    void SPKMemoryTracer::unregisterAllocation(void* position)
    {
        std::set<BlockInfo>::iterator it = blocks.find(BlockInfo(position));
        if (it != blocks.end())
        {
            totalMemorySize -= it->size;
            blocks.erase(it);
        }
    }

    std::string SPKMemoryTracer::formatSize(unsigned int s)
    {
        float sf = (float)s;
        unsigned int q = 0;
        const char* qualifiers[] =
        {
            "B",
            "KB",
            "MB",
            "GB",
            "TB"
        };
        while(sf >= 1024 && q < sizeof(qualifiers) / sizeof(const char*))
        {
            sf /= 1024;
            q++;
        }
        std::string result;
        std::ostringstream str(result);
        str.precision(2);
        str << std::fixed << sf << " " << qualifiers[q];
        return str.str();
    }

    void SPKMemoryTracer::dumpMemory()
    {
        std::ofstream file("SPARK_Memory_Dump.txt",std::ios::out | std::ios::app);

        if (file)
        {
            std::vector<BlockInfo> sortedBlocks(blocks.begin(),blocks.end());
            std::sort(sortedBlocks.begin(),sortedBlocks.end(),compareAllocTime);

            time_t currentTime = time(NULL);
            tm* timeinfo = localtime(&currentTime);
            file << "-----------------------------------------------------------------------------------------------\n";
            file << "SPARK MEMORY DUMP - " << asctime(timeinfo) << "\n\n";
            file.precision(3);
            file << "Dynamic memory used: " << totalMemorySize << " bytes allocated (" << formatSize(totalMemorySize) << ") in " << blocks.size() << " blocks\n";
            file << "Maximum dynamic memory allocated: " << maxMemorySize << " bytes ("<< formatSize(maxMemorySize) << ")\n";
            file << "Total number of allocated blocks: " << nextIndex << "\n\n";

            std::vector<BlockInfo>::const_iterator it = sortedBlocks.begin();
            std::vector<BlockInfo>::const_iterator end = sortedBlocks.end();
            for (; it != end; ++it)
            {
                file << it->position << " - ";

                file.width(10);
                file << std::right << it->size << " bytes";

                file.width(32);
                std::ostringstream typeStr;
                typeStr << " of " << it->type;
                file << std::right << typeStr.str();

                file.width(18);
                std::ostringstream timeStr;
                timeStr << " at " << it->time << " sec";
                file << std::right << timeStr.str();
                file << "\t(" << it->fileName << " - line " << it->lineNb << ")\n";
            }
            file << "-----------------------------------------------------------------------------------------------\n\n";
            file.close();
        }
    }
}

#endif
