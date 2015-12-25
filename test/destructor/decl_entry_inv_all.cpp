
// Test all derived and base classes with entry static invariants.

#undef BOOST_CONTRACT_AUX_TEST_NO_A_INV
#undef BOOST_CONTRACT_AUX_TEST_NO_B_INV
#undef BOOST_CONTRACT_AUX_TEST_NO_C_INV
#include "decl.hpp"

#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok;
    
    a_entry_inv = true;
    b_entry_inv = true;
    c_entry_inv = true;
    {
        a aa;
        out.str("");
    }
    ok.str(""); ok // Test nothing failed.
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl
        << "a::dtor::old" << std::endl
        << "a::dtor::body" << std::endl
        << "a::static_inv" << std::endl
        << "a::dtor::post" << std::endl

        << "b::static_inv" << std::endl
        << "b::inv" << std::endl
        << "b::dtor::old" << std::endl
        << "b::dtor::body" << std::endl
        << "b::static_inv" << std::endl
        << "b::dtor::post" << std::endl
        
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "c::dtor::old" << std::endl
        << "c::dtor::body" << std::endl
        << "c::static_inv" << std::endl
        << "c::dtor::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));
    
    struct err {};
    boost::contract::set_entry_invariant_failure([&ok] (boost::contract::from) {
        BOOST_TEST(out.eq(ok.str())); // Must check before dtor throws...
        throw err(); // for testing (as dtors should never throw anyways).
    });

    a_entry_inv = false;
    b_entry_inv = true;
    c_entry_inv = true;
    try {
        {
            a aa;
            ok.str(""); ok
                << "a::static_inv" << std::endl
                << "a::inv" << std::endl // Test this failed...
            ;
            out.str("");
        }
        BOOST_TEST(false);
    } catch(err const&) {
        ok // ... then exec other dtors and check inv on throw (as dtor threw).
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "b::dtor::old" << std::endl
            << "b::dtor::body" << std::endl
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl

            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
            << "c::dtor::old" << std::endl
            << "c::dtor::body" << std::endl
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_entry_inv = true;
    b_entry_inv = false;
    c_entry_inv = true;
    try {
        {
            a aa;
            ok.str(""); ok
                << "a::static_inv" << std::endl
                << "a::inv" << std::endl
                << "a::dtor::old" << std::endl
                << "a::dtor::body" << std::endl
                << "a::static_inv" << std::endl
                << "a::dtor::post" << std::endl

                << "b::static_inv" << std::endl
                << "b::inv" << std::endl // Test this failed...
            ;
            out.str("");
        }
        BOOST_TEST(false);
    } catch(err const&) {
        ok // ... then exec other dtors and check inv on throw (as dtor threw).
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
            << "c::dtor::old" << std::endl
            << "c::dtor::body" << std::endl
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_entry_inv = true;
    b_entry_inv = true;
    c_entry_inv = false;
    try {
        {
            a aa;
            ok.str(""); ok
                << "a::static_inv" << std::endl
                << "a::inv" << std::endl
                << "a::dtor::old" << std::endl
                << "a::dtor::body" << std::endl
                << "a::static_inv" << std::endl
                << "a::dtor::post" << std::endl

                << "b::static_inv" << std::endl
                << "b::inv" << std::endl
                << "b::dtor::old" << std::endl
                << "b::dtor::body" << std::endl
                << "b::static_inv" << std::endl
                << "b::dtor::post" << std::endl
                
                << "c::static_inv" << std::endl
                << "c::inv" << std::endl // Test this failed.
            ;
            out.str("");
        }
        BOOST_TEST(false);
    } catch(err const&) {
        // ... then exec other dtors and check inv on throw (as dtor threw).
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    boost::contract::set_entry_invariant_failure([] (boost::contract::from) {
        // Testing multiple failures so dtors must not throw multiple
        // exceptions, just ignore failure and continue test program...
    });
    
    a_entry_inv = false;
    b_entry_inv = false;
    c_entry_inv = false;
    {
        a aa;
        out.str("");
    }
    ok.str(""); ok
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl // Test this failed (as all did)...
        << "a::dtor::body" << std::endl
        
        << "b::static_inv" << std::endl
        << "b::inv" << std::endl // Test this failed (as all did)...
        << "b::dtor::body" << std::endl
        
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl // Test this failed (as all did)...
        << "c::dtor::body" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}
