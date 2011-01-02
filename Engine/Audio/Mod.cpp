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

#include "Precompiled.h"
#include "Audio.h"
#include "Channel.h"
#include "Deserializer.h"
#include "Mod.h"
#include "Profiler.h"
#include "Sound.h"

#include <cstring>

#include "DebugNew.h"

static const int AMIGA_CLOCK = 3579545;
static const int MOD_INSTRUMENTS = 31;
static const int MOD_MAXLENGTH = 128;
static const int MOD_MAXCHANNELS = 32;
static const int MOD_INFOBLOCK = 1084;
static const int MOD_NAMEOFFSET = 0;
static const int MOD_INSTROFFSET = 20;
static const int MOD_LENGTHOFFSET = 950;
static const int MOD_ORDEROFFSET = 952;
static const int MOD_IDENTOFFSET = 1080;

const ModIdent Mod::sIdent[] =
{
    {"2CHN", 2},
    {"M.K.", 4},
    {"M!K!", 4},
    {"4CHN", 4},
    {"6CHN", 6},
    {"8CHN", 8},
    {"10CH", 10},
    {"12CH", 12},
    {"14CH", 14},
    {"16CH", 16},
    {"18CH", 18},
    {"20CH", 20},
    {"22CH", 22},
    {"24CH", 24},
    {"26CH", 26},
    {"28CH", 28},
    {"30CH", 30},
    {"32CH", 32}
};

const unsigned short Mod::sPeriodTable[16][12] =
{
    {6848, 6464, 6096, 5760, 5424, 5120, 4832, 4560, 4304, 4064, 3840, 3624},
    {6800, 6416, 6056, 5720, 5392, 5096, 4808, 4536, 4280, 4040, 3816, 3600},
    {6752, 6368, 6016, 5672, 5360, 5056, 4776, 4504, 4256, 4016, 3792, 3576},
    {6704, 6328, 5968, 5632, 5320, 5024, 4736, 4472, 4224, 3984, 3760, 3552},
    {6656, 6280, 5928, 5592, 5280, 4984, 4704, 4440, 4192, 3960, 3736, 3528},
    {6608, 6232, 5888, 5552, 5240, 4952, 4672, 4408, 4160, 3928, 3704, 3496},
    {6560, 6192, 5840, 5512, 5208, 4912, 4640, 4376, 4128, 3896, 3680, 3472},
    {6512, 6144, 5800, 5472, 5168, 4880, 4600, 4344, 4104, 3872, 3656, 3448},
    {7256, 6848, 6464, 6096, 5760, 5424, 5120, 4832, 4560, 4304, 4032, 3840},
    {7200, 6800, 6416, 6056, 5720, 5400, 5088, 4808, 4536, 4280, 4040, 3816},
    {7152, 6752, 6368, 6016, 5672, 5360, 5056, 4776, 4504, 4256, 4016, 3792},
    {7096, 6704, 6328, 5968, 5632, 5320, 5024, 4736, 4472, 4224, 3984, 3760},
    {7048, 6656, 6280, 5928, 5592, 5280, 4984, 4704, 4440, 4192, 3952, 3736},
    {7000, 6608, 6232, 5888, 5552, 5240, 4952, 4672, 4408, 4160, 3928, 3704},
    {6944, 6560, 6192, 5840, 5512, 5208, 4912, 4640, 4376, 4128, 3896, 3680},
    {6896, 6512, 6144, 5800, 5472, 5168, 4880, 4600, 4344, 4104, 3872, 3656}
};

Mod::Mod(Audio* audio, const std::string& name) :
    Song(audio, name),
    mPos(0)
{
}

Mod::~Mod()
{
    release();
}

