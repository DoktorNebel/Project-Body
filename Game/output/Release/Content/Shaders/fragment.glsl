#version 330 core

in vec2 texCoord;
in vec4 fragColor;

out vec4 color;

uniform sampler2D defaultSampler;
 
void main()
{
    color = texture2D(defaultSampler, texCoord.xy) * fragColor;
}