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
#include "Profiler.h"
#include "Sound.h"
#include "XM.h"

#include <cstring>

#include "DebugNew.h"

static const int ENV_ON = 1;
static const int ENV_SUSTAIN = 2;
static const int ENV_LOOP = 4;
static const int SMP_LOOP = 1;
static const int SMP_PINGPONGLOOP = 2;
static const int SMP_16BIT = 16;
static const int MAX_CHANNELS = 32;
static const int MAX_PATTERNS = 256;
static const int MAX_INSTRUMENTS = 128;
static const int MAX_SAMPLES = 16;
static const int KEYOFF = 0x61;

const unsigned XM::sLinearFreqTable[] =
{
    535232, 534749, 534266, 533784, 533303, 532822, 532341, 531861, 531381, 530902,
    530423, 529944, 529466, 528988, 528511, 528034, 527558, 527082, 526607, 526131,
    525657, 525183, 524709, 524236, 523763, 523290, 522818, 522346, 521875, 521404,
    520934, 520464, 519994, 519525, 519057, 518588, 518121, 517653, 517186, 516720,
    516253, 515788, 515322, 514858, 514393, 513929, 513465, 513002, 512539, 512077,
    511615, 511154, 510692, 510232, 509771, 509312, 508852, 508393, 507934, 507476,
    507018, 506561, 506104, 505647, 505191, 504735, 504280, 503825, 503371, 502917,
    502463, 502010, 501557, 501104, 500652, 500201, 499749, 499298, 498848, 498398,
    497948, 497499, 497050, 496602, 496154, 495706, 495259, 494812, 494366, 493920,
    493474, 493029, 492585, 492140, 491696, 491253, 490809, 490367, 489924, 489482,
    489041, 488600, 488159, 487718, 487278, 486839, 486400, 485961, 485522, 485084,
    484647, 484210, 483773, 483336, 482900, 482465, 482029, 481595, 481160, 480726,
    480292, 479859, 479426, 478994, 478562, 478130, 477699, 477268, 476837, 476407,
    475977, 475548, 475119, 474690, 474262, 473834, 473407, 472979, 472553, 472126,
    471701, 471275, 470850, 470425, 470001, 469577, 469153, 468730, 468307, 467884,
    467462, 467041, 466619, 466198, 465778, 465358, 464938, 464518, 464099, 463681,
    463262, 462844, 462427, 462010, 461593, 461177, 460760, 460345, 459930, 459515,
    459100, 458686, 458272, 457859, 457446, 457033, 456621, 456209, 455797, 455386,
    454975, 454565, 454155, 453745, 453336, 452927, 452518, 452110, 451702, 451294,
    450887, 450481, 450074, 449668, 449262, 448857, 448452, 448048, 447644, 447240,
    446836, 446433, 446030, 445628, 445226, 444824, 444423, 444022, 443622, 443221,
    442821, 442422, 442023, 441624, 441226, 440828, 440430, 440033, 439636, 439239,
    438843, 438447, 438051, 437656, 437261, 436867, 436473, 436079, 435686, 435293,
    434900, 434508, 434116, 433724, 433333, 432942, 432551, 432161, 431771, 431382,
    430992, 430604, 430215, 429827, 429439, 429052, 428665, 428278, 427892, 427506,
    427120, 426735, 426350, 425965, 425581, 425197, 424813, 424430, 424047, 423665,
    423283, 422901, 422519, 422138, 421757, 421377, 420997, 420617, 420237, 419858,
    419479, 419101, 418723, 418345, 417968, 417591, 417214, 416838, 416462, 416086,
    415711, 415336, 414961, 414586, 414212, 413839, 413465, 413092, 412720, 412347,
    411975, 411604, 411232, 410862, 410491, 410121, 409751, 409381, 409012, 408643,
    408274, 407906, 407538, 407170, 406803, 406436, 406069, 405703, 405337, 404971,
    404606, 404241, 403876, 403512, 403148, 402784, 402421, 402058, 401695, 401333,
    400970, 400609, 400247, 399886, 399525, 399165, 398805, 398445, 398086, 397727,
    397368, 397009, 396651, 396293, 395936, 395579, 395222, 394865, 394509, 394153,
    393798, 393442, 393087, 392733, 392378, 392024, 391671, 391317, 390964, 390612,
    390259, 389907, 389556, 389204, 388853, 388502, 388152, 387802, 387452, 387102,
    386753, 386404, 386056, 385707, 385359, 385012, 384664, 384317, 383971, 383624,
    383278, 382932, 382587, 382242, 381897, 381552, 381208, 380864, 380521, 380177,
    379834, 379492, 379149, 378807, 378466, 378124, 377783, 377442, 377102, 376762,
    376422, 376082, 375743, 375404, 375065, 374727, 374389, 374051, 373714, 373377,
    373040, 372703, 372367, 372031, 371695, 371360, 371025, 370690, 370356, 370022,
    369688, 369355, 369021, 368688, 368356, 368023, 367691, 367360, 367028, 366697,
    366366, 366036, 365706, 365376, 365046, 364717, 364388, 364059, 363731, 363403,
    363075, 362747, 362420, 362093, 361766, 361440, 361114, 360788, 360463, 360137,
    359813, 359488, 359164, 358840, 358516, 358193, 357869, 357547, 357224, 356902,
    356580, 356258, 355937, 355616, 355295, 354974, 354654, 354334, 354014, 353695,
    353376, 353057, 352739, 352420, 352103, 351785, 351468, 351150, 350834, 350517,
    350201, 349885, 349569, 349254, 348939, 348624, 348310, 347995, 347682, 347368,
    347055, 346741, 346429, 346116, 345804, 345492, 345180, 344869, 344558, 344247,
    343936, 343626, 343316, 343006, 342697, 342388, 342079, 341770, 341462, 341154,
    340846, 340539, 340231, 339924, 339618, 339311, 339005, 338700, 338394, 338089,
    337784, 337479, 337175, 336870, 336566, 336263, 335959, 335656, 335354, 335051,
    334749, 334447, 334145, 333844, 333542, 333242, 332941, 332641, 332341, 332041,
    331741, 331442, 331143, 330844, 330546, 330247, 329950, 329652, 329355, 329057,
    328761, 328464, 328168, 327872, 327576, 327280, 326985, 326690, 326395, 326101,
    325807, 325513, 325219, 324926, 324633, 324340, 324047, 323755, 323463, 323171,
    322879, 322588, 322297, 322006, 321716, 321426, 321136, 320846, 320557, 320267,
    319978, 319690, 319401, 319113, 318825, 318538, 318250, 317963, 317676, 317390,
    317103, 316817, 316532, 316246, 315961, 315676, 315391, 315106, 314822, 314538,
    314254, 313971, 313688, 313405, 313122, 312839, 312557, 312275, 311994, 311712,
    311431, 311150, 310869, 310589, 310309, 310029, 309749, 309470, 309190, 308911,
    308633, 308354, 308076, 307798, 307521, 307243, 306966, 306689, 306412, 306136,
    305860, 305584, 305308, 305033, 304758, 304483, 304208, 303934, 303659, 303385,
    303112, 302838, 302565, 302292, 302019, 301747, 301475, 301203, 300931, 300660,
    300388, 300117, 299847, 299576, 299306, 299036, 298766, 298497, 298227, 297958,
    297689, 297421, 297153, 296884, 296617, 296349, 296082, 295815, 295548, 295281,
    295015, 294749, 294483, 294217, 293952, 293686, 293421, 293157, 292892, 292628,
    292364, 292100, 291837, 291574, 291311, 291048, 290785, 290523, 290261, 289999,
    289737, 289476, 289215, 288954, 288693, 288433, 288173, 287913, 287653, 287393,
    287134, 286875, 286616, 286358, 286099, 285841, 285583, 285326, 285068, 284811,
    284554, 284298, 284041, 283785, 283529, 283273, 283017, 282762, 282507, 282252,
    281998, 281743, 281489, 281235, 280981, 280728, 280475, 280222, 279969, 279716,
    279464, 279212, 278960, 278708, 278457, 278206, 277955, 277704, 277453, 277203,
    276953, 276703, 276453, 276204, 275955, 275706, 275457, 275209, 274960, 274712,
    274465, 274217, 273970, 273722, 273476, 273229, 272982, 272736, 272490, 272244,
    271999, 271753, 271508, 271263, 271018, 270774, 270530, 270286, 270042, 269798,
    269555, 269312, 269069, 268826, 268583, 268341, 268099, 267857
};

