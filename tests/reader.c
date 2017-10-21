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
#include "private.h"

static labpack_reader_t* reader = NULL;
static const char* ACTUAL_DOES_NOT_MATCH_EXPECTED = "The actual value does not match the expected value";

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

MU_TEST(test_reader_status_works)
{
    mu_assert(labpack_reader_status(reader) == LABPACK_STATUS_OK, "Reader status is not OK");
}

MU_TEST(test_reader_status_message_works)
{
    mu_assert_string_eq("No Error", labpack_reader_status_message(reader));
}

MU_TEST(test_reader_is_ok_works)
{
    mu_assert(labpack_reader_is_ok(reader), "Reader is not OK");
}

MU_TEST(test_reader_is_error_works)
{
    mu_assert(!labpack_reader_is_error(reader), "Reader is unexpectedly OK");
}

MU_TEST(test_reader_begin_works)
{
    labpack_reader_begin(reader, MSGPACK_HOME_PAGE_EXAMPLE_OUTPUT, MSGPACK_HOME_PAGE_EXAMPLE_LENGTH);
    mu_assert(labpack_reader_is_ok(reader), "Failed to begin reader");
    labpack_reader_end(reader);
}

MU_TEST(test_reader_end_works)
{
    labpack_reader_begin(reader, MSGPACK_HOME_PAGE_EXAMPLE_OUTPUT, MSGPACK_HOME_PAGE_EXAMPLE_LENGTH);
    labpack_reader_end(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end reader");
}

MU_TEST(test_read_u8_works)
{
    const uint8_t EXPECTED = 1;
    labpack_reader_begin(reader, "\x01", 1);
    uint8_t actual = labpack_read_u8(reader);
    labpack_reader_end(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end reader");
    mu_assert(actual == EXPECTED, ACTUAL_DOES_NOT_MATCH_EXPECTED);
}

MU_TEST_SUITE(reader_create_and_destroy) 
{
    MU_RUN_TEST(test_reader_sanity_check);
	MU_RUN_TEST(test_reader_create_works);
    MU_RUN_TEST(test_reader_destroy_works);
}

MU_TEST_SUITE(reader_status) 
{
    MU_SUITE_CONFIGURE((void*)&setup, (void*)&teardown);

    MU_RUN_TEST(test_reader_status_works);
    MU_RUN_TEST(test_reader_status_message_works);
    MU_RUN_TEST(test_reader_is_ok_works);
    MU_RUN_TEST(test_reader_is_error_works);
}

MU_TEST_SUITE(reader_begin_and_end)
{
    // The explicit `void*` cast is needed to fix C4113 warnings when using the MSVC
    // compiler on Windows. They are redundant on non-MSVC compilers.
    MU_SUITE_CONFIGURE((void*)&setup, (void*)&teardown);

    MU_RUN_TEST(test_reader_begin_works);
    MU_RUN_TEST(test_reader_end_works);
}

MU_TEST_SUITE(basic_number_functions)
{
    MU_SUITE_CONFIGURE((void*)&setup, (void*)&teardown);

    MU_RUN_TEST(test_read_u8_works);
}

int 
main(int argc, char* argv[]) 
{
    MU_RUN_SUITE(reader_create_and_destroy);
    MU_RUN_SUITE(reader_status);
    MU_RUN_SUITE(reader_begin_and_end);
    MU_RUN_SUITE(basic_number_functions);
	MU_REPORT();
	return minunit_fail;
}

