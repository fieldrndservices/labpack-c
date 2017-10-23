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
labpack_reader_check_decoder(labpack_reader_t* reader)
{
    mpack_error_t result = mpack_reader_error(reader->decoder);
    if (result != mpack_ok) {
        reader->status = LABPACK_STATUS_ERROR_DECODER;
        reader->status_message = mpack_error_to_string(result);
    }
}

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
    labpack_reader_reset_status(reader);
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
    uint8_t value = 0;
    if (labpack_reader_is_ok(reader)) {
        value = mpack_expect_u8(reader->decoder);
        labpack_reader_check_decoder(reader);
    }
    return value;
}

uint16_t
labpack_read_u16(labpack_reader_t* reader)
{
    assert(reader);
    uint16_t value = 0;
    if (labpack_reader_is_ok(reader)) {
        value = mpack_expect_u16(reader->decoder);
        labpack_reader_check_decoder(reader);
    }
    return value;
}

uint32_t
labpack_read_u32(labpack_reader_t* reader)
{
    assert(reader);
    uint32_t value = 0;
    if (labpack_reader_is_ok(reader)) {
        value = mpack_expect_u32(reader->decoder);
        labpack_reader_check_decoder(reader);
    }
    return value;
}

uint64_t
labpack_read_u64(labpack_reader_t* reader)
{
    assert(reader);
    uint64_t value = 0;
    if (labpack_reader_is_ok(reader)) {
        value = mpack_expect_u64(reader->decoder);
        labpack_reader_check_decoder(reader);
    }
    return value;
}

unsigned int
labpack_read_uint(labpack_reader_t* reader)
{
    assert(reader);
    unsigned int value = 0;
    if (labpack_reader_is_ok(reader)) {
        value = mpack_expect_uint(reader->decoder);
        labpack_reader_check_decoder(reader);
    }
    return value;
}

int8_t
labpack_read_i8(labpack_reader_t* reader)
{
    assert(reader);
    int8_t value = 0;
    if (labpack_reader_is_ok(reader)) {
        value = mpack_expect_i8(reader->decoder);
        labpack_reader_check_decoder(reader)
    }
    return value;
}

int16_t
labpack_read_i16(labpack_reader_t* reader)
{
    assert(reader);
    int16_t value = 0;
    if (labpack_reader_is_ok(reader)) {
        value = mpack_expect_i16(reader->decoder);
        labpack_reader_check_decoder(reader);
    }
    return value;
}

int32_t
labpack_read_i32(labpack_reader_t* reader)
{
    assert(reader);
    int32_t value = 0;
    if (labpack_reader_is_ok(reader)) {
        value = mpack_expect_i32(reader->decoder);
        labpack_reader_check_decoder(reader);
    }
    return value;
}

int64_t
labpack_read_i64(labpack_reader_t* reader)
{
    assert(reader);
    int64_t value = 0;
    if (labpack_reader_is_ok(reader)) {
        value = mpack_expect_i64(reader->decoder);
        labpack_reader_check_decoder(reader);
    }
    return value;
}

int
labpack_read_int(labpack_reader_t* reader)
{
    assert(reader);
    int value = 0;
    if (labpack_reader_is_ok(reader)) {
        value = mpack_expect_int(reader->decoder);
        labpack_reader_check_decoder(reader);
    }
    return value;
}

float
labpack_read_float(labpack_reader_t* reader)
{
    assert(reader);
    float value = 0;
    if (labpack_reader_is_ok(reader)) {
        value = mpack_expect_float(reader->decoder);
        labpack_reader_check_decoder(reader);
    }
    return value;
}

double
labpack_read_double(labpack_reader_t* reader)
{
    assert(reader);
    double value = 0;
    if (labpack_reader_is_ok(reader)) {
        value = mpack_expect_double(reader->decoder);
        labpack_reader_check_decoder(reader);
    }
    return value;
}

float
labpack_read_float_strict(labpack_reader_t* reader)
{
    assert(reader);
    float value = 0;
    if (labpack_reader_is_ok(reader)) {
        value = mpack_expect_float_strict(reader->decoder);
        labpack_reader_check_decoder(reader);
    }
    return value;
}

double
labpack_read_double_strict(labpack_reader_t* reader)
{
    assert(reader);
    double value = 0;
    if (labpack_reader_is_ok(reader)) {
        value = mpack_expect_double_strict(reader->decoder);
        labpack_reader_check_decoder(reader);
    }
    return value;
}

void
labpack_read_nil(labpack_reader_t* reader)
{
    assert(reader);
    if (labpack_reader_is_ok(reader)) {
        mpack_expect_nil(reader->decoder);
        labpack_reader_check_decoder(reader);
    }
}

bool
labpack_read_bool(labpack_reader_t* reader)
{
    assert(reader);
    bool value = false;
    if (labpack_reader_is_ok(reader)) {
        value = mpack_expect_bool(reader->decoder);
        labpack_reader_check_decoder(reader);
    }
}

void
labpack_read_true(labpack_reader_t* reader)
{
    assert(reader);
    if (labpack_reader_is_ok(reader)) {
        mpack_expect_true(reader->decoder);
        labpack_reader_check_decoder(reader);
    }
}

void
labpack_read_false(labpack_reader_t* reader)
{
    assert(reader);
    if (labpack_reader_is_ok(reader)) {
        mpack_expect_false(reader->decoder);
        labpack_reader_check_decoder(reader);
    }
}

uint32_t
labpack_reader_begin_map(labpack_reader_t* reader)
{
    assert(reader);
    uint32_t count = 0;
    if (labpack_reader_is_ok(reader)) {
        count = mpack_expect_map(reader->decoder);
        labpack_reader_check_decoder(reader);
    }
    return count;
}

bool
labpack_reader_begin_map_or_nil(labpack_reader_t* reader, uint32_t* count)
{
    assert(reader);
    bool is_map = false;
    if (labpack_reader_is_ok(reader)) {
        is_map = mpack_expect_map_or_nil(reader->decoder, count);
        labpack_reader_check_decoder(reader);
    }
    return is_map;
}

uint32_t
labpack_reader_begin_array(labpack_reader_t* reader)
{
    assert(reader);
    uint32_t count = 0;
    if (labpack_reader_is_ok(reader)) {
        count = mpack_expect_array(reader->decoder);
        labpack_reader_check_decoder(reader);
    }
    return count;
}

bool
labpack_reader_begin_array_or_nil(labpack_reader_t* reader, uint32_t* count)
{
    assert(reader);
    bool is_array = false;
    if (labpack_reader_is_ok(reader)) {
        is_array = mpack_expect_array_or_nil(reader->decoder, count);
        labpack_reader_check_decoder(reader);
    }
    return is_array;
}

// TODO: Add `end` map function
// TODO: Add `end` array function

uint32_t
labpack_reader_begin_str(labpack_reader_t* reader)
{
    assert(reader);
    uint32_t length = 0;
    if (labpack_reader_is_ok(reader)) {
        length = mpack_expect_str(reader->decoder);
        labpack_reader_check_decoder(reader);
    }
    return length;
}

void
labpack_reader_end_str(labpack_reader_t* reader)
{
    assert(reader);
    if (labpack_reader_is_ok(reader)) {
        mpack_done_str(reader->decoder);
        labpack_reader_check_decoder(reader);
    }
}

