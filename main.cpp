#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>

#include <midnight/midnight.ino>

// painstakingly define LED positions
struct Point {
    float x{0.f};
    float y{0.f};
};
std::array<Point, 180> outline_positions{
        Point{4.f, 5.f},
        Point{4.f, 4.5f},
        Point{3.5f, 4.f},
        Point{3.f, 3.5f},
        Point{3.f, 3.f},
        Point{2.5f, 2.5f},
        Point{2.5f, 2.0f},
        Point{2.0f, 1.5f},
        Point{2.0f, 1.0f},
        Point{1.5f, 0.5f},
        Point{1.5f, 0.0f},
        Point{1.5f, -0.5f},
        Point{1.0f, -1.0f},
        Point{1.0f, -1.5f},
        Point{1.0f, -2.0f},
        Point{0.5f, -2.5f},
        Point{0.5f, -3.0f},
        Point{0.5f, -3.5f},
        Point{0.5f, -4.0f},
        Point{0.0f, -4.5f},
        Point{0.0f, -5.0f},
        Point{0.0f, -5.5f},
        Point{0.0f, -6.0f},
        Point{0.0f, -6.5f},
        Point{0.0f, -7.0f},
        Point{0.0f, -7.5f},
        Point{0.0f, -8.0f},
        Point{0.5f, -8.0f},
        Point{1.0f, -7.5f},
        Point{1.5f, -7.0f},
        Point{2.0f, -7.0f},
        Point{2.5f, -6.5f},
        Point{3.0f, -6.5f},
        Point{3.5f, -6.0f},
        Point{4.0f, -6.0f},
        Point{4.0f, -5.5f},
        Point{4.5f, -5.5f},
        Point{5.0f, -5.5f},
        Point{5.0f, -5.0f},
        Point{5.5f, -5.0f},
        Point{6.0f, -4.5f},
        Point{6.5f, -4.0f},
        Point{7.0f, -4.0f},
        Point{7.5f, -4.0f},
        Point{8.0f, -3.5f},
        Point{8.5f, -3.0f},
        Point{9.0f, -3.0f},
        Point{9.5f, -2.5f},
        Point{10.f, -2.5f},
        Point{10.5f, -2.5f},
        Point{11.0f, -3.0f},
        Point{11.5f, -3.0f},
        Point{12.0f, -3.0f},
        Point{12.5f, -3.0f},
        Point{13.0f, -3.0f},
        Point{13.5f, -3.0f},
        Point{14.0f, -2.5f},
        Point{14.5f, -2.0f},
        Point{14.5f, -1.5f},
        Point{15.0f, -1.0f},
        Point{15.5f, -1.0f},
        Point{16.0f, -1.0f},
        Point{16.5f, -1.0f},
        Point{17.0f, -1.0f},
        Point{17.5f, -1.0f},
        Point{18.0f, -1.0f},
        Point{18.5f, -1.0f},
        Point{19.0f, -1.0f},
        Point{19.5f, -1.0f},
        Point{20.0f, -1.0f},
        Point{20.5f, -1.0f},
        Point{21.0f, -1.0f},
        Point{21.5f, -1.0f},
        Point{22.0f, -1.0f},
        Point{22.5f, -1.0f},
        Point{23.0f, -1.0f},
        Point{23.5f, -1.0f},
        Point{24.0f, -1.0f},
        Point{24.5f, -1.0f},
        Point{25.0f, -1.0f},
        Point{25.5f, -1.0f},
        Point{26.0f, -1.0f},
        Point{26.5f, -1.0f},
        Point{27.0f, -1.0f},
        Point{27.5f, -1.0f},
        Point{28.0f, -1.0f},
        Point{28.5f, -1.0f},
        Point{29.0f, -1.0f},
        Point{29.5f, -1.0f},
        Point{30.0f, -1.5f},
        Point{30.5f, -1.0f},
        Point{31.0f, -1.0f},
        Point{31.5f, -0.5f},
        Point{32.0f, -0.5f},
        Point{32.0f, 0.0f},
        Point{32.5f, 0.5f},
        Point{33.0f, 0.5f},
        Point{33.5f, 1.0f},
        Point{34.0f, 1.0f},
        Point{34.0f, 1.5f},
        Point{34.5f, 1.5f},
        Point{34.5f, 2.0f},
        Point{34.5f, 2.5f},
        Point{34.0f, 3.0f},
        Point{33.5f, 3.0f},
        Point{33.5f, 2.5f},
        Point{33.0f, 2.5f},
        Point{33.0f, 2.0f},
        Point{32.5f, 2.0f},
        Point{32.0f, 1.5f},
        Point{31.5f, 1.5f},
        Point{31.0f, 1.0f},
        Point{30.5f, 1.0f},
        Point{30.0f, 1.0f},
        Point{29.5f, 0.5f},
        Point{29.0f, 0.5f},
        Point{28.5f, 0.5f},
        Point{28.0f, 0.5f},
        Point{27.5f, 0.5f},
        Point{27.0f, 0.5f},
        Point{26.5f, 0.5f},
        Point{26.0f, 0.5f},
        Point{25.5f, 0.5f},
        Point{25.0f, 0.5f},
        Point{24.5f, 0.5f},
        Point{24.0f, 0.5f},
        Point{23.5f, 0.5f},
        Point{23.0f, 0.5f},
        Point{22.5f, 0.5f},
        Point{22.0f, 0.5f},
        Point{21.5f, 0.5f},
        Point{21.0f, 0.5f},
        Point{20.5f, 0.5f},
        Point{20.0f, 0.5f},
        Point{19.5f, 0.5f},
        Point{19.0f, 0.5f},
        Point{18.5f, 0.5f},
        Point{18.0f, 0.5f},
        Point{17.5f, 0.5f},
        Point{17.0f, 0.5f},
        Point{16.5f, 0.5f},
        Point{16.0f, 0.5f},
        Point{15.5f, 0.5f},
        Point{15.0f, 0.5f},
        Point{14.5f, 1.0f},
        Point{14.5f, 1.5f},
        Point{14.5f, 2.0f},
        Point{15.0f, 2.5f},
        Point{15.5f, 3.0f},
        Point{16.0f, 3.5f},
        Point{16.5f, 4.0f},
        Point{17.0f, 4.5f},
        Point{17.5f, 5.0f},
        Point{17.5f, 5.5f},
        Point{17.0f, 5.5f},
        Point{16.5f, 5.5f},
        Point{16.0f, 5.5f},
        Point{15.5f, 5.5f},
        Point{15.0f, 5.0f},
        Point{14.5f, 5.0f},
        Point{14.0f, 5.0f},
        Point{13.5f, 4.5f},
        Point{13.0f, 4.5f},
        Point{12.5f, 4.5f},
        Point{12.0f, 4.0f},
        Point{11.5f, 4.0f},
        Point{11.0f, 4.0f},
        Point{10.5f, 3.5f},
        Point{10.0f, 3.5f},
        Point{9.5f, 3.5f},
        Point{9.0f, 3.5f},
        Point{8.5f, 3.5f},
        Point{8.0f, 4.0f},
        Point{7.5f, 4.0f},
        Point{7.0f, 4.0f},
        Point{6.5f, 4.5f},
        Point{6.0f, 4.5f},
        Point{5.5f, 4.5f},
        Point{5.0f, 5.0f},
        Point{4.5f, 5.0f}
};

