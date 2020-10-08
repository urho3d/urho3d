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

#pragma once

#include <cstdint>
#include <stddef.h>

/// libwebsockets struct that must be declared outside of Urho3D namespace
struct lws;

namespace Urho3D {

    class WSConnection {
    public:
        /// Construct.
        WSConnection(): ws_(nullptr) {}
        /// Construct.
        WSConnection(lws* ws): ws_(ws) {}

        /// Get WS connection
        lws* GetWS() const { return ws_; }

        inline bool operator==( WSConnection const& connB) const { return connB.ws_ == ws_;}
        inline bool operator!=( WSConnection const& connB) const { return connB.ws_ != ws_;}

        unsigned ToHash() const
        {
            return ((unsigned)(size_t)(reinterpret_cast<intptr_t>(ws_) >> 9));
        }
    private:
        /// Websocket connection
        lws* ws_;
    };
}
