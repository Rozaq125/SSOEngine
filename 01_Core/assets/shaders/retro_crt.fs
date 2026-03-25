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

// CRT parameters
uniform float curveAmount = 0.1;
uniform float scanlineIntensity = 0.15;
uniform float vignetteStrength = 0.3;
uniform float noiseAmount = 0.05;

void main() {
    // Basic lighting
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    
    vec3 ambient = 0.3 * lightColor;
    vec3 diffuse = diff * lightColor;
    vec3 lighting = (ambient + diffuse) * objectColor.rgb;
    
    // Get screen coordinates
    vec2 uv = gl_FragCoord.xy / resolution;
    
    // CRT barrel distortion
    vec2 centered = uv - 0.5;
    float dist = length(centered);
    float curve = 1.0 + curveAmount * dist * dist;
    vec2 curvedUV = centered * curve + 0.5;
    
    // Check if distorted coordinates are valid
    if (curvedUV.x < 0.0 || curvedUV.x > 1.0 || 
        curvedUV.y < 0.0 || curvedUV.y > 1.0) {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
        return;
    }
    
    // Scanlines
    float scanline = sin(gl_FragCoord.y * 2.0) * 0.5 + 0.5;
    scanline = mix(1.0, scanline, scanlineIntensity);
    lighting *= scanline;
    
    // RGB phosphor effect (subtle color separation)
    vec3 phosphor = lighting;
    phosphor.r *= sin(gl_FragCoord.x * 3.0 + time) * 0.02 + 0.98;
    phosphor.g *= sin(gl_FragCoord.x * 3.0 + time + 2.094) * 0.02 + 0.98;
    phosphor.b *= sin(gl_FragCoord.x * 3.0 + time + 4.189) * 0.02 + 0.98;
    
    // Vignette effect
    float vignette = 1.0 - dist * dist * vignetteStrength;
    phosphor *= vignette;
    
    // Film grain/noise
    float noise = fract(sin(dot(gl_FragCoord.xy, vec2(12.9898, 78.233))) * 43758.5453);
    noise = noise * 2.0 - 1.0;
    phosphor += noise * noiseAmount;
    
    // Color temperature (warm CRT look)
    phosphor.r *= 1.1;
    phosphor.b *= 0.9;
    
    // Slight flicker
    float flicker = sin(time * 60.0) * 0.01 + 1.0;
    phosphor *= flicker;
    
    FragColor = vec4(phosphor, objectColor.a);
}
