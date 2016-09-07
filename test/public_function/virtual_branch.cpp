
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Test public function subcontracting from middle branch of inheritance tree.

#include "contracts.hpp"
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok;
    
    c cc; // Test call to class at mid- inheritance tree (a base with bases).
    s_type s; s.value = "C";
    out.str("");
    result_type& r = cc.f(s);

    ok.str(""); ok
        #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
            << "d::static_inv" << std::endl
            << "d::inv" << std::endl
            << "e::static_inv" << std::endl
            << "e::inv" << std::endl
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
            << "d::f::pre" << std::endl
            << "e::f::pre" << std::endl
            << "c::f::pre" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "d::f::old" << std::endl
            << "e::f::old" << std::endl
            << "c::f::old" << std::endl
        #endif
        << "c::f::body" << std::endl
        #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
            << "d::static_inv" << std::endl
            << "d::inv" << std::endl
            << "e::static_inv" << std::endl
            << "e::inv" << std::endl
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "d::f::old" << std::endl
            << "d::f::post" << std::endl
            << "e::f::old" << std::endl
            << "e::f::post" << std::endl
            // No old call here because not a base object.
            << "c::f::post" << std::endl
        #endif
    ;
    BOOST_TEST(out.eq(ok.str()));

    #ifdef BOOST_CONTRACT_NO_POSTCONDITIONS
        #define BOOST_CONTRACT_TEST_post 0
    #else
        #define BOOST_CONTRACT_TEST_post 1
    #endif
    
    BOOST_TEST_EQ(r.value, "C");
    BOOST_TEST_EQ(s.value, "cde");
    BOOST_TEST_EQ(s.copies(),
            BOOST_PP_IIF(BOOST_CONTRACT_TEST_post, 3u, 0u));
    BOOST_TEST_EQ(s.evals(),
            BOOST_PP_IIF(BOOST_CONTRACT_TEST_post, 3u, 0u));
    BOOST_TEST_EQ(s.ctors(), s.dtors() + 1); // 1 local var.

    BOOST_TEST_EQ(cc.y.value, "cC");
    BOOST_TEST_EQ(cc.y.copies(),
            BOOST_PP_IIF(BOOST_CONTRACT_TEST_post, 1u, 0u));
    BOOST_TEST_EQ(cc.y.evals(),
            BOOST_PP_IIF(BOOST_CONTRACT_TEST_post, 1u, 0u));
    BOOST_TEST_EQ(cc.y.ctors(), cc.y.dtors() + 1); // 1 data member.
    
    BOOST_TEST_EQ(cc.t<'d'>::z.value, "dC");
    BOOST_TEST_EQ(cc.t<'d'>::z.copies(),
            BOOST_PP_IIF(BOOST_CONTRACT_TEST_post, 1u, 0u));
    BOOST_TEST_EQ(cc.t<'d'>::z.evals(),
            BOOST_PP_IIF(BOOST_CONTRACT_TEST_post, 1u, 0u));
    BOOST_TEST_EQ(cc.t<'d'>::z.ctors(), cc.t<'d'>::z.dtors() + 1); // 1 member.

    BOOST_TEST_EQ(cc.t<'e'>::z.value, "eC");
    BOOST_TEST_EQ(cc.t<'e'>::z.copies(),
            BOOST_PP_IIF(BOOST_CONTRACT_TEST_post, 1u, 0u));
    BOOST_TEST_EQ(cc.t<'e'>::z.evals(),
            BOOST_PP_IIF(BOOST_CONTRACT_TEST_post, 1u, 0u));
    BOOST_TEST_EQ(cc.t<'e'>::z.ctors(), cc.t<'e'>::z.dtors() + 1); // 1 member.

    return boost::report_errors();
}
