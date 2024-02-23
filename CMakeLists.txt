project(uproot)
cmake_minimum_required(VERSION 3.10)

set(LIBRARY_NAME storm)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CMakeDependentOption)

option(BUILD_SHARED_LIBS "Compile shared libraries" OFF)
option(STORM_USE_BUNDLED_LIBRARIES
    "Force use of bundled dependencies instead of system libraries."
    OFF
)


set(SRC_FILES
           stormlib/adpcm/adpcm.cpp
           stormlib/huffman/huff.cpp
           stormlib/jenkins/lookup3.c
           stormlib/lzma/C/LzFind.c
           stormlib/lzma/C/LzmaDec.c
           stormlib/lzma/C/LzmaEnc.c
           stormlib/pklib/explode.c
           stormlib/pklib/implode.c
           stormlib/sparse/sparse.cpp
           stormlib/FileStream.cpp
           stormlib/SBaseCommon.cpp
           stormlib/SBaseDumpData.cpp
           stormlib/SBaseFileTable.cpp
           stormlib/SBaseSubTypes.cpp
           stormlib/SCompression.cpp
           stormlib/SFileAddFile.cpp
           stormlib/SFileAttributes.cpp
           stormlib/SFileCompactArchive.cpp
           stormlib/SFileCreateArchive.cpp
           stormlib/SFileExtractFile.cpp
           stormlib/SFileFindFile.cpp
           stormlib/SFileGetFileInfo.cpp
           stormlib/SFileListFile.cpp
           stormlib/SFileOpenArchive.cpp
           stormlib/SFileOpenFileEx.cpp
           stormlib/SFilePatchArchives.cpp
           stormlib/SFileReadFile.cpp
           stormlib/SFileVerify.cpp
           stormlib/libtomcrypt/src/pk/rsa/rsa_verify_simple.c
           stormlib/libtomcrypt/src/misc/crypt_libc.c
)

if(MSVC)
    # This file is used to create a DLL on windows
    # Use BUILD_SHARED_LIBS to create StormLib.dll
    set(STORM_DEF_FILES
           stormlib/DllMain.def
    )
endif()

