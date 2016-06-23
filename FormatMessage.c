#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <stdio.h>
#include <Shellapi.h>
#include "aoExceptionCodes.h"
#include "aoNTStatusCodes.h"

int main(int argc, char** argv) {
  BOOL    bInformationFound = FALSE;
  DWORD   dwCode = 0;
  LPWSTR* asArgs = 0;
  LPWSTR  lpBuffer = 0;
  UINT    i;
  UINT    uSeverity, bCustomer, bReservedR, bReservedC, bReservedN, bReserved, uFacility, uStatusCode;
  UINT    uArgCount = 0;
  UINT    uExitCode = 0;

  asArgs = CommandLineToArgvW(GetCommandLine(), &uArgCount);
  if (asArgs != NULL && uArgCount == 2 && asArgs[1][0] == L'0' && asArgs[1][1] == L'x') {
    dwCode = wcstoul(asArgs[1], NULL, 16);
  } else if (asArgs != NULL && uArgCount == 2 && asArgs[1][0] >= L'0' && asArgs[1][0] <= L'9') {
    dwCode = wcstol(asArgs[1], NULL, 10);
  } else {
    wprintf(L"Usage:\r\n");
    wprintf(L"  %s {error code}\r\n", asArgs[0]);
    wprintf(L"Where:\r\n");
    wprintf(L"  error code = hresult code for which to display the error message.\r\n");
    wprintf(L"\r\n");
    uExitCode = 1;
  }
  for (i = 0; i < iExceptionCodes; i++) {
    if (dwCode == aoExceptionCodes[i].dwExceptionCode) {
      fwprintf(stdout, L"Exception %08X: %s\r\n", dwCode, aoExceptionCodes[i].sName);
      fwprintf(stdout, L"    %s\r\n", aoExceptionCodes[i].sDescription);
      bInformationFound = TRUE;
    }
  }
  for (i = 0; i < iNTStatusCodes; i++) {
    if (dwCode == aoNTStatusCodes[i].dwNTStatus) {
      fwprintf(stdout, L"NTStatus %08X: %s\r\n", dwCode, aoNTStatusCodes[i].sName);
      bInformationFound = TRUE;
    }
  }
  if (uExitCode == 0) {
    if (FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dwCode,
        0,
        (LPWSTR)&lpBuffer,
        0,
        NULL) != 0) {
      fwprintf(stdout, L"Error %08X: %s\r\n", dwCode, lpBuffer);
      LocalFree(lpBuffer);
      bInformationFound = TRUE;
    } else if (GetLastError() != ERROR_MR_MID_NOT_FOUND) {
      fwprintf(stderr, L"Cannot get message for Error 0x%08X: 0x%08X\r\n", dwCode, GetLastError());
      bInformationFound = TRUE;
      uExitCode = 1;
    }
  }
  if (!bInformationFound) {
    fwprintf(stderr, L"No information available for code 0x%08X\r\n", dwCode);
    uStatusCode = dwCode & 0xFFFF;
    uFacility   = (dwCode >> 16) & 0x7FFF;
    bReserved   = (dwCode >> 28) & 0x1;
    bCustomer   = (dwCode >> 29) & 0x1;
    uSeverity   = (dwCode >> 30) & 0x2;
    // HRESULT
    fwprintf(stderr, L"HRESULT breakdown:\r\n");
    fwprintf(stderr, L"  Status:   0x%04X\r\n", uStatusCode);
    fwprintf(stderr, L"  Facility: 0x%04X\r\n", uFacility);
    if (bReserved) fwprintf(stderr, L"  Reserved flag set\r\n");
    if (bCustomer) fwprintf(stderr, L"  Customer flag set\r\n");
    switch (uSeverity) {
      case 0: fwprintf(stderr, L"  Severity: Success\r\n"); break;
      case 1: fwprintf(stderr, L"  Severity: Informational\r\n"); break;
      case 2: fwprintf(stderr, L"  Severity: Warning\r\n"); break;
      case 3: fwprintf(stderr, L"  Severity: Error\r\n"); break;
    }
    // COM Error
    uFacility   = (dwCode >> 16) & 0x3FFF;
    bReserved   = (dwCode >> 27) & 0x1;
    bReservedN  = (dwCode >> 28) & 0x1;
    bReservedC  = (dwCode >> 29) & 0x1;
    bReservedR  = (dwCode >> 30) & 0x1;
    uSeverity   = (dwCode >> 31) & 0x1;
    fwprintf(stderr, L"COM error breakdown:\r\n");
    fwprintf(stderr, L"  Facility: 0x%04X\r\n", uFacility);
    if (bReserved) fwprintf(stderr, L"  This is a message id, not a status code\r\n");
    if (bReservedN) {
      fwprintf(stderr, L"  Mapped NT status value (see HRESULT for flags and severity)\r\n");
    } else {
      if (bReservedC) fwprintf(stderr, L"  C-flag set (unexpected - this is probably an HRESULT)\r\n");
      if (bReservedR) fwprintf(stderr, L"  R-flag set (unexpected - this is probably an HRESULT)\r\n");
      if (uSeverity) fwprintf(stderr, L"  Fail (COERROR)\r\n");
      else           fwprintf(stderr, L"  Success\r\n");
    }
  }

  return uExitCode;
}