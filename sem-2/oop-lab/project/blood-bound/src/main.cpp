#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <climits>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/fwd.hpp>

#include "entity.h"

#define INFO_LOG_LEN 512
#define AA_BORDER 0.001f

constexpr int WIN_FACTOR = 100;
int WIN_WIDTH = 16 * WIN_FACTOR;
int WIN_HEIGHT = 9 * WIN_FACTOR;

std::vector<float> vertices = {
    0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top right
    0.5f,  -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // bottom right
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // bottom left
    -0.5f, 0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, // top left
};
    
std::vector<unsigned int> indices = {
    // note that we start from 0!
    0, 1, 3, // first triangle
    1, 2, 3, // second triangle
};

const char *vertex_shader_source =
    "#version 400\n"
    "in vec3 aPos;\n"
    "in vec3 aColor;\n"
    "in vec2 aTexCoord;\n"
    "out vec3 fColor;\n"
    "out vec2 fTexCoord;\n"
    "uniform mat4 uModel;\n"
    "uniform mat4 uView;\n"
    "uniform mat4 uProjection;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);\n"
    "   fColor = aColor;\n"
    "   fTexCoord = aTexCoord;\n"
    "}\0";

const char *fragment_shader_source =
    "#version 400\n"
    "in vec3 fColor;\n"
    "in vec2 fTexCoord;\n"
    "out vec4 oColor;\n"
    "uniform sampler2D Tex;"
    "uniform vec2 uTILE_SS_COUNT;\n" // ss = spritesheet; amount of tiles
    "uniform vec2 uTILE_SS_INDEX;\n" // ss = spritesheet; index of tile, in
                                     // terms of tiles
    "uniform vec2 uTILE_SS_PADDING;\n" // floats padding_pixels_per_tile/ss_width_in_pixels
    "vec2 TILE_SIZE;\n"
    "vec2 texCoord;\n"
    "void main() {\n"
    "    TILE_SIZE = 1.0/uTILE_SS_COUNT;\n"
    "    texCoord = TILE_SIZE * uTILE_SS_INDEX + fTexCoord*(TILE_SIZE - uTILE_SS_PADDING);\n"
    "    oColor = texture(Tex, texCoord) * vec4(1.0, 1.0, 1.0, 1.0);\n"
    "}\0";

int shader_success;
char info_log[INFO_LOG_LEN];

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    WIN_WIDTH = width;
    WIN_HEIGHT = height;
    glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
}    

