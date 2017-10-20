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

// The MSVC compiler complains if an integer constant literal is not used for
// defining a static array size. Instead of using static const size_t
// variables, macro definitions are used.
#define EXAMPLE_BINARY_COUNT 4
#define MSGPACK_HOME_PAGE_EXAMPLE_LENGTH 18 

static labpack_writer_t* writer = NULL;
static const char* EXAMPLE_STRING = "It's like JSON, but fast and small.";
static const uint32_t EXAMPLE_STRING_LENGTH = 35;
static const char EXAMPLE_BINARY[EXAMPLE_BINARY_COUNT] = {0x00, 0x01, 0x02, 0x03};
static const uint8_t EXAMPLE_EXT_TYPE = 2;

// Example from the MessagePack home page (http://msgpack.org), i.e. '{"compact":true,"schema":0}'
static const char MSGPACK_HOME_PAGE_EXAMPLE_OUTPUT[MSGPACK_HOME_PAGE_EXAMPLE_LENGTH] = {0x82, 0xA7, 0x63, 0x6F, 0x6D, 0x70, 0x61, 0x63, 0x74, 0xC3, 0xA6, 0x73, 0x63, 0x68, 0x65, 0x6d, 0x61, 0x00};

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
    labpack_writer_begin(writer);
    mu_assert(labpack_writer_is_ok(writer), "Failed to begin writer");
    // There appears to be an issue with the mpack library on Windows 10. If no
    // data is written, the application crashes with a Debug Assertion Failed!
    // error. An [issue](https://github.com/ludocode/mpack/issues/58) has been
    // submitted to the [mpack project](https://github.com/ludocode/mpack).
    // Until the issue has been resolved, let's write some data as
    // a workaround.
    labpack_write_object_bytes(writer, MSGPACK_HOME_PAGE_EXAMPLE_OUTPUT, MSGPACK_HOME_PAGE_EXAMPLE_LENGTH);
    labpack_writer_end(writer);
}

MU_TEST(test_writer_end_works)
{
    labpack_writer_begin(writer);
    // Need to write some data to avoid assertion error on Windows. Instead of
    // the pre-encoded data used for the `begin` test, a simple integer is
    // used. This is to mimic a similar test for a wrapper library in LabVIEW.
    labpack_write_i8(writer, 127);
    labpack_writer_end(writer);
    mu_assert(labpack_writer_is_ok(writer), "Failed to end writer");
}

MU_TEST(test_writer_status_works)
{
    mu_assert(labpack_writer_status(writer) == LABPACK_STATUS_OK, "Writer status is not OK");
}

MU_TEST(test_writer_status_message_works)
{
    mu_assert_string_eq("No Error", labpack_writer_status_message(writer));
}

MU_TEST(test_writer_is_ok_works)
{
    mu_assert(labpack_writer_is_ok(writer), "Writer is not OK");
}

MU_TEST(test_writer_is_error_works)
{
    mu_assert(!labpack_writer_is_error(writer), "Writer is unexpectedly OK");
}

MU_TEST(test_writer_buffer_size_works)
{
    labpack_writer_begin(writer);
    labpack_write_object_bytes(writer, MSGPACK_HOME_PAGE_EXAMPLE_OUTPUT, MSGPACK_HOME_PAGE_EXAMPLE_LENGTH);
    labpack_writer_end(writer);
    size_t size = labpack_writer_buffer_size(writer);
    mu_assert(size == MSGPACK_HOME_PAGE_EXAMPLE_LENGTH, "Actual value does not match expected value");
}

MU_TEST(test_writer_buffer_size_works_without_end)
{
    labpack_writer_begin(writer);
    labpack_write_object_bytes(writer, MSGPACK_HOME_PAGE_EXAMPLE_OUTPUT, MSGPACK_HOME_PAGE_EXAMPLE_LENGTH);
    size_t size = labpack_writer_buffer_size(writer);
    mu_assert(size == 0, "Actual value does not match expected value");
    labpack_writer_end(writer);
}

MU_TEST(test_writer_buffer_data_works)
{
    labpack_writer_begin(writer);
    labpack_write_object_bytes(writer, MSGPACK_HOME_PAGE_EXAMPLE_OUTPUT, MSGPACK_HOME_PAGE_EXAMPLE_LENGTH);
    labpack_writer_end(writer);
    size_t size = labpack_writer_buffer_size(writer);
    char* buffer = malloc(sizeof(char) * size);
    labpack_writer_buffer_data(writer, buffer);
    mu_assert(!memcmp(buffer, MSGPACK_HOME_PAGE_EXAMPLE_OUTPUT, size), "Actual value does not match expected value");
    free(buffer);
}

