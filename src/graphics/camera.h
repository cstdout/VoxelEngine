#ifndef CAMERA_H
#define CAMERA_H

#include "src/vectormath/vec3.h"
#include "src/vectormath/mat4.h"

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};


class Camera
{
public:

    Camera();

    float Yaw         = -90.0f;
    float Pitch       =  0.0f;
    float Speed       =  2.5f;
    float Sensitivity =  0.1f;

    Vec3 Position;
    Vec3 Front;
    Vec3 Up;
    Vec3 Right;
    Vec3 WorldUp;

    Mat4* viewMatrix = nullptr;

    void onKeyboard(Camera_Movement direction, float deltaTime);
    void onMouse(float xoffset, float yoffset, bool constrainPitch = true);

    void setViewMatrix(Mat4* viewMatrix);
    void updateViewMatrix();
    void init(Mat4* viewMatrix,
              Vec3 position,
              float upX = 0.0f,
              float upY = 1.0f,
              float upZ =  0.0f,
              float yaw = -90.f,
              float pitch = 0.0f,

              float movementSpeed = 2.5,
              float mouseSensitivity = 0.1f);
private:

    void updateCameraVectors();
    // Temporary vector for onKeyboard method
    Vec3 positionDelta;

    //Vectors for temporary computations of Mat4::lookAt method
    Vec3 centerVec;
    Vec3 f;
    Vec3 s;
    Vec3 u;
};

#endif // CAMERA_H
