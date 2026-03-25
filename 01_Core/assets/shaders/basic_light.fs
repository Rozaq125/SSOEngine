#version 330

// Input dari vertex shader
in vec3 fragPos;
in vec3 normal;
in vec2 texCoord;

// Output warna
out vec4 FragColor;

// Uniforms
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform vec4 objectColor;

void main() {
    // Ambient lighting
    float ambientStrength = 0.15;
    vec3 ambient = ambientStrength * lightColor;
    
    // Diffuse lighting
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Specular lighting
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;
    
    // Combine lighting
    vec3 result = (ambient + diffuse + specular) * objectColor.rgb;
    
    FragColor = vec4(result, objectColor.a);
}
