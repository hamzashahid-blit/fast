#pragma once
#include "glm/detail/qualifier.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <map>
#include <vector>
#include <sys/types.h>
#include <iostream>

#define ASPECT_RATIO (16.0f/9.0f) //(static_cast<float>(WIN_WIDTH) / WIN_HEIGHT)
#define TILE_SCALE 0.3f
#define PLAYER_SCALE 0.3f
#define PLAYER_SCALE_WIDTH 0.75f
#define TILE_HEIGHT (TILE_SCALE * 0.5f)
#define TILE_WIDTH (2 / (ASPECT_RATIO - -ASPECT_RATIO) * TILE_SCALE * 0.5f)
#define PLAYER_WIDTH (TILE_WIDTH * PLAYER_SCALE_WIDTH)
#define PLAYER_HEIGHT TILE_HEIGHT
#define GRAVITY 0.0005f //9.81f
#define JUMP_FACTOR -0.015f

// SS = Spritesheet
template <typename Type>
class SpriteSheet {
    std::string m_path;
    glm::vec2 m_tile_dimensions;
    glm::vec2 m_file_dimensions;
    glm::vec2 m_tile_padding;
    unsigned int m_tex;
    int m_channel_count;
    std::map<Type, glm::vec2> m_map;
public:
  SpriteSheet(std::string_view path, glm::vec2 tile_dimensions,
              glm::vec2 tile_padding, std::map<Type, glm::vec2> map)
      : m_path(path), m_tile_dimensions(tile_dimensions),
        m_tile_padding(tile_padding), m_map(map) {
        int width, height;
        unsigned char *tex_data = stbi_load(m_path.c_str(), &width, &height, &m_channel_count, 0);
        m_file_dimensions = {width, height}; // TODO: inline
        glGenTextures(1, &m_tex);
        glBindTexture(GL_TEXTURE_2D, m_tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_file_dimensions.x, m_file_dimensions.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(tex_data);
    }

    SpriteSheet(std::string_view path, glm::vec2 tile_dimensions, glm::vec2 tile_padding)
        : SpriteSheet(path, tile_dimensions, tile_padding, {}) {}

    void bind() const { glBindTexture(GL_TEXTURE_2D, m_tex); }

    std::string get_path() const { return  m_path; };
    glm::vec2 get_tile_dimensions() const { return m_tile_dimensions; };
    glm::vec2 get_file_dimensions() const { return m_file_dimensions; };
    glm::vec2 get_tile_padding() const { return  m_tile_padding; };
    int get_channel_count() const { return  m_channel_count; };
    unsigned int get_tex() const { return m_tex; };
    std::map<Type, glm::vec2> get_map() const { return m_map; };

    void set_map(std::map<Type, glm::vec2> val) { m_map = val; };
};

class Entity {
protected:
    glm::vec2 m_position;
public:
    Entity(float x, float y) : m_position(x, y) {}

    glm::vec2 get_position() const { return m_position; }
    void set_position(glm::vec2 val) { m_position = val; }
    void add_position(glm::vec2 val) { m_position += val; }
};

// m = mid, r = right, l = left
enum class TileType {
    grass_m,
    grass_l,
    grass_r,
    dirt_m,
    none,
};

const std::vector<std::vector<TileType>> LEVEL_1 = {
    {},
    {},
    {},
    {TileType::none, TileType::none, TileType::none, TileType::none,
     TileType::none, TileType::grass_m},
    {TileType::grass_l, TileType::grass_r, TileType::none, TileType::grass_l,
     TileType::grass_m, TileType::grass_m, TileType::grass_r},
};
class Level {
    std::vector<std::vector<TileType>> data;
public:
};

const std::map<TileType, glm::vec2> TILE_MAP {
    {TileType::grass_m, {7, 8}},
    {TileType::grass_l, {7, 9}},
    {TileType::grass_r, {7, 7}},
    {TileType::dirt_m, {10, 12}}, // 8,12
    {TileType::none, {11, 12}},
};

class Tile : public Entity {
    TileType m_type;
public:
    Tile(float x, float y, TileType type)
        : Entity(x, y), m_type(type) {}

    TileType get_type() { return m_type; };
};

class Character : public Entity {
protected:
    glm::vec2 m_velocity;
public:
    Character(float x, float y)
        : Entity(x, y), m_velocity(0.0f, 0.0f) {}
    Character(float x, float y, float vel_x, float vel_y)
        : Entity(x, y), m_velocity(vel_x, vel_y) {}

    glm::vec2 get_velocity() const { return m_velocity; }
    void set_velocity(glm::vec2 val) { m_velocity = val; }
    void add_velocity(glm::vec2 val) { m_velocity += val; }
};

enum class PlayerFrame {
    stand
};

const std::map<PlayerFrame, glm::vec2> PLAYER_MAP {
    {PlayerFrame::stand, {0, 0}},
};

class Player : public Character {
    PlayerFrame m_current_frame = PlayerFrame::stand;
    bool m_is_falling = false;
    glm::vec2 m_spawnpoint;
public:
    Player(glm::vec2 spawnpoint)
        : Character(spawnpoint.x, spawnpoint.y), m_spawnpoint(spawnpoint) {}

    Player() : Player({TILE_WIDTH * 2, TILE_HEIGHT * 2}) {}

    void respawn() {
        this->set_velocity({0.0f, 0.0f});
        this->set_is_falling(false);
        this->set_position(m_spawnpoint);
    }
    
    PlayerFrame get_current_frame() { return m_current_frame; }
    bool get_is_falling() { return m_is_falling; }
    void set_is_falling(bool val) { m_is_falling = val; }
};

class CollisionRect {
    float m_x, m_y, m_w, m_h;
    Entity *m_actor;
    Entity *m_entity;
public:
    CollisionRect(float x, float y, float w, float h, Entity* actor, Entity* entity) 
        : m_x(x), m_y(y), m_w(w), m_h(h), m_actor(actor), m_entity(entity) {}

    float get_area() const { return m_w * m_h; }
    
    float get_x() const { return m_x; }
    float get_y() const { return m_y; }
    float get_w() const { return m_w; }
    float get_h() const { return m_h; }
    Entity* get_actor() const { return m_actor; }
    Entity* get_entity() const { return m_entity; }
};
