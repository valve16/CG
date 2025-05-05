varying vec2 v_uv;

void main()
{
	// Преобразование координат из [-1,1] в [0,2]x[0,1] для UV
    v_uv = vec2(gl_Vertex.x * 1.0 + 1.0, gl_Vertex.y * 0.5 + 0.5);

	// Позиция вершины в пространстве отсечения
    gl_Position = vec4(gl_Vertex.xy, 0.0, 1.0);
}