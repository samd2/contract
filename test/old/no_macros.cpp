
// Test old values without BOOST_CONTRACT_OLDOF macro.

#include "../aux_/oteststream.hpp"
#include "../aux_/counter.hpp"
#include <boost/contract/function.hpp>
#include <boost/contract/public_function.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/override.hpp>
#include <boost/contract/assert.hpp>
#include <boost/contract/old.hpp>
#include <boost/contract/guard.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <cassert>

boost::contract::aux::test::oteststream out;

struct i_tag; typedef boost::contract::aux::test::counter<i_tag, int> i_type;
struct j_tag; typedef boost::contract::aux::test::counter<j_tag, int> j_type;

struct b {
    virtual void swap(i_type& i, j_type& j, boost::contract::virtual_* v = 0);
};

void b::swap(i_type& i, j_type& j, boost::contract::virtual_* v) {
    boost::contract::old_ptr<i_type> old_i = boost::contract::make_old(v,
        boost::contract::copy_old(v) ?
            i_type::eval(i)
        :
            boost::contract::null_old()
    );
    boost::contract::old_ptr<j_type> old_j;
    boost::contract::guard c = boost::contract::public_function(v, this)
        .precondition([&] {
            out << "b::swap::pre" << std::endl;
            BOOST_CONTRACT_ASSERT(i.value != j.value);
        })
        .old([&] {
            out << "b::swap::old" << std::endl;
            old_j = boost::contract::make_old(v, boost::contract::copy_old(v) ?
                    j_type::eval(j) : boost::contract::null_old());
        })
        .postcondition([&] {
            out << "b::swap::post" << std::endl;
            BOOST_CONTRACT_ASSERT(i.value == old_j->value);
            BOOST_CONTRACT_ASSERT(j.value == old_i->value);
        })
    ;
    assert(false);
};

struct a
    #define BASES public b
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void swap(i_type& i, j_type& j, boost::contract::virtual_* v = 0)
            /* override */ {
        boost::contract::guard c = boost::contract::public_function<
                override_swap>(v, &a::swap, this, i, j);
    
        out << "a::swap::body" << std::endl;
        int t = i.value;
        i.value = j.value;
        j.value = t;
    }
    BOOST_CONTRACT_OVERRIDE(swap)
};

struct x_tag; typedef boost::contract::aux::test::counter<x_tag, char> x_type;
struct y_tag; typedef boost::contract::aux::test::counter<y_tag, char> y_type;

void swap(x_type& x, y_type& y) {
    boost::contract::old_ptr<x_type> old_x = boost::contract::make_old(
        boost::contract::copy_old() ?
            x_type::eval(x)
        :
            boost::contract::null_old()
    );
    boost::contract::old_ptr<y_type> old_y;
    boost::contract::guard c = boost::contract::function()
        .precondition([&] {
            out << "swap::pre" << std::endl;
            BOOST_CONTRACT_ASSERT(x.value != y.value);
        })
        .old([&] {
            out << "swap::old" << std::endl;
            old_y = boost::contract::make_old(boost::contract::copy_old() ?
                    y_type::eval(y) : boost::contract::null_old());
        })
        .postcondition([&] {
            out << "swap::post" << std::endl;
            BOOST_CONTRACT_ASSERT(x.value == old_y->value);
            BOOST_CONTRACT_ASSERT(y.value == old_x->value);
        })
    ;

    out << "swap::body" << std::endl;
    char t = x.value;
    x.value = y.value;
    y.value = t;
}

int main() {
    std::ostringstream ok;

    out.str("");
    x_type x; x.value = 'a';
    y_type y; y.value = 'b';
    swap(x, y);
    
    ok.str(""); ok
        << "swap::pre" << std::endl
        << "swap::old" << std::endl
        << "swap::body" << std::endl
        << "swap::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));
    
    BOOST_TEST_EQ(x.value, 'b');
    BOOST_TEST_EQ(x.copies(), 1);
    BOOST_TEST_EQ(x.evals(), 1);
    
    BOOST_TEST_EQ(y.value, 'a');
    BOOST_TEST_EQ(y.copies(), 1);
    BOOST_TEST_EQ(y.evals(), 1);

    a aa;
    i_type i; i.value = 1;
    j_type j; j.value = 2;
    out.str("");
    aa.swap(i, j);
    
    ok.str(""); ok
        << "b::swap::pre" << std::endl
        << "b::swap::old" << std::endl
        << "a::swap::body" << std::endl
        << "b::swap::old" << std::endl
        << "b::swap::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));
    
    BOOST_TEST_EQ(i.value, 2);
    BOOST_TEST_EQ(i.copies(), 1);
    BOOST_TEST_EQ(i.evals(), 1);
    
    BOOST_TEST_EQ(j.value, 1);
    BOOST_TEST_EQ(j.copies(), 1);
    BOOST_TEST_EQ(j.evals(), 1);

    return boost::report_errors();
}
