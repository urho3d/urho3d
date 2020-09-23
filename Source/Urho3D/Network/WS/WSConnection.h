#pragma once
struct lws;

namespace Urho3D {

    class WSConnection {
    public:
        WSConnection(){}
        WSConnection(lws* ws):
        ws_(ws)
        {}

        inline bool operator==( WSConnection const& connA) const { return connA.ToHash() == ToHash();}

        unsigned ToHash() const
        {
            return ((unsigned)(size_t)(reinterpret_cast<intptr_t>(ws_) >> 9));
        }
    private:
        lws* ws_;
    };
}
