#pragma once
#ifdef __cplusplus
extern "C"
{
#endif
    void mainCpp(void);
    void handleErrorCpp(void);
#ifdef __cplusplus
}
#endif

// This is how we inject C++ code into a C project, as the main function is a C function.