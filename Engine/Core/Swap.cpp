#include "Precompiled.h"
#include "CoreString.h"
#include "ListBase.h"
#include "VectorBase.h"

template<> void Swap<String>(String& first, String& second)
{
    first.Swap(second);
}

template<> void Swap<VectorBase>(VectorBase& first, VectorBase& second)
{
    first.Swap(second);
}

template<> void Swap<SkipListBase>(SkipListBase& first, SkipListBase& second)
{
    first.Swap(second);
}
