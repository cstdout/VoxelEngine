#include "camera.h"

Camera::Camera()
{

}
void Camera::init(Mat4* viewMatrix,
                  Vec3 position,
                  float upX,
                  float upY,
                  float upZ,
                  float yaw,
                  float pitch,
                  float movementSpeed,
                  float mouseSensitivity)
{
    this->viewMatrix = viewMatrix;
    Position = position;
    WorldUp = Vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
    Front = Vec3(0.0f, 0.0f, -1.0f);

    Speed = movementSpeed;
    Sensitivity = mouseSensitivity;
}
