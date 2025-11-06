

#include "MaterialGL.h"
#include "Texture2D.h"

class TextureMaterial : public MaterialGL {
public:
    TextureMaterial(std::string name = "");

    ~TextureMaterial();

    virtual void render(Node *o);

    virtual void animate(Node *o, const float elapsedTime);

    virtual void displayInterface() {};

    virtual void setDiffuseTexture(Texture2D *tex, Texture2D *tex2 = nullptr) {
        if (tex) {
            m_Texture = tex;
        }
        if (tex2) {
            m_Texture2 = tex2;
        } else {
            m_Texture2 = nullptr;
        }
    }

    virtual void setNormalMap(Texture2D *tex) { m_NormalMap = tex;  }

    void TextureMaterial::setPhong(const glm::vec3 &Kd, const glm::vec3 &Ks, const glm::vec3 &Ka, float shininess) {
        // Enregistre les paramètres localement pour la fonction animate()
        m_Kd = Kd;
        m_Ks = Ks;
        m_Ka = Ka;
        m_Shininess = shininess;
    }


protected:
    // Variables de textures
    Texture2D *m_Texture;
    Texture2D *m_Texture2;
    Texture2D *m_NormalMap;
    

    // Variables de Phong
    glm::vec3 m_Ka;
    glm::vec3 m_Kd;
    glm::vec3 m_Ks;
    float m_Shininess;

    GLProgram *vp;
    GLProgram *fp;

    // Localisation des variables uniformes
    GLuint l_View, l_Proj, l_Model; 
    GLuint l_Ka, l_Kd, l_posLum, l_posCam, l_Ks, l_s;
    GLuint l_Tex, l_Tex2, l_NormalMap;
};