void Mod::load(Deserializer& source, ResourceCache* cache)
{
    PROFILE(Mod_Load);
    
    release();
    
    unsigned memoryUse = 0;
    
    // Load info
    mInfo = new unsigned char[MOD_INFOBLOCK];
    source.read(mInfo.getPtr(), MOD_INFOBLOCK);
    mInfo[20] = 0; 
    memoryUse += MOD_INFOBLOCK;
    
    mNumChannels = 0;
    for (unsigned i = 0; i < 18; ++i)
    {
        if (!memcmp(sIdent[i].mString.c_str(), &mInfo[MOD_IDENTOFFSET], 4))
            mNumChannels = sIdent[i].mChannels;
    }
    
    if (!mNumChannels)
        EXCEPTION("Could not determine mod format from " + source.getName());
    
    // Create tracks
    mTracks.resize(mNumChannels);
    
    mPatternLength = mNumChannels * 256;
    mLength = mInfo[MOD_LENGTHOFFSET];
    unsigned char* order = &mInfo[MOD_ORDEROFFSET];
    
    mNumPatterns = 0;
    for (unsigned i = 0; i < MOD_MAXLENGTH; ++i)
        if (order[i] > mNumPatterns) mNumPatterns = order[i];
    mNumPatterns++;
    
    // Read patterns
    mPatterns = new unsigned char[mPatternLength * mNumPatterns];
    source.read(mPatterns.getPtr(), mPatternLength * mNumPatterns);
    memoryUse += mPatternLength * mNumPatterns;
    
    ModNote* destPtr = (ModNote*)mPatterns.getPtr();
    unsigned char* srcPtr = mPatterns;
    for (unsigned i = 0; i < mPatternLength * mNumPatterns / 4; ++i)
    {
        unsigned short period = ((srcPtr[0] & 0x0f) << 8) | srcPtr[1];
        unsigned char note = 0, instrument, command;
        if (period)
        {
            int findNote;
            int offset = M_MAX_INT;
            
            for (findNote = 0; findNote < 96; ++findNote)
            {
                if (abs(period - (sPeriodTable[0][findNote % 12] >> (findNote / 12))) < offset)
                {
                    note = findNote + 1;
                    offset = abs(period - (sPeriodTable[0][findNote % 12] >> (findNote / 12)));
                }
            }
        }
        instrument = (srcPtr[0] & 0xf0) | ((srcPtr[2] & 0xf0) >> 4);
        command = srcPtr[2] & 0x0f;
        destPtr->mNote = note;
        destPtr->mInstrNum = instrument;
        destPtr->mCommand = command;
        srcPtr += 4;
        destPtr++;
    }

    // Load samples
    unsigned char *modInstr = &mInfo[MOD_INSTROFFSET];
    for (unsigned i = 0; i < MOD_INSTRUMENTS; ++i)
    {
        ModInstrument instr;
        memoryUse += sizeof instr;
        
        int length, repeat, end;
        bool looped = false;
        
        length = ((modInstr[22] << 8) | (modInstr[23])) << 1;
        repeat = ((modInstr[26] << 8) | (modInstr[27])) << 1;
        end = ((modInstr[28] << 8) | (modInstr[29])) << 1;
        instr.mFineTune = modInstr[24];
        instr.mVolume = modInstr[25];
        if (length)
        {
            if (end > 2)
            {
                looped = true;
                end += repeat;
                if (end > length) end = length;
            }
            else
                end = length;
            
            instr.mSound = new Sound();
            instr.mSound->setSize(length);
            memoryUse += instr.mSound->getMemoryUse();
            source.read(instr.mSound->getStart(), length);
            if (looped)
                instr.mSound->setLoop(repeat, end);
        }
        
        mInstruments.push_back(instr);
        modInstr += 30;
    }
    
    setMemoryUse(memoryUse);
    mLoaded = true;
}

void Mod::release()
{
    stop();
    
    mLoaded = false;
    
    mTracks.clear();
    mInstruments.clear();
    
    mInfo.reset();
    mPatterns.reset();
}

void Mod::play(unsigned position)
{
    if (!mLoaded)
        return;
    
    stop();
    
    if (position >= mLength)
        position = 0;
    
    mPos = position;
    mLine = 0;
    mTickCount = 0;
    mTickTempo = 6;
    mPatternDelay = 0;
    setBpmTempo(125);
    
    setNumChannels(mNumChannels);
    
    for (unsigned i = 0; i < mNumChannels; ++i)
    {
        ModTrack* tptr = &mTracks[i];
        Channel* chptr = mChannels[i];
        
        chptr->setIntPanning(Song::sPanningTable[i & 3]);
        memset(tptr, 0, sizeof(ModInstrument));
        tptr->mInstr = &mInstruments[0];
    }
    
    mPlaying = true;
    if (mAudio)
        mAudio->addSong(this);
}

