#include <SDL2/SDL_opengles2.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_timer.h>

#include "EmscriptenUtils.h"
#define EM_NO_GLWRAP
#include "EmscriptenGLShim.h"

static Uint64 g_StartTime;
static int g_FramesInSec;
static int g_FrameCount;
static float g_CurrentFps;

SDL_GLContext EmGLWrapCreateContext(SDL_Window *window)
{
    g_FramesInSec = 0;
    g_CurrentFps = 0.0;
    g_StartTime = SDL_GetTicks64();
    g_FrameCount = 0;
    return (SDL_GLContext)EmInvokeToFunctionRunner1(&SDL_GL_CreateContext, EM_FUNC_RETURN_TYPE_INT32, (int32_t)window);
}

void EmGLWrapDeleteContext(SDL_GLContext context)
{
    EmInvokeToFunctionRunner1(&SDL_GL_DeleteContext, EM_FUNC_RETURN_TYPE_VOID, (int32_t)context);
}

void EmGLWrapSwapWindow(SDL_Window *window)
{
    // Do swap
    EmInvokeToFunctionRunner1(&SDL_GL_SwapWindow, EM_FUNC_RETURN_TYPE_VOID, (int32_t)window);
    // Tell to break function runner loop after every swap happens
    EmRestartLoopForFunctionRunner();
    g_FramesInSec++;
    g_FrameCount++;
    Uint64 endTime = SDL_GetTicks64();
    Uint64 elapsedTime = endTime - g_StartTime;
    if (elapsedTime >= 1000) {
        g_CurrentFps = ((float)g_FramesInSec / 1000) * (1000 - (elapsedTime % 1000));
        g_StartTime = endTime;
        g_FramesInSec = 0;
        printf("FPS: %.2f\n", g_CurrentFps);
    }
}

int EmGLSetSwapInterval(int interval)
{
    return EmInvokeToFunctionRunner1(&SDL_GL_SetSwapInterval, EM_FUNC_RETURN_TYPE_INT32, interval);
}

float EmGLGetCurrentFPS()
{
    return g_CurrentFps;
}

int EmGLGetFrameCount()
{
    return g_FrameCount;
}

// glClear
void glClear_shim(GLbitfield mask)
{
    // Reset FPS start time from buffer clear
    if (g_FramesInSec == 0)
        g_StartTime = SDL_GetTicks64();
    EmInvokeToFunctionRunner1(&glClear, EM_FUNC_RETURN_TYPE_VOID, mask);
}

// glEnable
inline void glEnable_shim(GLenum cap)
{
    EmInvokeToFunctionRunner1(&glEnable, EM_FUNC_RETURN_TYPE_VOID, cap);
}

// glDisable
inline void glDisable_shim(GLenum cap)
{
    EmInvokeToFunctionRunner1(&glDisable, EM_FUNC_RETURN_TYPE_VOID, cap);
}

// glDepthFunc
inline void glDepthFunc_shim(GLenum func)
{
    EmInvokeToFunctionRunner1(&glDepthFunc, EM_FUNC_RETURN_TYPE_VOID, func);
}

// glDepthMask
inline void glDepthMask_shim(GLboolean flag)
{
    EmInvokeToFunctionRunner1(&glDepthMask, EM_FUNC_RETURN_TYPE_VOID, flag);
}

// glClearColor
static void glClearColor_wrap(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3)
{
    GLfloat arg0_f, arg1_f, arg2_f, arg3_f;
    memcpy(&arg0_f, &arg0, sizeof(GLfloat));
    memcpy(&arg1_f, &arg1, sizeof(GLfloat));
    memcpy(&arg2_f, &arg2, sizeof(GLfloat));
    memcpy(&arg3_f, &arg3, sizeof(GLfloat));
    glClearColor(arg0_f, arg1_f, arg2_f, arg3_f);
}
inline void glClearColor_shim(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    int32_t arg0, arg1, arg2, arg3;
    memcpy(&arg0, &red, sizeof(int32_t));
    memcpy(&arg1, &green, sizeof(int32_t));
    memcpy(&arg2, &blue, sizeof(int32_t));
    memcpy(&arg3, &alpha, sizeof(int32_t));
    EmInvokeToFunctionRunner4(&glClearColor_wrap, EM_FUNC_RETURN_TYPE_VOID, arg0, arg1, arg2, arg3);
}

