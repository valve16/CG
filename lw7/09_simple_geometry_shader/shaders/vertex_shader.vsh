
void main()
{
    float inX = gl_Vertex.x;
    //float x = gl_Vertex.x;

    float R = (1.0 + sin(inX)) *
	          (1.0 + 0.9 * cos(8.0 * inX)) *
	          (1.0 + 0.1 * cos(24.0 * inX)) *
	          (0.5 + 0.05 * cos(140.0 * inX));
	

    float x = R * cos(inX);
    float y = R * sin(inX);
    float z = gl_Vertex.z;
	
    //mat2 rotation = mat2(0.0, 1.0, 1.0, 0.0);
    //vec2 rotatedXY = rotation * vec2(x, y);
    gl_Position = gl_ModelViewProjectionMatrix * vec4(x, y, z, 1.0);
}