void Mod::updatePlayer()
{
    // Set new notes or do something else?
    if ((!mTickCount) && (!mPatternDelay))
    {
        ModNote* notePtr;
        unsigned char* order = &mInfo[MOD_ORDEROFFSET];
        
        notePtr = (ModNote*)(mPatterns.getPtr() + order[mPos] * mPatternLength + mLine * mNumChannels * sizeof(ModNote));
        mPatternBreak = false;
        for (unsigned i = 0; i < mNumChannels; ++i)
        {
            ModTrack* tptr = &mTracks[i];
            Channel* chptr = mChannels[i];
            
            tptr->mNewNote = 0;
            tptr->mRetrigCount = 0;
            
            // Get note (if any)
            if (notePtr->mNote)
            {
                tptr->mNote = notePtr->mNote - 1;
                tptr->mNewNote = 1;
            }
            
            // Get effect, effect data etc.
            tptr->mEffect = notePtr->mCommand;
            tptr->mEffectData = notePtr->mData;
            tptr->mNybble1 = notePtr->mData >> 4;
            tptr->mNybble2 = notePtr->mData & 0xf;
            tptr->mNewInstrNum = notePtr->mInstrNum;
            
            // Set sampleoffset here
            if (tptr->mNewInstrNum)
                tptr->mUseSoundOffset = false;
            if (tptr->mEffect == 0x9)
            {
                if (tptr->mEffectData) tptr->mSoundOffset = tptr->mEffectData;
                tptr->mUseSoundOffset = true;
            }
            
            // Start new note if there is one; but check for notedelay
            if ((tptr->mEffect != 0xe) || (tptr->mNybble1 != 0xd) || (tptr->mNybble2 == 0))
            {
                if (tptr->mNewNote) startNewNote(tptr, chptr);
                if (tptr->mNewInstrNum)
                {
                    tptr->mInstrNum = tptr->mNewInstrNum - 1;
                    tptr->mInstr = &mInstruments[tptr->mInstrNum];
                    tptr->mVolume = tptr->mInstr->mVolume;
                    chptr->setIntVolume(tptr->mVolume);
                }
            }
            
            // Reset period if not vibrato or toneportamento
            if ((tptr->mEffect < 0x3) || (tptr->mEffect > 0x6))
            {
                tptr->mPeriod = tptr->mBasePeriod;
            }
            
            // Reset volume if not tremolo
            if (tptr->mEffect != 0x7)
                chptr->setIntVolume(tptr->mVolume);
            
            switch (tptr->mEffect)
            {
                case 0x0:
                break;
                
                // Set portamento speed up
                case 0x1:
                if (tptr->mEffectData) tptr->mPortaSpeedUp = tptr->mEffectData;
                break;
                
                // Set portamento speed down
                case 0x2:
                if (tptr->mEffectData) tptr->mPortaSpeedDown = tptr->mEffectData;
                break;
                
                // Set TP. speed
                case 0x3:
                if (tptr->mEffectData) tptr->mTonePortaSpeed = tptr->mEffectData;
                break;
                
                // Set vibrato
                case 0x4:
                if (tptr->mNybble1) tptr->mVibratoSpeed = tptr->mNybble1;
                if (tptr->mNybble2) tptr->mVibratoDepth = tptr->mNybble2;
                break;
                
                // Set tremolo
                case 0x7:
                if (tptr->mNybble1) tptr->mTremoloSpeed = tptr->mNybble1;
                if (tptr->mNybble2) tptr->mTremoloDepth = tptr->mNybble2;
                break;
                
                // Set panning
                case 0x8:
                chptr->setIntPanning(tptr->mEffectData);
                break;
                
                // Volume slide speed set
                case 0x5:
                case 0x6:
                case 0xa:
                if (tptr->mEffectData)
                {
                    tptr->mVolSpeedUp = tptr->mNybble1;
                    tptr->mVolSpeedDown = tptr->mNybble2;
                }
                break;
                
                // Pos. jump
                case 0xb:
                mLine = 63;
                mPos = tptr->mEffectData - 1;
                break;
                
                // Set volume
                case 0xc:
                tptr->mVolume = tptr->mEffectData;
                chptr->setIntVolume(tptr->mVolume);
                break;
                
                // Pattern break
                case 0xd:
                if (!mPatternBreak)
                {
                    mPatternBreak = true;
                    mLine = tptr->mNybble1 * 10 + tptr->mNybble2 - 1;
                    mPos++;
                }
                break;
                
                // Extended command
                case 0xe:
                extendedCommand(tptr, chptr);
                break;
                
                // Set tempo
                case 0xf:
                if (!tptr->mEffectData)
                {
                    mPlaying = false;
                    break;
                }
                if (tptr->mEffectData < 32) mTickTempo = tptr->mEffectData;
                else setBpmTempo(tptr->mEffectData);
                break;
            }
            if (tptr->mPeriod)
                chptr->setIntFrequency(AMIGA_CLOCK / tptr->mPeriod);
            
            notePtr++;
        }
    }
    
    if (mTickCount)
    {
        // If tick isn't 0, update continuous effects
        for (unsigned i = 0; i < mNumChannels; ++i)
        {
            Channel* chptr = mChannels[i];
            ModTrack* tptr = &mTracks[i];
            
            switch (tptr->mEffect)
            {
                // Arpeggio
                case 0x0:
                {
                    if (tptr->mEffectData)
                    {
                        char phase = mTickCount % 3;
                        switch (phase)
                        {
                            unsigned char arpNote;
                            
                            case 0:
                            tptr->mPeriod = tptr->mBasePeriod;
                            break;
                            
                            case 1:
                            arpNote = tptr->mNote + tptr->mNybble1;
                            if (arpNote > 95) arpNote = 95;
                            tptr->mPeriod = sPeriodTable[tptr->mFineTune][arpNote % 12] >> (arpNote / 12);
                            break;
                            
                            case 2:
                            arpNote = tptr->mNote + tptr->mNybble2;
                            if (arpNote > 95) arpNote = 95;
                            tptr->mPeriod = sPeriodTable[tptr->mFineTune][arpNote % 12] >> (arpNote / 12);
                            break;
                        }
                    }
                }
                break;
                
                // Portamento up
                case 0x1:
                tptr->mBasePeriod -= tptr->mPortaSpeedUp;
                if (tptr->mBasePeriod < 27) tptr->mBasePeriod = 27;
                tptr->mPeriod = tptr->mBasePeriod;
                break;
                
                // Portamento down
                case 0x2:
                tptr->mBasePeriod += tptr->mPortaSpeedDown;
                if (tptr->mBasePeriod > 7256) tptr->mBasePeriod = 7256;
                tptr->mPeriod = tptr->mBasePeriod;
                break;
                
                // Toneportamento
                case 0x3:
                tonePortamento(tptr, chptr);
                break;
                
                // Vibrato
                case 0x4:
                vibrato(tptr, chptr);
                break;
                
                // Toneportamento + volslide
                case 0x5:
                tonePortamento(tptr, chptr);
                volumeSlide(tptr, chptr);
                break;
                
                // Vibrato + volslide
                case 0x6:
                vibrato(tptr, chptr);
                volumeSlide(tptr, chptr);
                break;
                
                // Tremolo
                case 0x7:
                tptr->mTremoloPhase += tptr->mTremoloSpeed * 4;
                chptr->setIntVolume(tptr->mVolume + ((Song::sVibratoTable[tptr->mTremoloType & 3][tptr->mTremoloPhase] * tptr->mTremoloDepth) >> 4));
                break;
                
                // Volume slide
                case 0xa:
                volumeSlide(tptr, chptr);
                break;
                
                // Extended command
                case 0xe:
                extendedCommand(tptr, chptr);
                break;
            }
            if (tptr->mPeriod)
                chptr->setIntFrequency(AMIGA_CLOCK / tptr->mPeriod);
        }
    }
    
    // Advance song
    mTickCount++;
    if (mTickCount >= mTickTempo)
    {
        mTickCount = 0;
        if (mPatternDelay)
            mPatternDelay--;
        if (!mPatternDelay)
        {
            mLine++;
            if (mLine >= 64)
            {
                mLine = 0;
                mPos++;
            }
            if (mPos >= mLength) 
                mPos = 0;
        }
    }
}

