#include <Camera.h>
#include <OpenGL.h>

Camera::Camera() :
myHorizontalAngle(180.f),
myVerticalAngle(0.f)
{

}

void Camera::move(const sf::Vector3f& speed, int elapsedTime)
{
    myDeltaPos = speed * static_cast<float>(elapsedTime);
}

void Camera::rotate(float horizontal, float vertical)
{
    myHorizontalAngle += horizontal;
    myVerticalAngle += -vertical;

    if(myHorizontalAngle < 0.f)
        myHorizontalAngle += 360.f;
    if(myHorizontalAngle > 360.f)
        myHorizontalAngle -= 360.f;

    // For vertical angle, limit the angle to avoid gimbal lock
    // or similar issues
    if(myVerticalAngle < -89.f)
        myVerticalAngle = -89.f;
    if(myVerticalAngle > 89.f)
        myVerticalAngle = 89.f;
}

void Camera::place()
{
    glRotatef(-myVerticalAngle, 1.f, 0.f, 0.f);     // Rotation around X-axis
    glRotatef(myHorizontalAngle, 0.f, 1.f, 0.f);    // Rotation around Y-axis

    // TODO: implement a real quaternion/matrix based solution
    //       without this hack using the internal OpenGL matrix

    // Get the current rotation transform
    float mat[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, mat);

    // Extract the right and forward vector from the matrix
    sf::Vector3f right(mat[0], mat[4], mat[8]);
    //Vector3f up(mat[1], mat[5], mat[9]);
    sf::Vector3f forward(mat[2], mat[6], mat[10]);

    // Update the position regarding the rotation transform
    myPosition += right * myDeltaPos.x;
    myPosition += forward * myDeltaPos.z;

    glTranslatef(myPosition.x, myPosition.y, myPosition.z);
}