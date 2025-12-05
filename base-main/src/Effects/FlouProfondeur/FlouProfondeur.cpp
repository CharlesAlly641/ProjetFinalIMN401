
#include "FlouProfondeur.h"
#include <glm/gtc/type_ptr.hpp>

FlouProfondeur::FlouProfondeur(std::string name) : EffectGL(name) {
    vp = new GLProgram(EffectPath + "common/Effect-VS.glsl", GL_VERTEX_SHADER);
    fp = new GLProgram(EffectPath + "FlouProfondeur/FlouProfondeur-FS.glsl", GL_FRAGMENT_SHADER);

    FBO = new FrameBufferObject("myFBO", 1024, 1024);
    m_flou = new Flou("FlouProfondeur");

    l_TextureScene = glGetUniformLocation(fp->getId(), "textureScene");
    l_TextureFloue = glGetUniformLocation(fp->getId(), "textureFloue");
    l_LargeurZoneNonFloue = glGetUniformLocation(fp->getId(), "zoneNette");
    l_QuantiteFlou = glGetUniformLocation(fp->getId(), "quantiteFlou");

}

FlouProfondeur::~FlouProfondeur() {
    delete FBO;
    delete m_flou;
}

void FlouProfondeur::apply(FrameBufferObject *src, FrameBufferObject *target) {
    // Passe 1: Flouter la scène
    m_flou->apply(src, FBO);

    // Passe 2: Combiner selon la "profondeur"
    // Définir la texture source comme src
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, src->getColorTexture()->getId());

    // Définir la texture de la scène floutée comme FBO
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, FBO->getColorTexture()->getId());

    // Définir la cible comme target si non nul
    if (target)
        target->enable();

    // Nettoyer les tampons
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    // Activer le fragment shader fp
    m_ProgramPipeline->useProgramStage(vp, GL_VERTEX_SHADER_BIT);
    m_ProgramPipeline->useProgramStage(fp, GL_FRAGMENT_SHADER_BIT);
    m_ProgramPipeline->link();

    // Passage des uniformes au FS
    glProgramUniform1i(fp->getId(), l_TextureScene, 0);
    glProgramUniform1i(fp->getId(), l_TextureFloue, 1);
    glProgramUniform1f(fp->getId(), l_LargeurZoneNonFloue, 0.2f);   
    glProgramUniform1f(fp->getId(), l_QuantiteFlou, 1.0f);  

    // Activer le pipeline
    m_ProgramPipeline->bind();

    // Afficher le quad
    drawQuad();

    // Désactiver le pipeline et les textures
    m_ProgramPipeline->release();

    // Désactiver les textures
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (target)
        target->disable();
}

void FlouProfondeur::animate(const float elapsedTime) {
}