void Mod::startNewNote(ModTrack* tptr, Channel* chptr)
{
    // Change instrument if necessary
    if (tptr->mNewInstrNum)
    {
        tptr->mInstrNum = tptr->mNewInstrNum - 1;
        tptr->mInstr = &mInstruments[tptr->mInstrNum];
    }

    tptr->mFineTune = tptr->mInstr->mFineTune;
    if (!(tptr->mVibratoType & 4)) tptr->mVibratoPhase = 0;
    if (!(tptr->mTremoloType & 4)) tptr->mTremoloPhase = 0;
    if ((tptr->mEffect == 0x3) || (tptr->mEffect == 0x5))
    {
        // Toneportamento
        tptr->mTargetPeriod = sPeriodTable[tptr->mFineTune][tptr->mNote % 12] >> (tptr->mNote / 12);
        tptr->mTonePortamento = true;
    }
    else
    {
        // Normal note start
        tptr->mBasePeriod = sPeriodTable[tptr->mFineTune][tptr->mNote % 12] >> (tptr->mNote / 12);
        tptr->mPeriod = tptr->mBasePeriod;
        tptr->mTonePortamento = false;
        if (tptr->mInstr->mSound)
        {
            chptr->playLockless(tptr->mInstr->mSound);
            
            if (tptr->mUseSoundOffset)
            {
                signed char* newPos = tptr->mInstr->mSound->getStart() + (tptr->mSoundOffset << 8);
                if (newPos >= tptr->mInstr->mSound->getEnd())
                {
                    if (tptr->mInstr->mSound->isLooped())
                        chptr->setPlayPositionLockless(tptr->mInstr->mSound->getRepeat());
                    else
                        chptr->stopLockless();
                }
                else
                    chptr->setPlayPositionLockless(newPos);
            }
        }
    }
}

