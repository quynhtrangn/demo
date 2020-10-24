#include "SFML/Graphics.hpp"
#include<iostream>
#include <vector>
#include <math.h>
#include<string>
using namespace std;
using namespace sf;
bool isOutside(CircleShape &tmp){
    if(tmp.getPosition().y<0||tmp.getPosition().y>800||tmp.getPosition().x>800||tmp.getPosition().x<0){
        return 1;
    }
    return 0;
}
bool isCollision(int x1, int y1, int r1, int x2, int y2, int r2){
    if(abs(x1-x2)<r1+r2&&abs(y1-y2)<(r1+r2)) return 1;
    return 0;
}
string doiDiem(int diem){
    string tmp="";
    while(diem){ //1234
        tmp=(char)((diem%10)+'0')+tmp;
        diem/=10;
    }
    return tmp;
}
int main(){

    RenderWindow window(VideoMode(800,800),"Destroy Corona Virus ");
    window.setFramerateLimit(60);
    RectangleShape player1;
    player1.setSize(Vector2f(50, 50));
    player1.setOrigin(Vector2f(25,25));
    player1.setPosition(Vector2f(400,700));
    player1.setFillColor(Color::Yellow);
    vector <CircleShape> bullet;
    int diem=0;
    int firerate=10;
    // ke thu
    vector<RectangleShape> enemy;
    vector<Sprite> spriteenemy;
    Texture imenemy;
    imenemy.loadFromFile("../Picture4.png");
    int enemyrate= 1.5*60;


    Texture imbackground;
    imbackground.loadFromFile("../Picture3.png");
    Sprite backround;
    backround.setTexture(imbackground);

    Font font;
    font.loadFromFile("../arial.ttf");
    Text text;
    text.setFont(font);
    text.setCharacterSize(30);
    text.setColor(Color::Yellow);
    text.setString("Hello World!!");
    text.setPosition(Vector2f(20,20));
    text.setStyle(Text::Bold);
    while(window.isOpen()){
        Event event;

        while (window.pollEvent(event)){
            switch(event.type){
                case Event::Closed:
                    window.close();
                    break;
                case Event::Resized:
                    std::cout<<"new width: "<<event.size.width<<"new height: "<<event.size.height<<std::endl;
                    break;
            }
        }
            text.setString(doiDiem(diem));
            player1.setPosition(Vector2f(Mouse::getPosition(window).x, 700));
            // kiem tra cua player
            if(Mouse::getPosition(window).x<0) {
                player1.setPosition(0,700);
            }
            if(Mouse::getPosition(window).x>800) {
                player1.setPosition(800,700);
            }
            // tao ke thu
            enemyrate--;
            if(enemyrate==0){
                enemyrate=1.5*60;
                RectangleShape tmp;
                int vtri=rand()%(301)+20;
                for(int i=0;i<5;i++){


                    tmp.setSize(Vector2f(40,40));
                    tmp.setFillColor(Color::Red);
                    tmp.setOrigin(Vector2f(20.0f,20.0f));
                    tmp.setPosition(Vector2f(vtri+(i*110),-20));
                    enemy.push_back(tmp);
                }

            }

            //ke thu bay
            for(int i=0;i<enemy.size();i++){
                enemy[i].move(0,5);
                enemy[i].setRotation(enemy[i].getRotation()-10);

            }
            // tao dan
            firerate--;
            if(firerate==0){
                firerate=10;
                CircleShape tmp;
                tmp.setRadius(15.0f);
                tmp.setOrigin(Vector2f(15.0f,15.0f));
                tmp.setPosition(player1.getPosition());
                bullet.push_back(tmp);
            }
            // dan bay
            for(int i=0;i<bullet.size();i++){
                bullet[i].move(10*0.886f,-10*0.5f);
               //move(0.0f,-10.0f);move(10*0.886f,-10*0.5f);

            }
            // pha huy dan
            for(int i=0;i<bullet.size();i++) {
                if (isOutside(bullet[i]) == 1) {
                    bullet.erase(bullet.begin() + i);
                }
            }
            window.clear();
            // kiem tra va cham
            for(int i=0;i<enemy.size();i++){
                for(int j=0;j<bullet.size();j++){
                    if(isCollision(enemy[i].getPosition().x,enemy[i].getPosition().y,20,bullet[j].getPosition().x,bullet[j].getPosition().y,15)){
                        enemy.erase(enemy.begin()+i);
                        bullet.erase(bullet.begin()+j);
                        diem++;
                    }
                }
            }

            // draw enemy
            window.draw(backround);
            for(int i=0;i<enemy.size();i++){
                window.draw(enemy[i]);
            }
           // window.draw(bullet);

            for(int i=0;i<bullet.size();i++){
                window.draw(bullet[i]);
            }

            window.draw(player1);

            window.draw(text);

            window.display();
    }
    return 0;
}