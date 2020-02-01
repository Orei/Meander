struct Material
{
    sampler2D Diffuse;
    sampler2D Normal;
    float Specularity;

    bool HasDiffuse;
    bool HasNormal;
};