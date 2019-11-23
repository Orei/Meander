Vertex
{
    #version 330 core
    layout (location = 0) in vec2 a_Position;
	layout (location = 1) in vec2 a_UV;

    out VS_OUT
    {
        vec2 UV;
    } vs_out;

    void main()
    {
        vs_out.UV = a_UV; 

        gl_Position = vec4(a_Position, 1.0, 1.0);
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