Vertex
{
    #version 330 core
    layout (location = 0) in vec3 a_Position;
	layout (location = 1) in vec2 a_UV;

    out VS_OUT
    {
        vec2 UV;
    } vs_out;

    uniform mat4 u_Projection;
    uniform mat4 u_View;
    uniform mat4 u_Transform;

    void main()
    {
        vs_out.UV = a_UV; 

        gl_Position = u_Projection * u_View * u_Transform * vec4(a_Position, 1.0);
    }
}

Fragment
{
    #version 330 core
    in VS_OUT
    {
        vec2 UV;
    } fs_in;

	out vec4 o_Color;

    void main()
    {
        vec2 uv = fs_in.UV;

        o_Color = vec4(uv.x, uv.y, uv.x + uv.y, 1.0);
    }
}