// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 18.05.2018.
//

#include "WindowForTests.hpp"

WindowForTests::WindowForTests(sf::VideoMode screen, sf::Drawable const& drawable)
: original_screen(screen)
, screen_for_test(
    static_cast<unsigned>(screen.width*scale_input),
    static_cast<unsigned>(screen.height*scale_input)
  )
, window(screen_for_test, "Test Window")
, drawable(drawable)
{ window.setFramerateLimit(60); }

void WindowForTests::run(sf::RenderStates states) {
    while(window.isOpen()) {
        handling_events();
        draw(states);
    }
}
void WindowForTests::handling_events() {
    sf::Event event;
    
    while(window.pollEvent(event)) {
        switch(event.type) {
            case sf::Event::EventType::Closed:
                window.close();
                break;
            
            default:
                break;
        }
    }
}

void WindowForTests::draw(sf::RenderStates states) {
    sf::Vector2f p1 = sf::Vector2f {
        window.getSize().x - float(original_screen.width),
        window.getSize().y - float(original_screen.height)
    } / 2.0f;
    
    sf::RectangleShape rectangle_shape({
        float(original_screen.width),
        float(original_screen.height)
    });
    rectangle_shape.setFillColor({0, 0, 0, 0});
    rectangle_shape.setOutlineColor({255, 100, 100});
    rectangle_shape.setOutlineThickness(1);
    rectangle_shape.move(p1);
    
    states.transform.translate(p1);
    
    window.clear({100, 100, 100});
    
    window.draw(drawable, states);
    window.draw(rectangle_shape);
    
    window.display();
}