MU_TEST(test_writer_buffer_data_errors_without_end)
{
    labpack_writer_begin(writer);
    labpack_write_object_bytes(writer, MSGPACK_HOME_PAGE_EXAMPLE_OUTPUT, MSGPACK_HOME_PAGE_EXAMPLE_LENGTH);
    char buffer[MSGPACK_HOME_PAGE_EXAMPLE_LENGTH];
    labpack_writer_buffer_data(writer, buffer);
    mu_assert(labpack_writer_is_error(writer), "Does not error when it should");
    mu_assert(labpack_writer_status(writer) == LABPACK_STATUS_ERROR_ENCODER, "Error status is not correct");
    labpack_writer_end(writer);
}

MU_TEST(test_writer_buffer_data_errors_with_null)
{
    labpack_writer_begin(writer);
    labpack_write_object_bytes(writer, MSGPACK_HOME_PAGE_EXAMPLE_OUTPUT, MSGPACK_HOME_PAGE_EXAMPLE_LENGTH);
    labpack_writer_buffer_data(writer, NULL);
    mu_assert(labpack_writer_is_error(writer), "Does not error when it should");
    mu_assert(labpack_writer_status(writer) == LABPACK_STATUS_ERROR_NULL_VALUE, "Error status is not correct");
    labpack_writer_end(writer);
}

MU_TEST(test_write_i8_works)
{
    labpack_write_i8(writer, 127);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write i8");
}

MU_TEST(test_write_i16_works)
{
    labpack_write_i16(writer, 32767);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write i16");
}

MU_TEST(test_write_i32_works)
{
    labpack_write_i32(writer, 2147483647);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write i32");
}

MU_TEST(test_write_i64_works)
{
    labpack_write_i64(writer, 2147483648);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write i64");
}

MU_TEST(test_write_int_works)
{
    labpack_write_int(writer, 123);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write int");
}

MU_TEST(test_write_u8_works)
{
    labpack_write_u8(writer, 127);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write u8");
}

MU_TEST(test_write_u16_works)
{
    labpack_write_u16(writer, 32767);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write u16");
}

MU_TEST(test_write_u32_works)
{
    labpack_write_u32(writer, 2147483647);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write u32");
}

MU_TEST(test_write_u64_works)
{
    labpack_write_u64(writer, 2147483648);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write u64");
}

MU_TEST(test_write_uint_works)
{
    labpack_write_uint(writer, 1234567890);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write uint");
}

MU_TEST(test_write_float_works)
{
    labpack_write_float(writer, 1.234567890f);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write float");
}

MU_TEST(test_write_double_works)
{
    labpack_write_double(writer, 1.234567890);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write double");
}

MU_TEST(test_write_bool_works)
{
    labpack_write_bool(writer, true);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write bool");
}

MU_TEST(test_write_true_works)
{
    labpack_write_true(writer);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write true");
}

MU_TEST(test_write_false_works)
{
    labpack_write_false(writer);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write false");
}

MU_TEST(test_write_nil_works)
{
    labpack_write_nil(writer);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write nil");
}

MU_TEST(test_write_object_bytes_works)
{
    labpack_write_object_bytes(writer, MSGPACK_HOME_PAGE_EXAMPLE_OUTPUT, MSGPACK_HOME_PAGE_EXAMPLE_LENGTH);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write object");
}

MU_TEST(test_write_object_bytes_works_with_null_data)
{
    labpack_write_object_bytes(writer, NULL, 0);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write object");
}

MU_TEST(test_write_object_bytes_errors_with_wrong_size)
{
    labpack_write_object_bytes(writer, NULL, 10);
    mu_assert(labpack_writer_is_error(writer), "Does not error when it should");
    mu_assert(labpack_writer_status(writer) == LABPACK_STATUS_ERROR_NULL_VALUE, "Error status is not correct");
}

MU_TEST(test_begin_and_end_array_works)
{
    labpack_begin_array(writer, 0);
    mu_assert(labpack_writer_is_ok(writer), "Failed to begin array");
    labpack_end_array(writer);
    mu_assert(labpack_writer_is_ok(writer), "Failed to end array");
}

