#version 450 core

//const int MAX_JOINTS = 50;//max joints allowed in a skeleton
//const int MAX_WEIGHTS = 3;//max number of joints that can affect a vertex

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_textureCoords;
layout(location = 2) in vec3 in_normal;
//in ivec3 in_jointIndices;
//in vec3 in_weights;

out vec2 pass_textureCoords;
out vec3 pass_normal;

//uniform mat4 jointTransforms[MAX_JOINTS];
uniform mat4 projectionViewMatrix;

void main()
{
	
	//vec4 totalLocalPos = vec4(0.0);
	//vec4 totalNormal = vec4(0.0);
	
	//for(int i=0;i<MAX_WEIGHTS;i++){
	//	mat4 jointTransform = jointTransforms[in_jointIndices[i]];
	//	vec4 posePosition = jointTransform * vec4(in_position, 1.0);
	//	totalLocalPos += posePosition * in_weights[i];
		
	//	vec4 worldNormal = jointTransform * vec4(in_normal, 0.0);
	//	totalNormal += worldNormal * in_weights[i];
	//}

	
	// not for my future self the 4th component of a vec4
	// is called 'w' and is used in perspetive devision after
	// the vertex shader had run

	// NEVER SET THE 'w' COMPONENT TO 0.0 IN VERTEX SHADER
	// YOU WILL DEVIDE BY 0 BUT YOU WON'T GET AN ERROR
	// JUST A BLANK SCREEN

	//gl_Position = projectionViewMatrix * totalLocalPos;
	gl_Position = projectionViewMatrix * vec4(in_position.xyz, 1.0);

	//pass_normal = totalNormal.xyz;
	pass_normal = in_normal;

	//pass_textureCoords = in_textureCoords;
	pass_textureCoords = in_textureCoords;
}
