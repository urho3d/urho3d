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

#ifndef AUDIO_XM_H
#define AUDIO_XM_H

#include "Song.h"

#include <vector>

class Channel;
class Sound;

//! XM identification
struct XMId
{
    unsigned char mId[17];
    unsigned char mModName[20];
    unsigned char mIdByte;
    unsigned char mTrackerName[20];
    unsigned short mVersion;
};

//! XM song header
struct XMHeader
{
    unsigned mHeaderSize;
    unsigned short mSongLength;
    unsigned short mRestartPos;
    unsigned short mNumChannels;
    unsigned short mNumPatterns;
    unsigned short mNumInstruments;
    unsigned short mUseLinear;
    unsigned short mDefaultTickTempo;
    unsigned short mDefaultBpmTempo;
    unsigned char mOrder[256];
} ;

//! XM packed pattern
struct XMPackedPattern
{
    unsigned mHeaderSize;
    unsigned char mPackingType;
    unsigned short mRows;
    unsigned short mPackSize;
};

//! XM unpacked pattern
struct XMPattern
{
    unsigned short mRows;
    SharedArrayPtr<unsigned char> mData;
};

//! XM note
struct XMNote
{
    unsigned char mNote;
    unsigned char mInstrument;
    unsigned char mVolEffect;
    unsigned char mEffect;
    unsigned char mEffectData;
};

//! XM volume or panning envelope
struct XMEnvelope
{
    unsigned short mX;
    unsigned short mY;
};

//! XM sample
struct XMSample
{
    int mLength;
    unsigned mLoopStart;
    unsigned mLoopLength;
    unsigned char mVolume;
    signed char mFineTune;
    unsigned char mSoundFlags;
    unsigned char mPanning;
    signed char mRelativeNote;
    unsigned char mReserved;
    unsigned char mName[22];
};

//! XM instrument
struct XMInstrument
{
    unsigned mHeaderSize;
    unsigned char mName[22];
    unsigned char mType;
    unsigned short mNumSamples;
    unsigned mSoundHeaderSize;
    unsigned char mSampleTable[96];
    XMEnvelope mVolumeEnv[12];
    XMEnvelope mPanningEnv[12];
    unsigned char mVolumeEnvPoints;
    unsigned char mPanningEnvPoints;
    unsigned short mVolumeSustainPoint;
    unsigned short mVolumeLoopStart;
    unsigned short mVolumeLoopEnd;
    unsigned short mPanningSustainPoint;
    unsigned short mPanningLoopStart;
    unsigned short mPanningLoopEnd;
    unsigned char mVolumeEnvFlags;
    unsigned char mPanningEnvFlags;
    unsigned char mVibratoType;
    unsigned char mVibratoSweep;
    unsigned char mVibratoDepth;
    unsigned char mVibratoRate;
    unsigned short mFadeOut;
    unsigned short mReserved;
    unsigned char mVolumeEnvLookup[325];
    unsigned char mPanningEnvLookup[325];
    std::vector<XMSample> mXMSamples;
    std::vector<SharedPtr<Sound> > mSounds;
};

