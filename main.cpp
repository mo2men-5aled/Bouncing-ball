#include <iostream>
#include <windows.h>
#include <conio.h>

//directions right and left
#define Key_left 77
#define Key_right 75

using namespace std;

class ball;

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

    //get roller i value
    int getrol_i()
    {
        return roller_i;
    }

    //get roller j value
    int getrol_j()
    {
        return roller_j;
    }
    //Width
    int getwidth()
    {
        return width;
    }

    //return roller location on the map
    int draw(int i,int j)
    {
        return (i==roller_i&&((j==roller_j)||(j==roller_j+1)||(j==roller_j+2)||(j==roller_j+3)||(j==roller_j+4)));
    }

    //roller movement by "d" for right and  "a" for left
    void move_roller()
    {
        //check if any key pressed
        if (kbhit())
        {
            switch (getch())
            {
            case Key_left:
                roller_j++;
                break;
            case Key_right:
                roller_j--;
                break;
            }
            //if((getch()=='d')&&((roller_j+4)<width-1))
            //roller_j++;
            //else if((getch()=='a')&&(roller_j>1))
           //roller_j--;
        }
    }
};




class point
{
private:
    int point_i=5;
    int point_j=6;

    int score=0;
public:

    void setPoint_i(int x)
    {
        point_i=x;
    }

    void setPoint_j(int b)
    {
        point_j=b;
    }

    int getPoint_i()
    {
        return point_i;
    }

    int getPoint_j()
    {
        return point_j;
    }

    int getScore()
    {
        return score;
    }

    void remove_point(ball inst_ball);

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
    //get ball i value
    int getBALLi(){return ball_i;}

    //get ball j value
    int getBALLj(){return ball_j;}

    //return ball location
    int draw_ball(int i,int j)
    {
        return (i==ball_i)&&(j==ball_j);
    }

    //ball movement and reflection
    void move_ball(roller reflect,point inst_point)
    {
        (flag_i==true)?ball_i++:ball_i--;
        (flag_j==true)?ball_j++:ball_j--;

        if((this->ball_i<=1)||(this->ball_i>=length-1)||(((this->ball_i==(reflect.getrol_i()-1))||(this->ball_i==(reflect.getrol_i()+1)))&&((ball_j==(reflect.getrol_j()))||(ball_j==(reflect.getrol_j()+1))||(ball_j==(reflect.getrol_j()+2))||(ball_j==(reflect.getrol_j()+3))||(ball_j==(reflect.getrol_j()+4)))))
        {
            flag_i^=1;
        }

        else if ((this->ball_j<=1)||(this->ball_j>=width-1))
        {
            flag_j^=1;
        }

        else if (((flag_i==1)||(flag_i==0))&&((inst_point.getPoint_i()==getBALLi())&&(inst_point.getPoint_j()==getBALLj())))
        {
            flag_i^=1;
        }
        else if (((flag_j==1)||(flag_j==0))&&((inst_point.getPoint_i()==getBALLi())&&(inst_point.getPoint_j()==getBALLj())))
        {
            flag_j^=1;
        }

    }
};

    //check if the ball hit the node and delete it
    void point::remove_point(ball inst_ball)
    {
        if(getPoint_i()==inst_ball.getBALLi()&&getPoint_j()==inst_ball.getBALLj())
        {
            setPoint_i(0);
            setPoint_j(0);
            score++;
        }
        cout<<"Score :"<<getScore()<<endl;
    }

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

    //draw borders and roller and ball
    void draw(ball ball_inst,roller rol_inst , point point_inst)
    {
        for (int i=0;i<=this->getLength();i++)
        {
            for(int j=0;j<=this->getWidth();j++)
            {
                if(this->draw_border(i,j)||  ball_inst.draw_ball(i,j)||rol_inst.draw(i,j))
                    cout<<"*";

                else if (point_inst.getPoint_i()==i&&point_inst.getPoint_j()==j)
                {
                    cout<<"o";
                }
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
    point nodes;
    mapa border(20,40);
    ball astrisk(10,15,20,40);
    roller rol(15,10,40);


    while(1)
    {
        border.draw(astrisk,rol,nodes);

        astrisk.move_ball(rol,nodes);

        rol.move_roller();

        nodes.remove_point(astrisk);

        border.speed(0.1);
    }
    return 0;
}