const unsigned short XM::sAmigaFreqTable[] =
{
    907, 900, 894, 887, 881, 875, 868, 862, 856, 850, 844, 838, 832, 826, 820, 814,
    808, 802, 796, 791, 785, 779, 774, 768, 762, 757, 752, 746, 741, 736, 730, 725,
    720, 715, 709, 704, 699, 694, 689, 684, 678, 675, 670, 665, 660, 655, 651, 646,
    640, 636, 632, 628, 623, 619, 614, 610, 604, 601, 597, 592, 588, 584, 580, 575,
    570, 567, 563, 559, 555, 551, 547, 543, 538, 535, 532, 528, 524, 520, 516, 513,
    508, 505, 502, 498, 494, 491, 487, 484, 480, 477, 474, 470, 467, 463, 460, 457,
    453, 450, 447, 443, 440, 437, 434, 431, 428
};

const signed char XM::sRetrigAddTable[] =
{
    0, -1, -2, -4, -8, -16, 0, 0, 0, +1, +2, +4, +8, +16, 0, 0
};

const signed char XM::sRetrigMulTable[] =
{
    0, 0, 0, 0, 0, 0, 11, 8, 0, 0, 0, 0, 0, 0, 24, 32
};

const XMNote XM::sEmptyNote = {0, 0, 0, 0, 0};

XM::XM(Audio* audio, const std::string& name) :
    Song(audio, name),
    mPos(0)
{
}

XM::~XM()
{
    release();
}

