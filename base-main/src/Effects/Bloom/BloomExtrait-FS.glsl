#version 460

uniform sampler2D myFBO;
uniform float seuil;

in vec2 uv;

layout(location = 0) out vec4 Color;

void main() {
    vec3 color = texture(myFBO, uv).rgb;
    
    // Calcul de la luminance
    float luminance = (color.r + color.g + color.b) / 3.0;
    
    // Extraction des zones lumineuses avec le seuil
    if (luminance > seuil) {
        Color = vec4(color, 1.0);
    } else {
        Color = vec4(0.0, 0.0, 0.0, 1.0);
    }
}