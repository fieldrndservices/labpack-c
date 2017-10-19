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

MU_TEST(test_version_works)
{
    mu_assert_string_eq(labpack_version(), VERSION);
}

MU_TEST(test_version_major_works)
{
    mu_assert(labpack_version_major() == VERSION_MAJOR, "Version major number does not match");
}

MU_TEST(test_version_minor_works)
{
    mu_assert(labpack_version_minor() == VERSION_MINOR, "Version minor number does not match");
}

MU_TEST(test_version_patch_works)
{
    mu_assert(labpack_version_patch() == VERSION_PATCH, "Version patch number does not match");
}

MU_TEST_SUITE(versions)
{
    MU_RUN_TEST(test_version_works);
    MU_RUN_TEST(test_version_major_works);
    MU_RUN_TEST(test_version_minor_works);
    MU_RUN_TEST(test_version_patch_works);
}

int 
main(int argc, char* argv[]) 
{
    MU_RUN_SUITE(versions);
	MU_REPORT();
	return minunit_fail;
}

