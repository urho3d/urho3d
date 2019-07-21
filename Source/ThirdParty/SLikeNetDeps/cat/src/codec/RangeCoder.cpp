/*
	Copyright (c) 2009-2010 Christopher A. Taylor.  All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	* Redistributions of source code must retain the above copyright notice,
	  this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright notice,
	  this list of conditions and the following disclaimer in the documentation
	  and/or other materials provided with the distribution.
	* Neither the name of LibCat nor the names of its contributors may be used
	  to endorse or promote products derived from this software without
	  specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
	LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
	SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
	POSSIBILITY OF SUCH DAMAGE.
*/

#include <cat/codec/RangeCoder.hpp>
#include <cat/hash/MurmurHash2.hpp>
#include <cat/port/EndianNeutral.hpp>
#include <cmath>
#include <cstring>
using namespace cat;
using namespace std;

const u64 Top = (u64)1 << 56;
const u64 MaxRange = (u64)1 << 48;

#define SYMBOL_LUT_BITS 8
#define SYMBOL_LUT_SHIFT (16 - SYMBOL_LUT_BITS)
#define SYMBOL_LUT_BYTES (1 << SYMBOL_LUT_BITS)

#define SYMBOL_BYTES(total) (SYMBOL_LUT_BYTES + (total) - 1)
#define STATIC_TABLE_BYTES(total) (4 + 2 + 2 + 256 + 256 + 2 * (total) * SYMBOL_BYTES(total) + (total) * (16 * 4))

#define GET_SYMBOL_LUT(frequencies, total, index) ((const u8 *)((frequencies) + (index) * SYMBOL_BYTES(total)))
#define GET_SYMBOL_BASE(frequencies, total, index) ((const u16 *)(GET_SYMBOL_LUT((frequencies), (total), (index)) + SYMBOL_LUT_BYTES*2))


//// TextStatsCollector

TextStatsCollector::TextStatsCollector()
{
    CAT_OBJCLR(frequencies);
    CAT_OBJCLR(seen);
    last = 0;
    total = 0;

    // The '\0' null terminator is always symbol 0 and always present
    seen[0] = 1;
    total = 1;
    frequencies[0][0] = 1;
}

void TextStatsCollector::Tally(u8 x)
{
    u32 &tf = frequencies[last][x];

    // Increment frequency in table and check for overflow
    // 2^24 is used as the limit so that there can be no cumulative
    // overflow if all the frequencies are added together.
    if (++tf >= 0x01000000)
    {
        // For each symbol that follows the last symbol,
        for (int ii = 0; ii < 256; ++ii)
        {
            u32 &tm = frequencies[last][ii];

            // Divide the frequencies by two
            if (tm > 1) tm >>= 1;
        }
    }

    if (!seen[x])
    {
        ++total;
        seen[x] = 1;
    }

    last = x;
}

