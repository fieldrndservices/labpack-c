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

#include "minunit.h"
#include "labpack.h"

static labpack_reader_t* reader = NULL;

static void
setup()
{
    reader = labpack_reader_create();
}

static void
teardown()
{
    labpack_reader_destroy(reader);
    reader = NULL;
}

MU_TEST(test_reader_sanity_check)
{
    labpack_reader_t* reader = NULL;
    mu_assert(!reader, "Reader is not NULL");
}

MU_TEST(test_reader_create_works)
{
    labpack_reader_t* reader = labpack_reader_create();
    mu_assert(reader, "Reader is NULL");
    mu_assert(labpack_reader_status(reader) == LABPACK_STATUS_OK, "Reader is not OK");
    labpack_reader_destroy(reader);
}

MU_TEST(test_reader_destroy_works)
{
    labpack_reader_t* reader = labpack_reader_create();
    labpack_reader_destroy(reader);
}

MU_TEST_SUITE(reader_create_and_destroy) 
{
    MU_RUN_TEST(test_reader_sanity_check);
	MU_RUN_TEST(test_reader_create_works);
    MU_RUN_TEST(test_reader_destroy_works);
}

int 
main(int argc, char* argv[]) 
{
    MU_RUN_SUITE(reader_create_and_destroy);
	MU_REPORT();
	return minunit_fail;
}

