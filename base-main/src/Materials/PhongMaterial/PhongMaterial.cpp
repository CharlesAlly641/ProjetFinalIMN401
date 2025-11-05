
#include "PhongMaterial.h"
#include "Node.h"
#include <glm/gtc/type_ptr.hpp>

PhongMaterial::PhongMaterial(std::string name) : MaterialGL(name) {

    vp = new GLProgram(MaterialPath + "PhongMaterial/Phong-VS.glsl", GL_VERTEX_SHADER);
    fp = new GLProgram(MaterialPath + "PhongMaterial/Phong-FS.glsl", GL_FRAGMENT_SHADER);

    m_ProgramPipeline->useProgramStage(vp, GL_VERTEX_SHADER_BIT);
    m_ProgramPipeline->useProgramStage(fp, GL_FRAGMENT_SHADER_BIT);

    l_View = glGetUniformLocation(vp->getId(), "View");
    l_Proj = glGetUniformLocation(vp->getId(), "Proj");
    l_Model = glGetUniformLocation(vp->getId(), "Model");
    l_Ka = glGetUniformLocation(vp->getId(), "Ka");
    l_Kd = glGetUniformLocation(vp->getId(), "Kd");
    l_posLum = glGetUniformLocation(vp->getId(), "posLum");
    l_posCam = glGetUniformLocation(vp->getId(), "posCam");
    l_Ks = glGetUniformLocation(fp->getId(), "Ks");
    l_s = glGetUniformLocation(fp->getId(), "s");
    l_posLum2 = glGetUniformLocation(vp->getId(), "posLum2"); // (Examen)
    l_Time = glGetUniformLocation(vp->getId(), "Deformation"); // (Examen)
    l_posBunny = glGetUniformLocation(vp->getId(), "posBunny"); // (Examen)
}

PhongMaterial::~PhongMaterial() {}

void PhongMaterial::render(Node *o) {

    m_ProgramPipeline->bind();

    o->drawGeometry(GL_TRIANGLES);
    m_ProgramPipeline->release();
}

void PhongMaterial::animate(Node *o, const float elapsedTime) {

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
    glProgramUniform3f(vp->getId(), l_Ka, 0.1, 0.1, 0.1);
    glProgramUniform3f(vp->getId(), l_Kd, 0.8, 0.2, 0.2);
    glProgramUniform3f(fp->getId(), l_Ks, 1.0, 1.0, 1.0);
    glProgramUniform1f(fp->getId(), l_s, 32.0f);

    // Conversion de la lumière du repère scène vers le repère objet
    Node *lumiere = Scene::getInstance()->getNode("Lumiere");
    glm::vec3 LumiereScene = lumiere->frame()->getModelMatrix() * glm::vec4(0.0, 0.0, 0.0, 1.0);
    glm::vec3 LumiereObjet = Scene::getInstance()->getSceneNode()->frame()->convertPtTo(LumiereScene, o->frame());
    glProgramUniform3fv(vp->getId(), l_posLum, 1, glm::value_ptr(LumiereObjet));

    Node *lumiere2 = Scene::getInstance()->getNode("Lumiere2");
    glm::vec3 LumiereScene2 = lumiere2->frame()->getModelMatrix() * glm::vec4(0.0, 0.0, 0.0, 1.0);
    glm::vec3 LumiereObjet2 = Scene::getInstance()->getSceneNode()->frame()->convertPtTo(LumiereScene2, o->frame());
    glProgramUniform3fv(vp->getId(), l_posLum2, 1, glm::value_ptr(LumiereObjet2));

    // Conversion de la caméra du repère scène vers le repère objet
    Camera *camera = Scene::getInstance()->camera();
    glm::vec3 CameraScene = camera->frame()->getModelMatrix() * glm::vec4(0.0, 0.0, 0.0, 1.0);
    glm::vec3 CameraObjet = Scene::getInstance()->getSceneNode()->frame()->convertPtTo(CameraScene, o->frame());
    glProgramUniform3fv(vp->getId(), l_posCam, 1, glm::value_ptr(CameraObjet));

    // On trouve les coordonnées du noeud Bunny (Examen)
    Node* bunny = Scene::getInstance()->getNode("Bunny");
    glm::vec3 BunnyScene = bunny->frame()->getModelMatrix() * glm::vec4(0.0, 0.0, 0.0, 1.0);
    glm::vec3 BunnyObjet = Scene::getInstance()->getSceneNode()->frame()->convertPtTo(BunnyScene, o->frame());
    glProgramUniform3fv(vp->getId(), l_posBunny, 1, glm::value_ptr(BunnyObjet));

    // On transmet le temps au vertex shader (Examen)
    float deformation = 0.75 * sin(elapsedTime * 1.0);
    if (o->getName() == "Sol") {
        glProgramUniform1f(vp->getId(), l_Time, deformation);
    }
}
