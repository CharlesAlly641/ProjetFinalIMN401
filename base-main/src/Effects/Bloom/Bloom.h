#pragma once

#include "EffectGL.h"
#include "Effects/Flou/Flou.h"

class Bloom : public EffectGL {
public:
    Bloom(std::string name);
    ~Bloom();

    virtual void apply(FrameBufferObject *src, FrameBufferObject *target);
    virtual void animate(const float elapsedTime);
    virtual void displayInterface() {};

protected:
    GLProgram *vp;
    GLProgram *fpExtract; // Extraction des zones lumineuses
    GLProgram *fpCombine; // Combinaison bloom + original

    FrameBufferObject *FBO1; // Zones lumineuses extraites
    FrameBufferObject *FBO2; // Résultat du flou

    Flou *flou;

    GLuint l_TextureSrc;
    GLuint l_TextureSrc2;
    GLuint l_TextureBloom;
    GLuint l_Seuil;
};