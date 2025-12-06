#version 460

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Proj;
uniform vec3 posLum;
uniform vec3 posCam;
uniform vec3 posLum2;

out vec3 LightDir;
out vec3 ViewDir;
out vec2 couleur;
out vec3 LightDir2;

out gl_PerVertex {
    vec4 gl_Position;
    float gl_PointSize;
    float gl_ClipDistance[];
};

layout(location = 0) in vec3 Position;
layout(location = 2) in vec3 Normal;
layout(location = 3) in vec3 Texture;
layout(location = 4) in vec4 Tangente;


void main() {
    // Calcul de la matrice TBN
    vec3 T = normalize(Tangente.rgb);
    vec3 N = normalize(Normal);;
    vec3 B = normalize(cross(N, T));
    mat3 TBN = transpose(mat3(T, B, N));

    // Calcul des parametres de Phong transmis au FS
    vec3 L = posLum - Position;
    vec3 L2 = posLum2 - Position;
    LightDir = TBN * L;
    LightDir2 = TBN * L2;
    vec3 V = posCam - Position;
    ViewDir = TBN * V;

    couleur = Texture.xy;

    gl_Position = Proj * View * Model * vec4(Position, 1.0);

} 