void XM::load(Deserializer& source, ResourceCache* cache)
{
    PROFILE(XM_Load);
    
    release();
    
    unsigned pos;
    unsigned memoryUse = 0;
    
    // Read in the identification
    memset(&mXMId, 0, sizeof mXMId);
    source.read(&mXMId.mId, 17);
    source.read(&mXMId.mModName, 20);
    mXMId.mIdByte = source.readUByte();
    source.read(&mXMId.mTrackerName, 20);
    mXMId.mVersion = source.readUShort();
    memoryUse += sizeof mXMId;
    
    // Check that it's an XM and the version is correct
    if ((mXMId.mIdByte != 0x1a) || (memcmp("Extended Module:", mXMId.mId, 16)))
        EXCEPTION("Could not determine XM format from " + source.getName());
    
    mXMId.mIdByte = 0x0; // Serves as the songmName endzero from now on 
    if (mXMId.mVersion < 0x103)
        EXCEPTION("Unsupported XM data version in " + source.getName());
    
    // Read in the header & orderlist
    pos = source.getPosition();
    mXMHeader.mHeaderSize = source.readUInt();
    mXMHeader.mSongLength = source.readUShort();
    mXMHeader.mRestartPos = source.readUShort();
    mXMHeader.mNumChannels = source.readUShort();
    mXMHeader.mNumPatterns = source.readUShort();
    mXMHeader.mNumInstruments = source.readUShort();
    mXMHeader.mUseLinear = source.readUShort();
    mXMHeader.mDefaultTickTempo = source.readUShort();
    mXMHeader.mDefaultBpmTempo = source.readUShort();
    source.read(mXMHeader.mOrder, 256);
    memoryUse += sizeof mXMHeader;
    
    // Create tracks
    mTracks.resize(mXMHeader.mNumChannels);
    
    // Skip to next section
    source.seek(pos + mXMHeader.mHeaderSize);
    
    // Load the patterns
    mPatterns.resize(mXMHeader.mNumPatterns);
    XMPackedPattern loadPattern;
    for (unsigned i = 0; i < mXMHeader.mNumPatterns; ++i)
    {
        // Load pattern header
        pos = source.getPosition();
        loadPattern.mHeaderSize = source.readUInt();
        loadPattern.mPackingType = source.readUByte();
        loadPattern.mRows = source.readUShort();
        loadPattern.mPackSize = source.readUShort();

        // Skip to next section
        source.seek(pos + loadPattern.mHeaderSize);
        
        // Allocate memory for unpacked pattern & clear
        mPatterns[i].mRows = loadPattern.mRows;
        unsigned patternSize = 5 * loadPattern.mRows * mXMHeader.mNumChannels;
        mPatterns[i].mData = new unsigned char[patternSize];
        memset(mPatterns[i].mData.getPtr(), 0, patternSize);
        memoryUse += patternSize;
        
        if (loadPattern.mPackSize)
        {
            SharedArrayPtr<unsigned char> packBuffer(new unsigned char[loadPattern.mPackSize]);
            source.read(packBuffer.getPtr(), loadPattern.mPackSize);
            
            unsigned char* packPtr = packBuffer.getPtr();
            unsigned char* unpackPtr = mPatterns[i].mData.getPtr();
            unsigned packLeft = loadPattern.mPackSize;
            
            while (packLeft)
            {
                unsigned char control = *packPtr++;
                --packLeft;
                // Packed? 
                if (control & 0x80)
                {
                    // Note? 
                    if (control & 0x01)
                    {
                        *unpackPtr++ = *packPtr++;
                        --packLeft;
                    }
                    else ++unpackPtr;
                    // Instrument? 
                    if (control & 0x02)
                    {
                        *unpackPtr++ = *packPtr++;
                        --packLeft;
                    }
                    else ++unpackPtr;
                    // Volume column? 
                    if (control & 0x04)
                    {
                        *unpackPtr++ = *packPtr++;
                        --packLeft;
                    }
                    else ++unpackPtr;
                    // Effect? 
                    if (control & 0x08)
                    {
                        *unpackPtr++ = *packPtr++;
                        --packLeft;
                    }
                    else ++unpackPtr;
                    // Effect parameter?
                    if (control & 0x10)
                    {
                        *unpackPtr++ = *packPtr++;
                        --packLeft;
                    }
                    else ++unpackPtr;
                }
                else
                {
                    *unpackPtr++ = control; // Note
                    *unpackPtr++ = *packPtr++; // Instrument
                    *unpackPtr++ = *packPtr++; // Volume c.
                    *unpackPtr++ = *packPtr++; // Effect
                    *unpackPtr++ = *packPtr++; // Effect p.
                    packLeft -= 4;
                }
            }
        }
    }
    
    // Load instruments
    mInstruments.resize(mXMHeader.mNumInstruments);
    memoryUse += mXMHeader.mNumInstruments * sizeof(XMInstrument);
    
    for (unsigned i = 0; i < mXMHeader.mNumInstruments; ++i)
    {
        XMInstrument* instrPtr = &mInstruments[i];
        
        // Read the part common to all instruments
        pos = source.getPosition();
        instrPtr->mHeaderSize = source.readUInt();
        source.read(instrPtr->mName, 22);
        instrPtr->mType = source.readUByte();
        instrPtr->mNumSamples = source.readUShort();
        
        if (instrPtr->mNumSamples)
        {
            instrPtr->mXMSamples.resize(instrPtr->mNumSamples);
            instrPtr->mSounds.resize(instrPtr->mNumSamples);
            
            int s;
            
            // There are samples; read the rest in
            instrPtr->mSoundHeaderSize = source.readUInt();
            source.read(&instrPtr->mSampleTable, 96);
            for (s = 0; s < 12; ++s)
            {
                instrPtr->mVolumeEnv[s].mX = source.readUShort();
                instrPtr->mVolumeEnv[s].mY = source.readUShort();
            }
            for (s = 0; s < 12; ++s)
            {
                instrPtr->mPanningEnv[s].mX = source.readUShort();
                instrPtr->mPanningEnv[s].mY = source.readUShort();
            }
            instrPtr->mVolumeEnvPoints = source.readUByte();
            instrPtr->mPanningEnvPoints = source.readUByte();
            instrPtr->mVolumeSustainPoint = source.readUByte();
            instrPtr->mVolumeLoopStart = source.readUByte();
            instrPtr->mVolumeLoopEnd = source.readUByte();
            instrPtr->mPanningSustainPoint = source.readUByte();
            instrPtr->mPanningLoopStart = source.readUByte();
            instrPtr->mPanningLoopEnd = source.readUByte();
            instrPtr->mVolumeEnvFlags = source.readUByte();
            instrPtr->mPanningEnvFlags = source.readUByte();
            instrPtr->mVibratoType = source.readUByte();
            instrPtr->mVibratoSweep = source.readUByte();
            instrPtr->mVibratoDepth = source.readUByte();
            instrPtr->mVibratoRate = source.readUByte();
            instrPtr->mFadeOut = source.readUShort();
            instrPtr->mReserved = source.readUShort();
            
            // Skip over extra data in instr. header
            source.seek(pos + instrPtr->mHeaderSize);
            
            // Precalculate envelopes
            if (instrPtr->mVolumeEnvFlags & ENV_ON)
            {
                for (s = 0; s < instrPtr->mVolumeEnvPoints; ++s)
                {
                    // Paranoid check
                    if (instrPtr->mVolumeEnv[s].mX > 324)
                        instrPtr->mVolumeEnv[s].mX = 324;
                }
                for (s = 0; s < instrPtr->mVolumeEnvPoints - 1; ++s)
                {
                    int x, y, dx, dy;
                    y = instrPtr->mVolumeEnv[s].mY;
                    dx = instrPtr->mVolumeEnv[s+1].mX - instrPtr->mVolumeEnv[s].mX;
                    dy = instrPtr->mVolumeEnv[s+1].mY - instrPtr->mVolumeEnv[s].mY;
                    if (dx)
                    {
                        for (x = 0; x < dx; ++x)
                        {
                            instrPtr->mVolumeEnvLookup[x + instrPtr->mVolumeEnv[s].mX] =
                                y + dy * x / dx;
                        }
                    }
                    if (s == instrPtr->mVolumeEnvPoints - 2)
                    {
                        for (x = instrPtr->mVolumeEnv[s+1].mX; x < 325; x++)
                            instrPtr->mVolumeEnvLookup[x] = (unsigned char)instrPtr->mVolumeEnv[s+1].mY;
                    }
                }
                instrPtr->mVolumeSustainPoint = instrPtr->mVolumeEnv[instrPtr->mVolumeSustainPoint].mX;
                instrPtr->mVolumeLoopStart = instrPtr->mVolumeEnv[instrPtr->mVolumeLoopStart].mX;
                instrPtr->mVolumeLoopEnd = instrPtr->mVolumeEnv[instrPtr->mVolumeLoopEnd].mY;
                // If zero length loop, must deactivate it
                if (instrPtr->mVolumeLoopStart == instrPtr->mVolumeLoopEnd)
                    instrPtr->mVolumeEnvFlags &= ~ENV_LOOP;
            }
            if (instrPtr->mPanningEnvFlags & ENV_ON)
            {
                for (s = 0; s < instrPtr->mPanningEnvPoints; ++s)
                {
                    // Paranoid check
                    if (instrPtr->mPanningEnv[s].mX > 324)
                        instrPtr->mPanningEnv[s].mX = 324;
                }
                for (s = 0; s < instrPtr->mPanningEnvPoints - 1; ++s)
                {
                    int x, y, dx, dy;
                    y = instrPtr->mPanningEnv[s].mY;
                    dx = instrPtr->mPanningEnv[s+1].mX - instrPtr->mPanningEnv[s].mX;
                    dy = instrPtr->mPanningEnv[s+1].mY - instrPtr->mPanningEnv[s].mY;
                    if (dx)
                    {
                        for (x = 0; x < dx; ++x)
                        {
                            instrPtr->mPanningEnvLookup[x + instrPtr->mPanningEnv[s].mX] =
                                y + dy * x / dx;
                        }
                    }
                    if (s == instrPtr->mPanningEnvPoints - 2)
                    {
                        for (x = instrPtr->mPanningEnv[s+1].mX; x < 325; ++x)
                            instrPtr->mPanningEnvLookup[x] = (unsigned char)instrPtr->mPanningEnv[s+1].mY;
                    }
                }
                instrPtr->mPanningSustainPoint = instrPtr->mPanningEnv[instrPtr->mPanningSustainPoint].mX;
                instrPtr->mPanningLoopStart = instrPtr->mPanningEnv[instrPtr->mPanningLoopStart].mX;
                instrPtr->mPanningLoopEnd = instrPtr->mPanningEnv[instrPtr->mPanningLoopEnd].mX;
                // If zero length loop, must deactivate it
                if (instrPtr->mPanningLoopStart == instrPtr->mPanningLoopEnd)
                    instrPtr->mPanningEnvFlags &= ~ENV_LOOP;
            }
            
            // Allocate xmsample & sample structures, but do not read any audio data yet
            for (s = 0; s < instrPtr->mNumSamples; ++s)
            {
                XMSample *xsp = &instrPtr->mXMSamples[s];
                SharedPtr<Sound> sp;
                unsigned reserve;
                
                // Read in sample header
                pos = source.getPosition();
                xsp->mLength = source.readUInt();
                xsp->mLoopStart = source.readUInt();
                xsp->mLoopLength = source.readUInt();
                xsp->mVolume = source.readUByte();
                xsp->mFineTune = source.readUByte();
                xsp->mSoundFlags = source.readUByte();
                xsp->mPanning = source.readUByte();
                xsp->mRelativeNote = source.readUByte();
                xsp->mReserved = source.readUByte();
                source.read(xsp->mName, 22);
                
                // Skip extra data in sample header
                source.seek(pos + instrPtr->mSoundHeaderSize);
                
                // If mLoopLength is zero, loop must be deactivated
                if (!xsp->mLoopLength)
                    xsp->mSoundFlags &= ~(SMP_LOOP | SMP_PINGPONGLOOP);
                
                reserve = xsp->mLength;
                
                // There might be zero length samples
                if (reserve)
                {
                    // Reserve sample
                    if (xsp->mSoundFlags & SMP_PINGPONGLOOP) reserve += xsp->mLoopLength;
                    sp = new Sound();
                    sp->setSize(reserve);
                    memoryUse += sp->getMemoryUse();
                }
                
                instrPtr->mSounds[s] = sp;
            }
            
            // Now load audio data
            for (s = 0; s < instrPtr->mNumSamples; ++s)
            {
                XMSample *xsp = &instrPtr->mXMSamples[s];
                Sound *sp = instrPtr->mSounds[s];
                
                if (sp)
                {
                    // Read sample data (delta values)
                    source.read(sp->getStart(), xsp->mLength);
                    
                    // Convert to normal signed data
                    if (xsp->mSoundFlags & SMP_16BIT)
                    {
                        sp->setFormat(sp->getIntFrequency(), true, false);
                        
                        int cc = xsp->mLength >> 1;
                        unsigned short old = 0;
                        unsigned short *cptr = (unsigned short *)sp->getStart();
                        
                        while (cc--)
                        {
                            *cptr += old;
                            old = *cptr++;
                        }
                    }
                    else
                    {
                        int cc = xsp->mLength;
                        signed char old = 0;
                        signed char *cptr = sp->getStart();
                        
                        while (cc--)
                        {
                            *cptr += old;
                            old = *cptr++;
                        }
                    }
                    
                    // "Unroll" pingpong-loop
                    if (xsp->mSoundFlags & SMP_PINGPONGLOOP)
                    {
                        if (xsp->mSoundFlags & SMP_16BIT)
                        {
                            int uc = xsp->mLoopLength >> 1;
                            short *source = (short *)(sp->getStart() + xsp->mLoopStart + xsp->mLoopLength - 2);
                            short *dest = (short *)(sp->getStart() + xsp->mLoopStart + xsp->mLoopLength);
                            
                            while (uc--) *dest++ = *source--;
                        }
                        else
                        {
                            int uc = xsp->mLoopLength;
                            signed char *source = sp->getStart() + xsp->mLoopStart + xsp->mLoopLength - 1;
                            signed char *dest = sp->getStart() + xsp->mLoopStart + xsp->mLoopLength;
                            
                            while (uc--) *dest++ = *source--;
                        }
                        xsp->mLoopLength <<= 1;
                    }
                    
                    // Set loop
                    if (xsp->mSoundFlags & (SMP_LOOP|SMP_PINGPONGLOOP))
                        sp->setLoop(xsp->mLoopStart, xsp->mLoopStart + xsp->mLoopLength);
                }
            }
        }
        else
        {
            // Header without samples; skip over extra if any
            source.seek(source.getPosition() + instrPtr->mHeaderSize - 29);
        }
    }
    
    setMemoryUse(memoryUse);
    mLoaded = true;
}

