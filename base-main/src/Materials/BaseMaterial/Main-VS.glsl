#version 460

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Proj;

uniform float Time;
uniform float Amplitude; 

layout(location = 0) in vec3 Position;
layout(location = 2) in vec3 Normal;

out vec3 vNormal;

void main()
{

    float displacement = Amplitude * (sin(10 * Position.x * Time) + sin(10 * Position.y * Time) + sin(10 * Position.z * Time));

    vec3 displacedPos = Position + Normal * displacement;

    gl_Position = Proj * View * Model * vec4(displacedPos, 1.0);
}
