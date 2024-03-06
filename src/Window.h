// Window.h
#include <GL/glew.h>
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x,__FILE__,__LINE__))

#pragma once
#ifndef WINDOW_H
#define WINDOW_H

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

// Other declarations...

#endif // WINDOW_H