bool TextStatsCollector::GenerateMinimalStaticTable(const char *TableName, std::ostream &osout)
{
    u32 bytes = STATIC_TABLE_BYTES(total);
    u8 *output = new u8[bytes + 3];
    if (!output)
    {
        osout << "Out of memory";
        return false;
    }

    TableFormat *table = (TableFormat *)output;

    // Write char2index table and some index2char
    u32 ii, jj;
    for (jj = 0, ii = 0; ii < 256; ++ii)
    {
        if (seen[ii])
        {
            table->index2char[jj] = ii;
            table->char2index[ii] = jj;
            ++jj;
        }
        else
        {
            table->char2index[ii] = 0;
        }
    }

    // Write remainder of index2char table
    while (jj < 256)
    {
        table->index2char[jj++] = 0;
    }

    // Generate normalized frequency table
    u16 *freq = table->frequencies;

    for (ii = 0; ii < total; ++ii)
    {
        u32 sum = 0, adjcum = 0;
        u32 work[256];

        u32 tlast = table->index2char[ii];
        for (jj = 0; jj < total; ++jj)
        {
            sum += frequencies[tlast][table->index2char[jj]];
            work[jj] = sum;
        }

        char *dict = (char*)freq;
        //memcpy(dict, frequent_words[table->index2char[ii]], DICTIONARY_WORDS * DICTIONARY_CHARS);

        //u8 *lut_low = (u8*)(dict + DICTIONARY_WORDS * DICTIONARY_CHARS);
        u8 *lut_low = (u8*)freq;
        u8 *lut_high = lut_low + SYMBOL_LUT_BYTES;
        freq += SYMBOL_LUT_BYTES;

        u16 *symbol_freqs = freq;
        u32 smax = work[total-1];

        for (jj = 0; jj < total-1; ++jj)
        {
            // Normalize the cumulative frequency to the range [0, 2^16)
            u32 adjcum_new;
            if (smax)
                adjcum_new = (u32)(((u64)work[jj] << 32) / smax) >> 16;
            else
                adjcum_new = (u32)(((u64)(jj+1) << 32) / total) >> 16;

            // Insure monotonic increase
            if (adjcum >= adjcum_new) adjcum_new = adjcum + 1;

            adjcum = adjcum_new;
            *freq++ = (u16)adjcum_new;
        }

        // It is possible that very unlikely symbols at the end will cause
        // an overflow since monotonicity is enforced.  Detect that overflow
        // and correct it by borrowing from earlier symbols.
        if (adjcum >= 0x10000)
        {
            u32 count = adjcum - 0xFFFF;
            u32 last = 0;
            u32 cumsub = 0;

            for (jj = 0; jj < total-1; ++jj)
            {
                u32 slack = symbol_freqs[jj] - last;

                if (slack >= 0x100)
                    cumsub = count;

                symbol_freqs[jj] -= cumsub;
            }
        }

        // Write LUT
        u8 symbol = 0, last_high = 0, last_low = 0;
        u32 high = 0;

        for (jj = 0; jj < SYMBOL_LUT_BYTES; ++jj)
        {
            for (;;)
            {
                high = symbol_freqs[symbol] >> SYMBOL_LUT_SHIFT;

                if (high > jj || symbol >= total - 1)
                    break;

                last_high = symbol++;
            }

            lut_low[jj] = last_low;
            lut_high[jj] = last_high;
            last_low = last_high;
        }
    }

    // Write header
    table->total = total;
    table->log2total = (u16)(std::log((double)total)/std::log((double)2) * 32768.0f / 8.0f);
    table->hash = MurmurHash32(output + 4, bytes - 4, 0);

    // Convert it to C code
    osout << "// To include this table, do something like this:" << endl;
    osout << "// #include \"" << TableName << ".stats\"" << endl << endl;
    osout << "static const u32 _" << TableName << "[] = {" << endl;

    u32 words = (bytes + 3)/4;
    u32 *output32 = (u32*)output;
    int line = 0;

    while (words--)
    {
        //if (!line) osout << "  ";

        osout << "0x" << hex << *output32++;

        // Cases for commas and newlines
        if (words)
        {
            osout << ',';
            if (++line >= 16)
            {
                osout << endl;
                line = 0;
            }
        }
    }

    osout << "};" << endl << endl;

    osout << "static const TextStatsCollector::TableFormat *" << TableName
          << " = (const TextStatsCollector::TableFormat*)_" << TableName << ';' << endl;

    // Free memory from workspace
    delete []output;

    return true;
}

