find_package(OpenSSL REQUIRED)

if (OPENSSL_VERSION VERSION_LESS "3.0")
  set(OPENSSL_DEP "libssl1.1, libssl-dev")
else()
  set(OPENSSL_DEP "libssl3, libssl-dev")
endif()

find_package(benchmark REQUIRED)