void Mod::extendedCommand(ModTrack* tptr, Channel* chptr)
{
    switch(tptr->mNybble1)
    {
        // Fine porta up
        case 0x1:
        if (!mTickCount)
        {
            if (tptr->mNybble2) tptr->mPortaSpeedUp = tptr->mNybble2;
            tptr->mBasePeriod -= tptr->mPortaSpeedUp;
            if (tptr->mBasePeriod < 27) tptr->mBasePeriod = 27;
        }
        break;
        
        // Fine porta down
        case 0x2:
        if (!mTickCount)
        {
            if (tptr->mNybble2) tptr->mPortaSpeedDown = tptr->mNybble2;
            tptr->mBasePeriod += tptr->mPortaSpeedDown;
            if (tptr->mBasePeriod > 7256) tptr->mBasePeriod = 7256;
        }
        break;
        
        // Set glissando
        case 0x3:
        if (!mTickCount) tptr->mGlissando = tptr->mNybble2;
        break;
        
        // Set vibrato waveform
        case 0x4:
        if (!mTickCount)
        {
            tptr->mVibratoType = Song::sVibratoTypeTable[tptr->mNybble2 & 3];
            tptr->mVibratoType |= tptr->mNybble2 & 4;
        }
        break;
        
        // Set finetune
        case 0x5:
        if ((!mTickCount) && (tptr->mNewNote))
        {
            tptr->mFineTune = (tptr->mNybble2 - 8) & 15;
            tptr->mBasePeriod = sPeriodTable[tptr->mFineTune][tptr->mNote % 12] >> (tptr->mNote / 12);
            tptr->mPeriod = tptr->mBasePeriod;
        }
        break;
        
        // Patternloop
        case 0x6:
        if (!mTickCount)
        {
            if (!tptr->mNybble2) tptr->mPatternLoopLine = mLine;
            else
            {
                if (!tptr->mPatternLoopCount)
                {
                    tptr->mPatternLoopCount = tptr->mNybble2;
                    mLine = tptr->mPatternLoopLine - 1;
                }
                else
                {
                    tptr->mPatternLoopCount--;
                    if (tptr->mPatternLoopCount) mLine = tptr->mPatternLoopLine - 1;
                }
            }
        }
        break;
        
        // Set tremolo waveform
        case 0x7:
        if (!mTickCount)
        {
            tptr->mTremoloType = Song::sVibratoTypeTable[tptr->mNybble2 & 3];
            tptr->mTremoloType |= tptr->mNybble2 & 4;
        }
        break;
        
        // Set panning (undocumented)
        case 0x8:
        chptr->setIntPanning((tptr->mNybble2 << 4) | tptr->mNybble2);
        break;
        
        // Retrig
        case 0x9:
        if (tptr->mNybble2)
        {
            if ((!tptr->mNewNote) && (!mTickCount))
            {
                tptr->mRetrigCount = mTickTempo;
            }
            if (tptr->mRetrigCount >= tptr->mNybble2)
            {
                tptr->mRetrigCount = 0;
                startNewNote(tptr, chptr);
            }
        }
        tptr->mRetrigCount++;
        break;
        
        // Notedelay
        case 0xd:
        // Don't start on tick 0 or if there's no note 
        if ((!mTickCount) || (!tptr->mNewNote)) break;
        if (mTickCount == tptr->mNybble2)
        {
            startNewNote(tptr, chptr);
            if (tptr->mNewInstrNum)
            {
                tptr->mVolume = tptr->mInstr->mVolume;
                chptr->setIntVolume(tptr->mVolume);
            }
        }
        break;
        
        // Cut note
        case 0xc:
        if (mTickCount == tptr->mNybble2)
        {
            tptr->mVolume = 0;
            chptr->setIntVolume(0);
        }
        break;
        
        // Fine volslide up
        case 0xa:
        if (!mTickCount)
        {
            if (tptr->mNybble2) tptr->mVolSpeedUp = tptr->mNybble2;
            tptr->mVolume += tptr->mVolSpeedUp;
            if (tptr->mVolume > 64) tptr->mVolume = 64;
            chptr->setIntVolume(tptr->mVolume);
        }
        break;
        
        // Fine volslide down
        case 0xb:
        if (!mTickCount)
        {
            if (tptr->mNybble2) tptr->mVolSpeedDown = tptr->mNybble2;
            tptr->mVolume -= tptr->mVolSpeedDown;
            if (tptr->mVolume < 0) tptr->mVolume = 0;
            chptr->setIntVolume(tptr->mVolume);
        }
        break;
        
        // Patterndelay
        case 0xe:
        if (!mTickCount)
            mPatternDelay = tptr->mNybble2 + 1;
        break;
    }
}

