
#ifndef BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_EXPORT_HPP_
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_EXPORT_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/class_index.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/keyword.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>
#include <boost/contract/ext_/preprocessor/keyword/export.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// NOTE: The `export` keyword for templates was deprecated in C++11 but it is
// still supported here for compliance and compatibility with C++03.

/* PUBLIC */

// Expand to `export | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_EXPORT(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_EXPORT_INDEX, traits)()

// Implementation: Trailing EMPTY already put by KEYWORD1.
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_EXPORT_PARSE(decl_traits) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_PUSH_BACK( \
        BOOST_CONTRACT_EXT_PP_KEYWORD1_TRAITS_PARSE( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
            export, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_EXPORT_FRONT, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_EXPORT_REMOVE_FRONT \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#endif // #include guard