void XM::release()
{
    stop();
    
    mLoaded = false;
    
    mTracks.clear();
    mPatterns.clear();
    mInstruments.clear();
}

void XM::play(unsigned position)
{
    if (!mLoaded) return;
    
    stop();
    
    if (position >= mXMHeader.mSongLength)
        position = 0;
    
    mPos = position;
    mLine = 0;
    mTickCount = 0;
    mTickTempo = mXMHeader.mDefaultTickTempo;
    mGlobalVol = 64;
    mGlobalVolSpeedUp = 0;
    mGlobalVolSpeedDown = 0;
    mPatternDelay = 0;
    setBpmTempo(mXMHeader.mDefaultBpmTempo);
    
    setNumChannels(mXMHeader.mNumChannels);
    
    for (unsigned i = 0; i < mXMHeader.mNumChannels; ++i)
    {
        XMTrack* tptr = &mTracks[i];
        Channel* chptr = mChannels[i];
        
        memset(tptr, 0, sizeof(XMTrack));
        tptr->mInstr = &mInstruments[0];
    }
    if (mXMHeader.mUseLinear)
    {
        mLowPeriod = 7743;
        mHighPeriod = 64;
    }
    else
    {
        mLowPeriod = 29024;
        mHighPeriod = 28;
    }
    
    mPlaying = true;
    if (mAudio)
        mAudio->addSong(this);
}

