#version 460
flat in float pic;
uniform vec3 Couleur;
layout(location = 0) out vec4 Color;

void main() {
    // On ajuste la couleur selon si c'est un pic ou non pour mettre la d�formation en �vidence
    if (pic > 0.9) {
        Color = vec4(0.0, 0.0, 0.0, 1.0);
    } else {
        Color = vec4(Couleur, 1.0);
    }
}