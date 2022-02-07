#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

class roller
{
private:
    int roller_i,roller_j;
    int width;
    bool direction_roller ;

public:
    roller(int rol_i,int rol_j,int width)
    {
        this->direction_roller = true;
        this->roller_i=rol_i;
        this->roller_j=rol_j;
        this->width=width;
    }

    int getrol_i()
    {
        return roller_i;
    }

    int getrol_j()
    {
        return roller_j;
    }

    int draw(int i,int j)
    {
        return (i==roller_i&&((j==roller_j)||(j==roller_j+1)||(j==roller_j+2)||(j==roller_j+3)||(j==roller_j+4)));
    }

    void move_roller()
    {
        if((getch()=='d')&&((roller_j+4)<width-1))
        roller_j++;
        else if((getch()=='a')&&(roller_j>1))
        roller_j--;

        if(((roller_j+4>=width-1)||(roller_j<=1)))
            direction_roller^=1;
    }

};

class ball
{
private:
    int ball_i;
    int ball_j;
    bool flag_i;
    bool flag_j;

    int length;
    int width;
public:
    ball(int BallI,int BallJ, int length, int width)
    {
        this->ball_i=BallI;
        this->ball_j=BallJ;
        this->flag_i=true;
        this->flag_j=true;
        this->length = length;
        this->width = width;
    }
    int getBALLi(){return ball_i;}
    int getBALLj(){return ball_j;}

    int draw_ball(int i,int j)
    {
        return (i==ball_i)&&(j==ball_j);
    }

    void move_ball()
    {
        (flag_i==true)?ball_i++:ball_i--;
        (flag_j==true)?ball_j++:ball_j--;

       // if(((this->ball_i==(reflect.getrol_i()-1))&&((ball_j==(reflect.getrol_j()))||(ball_j==(reflect.getrol_j()+1))||(ball_j==(reflect.getrol_j()+2))||(ball_j==(reflect.getrol_j()+3))||(ball_j==(reflect.getrol_j()+4)) ) )){
          //  flag_i^=1;
       // }

        if((this->ball_i<=1)||(this->ball_i>=length-1))
        {
            flag_i^=1;
        }

        else if ((this->ball_j<=1)||(this->ball_j>=width-1))
        {
            flag_j^=1;
        }

    }
};

class mapa
{
private:
    //drawing borders
    int width, length;
public:
    mapa(int l, int w)
    {
        this->length = l;
        this->width = w;
    }

    //getters length,width
    int getLength(){return length;}
    int getWidth(){return width;}

    //method drawing border
    int draw_border(int i,int j)
    {
        return j==0||j==width||i==0||i==length;
    }

    void draw(ball ball_inst,roller rol_inst){
        for (int i=0;i<=this->getLength();i++)
        {
            for(int j=0;j<=this->getWidth();j++)
            {
                if(this->draw_border(i,j)||  ball_inst.draw_ball(i,j)||rol_inst.draw(i,j))
                    cout<<"*";
                else
                    cout<<" ";
            }
            cout<<endl;
        }

    }

    void speed(int speed_val){
        Sleep(speed_val);
        system("cls");
    }
};

int main()
{
    mapa border(20,40);
    ball astrisk(10,15,20,40);
    roller rol(15,10,40);


    while(1)
    {

        border.draw(astrisk,rol);

        astrisk.move_ball();

        rol.move_roller();

        border.speed(0.1);
    }
    return 0;
}
