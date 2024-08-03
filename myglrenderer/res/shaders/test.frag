#version 330 core


varying vec3 ourColor;
varying vec2 texCoords;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float uRatio;

void main()
{
    vec4 texColor = texture(texture1, texCoords);
    if(texColor.a < 0.5){
        discard;
    }
    gl_FragColor = texColor;
}