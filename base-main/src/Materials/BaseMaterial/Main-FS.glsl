#version 460
in float pic;
layout(location = 0) out vec4 Color;

void main() {
    // On ajuste la couleur selon si c'est un pic ou non
    if (pic > 0.5) {
        Color = vec4(0.87, 0.87, 0.87, 1);
    } else {
        Color = vec4(0.9, 0.9, 0.9, 1.0);
    }
}