MU_TEST(test_begin_and_end_map_works)
{
    labpack_begin_map(writer, 0);
    mu_assert(labpack_writer_is_ok(writer), "Failed to begin map");
    labpack_end_map(writer);
    mu_assert(labpack_writer_is_ok(writer), "Failed to end map");
}

MU_TEST(test_write_str_works)
{
    labpack_write_str(writer, EXAMPLE_STRING, EXAMPLE_STRING_LENGTH);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write string");
}

MU_TEST(test_write_str_errors_with_wrong_size)
{
    labpack_write_str(writer, NULL, EXAMPLE_STRING_LENGTH);
    mu_assert(labpack_writer_is_error(writer), "Does not error when it should");
    mu_assert(labpack_writer_status(writer) == LABPACK_STATUS_ERROR_NULL_VALUE, "Error status is not correct");
}

MU_TEST(test_write_utf8_works)
{
    labpack_write_str(writer, EXAMPLE_STRING, EXAMPLE_STRING_LENGTH);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write string");
}

MU_TEST(test_write_utf8_errors_with_wrong_size)
{
    labpack_write_str(writer, NULL, EXAMPLE_STRING_LENGTH);
    mu_assert(labpack_writer_is_error(writer), "Does not error when it should");
    mu_assert(labpack_writer_status(writer) == LABPACK_STATUS_ERROR_NULL_VALUE, "Error status is not correct");
}

MU_TEST(test_write_cstr_works)
{
    labpack_write_cstr(writer, EXAMPLE_STRING);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write string");
}

MU_TEST(test_write_cstr_errors_with_null_value)
{
    labpack_write_cstr(writer, NULL);
    mu_assert(labpack_writer_is_error(writer), "Does not error when it should");
    mu_assert(labpack_writer_status(writer) == LABPACK_STATUS_ERROR_NULL_VALUE, "Error status is not correct");
}

MU_TEST(test_write_cstr_or_nil_works)
{
    labpack_write_cstr_or_nil(writer, EXAMPLE_STRING);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write string");
}

MU_TEST(test_write_cstr_or_nil_works_with_null_value)
{
    labpack_write_cstr_or_nil(writer, NULL);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write string");
}

MU_TEST(test_write_utf8_cstr_works)
{
    labpack_write_utf8_cstr(writer, EXAMPLE_STRING);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write string");
}

MU_TEST(test_write_utf8_cstr_errors_with_null_value)
{
    labpack_write_utf8_cstr(writer, NULL);
    mu_assert(labpack_writer_is_error(writer), "Does not error when it should");
    mu_assert(labpack_writer_status(writer) == LABPACK_STATUS_ERROR_NULL_VALUE, "Error status is not correct");
}

MU_TEST(test_write_utf8_cstr_or_nil_works)
{
    labpack_write_utf8_cstr_or_nil(writer, EXAMPLE_STRING);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write string");
}

MU_TEST(test_write_utf8_cstr_or_nil_works_with_null_value)
{
    labpack_write_utf8_cstr_or_nil(writer, NULL);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write string");
}

MU_TEST(test_write_bin_works)
{
    labpack_write_bin(writer, EXAMPLE_BINARY, EXAMPLE_BINARY_COUNT);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write binary data");
}

MU_TEST(test_write_bin_works_with_null_data)
{
    labpack_write_bin(writer, NULL, 0);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write binary data");
}

MU_TEST(test_write_bin_errors_with_wrong_count)
{
    labpack_write_bin(writer, NULL, EXAMPLE_BINARY_COUNT);
    mu_assert(labpack_writer_is_error(writer), "Does not error when it should");
    mu_assert(labpack_writer_status(writer) == LABPACK_STATUS_ERROR_NULL_VALUE, "Error status is not correct");
}

MU_TEST(test_write_ext_works)
{
    labpack_write_ext(writer, EXAMPLE_EXT_TYPE, EXAMPLE_BINARY, EXAMPLE_BINARY_COUNT);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write binary data");
}

MU_TEST(test_write_ext_works_with_null_data)
{
    labpack_write_ext(writer, EXAMPLE_EXT_TYPE, NULL, 0);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write binary data");
}


MU_TEST(test_write_ext_errors_with_wrong_count)
{
    labpack_write_ext(writer, EXAMPLE_EXT_TYPE, NULL, EXAMPLE_BINARY_COUNT);
    mu_assert(labpack_writer_is_error(writer), "Does not error when it should");
    mu_assert(labpack_writer_status(writer) == LABPACK_STATUS_ERROR_NULL_VALUE, "Error status is not correct");
}

