#include "Particle.h"
#include <iostream>

Particle::Particle(RenderTarget& target, int numPoints, Vector2i mouseClickPosition) : m_A(2, numPoints)
{
    m_ttl = TTL;
    m_numPoints = numPoints;
    m_radiansPerSec = ((float)rand() / (RAND_MAX)) * M_PI;
    m_cartesianPlane.setCenter(0, 0);
    m_cartesianPlane.setSize(target.getSize().x, (-1.0) * target.getSize().y);
    m_centerCoordinate = target.mapPixelToCoords(mouseClickPosition, m_cartesianPlane);

    m_vx = (rand() % 401) + 100; 
    m_vy = (rand() % 401) + 100;

    m_color1 = sf::Color::White;
    m_color2 = sf::Color(rand() % 256, rand() % 256, rand() % 256);

    float theta = static_cast<float>(rand()) / RAND_MAX * (M_PI / 2);
    float dTheta = 2 * M_PI / (numPoints - 1);

    for (int j = 0; j < numPoints; j++){
    int r = rand() % 20 + 60;
    float dx;
    float dy;

    dx = r * cos(theta);
    dy = r * sin(theta);

    m_A(0, j) = m_centerCoordinate.x + dx;
    m_A(1, j) = m_centerCoordinate.y + dy;

    theta += dTheta;
    }

    void Particle::draw(RenderTarget& target, RenderStates states) const override
    {
        VertexArray lines(sf::TriangleFan, m_numPoints + 1);
        lines[0].position = target.mapCoordsToPixel(m_centerCoordinate, m_cartesianPlane);  
        lines[0].color = m_color1;
        for (int j = 1; j < numPoints; j++)
        {
            Vector2f cartesianPoint(m_A(0, j-1), m_A(1, j-1));
            Vector2f pixelPoint = target.mapCoordsToPixel(cartesianPoint, m_cartesianPlane);
            lines[j].position = pixelPoint;
            lines[j].color = m_color2;
        }

        target.draw(lines);
    }
    
    void Particle::update(float dt)
    {
        m_ttl -= dt;
        rotate(dt * m_radiansPerSec);
        scale(SCALE);

        float dx, dy;
        dx = m_vx * dt;
        m_vy -= G * dt;
        dy = m_vy * dt;
        translate(dx, dy);
    }

    void Particle::translate(double xShift, double yShift)
    {
        TranslationMatrix T(xShift, yShift, nCols);
        m_A = T + m_A;
        m_centerCoordinate.x += xShift;
        m_centerCoordinate.y += yShift;
    }

    void Particle::rotate(double theta)
    {
        Vector2f temp = m_centerCoordinate;
        translate(-m_centerCoordinate.x, -m_centerCoordinate.y);

        RotationMatrix R(theta);

        m_A = R * m_A;

        translate(temp.x, temp.y);

    }

    void Particle::scale(double c)
    {
        Vector2f temp = m_centerCoordinate;
        translate(-m_centerCoordinate.x, -m_centerCoordinate.y);

        ScalingMatrix S(c);
 
        m_A = S * m_A;
        translate(temp.x, temp.y);
    }


}   
