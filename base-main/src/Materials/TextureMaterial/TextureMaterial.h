

#include "MaterialGL.h"
#include "Texture2D.h"

class TextureMaterial : public MaterialGL {
public:
    TextureMaterial(std::string name = "");

    ~TextureMaterial();

    virtual void render(Node *o);

    virtual void animate(Node *o, const float elapsedTime);

    virtual void displayInterface() {};

    virtual void setTexture(Texture2D *tex) { m_Texture = tex; }

    virtual void setTexture2(Texture2D *tex) { m_Texture2 = tex; }

    virtual void setNormalMap(Texture2D *tex) { m_NormalMap = tex;  }

protected:
    Texture2D *m_Texture;
    Texture2D* m_Texture2;
    Texture2D *m_NormalMap;

    GLProgram *vp;
    GLProgram *fp;

    GLuint l_View, l_Proj, l_Model; // location of uniforms
    GLuint l_Ka, l_Kd, l_posLum, l_posCam, l_Ks, l_s;
    GLuint l_Tex, l_Tex2, l_NormalMap;
    
};