void XM::updatePlayer()
{
    XMPattern *pattPtr = &mPatterns[mXMHeader.mOrder[mPos]];
    
    // Set new notes or do something else?
    if ((!mTickCount) && (!mPatternDelay))
    {
        const XMNote* notePtr = (XMNote *)pattPtr->mData.getPtr();
        
        if (!notePtr) notePtr = &sEmptyNote;
        else notePtr += mXMHeader.mNumChannels * mLine;
        
        mPatternBreak = false;
        for (unsigned i = 0; i < mXMHeader.mNumChannels; ++i)
        {
            XMTrack* tptr = &mTracks[i];
            Channel* chptr = mChannels[i];
            
            tptr->mNewNote = 0;
            tptr->mRetrigCount = 0;
            
            // Get note (if any)
            if (notePtr->mNote)
            {
                tptr->mNote = notePtr->mNote - 1;
                tptr->mNewNote = 1;
            }
            
            // Get effect & data
            tptr->mVolEffect = notePtr->mVolEffect;
            tptr->mEffect = notePtr->mEffect;
            tptr->mEffectData = notePtr->mEffectData;
            tptr->mNybble1 = notePtr->mEffectData >> 4;
            tptr->mNybble2 = notePtr->mEffectData & 0xf;
            tptr->mNewInstrument = notePtr->mInstrument;
            
            // Set sampleoffset here
            if (tptr->mEffect == 0x9)
            {
                if (tptr->mEffectData)
                    tptr->mSoundOffset = tptr->mEffectData;
            }
            
            // Start new note if there is one
            if ((tptr->mEffect != 0xe) || (tptr->mNybble1 != 0xd) || (tptr->mNybble2 == 0))
            {
                if (tptr->mNewNote) startNewNote(tptr, chptr);
                if (tptr->mNewInstrument) changeInstrument(tptr);
            }
            
            // Reset period if not vibrato or toneportamento
            if (((tptr->mEffect < 0x3) || (tptr->mEffect > 0x6)) && (tptr->mVolEffect != 0xb) && (tptr->mVolEffect != 0xf))
                tptr->mPeriod = tptr->mBasePeriod;
            
            // Reset volume if not tremolo / tremor
            if ((tptr->mEffect != 0x7) && (tptr->mEffect != 0x1d))
                tptr->mVolume = tptr->mNoteVolume;
            
            // Now check effects: volume column done first
            switch (tptr->mVolEffect >> 4)
            {
                case 0x0:
                break;
                
                // Set volume
                case 0x1:
                case 0x2:
                case 0x3:
                case 0x4:
                case 0x5:
                // Applies only if there isn't notedelay
                if ((tptr->mEffect != 0xe) || (tptr->mNybble1 != 0xd) || (tptr->mNybble2 == 0))
                {
                    tptr->mNoteVolume = tptr->mVolEffect - 0x10;
                    if (tptr->mNoteVolume > 64) tptr->mNoteVolume = 64;
                    tptr->mVolume = tptr->mNoteVolume;
                }
                break;
                
                // Fine volslide down
                case 0x8:
                tptr->mNoteVolume -= tptr->mVolEffect & 0xf;
                if (tptr->mNoteVolume < 0) tptr->mNoteVolume = 0;
                tptr->mVolume = tptr->mNoteVolume;
                break;
                
                // Fine volslide up
                case 0x9:
                tptr->mNoteVolume += tptr->mVolEffect & 0xf;
                if (tptr->mNoteVolume > 64) tptr->mNoteVolume = 64;
                tptr->mVolume = tptr->mNoteVolume;
                break;
                
                // Set vibrato speed
                case 0xa:
                if (tptr->mVolEffect & 0xf)
                    tptr->mVibratoSpeed = tptr->mVolEffect & 0xf;
                break;
                
                // Vibrato
                case 0xb:
                if (tptr->mVolEffect & 0xf)
                    tptr->mVibratoDepth = tptr->mVolEffect & 0xf;
                break;
                
                // Set panning
                case 0xc:
                // Applies only if there isn't notedelay
                if ((tptr->mEffect != 0xe) || (tptr->mNybble1 != 0xd) || (tptr->mNybble2 == 0))
                    tptr->mNotePanning = (tptr->mVolEffect & 0xf) << 4 | (tptr->mVolEffect & 0xf);
                break;
                
                // Toneportamento
                case 0xf:
                if (tptr->mVolEffect & 0xf)
                    tptr->mTonePortaSpeed = (tptr->mVolEffect & 0xf) << 4;
                break;
            }
            
            // Then the regular effects
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
                tptr->mNotePanning = tptr->mEffectData;
                break;
                
                // ´Set volume slide speed
                case 0x5:
                case 0x6:
                case 0xa:
                if (tptr->mEffectData)
                {
                    tptr->mVolumeSpeedUp = tptr->mNybble1;
                    tptr->mVolumeSpeedDown = tptr->mNybble2;
                }
                break;
                
                // Pos. jump
                case 0xb:
                mLine = pattPtr->mRows - 1;
                mPos = tptr->mEffectData - 1;
                break;
                
                // Set volume
                case 0xc:
                tptr->mNoteVolume = tptr->mEffectData;
                if (tptr->mNoteVolume < 0) tptr->mNoteVolume = 0;
                if (tptr->mNoteVolume > 64) tptr->mNoteVolume = 64;
                tptr->mVolume = tptr->mNoteVolume;
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
                if (tptr->mEffectData < 32) mTickTempo = tptr->mEffectData;
                else setBpmTempo(tptr->mEffectData);
                break;
                
                // Global volume
                case 0x10:
                mGlobalVol = tptr->mEffectData;
                if (mGlobalVol > 64) mGlobalVol = 64;
                break;
                
                // Global volume slide
                case 0x11:
                if (tptr->mEffectData)
                {
                    mGlobalVolSpeedUp = tptr->mNybble1;
                    mGlobalVolSpeedDown = tptr->mNybble2;
                }
                break;
                
                // Keyoff
                case 0x14:
                tptr->mKeyOn = false;
                if (!(tptr->mInstr->mVolumeEnvFlags & ENV_ON))
                {
                    tptr->mNoteVolume = 0;
                    tptr->mVolume = 0;
                }
                break;
                
                // Set envpos
                case 0x15:
                tptr->mVolumeEnvPos = tptr->mEffectData;
                tptr->mPanningEnvPos = tptr->mEffectData;
                break;
                
                // Panning slide
                case 0x19:
                if (tptr->mEffectData)
                {
                    tptr->mPanningSpeedRight = tptr->mNybble1;
                    tptr->mPanningSpeedLeft = tptr->mNybble2;
                }
                break;
                
                // Multi retrig
                case 0x1b:
                if (tptr->mNybble1) tptr->mRetrigVolChange = tptr->mNybble1;
                if (tptr->mNybble2) tptr->mRetrigInterval = tptr->mNybble2;
                if (tptr->mMultiRetrigCount >= tptr->mRetrigInterval)
                {
                    startNewNote(tptr, chptr);
                    tptr->mMultiRetrigCount = 0;
                    if (!sRetrigMulTable[tptr->mRetrigVolChange])
                    {
                        tptr->mNoteVolume += sRetrigAddTable[tptr->mRetrigVolChange];
                        if (tptr->mNoteVolume < 0) tptr->mNoteVolume = 0;
                        if (tptr->mNoteVolume > 64) tptr->mNoteVolume = 64;
                        tptr->mVolume = tptr->mNoteVolume;
                    }
                    else
                    {
                        tptr->mNoteVolume = (tptr->mNoteVolume * sRetrigMulTable[tptr->mRetrigVolChange]) >> 4;
                        if (tptr->mNoteVolume > 64) tptr->mNoteVolume = 64;
                        tptr->mVolume = tptr->mNoteVolume;
                    }
                }
                tptr->mMultiRetrigCount++;
                break;
                
                // Tremor
                case 0x1d:
                if (tptr->mEffectData)
                {
                    tptr->mTremorOnTime = tptr->mNybble1;
                    tptr->mTremorOffTime = tptr->mNybble2;
                }
                break;
                
                // Extra fine portamento
                case 0x21:
                switch (tptr->mNybble1)
                {
                    case 1:
                    if (tptr->mNybble2) tptr->mPortaSpeedUp = tptr->mNybble2;
                    tptr->mBasePeriod -= tptr->mPortaSpeedUp;
                    if (tptr->mBasePeriod < mHighPeriod) tptr->mBasePeriod = mHighPeriod;
                    tptr->mPeriod = tptr->mBasePeriod;
                    break;
                    
                    case 2:
                    if (tptr->mNybble2) tptr->mPortaSpeedDown = tptr->mNybble2;
                    tptr->mBasePeriod += tptr->mPortaSpeedDown;
                    if (tptr->mBasePeriod > mLowPeriod) tptr->mBasePeriod = mLowPeriod;
                    tptr->mPeriod = tptr->mBasePeriod;
                    break;
                }
                break;
            }
            if (notePtr != &sEmptyNote) notePtr++;
        }
    }
    if (mTickCount)
    {
        // If tick isn't 0, update "continuous" effects
        for (unsigned i = 0; i < mXMHeader.mNumChannels; ++i)
        {
            XMTrack* tptr = &mTracks[i];
            Channel* chptr = mChannels[i];
            
            switch (tptr->mVolEffect >> 4)
            {
                case 0x0:
                break;
                
                // Volslide down
                case 0x6:
                tptr->mNoteVolume -= tptr->mVolEffect & 0xf;
                if (tptr->mNoteVolume < 0) tptr->mNoteVolume = 0;
                tptr->mVolume = tptr->mNoteVolume;
                break;
                
                // Volslide up
                case 0x7:
                tptr->mNoteVolume += tptr->mVolEffect & 0xf;
                if (tptr->mNoteVolume > 64) tptr->mNoteVolume = 64;
                tptr->mVolume = tptr->mNoteVolume;
                break;
                
                // Vibrato
                case 0xb:
                tptr->mVibratoPhase += tptr->mVibratoSpeed * 4;
                tptr->mPeriod = tptr->mBasePeriod + ((Song::sVibratoTable[tptr->mVibratoType & 3][tptr->mVibratoPhase] * tptr->mVibratoDepth) >> 3);
                if (tptr->mPeriod < mHighPeriod) tptr->mPeriod = mHighPeriod;
                if (tptr->mPeriod > mLowPeriod) tptr->mPeriod = mLowPeriod;
                break;
                
                // Panslide left
                case 0xd:
                {
                    int newPan = tptr->mNotePanning;
                    newPan -= tptr->mVolEffect & 0xf;
                    if (newPan < 0) newPan = 0;
                    tptr->mNotePanning = newPan;
                }
                break;
                
                // Panslide right
                case 0xe:
                {
                    int newPan = tptr->mNotePanning;
                    newPan += tptr->mVolEffect & 0xf;
                    if (newPan > 255) newPan = 255;
                    tptr->mNotePanning = newPan;
                }
                break;
                
                // Toneportamento
                case 0xf:
                tonePortamento(tptr, chptr);
                break;
            }
            
            // Regular effects
            switch (tptr->mEffect)
            {
                // Arpeggio
                case 0x0:
                if (tptr->mEffectData)
                {
                    char phase = mTickCount % 3;
                    switch (phase)
                    {
                        case 0:
                        tptr->mPeriod = tptr->mBasePeriod;
                        break;
                        
                        case 1:
                        if (mXMHeader.mUseLinear) tptr->mPeriod = tptr->mBasePeriod - tptr->mNybble1 * 64;
                        else tptr->mPeriod = getAmigaPeriod(tptr->mRealNote + tptr->mNybble1, tptr->mFineTune);
                        if (tptr->mPeriod < mHighPeriod) tptr->mPeriod = mHighPeriod;
                        break;
                        
                        case 2:
                        if (mXMHeader.mUseLinear) tptr->mPeriod = tptr->mBasePeriod - tptr->mNybble2 * 64;
                        else tptr->mPeriod = getAmigaPeriod(tptr->mRealNote + tptr->mNybble2, tptr->mFineTune);
                        if (tptr->mPeriod < mHighPeriod) tptr->mPeriod = mHighPeriod;
                        break;
                    }
                }
                break;
                
                // Portamento up
                case 0x1:
                tptr->mBasePeriod -= tptr->mPortaSpeedUp * 4;
                if (tptr->mBasePeriod < mHighPeriod) tptr->mBasePeriod = mHighPeriod;
                tptr->mPeriod = tptr->mBasePeriod;
                break;
                
                // Portamento down
                case 0x2:
                tptr->mBasePeriod += tptr->mPortaSpeedDown * 4;
                if (tptr->mBasePeriod > mLowPeriod) tptr->mBasePeriod = mLowPeriod;
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
                tptr->mVolume = tptr->mNoteVolume + ((Song::sVibratoTable[tptr->mTremoloType & 3][tptr->mTremoloPhase] * tptr->mTremoloDepth) >> 4);
                if (tptr->mVolume < 0) tptr->mVolume = 0;
                if (tptr->mVolume > 64) tptr->mVolume = 64;
                break;
                
                // Volume slide
                case 0xa:
                volumeSlide(tptr, chptr);
                break;
                
                // Extended command
                case 0xe:
                extendedCommand(tptr, chptr);
                break;
                
                // Global volume slide
                case 0x11:
                if (mGlobalVolSpeedUp)
                {
                    mGlobalVol += mGlobalVolSpeedUp;
                    if (mGlobalVol > 64) mGlobalVol = 64;
                }
                else
                {
                    mGlobalVol -= mGlobalVolSpeedDown;
                    if (mGlobalVol < 0) mGlobalVol = 0;
                }
                break;
                
                // Panning slide
                case 0x19:
                {
                    int newPan = tptr->mNotePanning;
                    
                    newPan += tptr->mPanningSpeedRight;
                    if (newPan < 0) newPan = 0;
                    newPan -= tptr->mPanningSpeedLeft;
                    if (newPan > 255) newPan = 255;
                    tptr->mNotePanning = newPan;
                }
                break;
                
                // Multi retrig
                case 0x1b:
                if (tptr->mMultiRetrigCount >= tptr->mRetrigInterval)
                {
                    startNewNote(tptr, chptr);
                    tptr->mMultiRetrigCount = 0;
                    if (!sRetrigMulTable[tptr->mRetrigVolChange])
                    {
                        tptr->mNoteVolume += sRetrigAddTable[tptr->mRetrigVolChange];
                        if (tptr->mNoteVolume < 0) tptr->mNoteVolume = 0;
                        if (tptr->mNoteVolume > 64) tptr->mNoteVolume = 64;
                        tptr->mVolume = tptr->mNoteVolume;
                    }
                    else
                    {
                        tptr->mNoteVolume = (tptr->mNoteVolume * sRetrigMulTable[tptr->mRetrigVolChange]) >> 4;
                        if (tptr->mNoteVolume > 64) tptr->mNoteVolume = 64;
                        tptr->mVolume = tptr->mNoteVolume;
                    }
                }
                tptr->mMultiRetrigCount++;
                break;
                
                // Tremor
                case 0x1d:
                if (!tptr->mTremorCount)
                {
                    tptr->mTremorStatus ^= 1;
                    if (tptr->mTremorStatus) tptr->mTremorCount = tptr->mTremorOnTime + 1;
                    else tptr->mTremorCount = tptr->mTremorOffTime + 1;
                }
                if (tptr->mTremorStatus) tptr->mVolume = tptr->mNoteVolume;
                else tptr->mVolume = 0;
                tptr->mTremorCount--;
                break;
            }
            chptr++;
            tptr++;
        }
    }

    // Update envelopes and set the frequency, volume & panning of the channel
    for (unsigned i = 0; i < mXMHeader.mNumChannels; ++i)
    {
        XMTrack* tptr = &mTracks[i];
        Channel* chptr = mChannels[i];
        XMInstrument *instrPtr = tptr->mInstr;
        short finalPeriod = tptr->mPeriod;
        
        // Update fadeout (must be done before before calculating the final volume)
        if (!tptr->mKeyOn)
        {
            tptr->mFadeOutValue -= instrPtr->mFadeOut;
            if (tptr->mFadeOutValue < 0) tptr->mFadeOutValue = 0;
        }
        
        // Calculate final channel values
        int finalVol;
        if (instrPtr->mVolumeEnvFlags & ENV_ON) 
            finalVol = (tptr->mVolume * mGlobalVol * instrPtr->mVolumeEnvLookup[tptr->mVolumeEnvPos] * (tptr->mFadeOutValue >> 9)) >> 18;
        else 
            finalVol = (tptr->mVolume * mGlobalVol * (tptr->mFadeOutValue >> 9)) >> 12;
        int finalPan;
        if (instrPtr->mPanningEnvFlags & ENV_ON) 
            finalPan = tptr->mNotePanning + (instrPtr->mPanningEnvLookup[tptr->mPanningEnvPos] - 32) * (128 - abs(tptr->mNotePanning - 128)) / 32;
        else 
            finalPan = tptr->mNotePanning;
        
        chptr->setIntVolume(finalVol);
        chptr->setIntPanning(finalPan);
        
        // Update instrument vibrato
        if ((instrPtr->mVibratoDepth) && (instrPtr->mVibratoRate))
        {
            if (instrPtr->mVibratoSweep)
            {
                if (tptr->mKeyOn)
                {
                    tptr->mInstrVibratoDepth += (instrPtr->mVibratoDepth << 8) / instrPtr->mVibratoSweep;
                    if (tptr->mInstrVibratoDepth > (instrPtr->mVibratoDepth << 8)) tptr->mInstrVibratoDepth = instrPtr->mVibratoDepth << 8;
                }
            }
            else tptr->mInstrVibratoDepth = instrPtr->mVibratoDepth << 8;
            tptr->mInstrVibratoPhase += instrPtr->mVibratoRate;
            finalPeriod += (Song::sVibratoTable[instrPtr->mVibratoType & 3][tptr->mInstrVibratoPhase] * tptr->mInstrVibratoDepth) >> 14;
        }
        if (finalPeriod < (mHighPeriod - 15)) finalPeriod = mHighPeriod - 15;
        if (finalPeriod > (mLowPeriod + 15)) finalPeriod = mLowPeriod + 15;
        
        if (mXMHeader.mUseLinear)
            chptr->setIntFrequency(sLinearFreqTable[finalPeriod % 768] >> (finalPeriod / 768));
        else 
            chptr->setIntFrequency(14317456 / finalPeriod);
        
        // Update envelopes
        if ((instrPtr->mVolumeEnvFlags & ENV_ON) && ((!(instrPtr->mVolumeEnvFlags & ENV_SUSTAIN)) || (!tptr->mKeyOn) || (tptr->mVolumeEnvPos != instrPtr->mVolumeSustainPoint)))
        {
            tptr->mVolumeEnvPos++;
            if (tptr->mVolumeEnvPos > 324) tptr->mVolumeEnvPos = 324;
            if (instrPtr->mVolumeEnvFlags & ENV_LOOP)
            {
                if (tptr->mVolumeEnvPos >= instrPtr->mVolumeLoopEnd)
                    tptr->mVolumeEnvPos = instrPtr->mVolumeLoopStart;
            }
        }
        if ((instrPtr->mPanningEnvFlags & ENV_ON) && ((!(instrPtr->mPanningEnvFlags & ENV_SUSTAIN)) || (!tptr->mKeyOn) || (tptr->mPanningEnvPos != instrPtr->mPanningSustainPoint)))
        {
            tptr->mPanningEnvPos++;
            if (tptr->mPanningEnvPos > 324) tptr->mPanningEnvPos = 324;
            if (instrPtr->mPanningEnvFlags & ENV_LOOP)
            {
                if (tptr->mPanningEnvPos >= instrPtr->mPanningLoopEnd)
                    tptr->mPanningEnvPos = instrPtr->mPanningLoopStart;
            }
        }
    }
    
    // Advance song
    if (mTickTempo)
    {
        mTickCount++;
        if (mTickCount >= mTickTempo)
        {
            mTickCount = 0;
            if (mPatternDelay)
                mPatternDelay--;
            if (!mPatternDelay)
            {
                mLine++;
                if (mLine >= pattPtr->mRows)
                {
                    mLine = 0;
                    mPos++;
                }
                if (mPos >= mXMHeader.mSongLength) 
                    mPos = mXMHeader.mRestartPos;
            }
        }
    }
}

