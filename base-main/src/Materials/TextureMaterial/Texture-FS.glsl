#version 460

uniform float Ks;
uniform float Kd;
uniform float Ka;
uniform float s;
uniform sampler2D Tex;
uniform sampler2D Tex2;
uniform sampler2D NormalMap;

in vec3 LightDir2;
in vec3 LightDir;
in vec3 Norm;
in vec3 ViewDir;
in vec2 couleur;

layout(location = 0) out vec4 Color;


void main() {

    // Recuperation des textures et mixage
    vec4 texColor = texture(Tex, couleur);
    vec4 texColor2 = texture(Tex2, couleur);
    vec4 texNormalMap = texture(NormalMap, couleur);
    vec4 texMix = mix(texColor, texColor2, texColor2.a);

    // Calcul des parametres de Phong avec posLum1 et posLum2
    vec3 L = normalize(LightDir);
    vec3 L2 = normalize(LightDir2);
    vec3 N = normalize(texNormalMap.rgb * 2.0 - 1.0); // N = (valeur réelle + 1) / 2
    vec3 V = normalize(ViewDir);
    vec3 R = reflect(-L, N);
    vec3 R2 = reflect(-L2, N);
    float ambiant = Ka;
    float diffus = Kd * max(dot(N, L), 0.0);
    float diffus2 = Kd * max(dot(N, L2), 0.0);
    float spec = Ks * pow(max(dot(R, V), 0.0), s);
    float spec2 = Ks * pow(max(dot(R2, V), 0.0), s);
    
    // Calcul de l'éclairage
    vec3 couleurLum = vec3(0.7, 0.7, 0.7);
    vec3 couleurLum2 = vec3(0.7, 0.2, 0.2);
    vec3 Couleur = (ambiant*texMix.rgb) + (diffus*texMix.rgb + spec) * couleurLum + (diffus2*texMix.rgb + spec2) * couleurLum2;
    
    // R�sultat final
    Color = vec4(Couleur, 1.0);
}