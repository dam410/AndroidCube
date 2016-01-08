#include <vector>
#include <cmath>

#include <SFML/Window/Touch.hpp>
#include <SFML/OpenGL.hpp>

#include "logger/Log.hpp"
#include "sft/VectorFunctions.hpp"
#include "Cube.hpp"

Cube::Cube(float size) :
    size{size},
    angle{},
    speed{},
    V{0,0,1},
    theta{},
    maxSpeed{0.02,0.02},
    face1 {

        1,  1, -1,
        -1,  1, -1,
        -1,  1,  1,

        1,  1, -1,
        -1,  1,  1,
        1,  1,  1,

        1, -1, -1,
        -1, -1,  1,
        -1, -1, -1,

        1, -1, -1,
        1, -1,  1,
        -1, -1,  1,

    },

    face2{

        1, -1,  1,
        1,  1,  1,
        -1,  1,  1,

        1, -1,  1,
        -1,  1,  1,
        -1, -1,  1,

        1, -1, -1,
        -1,  1, -1,
        1,  1, -1,

        1, -1, -1,
        -1, -1, -1,
        -1,  1, -1,

    },

    face3 {

        1, -1, -1,
        1,  1, -1,
        1,  1,  1,

        1, -1, -1,
        1,  1,  1,
        1, -1,  1,

        -1, -1, -1,
        -1,  1,  1,
        -1,  1, -1,

        -1, -1, -1,
        -1, -1,  1,
        -1,  1,  1,

    }

{

}

void Cube::draw() const
{
    glPushMatrix();

    glScalef(size, size, size);

    glColor4f(1.0,1.0,1.0,1.0);


    glRotatef(theta * 180 / M_PI, V.x, V.y, V.z);

    glEnableClientState(GL_VERTEX_ARRAY);

    // Face1
    glColor4f(1.0,0.0,0.0,1.0);
    glVertexPointer(3, GL_FLOAT, 0, &face1[0]);
    glDrawArrays(GL_TRIANGLES, 0, face1.size() / 3);

    // Face2
    glColor4f(0.0,1.0,0.0,1.0);
    glVertexPointer(3, GL_FLOAT, 0, &face2[0]);
    glDrawArrays(GL_TRIANGLES, 0, face2.size() / 3);

    // Face3
    glColor4f(0.0,0.0,1.0,1.0);
    glVertexPointer(3, GL_FLOAT, 0, &face3[0]);
    glDrawArrays(GL_TRIANGLES, 0, face3.size() / 3);

    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();

}

void Cube::update(float time)
{

    if (sf::Touch::isDown(0)) {

        auto currentPosition = sf::Touch::getPosition(0);
        auto move = currentPosition - previousPosition;
        previousPosition = currentPosition;

        if (!wasDown) {
            wasDown = true;
            return;
        }

        speed.x -= (float) move.x / 5000;
        speed.y += (float) move.y / 5000;

        speed.x = speed.x > 0 ? std::min(speed.x, maxSpeed.x) : std::max(speed.x, -maxSpeed.x);
        speed.y = speed.y > 0 ? std::min(speed.y, maxSpeed.y) : std::max(speed.y, -maxSpeed.y);

    } else {

        wasDown = false;

    }

    sf::Vector3f dV;

    dV.x = time * speed.y;
    dV.y = time * speed.x;

    float dTheta = dV.y * dV.y + dV.x * dV.x;

    if (std::abs(dTheta) < 0.01) {
        return;
    }

    sft::normalize(dV);

    float cosT2 = std::cos(theta/2),
          sinT2 = std::sin(theta/2),
          cosDT2 = std::cos(dTheta/2),
          sinDT2 = std::sin(dTheta/2);

    sf::Vector3f A =
        cosT2 * sinDT2 * dV +
        cosDT2 * sinT2 * V  +
        sinDT2 * sinT2 * sft::crossProduct(dV, V);

    theta = 2 * std::acos(cosT2 * cosDT2 - sinT2 * sinDT2 * (sft::dotProduct(dV, V)));

    V = A;
    sft::normalize(V);

    speed.x /= 1.01;
    speed.y /= 1.01;
}
