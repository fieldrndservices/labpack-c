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

#include "labpack-private.h"

static const char* UNKNOWN_TYPE = "Unknown type";
static const char* UNKNOWN_ERROR = "Unknown Mpack error";

mpack_type_t
labpack_to_mpack_type(labpack_type_t type)
{
    switch (type) {
        case LABPACK_TYPE_NIL:
            return mpack_type_nil;
        case LABPACK_TYPE_BOOL:
            return mpack_type_bool;
        case LABPACK_TYPE_FLOAT:
            return mpack_type_float;
        case LABPACK_TYPE_DOUBLE:
            return mpack_type_double;
        case LABPACK_TYPE_INT:
            return mpack_type_int;
        case LABPACK_TYPE_UINT:
            return mpack_type_uint;
        case LABPACK_TYPE_STR:
            return mpack_type_str;
        case LABPACK_TYPE_BIN:
            return mpack_type_bin;
        case LABPACK_TYPE_EXT:
            return mpack_type_ext;
        case LABPACK_TYPE_ARRAY:
            return mpack_type_array;
        case LABPACK_TYPE_MAP:
            return mpack_type_map;
        default:            
            assert(UNKNOWN_TYPE);
    }
    return mpack_type_nil;
}

const char*
labpack_mpack_error_message(mpack_error_t error)
{
    switch (error) {
        case mpack_ok: return "No Error";
        case mpack_error_io: return "The reader or writer failed to fill or flush, or some other file or socket error occurred.";
        case mpack_error_invalid: return "The data read is no valid MessagePack.";
        case mpack_error_type: return "The type or value range did not match what was expected by the caller.";
        case mpack_error_too_big: return "A read or write was bigger than the maximum size allowed for that operation.";
        case mpack_error_memory: return "An allocation failure occurred.";                                 
        case mpack_error_bug: return "The MPack API was used incorrectly.";
        case mpack_error_data: return "The contained data is not valid.";
        default: assert(UNKNOWN_ERROR);
    }
    return UNKNOWN_ERROR;
}

const char*
labpack_version()
{
    return VERSION;
}

unsigned int
labpack_version_major()
{
    return VERSION_MAJOR;
}

unsigned int
labpack_version_minor()
{
    return VERSION_MINOR;
}

unsigned int
labpack_version_patch()
{
    return VERSION_PATCH;
}

