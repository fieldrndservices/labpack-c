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

static labpack_writer_t* writer = NULL;

static void
setup()
{
    writer = labpack_writer_create();
}

static void
teardown()
{
    labpack_writer_destroy(writer);
    writer = NULL;
}

static void
before_each()
{
    setup();
    labpack_writer_begin(writer);
}

static void
after_each()
{
    labpack_writer_end(writer);
    teardown();
}

MU_TEST(test_writer_sanity_check)
{
    labpack_writer_t* writer = NULL;
    mu_assert(!writer, "Writer is not NULL");
}

MU_TEST(test_writer_create_works)
{
    labpack_writer_t* writer = labpack_writer_create();
    mu_assert(writer, "Writer is NULL");
    mu_assert(labpack_writer_status(writer) == LABPACK_STATUS_OK, "Writer is not OK");
    labpack_writer_destroy(writer);
}

MU_TEST(test_writer_destroy_works)
{
    labpack_writer_t* writer = labpack_writer_create();
    labpack_writer_destroy(writer);
}

MU_TEST(test_writer_begin_works)
{
    int return_value = labpack_writer_begin(writer);
    mu_assert(return_value == LABPACK_SUCCESS, "Failed to begin writer");
    mu_assert(labpack_writer_status(writer) == LABPACK_STATUS_OK, "Writer is not OK");
    labpack_writer_end(writer);
}

MU_TEST(test_writer_end_works)
{
    labpack_writer_begin(writer);
    int return_value = labpack_writer_end(writer);
    mu_assert(return_value == LABPACK_SUCCESS, "Failed to end writer");
    mu_assert(labpack_writer_status(writer) == LABPACK_STATUS_OK, "Writer is not OK");
}

MU_TEST(test_write_i8_works)
{
    int return_value = labpack_write_i8(writer, 127);
    mu_assert(return_value == LABPACK_SUCCESS, "Failed to write i8");
    mu_assert(labpack_writer_status(writer) == LABPACK_STATUS_OK, "Writer is not OK");
}

MU_TEST_SUITE(writer_create_and_destroy) 
{
    MU_RUN_TEST(test_writer_sanity_check);
	MU_RUN_TEST(test_writer_create_works);
    MU_RUN_TEST(test_writer_destroy_works);
}

MU_TEST_SUITE(writer_begin_and_end)
{
    MU_SUITE_CONFIGURE(&setup, &teardown);

    MU_RUN_TEST(test_writer_begin_works);
    MU_RUN_TEST(test_writer_end_works);
}

MU_TEST_SUITE(write_types)
{
    MU_SUITE_CONFIGURE(&before_each, &after_each);

    MU_RUN_TEST(test_write_i8_works);
}

int 
main(int argc, char* argv[]) 
{
	MU_RUN_SUITE(writer_create_and_destroy);
	MU_RUN_SUITE(writer_begin_and_end);
	MU_RUN_SUITE(write_types);
	MU_REPORT();
	return minunit_fail;
}

