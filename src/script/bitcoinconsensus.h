// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Testcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef Testcoin_TestcoinCONSENSUS_H
#define Testcoin_TestcoinCONSENSUS_H

#if defined(BUILD_Testcoin_INTERNAL) && defined(HAVE_CONFIG_H)
#include "config/Testcoin-config.h"
  #if defined(_WIN32)
    #if defined(DLL_EXPORT)
      #if defined(HAVE_FUNC_ATTRIBUTE_DLLEXPORT)
        #define EXPORT_SYMBOL __declspec(dllexport)
      #else
        #define EXPORT_SYMBOL
      #endif
    #endif
  #elif defined(HAVE_FUNC_ATTRIBUTE_VISIBILITY)
    #define EXPORT_SYMBOL __attribute__ ((visibility ("default")))
  #endif
#elif defined(MSC_VER) && !defined(STATIC_LIBTestcoinCONSENSUS)
  #define EXPORT_SYMBOL __declspec(dllimport)
#endif

#ifndef EXPORT_SYMBOL
  #define EXPORT_SYMBOL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define TestcoinCONSENSUS_API_VER 0

typedef enum Testcoinconsensus_error_t
{
    Testcoinconsensus_ERR_OK = 0,
    Testcoinconsensus_ERR_TX_INDEX,
    Testcoinconsensus_ERR_TX_SIZE_MISMATCH,
    Testcoinconsensus_ERR_TX_DESERIALIZE,
} Testcoinconsensus_error;

/** Script verification flags */
enum
{
    Testcoinconsensus_SCRIPT_FLAGS_VERIFY_NONE      = 0,
    Testcoinconsensus_SCRIPT_FLAGS_VERIFY_P2SH      = (1U << 0), // evaluate P2SH (BIP16) subscripts
};

/// Returns 1 if the input nIn of the serialized transaction pointed to by
/// txTo correctly spends the scriptPubKey pointed to by scriptPubKey under
/// the additional constraints specified by flags.
/// If not NULL, err will contain an error/success code for the operation
EXPORT_SYMBOL int Testcoinconsensus_verify_script(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    unsigned int nIn, unsigned int flags, Testcoinconsensus_error* err);

EXPORT_SYMBOL unsigned int Testcoinconsensus_version();

#ifdef __cplusplus
} // extern "C"
#endif

#undef EXPORT_SYMBOL

#endif // Testcoin_TestcoinCONSENSUS_H
