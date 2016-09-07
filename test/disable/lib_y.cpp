
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Test contracts in .cpp compiled to never check post/except.

// Force .cpp never check post/except.
#ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
    #define BOOST_CONTRACT_NO_POSTCONDITIONS
#endif
#ifndef BOOST_CONTRACT_NO_EXCEPTS
    #define BOOST_CONTRACT_NO_EXCEPTS
#endif

#define BOOST_CONTRACT_TEST_LIB_Y_SOURCE
#include "lib_y.hpp"

namespace lib_y_ {
    void y_body() { out("y::body\n"); }
}
