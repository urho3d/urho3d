// DO NOT EDIT. This file is generated

#pragma once

#include <AngelScript/angelscript.h>

#include <new>

namespace Urho3D
{

// Constructors that don't require parameter conversion between C++ and AngelScript

#ifdef AS_MAX_PORTABILITY

template <class C>
void ASCompatibleConstructor(asIScriptGeneric* gen)
{
    new (gen->GetObject()) C();
}

template <class C, typename P0>
void ASCompatibleConstructor(asIScriptGeneric* gen)
{
    new (gen->GetObject()) C(*reinterpret_cast<P0*>(gen->GetAddressOfArg(0)));
}

template <class C, typename P0, typename P1>
void ASCompatibleConstructor(asIScriptGeneric* gen)
{
    new (gen->GetObject()) C(*reinterpret_cast<P0*>(gen->GetAddressOfArg(0)),
                             *reinterpret_cast<P1*>(gen->GetAddressOfArg(1)));
}

template <class C, typename P0, typename P1, typename P2>
void ASCompatibleConstructor(asIScriptGeneric* gen)
{
    new (gen->GetObject()) C(*reinterpret_cast<P0*>(gen->GetAddressOfArg(0)),
                             *reinterpret_cast<P1*>(gen->GetAddressOfArg(1)),
                             *reinterpret_cast<P2*>(gen->GetAddressOfArg(2)));
}

template <class C, typename P0, typename P1, typename P2, typename P3>
void ASCompatibleConstructor(asIScriptGeneric* gen)
{
    new (gen->GetObject()) C(*reinterpret_cast<P0*>(gen->GetAddressOfArg(0)),
                             *reinterpret_cast<P1*>(gen->GetAddressOfArg(1)),
                             *reinterpret_cast<P2*>(gen->GetAddressOfArg(2)),
                             *reinterpret_cast<P3*>(gen->GetAddressOfArg(3)));
}

template <class C, typename P0, typename P1, typename P2, typename P3, typename P4>
void ASCompatibleConstructor(asIScriptGeneric* gen)
{
    new (gen->GetObject()) C(*reinterpret_cast<P0*>(gen->GetAddressOfArg(0)),
                             *reinterpret_cast<P1*>(gen->GetAddressOfArg(1)),
                             *reinterpret_cast<P2*>(gen->GetAddressOfArg(2)),
                             *reinterpret_cast<P3*>(gen->GetAddressOfArg(3)),
                             *reinterpret_cast<P4*>(gen->GetAddressOfArg(4)));
}

template <class C, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
void ASCompatibleConstructor(asIScriptGeneric* gen)
{
    new (gen->GetObject()) C(*reinterpret_cast<P0*>(gen->GetAddressOfArg(0)),
                             *reinterpret_cast<P1*>(gen->GetAddressOfArg(1)),
                             *reinterpret_cast<P2*>(gen->GetAddressOfArg(2)),
                             *reinterpret_cast<P3*>(gen->GetAddressOfArg(3)),
                             *reinterpret_cast<P4*>(gen->GetAddressOfArg(4)),
                             *reinterpret_cast<P5*>(gen->GetAddressOfArg(5)));
}

template <class C, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
void ASCompatibleConstructor(asIScriptGeneric* gen)
{
    new (gen->GetObject()) C(*reinterpret_cast<P0*>(gen->GetAddressOfArg(0)),
                             *reinterpret_cast<P1*>(gen->GetAddressOfArg(1)),
                             *reinterpret_cast<P2*>(gen->GetAddressOfArg(2)),
                             *reinterpret_cast<P3*>(gen->GetAddressOfArg(3)),
                             *reinterpret_cast<P4*>(gen->GetAddressOfArg(4)),
                             *reinterpret_cast<P5*>(gen->GetAddressOfArg(5)),
                             *reinterpret_cast<P6*>(gen->GetAddressOfArg(6)));
}

template <class C, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
void ASCompatibleConstructor(asIScriptGeneric* gen)
{
    new (gen->GetObject()) C(*reinterpret_cast<P0*>(gen->GetAddressOfArg(0)),
                             *reinterpret_cast<P1*>(gen->GetAddressOfArg(1)),
                             *reinterpret_cast<P2*>(gen->GetAddressOfArg(2)),
                             *reinterpret_cast<P3*>(gen->GetAddressOfArg(3)),
                             *reinterpret_cast<P4*>(gen->GetAddressOfArg(4)),
                             *reinterpret_cast<P5*>(gen->GetAddressOfArg(5)),
                             *reinterpret_cast<P6*>(gen->GetAddressOfArg(6)),
                             *reinterpret_cast<P7*>(gen->GetAddressOfArg(7)));
}

#else

template <class C>
void ASCompatibleConstructor(C* ptr)
{
    new (ptr) C();
}

template <class C, typename P0>
void ASCompatibleConstructor(C* ptr, P0 p0)
{
    new (ptr) C(p0);
}

template <class C, typename P0, typename P1>
void ASCompatibleConstructor(C* ptr, P0 p0, P1 p1)
{
    new (ptr) C(p0, p1);
}

template <class C, typename P0, typename P1, typename P2>
void ASCompatibleConstructor(C* ptr, P0 p0, P1 p1, P2 p2)
{
    new (ptr) C(p0, p1, p2);
}

template <class C, typename P0, typename P1, typename P2, typename P3>
void ASCompatibleConstructor(C* ptr, P0 p0, P1 p1, P2 p2, P3 p3)
{
    new (ptr) C(p0, p1, p2, p3);
}

template <class C, typename P0, typename P1, typename P2, typename P3, typename P4>
void ASCompatibleConstructor(C* ptr, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4)
{
    new (ptr) C(p0, p1, p2, p3, p4);
}

template <class C, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
void ASCompatibleConstructor(C* ptr, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
{
    new (ptr) C(p0, p1, p2, p3, p4, p5);
}

template <class C, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
void ASCompatibleConstructor(C* ptr, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6)
{
    new (ptr) C(p0, p1, p2, p3, p4, p5, p6);
}

template <class C, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
void ASCompatibleConstructor(C* ptr, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7)
{
    new (ptr) C(p0, p1, p2, p3, p4, p5, p6, p7);
}

#endif

// Factories that don't require parameter conversion between C++ and AngelScript

#ifdef AS_MAX_PORTABILITY

template <class C>
void ASCompatibleFactory(asIScriptGeneric* gen)
{
    gen->SetReturnAddress(new C());
}

template <class C, typename P0>
void ASCompatibleFactory(asIScriptGeneric* gen)
{
    gen->SetReturnAddress(new C(*reinterpret_cast<P0*>(gen->GetAddressOfArg(0))));
}

template <class C, typename P0, typename P1>
void ASCompatibleFactory(asIScriptGeneric* gen)
{
    gen->SetReturnAddress(new C(*reinterpret_cast<P0*>(gen->GetAddressOfArg(0)),
                                *reinterpret_cast<P1*>(gen->GetAddressOfArg(1))));
}

template <class C, typename P0, typename P1, typename P2>
void ASCompatibleFactory(asIScriptGeneric* gen)
{
    gen->SetReturnAddress(new C(*reinterpret_cast<P0*>(gen->GetAddressOfArg(0)),
                                *reinterpret_cast<P1*>(gen->GetAddressOfArg(1)),
                                *reinterpret_cast<P2*>(gen->GetAddressOfArg(2))));
}

template <class C, typename P0, typename P1, typename P2, typename P3>
void ASCompatibleFactory(asIScriptGeneric* gen)
{
    gen->SetReturnAddress(new C(*reinterpret_cast<P0*>(gen->GetAddressOfArg(0)),
                                *reinterpret_cast<P1*>(gen->GetAddressOfArg(1)),
                                *reinterpret_cast<P2*>(gen->GetAddressOfArg(2)),
                                *reinterpret_cast<P3*>(gen->GetAddressOfArg(3))));
}

template <class C, typename P0, typename P1, typename P2, typename P3, typename P4>
void ASCompatibleFactory(asIScriptGeneric* gen)
{
    gen->SetReturnAddress(new C(*reinterpret_cast<P0*>(gen->GetAddressOfArg(0)),
                                *reinterpret_cast<P1*>(gen->GetAddressOfArg(1)),
                                *reinterpret_cast<P2*>(gen->GetAddressOfArg(2)),
                                *reinterpret_cast<P3*>(gen->GetAddressOfArg(3)),
                                *reinterpret_cast<P4*>(gen->GetAddressOfArg(4))));
}

template <class C, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
void ASCompatibleFactory(asIScriptGeneric* gen)
{
    gen->SetReturnAddress(new C(*reinterpret_cast<P0*>(gen->GetAddressOfArg(0)),
                                *reinterpret_cast<P1*>(gen->GetAddressOfArg(1)),
                                *reinterpret_cast<P2*>(gen->GetAddressOfArg(2)),
                                *reinterpret_cast<P3*>(gen->GetAddressOfArg(3)),
                                *reinterpret_cast<P4*>(gen->GetAddressOfArg(4)),
                                *reinterpret_cast<P5*>(gen->GetAddressOfArg(5))));
}

template <class C, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
void ASCompatibleFactory(asIScriptGeneric* gen)
{
    gen->SetReturnAddress(new C(*reinterpret_cast<P0*>(gen->GetAddressOfArg(0)),
                                *reinterpret_cast<P1*>(gen->GetAddressOfArg(1)),
                                *reinterpret_cast<P2*>(gen->GetAddressOfArg(2)),
                                *reinterpret_cast<P3*>(gen->GetAddressOfArg(3)),
                                *reinterpret_cast<P4*>(gen->GetAddressOfArg(4)),
                                *reinterpret_cast<P5*>(gen->GetAddressOfArg(5)),
                                *reinterpret_cast<P6*>(gen->GetAddressOfArg(6))));
}

template <class C, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
void ASCompatibleFactory(asIScriptGeneric* gen)
{
    gen->SetReturnAddress(new C(*reinterpret_cast<P0*>(gen->GetAddressOfArg(0)),
                                *reinterpret_cast<P1*>(gen->GetAddressOfArg(1)),
                                *reinterpret_cast<P2*>(gen->GetAddressOfArg(2)),
                                *reinterpret_cast<P3*>(gen->GetAddressOfArg(3)),
                                *reinterpret_cast<P4*>(gen->GetAddressOfArg(4)),
                                *reinterpret_cast<P5*>(gen->GetAddressOfArg(5)),
                                *reinterpret_cast<P6*>(gen->GetAddressOfArg(6)),
                                *reinterpret_cast<P7*>(gen->GetAddressOfArg(7))));
}

#else

template <class C>
C* ASCompatibleFactory()
{
    return new C();
}

template <class C, typename P0>
C* ASCompatibleFactory(P0 p0)
{
    return new C(p0);
}

template <class C, typename P0, typename P1>
C* ASCompatibleFactory(P0 p0, P1 p1)
{
    return new C(p0, p1);
}

template <class C, typename P0, typename P1, typename P2>
C* ASCompatibleFactory(P0 p0, P1 p1, P2 p2)
{
    return new C(p0, p1, p2);
}

template <class C, typename P0, typename P1, typename P2, typename P3>
C* ASCompatibleFactory(P0 p0, P1 p1, P2 p2, P3 p3)
{
    return new C(p0, p1, p2, p3);
}

template <class C, typename P0, typename P1, typename P2, typename P3, typename P4>
C* ASCompatibleFactory(P0 p0, P1 p1, P2 p2, P3 p3, P4 p4)
{
    return new C(p0, p1, p2, p3, p4);
}

template <class C, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
C* ASCompatibleFactory(P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
{
    return new C(p0, p1, p2, p3, p4, p5);
}

template <class C, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
C* ASCompatibleFactory(P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6)
{
    return new C(p0, p1, p2, p3, p4, p5, p6);
}

template <class C, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
C* ASCompatibleFactory(P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7)
{
    return new C(p0, p1, p2, p3, p4, p5, p6, p7);
}

#endif

} // namespace Urho3D
