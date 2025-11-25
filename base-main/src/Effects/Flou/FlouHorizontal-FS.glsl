#version 460

uniform sampler2D myFBO;

in vec2 uv;

layout(location = 0) out vec4 Color;

void main() {
    // Taille en texels de la texture
    ivec2 tSize = textureSize(myFBO, 0); 
    
    vec3 Couleur = vec3(0.0);
    int compteur = 0;
    
    // k = 5 pour un flou 3x3
    int k = 10;
    int moitie = k / 2;
    
    for (int i = -moitie; i <= moitie; i++) {
        // Coordonnées du texel voisin
        vec2 voisinUV = uv + vec2(float(i) / tSize.x, 0.0);
            
        Couleur += texture(myFBO, voisinUV).rgb;
        compteur++;
        
    }
    
    // Moyenne des couleurs
    vec3 CouleurMoyenne = Couleur / float(compteur);
    Color = vec4(CouleurMoyenne, 1.0);
}