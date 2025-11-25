#version 460
uniform float Ka;
uniform float Kd;
uniform float Ks;
uniform float s;

in vec3 LightDir;
in vec3 Norm;
in vec3 ViewDir;

layout(location = 0) out vec4 Color;


void main() {

    // Calcul des paramètres de Phong avec posLum
    vec3 L = normalize(LightDir);
    vec3 N = Norm;
    vec3 V = normalize(ViewDir);
    vec3 R = reflect(-L, N);
    float ambiant = Ka;
    float diffus = Kd * max(dot(N, L), 0.0);
    float spec = Ks * pow(max(dot(R, V), 0.0), s);


    // Calcul de la couleur
    vec3 couleurLum = glm::vec3(1.0f);
    vec3 Couleur = ambiant + (diffus + spec) * couleurLum;

    Color = vec4(Couleur, 1.0);
}