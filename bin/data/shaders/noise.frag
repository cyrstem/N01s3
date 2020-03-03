
#version 330
precision highp float;
#define TWO_PI 6.283185307179586476925286766559f

out vec4 outputColor;
uniform float alphaDamp;
uniform float time;
uniform vec2 resolution;
//uniform vec3 y_noise[724];
//uniform sampler2DRect tex;

float random(vec2 _st){
   return fract(sin(dot(_st.xy,
                        vec2(12.9898,78.233)))*
                        43758.5453123);
}

// Based on Morgan McGuire @morgan3d
// https://www.shadertoy.com/view/4dS3Wd
float noise (in vec2 _st) {
    vec2 i = floor(_st);
    vec2 f = fract(_st);

    // Four corners in 2D of a tile
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    vec2 u = f * f * (3.0 - 2.0 * f);

    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}

#define NUM_OCTAVES 5

float fbm ( in vec2 _st) {
    float v = 0.0;
    float a = 0.6;
    vec2 shift = vec2(100.0);
    // Rotate to reduce axial bias
    mat2 rot = mat2(cos(0.5), sin(0.5),
                    -sin(0.5), cos(0.50));
    for (int i = 0; i < NUM_OCTAVES; ++i) {
        v += a * noise(_st);
        _st = rot * _st * 2.0 + shift;
        a *= 0.5;
    }
    return v;
}
void main ()
{ 






    // vec2 st = gl_FragCoord.xy/resolution.xy;
    //  //vec2 pos = vec2(st*10.8);
    //  st.x *= resolution.x/resolution.y;
    //  vec3 color = vec3(0.0);
    //  color +=fbm(st*3.0);

    //float n =noise(pos);



  //  outputColor = vec4(color,1.0);


    float r = 1.0;
    float g = 0.0;
    float b = 0.0;

    r += (cos(time)*0.005);
    g += abs(tan(time)*0.004);
    b *= time/(g/r);
    //b = 1.0;
    float a = alphaDamp *1.0;
    outputColor = vec4(vec3(r,g,b),a);
    //outputColor = vec4(vec3(n),a);

}