set(TOMCRYPT_FILES
           stormlib/libtomcrypt/src/hashes/hash_memory.c
           stormlib/libtomcrypt/src/hashes/md5.c
           stormlib/libtomcrypt/src/hashes/sha1.c
           stormlib/libtomcrypt/src/math/ltm_desc.c
           stormlib/libtomcrypt/src/math/multi.c
           stormlib/libtomcrypt/src/math/rand_prime.c
           stormlib/libtomcrypt/src/misc/base64_decode.c
           stormlib/libtomcrypt/src/misc/crypt_argchk.c
           stormlib/libtomcrypt/src/misc/crypt_find_hash.c
           stormlib/libtomcrypt/src/misc/crypt_find_prng.c
           stormlib/libtomcrypt/src/misc/crypt_hash_descriptor.c
           stormlib/libtomcrypt/src/misc/crypt_hash_is_valid.c
           stormlib/libtomcrypt/src/misc/crypt_ltc_mp_descriptor.c
           stormlib/libtomcrypt/src/misc/crypt_prng_descriptor.c
           stormlib/libtomcrypt/src/misc/crypt_prng_is_valid.c
           stormlib/libtomcrypt/src/misc/crypt_register_hash.c
           stormlib/libtomcrypt/src/misc/crypt_register_prng.c
           stormlib/libtomcrypt/src/misc/zeromem.c
           stormlib/libtomcrypt/src/pk/asn1/der_decode_bit_string.c
           stormlib/libtomcrypt/src/pk/asn1/der_decode_boolean.c
           stormlib/libtomcrypt/src/pk/asn1/der_decode_choice.c
           stormlib/libtomcrypt/src/pk/asn1/der_decode_ia5_string.c
           stormlib/libtomcrypt/src/pk/asn1/der_decode_integer.c
           stormlib/libtomcrypt/src/pk/asn1/der_decode_object_identifier.c
           stormlib/libtomcrypt/src/pk/asn1/der_decode_octet_string.c
           stormlib/libtomcrypt/src/pk/asn1/der_decode_printable_string.c
           stormlib/libtomcrypt/src/pk/asn1/der_decode_sequence_ex.c
           stormlib/libtomcrypt/src/pk/asn1/der_decode_sequence_flexi.c
           stormlib/libtomcrypt/src/pk/asn1/der_decode_sequence_multi.c
           stormlib/libtomcrypt/src/pk/asn1/der_decode_short_integer.c
           stormlib/libtomcrypt/src/pk/asn1/der_decode_utctime.c
           stormlib/libtomcrypt/src/pk/asn1/der_decode_utf8_string.c
           stormlib/libtomcrypt/src/pk/asn1/der_encode_bit_string.c
           stormlib/libtomcrypt/src/pk/asn1/der_encode_boolean.c
           stormlib/libtomcrypt/src/pk/asn1/der_encode_ia5_string.c
           stormlib/libtomcrypt/src/pk/asn1/der_encode_integer.c
           stormlib/libtomcrypt/src/pk/asn1/der_encode_object_identifier.c
           stormlib/libtomcrypt/src/pk/asn1/der_encode_octet_string.c
           stormlib/libtomcrypt/src/pk/asn1/der_encode_printable_string.c
           stormlib/libtomcrypt/src/pk/asn1/der_encode_sequence_ex.c
           stormlib/libtomcrypt/src/pk/asn1/der_encode_sequence_multi.c
           stormlib/libtomcrypt/src/pk/asn1/der_encode_set.c
           stormlib/libtomcrypt/src/pk/asn1/der_encode_setof.c
           stormlib/libtomcrypt/src/pk/asn1/der_encode_short_integer.c
           stormlib/libtomcrypt/src/pk/asn1/der_encode_utctime.c
           stormlib/libtomcrypt/src/pk/asn1/der_encode_utf8_string.c
           stormlib/libtomcrypt/src/pk/asn1/der_length_bit_string.c
           stormlib/libtomcrypt/src/pk/asn1/der_length_boolean.c
           stormlib/libtomcrypt/src/pk/asn1/der_length_ia5_string.c
           stormlib/libtomcrypt/src/pk/asn1/der_length_integer.c
           stormlib/libtomcrypt/src/pk/asn1/der_length_object_identifier.c
           stormlib/libtomcrypt/src/pk/asn1/der_length_octet_string.c
           stormlib/libtomcrypt/src/pk/asn1/der_length_printable_string.c
           stormlib/libtomcrypt/src/pk/asn1/der_length_sequence.c
           stormlib/libtomcrypt/src/pk/asn1/der_length_utctime.c
           stormlib/libtomcrypt/src/pk/asn1/der_sequence_free.c
           stormlib/libtomcrypt/src/pk/asn1/der_length_utf8_string.c
           stormlib/libtomcrypt/src/pk/asn1/der_length_short_integer.c
           stormlib/libtomcrypt/src/pk/ecc/ltc_ecc_map.c
           stormlib/libtomcrypt/src/pk/ecc/ltc_ecc_mul2add.c
           stormlib/libtomcrypt/src/pk/ecc/ltc_ecc_mulmod.c
           stormlib/libtomcrypt/src/pk/ecc/ltc_ecc_points.c
           stormlib/libtomcrypt/src/pk/ecc/ltc_ecc_projective_add_point.c
           stormlib/libtomcrypt/src/pk/ecc/ltc_ecc_projective_dbl_point.c
           stormlib/libtomcrypt/src/pk/pkcs1/pkcs_1_mgf1.c
           stormlib/libtomcrypt/src/pk/pkcs1/pkcs_1_oaep_decode.c
           stormlib/libtomcrypt/src/pk/pkcs1/pkcs_1_pss_decode.c
           stormlib/libtomcrypt/src/pk/pkcs1/pkcs_1_pss_encode.c
           stormlib/libtomcrypt/src/pk/pkcs1/pkcs_1_v1_5_decode.c
           stormlib/libtomcrypt/src/pk/pkcs1/pkcs_1_v1_5_encode.c
           stormlib/libtomcrypt/src/pk/rsa/rsa_exptmod.c
           stormlib/libtomcrypt/src/pk/rsa/rsa_free.c
           stormlib/libtomcrypt/src/pk/rsa/rsa_import.c
           stormlib/libtomcrypt/src/pk/rsa/rsa_make_key.c
           stormlib/libtomcrypt/src/pk/rsa/rsa_sign_hash.c
           stormlib/libtomcrypt/src/pk/rsa/rsa_verify_hash.c
)

