
uniform float time;

void main()
{
    float x = gl_Vertex.x;
    float y = gl_Vertex.y;
    
    float a = 1.0;
    float b = 1.0;
    
    float t = (sin(time) + 1.0) / 2.0; // t [0, 1]
    
    //  z = (1-t)*Эллиптический + t*Гиперболический
    float z = (1.0 - t) * (x * x / (a * a) + (y * y / (b * b)))
              + t * (x * x / (a * a) - y * y / (b * b));
    
    gl_Position = gl_ModelViewProjectionMatrix * vec4(x, y, z, 1.0);
}