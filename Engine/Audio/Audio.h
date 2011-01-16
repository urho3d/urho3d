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

#ifndef AUDIO_AUDIO_H
#define AUDIO_AUDIO_H

#include "AudioDefs.h"
#include "Mutex.h"
#include "Quaternion.h"
#include "Thread.h"
#include "SharedArrayPtr.h"

#include <vector>

class AudioImpl;
class Channel;
class Song;
class Sound;

//! Manages a DirectSound audio buffer and the playback thread, channels and songs.
class Audio : public RefCounted, public Thread
{
    friend class AudioImpl;
    
public:
    //! Construct with a window handle (needs to be valid)
    Audio(unsigned windowHandle);
    //! Destruct. Terminate the audio thread and free the audio buffer
    virtual ~Audio();
    
    //! Initialize audio output with specified buffer length and output mode
    bool setMode(int bufferLengthMSec, int mixRate, bool sixteenBit, bool stereo, bool interpolate = true);
    //! Run update on sound channels. Not required for continued playback, but frees unused channels/sounds and updates 3D positions.
    void update(float timeStep);
    //! Restart audio output
    bool play();
    //! Suspend audio output
    void stop();
    //! Set master gain on a specific channel type such as sound effects, music or voice.
    void setMasterGain(ChannelType type, float gain);
    //! Set listener position
    void setListenerPosition(const Vector3& position);
    //! Set listener rotation
    void setListenerRotation(const Quaternion& rotation);
    //! Set listener position and rotation
    void setListenerTransform(const Vector3& position, const Quaternion& rotation);
    //! Stop any channel playing a certain sound
    void stopSound(Sound* sound);
    
    //! Return audio implementation, which holds the actual DirectSound resources
    AudioImpl* getImpl() { return mImpl; }
    //! Return audio buffer size in samples
    unsigned getBufferSamples() const { return mBufferSamples; }
    //! Return audio buffer size in bytes
    unsigned getBufferSize() const { return mBufferSize; }
    //! Return byte size of one sample
    unsigned getSampleSize() const { return mSampleSize; }
    //! Return mixing rate
    int getMixRate() const { return mMixRate; }
    //! Return whether output is sixteen bit
    bool isSixteenBit() const { return mSixteenBit; }
    //! Return whether output is stereo
    bool isStereo() const { return mStereo; }
    //! Return whether output is interpolated
    bool isInterpolated() const { return mInterpolate; }
    //! Return whether audio is being output
    bool isPlaying() const { return mPlaying; }
    //! Return whether an audio buffer has been reserved
    bool hasBuffer() const;
    //! Return master gain for a specific channel type
    float getMasterGain(ChannelType type) const;
    //! Return listener position
    const Vector3& getListenerPosition() const { return mListenerPosition; }
    //! Return listener rotation
    const Quaternion& getListenerRotation() const { return mListenerRotation; }
    //! Return all channels
    const std::vector<Channel*>& getChannels() const { return mChannels; }
    //! Return all active songs
    const std::vector<Song*>& getSongs() const { return mSongs; }
    
    //! Add a channel to keep track of. Called by Channel
    void addChannel(Channel* channel);
    //! Remove a channel. Called by Channel
    void removeChannel(Channel* channel);
    //! Add a song to keep track of. Called by Song
    void addSong(Song* song);
    //! Remove a song. Called by Song
    void removeSong(Song* song);
    //! Return audio thread mutex
    Mutex& getMutex() { return mAudioMutex; }
    //! Return channel type specific gain multiplied by master gain
    float getChannelMasterGain(ChannelType type) const { return mMasterGain[CHANNEL_MASTER] * mMasterGain[type]; }
    
    //! Mixing thread function
    virtual void threadFunction();
    
private:
    //! Mix audio to the buffer
    void mixOutput(void* dest, unsigned bytes);
    //! Release the audio buffer
    void releaseBuffer();
    
    //! Implementation
    AudioImpl* mImpl;
    //! Clipping buffer for mixing
    SharedArrayPtr<int> mClipBuffer;
    //! Audio thread mutex
    Mutex mAudioMutex;
    //! Audio buffer size in samples
    unsigned mBufferSamples;
    //! Audio buffer size in bytes
    unsigned mBufferSize;
    //! Sound size
    unsigned mSampleSize;
    //! Mixing rate
    int mMixRate;
    //! Sixteen bit flag
    bool mSixteenBit;
    //! Stereo flag
    bool mStereo;
    //! Interpolation flag
    bool mInterpolate;
    //! Playing flag
    bool mPlaying;
    //! Master gain by channel type
    float mMasterGain[MAX_CHANNEL_TYPES];
    //! Channels
    std::vector<Channel*> mChannels;
    //! Songs
    std::vector<Song*> mSongs;
    //! Listener position
    Vector3 mListenerPosition;
    //! Listener rotation
    Quaternion mListenerRotation;
};

#endif // AUDIO_AUDIO_H