MU_TEST(test_begin_and_end_str_works)
{
    labpack_begin_str(writer, EXAMPLE_STRING_LENGTH);
    mu_assert(labpack_writer_is_ok(writer), "Failed to begin writing string in chunks");
    labpack_write_bytes(writer, EXAMPLE_STRING, EXAMPLE_STRING_LENGTH);
    labpack_end_str(writer);
    mu_assert(labpack_writer_is_ok(writer), "Failed to end writing string in chunks");
}

MU_TEST(test_begin_and_end_bin_works)
{
    labpack_begin_bin(writer, EXAMPLE_BINARY_COUNT);
    mu_assert(labpack_writer_is_ok(writer), "Failed to begin writing binary blob in chunks");
    labpack_write_bytes(writer, EXAMPLE_BINARY, EXAMPLE_BINARY_COUNT);
    labpack_end_bin(writer);
    mu_assert(labpack_writer_is_ok(writer), "Failed to end writing binary blob in chunks");
}

MU_TEST(test_begin_and_end_ext_works)
{
    labpack_begin_ext(writer, EXAMPLE_EXT_TYPE, EXAMPLE_BINARY_COUNT);
    mu_assert(labpack_writer_is_ok(writer), "Failed to begin writing extension type in chunks");
    labpack_write_bytes(writer, EXAMPLE_BINARY, EXAMPLE_BINARY_COUNT);
    labpack_end_ext(writer);
    mu_assert(labpack_writer_is_ok(writer), "Failed to end writing extension type in chunks");
}

MU_TEST(test_write_bytes_works)
{
    labpack_begin_str(writer, EXAMPLE_STRING_LENGTH);
    labpack_write_bytes(writer, EXAMPLE_STRING, EXAMPLE_STRING_LENGTH);
    mu_assert(labpack_writer_is_ok(writer), "Failed to write bytes");
    labpack_end_str(writer);
}

MU_TEST(test_write_bytes_errors_with_wrong_count)
{
    labpack_begin_str(writer, EXAMPLE_STRING_LENGTH);
    labpack_write_bytes(writer, NULL, EXAMPLE_STRING_LENGTH);
    mu_assert(labpack_writer_is_error(writer), "Succeeds when it should have failed");
    mu_assert(labpack_writer_status(writer) == LABPACK_STATUS_ERROR_NULL_VALUE, "Not correct status");
    labpack_end_str(writer);
}

MU_TEST(test_end_type_works)
{
    labpack_begin_str(writer, EXAMPLE_STRING_LENGTH);
    labpack_write_bytes(writer, EXAMPLE_STRING, EXAMPLE_STRING_LENGTH);
    labpack_end_type(writer, LABPACK_TYPE_STR);
    mu_assert(labpack_writer_is_ok(writer), "Failed to end type"); 
}

MU_TEST_SUITE(writer_create_and_destroy) 
{
    MU_RUN_TEST(test_writer_sanity_check);
	MU_RUN_TEST(test_writer_create_works);
    MU_RUN_TEST(test_writer_destroy_works);
}

MU_TEST_SUITE(writer_begin_and_end)
{
    // The explicit `void*` cast is needed to fix C4113 warnings when using the MSVC
    // compiler on Windows. They are redundant on non-MSVC compilers.
    MU_SUITE_CONFIGURE((void*)&setup, (void*)&teardown);

    MU_RUN_TEST(test_writer_begin_works);
    MU_RUN_TEST(test_writer_end_works);
}

MU_TEST_SUITE(writer_buffer)
{
    MU_SUITE_CONFIGURE((void*)&setup, (void*)&teardown);

    MU_RUN_TEST(test_writer_buffer_size_works);
    MU_RUN_TEST(test_writer_buffer_size_works_without_end);
    MU_RUN_TEST(test_writer_buffer_data_works);
    MU_RUN_TEST(test_writer_buffer_data_errors_without_end);
    MU_RUN_TEST(test_writer_buffer_data_errors_with_null);
}

MU_TEST_SUITE(writer_status)
{
    MU_SUITE_CONFIGURE((void*)&setup, (void*)&teardown);

    MU_RUN_TEST(test_writer_status_works);
    MU_RUN_TEST(test_writer_status_message_works);
    MU_RUN_TEST(test_writer_is_ok_works);
    MU_RUN_TEST(test_writer_is_error_works);
}

