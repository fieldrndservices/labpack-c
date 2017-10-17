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

#ifndef LABPACK_H
#define LABPACK_H

#include "mpack.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LABPACK_API
#  ifdef _WIN32
#     if defined(LABPACK_BUILD_SHARED) /* build dll */
#         define LABPACK_API __declspec(dllexport)
#     elif !defined(LABPACK_BUILD_STATIC) /* use dll */
#         define LABPACK_API __declspec(dllimport)
#     else /* static library */
#         define LABPACK_API
#     endif
#  else
#     if __GNUC__ >= 4
#         define LABPACK_API __attribute__((visibility("default")))
#     else
#         define LABPACK_API
#     endif
#  endif
#endif

/**
 * A MessagePack encoder.
 */
typedef struct _labpack_writer labpack_writer_t;

/**
 * Status
 */
typedef enum _labpack_status {
    LABPACK_STATUS_OK,

    LABPACK_STATUS_ERROR_OUT_OF_MEMORY,
    LABPACK_STATUS_ERROR_NULL_VALUE,
    LABPACK_STATUS_ERROR_ENCODER
} labpack_status_t;

/**
 * Gets an integer representation of the status. Errors are negative values,
 * warnings are positive values, and zero (0) is no error or warning, i.e.
 * "OK".
 */
LABPACK_API int labpack_status_code(labpack_status_t status);

/**
 * Gets a string representation of the status.
 */
LABPACK_API const char* labpack_status_string(labpack_status_t status);

/**
 * Creates a MessagePack encoder. This allocates memory, and to prevent
 * a memory leak, the <code>labpack_writer_destroy</code> function should be
 * used to free the memory.
 */
LABPACK_API labpack_writer_t* labpack_writer_create();

/**
 * Destroys (frees) a MessagePack encoder. Frees the memory allocated during
 * creation.
 */
LABPACK_API void labpack_writer_destroy(labpack_writer_t* writer);

/**
 * Gets the current status of the MessagePack encoder.
 */
LABPACK_API labpack_status_t labpack_writer_status(labpack_writer_t* writer);

/**
 * Gets the current status message of the MessagePack encoder.
 */
LABPACK_API const char* labpack_writer_status_message(labpack_writer_t* writer);

/**
 * Returns <code>true</code> if the MessagePack encoder is OK. If an error has
 * occurred, then it returns <code>false</code>.
 */
LABPACK_API bool labpack_writer_is_ok(labpack_writer_t* writer);

/**
 * Returns <code>true</code> if an error has occurred with the MessagePack
 * encoder. Otherwise, it returns <code>false</code>.
 *
 * The <code>labpack_writer_status</code> and
 * <code>labpack_writer_status_message</code> should be used to determine the
 * cause of an error if one has occurred.
 */
LABPACK_API bool labpack_writer_is_error(labpack_writer_t* writer);

/**
 * Initializes the MessagePack encoder begins encoding. This must be called
 * before encoding any data. This also clears any errors and resets the status.
 */
LABPACK_API void labpack_writer_begin(labpack_writer_t* writer);

/**
 * Finishes the encoding. Makes the encoded data available for use.
 */
LABPACK_API void labpack_writer_end(labpack_writer_t* writer);

/**
 * Gets the number of bytes currently stored in the internal buffer after
 * encoding. In other words, gets the length in bytes of the encoded
 * MessagePack data.
 */
LABPACK_API size_t labpack_writer_buffer_size(labpack_writer_t* writer);

/**
 * Writes a signed 8-bit integer to the encoder's MessagePack data buffer.
 */
LABPACK_API void labpack_write_i8(labpack_writer_t* writer, int8_t value);

/**
 * Writes a signed 16-bit integer to the encoder's MessagePack data buffer.
 */
LABPACK_API void labpack_write_i16(labpack_writer_t* writer, int16_t value);

/**
 * Writes a signed 32-bit integer to the encoder's MessagePack data buffer.
 */
LABPACK_API void labpack_write_i32(labpack_writer_t* writer, int32_t value);

/**
 * Writes a signed 64-bit integer to the encoder's MessagePack data buffer.
 */
LABPACK_API void labpack_write_i64(labpack_writer_t* writer, int64_t value);

/**
 * Writes a signed integer as compactly as possible to the encoder's
 * MessagePack data buffer.
 */
LABPACK_API void labpack_write_int(labpack_writer_t* writer, int64_t value);

/**
 * Writes an unsigned 8-bit integer to the encoder's MessagePack data buffer.
 */
LABPACK_API void labpack_write_u8(labpack_writer_t* writer, uint8_t value);

/**
 * Writes an unsigned 16-bit integer to the encoder's MessagePack data buffer.
 */
LABPACK_API void labpack_write_u16(labpack_writer_t* writer, uint16_t value);

/**
 * Writes an unsigned 32-bit integer to the encoder's MessagePack data buffer.
 */
LABPACK_API void labpack_write_u32(labpack_writer_t* writer, uint32_t value);

/**
 * Writes an unsigned 64-bit integer to the encoder's MessagePack data buffer.
 */
LABPACK_API void labpack_write_u64(labpack_writer_t* writer, uint64_t value);

/**
 * Writes an unsigned integer to the encoder's MessagePack data buffer.
 */
LABPACK_API void labpack_write_uint(labpack_writer_t* writer, uint64_t value);

/**
 * Writes a float to the encoder's MessagePack data buffer.
 */
LABPACK_API void labpack_write_float(labpack_writer_t* writer, float value);

/**
 * Writes a double to the encoder's MessagePack data buffer.
 */
LABPACK_API void labpack_write_double(labpack_writer_t* writer, double value);

#ifdef __cplusplus
}
#endif

#endif