set(TOMMATH_FILES
           stormlib/libtommath/bncore.c
           stormlib/libtommath/bn_fast_mp_invmod.c
           stormlib/libtommath/bn_fast_mp_montgomery_reduce.c
           stormlib/libtommath/bn_fast_s_mp_mul_digs.c
           stormlib/libtommath/bn_fast_s_mp_mul_high_digs.c
           stormlib/libtommath/bn_fast_s_mp_sqr.c
           stormlib/libtommath/bn_mp_2expt.c
           stormlib/libtommath/bn_mp_abs.c
           stormlib/libtommath/bn_mp_add.c
           stormlib/libtommath/bn_mp_addmod.c
           stormlib/libtommath/bn_mp_add_d.c
           stormlib/libtommath/bn_mp_and.c
           stormlib/libtommath/bn_mp_clamp.c
           stormlib/libtommath/bn_mp_clear.c
           stormlib/libtommath/bn_mp_clear_multi.c
           stormlib/libtommath/bn_mp_cmp.c
           stormlib/libtommath/bn_mp_cmp_d.c
           stormlib/libtommath/bn_mp_cmp_mag.c
           stormlib/libtommath/bn_mp_cnt_lsb.c
           stormlib/libtommath/bn_mp_copy.c
           stormlib/libtommath/bn_mp_count_bits.c
           stormlib/libtommath/bn_mp_div.c
           stormlib/libtommath/bn_mp_div_2.c
           stormlib/libtommath/bn_mp_div_2d.c
           stormlib/libtommath/bn_mp_div_3.c
           stormlib/libtommath/bn_mp_div_d.c
           stormlib/libtommath/bn_mp_dr_is_modulus.c
           stormlib/libtommath/bn_mp_dr_reduce.c
           stormlib/libtommath/bn_mp_dr_setup.c
           stormlib/libtommath/bn_mp_exch.c
           stormlib/libtommath/bn_mp_exptmod.c
           stormlib/libtommath/bn_mp_exptmod_fast.c
           stormlib/libtommath/bn_mp_expt_d.c
           stormlib/libtommath/bn_mp_exteuclid.c
           stormlib/libtommath/bn_mp_fread.c
           stormlib/libtommath/bn_mp_fwrite.c
           stormlib/libtommath/bn_mp_gcd.c
           stormlib/libtommath/bn_mp_get_int.c
           stormlib/libtommath/bn_mp_grow.c
           stormlib/libtommath/bn_mp_init.c
           stormlib/libtommath/bn_mp_init_copy.c
           stormlib/libtommath/bn_mp_init_multi.c
           stormlib/libtommath/bn_mp_init_set.c
           stormlib/libtommath/bn_mp_init_set_int.c
           stormlib/libtommath/bn_mp_init_size.c
           stormlib/libtommath/bn_mp_invmod.c
           stormlib/libtommath/bn_mp_invmod_slow.c
           stormlib/libtommath/bn_mp_is_square.c
           stormlib/libtommath/bn_mp_jacobi.c
           stormlib/libtommath/bn_mp_karatsuba_mul.c
           stormlib/libtommath/bn_mp_karatsuba_sqr.c
           stormlib/libtommath/bn_mp_lcm.c
           stormlib/libtommath/bn_mp_lshd.c
           stormlib/libtommath/bn_mp_mod.c
           stormlib/libtommath/bn_mp_mod_2d.c
           stormlib/libtommath/bn_mp_mod_d.c
           stormlib/libtommath/bn_mp_montgomery_calc_normalization.c
           stormlib/libtommath/bn_mp_montgomery_reduce.c
           stormlib/libtommath/bn_mp_montgomery_setup.c
           stormlib/libtommath/bn_mp_mul.c
           stormlib/libtommath/bn_mp_mulmod.c
           stormlib/libtommath/bn_mp_mul_2.c
           stormlib/libtommath/bn_mp_mul_2d.c
           stormlib/libtommath/bn_mp_mul_d.c
           stormlib/libtommath/bn_mp_neg.c
           stormlib/libtommath/bn_mp_n_root.c
           stormlib/libtommath/bn_mp_or.c
           stormlib/libtommath/bn_mp_prime_fermat.c
           stormlib/libtommath/bn_mp_prime_is_divisible.c
           stormlib/libtommath/bn_mp_prime_is_prime.c
           stormlib/libtommath/bn_mp_prime_miller_rabin.c
           stormlib/libtommath/bn_mp_prime_next_prime.c
           stormlib/libtommath/bn_mp_prime_rabin_miller_trials.c
           stormlib/libtommath/bn_mp_prime_random_ex.c
           stormlib/libtommath/bn_mp_radix_size.c
           stormlib/libtommath/bn_mp_radix_smap.c
           stormlib/libtommath/bn_mp_rand.c
           stormlib/libtommath/bn_mp_read_radix.c
           stormlib/libtommath/bn_mp_read_signed_bin.c
           stormlib/libtommath/bn_mp_read_unsigned_bin.c
           stormlib/libtommath/bn_mp_reduce.c
           stormlib/libtommath/bn_mp_reduce_2k.c
           stormlib/libtommath/bn_mp_reduce_2k_l.c
           stormlib/libtommath/bn_mp_reduce_2k_setup.c
           stormlib/libtommath/bn_mp_reduce_2k_setup_l.c
           stormlib/libtommath/bn_mp_reduce_is_2k.c
           stormlib/libtommath/bn_mp_reduce_is_2k_l.c
           stormlib/libtommath/bn_mp_reduce_setup.c
           stormlib/libtommath/bn_mp_rshd.c
           stormlib/libtommath/bn_mp_set.c
           stormlib/libtommath/bn_mp_set_int.c
           stormlib/libtommath/bn_mp_shrink.c
           stormlib/libtommath/bn_mp_signed_bin_size.c
           stormlib/libtommath/bn_mp_sqr.c
           stormlib/libtommath/bn_mp_sqrmod.c
           stormlib/libtommath/bn_mp_sqrt.c
           stormlib/libtommath/bn_mp_sub.c
           stormlib/libtommath/bn_mp_submod.c
           stormlib/libtommath/bn_mp_sub_d.c
           stormlib/libtommath/bn_mp_toom_mul.c
           stormlib/libtommath/bn_mp_toom_sqr.c
           stormlib/libtommath/bn_mp_toradix.c
           stormlib/libtommath/bn_mp_toradix_n.c
           stormlib/libtommath/bn_mp_to_signed_bin.c
           stormlib/libtommath/bn_mp_to_signed_bin_n.c
           stormlib/libtommath/bn_mp_to_unsigned_bin.c
           stormlib/libtommath/bn_mp_to_unsigned_bin_n.c
           stormlib/libtommath/bn_mp_unsigned_bin_size.c
           stormlib/libtommath/bn_mp_xor.c
           stormlib/libtommath/bn_mp_zero.c
           stormlib/libtommath/bn_prime_tab.c
           stormlib/libtommath/bn_reverse.c
           stormlib/libtommath/bn_s_mp_add.c
           stormlib/libtommath/bn_s_mp_exptmod.c
           stormlib/libtommath/bn_s_mp_mul_digs.c
           stormlib/libtommath/bn_s_mp_mul_high_digs.c
           stormlib/libtommath/bn_s_mp_sqr.c
           stormlib/libtommath/bn_s_mp_sub.c
)

