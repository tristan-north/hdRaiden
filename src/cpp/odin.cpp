#include "odin.h"

void gl_funcptr_setup() {
    odin_glClearColor(glClearColor);
    odin_glClear(glClear);
    void odin_glUniformMatrix2fv(glUniformMatrix2fv);
    GLint odin_glGetUniformLocation(glGetUniformLocation);
    void odin_glViewport(glViewport);
    void odin_glPixelStorei(glPixelStorei);
    void odin_glGenTextures(glGenTextures);
    void odin_glBindTexture(glBindTexture);
    void odin_glTexImage2D(glTexImage2D);
    void odin_glTexParameteri(glTexParameteri);
    void odin_glGenVertexArrays(glGenVertexArrays);
    void odin_glBindVertexArray(glBindVertexArray);
    void odin_glGenBuffers(glGenBuffers);
    void odin_glBindBuffer(glBindBuffer);
    void odin_glBufferData(glBufferData);
    void odin_glVertexAttribPointer(glVertexAttribPointer);
    void odin_glEnableVertexAttribArray(glEnableVertexAttribArray);
    void odin_glUseProgram(glUseProgram);
    void odin_glEnable(glEnable);
    void odin_glBlendFunc(glBlendFunc);
    void odin_glBufferSubData(glBufferSubData);
    void odin_glDrawArrays(glDrawArrays);
}