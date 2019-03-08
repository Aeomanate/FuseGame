// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 08.03.2019.
//

#include "March8.hpp"

/*
MemoryTextureStorage march8_sprite_sheet {
      "March8SpriteSheet",
      { 15840, 4800 },
      { 0, 0 },
      MemoryTextureStorage::dontTouchAnything,
      { 22, 10 }
};
*/
March8::March8(sf::Vector2u screen)
// : secret_animation { march8_sprite_sheet, 60, -1 }
{
    font.loadFromMemory(font_source.data(), font_source.size());
    march8_text.setFont(font);
    march8_text.setCharacterSize(36);
    march8_text.setFillColor(sf::Color(10, 255, 10));
    march8_text.setOutlineColor(sf::Color(250, 20, 20));
    march8_text.setOutlineThickness(4);
    
    sf::Vector2f v = { screen.x / 0.5f, screen.y / 2.0f};
    march8_text.move(v / 8.0f );
    
    march8_text.setString(
        L"Привет, Камилла! Поздравляю тебя с восьмым марта!\n"
        L"Мы не раз обсуждали игру, в основе которой будет задача про гранату\n"
        L"За эти две недели я перешёл от мечты к реальности. Надеюсь, \n"
        L"такая реальность тебе нравится. И, надеюсь, когда-нибудь \n"
        L"понравится и математика. Жаль только, что мы вместе это не написали.\n"
        L"Но я всё ещё верю, что вместе мы всегда напишем лучше.\n"
        L"\n"
        L"Каждое твоё действие в новом дне всегда будет лучше предыдущих,\n"
        L"поэтому любое твоё решение всегда будет стремиться к лучшему варианту.\n"
        L"Лучшего проще всего добиться, используя точные науки.\n"
        L"Теория оптимизаций, теория игр - как раз про оптимумы и лучшие решения.\n"
        L"Если ты воспитаешь у себя любовь к математике, то сможешь\n"
        L"по-настоящему свободно выражать свои мысли как речью, так и кодом.\n"
        L"Ведь математика даёт не только задачи решать, но и помогает \n"
        L"структурировать твоё представление о мире вокруг.\n"
        L"\n"
        L"Знай, что я очень рад, если ты увидела это поздравление.\n"
        L"И знай, что ты навсегда останешься в памяти моей и этого компьютера,\n"
        L"даже если ты мне больше не напишешь. С праздником!\n"
        L"                                            -- Lyosha12, 08.03.2019"
    );
}

ProgramEvents March8::update() {
    ProgramEvents generated_events;
    
    /*
    if(is_secret_animation) {
        secret_animation.update();
    }
    
    append(generated_events, eventsWalker( RUN_FOR_ALL_OF_RECEIVED_EVENTS {

        if(std::holds_alternative<March8Music1End>(e)) {
            is_secret_animation = true;
        }
    }));
    */
    
    return generated_events;
}
void March8::notify(ProgramEvent e) {
    received_events.push_back(e);
}
void March8::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    /*
    if(is_secret_animation) {
        target.draw(secret_animation, states);
    }
    */
    
    target.draw(march8_text, states);
}