void XM::startNewNote(XMTrack* tptr, Channel* chptr)
{
    if (tptr->mNewInstrument) 
        tptr->mInstrument = tptr->mNewInstrument - 1;
    
    // Handle keyoff
    if (tptr->mNote == KEYOFF - 1)
    {
        tptr->mKeyOn = false;
        if (!(tptr->mInstr->mVolumeEnvFlags & ENV_ON))
        {
            tptr->mNoteVolume = 0;
            tptr->mVolume = 0;
        }
        return;
    }
    
    // Now get instrptr & sampleptr, but don't change them if using toneportamento
    if ((tptr->mEffect == 0x3) || (tptr->mEffect == 0x5) || ((tptr->mVolEffect >> 4) == 0xf))
        tptr->mTonePortamento = true;
    else
    {
        tptr->mTonePortamento = false;
        if (tptr->mInstrument < mXMHeader.mNumInstruments) 
            tptr->mInstr = &mInstruments[tptr->mInstrument];
        
        tptr->mSoundNumber = tptr->mInstr->mSampleTable[tptr->mNote];
        tptr->mXMSample = &tptr->mInstr->mXMSamples[tptr->mSoundNumber];
        tptr->mSound = tptr->mInstr->mSounds[tptr->mSoundNumber];
    }
    
    // Don't go further if sample doesn't exist
    if ((tptr->mXMSample) && (tptr->mSound))
    {
        tptr->mFineTune = tptr->mXMSample->mFineTune;
        tptr->mMultiRetrigCount = 1;
        if (!(tptr->mVibratoType & 4)) tptr->mVibratoPhase = 0;
        if (!(tptr->mTremoloType & 4)) tptr->mTremoloPhase = 0;
        tptr->mTremorCount = 0;
        tptr->mTremorStatus = 0;
        tptr->mRealNote = tptr->mNote + tptr->mXMSample->mRelativeNote;
        if (tptr->mRealNote < 0) tptr->mRealNote = 0;
        if (tptr->mRealNote > 118) tptr->mRealNote = 118;
        if (tptr->mTonePortamento)
        {
            // Toneportamento
            if (mXMHeader.mUseLinear) tptr->mTargetPeriod = 7680 - tptr->mRealNote * 64 - tptr->mFineTune / 2;
            else tptr->mTargetPeriod = getAmigaPeriod(tptr->mRealNote, tptr->mFineTune);
        }
        else
        {
            // Normal note start
            if (mXMHeader.mUseLinear) tptr->mBasePeriod = 7680 - tptr->mRealNote * 64 - tptr->mFineTune / 2;
            else tptr->mBasePeriod = getAmigaPeriod(tptr->mRealNote, tptr->mFineTune);
            tptr->mPeriod = tptr->mBasePeriod;
            chptr->playLockless(tptr->mSound);
            
            if (tptr->mEffect == 0x9)
            {
                signed char *newPos;
                if (tptr->mSound->isSixteenBit())
                    newPos = tptr->mSound->getStart() + (tptr->mSoundOffset << 9);
                else
                    newPos = tptr->mSound->getStart() + (tptr->mSoundOffset << 8);
                
                if (newPos >= tptr->mSound->getEnd())
                    chptr->stopLockless();
                else
                    chptr->setPlayPositionLockless(newPos);
            }
        }
    }
}

