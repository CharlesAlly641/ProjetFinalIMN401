#version 460

// Textures d'entrée
uniform sampler2D textureScene;      
uniform sampler2D textureFloue;     

// Paramètres de l'effet
uniform float distanceFocus;         
uniform float plageFocus;            
uniform float quantiteFlou;          

in vec2 uv;

layout(location = 0) out vec4 Couleur;

void main() {
    // Calcul des couleurs nette et floue
    vec3 couleurNette = texture(textureScene, uv).rgb;
    vec3 couleurFloue = texture(textureFloue, uv).rgb;
    
    // Calcul de la distance entre le pixel actuel et le centre
    vec2 centre = vec2(0.5, 0.5);
    float profondeur = length(uv - centre);
    
    // Calcul combien de flou s'applique selon la position
    float facteurFlou = 0.0; 
    
    // Différence entre la profondeur actuelle et la distance de focus
    float differenceProfondeur = abs(profondeur - distanceFocus);
    
    // Si on est en dehors de la zone nette, appliquer du flou
    if (differenceProfondeur > plageFocus) {
        // Calcul de l'intensité du flou :
        facteurFlou = (differenceProfondeur - plageFocus) / plageFocus;
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