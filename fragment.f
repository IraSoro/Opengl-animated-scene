/*
#version 330 core
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
    color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.2);
}
*/
#version 330 core
out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
  
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    //FragColor = vec4(lightColor * objectColor, 1.0);
	
	FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.2);
}