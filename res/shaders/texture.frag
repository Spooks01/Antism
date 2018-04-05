#version 330 core

layout (location = 0) out vec4 color;

uniform sampler2D texID;

in DATA {
    vec3 position;
    vec4 color;
    vec2 texCoords;
} fs_in;

void main() {
    color = texture(texID, fs_in.texCoords) * fs_in.color;
}

