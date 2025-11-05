#version 460

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Proj;
uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 posLum;
uniform vec3 posCam;
uniform vec3 posLum2;
uniform float Deformation;
uniform vec3 posBunny;

out vec3 vKa;
out vec3 vKd;
out vec3 LightDir;
out vec3 Norm;
out vec3 ViewDir;
out vec3 LightDir2;

out gl_PerVertex {
    vec4 gl_Position;
    float gl_PointSize;
    float gl_ClipDistance[];
};

layout(location = 0) in vec3 Position;
layout(location = 2) in vec3 Normal;

void main() {

    // Calcul des paramètres de Phong transmis au FS
    LightDir = posLum - Position;
    LightDir2 = posLum2 - Position;
    Norm = normalize(Normal);
    ViewDir = posCam - Position;
    vKa = Ka;
    vKd = Kd;

    // Déformation du sol seulement (Examen)
    float distance = length(posBunny.xz - Position.xz);
    vec3 newPos = Position;
    if (distance > 2.0) {
        newPos = Position + Deformation * Normal;
    }


    gl_Position = Proj * View * Model * vec4(newPos, 1.0);

} 