
#ifndef BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ADT_HPP_
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ADT_HPP_

#include <boost/preprocessor/seq/pop_front.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/pop_back.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

// Abstract Data Type (ADT) used to internally represent pp-traits.
// In theory, it is possible to change traits representation just changing
// these macros however Boost.Preprocessor docs say that pp-seq are the
// fastest (always close to random access performance because they use
// iteration instead of recursion) and largest (up to 256 elements) data
// structure so there should be no reason to change representation from pp-seq.

// WARNING: PP_TUPLE_ELEM does not handle EMPTY() elements. Therefore, it is
// necessary to always postfix decl with NIL, (NIL), etc. (for declaration
// tokens, sequences, etc.) and to never apply DONE(traits) while these are
// elements inside decl_traits = (decl, triats) 2-tuple (or other pp-tuples).

// NOTE: In this library PARSE macros are so that:
// * PARSE(...) all expand to 2-tuple `(remaining-decl, parsed-traits)`.
// * PARSE(decl) starts parsing declaration tokens (init. decl_traits).
// * PARSE(decl_seq) start parsing pp-seq of declarations (init. decl_traits).
// * PARSE(decl_traits) interim parsing of declarations (no init. decl_traits).
// Users will often only need to explicitly call the FUNC_TRAITS_PARSE and
// CLASS_TRAITS_PARSE macros directly (other PARSE macro are called internally).
// Some PARSE macros (e.g., from in aux_/) do no parse multiple traits but only
// a single trait so they do not use the PP_TRAITS macros below but just report
// trait as tokens (this is documented by these macros).

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INIT (BOOST_PP_NIL)
        
// Usage: DONE(traits) (could expand to EMPTY()).
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_DONE BOOST_PP_SEQ_POP_FRONT

// Usage: ELEM(index, traits)
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ELEM BOOST_PP_SEQ_ELEM

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PUSH_BACK(traits, trait) \
    traits (trait)

// Usage: POP_BACK(taits)
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_POP_BACK BOOST_PP_SEQ_POP_BACK

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_BACK(traits) \
    BOOST_PP_SEQ_ELEM(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(traits)), traits)

// NOTE: These DECL_TRAITS macros are provided for convenience only (but use
// them whenever possible instead of the TRAITS_INIT, TRAITS_DONE, etc. macros
// above so to make your code more readable and compact).
// These DECL_TRAITS macros cannot alter `decl` so they just pass that
// parameter throw (because the format of `decl` is up to the user, sometime
// it is a pp-seq, sometimes just tokens, etc.).

#define BOOST_CONTRACT_EXT_PP_DECL_TRAITS_AUX_INIT(decl) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INIT)

#define BOOST_CONTRACT_EXT_PP_DECL_TRAITS_AUX_DONE(decl_traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_DONE(BOOST_PP_TUPLE_ELEM(2, 1, \
                decl_traits)) \
    )

#define BOOST_CONTRACT_EXT_PP_DECL_TRAITS_AUX_PUSH_BACK(decl_trait, traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_trait), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_trait)) \
    )

#endif // #include guard
