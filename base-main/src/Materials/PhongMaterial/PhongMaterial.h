

#include "MaterialGL.h"

class PhongMaterial : public MaterialGL {
public:
    PhongMaterial(std::string name = "");

    ~PhongMaterial();

    virtual void render(Node *o);

    virtual void animate(Node *o, const float elapsedTime);

    virtual void displayInterface() {};

protected:
    GLProgram *vp;
    GLProgram *fp;

    GLuint l_View, l_Proj, l_Model; // location of uniforms
    GLuint l_Ka, l_Kd, l_posLum, l_posCam, l_Ks, l_s;
    GLuint l_posLum2, l_Time, l_posBunny; // (Examen)
    
};