int main() {
#if 0
#else
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow *window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT,                                          
                                          "Blood Bound", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "[ERROR] Failed to create a GLFW Window!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowAspectRatio(window, 16, 9);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "[ERROR] Failed to initialize GLAD!" << std::endl;
        return -1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 400");

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    
    auto tile_ss = SpriteSheet<TileType>("res/Base pack/Tiles/tiles_spritesheet.png", 
                                         {12, 13}, {2, 2}, TILE_MAP);
    auto player_1_ss = SpriteSheet<PlayerFrame>("res/Base pack/Player/p1_spritesheet.png",
                                                {7, 3}, {0, 0}, PLAYER_MAP);
    
    // std::cout << tile_ss.get_tile_dimensions().x << ' ' << tile_ss.get_tile_dimensions().y
    //           << ',' << tile_ss.get_tile_padding().x << ' ' << tile_ss.get_tile_padding().y 
    //           << ',' << tile_ss.get_map()[TileType::dirt_m].x << ' ' << tile_ss.get_map()[TileType::dirt_m].y;
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &shader_success);
    if (!shader_success) {
        glGetShaderInfoLog(vertex_shader, INFO_LOG_LEN, NULL, info_log);
        std::cerr << "[ERROR] Vertex Shader Compilation Failed!\n"
                  << info_log << std::endl;
        return -1;
    }

    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &shader_success);
    if (!shader_success) {
        glGetShaderInfoLog(fragment_shader, INFO_LOG_LEN, NULL, info_log);
        std::cerr << "[ERROR] Fragment Shader Compilation Failed!\n"
                  << info_log << std::endl;
        return -1;
    }

    unsigned int shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &shader_success);
    if (!shader_success) {
        glGetProgramInfoLog(shader_program, INFO_LOG_LEN, NULL, info_log);
        std::cerr << "[ERROR] Program Failed to Link!\n"
                  << info_log << std::endl;
        return -1;
    }

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(),
                 GL_STATIC_DRAW);
    int position_attrib_location = glGetAttribLocation(shader_program, "aPos");
    glVertexAttribPointer(position_attrib_location, 3, GL_FLOAT, GL_FALSE,
                          8 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(position_attrib_location);
    int color_attrib_location = glGetAttribLocation(shader_program, "aColor");
    glVertexAttribPointer(color_attrib_location, 3, GL_FLOAT, GL_FALSE,
                          8 * sizeof(float),
                          reinterpret_cast<void *>(3 * sizeof(float)));
    glEnableVertexAttribArray(color_attrib_location);
    int tex_coord_attrib_location = glGetAttribLocation(shader_program, "aTexCoord");
    glVertexAttribPointer(tex_coord_attrib_location, 2, GL_FLOAT, GL_FALSE,
                          8 * sizeof(float),
                          reinterpret_cast<void *>(6 * sizeof(float)));
    glEnableVertexAttribArray(tex_coord_attrib_location);

    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    unsigned int model_uniform_loc = glGetUniformLocation(shader_program, "uModel");
    unsigned int view_uniform_loc = glGetUniformLocation(shader_program, "uView");
    unsigned int projection_uniform_loc = glGetUniformLocation(shader_program, "uProjection");
    unsigned int tile_ss_count_uniform_loc = glGetUniformLocation(shader_program, "uTILE_SS_COUNT");
    unsigned int tile_ss_index_uniform_loc = glGetUniformLocation(shader_program, "uTILE_SS_INDEX");
    unsigned int tile_ss_padding_uniform_loc = glGetUniformLocation(shader_program, "uTILE_SS_PADDING");
    
    std::vector<Tile> tiles = {};
    for (int i = 0; i < LEVEL_1.size(); i++) {
        for (int j = 0; j < LEVEL_1[i].size(); j++) {
            tiles.emplace_back(TILE_WIDTH*j+TILE_WIDTH/2-(AA_BORDER*j), 
                               TILE_HEIGHT*i+TILE_HEIGHT/2-(AA_BORDER*i), LEVEL_1[i][j]);
        }
    }

    auto player = Player({TILE_WIDTH * 2, TILE_HEIGHT * 2});

    glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.2f, 0.3f, 1.0f);

    static bool use_work_area = true;
    static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;

    // We demonstrate using the full viewport area or the work area (without menu-bars, task-bars etc.)
    // Based on your use case you may want one or the other.
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
    ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);
    
    auto projection_mat =
        glm::ortho(-ASPECT_RATIO, ASPECT_RATIO, -1.0f, 1.0f, 0.1f, 100.0f);

    bool is_first_time = true;
    glm::vec2 camera_pos = {0.0f, 0.0f};
    std::array<bool, SHRT_MAX> keys_pressed = {false};
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        if (is_first_time) {
            if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0) {
                ImGui_ImplGlfw_Sleep(10);
                continue;
            }

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            {
                ImGui::Begin("Blood Bound");
                ImGui::Text("Blood Bound");
                if (ImGui::Button("Play"))
                    is_first_time = false;
                ImGui::End();
            }

            // Rendering
            ImGui::Render();
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(window);
        } else {
    
            /// Input
            for (int key = 0; key < keys_pressed.size(); key++) {
                keys_pressed[key] = (glfwGetKey(window, key) == GLFW_PRESS);
            }
        
            if (keys_pressed[GLFW_KEY_D]) {
                player.add_position(glm::vec2(0.003f, 0.0f));
            } if (keys_pressed[GLFW_KEY_A]) {
                player.add_position(glm::vec2(-0.003f, 0.0f));
            } if (keys_pressed[GLFW_KEY_W]) {
                if (!player.get_is_falling()) {
                    player.add_velocity(glm::vec2(0.0f, JUMP_FACTOR));
                    player.set_is_falling(true);
                }
            }
            // Update
            player.add_velocity(glm::vec2(0.0f, GRAVITY));
            player.add_position(player.get_velocity());

            if (player.get_position().y - PLAYER_HEIGHT / 2 > 1.0)
                player.respawn();

            std::vector<CollisionRect> coll_rects = {};
            for (Tile entity : tiles) {
                if (entity.get_type() == TileType::none) continue;
                float pl = player.get_position().x - PLAYER_WIDTH/2;
                float pr = player.get_position().x + PLAYER_WIDTH/2;
                float pt = player.get_position().y - PLAYER_HEIGHT/2;
                float pb = player.get_position().y + PLAYER_HEIGHT/2;
                float el = entity.get_position().x - TILE_WIDTH/2;
                float er = entity.get_position().x + TILE_WIDTH/2;
                float et = entity.get_position().y - TILE_HEIGHT/2;
                float eb = entity.get_position().y + TILE_HEIGHT/2;
                if (pl < er && pr > el && pt < eb && pb > et) {  // collision
                    float cx, cy, cw, ch;
                    if (player.get_position().y <= entity.get_position().y) { // player on top or inline
                        ch = std::abs(pb - et);
                        cy = ch/2 + et;
                    } else { // player on bottom
                        ch = std::abs(pt - eb);
                        cy = ch/2 + pt;
                    }
                    if (player.get_position().x >= entity.get_position().x) { // Player on right or inline
                        cw = std::abs(pl - er);
                        cx = cw/2 + pl;
                    } else { // player on left 
                        cw = std::abs(pr - el);
                        cx = cw/2 + el;
                    }
                    coll_rects.emplace_back(cx, cy, cw, ch, &player, &entity);
                }
            }

            auto largest_coll_rect_it = std::max_element(coll_rects.cbegin(), coll_rects.cend(), 
                                                         [](CollisionRect r1, CollisionRect r2){
                                                             return r1.get_area() < r2.get_area();
                                                         });
        
            if (largest_coll_rect_it != coll_rects.end()) { // Collision detected
                CollisionRect rect = *largest_coll_rect_it;
                Character* r_actor = static_cast<Character*>(rect.get_actor());
                Entity* r_entity = rect.get_entity();
                // Find smallest axis
                if (rect.get_w() < rect.get_h()) {
                    if (r_actor->get_position().x >= r_entity->get_position().x) { // Player on right or inline
                        r_actor->add_position(glm::vec2(rect.get_w(), 0.0f));
                    } else { // player on left
                        r_actor->add_position(glm::vec2(-rect.get_w(), 0.0f));
                    }
                } else {
                    if (r_actor->get_position().y <= r_entity->get_position().y) { // player on top
                        r_actor->set_velocity(glm::vec2(r_actor->get_velocity().x, 0.0f));
                        r_actor->add_position(glm::vec2(0.0f, -rect.get_h()));
                        player.set_is_falling(false);
                    } else { // player on bottom
                        r_actor->add_position(glm::vec2(0.0f, rect.get_h()));
                    }
                }
            } else {
                player.set_is_falling(true);
            }
        
            /// Render
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glUseProgram(shader_program);
            // glActiveTexture(GL_TEXTURE0);

            // camera_pos = camera_pos + player.get_position();
            for (auto tile : tiles) {
                tile_ss.bind();
                glBindVertexArray(vao);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

                auto model_mat = glm::mat4(1.0f);
                // tile position is from zero to one
                model_mat = glm::translate(model_mat,
                                           glm::vec3(-ASPECT_RATIO + (tile.get_position().x) *
                                                     2 * ASPECT_RATIO,
                                                     1.0 - (tile.get_position().y) * 2,
                                                     0.0f));
                model_mat = glm::scale(model_mat, glm::vec3(TILE_SCALE));
                glUniformMatrix4fv(model_uniform_loc, 1, GL_FALSE, glm::value_ptr(model_mat));
                auto view_mat = glm::mat4(1.0f);
                camera_pos = {
                    - (-ASPECT_RATIO + (player.get_position().x) * 2 * ASPECT_RATIO),
                    - (1.0 - (player.get_position().y) * 2),
                };
                view_mat = glm::translate(view_mat, glm::vec3(camera_pos, -1.0f));
                glUniformMatrix4fv(view_uniform_loc, 1, GL_FALSE,
                                   glm::value_ptr(view_mat));
                glUniformMatrix4fv(projection_uniform_loc, 1, GL_FALSE,
                                   glm::value_ptr(projection_mat));
                glUniform2fv(tile_ss_count_uniform_loc, 1, glm::value_ptr(tile_ss.get_tile_dimensions()));
                glm::vec2 tile_ss_index = tile_ss.get_map()[tile.get_type()];
                glUniform2fv(tile_ss_index_uniform_loc, 1, glm::value_ptr(tile_ss_index));
                glm::vec2 tile_ss_padding = (tile_ss.get_tile_padding()+1.0f)/tile_ss.get_file_dimensions();
                glUniform2fv(tile_ss_padding_uniform_loc, 1, glm::value_ptr(tile_ss_padding));
            
                glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
            }

            for (int i = 0; i < 1; i++) {
                player_1_ss.bind();
                auto model_mat = glm::mat4(1.0f);
                // tile position is from zero to one
                model_mat = glm::translate(model_mat,
                                           glm::vec3(-ASPECT_RATIO + (player.get_position().x) *
                                                     2 * ASPECT_RATIO,
                                                     1.0 - (player.get_position().y) * 2,
                                                     0.0f));
                model_mat = glm::scale(model_mat, glm::vec3(PLAYER_SCALE));
                model_mat = glm::scale(model_mat, glm::vec3(PLAYER_SCALE_WIDTH, 1.0f, 1.0f));
                glUniformMatrix4fv(model_uniform_loc, 1, GL_FALSE, glm::value_ptr(model_mat));
                auto view_mat = glm::mat4(1.0f);
                view_mat = glm::translate(view_mat, glm::vec3(camera_pos, -0.5f));
                glUniformMatrix4fv(view_uniform_loc, 1, GL_FALSE,
                                   glm::value_ptr(view_mat));
                glUniformMatrix4fv(projection_uniform_loc, 1, GL_FALSE,
                                   glm::value_ptr(projection_mat));
                glUniform2fv(tile_ss_count_uniform_loc, 1, glm::value_ptr(player_1_ss.get_tile_dimensions()));
                glm::vec2 player_ss_frame = player_1_ss.get_map()[player.get_current_frame()];
                glUniform2fv(tile_ss_index_uniform_loc, 1, glm::value_ptr(player_ss_frame));
                glm::vec2 player_ss_padding = (player_1_ss.get_tile_padding()+1.0f)/player_1_ss.get_file_dimensions();
                glUniform2fv(tile_ss_padding_uniform_loc, 1, glm::value_ptr(player_ss_padding));
            
                glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
            }
            glfwSwapBuffers(window);
        }
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
#endif
    return 0;
}
