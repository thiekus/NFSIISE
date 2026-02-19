
#include <strings.h>
#include <math.h>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_mutex.h>
#ifdef OPENGL1X
#define USE_GL4ES
#include <gl4esinit.h>
#endif

#ifdef MODULARIZE
#define MODULE_NAME "NFS2SEGame"
#else
#define MODULE_NAME "Module"
#endif

#include "EmscriptenUtils.h"
#include "EmscriptenGLShim.h"

static EmGameFunctionRunnerContext *_g_FunctionRunnerCtx;

static int _EmGameWorkerThread(void *args)
{
    EmGameWorkerContext *ctx = (EmGameWorkerContext*)args;
    SDL_SemWait(ctx->sem);

    // Wait assets to fully loaded
    printf("Waiting assets to load...\n");
    int lastPercent = -1;
    while (!EmIsAssetsLoaded()) {
        int percent = EmGetAssetsProgressPercent();
        if ((percent >= 0) && (percent / 10 != lastPercent)) {
            printf("Unpacking assets %d%%\n", percent);
            lastPercent = percent / 10;
        }
        SDL_Delay(EM_MIN_TICK_DELAY);
    }

    // Run game
    (*(EmGameEntryPointFunc)(ctx->func))();

    // Done
    ctx->done = 1;
    SDL_SemPost(ctx->sem);
    return 0;
}

void* EmRunGameWorker(EmGameEntryPointFunc entryPointFunc)
{
    EmGameWorkerContext *ctx = (EmGameWorkerContext *)malloc(sizeof(EmGameWorkerContext));
    ctx->done = 0;
    ctx->func = entryPointFunc;
    ctx->sem = SDL_CreateSemaphore(1);
    SDL_Thread *sdl_thread = SDL_CreateThread(_EmGameWorkerThread, NULL, ctx);
    if (!sdl_thread) {
        printf("Spawing thread error %s\n", SDL_GetError());
        free(ctx);
        return NULL;
    }
    SDL_DetachThread(sdl_thread);
    return ctx;
}

int EmCheckGameWorkerStatus(EmGameWorkerContext *ctx)
{
    if (!ctx)
        return 1;
    if (!ctx->done) {
        if (SDL_SemValue(ctx->sem) == 0)
            return 0;
    }
    return ctx->done;
}

void EmFreeGameWorker(EmGameWorkerContext *ctx)
{
    if (!ctx)
        return;
    SDL_DestroySemaphore(ctx->sem);
    free(ctx);
}

void* EmInitFunctionRunner()
{
    EmGameFunctionRunnerContext *ctx = (EmGameFunctionRunnerContext*)malloc(sizeof(EmGameFunctionRunnerContext));
    memset(ctx, 0, sizeof(EmGameFunctionRunnerContext));
    ctx->semFuncWait = SDL_CreateSemaphore(0);
    ctx->semLockFunc = SDL_CreateSemaphore(1);
    ctx->semSendRequest = SDL_CreateSemaphore(0);
    // At this time, only Firefox which able put maximum delay same as frame time to increase overall FPS due to it's audio thread design.
    // In Chromium based browser, this maximum dynamic tick delay introduces audio issues (like popping) if per loop tick higher than 5ms.
    // This because web browser audioContext only can be created by main thread, thus why this depend to loop time.
    // Disable this and stick to lowest max tick delay may significantly drop FPS, but better than hear unbearable broken audio.
    // Possibly audio is tied to game 64fps max (roughly 5.55ms of delay), although in reality it's run on independent thread.
    int isFirefox = EM_ASM_INT({return navigator.userAgent.indexOf("Firefox") != -1;});
    ctx->dynamicTickDelay = isFirefox ? 1 : 0;
    ctx->tickDelay = EM_MIN_TICK_DELAY;
    ctx->funcInfo = NULL;
    return ctx;
}

EmGameFunctionRunnerContext *EmGetGlobalFunctionRunner()
{
    return _g_FunctionRunnerCtx;
}

void EmSetGlobalFunctionRunner(EmGameFunctionRunnerContext *ctx)
{
    _g_FunctionRunnerCtx = ctx;
}

static inline int _EmFunctionRunnerCallInt32(EmRunnerFunctionInfo *funcInfo)
{
    void *func = funcInfo->func;
    int32_t result = 0;
    int32_t *arg = funcInfo->funcArgs;
    switch (funcInfo->funcArgc) {
        case 0:
            result = (*(EmRunnerInt32Func0)(func))();
            break;
        case 1:
            result = (*(EmRunnerInt32Func1)(func))(arg[0]);
            break;
        case 2:
            result = (*(EmRunnerInt32Func2)(func))(arg[0], arg[1]);
            break;
        case 3:
            result = (*(EmRunnerInt32Func3)(func))(arg[0], arg[1], arg[2]);
            break;
        case 4:
            result = (*(EmRunnerInt32Func4)(func))(arg[0], arg[1], arg[2], arg[3]);
            break;
        case 5:
            result = (*(EmRunnerInt32Func5)(func))(arg[0], arg[1], arg[2], arg[3], arg[4]);
            break;
        case 6:
            result = (*(EmRunnerInt32Func6)(func))(arg[0], arg[1], arg[2], arg[3], arg[4], arg[5]);
            break;
        case 7:
            result = (*(EmRunnerInt32Func7)(func))(arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6]);
            break;
        case 8:
            result = (*(EmRunnerInt32Func8)(func))(arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7]);
            break;
        case 9:
            result = (*(EmRunnerInt32Func9)(func))(arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7], arg[8]);
            break;
    }
    return result;
}

