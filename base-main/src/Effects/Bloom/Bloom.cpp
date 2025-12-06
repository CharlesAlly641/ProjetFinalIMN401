#include "Bloom.h"
#include <glm/gtc/type_ptr.hpp>

Bloom::Bloom(std::string name) : EffectGL(name) {
    vp = new GLProgram(EffectPath + "common/Effect-VS.glsl", GL_VERTEX_SHADER);
    fpExtract = new GLProgram(EffectPath + "Bloom/BloomExtrait-FS.glsl", GL_FRAGMENT_SHADER);
    fpCombine = new GLProgram(EffectPath + "Bloom/BloomCombine-FS.glsl", GL_FRAGMENT_SHADER);

    FBO1 = new FrameBufferObject("BloomFBO1", 1024, 1024);
    FBO2 = new FrameBufferObject("BloomFBO2", 1024, 1024);

    flou = new Flou("FlouBloom");

    l_TextureSrc = glGetUniformLocation(fpExtract->getId(), "myFBO");
    l_Seuil = glGetUniformLocation(fpExtract->getId(), "seuil");
    l_TextureSrc2 = glGetUniformLocation(fpCombine->getId(), "myFBO");
    l_TextureBloom = glGetUniformLocation(fpCombine->getId(), "bloomTexture");
}

Bloom::~Bloom() {
    delete FBO1;
    delete FBO2;
    delete flou;
}

void Bloom::apply(FrameBufferObject *src, FrameBufferObject *target) {
    

     // PASSE 1 : Fragment Lumineux
     // 1. Définir la texture source comme src
     glActiveTexture(GL_TEXTURE0);
     glBindTexture(GL_TEXTURE_2D, src->getColorTexture()->getId());

     // 2. Définir la cible comme FBO1
     FBO1->enable();

     // Nettoyer les tampons
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glDisable(GL_DEPTH_TEST);

     // Activer le fragment shader fpExtract
     m_ProgramPipeline->useProgramStage(vp, GL_VERTEX_SHADER_BIT);
     m_ProgramPipeline->useProgramStage(fpExtract, GL_FRAGMENT_SHADER_BIT);
     m_ProgramPipeline->link();

     glProgramUniform1i(fpExtract->getId(), l_TextureSrc, 0);
     glProgramUniform1f(fpExtract->getId(), l_Seuil, 0.75f);

     // Activer le pipeline
     m_ProgramPipeline->bind();

     // Afficher le quad
     drawQuad();

     // Désactiver le pipeline
     m_ProgramPipeline->release();

     glActiveTexture(GL_TEXTURE0);
     glBindTexture(GL_TEXTURE_2D, 0);

     FBO1->disable();

    // PASSE 2 : Application de l'effet
    flou->apply(FBO1, FBO2);

    // PASSE 3 : Combiner les fragments
    // Activer les deux textures
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, src->getColorTexture()->getId());

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, FBO2->getColorTexture()->getId());

    // Définir la cible comme target si non nul
    if (target)
        target->enable();

    // Nettoyer les tampons
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    // Activer le fragment shader fpCombine
    m_ProgramPipeline->useProgramStage(vp, GL_VERTEX_SHADER_BIT);
    m_ProgramPipeline->useProgramStage(fpCombine, GL_FRAGMENT_SHADER_BIT);
    m_ProgramPipeline->link();

    glProgramUniform1i(fpCombine->getId(), l_TextureSrc, 0); 
    glProgramUniform1i(fpCombine->getId(), l_TextureBloom, 1); 

    // Activer le pipeline
    m_ProgramPipeline->bind();

    // Afficher le quad
    drawQuad();

    // Désactiver le pipeline, textures, target
    m_ProgramPipeline->release();

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (target)
        target->disable();
    
}

void Bloom::animate(const float elapsedTime) {}