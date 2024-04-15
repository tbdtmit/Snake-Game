#include"Menu.h"

using namespace std;
using namespace sf;




Menu::Menu(sf::RenderWindow& window) : window(window) {
    if (!font.loadFromFile("../Data/arial.TTF"))
    {

    }

    title.setFont(font);
    title.setString("Snake Game");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::White);
    title.setPosition(250, 100);

    startOption.setFont(font);
    startOption.setString("Start Game ");
    startOption.setCharacterSize(24);
    startOption.setFillColor(sf::Color::White);
    startOption.setPosition(300, 200);

    highScore.setFont(font);
    highScore.setString("High Score ");
    highScore.setCharacterSize(24);
    highScore.setFillColor(sf::Color::White);
    highScore.setPosition(300, 250);

    exitOption.setFont(font);
    exitOption.setString("Exit Game ");
    exitOption.setCharacterSize(24);
    exitOption.setFillColor(sf::Color::White);
    exitOption.setPosition(300, 300);

    square.setPointCount(4);
    square.setRadius(15.f);
    square.setFillColor(Color::Yellow);
    square.setPosition(Vector2f(250, 200));

    selectedOption = 0; // 0: Start, 1: Exit
}

void Menu::draw() {
    window.clear();
    window.draw(square);
    window.draw(title);
    window.draw(startOption);
    window.draw(highScore);
    window.draw(exitOption);
    window.display();
}
void Menu::draw_score() {
    window.clear();
    int sc = get_score();
    //out << sc << endl;
    sf::Text s;
    s.setFont(font);
    s.setString("Your High Score : " + to_string(sc));
    s.setCharacterSize(50);
    s.setFillColor(sf::Color::Yellow);
    s.setPosition(180, 250);
    window.draw(s);
    window.display();
}
void Menu::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Down) {
                // Người chơi chọn "Start Game"
                selectedOption = (selectedOption + 1) % 3;
                square.setPosition(250, selectedOption * 50 + 200);
            }
            if (event.key.code == sf::Keyboard::Up) {
                // Người chơi chọn "Exit Game"
                selectedOption -= 1;
                if (selectedOption == -1) selectedOption = 2;
                square.setPosition(250, selectedOption * 50 + 200);

            }
            if (event.key.code == sf::Keyboard::Return) {
                // Người chơi chọn "Exit Game"
                if (selectedOption == 0) {
                    // Người chơi đã chọn "Start Game"
                    // Bắt đầu trò chơi tại đây
                    gamePlay();
                }
                else if (selectedOption == 2) {

                    // Người chơi đã chọn "Exit Game"
                    exit(1);
                }
                else if (selectedOption == 1) {
                    // Hiện điểm cao
                    while (back() == 0)
                        draw_score();

                }


            }

        }
    }
    //cout << "no" << endl;
    //return -1; // Không có sự kiện lựa chọn
}