static inline int _EmFunctionRunnerCallVoid(EmRunnerFunctionInfo *funcInfo)
{
    void *func = funcInfo->func;
    int32_t *arg = funcInfo->funcArgs;
    switch (funcInfo->funcArgc) {
        case 0:
            (*(EmRunnerVoidFunc0)(func))();
            break;
        case 1:
            (*(EmRunnerVoidFunc1)(func))(arg[0]);
            break;
        case 2:
            (*(EmRunnerVoidFunc2)(func))(arg[0], arg[1]);
            break;
        case 3:
            (*(EmRunnerVoidFunc3)(func))(arg[0], arg[1], arg[2]);
            break;
        case 4:
            (*(EmRunnerVoidFunc4)(func))(arg[0], arg[1], arg[2], arg[3]);
            break;
        case 5:
            (*(EmRunnerVoidFunc5)(func))(arg[0], arg[1], arg[2], arg[3], arg[4]);
            break;
        case 6:
            (*(EmRunnerVoidFunc6)(func))(arg[0], arg[1], arg[2], arg[3], arg[4], arg[5]);
            break;
        case 7:
            (*(EmRunnerVoidFunc7)(func))(arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6]);
            break;
        case 8:
            (*(EmRunnerVoidFunc8)(func))(arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7]);
            break;
        case 9:
            (*(EmRunnerVoidFunc9)(func))(arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7], arg[8]);
            break;
    }
    return 0;
}

void EmPeekFunctionRunner(EmGameFunctionRunnerContext *ctx)
{
    // if (!ctx->hasRequest) {
    //     if (!ctx->dynamicTickDelay)
    //         SDL_Delay(EM_MIN_TICK_DELAY);
    //     return;
    // }
    Uint64 startTime = SDL_GetTicks64();
    Uint64 timeout = startTime + ctx->tickDelay;
    Uint64 endTime = startTime;
    Uint64 elapsedTime = 0;
    while (timeout > endTime) {
        uint32_t semDelay = elapsedTime < ctx->tickDelay ? ctx->tickDelay - elapsedTime : 0;
        if (semDelay == 0) {
            endTime = SDL_GetTicks64();
            break;
        }
        int semWait = SDL_SemWaitTimeout(ctx->semSendRequest, semDelay);
        if (semWait == SDL_MUTEX_TIMEDOUT) {
            endTime = SDL_GetTicks64();
            break;
        }
        if (ctx->hasRequest) {
            EmRunnerFunctionInfo *funcInfo = ctx->funcInfo;
            int32_t result = 0;
            switch (funcInfo->funcReturnType) {
                case EM_FUNC_RETURN_TYPE_VOID:
                    result = _EmFunctionRunnerCallVoid(funcInfo);
                    break;
                case EM_FUNC_RETURN_TYPE_INT32:
                    result = _EmFunctionRunnerCallInt32(funcInfo);
                    break;
            }
            funcInfo->funcResult = result;
            ctx->hasRequest = 0;
            SDL_SemPost(ctx->semFuncWait);
        }
        endTime = SDL_GetTicks64();
        // Did swap buffer
        if (ctx->restartLoop && !ctx->dynamicTickDelay)
            break;
    }
    elapsedTime = endTime - startTime;
    // printf("Elapsed time %lu ms\n", elapsedTime);
    // Adapt maximum tick delay to current FPS, if browser has no issue of this method
    if (ctx->dynamicTickDelay) {
        int fc = EmGLGetFrameCount();
        if (fc != ctx->currentFrameCount) {
            float currentFps = EmGLGetCurrentFPS();
            if (currentFps > 0.0) {
                int newTickDelay = round(1000.0 / (float)currentFps);
                ctx->tickDelay = newTickDelay > EM_MIN_TICK_DELAY ? (newTickDelay < EM_MAX_TICK_DELAY ? newTickDelay : EM_MAX_TICK_DELAY) : EM_MIN_TICK_DELAY;
            }
            ctx->currentFrameCount = fc;
        }
    }
    ctx->restartLoop = 0;
}

void EmRestartLoopForFunctionRunner()
{
    EmGameFunctionRunnerContext *ctx = EmGetGlobalFunctionRunner();
    ctx->restartLoop = 1;
}

void EmFreeFunctionRunner(EmGameFunctionRunnerContext *ctx)
{
    if (!ctx)
        return;
    SDL_DestroySemaphore(ctx->semFuncWait);
    SDL_DestroySemaphore(ctx->semLockFunc);
    SDL_DestroySemaphore(ctx->semSendRequest);
    free(ctx);
}

