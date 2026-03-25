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

// Blur parameters
uniform float blurRadius = 2.0;
uniform float blurStrength = 1.0;
uniform float depthThreshold = 0.5; // Depth at which blur starts
uniform float focusDistance = 10.0;  // Distance of focus point

void main() {
    // Calculate basic lighting
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    
    vec3 ambient = 0.3 * lightColor;
    vec3 diffuse = diff * lightColor;
    vec3 lighting = (ambient + diffuse) * objectColor.rgb;
    
    // Calculate depth (distance from camera)
    float depth = distance(fragPos, viewPos);
    
    // Normalize depth for blur calculation
    float normalizedDepth = (depth - focusDistance) / 20.0; // 20 unit range
    normalizedDepth = clamp(normalizedDepth, 0.0, 1.0);
    
    // Apply blur based on depth
    if (normalizedDepth > depthThreshold) {
        // Calculate blur amount
        float blurAmount = (normalizedDepth - depthThreshold) * blurStrength;
        blurAmount = min(blurAmount, blurRadius);
        
        // Simple box blur (in real implementation, you'd use Gaussian blur)
        vec3 blurredColor = vec3(0.0);
        float totalWeight = 0.0;
        
        // Sample surrounding pixels (simplified - real implementation needs texture sampling)
        for (float x = -blurAmount; x <= blurAmount; x += 1.0) {
            for (float y = -blurAmount; y <= blurAmount; y += 1.0) {
                // Weight based on distance from center
                float weight = 1.0 / (1.0 + abs(x) + abs(y));
                
                // Add weighted color (this is simplified - real shader would sample texture)
                vec3 sampleColor = lighting + vec3(x * 0.01, y * 0.01, 0.0);
                blurredColor += sampleColor * weight;
                totalWeight += weight;
            }
        }
        
        // Normalize the blurred color
        if (totalWeight > 0.0) {
            blurredColor /= totalWeight;
        }
        
        // Mix between original and blurred based on depth
        float blurMix = smoothstep(depthThreshold, 1.0, normalizedDepth);
        lighting = mix(lighting, blurredColor, blurMix);
        
        // Add bokeh effect (bright spots get more blurred)
        float brightness = dot(lighting, vec3(0.2126, 0.7152, 0.0722));
        if (brightness > 0.7) {
            // Create hexagonal bokeh shape
            float bokeh = sin(gl_FragCoord.x * 0.1 + time) * 0.5 + 0.5;
            lighting *= (1.0 + bokeh * 0.2);
        }
        
        // Add subtle chromatic aberration for distant objects
        vec2 uv = gl_FragCoord.xy / resolution;
        float aberration = normalizedDepth * 0.5;
        lighting.r += aberration * 0.1;
        lighting.b -= aberration * 0.1;
    }
    
    // Add subtle depth fog
    vec3 fogColor = vec3(0.7, 0.8, 0.9); // Bluish fog
    float fogAmount = smoothstep(focusDistance, focusDistance + 30.0, depth);
    lighting = mix(lighting, fogColor, fogAmount * 0.3);
    
    FragColor = vec4(lighting, objectColor.a);
}
