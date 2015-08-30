uniform highp vec4 colour;
uniform highp vec2 light_pos;

varying highp vec4  vs_position;
varying highp vec2  vs_uv;
varying highp float vs_tid;
varying highp vec4  vs_color;

uniform sampler2D textures_0;
uniform sampler2D textures_1;
uniform sampler2D textures_2;
uniform sampler2D textures_3;
uniform sampler2D textures_4;
uniform sampler2D textures_5;
uniform sampler2D textures_6;
uniform sampler2D textures_7;
uniform sampler2D textures_8;
uniform sampler2D textures_9;
uniform sampler2D textures_10;
uniform sampler2D textures_11;
uniform sampler2D textures_12;
uniform sampler2D textures_13;
uniform sampler2D textures_14;
uniform sampler2D textures_15;
uniform sampler2D textures_16;
uniform sampler2D textures_17;
uniform sampler2D textures_18;
uniform sampler2D textures_19;
uniform sampler2D textures_20;
uniform sampler2D textures_21;
uniform sampler2D textures_22;
uniform sampler2D textures_23;
uniform sampler2D textures_24;
uniform sampler2D textures_25;
uniform sampler2D textures_26;
uniform sampler2D textures_27;
uniform sampler2D textures_28;
uniform sampler2D textures_29;
uniform sampler2D textures_30;
uniform sampler2D textures_31;

void main()
{
	float intensity = 1.0 / length(vs_position.xy - light_pos); 
	vec4 texColor = vs_color;
	if (vs_tid > 0.0)
	{
		int tid = int(vs_tid - 0.5f);
		if (tid == 0)
		texColor = texture(textures_0, vs_uv);
		else if (tid == 1)
		texColor = texture(textures_1, vs_uv);
		else if (tid == 2)
		texColor = texture(textures_2, vs_uv);
		else if (tid == 3)
		texColor = texture(textures_3, vs_uv);
		else if (tid == 4)
		texColor = texture(textures_4, vs_uv);
		else if (tid == 5)
		texColor = texture(textures_5, vs_uv);
		else if (tid == 6)
		texColor = texture(textures_6, vs_uv);
		else if (tid == 7)
		texColor = texture(textures_7, vs_uv);
		else if (tid == 8)
		texColor = texture(textures_8, vs_uv);
		else if (tid == 9)
		texColor = texture(textures_9, vs_uv);
		else if (tid == 10)
		texColor = texture(textures_10, vs_uv);
		else if (tid == 11)
		texColor = texture(textures_11, vs_uv);
		else if (tid == 12)
		texColor = texture(textures_12, vs_uv);
		else if (tid == 13)
		texColor = texture(textures_13, vs_uv);
		else if (tid == 14)
		texColor = texture(textures_14, vs_uv);
		else if (tid == 15)
		texColor = texture(textures_15, vs_uv);
		else if (tid == 16)
		texColor = texture(textures_16, vs_uv);
		else if (tid == 17)
		texColor = texture(textures_17, vs_uv);
		else if (tid == 18)
		texColor = texture(textures_18, vs_uv);
		else if (tid == 19)
		texColor = texture(textures_19, vs_uv);
		else if (tid == 20)
		texColor = texture(textures_20, vs_uv);
		else if (tid == 21)
		texColor = texture(textures_21, vs_uv);
		else if (tid == 22)
		texColor = texture(textures_22, vs_uv);
		else if (tid == 23)
		texColor = texture(textures_23, vs_uv);
		else if (tid == 24)
		texColor = texture(textures_24, vs_uv);
		else if (tid == 25)
		texColor = texture(textures_25, vs_uv);
		else if (tid == 26)
		texColor = texture(textures_26, vs_uv);
		else if (tid == 27)
		texColor = texture(textures_27, vs_uv);
		else if (tid == 28)
		texColor = texture(textures_28, vs_uv);
		else if (tid == 29)
		texColor = texture(textures_29, vs_uv);
		else if (tid == 30)
		texColor = texture(textures_30, vs_uv);
		else if (tid == 31)
		texColor = texture(textures_31, vs_uv);
	}
	gl_FragColor = texColor * intensity;
	
}