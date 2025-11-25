
#pragma once

#include "EffectGL.h"
#include "Effects/Flou/Flou.h"

class FlouProfondeur : public EffectGL {
public:
    FlouProfondeur(std::string name);
    ~FlouProfondeur();

    virtual void apply(FrameBufferObject *src, FrameBufferObject *target);
    virtual void animate(const float elapsedTime);
    virtual void displayInterface() {};

protected:
    GLProgram *vp;
    GLProgram *fp;

    FrameBufferObject *FBO;
    Flou *m_flou;

    GLuint l_TextureScene;
    GLuint l_TextureFloue;
    GLuint l_FocusDistance;
    GLuint l_FocusPlage;
    GLuint l_QuantiteFlou;
};