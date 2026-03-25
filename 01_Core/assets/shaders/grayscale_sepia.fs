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
uniform float time;
uniform vec2 resolution;

// Effect parameters
uniform float effectAmount = 1.0; // 0 = normal, 1 = full effect
uniform int effectType = 0;        // 0 = grayscale, 1 = sepia

void main() {
    // Basic lighting
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    
    vec3 ambient = 0.3 * lightColor;
    vec3 diffuse = diff * lightColor;
    vec3 lighting = (ambient + diffuse) * objectColor.rgb;
    
    // Apply selected effect
    vec3 finalColor;
    
    if (effectType == 0) {
        // Grayscale conversion using luminance formula
        float gray = dot(lighting, vec3(0.299, 0.587, 0.114));
        finalColor = vec3(gray);
    } else if (effectType == 1) {
        // Sepia tone effect
        vec3 sepia;
        sepia.r = dot(lighting, vec3(0.393, 0.769, 0.189));
        sepia.g = dot(lighting, vec3(0.349, 0.686, 0.168));
        sepia.b = dot(lighting, vec3(0.272, 0.534, 0.131));
        finalColor = sepia;
    } else {
        // Default to original
        finalColor = lighting;
    }
    
    // Blend between original and effect
    finalColor = mix(lighting, finalColor, effectAmount);
    
    // Add subtle film grain for flashback effect
    if (effectAmount > 0.5) {
        float grain = fract(sin(dot(gl_FragCoord.xy, vec2(12.9898, 78.233))) * 43758.5453);
        grain = grain * 0.1 - 0.05;
        finalColor += grain;
    }
    
    // Add slight vignette for dramatic effect
    vec2 uv = gl_FragCoord.xy / resolution;
    float dist = distance(uv, vec2(0.5));
    float vignette = 1.0 - dist * dist * 0.3;
    finalColor *= vignette;
    
    // Pulse effect for death/flashback
    float pulse = sin(time * 3.0) * 0.05 + 1.0;
    finalColor *= pulse;
    
    FragColor = vec4(finalColor, objectColor.a);
}