set(BZIP2_FILES
           stormlib/bzip2/blocksort.c
           stormlib/bzip2/bzlib.c
           stormlib/bzip2/compress.c
           stormlib/bzip2/crctable.c
           stormlib/bzip2/decompress.c
           stormlib/bzip2/huffman.c
           stormlib/bzip2/randtable.c
)

set(ZLIB_FILES
           stormlib/zlib/adler32.c
           stormlib/zlib/compress.c
           stormlib/zlib/crc32.c
           stormlib/zlib/deflate.c
           stormlib/zlib/inffast.c
           stormlib/zlib/inflate.c
           stormlib/zlib/inftrees.c
           stormlib/zlib/trees.c
           stormlib/zlib/zutil.c
)

set(APP_SRC_FILES
           src/uproot.cpp
)

add_definitions(-D_7ZIP_ST -DBZ_STRICT_ANSI)
set(LINK_LIBS)

find_package(ZLIB)
if (ZLIB_FOUND AND NOT STORM_USE_BUNDLED_LIBRARIES)
	set(LINK_LIBS ${LINK_LIBS} ZLIB::ZLIB)
    add_definitions(-D__SYS_ZLIB)
else()
	set(SRC_FILES ${SRC_FILES} ${ZLIB_FILES})
endif()

find_package(BZip2)
if (BZIP2_FOUND AND NOT STORM_USE_BUNDLED_LIBRARIES)
	set(LINK_LIBS ${LINK_LIBS} BZip2::BZip2)
    add_definitions(-D__SYS_BZLIB)