static void _EmPrepareAssets()
{
    // Prepare assets
    EM_ASM({
        // Put global values at module so didn't pollute world as whole
        const thisModule = window[UTF8ToString($0)];
        thisModule['nfs2AssetsLoaded'] = 0;
        thisModule['nfs2AssetsLoadProgress'] = -1;
        setTimeout(async (thisModule) => {
            const assetsExtractFunc = async (assetsBuffer) => {
                console.log("Reading ZIP file");
                const zipReader = await new JSZip.loadAsync(assetsBuffer);
                thisModule['nfs2AssetsLoadProgress'] = 0;
                let fileCount = 0;
                Object.keys(zipReader.files).map((p) => {
                    const file = zipReader.files[p];
                    if (!file.dir)
                        fileCount++;
                });
                let fileProcessed = 0;
                await Promise.all(Object.keys(zipReader.files).map(async (p) => {
                    const file = zipReader.files[p];
                    const newFileName = "/" + file.name.toLowerCase();
                    if (file.dir) {
                        // console.log("Creating directory " + newFileName);
                        FS.mkdirTree(newFileName);
                    } else {
                        // console.log("Writing file " + newFileName);
                        FS.writeFile(newFileName, await file.async("uint8array"));
                        fileProcessed++;
                        thisModule['nfs2AssetsLoadProgress'] = Math.round((fileProcessed / fileCount) * 100);
                    }
                }));
                console.log(fileCount + " files extracted!");
                return true;
            };
            const asyncFetchFunc = async (path, cached) => {
                console.log("Fetching " + path);
                return await fetch(path, {
                    cache: cached? "force-cache" : "no-cache",
                }).then((transfer) => {
                    return transfer.arrayBuffer();
                });
            };
            const assetsBuffer = await asyncFetchFunc("./nfs2se.zip", true);
            await assetsExtractFunc(assetsBuffer);
            const confFile = new Uint8Array(await asyncFetchFunc("./nfs2se.conf", false));
            FS.writeFile("/nfs2se.conf", confFile);
            // Tell we have done
            thisModule['nfs2AssetsLoaded'] = 1;
        }, 0, thisModule);
    }, MODULE_NAME);
}

int EmIsAssetsLoaded()
{
    return MAIN_THREAD_EM_ASM_INT({
        const thisModule = window[UTF8ToString($0)];
        return thisModule['nfs2AssetsLoaded'];
    }, MODULE_NAME);
}

int EmGetAssetsProgressPercent()
{
    return MAIN_THREAD_EM_ASM_INT({
        const thisModule = window[UTF8ToString($0)];
        return thisModule['nfs2AssetsLoadProgress'];
    }, MODULE_NAME);
}

static void _EmMainLoop(void* arg) {
    EmMainLoopContext* loopCtx = (EmMainLoopContext*)arg;
    EmGameFunctionRunnerContext* runnerCtx = loopCtx->runnerCtx;
    EmGameWorkerContext* workerCtx = loopCtx->workerCtx;
    if (workerCtx) {
        EmPeekFunctionRunner(runnerCtx);
        // Not yet finish?
        if (!EmCheckGameWorkerStatus(workerCtx))
            return;
    }
    // Cleanup
    EmFreeGameWorker(loopCtx->workerCtx);
    EmFreeFunctionRunner(loopCtx->runnerCtx);
    free(loopCtx);
    emscripten_cancel_main_loop();
}

int EmInvokeGameEntryPoint(void* entryPointFunc)
{
    _EmPrepareAssets();
#ifdef USE_GL4ES
	setenv("LIBGL_ES", "2", 1);
	setenv("LIBGL_GL", "15", 1);
	// Important: BeginEnd caching must be off as have known bug
	setenv("LIBGL_BEGINEND", "0", 1);
    setenv("LIBGL_FBO", "2", 1);
    setenv("LIBGL_BLITFULLSCREEN", "0", 1);
    initialize_gl4es();
#endif
    EmMainLoopContext *loopCtx = (EmMainLoopContext*)malloc(sizeof(EmMainLoopContext));
    memset(loopCtx, 0, sizeof(EmMainLoopContext));
    EmGameFunctionRunnerContext *runnerCtx = EmInitFunctionRunner();
    if (!runnerCtx)
        return 1;
    EmSetGlobalFunctionRunner(runnerCtx);
    EmGameWorkerContext* workerCtx = EmRunGameWorker(entryPointFunc);
    if (!workerCtx)
        return 1;
    loopCtx->runnerCtx = runnerCtx;
    loopCtx->workerCtx = workerCtx;
    emscripten_set_main_loop_arg(&_EmMainLoop, loopCtx, 0, true);
    return 0;
}

int StartNFS2Game()
{
    void nfs2seEntrypoint();
	return EmInvokeGameEntryPoint(&nfs2seEntrypoint);
    return 0;
}

