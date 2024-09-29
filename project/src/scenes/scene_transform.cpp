#include "scene_transform.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "utils.h"
#include "iostream"

SceneTransform::SceneTransform(Resources &res, bool &isMouseMotionEnabled, bool &isThirdPerson, bool &isOrtho)
    : Scene(res), m_isMouseMotionEnabled(isMouseMotionEnabled), m_isThirdPerson(isThirdPerson), m_isOrtho(isOrtho),
      m_cameraPosition(0.0f, 1.0f, 5.0f), m_cameraOrientation(0.0f, 0.0f), m_carouselAngleRad(0.0f),
      m_carouselFrame("../models/carousel_frame.obj"),
      m_carouselPole("../models/carousel_pole.obj"),
      m_carouselHorse("../models/carousel_horse.obj")
{
}

void SceneTransform::run(Window &w)
{
    updateInput(w);
    // TODO
    const float SCREEN_SIZE_ORTHO = 5.0f;
    float aspectRatio = static_cast<float>(w.getWidth()) / static_cast<float>(w.getHeight());

    glm::mat4 projection;
    if (m_isOrtho)
    {
        projection = glm::ortho(-SCREEN_SIZE_ORTHO / 2 , SCREEN_SIZE_ORTHO / 2,
                                -SCREEN_SIZE_ORTHO / 2, SCREEN_SIZE_ORTHO / 2, 0.1f, 100.0f);
    }
    else
    {
        projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
    }

    glm::mat4 view = m_isThirdPerson ? getCameraThirdPerson() : getCameraFirstPerson();

    float carouselHorseTranslation = sin(m_carouselAngleRad * 2.0f) / 6.0f;
    const int N_HORSES = 5;

    m_resources.transformSolidColor.use();

    glm::mat4 carouselBase = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.1f, 0.0f));

    // Dessiner la base du carrousel
    glm::mat4 mvp = projection * view * carouselBase;
    GLint mvpLoc = m_resources.transformSolidColor.getUniformLoc("mvp");
    GLint colLoc = m_resources.transformSolidColor.getUniformLoc("uniformColor");

    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
    glUniform3f(colLoc, 0.7f, 0.0f, 0.0f); // Rouge

    m_carouselFrame.draw();

    for (int i = 0; i < N_HORSES; i++)
    {
        float angle = (2.0f * glm::pi<float>() * i) / N_HORSES;
        glm::mat4 horseTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        horseTransform = glm::rotate(horseTransform, m_carouselAngleRad + angle, glm::vec3(0.0f, 1.0f, 0.0f));
        horseTransform = glm::translate(horseTransform, glm::vec3(1.7f, 0.0f, 0.0f));

        // Dessiner le pôle
        mvp = projection * view * horseTransform;
        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
        glUniform3f(colLoc, 0.0f, 0.7f, 0.0f); // Vert
        m_carouselPole.draw();

        // Dessiner le cheval
        glm::mat4 horseAnimation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, carouselHorseTranslation * (i % 2 == 0 ? 1 : -1), 0.0f));
        mvp = projection * view * horseTransform * horseAnimation;
        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
        glUniform3f(colLoc, 0.0f, 0.0f, 0.7f); // Bleu
        m_carouselHorse.draw();
    }

    m_carouselAngleRad -= 0.01f;
}

void SceneTransform::updateInput(Window &w)
{
    int x = 0, y = 0;
    if (m_isMouseMotionEnabled)
        w.getMouseMotion(x, y);
    m_cameraOrientation.y -= x * 0.001f;
    m_cameraOrientation.x -= y * 0.001f;

    glm::vec3 positionOffset = glm::vec3(0.0);
    const float SPEED = 0.1f;
    if (w.getKeyHold(Window::Key::W))
        positionOffset.z -= SPEED;
    if (w.getKeyHold(Window::Key::S))
        positionOffset.z += SPEED;
    if (w.getKeyHold(Window::Key::A))
        positionOffset.x -= SPEED;
    if (w.getKeyHold(Window::Key::D))
        positionOffset.x += SPEED;

    if (w.getKeyHold(Window::Key::Q))
        positionOffset.y -= SPEED;
    if (w.getKeyHold(Window::Key::E))
        positionOffset.y += SPEED;

    positionOffset = glm::rotate(glm::mat4(1.0f), m_cameraOrientation.y, glm::vec3(0.0, 1.0, 0.0)) * glm::vec4(positionOffset, 1);
    m_cameraPosition += positionOffset;
}

glm::mat4 SceneTransform::getCameraFirstPerson()
{
    // TODO
    // 
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::rotate(view, -m_cameraOrientation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::rotate(view, -m_cameraOrientation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::translate(view, -m_cameraPosition);
    return view;
}

glm::mat4 SceneTransform::getCameraThirdPerson()
{
    // TODO
    //transformees spherique scartesien
    const float radius = 6.0f;
    float camX = sin(m_cameraOrientation.y) * radius;
    float camZ = cos(m_cameraOrientation.y) * radius;
    glm::vec3 cameraPos = glm::vec3(camX, 1.0f, camZ);
    return glm::lookAt(cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}