// glClearDepthf
static void glClearDepthf_wrap(int32_t arg0)
{
    GLfloat arg0_f;
    memcpy(&arg0_f, &arg0, sizeof(GLfloat));
    glClearDepthf(arg0_f);
}
inline void glClearDepthf_shim(GLfloat d)
{
    int32_t arg0;
    memcpy(&arg0, &d, sizeof(int32_t));
    EmInvokeToFunctionRunner1(&glClearDepthf_wrap, EM_FUNC_RETURN_TYPE_VOID, arg0);
}

// glDrawArrays
inline void glDrawArrays_shim(GLenum mode, GLint first, GLsizei count)
{
    EmInvokeToFunctionRunner3(&glDrawArrays, EM_FUNC_RETURN_TYPE_VOID, mode, first, count);
}

// glBlendFunc
inline void glBlendFunc_shim(GLenum sfactor, GLenum dfactor)
{
    EmInvokeToFunctionRunner2(&glBlendFunc, EM_FUNC_RETURN_TYPE_VOID, sfactor, dfactor);
}

// glTexParameteri
inline void glTexParameteri_shim(GLenum target, GLenum pname, GLint param)
{
    EmInvokeToFunctionRunner3(&glTexParameteri, EM_FUNC_RETURN_TYPE_VOID, target, pname, param);
}

// glGenTextures
static void glGenTextures_wrap(int32_t arg0, int32_t arg1)
{
    glGenTextures(arg0, (GLuint*)arg1);
}
inline void glGenTextures_shim(GLsizei n, GLuint *textures)
{
    EmInvokeToFunctionRunner2(&glGenTextures_wrap, EM_FUNC_RETURN_TYPE_VOID, n, (int32_t)textures);
}

// glBindTexture
inline void glBindTexture_shim(GLenum target, GLuint texture)
{
    EmInvokeToFunctionRunner2(&glBindTexture, EM_FUNC_RETURN_TYPE_VOID, target, texture);
}

// glTexImage2D
static void glTexImage2D_wrap(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4, int32_t arg5, int32_t arg6, int32_t arg7, int32_t arg8)
{
    glTexImage2D(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, (void*)arg8);
}
inline void glTexImage2D_shim(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels)
{
    EmInvokeToFunctionRunner9(&glTexImage2D_wrap, EM_FUNC_RETURN_TYPE_VOID, target, level, internalformat, width, height, border, format, type, (int32_t)pixels);
}

// glGetString
inline GLubyte* glGetString_shim(GLenum name)
{
    return (GLubyte*)EmInvokeToFunctionRunner1(&glGetString, EM_FUNC_RETURN_TYPE_INT32, name);
}

// glGetIntegerv
static void glGetIntegerv_wrap(int32_t arg0, int32_t arg1)
{
    glGetIntegerv(arg0, (GLint*)arg1);
}
inline void glGetIntegerv_shim(GLenum pname, GLint *data)
{
    EmInvokeToFunctionRunner2(&glGetIntegerv_wrap, EM_FUNC_RETURN_TYPE_VOID, pname, (int32_t)data);
}

// glViewport
inline void glViewport_shim(GLint x, GLint y, GLsizei width, GLsizei height)
{
    EmInvokeToFunctionRunner4(&glViewport, EM_FUNC_RETURN_TYPE_VOID, x, y, width, height);
}

// glScissor
inline void glScissor_shim(GLint x, GLint y, GLsizei width, GLsizei height)
{
    EmInvokeToFunctionRunner4(&glScissor, EM_FUNC_RETURN_TYPE_VOID, x, y, width, height);
}

