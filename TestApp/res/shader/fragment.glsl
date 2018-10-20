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

	float cutOff, outCutOff;
	float quadratic, linear, constant;

	vec3 ambientStrength;
	vec3 diffuseStrength;
	vec3 specularStrength;
};

uniform Light l1, l2, l3;

vec3 dirLight(Light light){
	//Ambient
	vec3 ambient = light.ambientStrength;

	//Diffuse
	vec3 lightDir = normalize(light.direction);
	vec3 diffuse = max(dot(Normal, lightDir), 0) * light.diffuseStrength;

	//Specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectionDir = reflect(-lightDir, Normal);

	vec3 specular = pow(max(dot(viewDir, reflectionDir), 0), 0.15) * light.specularStrength;

	//Result color
	return (ambient + diffuse + specular) * light.color;
}

vec3 dotLight(Light light){
	float distance    = length(light.position.xyz - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	//Ambient
	vec3 ambient = light.ambientStrength;

	//Diffuse
	vec3 diffuseStrength = light.diffuseStrength;
	vec3 lightDir = normalize(light.position.xyz - FragPos);
	vec3 diffuse = max(dot(Normal, lightDir), 0) * diffuseStrength;

	//Specular
	vec3 specularStrength = light.specularStrength;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectionDir = reflect(-lightDir, Normal);

	vec3 specular = pow(max(dot(viewDir, reflectionDir), 0), 0.15) * specularStrength;

	//Result color
	return (ambient + diffuse + specular) * light.color * attenuation;
}

vec3 spotLight(Light light) {
	float distance    = length(light.position.xyz - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	//Ambient
	vec3 ambient = light.ambientStrength;

	//Diffuse
	vec3 diffuseStrength = light.diffuseStrength;
	vec3 lightDir = normalize(light.position.xyz - FragPos);
	vec3 diffuse = max(dot(Normal, lightDir), 0) * diffuseStrength;

	//Specular
	vec3 specularStrength = light.specularStrength;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectionDir = reflect(-lightDir, Normal);

	vec3 specular = pow(max(dot(viewDir, reflectionDir), 0), 0.15) * specularStrength;

	// spotlight (soft edges)
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = (light.cutOff - light.outCutOff);
    float intensity = clamp((theta - light.outCutOff) / epsilon, 0.0, 1.0);

	//Result color
	return (ambient + (diffuse + specular) * intensity) * light.color * attenuation;
}

void main(){
	//Result color
	vec3 FragColor = texture(texture0, TexCoords).rgb;
	vec3 resultLight = dotLight(l1) + dirLight(l2) + spotLight(l3);
	resultColor = vec4(resultLight * FragColor, 1);
}