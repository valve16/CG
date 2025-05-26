uniform sampler2D TextureMap1;
uniform sampler2D TextureMap2;
uniform float Time;

void main()
{
    vec2 texCoord = gl_TexCoord[0].xy;
    vec2 center = vec2(0.5, 0.5);
    float maxRadius = 1.5;
    
    float radius = Time * maxRadius;
    
    float dist = distance(texCoord, center);

    //vec4 color1 = texture2D(TextureMap1, texCoord);
    //vec4 color2 = texture2D(TextureMap2, texCoord);

    //float brightness = sin(Time * 10);
    float changeImg = smoothstep(radius - 0.2, radius, dist);

    float brightnessChange1 = smoothstep(radius - 0.3, radius - 0.15, dist); // затенение
    float brightnessChange1fin = smoothstep(radius - 0.3, radius - 0.45, dist); // осветление
    float bright1 = 0.3 + (brightnessChange1 * 0.7) + (brightnessChange1fin * 0.7);

    float brightnessChange2 = smoothstep(radius + 0.15, radius + 0.3, dist); // затенение
    float brightnessChange2fin = smoothstep(radius + 0.15, radius, dist); // осветление
    float bright2 = 0.3 + (brightnessChange2 * 0.7) + (brightnessChange2fin * 0.7);
    //float bright = mix(brightnessChange1, brightnessChange1fin, dist);

    float wave1 = brightnessChange1 * 0.025;
    float wave2 = brightnessChange2 * 0.025;

    vec2 newCoord = texCoord - wave1 + wave2;

    vec4 color1 = texture2D(TextureMap1, newCoord);
    vec4 color2 = texture2D(TextureMap2, newCoord);

    gl_FragColor = mix(color2, color1, changeImg) * bright1 * bright2;
    //gl_FragColor = color1 * brightness;
    //vec4 mainImg = (dist < radius) ? color2 : color1;

    //gl_FragColor = mainImg * brightnessChange2;
}