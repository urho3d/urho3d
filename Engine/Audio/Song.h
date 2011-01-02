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

#ifndef AUDIO_SONG_H
#define AUDIO_SONG_H

#include "Resource.h"
#include "SharedPtr.h"

#include <vector>

class Audio;
class Channel;

//! Base class for sound resources
class Song : public Resource
{
public:
    //! Construct with audio subsystem pointer and name
    Song(Audio* audio, const std::string& name);
    //! Destruct. Stop playback and free song data
    virtual ~Song();
    
    //! Play from a specified position
    virtual void play(unsigned position = 0) = 0;
    //! Return current position
    virtual unsigned getPosition() const = 0;
    
    //! Stop playback
    void stop();
    //! Set master volume between 0.0 (silence) and 1.0 (full volume)
    void setGain(float gain);
    //! Activate a fade in or out. Target 0.0 is silence and 1.0 is full volume
    void fade(float target, float speed);
    //! Change BPM tempo
    void setBpmTempo(unsigned tempo);
    
    //! Return master volume
    float getGain() const { return mGain; }
    //! Return current fader value
    float getFader() const { return mFader; }
    //! Return fader target volume
    float getFaderTarget() const { return mFaderTarget; }
    //! Return fade speed
    float getFadeSpeed() const { return mFadeSpeed; }
    //! Return BPM tempo
    unsigned getBpmTempo() const { return mBpmTempo; }
    //! Return whether loaded
    bool isLoaded() const { return mLoaded; }
    //! Return whether playing
    bool isPlaying() const { return mPlaying; }
    
    //! Advance song and update fader if active
    void update();
    //! Decrement sample counter until next tempo tick
    void decSampleCount(unsigned played);
    //! Return sample counter
    unsigned getSampleCount() const { return mSampleCount; }
    
    //! Vibrato type table common to MOD and XM modules
    static const unsigned char sVibratoTypeTable[];
    //! Panning table common to MOD and XM modules
    static const unsigned char sPanningTable[];
    //! Vibrato table common to MOD and XM modules
    static const signed char sVibratoTable[4][256];
    
protected:
    //! Subclass-specific player tick
    virtual void updatePlayer() = 0;
    //! Set number of channels
    void setNumChannels(unsigned channels);
    
    //! Audio subsystem
    WeakPtr<Audio> mAudio;
    //! Channels used by the song
    std::vector<Channel*> mChannels;
    //! Loaded flag
    bool mLoaded;
    //! Playing flag
    bool mPlaying;
    
private:
    //! Update fader
    void updateMasterFade();
    //! Free channels
    void releaseChannels();
    
    //! Samples remaining until next update tick
    unsigned mSampleCount;
    //! BPM tempo
    unsigned mBpmTempo;
    //! Master gain
    float mGain;
    //! Fader value
    float mFader;
    //! Fader target
    float mFaderTarget;
    //! Fade speed
    float mFadeSpeed;
};

#endif // AUDIO_SONG_H
