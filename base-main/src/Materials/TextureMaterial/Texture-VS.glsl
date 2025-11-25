#version 460

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Proj;
uniform vec3 posLum;
uniform vec3 posCam;
uniform float Time;

uniform sampler2D HeightMap;
uniform float HeightScale;

out vec3 vKa;
out vec3 vKd;
out vec3 LightDir;
out vec3 Norm;
out vec3 ViewDir;
out vec2 couleur;

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
    mat3 TBN = mat3(T, B, N);

    // Calcul des paramètres de Phong transmis au FS
    vec3 L = posLum - Position;
    LightDir = TBN * L;
    Norm = vec3(0.0, 0.0, 1.0);
    vec3 V = posCam - Position;
    ViewDir = TBN * V;

    couleur = Texture.xy;

    // Displacement Mapping avec HeigthMap
    float hauteur = texture(HeightMap, couleur).r;
    float displacement = hauteur * HeightScale;
    vec3 displaced = Position + N * displacement;

    gl_Position = Proj * View * Model * vec4(displaced, 1.0);

} 