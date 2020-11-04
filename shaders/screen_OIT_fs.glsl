#version 330 core
out vec4 FragColor;
uniform sampler2D accumTex;
uniform sampler2D revealageTex;

void main()
{
    vec4 accum = texelFetch(accumTex, ivec2(gl_FragCoord.xy), 0);
    float r = texelFetch(revealageTex, ivec2(gl_FragCoord.xy), 0).r;
    FragColor = vec4(accum.rgb / clamp(accum.a, 1e-4, 5e4), r);
}