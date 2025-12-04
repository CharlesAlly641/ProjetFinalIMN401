#version 460

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Proj;

uniform float Time;
uniform float Amplitude; 
uniform float Frequence;

out gl_PerVertex {
    vec4 gl_Position;
};
flat out float pic;

layout(location = 0) in vec3 Position;
layout(location = 2) in vec3 Normal;

void main()
{
    vec3 displacedPos = Position;
    pic = 0.0;

    // Déformation aux sommets qui ont des index "pairs" uniquement
    if (gl_VertexID %  2 == 0)
    {
        float displacement = Amplitude * cos(Time * Frequence);
        displacedPos += Normal * displacement;

        // On met pic à 1 si le sommet a subit la déformation
        pic = 1.0;
    }

    // Mouvement d'oscillation de l'Objet
    float amplitude = 0.5;
    float vitesse = 0.002;
    float decalage = amplitude * sin(Time * vitesse);

    gl_Position = Proj * View * Model * vec4(displacedPos + decalage, 1.0);
}
