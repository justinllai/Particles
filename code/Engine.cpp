#include "Engine.h"
#include <iostream>

using namespace std;

    Engine::Engine() 
    {
        m_Window.create(VideoMode::getDesktopMode());
    }

    void Engine::run() 
    {
        Clock theClock;

        cout << "Starting Particle unit tests..." << endl;
        Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
        p.unitTests();
        cout << "Unit tests complete.  Starting engine..." << endl;

        while (m_Window.isOpen())
        {
            Time time1 = theClock.restart();


            input();
            update(time1.asSeconds());
            draw();
        }
    }

    void Engine::input() 
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }
            if (event.mouseButton.button == Mouse::Left)
            {
                Vector2i mouseClickPosition = Mouse::getPosition(m_Window);
                for (int i = 0; i < 5; ++i) {
                int numPoints = rand() % 26 + 25;  
                Particle newParticle(m_Window, numPoints, mouseClickPosition);  
                m_particles.push_back(newParticle);  
                }
            }
        }
    }

    void Engine::update(float dtAsSeconds) 
    {
        for (auto iterator = m_particles.begin(); iterator != m_particles.end(); ) {
            if (iterator->getTTL() > 0.0) {
                iterator->update(dtAsSeconds);
                ++iterator;
            } else {
                iterator = m_particles.erase(iterator); 
            }
        }
    }

    void Engine::draw() 
    {
        m_Window.clear();

        for (auto iterator = m_particles.begin(); iterator != m_particles.end(); ++iterator) {
            m_Window.draw(*iterator); 
        }

        
        m_Window.display();
    }

}
