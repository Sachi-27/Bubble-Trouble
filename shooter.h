#include <simplecpp>
#include "bullet.h"

/* Shooter Vars */
const int SHOOTER_START_X = WINDOW_X/2;
const int SHOOTER_START_Y = PLAY_Y_HEIGHT - 20*WINDOW_Y/500.0;
const int SHOOTER_VX = 400;

class Shooter{
private:
    Rectangle body; // The body of the shooter
    Circle head;    // The head of the shooter
    double vx;      // The x-velocity of the shooter
    Color color;    // The color of the shooter

public:
    Shooter(double position_x, double position_y, double vx_=400, double height=30*WINDOW_Y/500.0, double width=18*WINDOW_X/500.0, double head_radius=8*sqrt(WINDOW_X*WINDOW_Y)/500.0, Color color_=COLOR(0, 255, 0)){   
        // Shooter constructor
        color = color_; //green colour

        // body (represented by a green rectangle)
        body = Rectangle(position_x, position_y, width, height);                        
        body.setColor(color);
        body.setFill(true);

        // head (represented by a green circle)
        head = Circle(position_x, position_y - height/2 - head_radius, head_radius);   
        head.setColor(color);
        head.setFill(true);
        
        // initial velocity
        vx = vx_;
    }
    
    Bullet shoot(){
        // shoot a bullet
        return Bullet(head.getX(), head.getY());
    }

    void move(double t, bool is_moving_left){   
        // moves the shooter
        double vel = vx;
        if (is_moving_left)
        {
            vel = -vel;
        }

        double new_body_x = body.getX() + vel*t;
        double new_head_x = head.getX() + vel*t;

        if (vel < 0 && new_body_x < (0 + body.getWidth()/2.0)) // stop moving along X direction at left border (if pressed A)
        {
            new_body_x = 0 + body.getWidth()/2.0;
            new_head_x = 0 + body.getWidth()/2.0;
        }
        else if (vel > 0 && new_body_x > (WINDOW_X - body.getWidth()/2.0)) // stop moving along X direction at right border (if pressed D)
        {
            new_body_x = WINDOW_X - body.getWidth()/2.0;
            new_head_x = WINDOW_X - body.getWidth()/2.0;
        }

        body.moveTo(new_body_x, body.getY());
        head.moveTo(new_head_x, head.getY());
    }
    
    bool collision_check(double Bx,double By,double R){   
        //Checks collision between Shooter and a bubble
        //First check for collision between head and bubble
        double LHS = pow(head.getX()-Bx,2)+pow(head.getY()-By,2);
        if ( LHS < pow(R + head.getRadius(),2)) return true;
        double R1x = body.getX() - body.getWidth()/2.0;
        double R2x = body.getX() + body.getWidth()/2.0;
        double R1y = body.getY() + body.getHeight()/2.0;
        double R2y = body.getY() - body.getHeight()/2.0;
        double Nx = max(R1x, min(Bx, R2x)); //Nearest point to Center of bubble along x
        double Ny = min(R1y, max(By,R2y)); // Nearest point to center of bubble along y
        return (pow(Nx-Bx,2)+pow(Ny-By,2) < R*R);
    }

    void change_color(Color col){
        //changes colour of shooter 
        body.setColor(col); body.setFill(true);
        head.setColor(col); head.setFill(true);
        color = col;
    }
    
    bool am_i_red(){   
        //checks whether the shooter is red in color
        if (color == COLOR(255,0,0)) return true;
        return false;
    }
};
