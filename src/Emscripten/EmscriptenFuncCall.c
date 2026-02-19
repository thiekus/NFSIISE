
#include "EmscriptenUtils.h"

// There's annoying bugs that causes crash when compiling this code with optimization
// Must use -O0 only for this code

static inline int _EmInvokeFunction(EmGameFunctionRunnerContext *ctx, EmRunnerFunctionInfo *funcInfo)
{
    SDL_SemWait(ctx->semLockFunc);
    ctx->funcInfo = funcInfo;
    ctx->hasRequest = 1;
    SDL_SemPost(ctx->semSendRequest);
    SDL_SemWait(ctx->semFuncWait);
    SDL_SemPost(ctx->semLockFunc);
    return funcInfo->funcResult;
}

int EmInvokeToFunctionRunner0(void *func, int returnType)
{
    EmRunnerFunctionInfo funcInfo;
    EmGameFunctionRunnerContext *ctx = EmGetGlobalFunctionRunner();
    memset(&funcInfo, 0, sizeof(EmRunnerFunctionInfo));
    funcInfo.func = func;
    funcInfo.funcReturnType = returnType;
    funcInfo.funcArgc = 0;
    // funcInfo.funcResult = 0;
    return _EmInvokeFunction(ctx, &funcInfo);
}

int EmInvokeToFunctionRunner1(void *func, int returnType, int32_t arg0)
{
    EmRunnerFunctionInfo funcInfo;
    EmGameFunctionRunnerContext *ctx = EmGetGlobalFunctionRunner();
    memset(&funcInfo, 0, sizeof(EmRunnerFunctionInfo));
    funcInfo.func = func;
    funcInfo.funcReturnType = returnType;
    funcInfo.funcArgc = 1;
    funcInfo.funcArgs[0] = arg0;
    // funcInfo.funcResult = 0;
    return _EmInvokeFunction(ctx, &funcInfo);
}

int EmInvokeToFunctionRunner2(void *func, int returnType, int32_t arg0, int32_t arg1)
{
    EmRunnerFunctionInfo funcInfo;
    EmGameFunctionRunnerContext *ctx = EmGetGlobalFunctionRunner();
    memset(&funcInfo, 0, sizeof(EmRunnerFunctionInfo));
    funcInfo.func = func;
    funcInfo.funcReturnType = returnType;
    funcInfo.funcArgc = 2;
    funcInfo.funcArgs[0] = arg0;
    funcInfo.funcArgs[1] = arg1;
    // funcInfo.funcResult = 0;
    return _EmInvokeFunction(ctx, &funcInfo);
}

int EmInvokeToFunctionRunner3(void *func, int returnType, int32_t arg0, int32_t arg1, int32_t arg2)
{
    EmRunnerFunctionInfo funcInfo;
    EmGameFunctionRunnerContext *ctx = EmGetGlobalFunctionRunner();
    memset(&funcInfo, 0, sizeof(EmRunnerFunctionInfo));
    funcInfo.func = func;
    funcInfo.funcReturnType = returnType;
    funcInfo.funcArgc = 3;
    funcInfo.funcArgs[0] = arg0;
    funcInfo.funcArgs[1] = arg1;
    funcInfo.funcArgs[2] = arg2;
    // funcInfo.funcResult = 0;
    return _EmInvokeFunction(ctx, &funcInfo);
}

int EmInvokeToFunctionRunner4(void *func, int returnType, int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3)
{
    EmRunnerFunctionInfo funcInfo;
    EmGameFunctionRunnerContext *ctx = EmGetGlobalFunctionRunner();
    memset(&funcInfo, 0, sizeof(EmRunnerFunctionInfo));
    funcInfo.func = func;
    funcInfo.funcReturnType = returnType;
    funcInfo.funcArgc = 4;
    funcInfo.funcArgs[0] = arg0;
    funcInfo.funcArgs[1] = arg1;
    funcInfo.funcArgs[2] = arg2;
    funcInfo.funcArgs[3] = arg3;
    // funcInfo.funcResult = 0;
    return _EmInvokeFunction(ctx, &funcInfo);
}

