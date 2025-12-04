#version 460

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Proj;

uniform float Time;
uniform float Amplitude; 
uniform float Frequence;

out gl_PerVertex {
    vec4 gl_Position;
};

layout(location = 0) in vec3 Position;
layout(location = 2) in vec3 Normal;

void main()
{

    float displacement = Amplitude * cos(Time * Frequence);

    vec3 displacedPos = Position + Normal * displacement;

    float amplitude = 0.5;
	float vitesse = 0.002;
	float decalage = amplitude * sin(Time * vitesse);


    gl_Position = Proj * View * Model * vec4(displacedPos + decalage, 1.0);
}
