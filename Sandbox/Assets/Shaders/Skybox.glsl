Vertex
{
	#version 330 core
	layout (location = 0) in vec3 a_Position;

	out VS_OUT
	{
		vec3 Direction;
	} vs_out;

	uniform mat4 u_Model;
	uniform mat4 u_View;
	uniform mat4 u_Projection;

	void main()
	{
		mat4 modelInvert = u_Model;

		modelInvert[2][2] = -1.0;

		mat4 viewNoTranslate = u_View;

		viewNoTranslate[3][0] = 0.0;
		viewNoTranslate[3][1] = 0.0;
		viewNoTranslate[3][2] = 0.0;

		gl_Position = u_Projection * viewNoTranslate * modelInvert * vec4(a_Position, 1.0);
		gl_Position.z = gl_Position.w - 0.001;

		vs_out.Direction = a_Position;
	}
}

Fragment
{
	#version 330 core
	in VS_OUT
	{
		vec3 Direction;
	} fs_in;

	uniform samplerCube u_Skybox;

	out vec4 o_Color;

	void main()
	{
		o_Color = texture(u_Skybox, fs_in.Direction);
	}
}