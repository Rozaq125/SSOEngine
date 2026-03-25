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

// Bloom threshold
uniform float bloomThreshold = 1.0;
uniform float bloomIntensity = 1.5;

void main() {
    // Basic lighting calculation
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    
    // Ambient + diffuse
    vec3 ambient = 0.2 * lightColor;
    vec3 diffuse = diff * lightColor;
    vec3 lighting = (ambient + diffuse) * objectColor.rgb;
    
    // Calculate brightness for bloom
    float brightness = dot(lighting, vec3(0.2126, 0.7152, 0.0722));
    
    // Apply bloom effect to bright areas
    if (brightness > bloomThreshold) {
        // Create glow effect
        float glowFactor = (brightness - bloomThreshold) / (1.0 - bloomThreshold);
        glowFactor = pow(glowFactor, 2.0); // Smooth curve
        
        // Add color-shifted glow for cinematic feel
        vec3 glowColor = lighting * glowFactor * bloomIntensity;
        glowColor.r *= 1.2; // Warm tint
        glowColor.b *= 0.8;
        
        // Combine original with glow
        vec3 finalColor = lighting + glowColor;
        
        // Add subtle pulsing effect
        float pulse = sin(time * 2.0) * 0.05 + 1.0;
        finalColor *= pulse;
        
        FragColor = vec4(finalColor, objectColor.a);
    } else {
        FragColor = vec4(lighting, objectColor.a);
    }
    
    // Add subtle chromatic aberration for edges
    vec2 uv = gl_FragCoord.xy / resolution;
    float edge = distance(uv, vec2(0.5));
    if (edge > 0.4) {
        float aberration = (edge - 0.4) * 0.5;
        FragColor.r += aberration * 0.1;
        FragColor.b -= aberration * 0.1;
    }
}
