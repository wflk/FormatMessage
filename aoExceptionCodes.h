#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
typedef struct ExceptionCode {
  DWORD dwExceptionCode;
  LPWSTR sName;
  LPWSTR sDescription;
};

// http://msdn.microsoft.com/en-us/library/windows/desktop/aa363082(v=vs.85).aspx
struct ExceptionCode aoExceptionCodes[] = {
  {EXCEPTION_ACCESS_VIOLATION,          "EXCEPTION_ACCESS_VIOLATION",           L"Attempt to access memory on a virtual address for which it does not have the appropriate access."},
  {EXCEPTION_ARRAY_BOUNDS_EXCEEDED,     "EXCEPTION_ARRAY_BOUNDS_EXCEEDED",      L"Attempt to access an array element that is out of bounds."},
  {EXCEPTION_BREAKPOINT,                "EXCEPTION_BREAKPOINT",                 L"A breakpoint was encountered."},
  {EXCEPTION_DATATYPE_MISALIGNMENT,     "EXCEPTION_DATATYPE_MISALIGNMENT",      L"Attempt to access memory on a virtual address that is misaligned."},
  {EXCEPTION_FLT_DENORMAL_OPERAND,      "EXCEPTION_FLT_DENORMAL_OPERAND",       L"One of the operands in a floating-point operation is denormal (too small)."},
  {EXCEPTION_FLT_DIVIDE_BY_ZERO,        "EXCEPTION_FLT_DIVIDE_BY_ZERO",         L"Attempt to divide a floating-point value by zero."},
  {EXCEPTION_FLT_INEXACT_RESULT,        "EXCEPTION_FLT_INEXACT_RESULT",         L"The result of a floating-point operation cannot be represented exactly."},
  {EXCEPTION_FLT_INVALID_OPERATION,     "EXCEPTION_FLT_INVALID_OPERATION",      L"Non-specific floating-point exception."},
  {EXCEPTION_FLT_OVERFLOW,              "EXCEPTION_FLT_OVERFLOW",               L"The result of a floating-point operation is greater than can be stored."},
  {EXCEPTION_FLT_STACK_CHECK,           "EXCEPTION_FLT_STACK_CHECK",            L"The stack overflowed or underflowed as the result of a floating-point operation."},
  {EXCEPTION_FLT_UNDERFLOW,             "EXCEPTION_FLT_UNDERFLOW",              L"The result of a floating-point operation is smaller than can be stored."},
  {EXCEPTION_ILLEGAL_INSTRUCTION,       "EXCEPTION_ILLEGAL_INSTRUCTION",        L"Attempt to execute an invalid instruction."},
  {EXCEPTION_IN_PAGE_ERROR,             "EXCEPTION_IN_PAGE_ERROR",              L"Attempt to access memory on a page that cannot be paged-in."},
  {EXCEPTION_INT_DIVIDE_BY_ZERO,        "EXCEPTION_INT_DIVIDE_BY_ZERO",         L"Attempt to divide an integer value by zero."},
  {EXCEPTION_INT_OVERFLOW,              "EXCEPTION_INT_OVERFLOW",               L"The result of an integer operation is greater than can be stored."},
  {EXCEPTION_INVALID_DISPOSITION,       "EXCEPTION_INVALID_DISPOSITION",        L"An exception handler returned an invalid disposition to the exception dispatcher."},
  {EXCEPTION_NONCONTINUABLE_EXCEPTION,  "EXCEPTION_NONCONTINUABLE_EXCEPTION",   L"Attempt to continue execution after a noncontinuable exception occurred."},
  {EXCEPTION_PRIV_INSTRUCTION,          "EXCEPTION_PRIV_INSTRUCTION",           L"Attempt to execute a privileged instruction, which is not allowed in the current machine mode."},
  {EXCEPTION_SINGLE_STEP,               "EXCEPTION_SINGLE_STEP",                L"A trace trap or other single-instruction mechanism signaled that one instruction has been executed."},
  {EXCEPTION_STACK_OVERFLOW,            "EXCEPTION_STACK_OVERFLOW",             L"Attempt to use more memory for the stack than has been allocated."}
};

DWORD iExceptionCodes = sizeof(aoExceptionCodes) / sizeof(struct ExceptionCode);