// glLineWidth
static void glLineWidth_wrap(int32_t arg0)
{
    GLfloat arg0_f;
    memcpy(&arg0_f, &arg0, sizeof(GLfloat));
    glLineWidth(arg0_f);
}
inline void glLineWidth_shim(GLfloat width)
{
    int32_t arg0;
    memcpy(&arg0, &width, sizeof(int32_t));
    EmInvokeToFunctionRunner1(&glLineWidth_wrap, EM_FUNC_RETURN_TYPE_VOID, arg0);
}

// glGetShaderiv
static void glGetShaderiv_wrap(int32_t arg0, int32_t arg1, int32_t arg2)
{
    glGetShaderiv(arg0, arg1, (GLint*)arg2);
}
inline void glGetShaderiv_shim(GLuint shader, GLenum pname, GLint *params)
{
    EmInvokeToFunctionRunner3(&glGetShaderiv_wrap, EM_FUNC_RETURN_TYPE_VOID, shader, pname, (int32_t)params);
}

// glGetProgramiv
static void glGetProgramiv_wrap(int32_t arg0, int32_t arg1, int32_t arg2)
{
    glGetProgramiv(arg0, arg1, (GLint*)arg2);
}
inline void glGetProgramiv_shim(GLuint program, GLenum pname, GLint *params)
{
    EmInvokeToFunctionRunner3(&glGetProgramiv_wrap, EM_FUNC_RETURN_TYPE_VOID, program, pname, (int32_t)params);
}

// glGetShaderInfoLog
static void glGetShaderInfoLog_wrap(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3)
{
    glGetShaderInfoLog(arg0, arg1, (GLsizei*)arg2, (GLchar*)arg3);
}
inline void glGetShaderInfoLog_shim(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog)
{
    EmInvokeToFunctionRunner4(&glGetShaderInfoLog_wrap, EM_FUNC_RETURN_TYPE_VOID, shader, bufSize, (int32_t)length, (int32_t)infoLog);
}

// glGetProgramInfoLog
static void glGetProgramInfoLog_wrap(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3)
{
    glGetProgramInfoLog(arg0, arg1, (GLsizei*)arg2, (GLchar*)arg3);
}
inline void glGetProgramInfoLog_shim(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog)
{
    EmInvokeToFunctionRunner4(&glGetProgramInfoLog_wrap, EM_FUNC_RETURN_TYPE_VOID, program, bufSize, (int32_t)length, (int32_t)infoLog);
}

// glCreateShader
inline GLuint glCreateShader_shim(GLenum type)
{
    return EmInvokeToFunctionRunner1(&glCreateShader, EM_FUNC_RETURN_TYPE_INT32, type);
}

// glDeleteShader
inline void glDeleteShader_shim(GLenum shader)
{
    EmInvokeToFunctionRunner1(&glDeleteShader, EM_FUNC_RETURN_TYPE_VOID, shader);
}

// glShaderSource
static void glShaderSource_wrap(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3)
{
    glShaderSource(arg0, arg1, (const GLchar *const*)arg2, (GLint*)arg3);
}
inline void glShaderSource_shim(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length)
{
    EmInvokeToFunctionRunner4(&glShaderSource_wrap, EM_FUNC_RETURN_TYPE_VOID, shader, count, (int32_t)string, (int32_t)length);
}

// glCompileShader
inline void glCompileShader_shim(GLenum shader)
{
    EmInvokeToFunctionRunner1(&glCompileShader, EM_FUNC_RETURN_TYPE_VOID, shader);
}

// glCreateProgram
inline GLuint glCreateProgram_shim(void)
{
    return EmInvokeToFunctionRunner0(&glCreateProgram, EM_FUNC_RETURN_TYPE_INT32);
}

// glDeleteProgram
inline void glDeleteProgram_shim(GLenum program)
{
    EmInvokeToFunctionRunner1(&glDeleteProgram, EM_FUNC_RETURN_TYPE_VOID, program);
}

// glAttachShader
inline void glAttachShader_shim(GLuint program, GLuint shader)
{
    EmInvokeToFunctionRunner2(&glAttachShader, EM_FUNC_RETURN_TYPE_VOID, program, shader);
}

