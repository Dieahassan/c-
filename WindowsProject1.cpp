#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
using namespace sf;
struct snake 
{
	int x,y;
};
struct fruit
{
	int x=10, y=10;
};
int num=2,v=5;
enum diraction{top,down,right,lift}dir;
class Game
{
public:
    int n = 30, m = 25;
    int size = 16;
    int h = n * size, w = m * size;
    snake s1[301];
    Game()
    {
        s1[0].x = rand() % n; s1[0].y = rand() % m;
    };
    fruit f1;
    void g1();
};
Game G1;
Music m1;
RenderWindow window(VideoMode(G1.h, G1.w), "Snake Game!");
int main()
{
    srand(time(0));
    Texture t1, t2,t3;
    t1.loadFromFile("images/white1.png");
    t2.loadFromFile("images/red.png");
    t3.loadFromFile("images/ap11.png");
    m1.openFromFile("Fur Elise Piano Mp3 - Free-Loops.com.mp3");
    Sprite sprite1(t1);
    Sprite sprite2(t2);
    Sprite sprite3(t3);
    m1.play();
    Clock clock;
    float timer = 0, delay = 0.1;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
        Event e;
        m1.setVolume(v);
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }
        /************************* KEYBOARD **************************************************/
        if (Keyboard::isKeyPressed(Keyboard::Left)) dir = lift;
        if (Keyboard::isKeyPressed(Keyboard::A)) dir = lift;
        if (Keyboard::isKeyPressed(Keyboard::Right)) dir = right;
        if (Keyboard::isKeyPressed(Keyboard::D)) dir = right;
        if (Keyboard::isKeyPressed(Keyboard::Up)) dir = top;
        if (Keyboard::isKeyPressed(Keyboard::W)) dir = top;
        if (Keyboard::isKeyPressed(Keyboard::Down)) dir = down;
        if (Keyboard::isKeyPressed(Keyboard::S)) dir = down;
        if (timer > delay) { timer = 0; G1.g1(); }

        /***************************** DRAW  *********************************/
        window.clear();

        for (int i = 0; i < G1.n; i++)
            for (int j = 0; j < G1.m; j++)
            {
                sprite1.setPosition(i * G1.size, j * G1.size);  window.draw(sprite1);
            }

        for (int i = 0; i < num; i++)
        {
            sprite2.setPosition(G1.s1[i].x * G1.size, G1.s1[i].y * G1.size);  window.draw(sprite2);
        }

        sprite3.setPosition(G1.f1.x * G1.size, G1.f1.y * G1.size);  window.draw(sprite3);

        window.display();
    }

    return 0;
 
}
void Game:: g1()
{
    for (int i = num; i > 0; i--)
    {
        s1[i].x = s1[i - 1].x; s1[i].y = s1[i - 1].y;
    }
    switch (dir)
    {
    case top:s1[0].y--; break;
    case down:s1[0].y++; break;
    case right:s1[0].x++; break;
    case lift:s1[0].x--; break;
    }
    if (s1[0].x == f1.x && s1[0].y == f1.y)
    {
        num++; f1.x = rand() % n; f1.y = rand() % m; v+=10;
    }
    if (s1[0].x > n) s1[0].x = 0;  if (s1[0].x < 0) s1[0].x = n;
    if (s1[0].y > m) s1[0].y = 0;  if (s1[0].y < 0) s1[0].y = m;
    for (int i = 1; i < num; i++)
    {
        if (s1[0].x == s1[i].x && s1[0].y == s1[i].y)
        {
            num = i;
            RenderWindow L(VideoMode(579, 506), "GAME OVER");
            Texture x;
            Sprite y;
            Music music;
            music.openFromFile("mixkit-arcade-game-over-3068.wav");
            x.loadFromFile("base.png");
            y.setTexture(x);
            window.isOpen();
            L.clear();
            while (L.isOpen())
            {

                Event o;
                window.close();
                while (L.pollEvent(o))
                {
                    switch (o.type){case Event::Closed:L.close();}
                    m1.pause(); window.close(); music.play();music.setVolume(100); music.setMinDistance(0.05); L.draw(y); L.display();
                }
            }
        }
    }
}