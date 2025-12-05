#version 460

uniform sampler2D textureScene;      
uniform sampler2D textureFloue;     
     
uniform float zoneNette;           
uniform float quantiteFlou;          

in vec2 uv;

layout(location = 0) out vec4 Couleur;

void main() {
    vec3 couleurNette = texture(textureScene, uv).rgb;
    vec3 couleurFloue = texture(textureFloue, uv).rgb;
    
    // Calcul de la distance entre le pixel actuel et le centre
    vec2 centre = vec2(0.5, 0.5);
    float dist = length(uv - centre);
    
    // Calcul combien de flou s'applique selon la position
    float facteurFlou = 0.0; 
    
    // Si on est en dehors de la zone nette, on applique du flou
    if (dist > zoneNette) {
        // Calcul de l'intensité du flou entre 0 et 1
        facteurFlou = (dist - zoneNette) / zoneNette;
        facteurFlou = clamp(facteurFlou, 0.0, 1.0); 

        // Application de l'intensité globale du flou
        facteurFlou = facteurFlou * quantiteFlou;
    }
    
    // Application d'une transition entre le net et le flou
    facteurFlou = smoothstep(0.0, 1.0, facteurFlou);
    
    // Mélange des deux versions de couleur
    vec3 couleurFinale = mix(couleurNette, couleurFloue, facteurFlou);
    Couleur = vec4(couleurFinale, 1.0);
}