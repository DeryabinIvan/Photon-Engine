#version 330 core

out vec4 resultColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

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

struct Material{
	sampler2D diffuse;
	sampler2D specular;
	//sampler2D normal;

	float shininess;
};

uniform Light l, s;
uniform Material material;

vec3 dirLight(Light light){
	//Ambient
	vec3 ambient = light.ambientStrength;

	//Diffuse
	vec3 lightDir = normalize(light.direction);
	vec3 diffuse = max(dot(Normal, lightDir), 0) * light.diffuseStrength;

	//Specular
	vec3 specularStrength = light.specularStrength * texture(material.specular, TexCoords).rgb;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 halfway = normalize(lightDir + viewDir);
	vec3 specular = pow(max(dot(Normal, halfway), 0), material.shininess) * specularStrength;

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
	vec3 specularStrength = light.specularStrength * texture(material.specular, TexCoords).rgb;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 halfway = normalize(lightDir + viewDir);
	vec3 specular = pow(max(dot(Normal, halfway), 0), material.shininess) * specularStrength;

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
	vec3 specularStrength = light.specularStrength * texture(material.specular, TexCoords).rgb;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 halfway = normalize(lightDir + viewDir);
	vec3 specular = pow(max(dot(Normal, halfway), 0), material.shininess) * specularStrength;

	// spotlight (soft edges)
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = (light.cutOff - light.outCutOff);
    float intensity = clamp((theta - light.outCutOff) / epsilon, 0.0, 1.0);

	//Result color
	return (ambient + (diffuse + specular) * intensity) * light.color * attenuation;
}

void main(){
	//Result color
	vec3 DiffuseColor = texture(material.diffuse, TexCoords).rgb;
	vec3 SpecColor = texture(material.specular, TexCoords).rgb;

	vec3 resultLight = dotLight(l) + spotLight(s);

	resultColor = vec4(resultLight * DiffuseColor, 1);
	//resultColor = vec4(DiffuseColor.r, SpecColor.g, 0, 1);
}