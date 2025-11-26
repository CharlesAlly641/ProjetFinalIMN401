
#include "TextureMaterial.h"
#include "Node.h"
#include <glm/gtc/type_ptr.hpp>

TextureMaterial::TextureMaterial(std::string name) : MaterialGL(name) {

    vp = new GLProgram(MaterialPath + "TextureMaterial/Texture-VS.glsl", GL_VERTEX_SHADER);
    fp = new GLProgram(MaterialPath + "TextureMaterial/Texture-FS.glsl", GL_FRAGMENT_SHADER);

    m_ProgramPipeline->useProgramStage(vp, GL_VERTEX_SHADER_BIT);
    m_ProgramPipeline->useProgramStage(fp, GL_FRAGMENT_SHADER_BIT);

    m_Texture = nullptr;

    l_View = glGetUniformLocation(vp->getId(), "View");
    l_Proj = glGetUniformLocation(vp->getId(), "Proj");
    l_Model = glGetUniformLocation(vp->getId(), "Model");
    l_Ka = glGetUniformLocation(fp->getId(), "Ka");
    l_Kd = glGetUniformLocation(fp->getId(), "Kd");
    l_Ks = glGetUniformLocation(fp->getId(), "Ks");
    l_s = glGetUniformLocation(fp->getId(), "s");
    l_posLum = glGetUniformLocation(vp->getId(), "posLum");
    l_posLum2 = glGetUniformLocation(vp->getId(), "posLum2");
    l_posCam = glGetUniformLocation(vp->getId(), "posCam");
    l_Tex = glGetUniformLocation(fp->getId(), "Tex");
    l_Tex2 = glGetUniformLocation(fp->getId(), "Tex2");
    l_NormalMap = glGetUniformLocation(fp->getId(), "NormalMap");
    l_Time = glGetUniformLocation(vp->getId(), "Time");
    l_HeightMap = glGetUniformLocation(vp->getId(), "HeightMap");
    l_HeightScale = glGetUniformLocation(vp->getId(), "HeightScale");

    m_HeightMap = nullptr;
}

TextureMaterial::~TextureMaterial() {}

void TextureMaterial::render(Node *o) {

    m_ProgramPipeline->bind();

    // Liaison des textures au canaux
    if (m_Texture) { glBindTextureUnit(0, m_Texture->getId()); }
    if (m_Texture2) { glBindTextureUnit(1, m_Texture2->getId()); }
    if (m_NormalMap) { glBindTextureUnit(2, m_NormalMap->getId()); }
    if (m_HeightMap) {glBindTextureUnit(3, m_HeightMap->getId());}

    o->drawGeometry(GL_TRIANGLES);
    m_ProgramPipeline->release();
}

void TextureMaterial::animate(Node *o, const float elapsedTime) {

    /**********************************************
    TP 2 - A completer
    Calculer et Transmettre les matrices Model View et Proj au shaders
    - Utilisez glm::value_ptr(mat) pour trouver le pointeur de la matrice mat a transmettre au GPU via la fonction glProgramUniform*()
    - Une matrice 4X4 se transmet grace a glProgramUniformMatrix4fv
    ***********************************************/
    // On récupère les matrices MVP
    glm::mat4 Model = o->frame()->getModelMatrix();
    glm::mat4 View = Scene::getInstance()->camera()->getViewMatrix();
    glm::mat4 Proj = Scene::getInstance()->camera()->getProjectionMatrix();

    // On transmet les valeurs des uniformes au Vertex Shader
    glProgramUniformMatrix4fv(vp->getId(), l_Model, 1, GL_FALSE, glm::value_ptr(Model));
    glProgramUniformMatrix4fv(vp->getId(), l_View, 1, GL_FALSE, glm::value_ptr(View));
    glProgramUniformMatrix4fv(vp->getId(), l_Proj, 1, GL_FALSE, glm::value_ptr(Proj));

    // On transmet les paramètres du modèle de Phong au VS
    glProgramUniform1f(fp->getId(), l_Ka, m_Ka);
    glProgramUniform1f(fp->getId(), l_Kd, m_Kd);
    glProgramUniform1f(fp->getId(), l_Ks, m_Ks);
    glProgramUniform1f(fp->getId(), l_s, m_Shininess);


    // Conversion de la lumière du repère scène vers le repère objet
    Node *lumiere = Scene::getInstance()->getNode("L");
    glm::vec3 LumiereObjet = lumiere->frame()->convertPtTo(glm::vec3(0.0, 0.0, 0.0), o->frame());
    glProgramUniform3fv(vp->getId(), l_posLum, 1, glm::value_ptr(LumiereObjet));

    
    Node *lumiere2 = Scene::getInstance()->getNode("Objet en rotation");
    glm::vec3 LumiereObjet2 = lumiere2->frame()->convertPtTo(glm::vec3(0.0, 0.0, 0.0), o->frame());
    glProgramUniform3fv(vp->getId(), l_posLum2, 1, glm::value_ptr(LumiereObjet2));

    // Conversion de la caméra du repère scène vers le repère objet
    Camera *camera = Scene::getInstance()->camera();
    glm::vec3 CameraObjet = camera->frame()->convertPtTo(glm::vec3(0.0, 0.0, 0.0), o->frame());
    glProgramUniform3fv(vp->getId(), l_posCam, 1, glm::value_ptr(CameraObjet));

    // On indique au Fragment Shader où se trouve les textures
    if (m_Texture) {
        glProgramUniform1i(fp->getId(), l_Tex, 0);
    }
    if (m_Texture2) {
        glProgramUniform1i(fp->getId(), l_Tex2, 1);
    }
    if (m_NormalMap) {
        glProgramUniform1i(fp->getId(), l_NormalMap, 2);
    }
    if (m_HeightMap) {
        glProgramUniform1i(vp->getId(), l_HeightMap, 3);
        glProgramUniform1f(vp->getId(), l_HeightScale, 0.1f); // amplitude
    }

    // Envoie du temps au VS pour le displacement mapping si c'est le bon objet
    if (o->getName() == "Bunny") {
        glProgramUniform1f(vp->getId(), l_Time, elapsedTime);
    }
}


