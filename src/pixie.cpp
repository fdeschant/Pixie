#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <imgui-SFML.h>
#include <imgui.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <math.h>

#include "noise.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "Pixie - Mapper");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);
    OpenSimplexNoise::Noise noise(1);
    int x =0,imgsize = 350;

    sf::Vector2f offset{0,0};
    sf::Vector2f zoom{0.00001,0.00001};
    sf::Vector2u windowSize = window.getSize();


    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_LeftArrow)))
        {
            offset.x--;
        }
        if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_RightArrow)))
        {
            offset.x++;
        }
        if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_UpArrow)))
        {
            offset.y--;
        }
        if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_DownArrow)))
        {
            offset.y++;
        }
        if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_PageUp )))
        {
            zoom.x*=1.01;
            zoom.y*=1.01;
        }
        if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_PageDown )))
        {
            zoom.x*=0.99;
            zoom.y*=0.99;
        }
        sf::Time elapsed = deltaClock.getElapsedTime();
        ImGui::SFML::Update(window, deltaClock.restart());
        window.clear();
        
        if(ImGui::BeginMainMenuBar())
        {
            if(ImGui::BeginMenu("Menu"))
            {
                ImGui::MenuItem("(demo menu)", NULL, false, false);
                ImGui::MenuItem("(demo menu)", NULL, false, false);
                ImGui::MenuItem("(demo menu)", NULL, false, false);
                ImGui::MenuItem("(demo menu)", NULL, false, false);
                ImGui::EndMenu();
            }
            ImGui::ShowMetricsWindow();
            ImGui::EndMainMenuBar();
            
        }
        //ImGui::ShowDemoWindow();
        // All Drawing goes here
        
            sf::Texture texture;
            texture.create(windowSize.x,windowSize.y);

            sf::Image image;
            image.create(windowSize.x,windowSize.y);

            
            //ImGui::BeginTable("pixels",1024);
            for(int i = 0; i < windowSize.x; ++i)
            {
                //ImGui::TableNextRow();
                for(int j = 0; j < windowSize.y; ++j)
                {
                    double n = ( noise.eval((offset.x + (double)i)*zoom.x*windowSize.x ,(offset.y + (double)j) * zoom.y * windowSize.y,(double)0.001)+1)/2;
                    uint8_t r = n*256;
                    if(r > 128)
                    image.setPixel(i,j,sf::Color(r,r,r));

                    
                    //ImGui::TableNextColumn();
                    //ImGui::Text("%d", r);

                }
            }
            //ImGui::EndTable();

            texture.loadFromImage(image);
            sf::Sprite sprite;
            sprite.setTexture(texture);

            window.draw(sprite);
            
            windowSize = window.getSize();
            x++;
        

        // All drawing stops here
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}
