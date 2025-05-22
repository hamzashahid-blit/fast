#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Entity {
    glm::vec2 m_position;
    std::string m_tex_path; // TODO: turn to spritesheet
    unsigned int m_tex;
public:
    Entity(float x, float y, std::string_view tex_path) : m_position(x, y), m_tex_path(tex_path) {
        int tex_width, tex_height, tex_channel_count;
        unsigned char *tex_data = stbi_load(m_tex_path.c_str(), &tex_width, &tex_height, &tex_channel_count, 0);
        glGenTextures(1, &m_tex);
        glBindTexture(GL_TEXTURE_2D, m_tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_width, tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(tex_data);
    }

    glm::vec2 get_position() const { return m_position; }    
    std::string get_tex_path() const { return m_tex_path; }
    unsigned int get_tex() const { return m_tex; }    
};

class Tile : public Entity {
public:
    Tile(float x, float y, std::string_view tex_path) : Entity(x, y, tex_path) {}
};

class Character : public Entity {
    glm::vec2 m_velocity;
public:
    Character(float x, float y, std::string_view tex_path)
        : Entity(x, y, tex_path), m_velocity(0.0f, 0.0f) {}
    Character(float x, float y, std::string_view tex_path, float vel_x, float vel_y)
        : Entity(x, y, tex_path), m_velocity(vel_x, vel_y) {}

    glm::vec2 get_velocity() const { return m_velocity; }
};

class Player : public Character {
public:
    Player(float x, float y, std::string_view tex_path)
        : Character(x, y, tex_path) {}
};
