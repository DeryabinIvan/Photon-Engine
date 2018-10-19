#version 330 core

out vec4 resultColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

// texture samplers
uniform sampler2D texture0;

uniform vec3 viewPos;
struct Light{
	vec4 position;
	vec3 color;
	vec3 direction;

	vec3 ambientStrength;
	vec3 diffuseStrength;
	vec3 specularStrength;
};

uniform Light light;

vec3 dirLight(Light light){
	//Ambient
	vec3 ambient = light.ambientStrength;

	//Diffuse
	vec3 lightDir = normalize(light.direction);
	vec3 diffuse = max(dot(Normal, lightDir), 0) * light.diffuseStrength;

	//Specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectionDir = reflect(-lightDir, Normal);

	vec3 specular = pow(max(dot(viewDir, reflectionDir), 0), .1) * light.specularStrength;

	//Result color
	vec3 FragColor = texture(texture0, TexCoords).rgb;
	return (ambient + diffuse + specular) * light.color * FragColor;
}

vec3 dotLight(Light light){
	float attenetion = 1.0 / distance(light.position.xyz, FragPos);

	//Ambient
	vec3 ambient = light.ambientStrength * attenetion;

	//Diffuse
	vec3 diffuseStrength = light.diffuseStrength * attenetion;
	vec3 lightDir = normalize(light.position.xyz - FragPos);
	vec3 diffuse = max(dot(Normal, lightDir), 0) * diffuseStrength;

	//Specular
	vec3 specularStrength = light.specularStrength * attenetion;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectionDir = reflect(-lightDir, Normal);

	vec3 specular = pow(max(dot(viewDir, reflectionDir), 0), .1) * specularStrength;

	//Result color
	vec3 FragColor = texture(texture0, TexCoords).rgb;
	return (ambient + diffuse + specular) * light.color * FragColor;
}

void main(){
	//Result color
	vec3 FragColor = texture(texture0, TexCoords).rgb;
	resultColor = vec4(dotLight(light) * FragColor, 1);
}