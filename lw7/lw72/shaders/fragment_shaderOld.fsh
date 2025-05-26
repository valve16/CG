uniform sampler2D TextureMap;

void main()
{
    // float innerRadius = 0.2; 
    // float outerRadius = 0.3; 

	//vec2 tex = gl_TexCoord[0].xy;

    gl_FragColor = texture2D(TextureMap, gl_TexCoord[0].xy);

    // vec2 center = vec2(1.0, 0.5);

    // float dist = distance(tex, center);

    // if (dist >= innerRadius && dist <= outerRadius)
    // {
    //     gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0); 
    // }
    // else
    // {
    //     gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0); 
    // }
}