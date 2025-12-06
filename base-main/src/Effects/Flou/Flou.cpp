
#include "Flou.h"
#include <glm/gtc/type_ptr.hpp>

Flou::Flou(std::string name) : EffectGL(name) {
    vp = new GLProgram(EffectPath + "common/Effect-VS.glsl", GL_VERTEX_SHADER);
    fph = new GLProgram(EffectPath + "Flou/FlouHorizontal-FS.glsl", GL_FRAGMENT_SHADER);
    fpv = new GLProgram(EffectPath + "Flou/FlouVertical-FS.glsl", GL_FRAGMENT_SHADER);

    tmp = new FrameBufferObject("Floutmp", 1024, 1024);

    l_TextureH = glGetUniformLocation(fph->getId(), "myFBO");
    l_TextureV = glGetUniformLocation(fpv->getId(), "myFBO");
}

Flou::~Flou() {
    delete tmp;
}

void Flou::apply(FrameBufferObject *src, FrameBufferObject *target) {

    // PASSE 1 : Flou Horizontal
    // 1. Définir la texture source comme src
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, src->getColorTexture()->getId());

    // 2. Définir la cible comme tmp (activer le FBO tmp)
    tmp->enable();

    // 3. Nettoyer les tampons
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    // 4. Activer le fragment shader fph
    m_ProgramPipeline->useProgramStage(vp, GL_VERTEX_SHADER_BIT);
    m_ProgramPipeline->useProgramStage(fph, GL_FRAGMENT_SHADER_BIT);
    m_ProgramPipeline->link();

    // 5. Activer le pipeline
    m_ProgramPipeline->bind();

    // 6. Afficher le quad
    drawQuad();

    // 7. Désactiver le pipeline
    m_ProgramPipeline->release();

    // 8. Désactiver le FBO tmp
    tmp->disable();
    
    // === PASSE 2: Flou Vertical ===

    // 1. Définir la texture source comme tmp
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tmp->getColorTexture()->getId());

    // 2. Définir la cible comme target si non nul (activer le FBO target)
    if (target)
        target->enable();

    // 3. Nettoyer les tampons
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 4. Activer le fragment shader fpv (en utilisant useProgramStage)
    m_ProgramPipeline->useProgramStage(vp, GL_VERTEX_SHADER_BIT);
    m_ProgramPipeline->useProgramStage(fpv, GL_FRAGMENT_SHADER_BIT);
    m_ProgramPipeline->link();

    // 5. Activer le pipeline
    m_ProgramPipeline->bind();

    // 6. Afficher le quad
    drawQuad();

    // 7. Désactiver le pipeline
    m_ProgramPipeline->release();

    // 8. Désactiver le FBO target
    if (target)
        target->disable();
}

void Flou::animate(const float elapsedTime) {}
