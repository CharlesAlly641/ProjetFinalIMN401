#version 460

uniform vec3 Ks;
uniform float s;

in vec3 vKa;
in vec3 vKd;
in vec3 LightDir;
in vec3 Norm;
in vec3 ViewDir;
in vec3 LightDir2;

layout(location = 0) out vec4 Color;


void main() {

    // Calcul des paramètres de Phong avec posLum1
    vec3 L = normalize(LightDir);
    vec3 N = Norm;
    vec3 V = normalize(ViewDir);
    vec3 R = reflect(-L, N);
    vec3 ambiant = vKa;
    vec3 diffus = vKd * max(dot(N, L), 0.0);
    vec3 spec = Ks * pow(max(dot(R, V), 0.0), s);

    // Calcul des paramètres de Phong avec posLum2
    vec3 L2 = normalize(LightDir2);
    vec3 R2 = reflect(-L2, N);
    vec3 ambiant2 = vKa;
    vec3 diffus2 = vKd*max(dot(N, L2), 0.0);
    vec3 spec2 = Ks * pow(max(dot(R2, V), 0.0), s);

    // Calcul de la couleur
    vec3 Couleur = ambiant + diffus + spec + ambiant2 + diffus2 + spec2;

    Color = vec4(Couleur, 1.0);
}