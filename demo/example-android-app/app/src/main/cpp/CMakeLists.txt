# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/boost/x86_64/include/boost-1_73)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/cos/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/openssl/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/poco/include)

add_library(local_crypto STATIC IMPORTED)
add_library(local_openssl STATIC IMPORTED)

add_library(local_boost_system STATIC IMPORTED)
add_library(local_boost_thread STATIC IMPORTED)

#add_library(local_poco_crypto STATIC IMPORTED)
#add_library(local_poco_foundation STATIC IMPORTED)
#add_library(local_poco_json STATIC IMPORTED)
#add_library(local_poco_net STATIC IMPORTED)
#add_library(local_poco_netssl STATIC IMPORTED)
#add_library(local_poco_util STATIC IMPORTED)
#add_library(local_poco_xml STATIC IMPORTED)

add_library(local_cossdk STATIC IMPORTED)

set_target_properties(local_crypto PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/openssl/${ANDROID_ABI}/libcrypto.a)
set_target_properties(local_openssl PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/openssl/${ANDROID_ABI}/libssl.a)

set_target_properties(local_boost_system PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/boost/${ANDROID_ABI}/lib/libboost_system-clang-darwin-mt-x64-1_73.a)
set_target_properties(local_boost_thread PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/boost/${ANDROID_ABI}/lib/libboost_thread-clang-darwin-mt-x64-1_73.a)

#set_target_properties(local_poco_crypto PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/poco/${ANDROID_ABI}/libPocoCrypto.a)
#set_target_properties(local_poco_foundation PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/poco/${ANDROID_ABI}/libPocoFoundation.a)
#set_target_properties(local_poco_json PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/poco/${ANDROID_ABI}/libPocoJSON.a)
#set_target_properties(local_poco_net PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/poco/${ANDROID_ABI}/libPocoNet.a)
#set_target_properties(local_poco_netssl PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/poco/${ANDROID_ABI}/libPocoNetSSL.a)
#set_target_properties(local_poco_util PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/poco/${ANDROID_ABI}/libPocoUtil.a)
#set_target_properties(local_poco_xml PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/poco/${ANDROID_ABI}/libPocoXML.a)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/poco/${ANDROID_ABI})

set_target_properties(local_cossdk PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/cos/lib/libcossdk.a)

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
            cos.cpp
             native-lib.cpp )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib

                        local_cossdk

#                        local_poco_crypto
#                        local_poco_foundation
#                        local_poco_json
#                        local_poco_net
#                        local_poco_netssl
#                        local_poco_util
#                        local_poco_xml
                        PocoNetSSL
                        PocoNet
                        PocoCrypto
                        PocoUtil
                        PocoJSON
                        PocoXML
                        PocoFoundation

                        local_crypto
                        local_openssl

                        stdc++

                        pthread

                        local_boost_thread
                        local_boost_system

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )