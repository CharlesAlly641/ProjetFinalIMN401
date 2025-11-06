#version 460

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Proj;
uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 posLum;
uniform vec3 posCam;

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
    Norm = normalize(Normal);
    ViewDir = posCam - Position;
    vKa = Ka;
    vKd = Kd;

    gl_Position = Proj * View * Model * vec4(newPos, 1.0);

} 