// Check for errors in the in-memory version of the table that was generated
bool TextStatsCollector::VerifyTableIntegrity(const TableFormat *table)
{
    u32 total = table->total;
    u32 bytes = STATIC_TABLE_BYTES(total);

    if (MurmurHash32(&table->total, bytes - 4, 0) != table->hash)
        return false;

    if (table->total > 256)
        return false;

    int used = 0;
    for (int ii = 0; ii < 256; ++ii)
    {
        u8 index = table->char2index[ii];
        if (index)
        {
            if (table->index2char[index] != ii)
                return false;

            ++used;
        }
    }

    if (used + 1 != (int)total)
        return false;

    u16 flog = (u16)(std::log((double)total)/std::log((double)2) * 32768.0f / 8.0f);
    if (flog != table->log2total)
        return false;

    used = 0;
    for (int ii = 0; ii < 256; ++ii)
    {
        if (table->index2char[ii])
            ++used;
    }

    if (used + 1 != (int)total)
        return false;

    for (u32 ii = 0; ii < total; ++ii)
    {
        u32 last = 0;

        for (u32 jj = 0; jj < total - 1; ++jj)
        {
            u32 x = GET_SYMBOL_BASE(table->frequencies, total, ii)[jj];

            if (last >= x)
                return false;

            //u32 range = x - last;

            last = x;
        }

        const u8 *lut_low = GET_SYMBOL_LUT(table->frequencies, total, ii);
        const u8 *lut_high = lut_low + SYMBOL_LUT_BYTES;

        for (u32 jj = 0; jj < SYMBOL_LUT_BYTES; ++jj)
        {
            if (lut_low[jj] > lut_high[jj])
                return false;

            if (lut_low[jj] >= total - 1)
                return false;

            if (lut_high[jj] >= total - 1)
                return false;
        }
    }

    return true;
}


//// RangeEncoder

// Intializing constructor
RangeEncoder::RangeEncoder(void *output_i, int limit_i)
{
    output = (u8*)output_i;
    remaining = limit = limit_i;

    range = 0;
}

// Copy Constructor
// See header for usage
RangeEncoder::RangeEncoder(RangeEncoder &cp)
{
    output = cp.output;
    limit = cp.limit;
    remaining = cp.remaining;
    low = cp.low;
    range = cp.range;
}

// Overwrite one context with another.  Using context references instead
// of working on the contexts directly is probably more efficient.
RangeEncoder &RangeEncoder::operator=(RangeEncoder &cp)
{
    output = cp.output;
    limit = cp.limit;
    remaining = cp.remaining;
    low = cp.low;
    range = cp.range;
    return *this;
}

// Write out bytes as needed
void RangeEncoder::Normalize()
{
    while ((low ^ (low + range)) < Top ||
           range < MaxRange && ((range = -(s64)low & (MaxRange - 1)),1))
    {
        // If we're out of room, fail
        if (!remaining)
        {
            output = 0;
            return;
        }
        --remaining;

        // Store the shifted out byte
        *output++ = (u8)(low >> 56);
        range <<= 8;
        low <<= 8;
    }
}

// Grab symbol low frequency and range from the table
void RangeEncoder::GetTableSymbol(const TextStatsCollector::TableFormat *stats, u32 &last, u8 ch, u16 &symbol_low, u16 &symbol_range)
{
    u8 symbol = stats->char2index[ch];
    const u16 *base = GET_SYMBOL_BASE(stats->frequencies, stats->total, last);

    if (symbol)
    {
        symbol_low = base[symbol - 1];
        if (symbol == stats->total - 1)
            symbol_range = (u16)(0x10000 - symbol_low);
        else
            symbol_range = base[symbol] - symbol_low;
    }
    else
    {
        symbol_low = 0;
        symbol_range = base[0];
    }

    last = symbol;
}