//! XM track state
struct XMTrack
{
    XMInstrument *mInstr;
    XMSample* mXMSample;
    SharedPtr<Sound> mSound;
    unsigned short mVolumeEnvPos;
    unsigned short mPanningEnvPos;
    int mFadeOutValue;
    unsigned char mNewNote;
    short mRealNote;
    unsigned char mNote;
    unsigned char mInstrument;
    unsigned char mNewInstrument;
    unsigned char mVolEffect;
    unsigned char mEffect;
    unsigned char mEffectData;
    unsigned char mNybble1;
    unsigned char mNybble2;
    unsigned char mSoundNumber;
    signed char mNoteVolume;
    signed char mVolume;
    signed char mFineTune;
    short mBasePeriod;
    short mPeriod;
    short mTargetPeriod;
    unsigned char mNotePanning;
    bool mKeyOn;
    bool mTonePortamento;
    unsigned char mTonePortaSpeed;
    unsigned char mVolumeSpeedUp;
    unsigned char mVolumeSpeedDown;
    unsigned char mPortaSpeedUp;
    unsigned char mPortaSpeedDown;
    unsigned char mPanningSpeedRight;
    unsigned char mPanningSpeedLeft;
    unsigned char mVibratoType;
    unsigned char mVibratoSpeed;
    unsigned char mVibratoDepth;
    unsigned char mVibratoPhase;
    unsigned char mSoundOffset;
    unsigned char mGlissando;
    unsigned char mTremoloType;
    unsigned char mTremoloSpeed;
    unsigned char mTremoloDepth;
    unsigned char mTremoloPhase;
    unsigned char mInstrVibratoPhase;
    unsigned short mInstrVibratoDepth;
    unsigned char mMultiRetrigCount;
    unsigned char mRetrigCount;
    unsigned char mRetrigInterval;
    unsigned char mRetrigVolChange;
    unsigned short mPatternLoopLine;
    unsigned char mPatternLoopCount;
    unsigned char mTremorCount;
    unsigned char mTremorOnTime;
    unsigned char mTremorOffTime;
    unsigned char mTremorStatus;
};

//! XM format song resource
class XM : public Song
{
    DEFINE_TYPE(XM);
    
public:
    //! Construct with audio subsystem pointer and name
    XM(Audio* audio, const std::string& name = std::string());
    //! Destruct. Stop playback and free song data
    virtual ~XM();
    
    //! Load the resource
    virtual void load(Deserializer& source, ResourceCache* cache = 0);
    //! Play from a specified position
    virtual void play(unsigned position = 0);
    //! Return current position
    virtual unsigned getPosition() const { return mPos; }
    
    //! XM linear frequency table
    static const unsigned sLinearFreqTable[];
    //! XM Amiga frequency table
    static const unsigned short sAmigaFreqTable[];
    //! Note retrigger add table
    static const signed char sRetrigAddTable[];
    //! Note retrigger multiply table
    static const signed char sRetrigMulTable[];
    //! Empty note
    static const XMNote sEmptyNote;
    
protected:
    //! Update player
    virtual void updatePlayer();
    
private:
    //! Release song data
    void release();
    //! Start new note
    void startNewNote(XMTrack* tptr, Channel* chptr);
    //! Perform toneportamento effect
    void tonePortamento(XMTrack* tptr, Channel* chptr);
    //! Perform vibrato effect
    void vibrato(XMTrack* tptr, Channel* chptr);
    //! Perform volume slide
    void volumeSlide(XMTrack* tptr, Channel* chptr);
    //! Perform an extended command
    void extendedCommand(XMTrack* tptr, Channel* chptr);
    //! Change instrument on a track
    void changeInstrument(XMTrack* tptr);
    //! Return the Amiga period value corresponding to a note
    unsigned getAmigaPeriod(int mNote, int mFineTune);
    
    //! Sequencer position
    unsigned short mPos;
    //! Position within pattern
    unsigned short mLine;
    //! Tick tempo
    unsigned short mTickTempo;
    //! Tick counter
    unsigned short mTickCount;
    //! Global volume speed up
    unsigned char mGlobalVolSpeedUp;
    //! Global volume speed down
    unsigned char mGlobalVolSpeedDown;
    //! Pattern break flag
    bool mPatternBreak;
    //! Pattern delay counter
    unsigned char mPatternDelay;
    //! Global volume
    int mGlobalVol;
    //! Low period limit
    int mLowPeriod;
    //! High period limit
    int mHighPeriod;
    //! XM identification
    XMId mXMId;
    //! XM song header
    XMHeader mXMHeader;
    //! XM patterns
    std::vector<XMPattern> mPatterns;
    //! XM instruments
    std::vector<XMInstrument> mInstruments;
    //! XM track states
    std::vector<XMTrack> mTracks;
};

#endif // AUDIO_XM_H
