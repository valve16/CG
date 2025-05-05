
void main()
{
	// Get the original x coordinate
    float x = gl_Vertex.x;
	
	// Calculate R according to the given formula
	// R = (1 + sin(x)) * (1 + 0.9 * cos(8x)) * (1 + 0.1 * cos(24x)) * (0.5 + 0.05 * cos(140x))
    float R = (1.0 + sin(x)) *
	          (1.0 + 0.9 * cos(8.0 * x)) *
	          (1.0 + 0.1 * cos(24.0 * x)) *
	          (0.5 + 0.05 * cos(140.0 * x));
	
	// Transform coordinates
    float x_prime = R * cos(x);
    float y_prime = R * sin(x);
    float z_prime = gl_Vertex.z;
	
	// Set the transformed position
    gl_Position = gl_ModelViewProjectionMatrix * vec4(x_prime, y_prime, z_prime, 1.0);
}