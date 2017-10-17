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

#include "labpack.h"
#include "labpack-writer-private.h"

static labpack_writer_t OUT_OF_MEMORY_WRITER = {
    NULL,                                          // encoder
    NULL,                                          // buffer
    0,                                             // size
    LABPACK_STATUS_ERROR_OUT_OF_MEMORY,            // status
    "Not enough memory available to create writer" // status message
};

static void
labpack_writer_reset_status(labpack_writer_t* writer)
{
    assert(writer);
    writer->status = LABPACK_STATUS_OK;        
    writer->status_message = labpack_status_string(writer->status);
}

static void
labpack_writer_init(labpack_writer_t* writer)
{
    assert(writer);
    writer->encoder = malloc(sizeof(mpack_writer_t));
    if (writer->encoder) {
        labpack_writer_reset_status(writer);
    } else {
        writer->status = LABPACK_STATUS_ERROR_OUT_OF_MEMORY;
        writer->status_message = "Not enough memory available to create internal encoder";
    }
    writer->buffer = NULL;
    writer->size = 0;
}

labpack_writer_t*
labpack_writer_create() 
{
    labpack_writer_t* writer = malloc(sizeof(labpack_writer_t));
    if (writer == NULL) {
        return &OUT_OF_MEMORY_WRITER;
    }
    labpack_writer_init(writer);
    return writer;
}

void
labpack_writer_destroy(labpack_writer_t* writer)
{
    free(writer->encoder);
    writer->encoder = NULL;
    free(writer->buffer);
    writer->buffer = NULL;
    writer->size = 0;
    free(writer);
}

void
labpack_writer_begin(labpack_writer_t* writer)
{
    assert(writer);
    mpack_writer_init_growable(writer->encoder, &writer->buffer, &writer->size);
    if (mpack_writer_error(writer->encoder) != mpack_ok) {
        writer->status = LABPACK_STATUS_ERROR_ENCODER;
        writer->status_message = mpack_error_to_string(mpack_writer_error(writer->encoder));
    }
    labpack_writer_reset_status(writer);
}

void
labpack_writer_end(labpack_writer_t* writer)
{
    assert(writer);
    if (mpack_writer_destroy(writer->encoder) != mpack_ok) {
        writer->status = LABPACK_STATUS_ERROR_ENCODER;
        writer->status_message = mpack_error_to_string(mpack_writer_error(writer->encoder));
    }
}

labpack_status_t
labpack_writer_status(labpack_writer_t* writer) 
{
    assert(writer);
    return writer->status;
}

const char*
labpack_writer_status_message(labpack_writer_t* writer)
{
    assert(writer);
    return writer->status_message;
}

bool
labpack_writer_is_ok(labpack_writer_t* writer)
{
    assert(writer);
    return labpack_writer_status(writer) == LABPACK_STATUS_OK;
}

bool
labpack_writer_is_error(labpack_writer_t* writer)
{
    assert(writer);
    return labpack_writer_status(writer) != LABPACK_STATUS_OK;
}

size_t
labpack_writer_buffer_size(labpack_writer_t* writer)
{
    assert(writer);
    return mpack_writer_buffer_used(writer->encoder);
}

void
labpack_write_i8(labpack_writer_t* writer, int8_t value)
{
    assert(writer);
    mpack_write_i8(writer->encoder, value); 
}

void
labpack_write_i16(labpack_writer_t* writer, int16_t value)
{
    assert(writer);
    mpack_write_i16(writer->encoder, value); 
}

void
labpack_write_i32(labpack_writer_t* writer, int32_t value)
{
    assert(writer);
    mpack_write_i32(writer->encoder, value); 
}

void
labpack_write_i64(labpack_writer_t* writer, int64_t value)
{
    assert(writer);
    mpack_write_i64(writer->encoder, value); 
}

void
labpack_write_int(labpack_writer_t* writer, int64_t value)
{
    assert(writer);
    mpack_write_int(writer->encoder, value);
}

void
labpack_write_u8(labpack_writer_t* writer, uint8_t value)
{
    assert(writer);
    mpack_write_u8(writer->encoder, value);
}

void
labpack_write_u16(labpack_writer_t* writer, uint16_t value)
{
    assert(writer);
    mpack_write_u16(writer->encoder, value);
}

void
labpack_write_u32(labpack_writer_t* writer, uint32_t value)
{
    assert(writer);
    mpack_write_u32(writer->encoder, value);
}

void
labpack_write_u64(labpack_writer_t* writer, uint64_t value)
{
    assert(writer);
    mpack_write_u64(writer->encoder, value);
}

void
labpack_write_uint(labpack_writer_t* writer, uint64_t value)
{
    assert(writer);
    mpack_write_uint(writer->encoder, value);
}

