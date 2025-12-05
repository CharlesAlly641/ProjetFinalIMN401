
#include "EngineGL.h"
#include "Scene.h"

#include "Materials/BaseMaterial/BaseMaterial.h"
#include "Materials/TextureMaterial/TextureMaterial.h"
#include "Materials/RotationMaterial/RotationMaterial.h"

#include "Texture2D.h"

#define M_PI 3.14159265358979323846264338327950288

bool EngineGL::init() {
    LOG_INFO << "Initializing Scene" << std::endl;

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, m_Width, m_Height);
    setClearColor(glm::vec4(.5, .5, .5, 1));

    // light node L
    Node *L = scene->getNode("L");
    L->frame()->translate(glm::vec3(10, 10, 0));
    L->frame()->translate(glm::vec3(0, 1.75, 0));
    L->frame()->scale(glm::vec3(0.1));
    L->frame()->translate(glm::vec3(-20.0, 20.0, 20.0));
    L->setModel(scene->m_Models.get<ModelGL>(ObjPath + "Sphere.obj"));
    scene->getSceneNode()->adopt(L);

    BaseMaterial *lightMaterial = new BaseMaterial("light");
    L->setMaterial(lightMaterial);

    // box
    Node *box = scene->getNode("Box");
    box->setModel(scene->m_Models.get<ModelGL>(ObjPath + "Box.obj"));
    box->frame()->translate(glm::vec3(0.0, 1.1, 0.0));
    Texture2D *textureBox = new Texture2D(ObjPath + "Textures/Box_diff.jpg");
    Texture2D *textureBoxN = new Texture2D(ObjPath + "Textures/Box_nrm.jpg");
    TextureMaterial *matBox = new TextureMaterial("matBox");
    matBox->setDiffuseTexture(textureBox, nullptr);
    matBox->setNormalMap(textureBoxN);
    matBox->setPhong(1, 0.5, 0.1, 60.0);
    box->setMaterial(matBox);

    // Pillar
    Node *pillar = scene->getNode("Pillar");
    pillar->setModel(scene->m_Models.get<ModelGL>(ObjPath + "Pillar.obj"));
    Texture2D *texturePillar = new Texture2D(ObjPath + "Textures/Pillar_diff.jpg");
    Texture2D *texturePillarN = new Texture2D(ObjPath + "Textures/Pillar_nrm.jpg");
    TextureMaterial *matPillar = new TextureMaterial("matPillar");
    matPillar->setDiffuseTexture(texturePillar, nullptr);
    matPillar->setNormalMap(texturePillarN);
    matPillar->setPhong(1, 0.5, 0.1, 20.0);
    pillar->frame()->rotate(glm::vec3(0.0, 1.0, 0.0), M_PI/2);
    pillar->setMaterial(matPillar);
    pillar->frame()->translate(glm::vec3(0.0, 1.1, 0.0));

    // (0,0.775,0) is the center of the pillar
    
    // Création du bunny
    Node *bunny = scene->getNode("Bunny");
    bunny->setModel(scene->m_Models.get<ModelGL>(ObjPath + "Bunny.obj"));
    Texture2D *textureBunny = new Texture2D(ObjPath + "Textures/Bunny1.png");
    Texture2D *textureBunny2 = new Texture2D(ObjPath + "Textures/Bunny2.png");
    Texture2D *textureBunnyN = new Texture2D(ObjPath + "Textures/Bunny_N.png");
    TextureMaterial* matBunny = new TextureMaterial("matBunny");
    bunny->frame()->scale(glm::vec3(2.0));
    bunny->frame()->translate(glm::vec3(0.4, 0.03, 0.8));
    matBunny->setDiffuseTexture(textureBunny, textureBunny2);
    matBunny->setNormalMap(textureBunnyN);
    matBunny->setPhong(1, 0.5, 0.1, 32.0);
    bunny->setMaterial(matBunny);

    // Création de l'objet statue (sur le pilier)
    Node *statue = scene->getNode("statue");
    statue->setModel(scene->m_Models.get<ModelGL>(ObjPath + "lion.obj"));
    Texture2D *textureStatue = new Texture2D(ObjPath + "Textures/textures_lion/material0_basecolor.png");
    Texture2D *textureStatueN = new Texture2D(ObjPath + "Textures/textures_lion/material0_normal.png");
    TextureMaterial *matStatue = new TextureMaterial("matStatue");
    statue->frame()->scale(glm::vec3(0.013));
    statue->frame()->translate(glm::vec3(-1.5,35.0, 0.0));
    statue->frame()->rotate(glm::vec3(1.0, 0.0, 0.0), -M_PI / 2);

    matStatue->setDiffuseTexture(textureStatue, nullptr);
    matStatue->setNormalMap(textureStatueN);
    matStatue->setPhong(1, 0.5, 0.1, 32.0);
    statue->setMaterial(matStatue);

    // Création de la roche 
    Node *boulder = scene->getNode("Boulder");
    boulder->setModel(scene->m_Models.get<ModelGL>(ObjPath + "boulder_01_4k.obj"));
    Texture2D *textureBoulder = new Texture2D(ObjPath + "Textures/boulder_01_diff_4k.jpg");
    Texture2D *textureBoulderN = new Texture2D(ObjPath + "Textures/boulder_01_nor_gl_4k.png"); // normal map en EXR
    TextureMaterial *matBoulder = new TextureMaterial("matBoulder");
    matBoulder->setDiffuseTexture(textureBoulder, nullptr);
    matBoulder->setNormalMap(textureBoulderN);
    matBoulder->setPhong(1.0f, 0.6f, 0.1f, 32.0f);
    boulder->frame()->translate(glm::vec3(-2.3f, 0.0f, 1.0f)); // position sur le sol
    boulder->frame()->rotate(glm::vec3(0.0, 1.0, 0.0), M_PI);
    boulder->frame()->scale(glm::vec3(1.5f));                 
    boulder->setMaterial(matBoulder);

    Node *boulder2 = scene->getNode("Boulder2");
    boulder2->setModel(scene->m_Models.get<ModelGL>(ObjPath + "boulder_01_4k.obj"));
    TextureMaterial *matBoulder2 = new TextureMaterial("matBoulder2");
    matBoulder2->setDiffuseTexture(textureBoulder, nullptr);
    matBoulder2->setNormalMap(textureBoulderN);
    matBoulder2->setPhong(1.0f, 0.6f, 0.1f, 32.0f);
    boulder2->frame()->translate(glm::vec3(-2.3f, 0.0f, -0.7f)); // position sur le sol
    boulder2->frame()->rotate(glm::vec3(0.0, 1.0, 0.0), M_PI);
    boulder2->frame()->scale(glm::vec3(1.5f));
    boulder2->setMaterial(matBoulder2);

    Node *boulder3 = scene->getNode("Boulder3");
    boulder3->setModel(scene->m_Models.get<ModelGL>(ObjPath + "boulder_01_4k.obj"));
    TextureMaterial *matBoulder3 = new TextureMaterial("matBoulder3");
    matBoulder3->setDiffuseTexture(textureBoulder, nullptr);
    matBoulder3->setNormalMap(textureBoulderN);
    matBoulder3->setPhong(1.0f, 0.6f, 0.1f, 32.0f);
    boulder3->frame()->translate(glm::vec3(2.0f, 0.0f, 1.0f)); // position sur le sol
    boulder3->frame()->rotate(glm::vec3(0.0, 1.0, 0.0), M_PI);
    boulder3->frame()->scale(glm::vec3(1.5f));
    boulder3->setMaterial(matBoulder3);

    Node *boulder4 = scene->getNode("Boulder4");
    boulder4->setModel(scene->m_Models.get<ModelGL>(ObjPath + "boulder_01_4k.obj"));
    TextureMaterial *matBoulder4 = new TextureMaterial("matBoulder4");
    matBoulder4->setDiffuseTexture(textureBoulder, nullptr);
    matBoulder4->setNormalMap(textureBoulderN);
    matBoulder4->setPhong(1.0f, 0.6f, 0.1f, 32.0f);
    boulder4->frame()->translate(glm::vec3(2.0f, 0.0f, -0.7f)); // position sur le sol
    boulder4->frame()->rotate(glm::vec3(0.0, 1.0, 0.0), M_PI);
    boulder4->frame()->scale(glm::vec3(1.5f));
    boulder4->setMaterial(matBoulder4);

    Node *boulder5 = scene->getNode("Boulder5");
    boulder5->setModel(scene->m_Models.get<ModelGL>(ObjPath + "boulder_01_4k.obj"));
    TextureMaterial *matBoulder5 = new TextureMaterial("matBoulder5");
    matBoulder5->setDiffuseTexture(textureBoulder, nullptr);
    matBoulder5->setNormalMap(textureBoulderN);
    matBoulder5->setPhong(1.0f, 0.6f, 0.1f, 32.0f);
    boulder5->frame()->translate(glm::vec3(-1.5f, 0.0f, -2.4f));
    boulder5->frame()->rotate(glm::vec3(0, 1, 0), M_PI);      // oriente vers la caméra
    boulder5->frame()->scale(glm::vec3(1.5f));
    boulder5->setMaterial(matBoulder5);

    Node *boulder6 = scene->getNode("Boulder6");
    boulder6->setModel(scene->m_Models.get<ModelGL>(ObjPath + "boulder_01_4k.obj"));
    TextureMaterial *matBoulder6 = new TextureMaterial("matBoulder6");
    matBoulder6->setDiffuseTexture(textureBoulder, nullptr);
    matBoulder6->setNormalMap(textureBoulderN);
    matBoulder6->setPhong(1.0f, 0.6f, 0.1f, 32.0f);
    boulder6->frame()->translate(glm::vec3(0.0f, 0.0f, -2.4f)); // position sur le sol
    boulder6->frame()->rotate(glm::vec3(0.0, 1.0, 0.0), M_PI);
    boulder6->frame()->scale(glm::vec3(1.5f));
    boulder6->setMaterial(matBoulder6);

    Node *boulder7 = scene->getNode("Boulder7");
    boulder7->setModel(scene->m_Models.get<ModelGL>(ObjPath + "boulder_01_4k.obj"));
    TextureMaterial *matBoulder7 = new TextureMaterial("matBoulder7");
    matBoulder7->setDiffuseTexture(textureBoulder, nullptr);
    matBoulder7->setNormalMap(textureBoulderN);
    matBoulder7->setPhong(1.0f, 0.6f, 0.1f, 32.0f);
    boulder7->frame()->translate(glm::vec3(1.5f, 0.0f, -2.4f)); // position sur le sol
    boulder7->frame()->rotate(glm::vec3(0.0, 1.0, 0.0), M_PI);
    boulder7->frame()->scale(glm::vec3(1.5f));
    boulder7->setMaterial(matBoulder7);

    Node *boulder8 = scene->getNode("Boulder8");
    boulder8->setModel(scene->m_Models.get<ModelGL>(ObjPath + "boulder_01_4k.obj"));
    TextureMaterial *matBoulder8 = new TextureMaterial("matBoulder8");
    matBoulder8->setDiffuseTexture(textureBoulder, nullptr);
    matBoulder8->setNormalMap(textureBoulderN);
    matBoulder8->setPhong(1.0f, 0.6f, 0.1f, 32.0f);
    boulder8->frame()->translate(glm::vec3(-1.5f, 0.0f, 2.4f));
    boulder8->frame()->rotate(glm::vec3(0, 1, 0), M_PI); // oriente vers la caméra
    boulder8->frame()->scale(glm::vec3(1.5f));
    boulder8->setMaterial(matBoulder8);

    Node *boulder9 = scene->getNode("Boulder9");
    boulder9->setModel(scene->m_Models.get<ModelGL>(ObjPath + "boulder_01_4k.obj"));
    TextureMaterial *matBoulder9 = new TextureMaterial("matBoulder9");
    matBoulder9->setDiffuseTexture(textureBoulder, nullptr);
    matBoulder9->setNormalMap(textureBoulderN);
    matBoulder9->setPhong(1.0f, 0.6f, 0.1f, 32.0f);
    boulder9->frame()->translate(glm::vec3(0.0f, 0.0f, 2.4f));
    boulder9->frame()->rotate(glm::vec3(0, 1, 0), M_PI); // oriente vers la caméra
    boulder9->frame()->scale(glm::vec3(1.5f));
    boulder9->setMaterial(matBoulder9);

    Node *boulder10 = scene->getNode("Boulder10");
    boulder10->setModel(scene->m_Models.get<ModelGL>(ObjPath + "boulder_01_4k.obj"));
    TextureMaterial *matBoulder10 = new TextureMaterial("matBoulder9");
    matBoulder10->setDiffuseTexture(textureBoulder, nullptr);
    matBoulder10->setNormalMap(textureBoulderN);
    matBoulder10->setPhong(1.0f, 0.6f, 0.1f, 32.0f);
    boulder10->frame()->translate(glm::vec3(1.5f, 0.0f, 2.4f));
    boulder10->frame()->rotate(glm::vec3(0, 1, 0), M_PI); // oriente vers la caméra
    boulder10->frame()->scale(glm::vec3(1.5f));
    boulder10->setMaterial(matBoulder10);

    // Création du tronc d’arbre 
    Node *stump = scene->getNode("TreeStump");
    stump->setModel(scene->m_Models.get<ModelGL>(ObjPath + "tree_stump_01_4k.obj"));
    Texture2D *textureStump = new Texture2D(ObjPath + "Textures/tree_stump_01_diff_4k.jpg");
    Texture2D *textureStumpN = new Texture2D(ObjPath + "Textures/tree_stump_01_nor_gl_4k.jpg");
    TextureMaterial *matStump = new TextureMaterial("matStump");
    matStump->setDiffuseTexture(textureStump, nullptr);
    matStump->setNormalMap(textureStumpN);
    matStump->setPhong(1, 0.5, 0.1, 32.0);
    stump->frame()->scale(glm::vec3(0.25));                  
    stump->frame()->translate(glm::vec3(6.0, -0.10, 5.5));
    stump->setMaterial(matStump);

    // Création d'un noeud 
    Node *noeud = scene->getNode("Noeud");
    pillar->adopt(noeud);
    noeud->setMaterial(new RotationMaterial("rotMat"));
    
    // Création d'un objet en mouvement 
    Node *rotObjet = scene->getNode("Objet en mouvement");
    rotObjet->setModel(scene->m_Models.get<ModelGL>(ObjPath + "Sphere.obj"));
    rotObjet->setMaterial(new BaseMaterial("baseMat"));
    rotObjet->frame()->translate(glm::vec3(0.5, 1.2, 0.0));
    rotObjet->frame()->scale(glm::vec3(0.3, 0.3, 0.3));
    noeud->adopt(rotObjet);
    rotObjet->frame()->translate(glm::vec3(0.0, 1.1, 0.0));

    // Création d'un objet sol
    Node *sol = scene->getNode("Sol");
    sol->setModel(scene->m_Models.get<ModelGL>(ObjPath + "Wall.obj"));
    TextureMaterial* solMat = new TextureMaterial("solMat");
    sol->setMaterial(solMat);
    sol->frame()->translate(glm::vec3(0.0, -0.1, 0.0));
    sol->frame()->scale(glm::vec3(0.9, 0.9, 0.9));
    solMat->setPhong(1, 0.5, 0.1, 32.0);

    Node *sol2 = scene->getNode("Sol2");
    sol2->setModel(scene->m_Models.get<ModelGL>(ObjPath + "Wall.obj"));
    TextureMaterial *solMat2 = new TextureMaterial("solMat2");
    sol2->setMaterial(solMat2);
    sol2->frame()->translate(glm::vec3(0.0, 1.0, 0.0));
    sol2->frame()->scale(glm::vec3(0.3, 0.3, 0.3));
    solMat2->setPhong(1, 0.5, 0.1, 32.0);

    // Création de la texture du sol
    Texture2D *textureSol = new Texture2D(ObjPath + "Textures/Ground/Ground013_4K-JPG_Color.jpg");
    Texture2D *textureSolN = new Texture2D(ObjPath + "Textures/Ground/Ground013_4K-JPG_NormalDX.jpg");
    solMat->setDiffuseTexture(textureSol, nullptr);
    solMat->setNormalMap(textureSolN);
    solMat2->setDiffuseTexture(textureSol, nullptr);
    solMat2->setNormalMap(textureSolN);

    // Ajout des objets dans la scène
    scene->getSceneNode()->adopt(bunny);
    scene->getSceneNode()->adopt(L);
    scene->getSceneNode()->adopt(box);
    scene->getSceneNode()->adopt(pillar);
    scene->getSceneNode()->adopt(sol);
    pillar->adopt(statue);
    scene->getSceneNode()->adopt(boulder);
    scene->getSceneNode()->adopt(boulder2);
    scene->getSceneNode()->adopt(boulder3);
    scene->getSceneNode()->adopt(boulder4);
    scene->getSceneNode()->adopt(boulder5);
    scene->getSceneNode()->adopt(boulder6);
    scene->getSceneNode()->adopt(boulder7);
    scene->getSceneNode()->adopt(boulder8);
    scene->getSceneNode()->adopt(boulder9);
    scene->getSceneNode()->adopt(boulder10);
    scene->getSceneNode()->adopt(stump);
    scene->getSceneNode()->adopt(sol);
    scene->getSceneNode()->adopt(sol2);


    // Création des FBOs
    myFBO = new FrameBufferObject("myFBO", m_Width, m_Height);
    bloomFBO = new FrameBufferObject("bloomFBO", m_Width, m_Height);

    // Création des effets de post-process
    display = new Display("display");
    flou = new Flou("flou");
    bloom = new Bloom("bloom");
    flouProfondeur = new FlouProfondeur("flouProf");

    setupEngine();
    return (true);
}