// Encode the given text with the given statistics
// NOTE: May be up to one byte longer than the original message
void RangeEncoder::Text(const char *msg, const TextStatsCollector::TableFormat *stats)
{
    u8 *backup_output = output;
    int backup_remaining = remaining;
    u64 backup_low = low, backup_range = range;
    const char *backup_msg = msg;

    BiasedBit(0, 0xFF000000);

    // Encode with order-1 statistics
    u16 symbol_low, symbol_range;
    u32 last = 0;

    do
    {
        Normalize();

        GetTableSymbol(stats, last, (u8)*msg++, symbol_low, symbol_range);

        range >>= 16;
        low += symbol_low * range;
        range *= symbol_range;
    } while (symbol_low);

    int len = (int)(msg - backup_msg);

    // If the tables failed, fall back to uniform distribution
    if ((backup_remaining - remaining) > (len * stats->log2total) >> 15)
    {
        // Restore state
        output = backup_output;
        remaining = backup_remaining;
        low = backup_low;
        range = backup_range;
        msg = backup_msg;

        BiasedBit(1, 0xFF000000);

        // Uniform range encode
        u8 ch;
        do
        {
            Normalize();

            ch = (u8)*msg++;
            range /= stats->total;
            low += stats->char2index[ch] * range;
        } while (ch);
    }
}

// Compress a biased bit given the frequency it is set
// frequency = average times out of 2^32 trials the bit will be 0
void RangeEncoder::BiasedBit(u32 b, u32 frequency)
{
    if (!range)
    {
        if (b)
        {
            low = (u64)frequency << 32;
            range = (u64)(-(s32)frequency) << 32;
        }
        else
        {
            low = 0;
            range = (u64)frequency << 32;
        }
    }
    else
    {
        Normalize();

        range >>= 32;

        if (b)
        {
            low += frequency * range;
            range *= (u32)(-(s32)frequency);
        }
        else
        {
            range *= frequency;
        }
    }
}

// Encode a field that takes on [0, total) values with equal likelihood
void RangeEncoder::Range(u32 symbol, u32 total)
{
    if (!range)
    {
        range = 0xFFFFFFFFFFFFFFFFLL / total;
        low = symbol * range;
    }
    else
    {
        Normalize();

        range /= total;
        low += symbol * range;
    }
}

// Emit the final byte(s) needed to encode the symbols
void RangeEncoder::Finish()
{
    // Output a minimal number of bytes, up to 2

    Normalize();

    if (!low) return;

    if (!remaining)
        output = 0;
    else
    {
        --remaining;
        low += range - 1;
        *output++ = (u8)(low >> 56);

        if (range < Top)
        {
            low <<= 8;

            if (!remaining)
            {
                output = 0;
                return;
            }

            *output++ = (u8)(low >> 56);
            --remaining;
        }
    }
}


//// RangeDecoder

// Intializing constructor
RangeDecoder::RangeDecoder(const void *message, int bytes)
{
    const u8 *m8 = (const u8*)message;

    range = 0;

    // Read up to 8 bytes of the frequency code
    if (bytes < 8)
    {
        code = 0;
        remaining = 0;

        u8 *code8 = (u8*)&code;

        switch (bytes)
        {
#if defined(CAT_ENDIAN_LITTLE)
        case 7: code8[1] = m8[6];
        case 6: code8[2] = m8[5];
        case 5: code8[3] = m8[4];
        case 4: *(u32*)&code8[4] = getBE(*(u32*)m8);
            break;
        case 3: code8[5] = m8[2];
        case 2: code8[6] = m8[1];
        case 1: code8[7] = m8[0];
#elif defined(CAT_ENDIAN_BIG)
        case 7: code8[6] = m8[6];
        case 6: code8[5] = m8[5];
        case 5: code8[4] = m8[4];
        case 4: *(u32*)code8 = *(u32*)m8;
            break;
        case 3: code8[2] = m8[2];
        case 2: code8[1] = m8[1];
        case 1: code8[0] = m8[0];
#else
#error "Fix this you lazy bastard"
#endif
        }
    }
    else
    {
        code = getBE(*(u64*)m8);
        input = m8 + 8;
        remaining = bytes - 8;
    }
}

// Read in bytes as needed
void RangeDecoder::Normalize()
{
    while ((low ^ (low + range)) < Top ||
           range < MaxRange && ((range = -(s64)low & (MaxRange - 1)),1))
    {
        code <<= 8;
        if (remaining)
        {
            code |= *input++;
            --remaining;
        }

        low <<= 8;
        range <<= 8;
    }
}

