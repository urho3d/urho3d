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

#ifndef COMMON_SIGNAL_H
#define COMMON_SIGNAL_H

//! An operating system signal (event) for communication between threads
class Signal
{
    //! Construct with either automatical or manual reset
    Signal(bool autoReset = true);
    //! Destruct
    ~Signal();
    
    //! Raise the signal
    void set();
    //! Reset the signal if not automatically reset
    void reset();
    //! Wait for the signal to be raised. Reset automatically if enabled
    void wait();
    
    //! Return whether signal is automatically reset
    bool isAutoReset() const;
    
private:
    //! Event handle
    void* mHandle;
    //! Autoreset flag
    bool mAutoReset;
};

#endif // COMMON_SIGNAL_H
