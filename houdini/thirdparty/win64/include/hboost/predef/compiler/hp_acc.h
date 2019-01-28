/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef HBOOST_PREDEF_COMPILER_HP_ACC_H
#define HBOOST_PREDEF_COMPILER_HP_ACC_H

#include <hboost/predef/version_number.h>
#include <hboost/predef/make.h>

/*`
[heading `HBOOST_COMP_HPACC`]

HP aC++ compiler.
Version number available as major, minor, and patch.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__HP_aCC`] [__predef_detection__]]

    [[`__HP_aCC`] [V.R.P]]
    ]
 */

#define HBOOST_COMP_HPACC HBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__HP_aCC)
#   if !defined(HBOOST_COMP_HPACC_DETECTION) && (__HP_aCC > 1)
#       define HBOOST_COMP_HPACC_DETECTION HBOOST_PREDEF_MAKE_10_VVRRPP(__HP_aCC)
#   endif
#   if !defined(HBOOST_COMP_HPACC_DETECTION)
#       define HBOOST_COMP_HPACC_DETECTION HBOOST_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#ifdef HBOOST_COMP_HPACC_DETECTION
#   if defined(HBOOST_PREDEF_DETAIL_COMP_DETECTED)
#       define HBOOST_COMP_HPACC_EMULATED HBOOST_COMP_HPACC_DETECTION
#   else
#       undef HBOOST_COMP_HPACC
#       define HBOOST_COMP_HPACC HBOOST_COMP_HPACC_DETECTION
#   endif
#   define HBOOST_COMP_HPACC_AVAILABLE
#   include <hboost/predef/detail/comp_detected.h>
#endif

#define HBOOST_COMP_HPACC_NAME "HP aC++"

#endif

#include <hboost/predef/detail/test.h>
HBOOST_PREDEF_DECLARE_TEST(HBOOST_COMP_HPACC,HBOOST_COMP_HPACC_NAME)

#ifdef HBOOST_COMP_HPACC_EMULATED
#include <hboost/predef/detail/test.h>
HBOOST_PREDEF_DECLARE_TEST(HBOOST_COMP_HPACC_EMULATED,HBOOST_COMP_HPACC_NAME)
#endif
