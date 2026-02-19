
#ifndef EMSCRIPTENUTILS_H
#define EMSCRIPTENUTILS_H

#include <emscripten.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_mutex.h>

typedef void (*EmGameEntryPointFunc)();

typedef struct
{
    int done;
    EmGameEntryPointFunc func;
    SDL_sem *sem;
} EmGameWorkerContext;

typedef void (*EmRunnerVoidFunc0)();
typedef void (*EmRunnerVoidFunc1)(int32_t);
typedef void (*EmRunnerVoidFunc2)(int32_t, int32_t);
typedef void (*EmRunnerVoidFunc3)(int32_t, int32_t, int32_t);
typedef void (*EmRunnerVoidFunc4)(int32_t, int32_t, int32_t, int32_t);
typedef void (*EmRunnerVoidFunc5)(int32_t, int32_t, int32_t, int32_t, int32_t);
typedef void (*EmRunnerVoidFunc6)(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
typedef void (*EmRunnerVoidFunc7)(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
typedef void (*EmRunnerVoidFunc8)(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
typedef void (*EmRunnerVoidFunc9)(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);

typedef int32_t (*EmRunnerInt32Func0)();
typedef int32_t (*EmRunnerInt32Func1)(int32_t);
typedef int32_t (*EmRunnerInt32Func2)(int32_t, int32_t);
typedef int32_t (*EmRunnerInt32Func3)(int32_t, int32_t, int32_t);
typedef int32_t (*EmRunnerInt32Func4)(int32_t, int32_t, int32_t, int32_t);
typedef int32_t (*EmRunnerInt32Func5)(int32_t, int32_t, int32_t, int32_t, int32_t);
typedef int32_t (*EmRunnerInt32Func6)(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
typedef int32_t (*EmRunnerInt32Func7)(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
typedef int32_t (*EmRunnerInt32Func8)(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
typedef int32_t (*EmRunnerInt32Func9)(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);

typedef struct
{
    void *func;
    int funcReturnType; // 0 = void, 1 = int32_t
    int32_t funcResult;
    int32_t funcArgc;
    int32_t funcArgs[9];
} EmRunnerFunctionInfo;

#define EM_FUNC_RETURN_TYPE_VOID  0
#define EM_FUNC_RETURN_TYPE_INT32 1

#define EM_MIN_TICK_DELAY 5
#define EM_MAX_TICK_DELAY 100

typedef struct
{
    SDL_sem* semFuncWait;
    SDL_sem* semLockFunc;
    SDL_sem* semSendRequest;
    int hasRequest;
    int restartLoop;
    int dynamicTickDelay;
    Uint64 tickDelay;
    int currentFrameCount;
    EmRunnerFunctionInfo* funcInfo;

} EmGameFunctionRunnerContext;

typedef struct
{
    EmGameFunctionRunnerContext* runnerCtx;
    EmGameWorkerContext* workerCtx;
    Uint64 startAudioTick;
    int audioLocked;
} EmMainLoopContext;

void* EmRunGameWorker(EmGameEntryPointFunc entryPointFunc);
int EmCheckGameWorkerStatus(EmGameWorkerContext *ctx);
void EmFreeGameWorker(EmGameWorkerContext *ctx);

void* EmInitFunctionRunner();
EmGameFunctionRunnerContext *EmGetGlobalFunctionRunner();
void EmSetGlobalFunctionRunner(EmGameFunctionRunnerContext *ctx);
void EmPeekFunctionRunner(EmGameFunctionRunnerContext *ctx);
void EmFreeFunctionRunner(EmGameFunctionRunnerContext *ctx);

void EmRestartLoopForFunctionRunner();
int EmInvokeToFunctionRunner0(void *func, int returnType);
int EmInvokeToFunctionRunner1(void *func, int returnType, int32_t arg0);
int EmInvokeToFunctionRunner2(void *func, int returnType, int32_t arg0, int32_t arg1);
int EmInvokeToFunctionRunner3(void *func, int returnType, int32_t arg0, int32_t arg1, int32_t arg2);
int EmInvokeToFunctionRunner4(void *func, int returnType, int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3);
int EmInvokeToFunctionRunner5(void *func, int returnType, int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4);
int EmInvokeToFunctionRunner6(void *func, int returnType, int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4, int32_t arg5);
int EmInvokeToFunctionRunner7(void *func, int returnType, int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4, int32_t arg5, int32_t arg6);
int EmInvokeToFunctionRunner8(void *func, int returnType, int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4, int32_t arg5, int32_t arg6, int32_t arg7);
int EmInvokeToFunctionRunner9(void *func, int returnType, int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4, int32_t arg5, int32_t arg6, int32_t arg7, int32_t arg8);

int EmIsAssetsLoaded();
int EmGetAssetsProgressPercent();

int EmInvokeGameEntryPoint(void* entryPointFunc);

#endif // EMSCRIPTENUTILS_H