void Mod::tonePortamento(ModTrack* tptr, Channel* chptr)
{
    if (tptr->mTonePortamento)
    {
        if (tptr->mBasePeriod < tptr->mTargetPeriod)
        {
            tptr->mBasePeriod += tptr->mTonePortaSpeed;
            if (tptr->mBasePeriod >= tptr->mTargetPeriod)
            {
                tptr->mBasePeriod = tptr->mTargetPeriod;
                tptr->mTonePortamento = false;
            }
        }
        if (tptr->mBasePeriod > tptr->mTargetPeriod)
        {
            tptr->mBasePeriod -= tptr->mTonePortaSpeed;
            if (tptr->mBasePeriod <= tptr->mTargetPeriod)
            {
                tptr->mBasePeriod = tptr->mTargetPeriod;
                tptr->mTonePortamento = false;
            }
        }
        tptr->mPeriod = tptr->mBasePeriod;
        if (tptr->mGlissando)
        {
            int offset = M_MAX_INT;
            int sc;
            short bestPeriod = 0;
            
            for (sc = 0; sc < 96; sc++)
            {
                int newOffset = abs(tptr->mPeriod - (sPeriodTable[tptr->mFineTune][sc % 12] >> (sc / 12)));
                if (newOffset < offset)
                {
                    bestPeriod = sPeriodTable[tptr->mFineTune][sc % 12] >> (sc / 12);
                    offset = newOffset;
                }
            }
            tptr->mPeriod = bestPeriod;
        }
    }
}

void Mod::vibrato(ModTrack* tptr, Channel* chptr)
{
    tptr->mVibratoPhase += tptr->mVibratoSpeed * 4;
    tptr->mPeriod = tptr->mBasePeriod + ((Song::sVibratoTable[tptr->mVibratoType & 3][tptr->mVibratoPhase] * tptr->mVibratoDepth) >> 5);
    if (tptr->mPeriod < 27) tptr->mPeriod = 27;
    if (tptr->mPeriod > 7256) tptr->mPeriod = 7256;
}

void Mod::volumeSlide(ModTrack* tptr, Channel* chptr)
{
    if (tptr->mVolSpeedUp)
        tptr->mVolume += tptr->mVolSpeedUp;
    if (tptr->mVolume < 0) tptr->mVolume = 0;
    if (tptr->mVolSpeedDown)
        tptr->mVolume -= tptr->mVolSpeedDown;
    if (tptr->mVolume > 64) tptr->mVolume = 64;
    chptr->setIntVolume(tptr->mVolume);
}