int EmInvokeToFunctionRunner5(void *func, int returnType, int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4)
{
    EmRunnerFunctionInfo funcInfo;
    EmGameFunctionRunnerContext *ctx = EmGetGlobalFunctionRunner();
    memset(&funcInfo, 0, sizeof(EmRunnerFunctionInfo));
    funcInfo.func = func;
    funcInfo.funcReturnType = returnType;
    funcInfo.funcArgc = 5;
    funcInfo.funcArgs[0] = arg0;
    funcInfo.funcArgs[1] = arg1;
    funcInfo.funcArgs[2] = arg2;
    funcInfo.funcArgs[3] = arg3;
    funcInfo.funcArgs[4] = arg4;
    // funcInfo.funcResult = 0;
    return _EmInvokeFunction(ctx, &funcInfo);
}

int EmInvokeToFunctionRunner6(void *func, int returnType, int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4, int32_t arg5)
{
    EmRunnerFunctionInfo funcInfo;
    EmGameFunctionRunnerContext *ctx = EmGetGlobalFunctionRunner();
    memset(&funcInfo, 0, sizeof(EmRunnerFunctionInfo));
    funcInfo.func = func;
    funcInfo.funcReturnType = returnType;
    funcInfo.funcArgc = 6;
    funcInfo.funcArgs[0] = arg0;
    funcInfo.funcArgs[1] = arg1;
    funcInfo.funcArgs[2] = arg2;
    funcInfo.funcArgs[3] = arg3;
    funcInfo.funcArgs[4] = arg4;
    funcInfo.funcArgs[5] = arg5;
    // funcInfo.funcResult = 0;
    return _EmInvokeFunction(ctx, &funcInfo);
}

int EmInvokeToFunctionRunner7(void *func, int returnType, int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4, int32_t arg5, int32_t arg6)
{
    EmRunnerFunctionInfo funcInfo;
    EmGameFunctionRunnerContext *ctx = EmGetGlobalFunctionRunner();
    memset(&funcInfo, 0, sizeof(EmRunnerFunctionInfo));
    funcInfo.func = func;
    funcInfo.funcReturnType = returnType;
    funcInfo.funcArgc = 7;
    funcInfo.funcArgs[0] = arg0;
    funcInfo.funcArgs[1] = arg1;
    funcInfo.funcArgs[2] = arg2;
    funcInfo.funcArgs[3] = arg3;
    funcInfo.funcArgs[4] = arg4;
    funcInfo.funcArgs[5] = arg5;
    funcInfo.funcArgs[6] = arg6;
    // funcInfo.funcResult = 0;
    return _EmInvokeFunction(ctx, &funcInfo);
}

int EmInvokeToFunctionRunner8(void *func, int returnType, int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4, int32_t arg5, int32_t arg6, int32_t arg7)
{
    EmRunnerFunctionInfo funcInfo;
    EmGameFunctionRunnerContext *ctx = EmGetGlobalFunctionRunner();
    memset(&funcInfo, 0, sizeof(EmRunnerFunctionInfo));
    funcInfo.func = func;
    funcInfo.funcReturnType = returnType;
    funcInfo.funcArgc = 8;
    funcInfo.funcArgs[0] = arg0;
    funcInfo.funcArgs[1] = arg1;
    funcInfo.funcArgs[2] = arg2;
    funcInfo.funcArgs[3] = arg3;
    funcInfo.funcArgs[4] = arg4;
    funcInfo.funcArgs[5] = arg5;
    funcInfo.funcArgs[6] = arg6;
    funcInfo.funcArgs[7] = arg7;
    // funcInfo.funcResult = 0;
    return _EmInvokeFunction(ctx, &funcInfo);
}

int EmInvokeToFunctionRunner9(void *func, int returnType, int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4, int32_t arg5, int32_t arg6, int32_t arg7, int32_t arg8)
{
    EmRunnerFunctionInfo funcInfo;
    EmGameFunctionRunnerContext *ctx = EmGetGlobalFunctionRunner();
    memset(&funcInfo, 0, sizeof(EmRunnerFunctionInfo));
    funcInfo.func = func;
    funcInfo.funcReturnType = returnType;
    funcInfo.funcArgc = 9;
    funcInfo.funcArgs[0] = arg0;
    funcInfo.funcArgs[1] = arg1;
    funcInfo.funcArgs[2] = arg2;
    funcInfo.funcArgs[3] = arg3;
    funcInfo.funcArgs[4] = arg4;
    funcInfo.funcArgs[5] = arg5;
    funcInfo.funcArgs[6] = arg6;
    funcInfo.funcArgs[7] = arg7;
    funcInfo.funcArgs[8] = arg8;
    // funcInfo.funcResult = 0;
    return _EmInvokeFunction(ctx, &funcInfo);
}
