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

#ifndef H_SPK_MEMORYTRACER
#define H_SPK_MEMORYTRACER

#ifdef SPK_OVERRIDE_NEW
#undef new
#undef delete

void * operator new(size_t);
void * operator new[](size_t size);
void operator delete(void*) noexcept;
void operator delete[](void*) noexcept;
#endif


#ifndef SPK_TRACE_MEMORY
#define SPK_NEW(name,...) new name(__VA_ARGS__)
#define SPK_NEW_ARRAY(name,nb) new name[nb]
#define SPK_DELETE(name) delete name
#define SPK_DELETE_ARRAY(name) delete[] name
#define SPK_DUMP_MEMORY {}
#else
#define SPK_NEW(name,...) (name*)SPK::SPKMemoryTracer::get().registerAllocation(new name(__VA_ARGS__),sizeof(name),#name,__FILE__,__LINE__)
#define SPK_NEW_ARRAY(name,nb) (name*)SPK::SPKMemoryTracer::get().registerAllocation(new name[nb],sizeof(name) * nb,std::string(#name).append("[]"),__FILE__,__LINE__)
#define SPK_DELETE(name) { SPK::SPKMemoryTracer::get().unregisterAllocation(name); delete name; }
#define SPK_DELETE_ARRAY(name) { SPK::SPKMemoryTracer::get().unregisterAllocation(name); delete[] name; }
#define SPK_DUMP_MEMORY { SPK::SPKMemoryTracer::get().dumpMemory(); }

#include <string>
#include <set>

namespace SPK
{
    // Note: don't forget to verify static objects that depends on the tracer.
    // For the moment, only SPKContext and IO::Manager depends on it
    class SPK_PREFIX SPKMemoryTracer
    {
    struct BlockInfo;

    friend bool operator==(const BlockInfo&,const BlockInfo&);
    friend bool operator<(const BlockInfo&,const BlockInfo&);
    friend bool compareAllocTime(const BlockInfo&,const BlockInfo&);

    public :

        static SPKMemoryTracer& get();

        void* registerAllocation(void* position, size_t size, const std::string& type, const std::string& file, size_t line);
        void unregisterAllocation(void* position);
        std::string formatSize(unsigned int s);
        void dumpMemory();

    private :

        struct BlockInfo
        {
            void* position;
            size_t size;
            std::string type;
            std::string fileName;
            size_t lineNb;
            float time;
            unsigned long index;

            BlockInfo(void* position) : position(position) {}
        };

        SPKMemoryTracer() :
            nextIndex(0),
            totalMemorySize(0),
            maxMemorySize(0)
        {}

        SPKMemoryTracer(const SPKMemoryTracer&); // Not used
        SPKMemoryTracer& operator=(const SPKMemoryTracer&); // Not used

        unsigned long nextIndex;
        unsigned long totalMemorySize;
        unsigned long maxMemorySize;

        std::set<BlockInfo> blocks;
    };

    inline bool operator==(const SPKMemoryTracer::BlockInfo& block0,const SPKMemoryTracer::BlockInfo& block1)
    {
        return block0.position == block1.position;
    }

    inline bool operator<(const SPKMemoryTracer::BlockInfo& block0,const SPKMemoryTracer::BlockInfo& block1)
    {
        return block0.position < block1.position;
    }

    inline bool compareAllocTime(const SPKMemoryTracer::BlockInfo& block0,const SPKMemoryTracer::BlockInfo& block1)
    {
        return block0.index < block1.index;
    }
}
#endif
#endif