// glLinkProgram
inline void glLinkProgram_shim(GLuint program)
{
    EmInvokeToFunctionRunner1(&glLinkProgram, EM_FUNC_RETURN_TYPE_VOID, program);
}

// glGetAttribLocation
static int32_t glGetAttribLocation_wrap(int32_t arg0, int32_t arg1)
{
    return glGetAttribLocation(arg0, (const GLchar*)arg1);
}
GLint glGetAttribLocation_shim(GLuint program, const GLchar *name)
{
    return EmInvokeToFunctionRunner2(&glGetAttribLocation_wrap, EM_FUNC_RETURN_TYPE_INT32, program, (int32_t)name);
}

// glGetUniformLocation
static int32_t glGetUniformLocation_wrap(int32_t arg0, int32_t arg1)
{
    return glGetUniformLocation(arg0, (GLchar*)arg1);
}
inline GLint glGetUniformLocation_shim(GLuint program, const GLchar *name)
{
    return EmInvokeToFunctionRunner2(&glGetUniformLocation_wrap, EM_FUNC_RETURN_TYPE_INT32, program, (int32_t)name);
}

// glUseProgram
inline void glUseProgram_shim(GLuint program)
{
    EmInvokeToFunctionRunner1(&glUseProgram, EM_FUNC_RETURN_TYPE_VOID, program);
}

// glUniform1i
inline void glUniform1i_shim(GLint location, GLint v0)
{
    EmInvokeToFunctionRunner2(&glUniform1i, EM_FUNC_RETURN_TYPE_VOID, location, v0);
}

// glUniformMatrix4fv
static void glUniformMatrix4fv_wrap(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3)
{
    glUniformMatrix4fv(arg0, arg1, arg2, (GLfloat*)arg3);
}
inline void glUniformMatrix4fv_shim(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    EmInvokeToFunctionRunner4(&glUniformMatrix4fv_wrap, EM_FUNC_RETURN_TYPE_VOID, location, count, transpose, (int32_t)value);
}

// glVertexAttribPointer
static void glVertexAttribPointer_wrap(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4, int32_t arg5)
{
    glVertexAttribPointer(arg0, arg1, arg2, arg3, arg4, (void*)arg5);
}
inline void glVertexAttribPointer_shim(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)
{
    EmInvokeToFunctionRunner6(&glVertexAttribPointer_wrap, EM_FUNC_RETURN_TYPE_VOID, index, size, type, normalized, stride, (int32_t)pointer);
}

// glUniform3f
static void glUniform3f_wrap(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3)
{
    GLfloat arg1_f, arg2_f, arg3_f;
    memcpy(&arg1_f, &arg1, sizeof(GLfloat));
    memcpy(&arg2_f, &arg2, sizeof(GLfloat));
    memcpy(&arg3_f, &arg3, sizeof(GLfloat));
    glUniform3f(arg0, arg1_f, arg2_f, arg3_f);
}
inline void glUniform3f_shim(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
    int32_t arg1, arg2, arg3;
    memcpy(&arg1, &v0, sizeof(int32_t));
    memcpy(&arg2, &v1, sizeof(int32_t));
    memcpy(&arg3, &v2, sizeof(int32_t));
    EmInvokeToFunctionRunner4(&glUniform3f_wrap, EM_FUNC_RETURN_TYPE_VOID, location, arg1, arg2, arg3);
}

// glUniform1f
static void glUniform1f_wrap(int32_t arg0, int32_t arg1)
{
    GLfloat arg1_f;
    memcpy(&arg1_f, &arg1, sizeof(GLfloat));
    glUniform1f(arg0, arg1_f);
}
inline void glUniform1f_shim(GLint location, GLfloat v0)
{
    int32_t arg1;
    memcpy(&arg1, &v0, sizeof(int32_t));
    EmInvokeToFunctionRunner2(&glUniform1f_wrap, EM_FUNC_RETURN_TYPE_VOID, location, arg1);
}

