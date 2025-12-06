#version 460
in float pic;
uniform vec3 Couleur;
layout(location = 0) out vec4 Color;

void main() {
    // On ajuste la couleur selon si c'est un pic ou non pour mettre la déformation en évidence
    // On fait une interpolation pour adoucir la transition entre les pics
    vec3 noir = vec3(0.0, 0.0, 0.0);
    vec3 couleurFinale = mix(Couleur, noir, pic);
    Color = vec4(couleurFinale, 1.0);
}