void XM::tonePortamento(XMTrack* tptr, Channel* chptr)
{
    if (tptr->mTonePortamento)
    {
        if (tptr->mBasePeriod < tptr->mTargetPeriod)
        {
            tptr->mBasePeriod += tptr->mTonePortaSpeed * 4;
            if (tptr->mBasePeriod >= tptr->mTargetPeriod)
            {
                tptr->mBasePeriod = tptr->mTargetPeriod;
                tptr->mTonePortamento = false;
            }
        }
        if (tptr->mBasePeriod > tptr->mTargetPeriod)
        {
            tptr->mBasePeriod -= tptr->mTonePortaSpeed * 4;
            if (tptr->mBasePeriod <= tptr->mTargetPeriod)
            {
                tptr->mBasePeriod = tptr->mTargetPeriod;
                tptr->mTonePortamento = false;
            }
        }
        tptr->mPeriod = tptr->mBasePeriod;
        if (tptr->mGlissando)
        {
            if (mXMHeader.mUseLinear)
            {
                tptr->mPeriod += tptr->mFineTune / 2;
                tptr->mPeriod += 32;
                tptr->mPeriod &= 0xffc0;
                tptr->mPeriod -= tptr->mFineTune / 2;
            }
            else
            {
                int offset = M_MAX_INT;
                int sc;
                short bestperiod = 0;
                
                for (sc = 0; sc <= 118; sc++)
                {
                    int newoffset = abs((int)tptr->mPeriod - (int)getAmigaPeriod(sc, tptr->mFineTune));
                    
                    if (newoffset < offset)
                    {
                        bestperiod = getAmigaPeriod(sc, tptr->mFineTune);
                        offset = newoffset;
                    }
                }
                tptr->mPeriod = bestperiod;
            }
        }
    }
}

