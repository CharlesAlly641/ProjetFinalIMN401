
#include "RotationMaterial.h"
#include "Node.h"
#include <glm/gtc/type_ptr.hpp>

RotationMaterial::RotationMaterial(std::string name) : MaterialGL(name) {}

RotationMaterial::~RotationMaterial() {}

// La méthode render est vide
void RotationMaterial::render(Node *o) {}

void RotationMaterial::animate(Node *o, const float elapsedTime) {
    // Translation de 1 autour de l'axe Y
    o->frame()->rotate(glm::vec3(0.0, 1.0, 0.0), 0.01f);
}
