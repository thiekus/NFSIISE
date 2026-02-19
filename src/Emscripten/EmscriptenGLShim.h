
#ifndef EMSCRIPTENGLSHIM_H
#define EMSCRIPTENGLSHIM_H

#include <SDL2/SDL_opengles2.h>
#include <SDL2/SDL_video.h>

#ifdef OPENGL1X
#error "Emscripten target doesn't support OpenGL 1.x"
#endif
#ifndef GLES2
#error "Emscripten target must be use OpenGL ES 2.0"
#endif

SDL_GLContext EmGLWrapCreateContext(SDL_Window *window);
void EmGLWrapDeleteContext(SDL_GLContext context);
void EmGLWrapSwapWindow(SDL_Window *window);
int EmGLSetSwapInterval(int interval);
float EmGLGetCurrentFPS();
int EmGLGetFrameCount();

#ifndef EM_NO_GLWRAP

void glClear_shim (GLbitfield mask);
#define glClear(...) glClear_shim(__VA_ARGS__)

inline void glEnable_shim (GLenum cap);
#define glEnable(...) glEnable_shim(__VA_ARGS__)

inline void glDisable_shim (GLenum cap);
#define glDisable(...) glDisable_shim(__VA_ARGS__)

inline void glDepthFunc_shim (GLenum func);
#define glDepthFunc(...) glDepthFunc_shim(__VA_ARGS__)

inline void glDepthMask_shim (GLboolean flag);
#define glDepthMask(...) glDepthMask_shim(__VA_ARGS__)

