#include <vector>
#include <algorithm>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <SFML/OpenGL.hpp>

#include "logger/Log.hpp"
#include "Cube.hpp"

int main(int argc, char *argv[])
{
    logger::cinfo << "Main started" << logger::endl;

    sf::ContextSettings settings{24, 8, 0, 1, 1};
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "", sf::Style::Default, settings);

    double near = 0.02;
    double far = 3000;

    sf::Vector2i lastTouch;

    Cube cube(0.1);

    // logger::cdebug << (mesh.loadFromFile("cube.obj") ? "true" : "false") << logger::endl;
    // logger::cdebug << "Mesh loaded : " << mesh.m_vertex_array.size() << " vertices" << logger::endl;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // glFrustumf(-0.5 * near, 0.5 * near, 0.5 * ((double) 1920 / 1080) * near,  - 0.5 * ((double) 1920 / 1080) * near, near, far);
    // glScalef(1,1,-1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFlush();

    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    while (window.isOpen())
    {
        glEnable(GL_DEPTH_TEST);

        sf::Event event;

        while (window.pollEvent(event))
        {

            sf::Vector2i move;
            float aspect;

            switch (event.type) {

                case sf::Event::TouchBegan:

                    lastTouch.x = event.touch.x;
                    lastTouch.y = event.touch.y;

                    logger::cinfo << "TouchBegan" << logger::endl;
                    break;

                case sf::Event::TouchMoved:

                    break;

                case sf::Event::Closed:
                    logger::cinfo << "Event received : closed" << logger::endl;
                    window.close();
                    break;

                case sf::Event::LostFocus:
                    logger::cinfo << "Lost focus" << logger::endl;
                    break;

                case sf::Event::GainedFocus:
                    logger::cinfo << "Gained focus" << logger::endl;
                    break;

                case sf::Event::MouseLeft:
                    logger::cinfo << "Mouse left" << logger::endl;
                    break;

                case sf::Event::MouseEntered:
                    logger::cinfo << "Mouse entered" << logger::endl;
                    break;


                case sf::Event::Resized:

                    logger::cdebug << "Resized : ("
                        << event.size.width
                        << ","
                        << event.size.height
                        << ")"
                        << logger::endl;

                    glMatrixMode(GL_PROJECTION);
                    glLoadIdentity();

                    aspect =  (float) std::max(event.size.height, event.size.width) / std::min(event.size.height, event.size.width);

                    window.setSize(sf::Vector2u{event.size.width, event.size.height});
                    glFrustumf(
                        -0.5 * near,
                        0.5 * near,
                        0.5 * (aspect) * near,
                        - 0.5 * (aspect) * near,
                        near,
                        far
                    );

                    glScalef(1,1,-1);

                    break;

                case sf::Event::KeyPressed:

                    if (event.key.code == sf::Keyboard::Escape)
                        window.close();

                    break;

                default:
                    break;

            }

        }

        // Update
        cube.update(20);

        // Draw
        window.clear(sf::Color::Black);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslatef(0,0,1);

        cube.draw();

        glFlush();
        window.display();
    }

    logger::cinfo << "Main finished" << logger::endl;

}
