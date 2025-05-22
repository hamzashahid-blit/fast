#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <ostream>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "entity.h"

#define INFO_LOG_LEN 512
#define ASPECT_RATIO (static_cast<float>(WIN_WIDTH) / WIN_HEIGHT)

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
    "void main() {\n"
    "    oColor = texture(Tex, fTexCoord) * vec4(1.0, 1.0, 1.0, 1.0);\n"
    "}\0";

int shader_success;
char info_log[INFO_LOG_LEN];

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    WIN_WIDTH = width;
    WIN_HEIGHT = height;
    glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
}    

int main() {
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
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "[ERROR] Failed to initialize GLAD!" << std::endl;
        return -1;
    }

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

    auto grass_tile = Tile(0.5f, 0.5f, "res/Base pack/Tiles/grass.png");
    
    glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.2f, 0.3f, 1.0f);

    unsigned int model_uniform_loc = glGetUniformLocation(shader_program, "uModel");
    unsigned int view_uniform_loc = glGetUniformLocation(shader_program, "uView");
    unsigned int projection_uniform_loc = glGetUniformLocation(shader_program, "uProjection");
    
    while (!glfwWindowShouldClose(window)) {
        /// Input
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            std::cout << "Yay!\n";
        /// Update Then Render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_program);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, grass_tile.get_tex());
        glBindVertexArray(vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        
        auto model_mat = glm::mat4(1.0f);
        model_mat = glm::translate(model_mat,
                                   glm::vec3(-ASPECT_RATIO + grass_tile.get_position().x * 2*ASPECT_RATIO,
                                             1.0 - grass_tile.get_position().y * 2,
                                             0.0f));
        // model_mat = glm::scale(model_mat, glm::vec3(0.2f));
        glUniformMatrix4fv(model_uniform_loc, 1, GL_FALSE, glm::value_ptr(model_mat));
        auto view_mat = glm::mat4(1.0f);
        view_mat = glm::translate(view_mat, glm::vec3(0.0f, 0.0f, -1.0f));
        glUniformMatrix4fv(view_uniform_loc, 1, GL_FALSE, glm::value_ptr(view_mat));
        auto projection_mat =
            glm::ortho(-ASPECT_RATIO, ASPECT_RATIO, -1.0f, 1.0f, 0.1f, 100.0f);
        glUniformMatrix4fv(projection_uniform_loc, 1, GL_FALSE, glm::value_ptr(projection_mat));
        
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        /// Swap & Poll
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    glfwTerminate();
    return 0;
}
