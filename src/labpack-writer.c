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
#include "labpack-writer-private.h"

static const char* NULL_STRING_MESSAGE = "The string value cannot be NULL while the length is greater than zero (0)";
static const char* NULL_DATA_MESSAGE = "The data cannot be NULL while the count is greater than zero (0)";
static const char* NULL_CSTR_MESSAGE = "The NUL-terminated string value cannot be NULL";

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

void
labpack_writer_create(labpack_writer_t** handle) 
{
    labpack_writer_t* writer = malloc(sizeof(labpack_writer_t));
    if (writer == NULL) {
        return &OUT_OF_MEMORY_WRITER;
    }
    labpack_writer_init(writer);
    *handle = writer;
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

void
labpack_write_float(labpack_writer_t* writer, float value)
{
    assert(writer);
    mpack_write_float(writer->encoder, value);
}

void
labpack_write_double(labpack_writer_t* writer, double value)
{
    assert(writer);
    mpack_write_double(writer->encoder, value);
}

void
labpack_write_bool(labpack_writer_t* writer, bool value)
{
    assert(writer);
    mpack_write_bool(writer->encoder, value);
}

void
labpack_write_true(labpack_writer_t* writer)
{
    assert(writer);
    mpack_write_true(writer->encoder);
}

void
labpack_write_false(labpack_writer_t* writer)
{
    assert(writer);
    mpack_write_false(writer->encoder);
}

void
labpack_write_nil(labpack_writer_t* writer)
{
    assert(writer);
    mpack_write_nil(writer->encoder);
}

void
labpack_write_object_bytes(labpack_writer_t* writer, const char* data, size_t size)
{
    assert(writer);
    if (!data && size > 0) {
        writer->status = LABPACK_STATUS_ERROR_NULL_VALUE;
        writer->status_message = "The MessagePack object data is NULL but the size is not zero";
        return;
    }
    mpack_write_object_bytes(writer->encoder, data, size);
}

void
labpack_begin_array(labpack_writer_t* writer, uint32_t count)
{
    assert(writer);
    mpack_start_array(writer->encoder, count);
}

void
labpack_begin_map(labpack_writer_t* writer, uint32_t count)
{
    assert(writer);
    mpack_start_map(writer->encoder, count);
}

void
labpack_end_array(labpack_writer_t* writer)
{
    assert(writer);
    mpack_finish_array(writer->encoder);
}

void
labpack_end_map(labpack_writer_t* writer)
{
    assert(writer);
    mpack_finish_map(writer->encoder);
}

void
labpack_write_str(labpack_writer_t* writer, const char* value, uint32_t length)
{
    assert(writer);
    if (!value && length > 0) {
        writer->status = LABPACK_STATUS_ERROR_NULL_VALUE;
        writer->status_message = NULL_STRING_MESSAGE;
        return;
    }
    mpack_write_str(writer->encoder, value, length);
}

void
labpack_write_utf8(labpack_writer_t* writer, const char* value, uint32_t length)
{
    assert(writer);
    if (!value && length > 0) {
        writer->status = LABPACK_STATUS_ERROR_NULL_VALUE;
        writer->status_message = NULL_STRING_MESSAGE;
        return;
    }
    mpack_write_utf8(writer->encoder, value, length);
    if (mpack_writer_error(writer->encoder) != mpack_ok) {
        writer->status = LABPACK_STATUS_ERROR_ENCODER;
        writer->status_message = mpack_error_to_string(mpack_writer_error(writer->encoder));
        return;
    }
}

void
labpack_write_cstr(labpack_writer_t* writer, const char* value)
{
    assert(writer);
    if (!value) {
        writer->status = LABPACK_STATUS_ERROR_NULL_VALUE;
        writer->status_message = NULL_CSTR_MESSAGE;
        return;
    }
    mpack_write_cstr(writer->encoder, value);
}

void
labpack_write_cstr_or_nil(labpack_writer_t* writer, const char* value)
{
    assert(writer);
    mpack_write_cstr_or_nil(writer->encoder, value);
}

void
labpack_write_utf8_cstr(labpack_writer_t* writer, const char* value)
{
    assert(writer);
    if (!value) {
        writer->status = LABPACK_STATUS_ERROR_NULL_VALUE;
        writer->status_message = NULL_CSTR_MESSAGE;
        return;
    }
    mpack_write_utf8_cstr(writer->encoder, value);
    if (mpack_writer_error(writer->encoder) != mpack_ok) {
        writer->status = LABPACK_STATUS_ERROR_ENCODER;
        writer->status_message = mpack_error_to_string(mpack_writer_error(writer->encoder));
        return;
    }
}

void
labpack_write_utf8_cstr_or_nil(labpack_writer_t* writer, const char* value)
{
    assert(writer);
    mpack_write_utf8_cstr_or_nil(writer->encoder, value);
    if (mpack_writer_error(writer->encoder) != mpack_ok) {
        writer->status = LABPACK_STATUS_ERROR_ENCODER;
        writer->status_message = mpack_error_to_string(mpack_writer_error(writer->encoder));
        return;
    }
}

void
labpack_write_bin(labpack_writer_t* writer, const char* data, uint32_t count)
{
    assert(writer);
    if (!data && count > 0) {
        writer->status = LABPACK_STATUS_ERROR_NULL_VALUE;
        writer->status_message = NULL_DATA_MESSAGE;
        return;
    }
    mpack_write_bin(writer->encoder, data, count);
}

void
labpack_write_ext(labpack_writer_t* writer, int8_t type, const char* data, uint32_t count)
{
    assert(writer);
    if (!data && count > 0) {
        writer->status = LABPACK_STATUS_ERROR_NULL_VALUE;
        writer->status_message = NULL_DATA_MESSAGE;
        return;
    }
    mpack_write_ext(writer->encoder, type, data, count);
}

void
labpack_begin_str(labpack_writer_t* writer, uint32_t count)
{
    assert(writer);
    mpack_start_str(writer->encoder, count);
}

void
labpack_begin_bin(labpack_writer_t* writer, uint32_t count)
{
    assert(writer);
    mpack_start_bin(writer->encoder, count);
}

void
labpack_begin_ext(labpack_writer_t* writer, int8_t type, uint32_t count)
{
    assert(writer);
    mpack_start_ext(writer->encoder, type, count);
}

void
labpack_write_bytes(labpack_writer_t* writer, const char* data, size_t count)
{
    assert(writer);
    if (!data && count > 0) {
        writer->status = LABPACK_STATUS_ERROR_NULL_VALUE;
        writer->status_message = NULL_DATA_MESSAGE;
        return;
    }
    mpack_write_bytes(writer->encoder, data, count);
}

void
labpack_end_str(labpack_writer_t* writer)
{
    assert(writer);
    mpack_finish_str(writer->encoder);
}

void
labpack_end_bin(labpack_writer_t* writer)
{
    assert(writer);
    mpack_finish_bin(writer->encoder);
}

void
labpack_end_ext(labpack_writer_t* writer)
{
    assert(writer);
    mpack_finish_ext(writer->encoder);
}

void
labpack_end_type(labpack_writer_t* writer, labpack_type_t type)
{
    assert(writer);
    mpack_finish_type(writer->encoder, labpack_to_mpack_type(type));
}

