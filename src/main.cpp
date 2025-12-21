#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include <vector>

#include "shader.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f
};

std::vector<glm::vec3> cubePositions = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

unsigned int indices[] = {  
    0, 1, 2 
};

glm::vec3 eye(0.0f, 0.0f, 3.0f);
float moveSpeed = 2.5f;

float pitch = 0.0f;
float yaw = -90.0f;
float sensitivity = 0.025f;

glm::vec3 eyeFront(glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch)),
                  glm::sin(glm::radians(pitch)),
                  glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch)));

bool firstFocus = true;
float lastX = WINDOW_WIDTH / 2;
float lastY = WINDOW_HEIGHT / 2;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int polygonMode = GL_FILL;

void toggleWireframe(){
    if(polygonMode == GL_FILL){
        polygonMode = GL_LINE;
    }
    else{
        polygonMode = GL_FILL; 
    }
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_T && action == GLFW_PRESS){
        toggleWireframe();
    }
}

void scroll_callback(GLFWwindow* window, double dx, double dy){
    moveSpeed += (float)dy;
    if(moveSpeed < 0.0f){
        moveSpeed = 0.0f;
    }
}

void mouse_callback(GLFWwindow* window, double x, double y){
    if(firstFocus){
        lastX = x;
        lastY = y;
        firstFocus = false;
    }

    float dx = sensitivity * (x - lastX);
    float dy = sensitivity * (y - lastY);
    lastX = x;
    lastY = y;

    yaw += dx;
    pitch -= dy;

    if(pitch > 89.0f){
        pitch = 89.0f;
    }
    if(pitch < -89.0f){
        pitch = -89.0f;
    }

    eyeFront = glm::vec3(glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch)),
                         glm::sin(glm::radians(pitch)),
                         glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch)));
    eyeFront = glm::normalize(eyeFront);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window){
    float cameraSpeed = moveSpeed * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        eye += cameraSpeed * eyeFront;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        eye -= glm::normalize(glm::cross(eyeFront, glm::vec3(0.0f, 1.0f, 0.1f))) * cameraSpeed;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        eye -= cameraSpeed * eyeFront;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        eye += glm::normalize(glm::cross(eyeFront, glm::vec3(0.0f, 1.0f, 0.1f))) * cameraSpeed;
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        eye += cameraSpeed * glm::vec3(0.0f, 1.0f, 0.0f);
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        eye -= cameraSpeed * glm::vec3(0.0f, 1.0f, 0.0f);
    }
}

int main(int argc, char** argv){

    glfwInit();
    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 3);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Learning OpenGL :)", 0, 0);

    if(window == nullptr){
        std::cout << "Error creating window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Error initializing GLAD\n";
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    

    // setup vertex and buffer data, configure vertex attributes
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    
    GLuint VBO;
    glGenBuffers(1, &VBO);

    GLuint EBO;
    glGenBuffers(1, &EBO); 

    Shader shader("resources/vert.glsl", "resources/frag.glsl");
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);

    while(!glfwWindowShouldClose(window)){ 
        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;

        //input
        processInput(window);
        
        //rendering
        glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = glm::lookAt(eye, eye + eyeFront, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        shader.use();
        glBindVertexArray(VAO);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        for(int i = 0; i < cubePositions.size(); ++i){
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions.at(i));
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(20.0f * i), glm::vec3(0.5f, 1.0f, 0.0f));
            shader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        //check and call events, swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