int main() {
    setup();

    auto const CY{200};
    auto const CX{400};
    sf::RenderWindow window(sf::VideoMode(2 * CX, 2 * CY), "LED Guitar Renderer");

    sf::Music music;
    if (!music.openFromFile("midnight.wav")) {
        return EXIT_FAILURE;
    }

    music.play();
    music.setPlayingOffset(sf::seconds(56.10f));

    sf::Clock clock;

    for (auto i{0u}; i < outline.circles.size(); ++i) {
        auto const x = CX - 200 + outline_positions[i].x * 22;
        auto const y = CY + outline_positions[i].y * 22;
        outline.circles[i].setPosition(x, y);
    }
    for (auto i{0u}; i < e_string.circles.size(); ++i) {
        auto const x{CX - 100 + i * 25.f};
        e_string.circles[i].setPosition(x, CY + 10.f);
        g_string.circles[i].setPosition(x, CY);
        b_string.circles[i].setPosition(x, CY - 10.f);
    }

    unsigned long time_step{0};
    auto updateLEDs = [&]() {
        auto const &elapsed = clock.getElapsedTime();
        if (static_cast<unsigned long>(elapsed.asMicroseconds()) >= time_step * us_per_dt) {
            ++time_step;

            // update leds
            loop();
        }
    };

    while (window.isOpen()) {
        updateLEDs();

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        for (auto const &circle: outline.circles) {
            window.draw(circle);
        }
        for (auto const &circle: e_string.circles) {
            window.draw(circle);
        }
        for (auto const &circle: b_string.circles) {
            window.draw(circle);
        }
        for (auto const &circle: g_string.circles) {
            window.draw(circle);
        }
        window.display();
    }

    return 0;
}