void EngineGL::render() {
    glEnable(GL_DEPTH_TEST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    myFBO->enable();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (unsigned int i = 0; i < allNodes->nodes.size(); i++)
        allNodes->nodes[i]->render();
    myFBO->disable();
    bloom->apply(myFBO, bloomFBO);
    flouProfondeur->apply(bloomFBO, NULL);
    
}

void EngineGL::animate(const float elapsedTime) {
    // Animate each node
    for (unsigned int i = 0; i < allNodes->nodes.size(); i++) {
        allNodes->nodes[i]->animate(elapsedTime);
    }

    // Update Camera Buffer
    scene->camera()->updateBuffer();
}

void EngineGL::onWindowResize(int w, int h) {
    m_Width = w;
    m_Height = h;
    glViewport(0, 0, w, h);
    float ratio = (float)w / (float)h;

    scene->resizeViewport(w, h);
    scene->camera()->setPerspectiveProjection(glm::radians(45.0f), ratio, 1.0f, 2000.0f);
}

void EngineGL::setClearColor(glm::vec4 color) {
    glClearColor(color.x, color.y, color.z, color.w);
}

void EngineGL::displayInterface() {
    if (myFBO) {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("FBOs")) {
                ImGui::MenuItem(myFBO->getName().c_str(), NULL, &(myFBO->show_interface));
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        myFBO->displayInterface();
    }

}

// Message callbck error for getting OpenGL problems
// All credits to https://github.com/fendevel/Guide-to-Modern-OpenGL-Functions/blob/master/README.md#gltexture
void message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const *message, void const *user_param) {
    auto const src_str = [source]() {
        switch (source) {
        case GL_DEBUG_SOURCE_API: return "API";
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "WINDOW SYSTEM";
        case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER COMPILER";
        case GL_DEBUG_SOURCE_THIRD_PARTY: return "THIRD PARTY";
        case GL_DEBUG_SOURCE_APPLICATION: return "APPLICATION";
        case GL_DEBUG_SOURCE_OTHER: return "OTHER";
        default: return "";
        }
    }();

    auto const type_str = [type]() {
        switch (type) {
        case GL_DEBUG_TYPE_ERROR: return "ERROR";
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "UNDEFINED_BEHAVIOR";
        case GL_DEBUG_TYPE_PORTABILITY: return "PORTABILITY";
        case GL_DEBUG_TYPE_PERFORMANCE: return "PERFORMANCE";
        case GL_DEBUG_TYPE_MARKER: return "MARKER";
        case GL_DEBUG_TYPE_OTHER: return "OTHER";
        default: return "";
        }
    }();

    auto const severity_str = [severity]() {
        switch (severity) {
        case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
        case GL_DEBUG_SEVERITY_LOW: return "LOW";
        case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM";
        case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
        default: return "";
        }
    }();
    LOG_INFO << src_str << ", " << type_str << ", " << severity_str << ", " << id << ": " << message << '\n';
}

EngineGL::EngineGL(int width, int height) {
    m_Width = width;
    m_Height = height;

    myFBO = NULL;

    scene = Scene::getInstance();
    scene->resizeViewport(m_Width, m_Height);
}

EngineGL::~EngineGL() {}

void EngineGL::setupEngine() {
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
    glDebugMessageCallback(message_callback, nullptr);

    this->allNodes = new NodeCollector();
    allNodes->collect(scene->getRoot());

    LOG_INFO << "initialisation complete" << std::endl;
}