inline void glClearColor_shim (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
#define glClearColor(...) glClearColor_shim(__VA_ARGS__)

inline void glClearDepthf_shim (GLfloat d);
#define glClearDepthf(...) glClearDepthf_shim(__VA_ARGS__)

inline void glDrawArrays_shim (GLenum mode, GLint first, GLsizei count);
#define glDrawArrays(...) glDrawArrays_shim(__VA_ARGS__)

inline void glBlendFunc_shim (GLenum sfactor, GLenum dfactor);
#define glBlendFunc(...) glBlendFunc_shim(__VA_ARGS__)

inline void glTexParameteri_shim (GLenum target, GLenum pname, GLint param);
#define glTexParameteri(...) glTexParameteri_shim(__VA_ARGS__)

inline void glGenTextures_shim (GLsizei n, GLuint *textures);
#define glGenTextures(...) glGenTextures_shim(__VA_ARGS__)

inline void glBindTexture_shim (GLenum target, GLuint texture);
#define glBindTexture(...) glBindTexture_shim(__VA_ARGS__)

inline void glTexImage2D_shim (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
#define glTexImage2D(...) glTexImage2D_shim(__VA_ARGS__)

inline const GLubyte * glGetString_shim (GLenum name);
#define glGetString(...) glGetString_shim(__VA_ARGS__)

inline void glGetIntegerv_shim (GLenum pname, GLint *data);
#define glGetIntegerv(...) glGetIntegerv_shim(__VA_ARGS__)

inline void glViewport_shim (GLint x, GLint y, GLsizei width, GLsizei height);
#define glViewport(...) glViewport_shim(__VA_ARGS__)

inline void glScissor_shim (GLint x, GLint y, GLsizei width, GLsizei height);
#define glScissor(...) glScissor_shim(__VA_ARGS__)

inline void glLineWidth_shim (GLfloat width);
#define glLineWidth(...) glLineWidth_shim(__VA_ARGS__)

inline void GL_APIENTRY glGetShaderiv_shim (GLuint shader, GLenum pname, GLint *params);
#define glGetShaderiv(...) glGetShaderiv_shim(__VA_ARGS__)

inline void GL_APIENTRY glGetProgramiv_shim (GLuint program, GLenum pname, GLint *params);
#define glGetProgramiv(...) glGetProgramiv_shim(__VA_ARGS__)

inline void GL_APIENTRY glGetShaderInfoLog_shim (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
#define glGetShaderInfoLog(...) glGetShaderInfoLog_shim(__VA_ARGS__)

inline void GL_APIENTRY glGetProgramInfoLog_shim (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
#define glGetProgramInfoLog(...) glGetProgramInfoLog_shim(__VA_ARGS__)

inline GLuint GL_APIENTRY glCreateShader_shim (GLenum type);
#define glCreateShader(...) glCreateShader_shim(__VA_ARGS__)

inline void GL_APIENTRY glDeleteShader_shim (GLuint shader);
#define glDeleteShader(...) glDeleteShader_shim(__VA_ARGS__)

inline void GL_APIENTRY glShaderSource_shim (GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
#define glShaderSource(...) glShaderSource_shim(__VA_ARGS__)

inline void GL_APIENTRY glCompileShader_shim (GLuint shader);
#define glCompileShader(...) glCompileShader_shim(__VA_ARGS__)

inline GLuint GL_APIENTRY glCreateProgram_shim (void);
#define glCreateProgram(...) glCreateProgram_shim(__VA_ARGS__)

inline void GL_APIENTRY glDeleteProgram_shim (GLuint program);
#define glDeleteProgram(...) glDeleteProgram_shim(__VA_ARGS__)

inline void GL_APIENTRY glAttachShader_shim (GLuint program, GLuint shader);
#define glAttachShader(...) glAttachShader_shim(__VA_ARGS__)

inline void GL_APIENTRY glLinkProgram_shim (GLuint program);
#define glLinkProgram(...) glLinkProgram_shim(__VA_ARGS__)

inline GLint GL_APIENTRY glGetAttribLocation_shim (GLuint program, const GLchar *name);
#define glGetAttribLocation(...) glGetAttribLocation_shim(__VA_ARGS__)

inline GLint GL_APIENTRY glGetUniformLocation_shim (GLuint program, const GLchar *name);
#define glGetUniformLocation(...) glGetUniformLocation_shim(__VA_ARGS__)

inline void GL_APIENTRY glUseProgram_shim (GLuint program);
#define glUseProgram(...) glUseProgram_shim(__VA_ARGS__)

inline void GL_APIENTRY glUniform1i_shim (GLint location, GLint v0);
#define glUniform1i(...) glUniform1i_shim(__VA_ARGS__)

inline void GL_APIENTRY glUniformMatrix4fv_shim (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
#define glUniformMatrix4fv(...) glUniformMatrix4fv_shim(__VA_ARGS__)

inline void GL_APIENTRY glVertexAttribPointer_shim (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
#define glVertexAttribPointer(...) glVertexAttribPointer_shim(__VA_ARGS__)

inline void GL_APIENTRY glUniform3f_shim (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
#define glUniform3f(...) glUniform3f_shim(__VA_ARGS__)

inline void GL_APIENTRY glUniform1f_shim (GLint location, GLfloat v0);
#define glUniform1f(...) glUniform1f_shim(__VA_ARGS__)

inline void GL_APIENTRY glEnableVertexAttribArray_shim (GLuint index);
#define glEnableVertexAttribArray(...) glEnableVertexAttribArray_shim(__VA_ARGS__)

inline void GL_APIENTRY glDisableVertexAttribArray_shim (GLuint index);
#define glDisableVertexAttribArray(...) glDisableVertexAttribArray_shim(__VA_ARGS__)

inline void GL_APIENTRY glGenFramebuffers_shim (GLsizei n, GLuint *framebuffers);
#define glGenFramebuffers(...) glGenFramebuffers_shim(__VA_ARGS__)

inline void GL_APIENTRY glBindFramebuffer_shim (GLenum target, GLuint framebuffer);
#define glBindFramebuffer(...) glBindFramebuffer_shim(__VA_ARGS__)

inline void GL_APIENTRY glFramebufferTexture2D_shim (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
#define glFramebufferTexture2D(...) glFramebufferTexture2D_shim(__VA_ARGS__)

inline void GL_APIENTRY glGenRenderbuffers_shim (GLsizei n, GLuint *renderbuffers);
#define glGenRenderbuffers(...) glGenRenderbuffers_shim(__VA_ARGS__)

inline void GL_APIENTRY glBindRenderbuffer_shim (GLenum target, GLuint renderbuffer);
#define glBindRenderbuffer(...) glBindRenderbuffer_shim(__VA_ARGS__)

inline void GL_APIENTRY glRenderbufferStorage_shim (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
#define glRenderbufferStorage(...) glRenderbufferStorage_shim(__VA_ARGS__)

inline void GL_APIENTRY glFramebufferRenderbuffer_shim (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
#define glFramebufferRenderbuffer(...) glFramebufferRenderbuffer_shim(__VA_ARGS__)

inline GLenum GL_APIENTRY glCheckFramebufferStatus_shim (GLenum target);
#define glCheckFramebufferStatus(...) glCheckFramebufferStatus_shim(__VA_ARGS__)

inline void GL_APIENTRY glDeleteRenderbuffers_shim (GLsizei n, const GLuint *renderbuffers);
#define glDeleteRenderbuffers(...) glDeleteRenderbuffers_shim(__VA_ARGS__)

inline void GL_APIENTRY glDeleteFramebuffers_shim (GLsizei n, const GLuint *framebuffers);
#define glDeleteFramebuffers(...) glDeleteFramebuffers_shim(__VA_ARGS__)

#endif // EM_NO_GLWRAP

#endif // EMSCRIPTENGLSHIM_H