// glEnableVertexAttribArray
inline void glEnableVertexAttribArray_shim(GLuint index)
{
    EmInvokeToFunctionRunner1(&glEnableVertexAttribArray, EM_FUNC_RETURN_TYPE_VOID, index);
}

// glDisableVertexAttribArray
inline void glDisableVertexAttribArray_shim(GLuint index)
{
    EmInvokeToFunctionRunner1(&glDisableVertexAttribArray, EM_FUNC_RETURN_TYPE_VOID, index);
}

// glGenFramebuffers
static void glGenFramebuffers_wrap(int32_t arg0, int32_t arg1)
{
    glGenFramebuffers(arg0, (GLuint*)arg1);
}
inline void glGenFramebuffers_shim(GLsizei n, GLuint *framebuffers)
{
    EmInvokeToFunctionRunner2(&glGenFramebuffers_wrap, EM_FUNC_RETURN_TYPE_VOID, n, (int32_t)framebuffers);
}

// glBindFramebuffer
inline void glBindFramebuffer_shim(GLenum target, GLuint framebuffer)
{
    EmInvokeToFunctionRunner2(&glBindFramebuffer, EM_FUNC_RETURN_TYPE_VOID, target, framebuffer);
}

// glFramebufferTexture2D
inline void glFramebufferTexture2D_shim(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
    EmInvokeToFunctionRunner5(&glFramebufferTexture2D, EM_FUNC_RETURN_TYPE_VOID, target, attachment, textarget, texture, level);
}

// glGenRenderbuffers
static void glGenRenderbuffers_wrap(int32_t arg0, int32_t arg1)
{
    glGenRenderbuffers(arg0, (GLuint*)arg1);
}
inline void glGenRenderbuffers_shim(GLsizei n, GLuint *framebuffers)
{
    EmInvokeToFunctionRunner2(&glGenRenderbuffers_wrap, EM_FUNC_RETURN_TYPE_VOID, n, (int32_t)framebuffers);
}

// glBindRenderbuffer
inline void glBindRenderbuffer_shim(GLenum target, GLuint renderbuffer)
{
    EmInvokeToFunctionRunner2(&glBindRenderbuffer, EM_FUNC_RETURN_TYPE_VOID, target, renderbuffer);
}

// glRenderbufferStorage
inline void glRenderbufferStorage_shim(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
    EmInvokeToFunctionRunner4(&glRenderbufferStorage, EM_FUNC_RETURN_TYPE_VOID, target, internalformat, width, height);
}

// glFramebufferRenderbuffer
inline void glFramebufferRenderbuffer_shim(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
    EmInvokeToFunctionRunner4(&glFramebufferRenderbuffer, EM_FUNC_RETURN_TYPE_VOID, target, attachment, renderbuffertarget, renderbuffer);
}

// glCheckFramebufferStatus
inline GLenum glCheckFramebufferStatus_shim(GLenum target)
{
    return EmInvokeToFunctionRunner1(&glCheckFramebufferStatus, EM_FUNC_RETURN_TYPE_INT32, target);
}

// glDeleteRenderbuffers
static void glDeleteRenderbuffers_wrap(int32_t arg0, int32_t arg1)
{
    glDeleteRenderbuffers(arg0, (GLuint*)arg1);
}
inline void glDeleteRenderbuffers_shim(GLsizei n, const GLuint *renderbuffers)
{
    EmInvokeToFunctionRunner2(&glDeleteRenderbuffers_wrap, EM_FUNC_RETURN_TYPE_VOID, n, (int32_t)renderbuffers);
}

// glDeleteFramebuffers
static void glDeleteFramebuffers_wrap(int32_t arg0, int32_t arg1)
{
    glDeleteFramebuffers(arg0, (GLuint*)arg1);
}
inline void glDeleteFramebuffers_shim(GLsizei n, const GLuint *framebuffers)
{
    EmInvokeToFunctionRunner2(&glDeleteFramebuffers_wrap, EM_FUNC_RETURN_TYPE_VOID, n, (int32_t)framebuffers);
}

