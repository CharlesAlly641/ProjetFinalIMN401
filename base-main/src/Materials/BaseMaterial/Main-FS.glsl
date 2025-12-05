#version 460
flat in float pic;
layout(location = 0) out vec4 Color;

void main() {
    // On ajuste la couleur selon si c'est un pic ou non pour mettre la déformation en évidence
    if (pic == 1.0) {
        Color = vec4(0.2, 0.2, 0.2, 1.0);
    } else {
        Color = vec4(0.9, 0.9, 0.9, 1.0);
    }
}