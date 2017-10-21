/*
 * labpack - A LabVIEW-Friendly C library for encoding and decoding MessagePack
 * data
 *
 * Copyright (c) 2017 Field R&D Services, LLC. All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * withoutmodification, are permitted provided that the following conditions
 * are met: 
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution. 
 * 3. Neither the name of the Field R&D Services nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY Field R&D Services, LLC ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Field R&D Services, LLC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Contributor(s):
 *   Christopher R. Field <chris@fieldrndservices.com>
 */

#include <assert.h>

#include "mpack.h"

#include "labpack.h"
#include "labpack-private.h"
#include "labpack-reader-private.h"

static labpack_reader_t OUT_OF_MEMORY_READER = {
    NULL,                                          // decoder
    LABPACK_STATUS_ERROR_OUT_OF_MEMORY,            // status
    "Not enough memory available to create reader" // status message
};

static void
labpack_reader_reset_status(labpack_reader_t* reader)
{
    assert(reader);
    reader->status = LABPACK_STATUS_OK;
    reader->status_message = labpack_status_string(reader->status);
}

static void
labpack_reader_init(labpack_reader_t* reader)
{
    assert(reader);
    reader->decoder = malloc(sizeof(mpack_reader_t));
    if (reader->decoder) {
        labpack_reader_reset_status(reader);
    } else {
        reader->status = LABPACK_STATUS_ERROR_OUT_OF_MEMORY;
        reader->status_message = "Not enough memory available to create internal decoder";
    }
}

labpack_reader_t*
labpack_reader_create()
{
    labpack_reader_t* reader = malloc(sizeof(labpack_reader_t));
    if (reader == NULL) {
        return &OUT_OF_MEMORY_READER;
    }
    labpack_reader_init(reader);
    return reader;
}

void
labpack_reader_destroy(labpack_reader_t* reader)
{
    free(reader->decoder);
    reader->decoder = NULL;
    free(reader);
}

labpack_status_t
labpack_reader_status(labpack_reader_t* reader) 
{
    assert(reader);
    return reader->status;
}

const char*
labpack_reader_status_message(labpack_reader_t* reader)
{
    assert(reader);
    return reader->status_message;
}

bool
labpack_reader_is_ok(labpack_reader_t* reader)
{
    assert(reader);
    return labpack_reader_status(reader) == LABPACK_STATUS_OK;
}

bool
labpack_reader_is_error(labpack_reader_t* reader)
{
    assert(reader);
    return labpack_reader_status(reader) != LABPACK_STATUS_OK;
}

void
labpack_reader_begin(labpack_reader_t* reader, const char* data, size_t count)
{
    assert(reader);
    mpack_reader_init_data(reader->decoder, data, count);
}

void
labpack_reader_end(labpack_reader_t* reader)
{
    assert(reader);
    if (mpack_reader_destroy(reader->decoder) != mpack_ok) {
        reader->status = LABPACK_STATUS_ERROR_DECODER;
        reader->status_message = mpack_error_to_string(mpack_reader_error(reader->decoder));
    }
}

uint8_t
labpack_read_u8(labpack_reader_t* reader)
{
    assert(reader);
    return mpack_expect_u8(reader->decoder);
}

uint16_t
labpack_read_u16(labpack_reader_t* reader)
{
    assert(reader);
    return mpack_expect_u16(reader->decoder);
}

uint32_t
labpack_read_u32(labpack_reader_t* reader)
{
    assert(reader);
    return mpack_expect_u32(reader->decoder);
}

uint64_t
labpack_read_u64(labpack_reader_t* reader)
{
    assert(reader);
    return mpack_expect_u64(reader->decoder);
}

unsigned int
labpack_read_uint(labpack_reader_t* reader)
{
    assert(reader);
    return mpack_expect_uint(reader->decoder);
}

