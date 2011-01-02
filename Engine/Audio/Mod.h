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

// Original MOD & XM playback code from JUDAS Soundsystem
// Copyright (c) 1997 Lasse Öörni & Olli Niemitalo

#ifndef AUDIO_MOD_H
#define AUDIO_MOD_H

#include "Song.h"

#include <string>
#include <vector>

class Channel;
class Sound;

//! MOD identification string and corresponding channel count
struct ModIdent
{
    std::string mString;
    int mChannels;
};

//! MOD note
struct ModNote
{
    unsigned char mNote;
    unsigned char mInstrNum;
    unsigned char mCommand;
    unsigned char mData;
};

//! MOD instrument
struct ModInstrument
{
    SharedPtr<Sound> mSound;
    signed char mVolume;
    unsigned char mFineTune;
};

//! MOD track state
struct ModTrack
{
    ModInstrument* mInstr;
    unsigned char mNewNote;
    unsigned char mNote;
    unsigned char mInstrNum;
    unsigned char mNewInstrNum;
    unsigned char mEffect;
    unsigned char mEffectData;
    unsigned char mNybble1;
    unsigned char mNybble2;
    unsigned char mSmp;
    signed char mFineTune;
    signed char mVolume;
    unsigned short mBasePeriod;
    unsigned short mPeriod;
    unsigned short mTargetPeriod;
    bool mTonePortamento;
    bool mUseSoundOffset;
    unsigned char mTonePortaSpeed;
    unsigned char mSoundOffset;
    unsigned char mVolSpeedUp;
    unsigned char mVolSpeedDown;
    unsigned char mPortaSpeedUp;
    unsigned char mPortaSpeedDown;
    unsigned char mVibratoType;
    unsigned char mVibratoSpeed;
    unsigned char mVibratoDepth;
    unsigned char mVibratoPhase;
    unsigned char mGlissando;
    unsigned char mTremoloType;
    unsigned char mTremoloSpeed;
    unsigned char mTremoloDepth;
    unsigned char mTremoloPhase;
    unsigned char mPatternLoopLine;
    unsigned char mPatternLoopCount;
    unsigned char mRetrigCount;
};

//! MOD format song resource
class Mod : public Song
{
    DEFINE_TYPE(Mod);
    
public:
    //! Construct with audio subsystem pointer and name
    Mod(Audio* audio, const std::string& name = std::string());
    //! Destruct. Stop playback and free song data
    virtual ~Mod();
    
    //! Load the resource
    virtual void load(Deserializer& source, ResourceCache* cache = 0);
    //! Play from a specified position
    virtual void play(unsigned position = 0);
    //! Return current position
    virtual unsigned getPosition() const { return mPos; }
    
    //! MOD identification strings
    static const ModIdent sIdent[];
    //! MOD frequency table
    static const unsigned short sPeriodTable[16][12];
    
protected:
    //! Update player
    virtual void updatePlayer();
    
private:
    //! Release song data
    void release();
    //! Start new note
    void startNewNote(ModTrack* tptr, Channel* chptr);
    //! Perform toneportamento effect
    void tonePortamento(ModTrack* tptr, Channel* chptr);
    //! Perform vibrato effect
    void vibrato(ModTrack* tptr, Channel* chptr);
    //! Perform volume slide effect
    void volumeSlide(ModTrack* tptr, Channel* chptr);
    //! Perform extended command
    void extendedCommand(ModTrack* tptr, Channel* chptr);
    
    //! Sequencer position
    unsigned char mPos;
    //! Position within pattern
    unsigned char mLine;
    //! Song length
    unsigned char mLength;
    //! Tick tempo
    unsigned char mTickTempo;
    //! Tick counter
    unsigned char mTickCount;
    //! Pattern delay counter
    unsigned char mPatternDelay;
    //! Pattern break flag
    bool mPatternBreak;
    //! Number of channels
    unsigned mNumChannels;
    //! Number of patterns
    unsigned mNumPatterns;
    //! Pattern size in bytes
    unsigned mPatternLength;
    //! MOD info block
    SharedArrayPtr<unsigned char> mInfo;
    //! MOD pattern data
    SharedArrayPtr<unsigned char> mPatterns;
    //! MOD instruments
    std::vector<ModInstrument> mInstruments;
    //! MOD track states
    std::vector<ModTrack> mTracks;
};

#endif // AUDIO_MOD_H