void XM::vibrato(XMTrack* tptr, Channel* chptr)
{
    tptr->mVibratoPhase += tptr->mVibratoSpeed * 4;
    tptr->mPeriod = tptr->mBasePeriod + ((Song::sVibratoTable[tptr->mVibratoType & 3][tptr->mVibratoPhase] * tptr->mVibratoDepth) >> 3);
    if (tptr->mPeriod < mHighPeriod) tptr->mPeriod = mHighPeriod;
    if (tptr->mPeriod > mLowPeriod) tptr->mPeriod = mLowPeriod;
}

void XM::volumeSlide(XMTrack* tptr, Channel* chptr)
{
    if (tptr->mVolumeSpeedUp)
    {
        tptr->mNoteVolume += tptr->mVolumeSpeedUp;
        if (tptr->mNoteVolume > 64) tptr->mNoteVolume = 64;
    }
    else
    {
        tptr->mNoteVolume -= tptr->mVolumeSpeedDown;
        if (tptr->mNoteVolume < 0) tptr->mNoteVolume = 0;
    }
    tptr->mVolume = tptr->mNoteVolume;
}

void XM::extendedCommand(XMTrack* tptr, Channel* chptr)
{
    switch(tptr->mNybble1)
    {
        // Fine porta up
        case 0x1:
        if (!mTickCount)
        {
            if (tptr->mNybble2) tptr->mPortaSpeedUp = tptr->mNybble2;
            tptr->mBasePeriod -= tptr->mPortaSpeedUp * 4;
            if (tptr->mBasePeriod < mHighPeriod) tptr->mBasePeriod = mHighPeriod;
        }
        break;
        
        // Fine porta down
        case 0x2:
        if (!mTickCount)
        {
            if (tptr->mNybble2) tptr->mPortaSpeedDown = tptr->mNybble2;
            tptr->mBasePeriod += tptr->mPortaSpeedDown * 4;
            if (tptr->mBasePeriod > mLowPeriod) tptr->mBasePeriod = mLowPeriod;
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
            tptr->mFineTune = (tptr->mNybble2 << 4) - 128;
            if (mXMHeader.mUseLinear) tptr->mBasePeriod = 7680 - tptr->mRealNote * 64 - tptr->mFineTune / 2;
            else tptr->mBasePeriod = getAmigaPeriod(tptr->mRealNote, tptr->mFineTune);
            tptr->mPeriod = tptr->mBasePeriod;
        }
        break;
        
        // Patternloop
        case 0x6:
        if (!mTickCount)
        {
            if (!tptr->mNybble2) 
                tptr->mPatternLoopLine = mLine;
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
        
        // Retrig
        case 0x9:
        if (tptr->mNybble2)
        {
            if (tptr->mRetrigCount >= tptr->mNybble2)
            {
                tptr->mRetrigCount = 0;
                // Don't retrig on tick 0 
                if (mTickCount)
                {
                    startNewNote(tptr, chptr);
                    tptr->mKeyOn = true;
                    tptr->mFadeOutValue = 32768;
                    tptr->mVolumeEnvPos = 0;
                    tptr->mPanningEnvPos = 0;
                    tptr->mInstrVibratoPhase = 0;
                    tptr->mInstrVibratoDepth = 0;
                }
            }
        }
        else
        {
            // Special case e90: start the note at tick 0 but don't restart envelope
            if (!mTickCount)
            {
                startNewNote(tptr, chptr);
            }
        }
        tptr->mRetrigCount++;
        break;
        
        // Notedelay
        case 0xd:
        // Don't start on tick 0 
        if (!mTickCount) break;
        if (mTickCount == tptr->mNybble2)
        {
            startNewNote(tptr, chptr);
            if (tptr->mNewInstrument) 
                changeInstrument(tptr);
            else
            {
                tptr->mKeyOn = true;
                tptr->mFadeOutValue = 32768;
                tptr->mVolumeEnvPos = 0;
                tptr->mPanningEnvPos = 0;
                tptr->mInstrVibratoPhase = 0;
                tptr->mInstrVibratoDepth = 0;
            }
            if ((tptr->mVolEffect >= 0x10) && (tptr->mVolEffect <= 0x50))
            {
                tptr->mNoteVolume = tptr->mVolEffect - 0x10;
                tptr->mVolume = tptr->mNoteVolume;
            }
            if ((tptr->mVolEffect >> 4) == 0xc)
            {
                tptr->mNotePanning = (tptr->mVolEffect & 0xf) << 4 | (tptr->mVolEffect & 0xf);
            }
        }
        break;
        
        // Cut note
        case 0xc:
        if (mTickCount == tptr->mNybble2) tptr->mNoteVolume = 0;
        break;
        
        // Fine volslide up
        case 0xa:
        if (!mTickCount)
        {
            if (tptr->mNybble2) tptr->mVolumeSpeedUp = tptr->mNybble2;
            tptr->mNoteVolume += tptr->mVolumeSpeedUp;
            if (tptr->mNoteVolume > 64) tptr->mNoteVolume = 64;
        }
        break;
        
        // Fine volslide down
        case 0xb:
        if (!mTickCount)
        {
            if (tptr->mNybble2) tptr->mVolumeSpeedDown = tptr->mNybble2;
            tptr->mNoteVolume -= tptr->mVolumeSpeedDown;
            if (tptr->mNoteVolume < 0) tptr->mNoteVolume = 0;
        }
        break;
        
        // Patterndelay
        case 0xe:
        if (!mTickCount)
        {
            mPatternDelay = tptr->mNybble2 + 1;
        }
        break;
    }
}

void XM::changeInstrument(XMTrack* tptr)
{
    tptr->mInstrument = tptr->mNewInstrument - 1;
    if (tptr->mXMSample)
    {
        tptr->mNotePanning = tptr->mXMSample->mPanning;
        tptr->mNoteVolume = tptr->mXMSample->mVolume;
        tptr->mVolume = tptr->mNoteVolume;
    }
    
    // Must not restart envelopes if there's a keyoff just in that place
    if ((!tptr->mNewNote) || (tptr->mNote != KEYOFF - 1))
    {
        tptr->mKeyOn = true;
        tptr->mFadeOutValue = 32768;
        tptr->mVolumeEnvPos = 0;
        tptr->mPanningEnvPos = 0;
        tptr->mInstrVibratoPhase = 0;
        tptr->mInstrVibratoDepth = 0;
    }
}

unsigned XM::getAmigaPeriod(int mNote, int fineTune)
{
    int noteOffset = (mNote % 12) << 3;
    if (fineTune >= 0)
    {
        int roughFineTune = fineTune >> 4;
        int fineFineTune = fineTune & 15;
        return ((sAmigaFreqTable[8 + noteOffset + roughFineTune] * (16 - fineFineTune) +
            sAmigaFreqTable[9 + noteOffset + roughFineTune] * fineFineTune)
            * 2) >> (mNote / 12);
    }
    else
    {
        int roughFineTune = (fineTune - 15) >> 4;
        int fineFineTune = fineTune & 15;
        return ((sAmigaFreqTable[8 + noteOffset + roughFineTune] * (16 - fineFineTune) +
            sAmigaFreqTable[9 + noteOffset + roughFineTune] * fineFineTune)
            * 2) >> (mNote / 12);
    }
}