MU_TEST_SUITE(write_types)
{
    MU_SUITE_CONFIGURE((void*)&before_each, (void*)&after_each);

    MU_RUN_TEST(test_write_i8_works);
    MU_RUN_TEST(test_write_i16_works);
    MU_RUN_TEST(test_write_i32_works);
    MU_RUN_TEST(test_write_i64_works);
    MU_RUN_TEST(test_write_int_works);
    MU_RUN_TEST(test_write_u8_works);
    MU_RUN_TEST(test_write_u16_works);
    MU_RUN_TEST(test_write_u32_works);
    MU_RUN_TEST(test_write_u64_works);
    MU_RUN_TEST(test_write_uint_works);
    MU_RUN_TEST(test_write_float_works);
    MU_RUN_TEST(test_write_double_works);
    MU_RUN_TEST(test_write_bool_works);
    MU_RUN_TEST(test_write_true_works);
    MU_RUN_TEST(test_write_false_works);
    MU_RUN_TEST(test_write_nil_works);
    MU_RUN_TEST(test_write_object_bytes_works);
    /*MU_RUN_TEST(test_write_object_bytes_works_with_null_data);*/
    /*MU_RUN_TEST(test_write_object_bytes_errors_with_wrong_size);*/
}

MU_TEST_SUITE(arrays_and_maps)
{
    MU_SUITE_CONFIGURE((void*)&before_each, (void*)&after_each);

    MU_RUN_TEST(test_begin_and_end_array_works);
    MU_RUN_TEST(test_begin_and_end_map_works);
}

MU_TEST_SUITE(data_helpers)
{
    MU_SUITE_CONFIGURE((void*)&before_each, (void*)&after_each);

    MU_RUN_TEST(test_write_str_works);
    /*MU_RUN_TEST(test_write_str_errors_with_wrong_size);*/
    MU_RUN_TEST(test_write_utf8_works);
    /*MU_RUN_TEST(test_write_utf8_errors_with_wrong_size);*/
    MU_RUN_TEST(test_write_cstr_works);
    /*MU_RUN_TEST(test_write_cstr_errors_with_null_value);*/
    MU_RUN_TEST(test_write_cstr_or_nil_works);
    /*MU_RUN_TEST(test_write_cstr_or_nil_works_with_null_value);*/
    MU_RUN_TEST(test_write_utf8_cstr_works);
    /*MU_RUN_TEST(test_write_utf8_cstr_errors_with_null_value);*/
    MU_RUN_TEST(test_write_utf8_cstr_or_nil_works);
    /*MU_RUN_TEST(test_write_utf8_cstr_or_nil_works_with_null_value);*/
    MU_RUN_TEST(test_write_bin_works);
    // Test is commented out until a fix is available for empty writer destruction.
    /*MU_RUN_TEST(test_write_bin_works_with_null_data);*/
    /*MU_RUN_TEST(test_write_bin_errors_with_wrong_count);*/
    MU_RUN_TEST(test_write_ext_works);
    // Test is commented out until a fix is available for empty writer destruction.
    /*MU_RUN_TEST(test_write_ext_works_with_null_data);*/
    /*MU_RUN_TEST(test_write_ext_errors_with_wrong_count);*/
}

MU_TEST_SUITE(chunked_data)
{
    MU_SUITE_CONFIGURE((void*)&before_each, (void*)&after_each);

    MU_RUN_TEST(test_begin_and_end_str_works);
    MU_RUN_TEST(test_begin_and_end_bin_works);
    MU_RUN_TEST(test_begin_and_end_ext_works);
    MU_RUN_TEST(test_write_bytes_works);
    // Test is commented out until a fix is available for empty writer destruction.
    /*MU_RUN_TEST(test_write_bytes_errors_with_wrong_count);*/
    MU_RUN_TEST(test_end_type_works);
}

int 
main(int argc, char* argv[]) 
{
    MU_RUN_SUITE(writer_create_and_destroy);
    MU_RUN_SUITE(writer_begin_and_end);
    MU_RUN_SUITE(writer_buffer);
    MU_RUN_SUITE(writer_status);
    MU_RUN_SUITE(write_types);
    MU_RUN_SUITE(arrays_and_maps);
    MU_RUN_SUITE(data_helpers);
    MU_RUN_SUITE(chunked_data);
	MU_REPORT();
	return minunit_fail;
}

