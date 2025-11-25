#version 460

uniform sampler2D myFBO;
uniform sampler2D bloomTexture;

in vec2 uv;

layout(location = 0) out vec4 Color;

void main() {
    vec3 original = texture(myFBO, uv).rgb;
    vec3 bloom = texture(bloomTexture, uv).rgb;
    
    vec3 result = original + bloom;
    
    Color = vec4(result, 1.0);
}