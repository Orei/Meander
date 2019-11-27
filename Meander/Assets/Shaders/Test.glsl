Vertex
{
    #version 330 core
    layout (location = 0) in vec3 a_Position;
	layout (location = 1) in vec3 a_Normal;
	layout (location = 2) in vec2 a_UV;

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
    #include "Material.inc"
    
    in VS_OUT
    {
        vec2 UV;
    } fs_in;

    uniform Material u_Material;
	out vec4 o_Color;

    void main()
    {
		vec3 color = texture(u_Material.Diffuse, fs_in.UV).rgb;

        o_Color = vec4(color, 1.0);
    }
}