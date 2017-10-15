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

typedef mpack_error_t labpack_error_t;

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
 * Initializes the MessagePack encoder begins encoding. This must be called
 * before encoding any data.
 */
LABPACK_API void labpack_writer_begin(labpack_writer_t* writer);

/**
 * Finishes the encoding. Makes the encoded data available for use.
 */
LABPACK_API void labpack_writer_end(labpack_writer_t* writer);

#ifdef __cplusplus
}
#endif

#endif
