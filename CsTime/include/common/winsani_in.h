#if _MSC_VER >= 1500 // MSVC++ 9.0 (Visual Studio 2008)
#pragma push_macro("ARRAYSIZE")
#ifdef ARRAYSIZE
#undef ARRAYSIZE
#endif
#define SptiteHandle_t WINDOWS_SptiteHandle_t
#endif
