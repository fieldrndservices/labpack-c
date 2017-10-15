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
#include "labpack-private.h"

static void
labpack_writer_init(labpack_writer_t* writer)
{
    assert(writer);
    writer->encoder = malloc(sizeof(mpack_writer_t));
    if (writer->encoder == NULL) {
        writer->status = LABPACK_STATUS_ERROR_NO_MEMORY;
        return;
    }
    writer->buffer = NULL;
    writer->size = NULL;
    writer->status = LABPACK_STATUS_OK;
}

labpack_writer_t*
labpack_writer_create() 
{
    labpack_writer_t* writer = malloc(sizeof(labpack_writer_t));
    if (writer == NULL) {
        // TODO: Return static writer with error
        return NULL;
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
    writer->size = NULL;
    free(writer);
    writer = NULL;
}

int
labpack_writer_begin(labpack_writer_t* writer)
{
    if (!writer) {
        return LABPACK_FAILURE_NULL_VALUE;
    }
    mpack_writer_init_growable(writer->encoder, writer->buffer, writer->size);
    return LABPACK_SUCCESS;
}

int
labpack_writer_end(labpack_writer_t* writer)
{
    if (!writer) {
        return LABPACK_FAILURE_NULL_VALUE;
    }
    if (mpack_writer_destroy(writer->encoder) != mpack_ok) {
        /*return mpack_writer_error(writer->encoder);*/
        writer->status = LABPACK_STATUS_ERROR_ENCODER;
        return LABPACK_FAILURE;
    }
    return LABPACK_SUCCESS;
}

labpack_status_t
labpack_writer_status(labpack_writer_t* writer) 
{
    assert(writer);
    return writer->status;
}

