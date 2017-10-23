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

MU_TEST(test_read_u16_works)
{
    const uint16_t EXPECTED = 1;
    labpack_reader_begin(reader, "\x01", 1);
    uint16_t actual = labpack_read_u16(reader);
    labpack_reader_end(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end reader");
    mu_assert(actual == EXPECTED, ACTUAL_DOES_NOT_MATCH_EXPECTED);
}

MU_TEST(test_read_u32_works)
{
    const uint32_t EXPECTED = 1;
    labpack_reader_begin(reader, "\x01", 1);
    uint32_t actual = labpack_read_u32(reader);
    labpack_reader_end(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end reader");
    mu_assert(actual == EXPECTED, ACTUAL_DOES_NOT_MATCH_EXPECTED);
}

MU_TEST(test_read_u64_works)
{
    const uint64_t EXPECTED = 1;
    labpack_reader_begin(reader, "\x01", 1);
    uint64_t actual = labpack_read_u64(reader);
    labpack_reader_end(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end reader");
    mu_assert(actual == EXPECTED, ACTUAL_DOES_NOT_MATCH_EXPECTED);
}

MU_TEST(test_read_uint_works)
{
    const unsigned int EXPECTED = 1;
    labpack_reader_begin(reader, "\x01", 1);
    unsigned int actual = labpack_read_uint(reader);
    labpack_reader_end(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end reader");
    mu_assert(actual == EXPECTED, ACTUAL_DOES_NOT_MATCH_EXPECTED);
}

MU_TEST(test_read_i8_works)
{
    const int8_t EXPECTED = 1;
    labpack_reader_begin(reader, "\x01", 1);
    int8_t actual = labpack_read_i8(reader);
    labpack_reader_end(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end reader");
    mu_assert(actual == EXPECTED, ACTUAL_DOES_NOT_MATCH_EXPECTED);
}

MU_TEST(test_read_i16_works)
{
    const int16_t EXPECTED = 1;
    labpack_reader_begin(reader, "\x01", 1);
    int16_t actual = labpack_read_i16(reader);
    labpack_reader_end(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end reader");
    mu_assert(actual == EXPECTED, ACTUAL_DOES_NOT_MATCH_EXPECTED);
}

MU_TEST(test_read_i32_works)
{
    const int32_t EXPECTED = 1;
    labpack_reader_begin(reader, "\x01", 1);
    int32_t actual = labpack_read_i32(reader);
    labpack_reader_end(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end reader");
    mu_assert(actual == EXPECTED, ACTUAL_DOES_NOT_MATCH_EXPECTED);
}

MU_TEST(test_read_i64_works)
{
    const int64_t EXPECTED = 1;
    labpack_reader_begin(reader, "\x01", 1);
    int64_t actual = labpack_read_i64(reader);
    labpack_reader_end(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end reader");
    mu_assert(actual == EXPECTED, ACTUAL_DOES_NOT_MATCH_EXPECTED);
}

MU_TEST(test_read_int_works)
{
    const int EXPECTED = 1;
    labpack_reader_begin(reader, "\x01", 1);
    int actual = labpack_read_int(reader);
    labpack_reader_end(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end reader");
    mu_assert(actual == EXPECTED, ACTUAL_DOES_NOT_MATCH_EXPECTED);
}

MU_TEST(test_read_float_works)
{
    const float EXPECTED = 0.0f;
    labpack_reader_begin(reader, "\xca\x00\x00\x00\x00", 5);
    float actual = labpack_read_float(reader);
    labpack_reader_end(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end reader");
    mu_assert(actual == EXPECTED, ACTUAL_DOES_NOT_MATCH_EXPECTED);
}

MU_TEST(test_read_double_works)
{
    const double EXPECTED = 0.0;
    labpack_reader_begin(reader, "\xcb\x00\x00\x00\x00\x00\x00\x00\x00", 9);
    double actual = labpack_read_double(reader);
    labpack_reader_end(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end reader");
    mu_assert(actual == EXPECTED, ACTUAL_DOES_NOT_MATCH_EXPECTED);
}

MU_TEST(test_read_float_strict_works)
{
    const float EXPECTED = 0.0f;
    labpack_reader_begin(reader, "\xca\x00\x00\x00\x00", 5);
    float actual = labpack_read_float_strict(reader);
    labpack_reader_end(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end reader");
    mu_assert(actual == EXPECTED, ACTUAL_DOES_NOT_MATCH_EXPECTED);
}

MU_TEST(test_read_double_strict_works)
{
    const double EXPECTED = 0.0;
    labpack_reader_begin(reader, "\xcb\x00\x00\x00\x00\x00\x00\x00\x00", 9);
    double actual = labpack_read_double_strict(reader);
    labpack_reader_end(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end reader");
    mu_assert(actual == EXPECTED, ACTUAL_DOES_NOT_MATCH_EXPECTED);
}

MU_TEST(test_read_nil_works)
{
    labpack_reader_begin(reader, "\xc0", 1);
    labpack_read_nil(reader);
    labpack_reader_end(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end reader");
}

MU_TEST(test_read_bool_works)
{
    const bool EXPECTED = true;
    labpack_reader_begin(reader, "\xc3", 1);
    bool actual = labpack_read_bool(reader);
    labpack_reader_end(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end reader");
    mu_assert(actual == EXPECTED, ACTUAL_DOES_NOT_MATCH_EXPECTED);
}

MU_TEST(test_read_true_works)
{
    labpack_reader_begin(reader, "\xc3", 1);
    labpack_read_true(reader);
    labpack_reader_end(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end reader");
}

MU_TEST(test_read_false_works)
{
    labpack_reader_begin(reader, "\xc2", 1);
    labpack_read_false(reader);
    labpack_reader_end(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end reader");
}

MU_TEST(test_begin_and_end_map_works)
{
    const uint32_t EXPECTED = 0;
    labpack_reader_begin(reader, "\x80", 1);
    uint32_t actual = labpack_reader_begin_map(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to begin map");
    labpack_reader_end_map(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end map");
    labpack_reader_end(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end reader");
    mu_assert(actual == EXPECTED, ACTUAL_DOES_NOT_MATCH_EXPECTED);
}

MU_TEST(test_read_map_or_nil_works)
{
    const uint32_t EXPECTED = 0;
    uint32_t actual;
    labpack_reader_begin(reader, "\x80", 1);
    bool is_map = labpack_reader_begin_map_or_nil(reader, &actual);
    mu_assert(labpack_reader_is_ok(reader), "Failed to begin map");
    labpack_reader_end_map(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end map");
    labpack_reader_end(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end reader");
    mu_assert(is_map, "Map not read");
    mu_assert(actual == EXPECTED, ACTUAL_DOES_NOT_MATCH_EXPECTED);
}

MU_TEST(test_begin_and_end_array_works)
{
    const uint32_t EXPECTED = 0;
    labpack_reader_begin(reader, "\x90", 1);
    uint32_t actual = labpack_reader_begin_array(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to begin array");
    labpack_reader_end_array(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end array");
    labpack_reader_end(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end reader");
    mu_assert(actual == EXPECTED, ACTUAL_DOES_NOT_MATCH_EXPECTED);
}

MU_TEST(test_read_array_or_nil_works)
{
    const uint32_t EXPECTED = 0;
    uint32_t actual;
    labpack_reader_begin(reader, "\x90", 1);
    bool is_array = labpack_reader_begin_array_or_nil(reader, &actual);
    mu_assert(labpack_reader_is_ok(reader), "Failed to begin array");
    labpack_reader_end_array(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end array");
    labpack_reader_end(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end reader");
    mu_assert(is_array, "Array not read");
    mu_assert(actual == EXPECTED, ACTUAL_DOES_NOT_MATCH_EXPECTED);
}

MU_TEST(test_begin_and_end_str_works)
{
    const uint32_t EXPECTED = 0;
    uint32_t actual;
    labpack_reader_begin(reader, "\xa0", 1);
    actual = labpack_reader_begin_str(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to begin str");
    labpack_reader_end_str(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end str");
    labpack_reader_end(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end reader");
    mu_assert(actual == EXPECTED, ACTUAL_DOES_NOT_MATCH_EXPECTED);
}

MU_TEST(test_read_bytes_works)
{
    const char* EXPECTED = "Test";
    uint32_t count;
    labpack_reader_begin(reader, "\xa4\x54\x65\x73\x74", 5);
    count = labpack_reader_begin_str(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to begin str");
    char* actual = malloc(sizeof(char) * count);
    labpack_read_bytes(reader, actual, count);
    mu_assert(labpack_reader_is_ok(reader), "Failed to begin str");
    labpack_reader_end_str(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end str");
    labpack_reader_end(reader);
    mu_assert(labpack_reader_is_ok(reader), "Failed to end reader");
    mu_assert_string_eq(actual, EXPECTED);
    free(actual);
}

MU_TEST_SUITE(reader_create_and_destroy) 
{
    MU_RUN_TEST(test_reader_sanity_check);
	MU_RUN_TEST(test_reader_create_works);
    MU_RUN_TEST(test_reader_destroy_works);
}

MU_TEST_SUITE(reader_status) 
{
    // The explicit `void*` cast is needed to fix C4113 warnings when using the MSVC
    // compiler on Windows. They are redundant on non-MSVC compilers.
    MU_SUITE_CONFIGURE((void*)&setup, (void*)&teardown);

    MU_RUN_TEST(test_reader_status_works);
    MU_RUN_TEST(test_reader_status_message_works);
    MU_RUN_TEST(test_reader_is_ok_works);
    MU_RUN_TEST(test_reader_is_error_works);
}

MU_TEST_SUITE(reader_begin_and_end)
{
    MU_SUITE_CONFIGURE((void*)&setup, (void*)&teardown);

    MU_RUN_TEST(test_reader_begin_works);
    MU_RUN_TEST(test_reader_end_works);
}

MU_TEST_SUITE(basic_number_functions)
{
    MU_SUITE_CONFIGURE((void*)&setup, (void*)&teardown);

    MU_RUN_TEST(test_read_u8_works);
    MU_RUN_TEST(test_read_u16_works);
    MU_RUN_TEST(test_read_u32_works);
    MU_RUN_TEST(test_read_u64_works);
    MU_RUN_TEST(test_read_uint_works);
    MU_RUN_TEST(test_read_i8_works);
    MU_RUN_TEST(test_read_i16_works);
    MU_RUN_TEST(test_read_i32_works);
    MU_RUN_TEST(test_read_i64_works);
    MU_RUN_TEST(test_read_int_works);
    MU_RUN_TEST(test_read_float_works);
    MU_RUN_TEST(test_read_double_works);
    MU_RUN_TEST(test_read_float_strict_works);
    MU_RUN_TEST(test_read_double_strict_works);
}

MU_TEST_SUITE(other_basic_types)
{
    MU_SUITE_CONFIGURE((void*)&setup, (void*)&teardown);

    MU_RUN_TEST(test_read_nil_works);
    MU_RUN_TEST(test_read_bool_works);
    MU_RUN_TEST(test_read_true_works);
    MU_RUN_TEST(test_read_false_works);
} 

MU_TEST_SUITE(compound_types)
{
    MU_SUITE_CONFIGURE((void*)&setup, (void*)&teardown);

    MU_RUN_TEST(test_begin_and_end_map_works);
    MU_RUN_TEST(test_read_map_or_nil_works);
    MU_RUN_TEST(test_begin_and_end_array_works);
    MU_RUN_TEST(test_read_array_or_nil_works);
} 

MU_TEST_SUITE(string_functions)
{
    MU_SUITE_CONFIGURE((void*)&setup, (void*)&teardown);

    MU_RUN_TEST(test_begin_and_end_str_works);
    MU_RUN_TEST(test_read_bytes_works);
} 

int 
main(int argc, char* argv[]) 
{
    MU_RUN_SUITE(reader_create_and_destroy);
    MU_RUN_SUITE(reader_status);
    MU_RUN_SUITE(reader_begin_and_end);
    MU_RUN_SUITE(basic_number_functions);
    MU_RUN_SUITE(other_basic_types);
    MU_RUN_SUITE(compound_types);
    MU_RUN_SUITE(string_functions);
	MU_REPORT();
	return minunit_fail;
}

