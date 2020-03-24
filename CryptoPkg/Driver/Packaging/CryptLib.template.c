/** @file
  Implements the BaseCryptLib and TlsLib using the services of the EDK II Crypto
  Protocol/PPI.

  Copyright (C) Microsoft Corporation. All rights reserved.
  Copyright (c) 2019 - 2020, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Base.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseCryptLib.h>
#include <Library/TlsLib.h>
#include <Protocol/Crypto.h>

/**
  A macro used to call a non-void service in an EDK II Crypto Protocol.
  If the protocol is NULL or the service in the protocol is NULL, then a debug
  message and assert is generated and an appropriate return value is returned.

  @param  Function          Name of the EDK II Crypto Protocol service to call.
  @param  Args              The argument list to pass to Function.
  @param  ErrorReturnValue  The value to return if the protocol is NULL or the
                            service in the protocol is NULL.

**/
#define CALL_CRYPTO_SERVICE(Function, Args, ErrorReturnValue)          \
  do {                                                                 \
    EDKII_CRYPTO_PROTOCOL  *CryptoServices;                            \
                                                                       \
    CryptoServices = (EDKII_CRYPTO_PROTOCOL *)GetCryptoServices ();    \
    if (CryptoServices != NULL && CryptoServices->Function != NULL) {  \
      return (CryptoServices->Function) Args;                          \
    }                                                                  \
    CryptoServiceNotAvailable (#Function);                             \
    return ErrorReturnValue;                                           \
  } while (FALSE);

/**
  A macro used to call a void service in an EDK II Crypto Protocol.
  If the protocol is NULL or the service in the protocol is NULL, then a debug
  message and assert is generated.

  @param  Function          Name of the EDK II Crypto Protocol service to call.
  @param  Args              The argument list to pass to Function.

**/
#define CALL_VOID_CRYPTO_SERVICE(Function, Args)                       \
  do {                                                                 \
    EDKII_CRYPTO_PROTOCOL  *CryptoServices;                            \
                                                                       \
    CryptoServices = (EDKII_CRYPTO_PROTOCOL *)GetCryptoServices ();    \
    if (CryptoServices != NULL && CryptoServices->Function != NULL) {  \
      (CryptoServices->Function) Args;                                 \
      return;                                                          \
    }                                                                  \
    CryptoServiceNotAvailable (#Function);                             \
    return;                                                            \
  } while (FALSE);

/**
  Internal worker function that returns the pointer to an EDK II Crypto
  Protocol/PPI.  The layout of the PPI, DXE Protocol, and SMM Protocol are
  identical which allows the implementation of the BaseCryptLib functions that
  call through a Protocol/PPI to be shared for the PEI, DXE, and SMM
  implementations.
**/
VOID *
GetCryptoServices (
  VOID
  );

/**
  Internal worker function that prints a debug message and asserts if a crypto
  service is not available.  This should never occur because library instances
  have a dependency expression for the for the EDK II Crypto Protocol/PPI so
  a module that uses these library instances are not dispatched until the EDK II
  Crypto Protocol/PPI is available.  The only case that this function handles is
  if the EDK II Crypto Protocol/PPI installed is NULL or a function pointer in
  the EDK II Protocol/PPI is NULL.

  @param[in]  FunctionName  Null-terminated ASCII string that is the name of an
                            EDK II Crypto service.

**/
static
VOID
CryptoServiceNotAvailable (
  IN CONST CHAR8  *FunctionName
  )
{
  DEBUG ((DEBUG_ERROR, "[%a] Function %a is not available\n", gEfiCallerBaseName, FunctionName));
  ASSERT_EFI_ERROR (EFI_UNSUPPORTED);
}

// MU_CHANGE START
< !--REPLACEMENT-->
// MU_CHANGE END