//extern Music theme;
void Menu::gamePlay()
{

    Snake snake(20); // 20 is the size of each grid cell.
    Food food(20, snake);
    superFood sfood(40, snake);
    Clock tim;
    Clock tim_sf;

    int cnt = 0;
    bool check = 0;

    sf::SoundBuffer ballSFX;
    ballSFX.loadFromFile("../Data/mixkit-hungry-man-eating-2252.wav");
    sf::Sound sfx;
    sfx.setBuffer(ballSFX);

    sf::SoundBuffer o;
    o.loadFromFile("../Data/mixkit-funny-game-over-2878.wav");
    sf::Sound over;
    over.setBuffer(o);

    int vol = 100;
    sf::Music music;
    if (!music.openFromFile("../Data/mixkit-tech-house-vibes-130.ogg"))
        cout << "music error " << endl;
    //return -1; // error

    music.play();
    music.setLoop(true);

    while (window.isOpen()) {
        music.setVolume(vol);
        sfx.setVolume(vol);
        over.setVolume(vol);
        sf::Event event;
        while (window.pollEvent(event)) {
            // sử dụng như 1 ngắt ngoài có thể nhảy vào bất cứ lúc nào ấn nút
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                //cout << "in poll" << endl;
                if (event.key.code == sf::Keyboard::Space) {
                    while (1) {
                        bool sp = 0;
                        while (window.pollEvent(event))
                        {

                            if (event.type == sf::Event::KeyPressed)
                                sp = 1;

                        }
                        if (sp) break;
                    }
                }
                if (event.key.code == sf::Keyboard::Left && snake.getDirection() != sf::Vector2f(snake.getGridSize(), 0)) {
                    snake.setDirection(sf::Vector2f(-snake.getGridSize(), 0)); break;
                }
                if (event.key.code == sf::Keyboard::Right && snake.getDirection() != sf::Vector2f(-snake.getGridSize(), 0)) {
                    snake.setDirection(sf::Vector2f(snake.getGridSize(), 0)); break;
                }
                if (event.key.code == sf::Keyboard::Up && snake.getDirection() != sf::Vector2f(0, snake.getGridSize())) {
                    snake.setDirection(sf::Vector2f(0, -snake.getGridSize())); break;
                }
                if (event.key.code == sf::Keyboard::Down && snake.getDirection() != sf::Vector2f(0, -snake.getGridSize())) {
                    snake.setDirection(sf::Vector2f(0, snake.getGridSize())); break;
                }

                if (event.key.code == sf::Keyboard::Escape) {
                    int sc = get_score();
                    if (snake.score > sc)
                        write_score(snake.score);
                    return;
                }

                if (event.key.code == sf::Keyboard::Q) {
                    if (vol >= 10)
                        vol -= 10;
                }
                if (event.key.code == sf::Keyboard::E) {
                    if (vol <= 90)
                        vol += 10;
                }

            }
        }



        // Game logic
        //cout << "out poll" << endl;
        snake.move();


        // Check if the snake ate the food
        if (snake.headCollidesWithFood(food)) {
            sfx.play();

            cnt += 1;
            snake.grow();
            food.generate(snake);

            snake.score += food.score;
            cout << snake.score << endl;
        }

        if (cnt == 5)
        {
            check = 1;
            cnt = 0;
            sfood.generate(snake);
            tim_sf.restart();

        }
        if (snake.headCollidesWithFood(sfood)) {
            sfx.play();
            snake.score += sfood.score;
            check = 0;
            sfood.setPosition(Vector2f(800, 800));
            cout << snake.score << endl;
        }
        if (tim_sf.getElapsedTime().asMilliseconds() > 3000)
        {
            check = 0;
            sfood.setPosition(Vector2f(800, 800));
        }
        // Check for collisions with walls and itself
        if (snake.isCollidingWithItself()) {
            over.play();
            // Game over logic
            // You can implement game over handling here
            // For example, display a game over message and restart the game.
            int sc = get_score();
            if (snake.score > sc)
                write_score(snake.score);

            return;
        }

        // Rendering
        window.clear();
        if (check) sfood.render(window);
        snake.render(window);
        food.render(window);


        window.display();
        tim.restart();
        while (tim.getElapsedTime().asMilliseconds() <= 100);
    }

}


bool Menu::back()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            return 1;

        }
    }
    return 0;
}

void Menu::write_score(int sc)
{
    ofstream ofs("score.txt");
    if (ofs.is_open()) {
        ofs << sc << "\n";
        ofs.close();
        std::cout << "High scores have been written to the file." << std::endl;
    }
    else {
        std::cerr << "Unable to open the file for writing." << std::endl;
    }
}

int Menu::get_score()
{
    ifstream ifs("score.txt");
    if (ifs.is_open()) {
        int score;
        ifs >> score;

        ifs.close();

        return score;
    }
    else {
        std::cerr << "Unable to open the file for reading." << std::endl;
    }

}

void Menu::lauch()
{
    while (true)
    {
        draw();
        handleInput();
    }
}
