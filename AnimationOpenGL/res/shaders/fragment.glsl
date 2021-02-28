#version 450 core

const vec2 lightBias = vec2(0.7, 0.6);

in vec2 pass_textureCoords;
in vec3 pass_normal;

uniform sampler2D diffuseMap;
uniform vec3 lightDirection;

out vec4 FragColor;

void main()
{
	vec4 diffuseColour = texture(diffuseMap, pass_textureCoords);//vec4(1.0, 1.0, 0.0,1.0);
	vec3 unitNormal = normalize(pass_normal);
	float diffuseLight = max(dot(-lightDirection, unitNormal), 0.0) * lightBias.x + lightBias.y;
	FragColor = diffuseColour * diffuseLight;
}
