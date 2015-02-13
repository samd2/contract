
#ifndef BOOST_CONTRACT_EXT_PP_USING_ASSERTION_NEW_NAME_HPP_
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_NEW_NAME_HPP_

#include <boost/contract/ext_/preprocessor/keyword/contract/as.hpp>

/* PRIVATE */

// Precondition: decl = (new-name) as ...`.
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NEW_NAME_YES_( \
        decl, traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_AS_REMOVE_FRONT(BOOST_PP_TUPLE_EAT(1) \
                decl), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_REM_CTOR(1, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NEW_NAME_NO_( \
        decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))

// Precondition: decl = `(,,,) ...` (in general there could be commas in leading
// parenthesis if that is not a new-name).
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NEW_NAME_CHECK_( \
        decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AS_FRONT( \
            BOOST_PP_TUPLE_EAT(0) decl), \
        BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NEW_NAME_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NEW_NAME_NO_ \
    )(decl, traits)
        
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NEW_NAME_PARSE_ARGS_(\
        decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NEW_NAME_CHECK_ \
    , \
        BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NEW_NAME_NO_ \
    )(decl, traits)

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NEW_NAME_PARSE( \
        decl_traits) \
    BOOST_PP_EXPAND( \
        BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NEW_NAME_PARSE_ARGS_ \
        decl_traits \
    )

// Expand to `new-name | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NEW_NAME(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
        BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_AUX_NEW_NAME_INDEX, \
        traits \
    )()
    
#endif // #include guard
