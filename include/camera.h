#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Movement {
    FORWARD, 
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

const float PITCH = 0.0f; 
const float YAW = -90.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.025f; 
const float ZOOM = 45.0f;

class Camera{
    public:
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 right;
        glm::vec3 up;
        glm::vec3 worldUp;

        float pitch;
        float yaw;
        float speed;
        float sensitivity;
        float zoom;

        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float pitch = PITCH, float yaw = YAW) : front(glm::vec3(0.0f, 0.0f, -1.0f)), speed(SPEED), sensitivity(SENSITIVITY), zoom(ZOOM){
            this->position = position;
            this->worldUp = up;
            this->pitch = pitch;
            this->yaw = yaw;
            updateVectors();
        }
        
        Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float pitch = PITCH, float yaw = YAW) : front(glm::vec3(0.0f, 0.0f, -1.0f)), speed(SPEED), sensitivity(SENSITIVITY), zoom(ZOOM){
            this->position = glm::vec3(posX, posY, posZ);
            this->worldUp = glm::vec3(upX, upY, upZ);
            this->pitch = pitch;
            this->yaw = yaw;
            updateVectors();
        }

        glm::mat4 getViewMatrix(){
            return glm::lookAt(position, position + front, up);
        }

        void processInput(Movement direction, float deltaTime){
            float cameraSpeed = speed * deltaTime;
            if(direction == FORWARD){
                position += cameraSpeed * front;
            }
            if(direction == LEFT){
                position -= cameraSpeed * right;
            }
            if(direction ==  BACKWARD){
                position -= cameraSpeed * front;
            }
            if(direction == RIGHT){
                position += cameraSpeed * right;
            }
            if(direction == UP){
                position += cameraSpeed * worldUp;
            }
            if(direction == DOWN){
                position -= cameraSpeed * worldUp;
            }
        }

        void processMouseMovement(float dx, float dy, GLboolean constrainPitch = true){
            dx *= sensitivity;
            dy *= sensitivity;

            yaw += dx;
            pitch -= dy;

            if(constrainPitch){
                if(pitch < -89.0f){
                    pitch = -89.0f;
                }
                if(pitch > 89.0f){
                    pitch = 89.0f;
                }
            }

            updateVectors();
        }

        void processScroll(float dy){
            speed += dy;
            if(speed < 0.0f){
                speed = 0.0f;
            }
        }

    private:
        void updateVectors(){
            front.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
            front.y = glm::sin(glm::radians(pitch));
            front.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
            front = glm::normalize(front);
            right = glm::normalize(glm::cross(front, worldUp));
            up = glm::normalize(glm::cross(right, front));
        }

};