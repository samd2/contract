
// Test free function contracts.

#include "../aux_/oteststream.hpp"
#include "../aux_/cpcnt.hpp"
#include <boost/contract/free_function.hpp>
#include <boost/contract/oldof.hpp>
#include <boost/contract/var.hpp>
#include <boost/contract/assert.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::aux::test::oteststream out;

struct x_tag; typedef boost::contract::aux::test::cpcnt<x_tag, int> x_type;
struct y_tag; typedef boost::contract::aux::test::cpcnt<y_tag, int> y_type;

void swap(x_type& x, y_type& y) {
    boost::shared_ptr<x_type const> old_x =
            BOOST_CONTRACT_OLDOF(x_type::eval(x));
    boost::shared_ptr<y_type const> old_y =
            BOOST_CONTRACT_OLDOF(y_type::eval(y));
    boost::contract::var contract = boost::contract::free_function()
        .precondition([&] {
            out << "swap::pre" << std::endl;
            BOOST_CONTRACT_ASSERT(x.value != y.value);
        })
        .postcondition([&] {
            out << "swap::post" << std::endl;
            BOOST_CONTRACT_ASSERT(x.value == old_y->value);
            BOOST_CONTRACT_ASSERT(y.value == old_x->value);
        })
    ;
    out << "swap::body" << std::endl;
    int save_x = x.value;
    x.value = y.value;
    y.value = save_x;
}

int main() {
    std::ostringstream ok;

    x_type x; x.value = 123;
    y_type y; y.value = 456;

    out.str("");
    swap(x, y);
    BOOST_TEST_EQ(x.value, 456);
    BOOST_TEST_EQ(y.value, 123);
    ok.str("");
    ok
        << "swap::pre" << std::endl
        << "swap::body" << std::endl
        << "swap::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));

    BOOST_TEST_EQ(x.copies(), 1); BOOST_TEST_EQ(x.evals(), 1);
    BOOST_TEST_EQ(y.copies(), 1); BOOST_TEST_EQ(y.evals(), 1);

    return boost::report_errors();
}

