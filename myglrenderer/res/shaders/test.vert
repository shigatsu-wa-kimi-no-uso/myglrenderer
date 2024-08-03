#version 330 core

attribute vec3 aPosition;
attribute vec3 aColor;
attribute vec2 aTexCoords;

uniform mat4 uModeling;
uniform mat4 uView;
uniform mat4 uProjection;

varying vec3 ourColor;
varying vec2 texCoords;

void main()
{
    gl_Position = uProjection * uView * uModeling*vec4(aPosition, 1.0);
    ourColor = aColor;
    texCoords = aTexCoords;
}