else()
	set(SRC_FILES ${SRC_FILES} ${BZIP2_FILES})
endif()

if(WIN32)
    set(SRC_ADDITIONAL_FILES ${TOMCRYPT_FILES} ${TOMMATH_FILES})
	set(LINK_LIBS ${LINK_LIBS} wininet)
else()
    option(WITH_LIBTOMCRYPT "Use system LibTomCrypt library" OFF)
    if(WITH_LIBTOMCRYPT)
        include(FindPkgConfig)
        pkg_check_modules(PC_LIBTOMCRYPT libtomcrypt REQUIRED)
        find_path(LIBTOMCRYPT_INCLUDE_DIR NAMES tomcrypt.h HINTS ${PC_LIBTOMCRYPT_INCLUDE_DIRS} REQUIRED)
        find_library(LIBTOMCRYPT_LIBRARY NAMES tomcrypt HINTS ${PC_LIBTOMCRYPT_LIBRARY_DIRS} REQUIRED)
        set(LINK_LIBS ${LINK_LIBS} ${LIBTOMCRYPT_LIBRARY})
        include_directories(${LIBTOMCRYPT_INCLUDE_DIR})
    else()
        set(SRC_ADDITIONAL_FILES ${TOMCRYPT_FILES} ${TOMMATH_FILES})
    endif()
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "(Free|Net|Open)BSD")
    message(STATUS "Using BSD port")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DO_LARGEFILE=0 -Dstat64=stat -Dlstat64=lstat -Dlseek64=lseek -Doff64_t=off_t -Dfstat64=fstat -Dftruncate64=ftruncate")
endif()

add_library(${LIBRARY_NAME} ${LIB_TYPE} ${SRC_FILES} ${SRC_ADDITIONAL_FILES} ${STORM_DEF_FILES})
if(WIN32)
    set_target_properties(${LIBRARY_NAME} PROPERTIES OUTPUT_NAME "StormLib")
endif()

target_link_libraries(${LIBRARY_NAME} ${LINK_LIBS})
target_compile_definitions(${LIBRARY_NAME} INTERFACE STORMLIB_NO_AUTO_LINK) #CMake will take care of the linking
target_include_directories(${LIBRARY_NAME} PUBLIC stormlib/)
set_target_properties(${LIBRARY_NAME} PROPERTIES PUBLIC_HEADER "stormlib/StormLib.h;stormlib/StormPort.h")

add_executable(uproot ${APP_SRC_FILES})
target_link_libraries(uproot ${LIBRARY_NAME})