// Grab symbol low frequency and range from the table
u8 RangeDecoder::GetTableSymbol(const TextStatsCollector::TableFormat *stats, u32 &last, u16 freq, u16 &symbol_low, u16 &symbol_range)
{
    const u8 *lut = GET_SYMBOL_LUT(stats->frequencies, stats->total, last);
    const u16 *base = (const u16 *)(lut + SYMBOL_LUT_BYTES * 2);
    u32 lut_bits = freq >> SYMBOL_LUT_SHIFT;

    // Binary search for the symbol
    u32 below = lut[lut_bits], above = lut[SYMBOL_LUT_BYTES + lut_bits];

    while (below != above)
    {
        u32 pivot = (above - below + 1) / 2 + below;
        if (freq >= base[pivot])
            below = pivot;
        else
            above = pivot - 1;
    }

    u8 symbol;

    // Offset it for the unlisted zero element
    if (below || freq >= base[0])
    {
        symbol_low = base[below];
        ++below;

        if ((int)below == stats->total - 1)
            symbol_range = (u16)(0x10000 - symbol_low);
        else
            symbol_range = base[below] - symbol_low;
        symbol = (u8)below;
    }
    else
    {
        symbol_low = 0;
        symbol_range = base[0];
        symbol = 0;
    }

    last = symbol;
    return symbol;
}

// Decode the given text with the given statistics
int RangeDecoder::Text(char *msg, int buffer_size, const TextStatsCollector::TableFormat *stats)
{
    u16 symbol_low, symbol_range;
    u32 last = 0;
    char *init_msg = msg;

    if (BiasedBit(0xFF000000))
    {
        // Selected uniform model
        while (--buffer_size > 0)
        {
            Normalize();

            range /= stats->total;
            u8 symbol = (u8)((code - low) / range);
            low += symbol * range;
            last = stats->index2char[symbol];
            if (!last) break;
            *msg++ = (char)last;
        }
    }
    else
    {
        // Selected order-1 static model
        while (--buffer_size > 0)
        {
            Normalize();

            range >>= 16;
            u16 x = (u16)((code - low) / range);

            u8 symbol = GetTableSymbol(stats, last, x, symbol_low, symbol_range);
            low += symbol_low * range;
            range *= symbol_range;
            if (!symbol) break;
            *msg++ = (char)stats->index2char[symbol];
            --buffer_size;
        }
    }

    *msg = '\0';
    return (int)(msg - init_msg);
}

// Decompress a biased bit given the frequency it is set
// frequency = average times out of 2^32 trials the bit will be 0
u32 RangeDecoder::BiasedBit(u32 frequency)
{
    if (!range)
    {
        // Treat the first encoding specially.
        if ((u32)(code >> 32) < frequency)
        {
            low = 0;
            range = (u64)frequency << 32;
            return 0;
        }
        else
        {
            low = (u64)frequency << 32;
            range = (u64)(-(s32)frequency) << 32;
            return 1;
        }
    }
    else
    {
        Normalize();

        range >>= 32;
        u32 x = (u32)((code - low) / range);

        if (x < frequency)
        {
            range *= frequency;
            return 0;
        }
        else
        {
            low += frequency * range;
            range *= (u32)(-(s32)frequency);
            return 1;
        }
    }
}

// Decode a field that takes on [0, total) values with equal likelihood
u32 RangeDecoder::Range(u32 total)
{
    u32 symbol;

    if (!range)
    {
        range = 0xFFFFFFFFFFFFFFFFLL / total;
        symbol = (u32)(code / range);
        low = symbol * range;
    }
    else
    {
        Normalize();

        range /= total;
        symbol = (u32)((code - low) / range);
        low += symbol * range;
    }

    return symbol;
}
