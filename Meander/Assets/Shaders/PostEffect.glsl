Vertex
{
    #version 330 core
    const vec2 Vertices[] = vec2[](
        vec2(-1.0, -1.0),
        vec2( 1.0, -1.0),
        vec2( 1.0,  1.0),
        vec2(-1.0,  1.0)
    );

    const vec2 UV[] = vec2[](
        vec2(0.0, 0.0),
        vec2(1.0, 0.0),
        vec2(1.0, 1.0),
        vec2(0.0, 1.0)
    );

    out VS_OUT
    {
        vec2 UV;
    } vs_out;

    void main()
    {
        gl_Position = vec4(Vertices[gl_VertexID], 0.0, 1.0);
        vs_out.UV = UV[gl_VertexID];
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

    uniform sampler2D u_Color;
	uniform sampler2D u_Depth;

    void main()
    {
        vec3 color = texture(u_Color, fs_in.UV).rgb;
        vec3 depth = texture(u_Depth, fs_in.UV).rgb;

		o_Color = vec4(mix(color, depth, 0.5), 1.0);
    }
}