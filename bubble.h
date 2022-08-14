#include <simplecpp>

/*Game Window Dimensions*/
const int WINDOW_X = 500;
const int WINDOW_Y = 500;
const int PLAY_Y_HEIGHT = WINDOW_Y*0.9; 

/*Bubble Vars*/
const int BUBBLE_START_X = WINDOW_X/2;
const int BUBBLE_START_Y = WINDOW_Y/10; 
const int BUBBLE_DEFAULT_RADIUS = 10*sqrt(WINDOW_X*WINDOW_Y)/500.0;
const int BUBBLE_DEFAULT_VX = 250;
const int BUBBLE_DEFAULT_VY = 10;


class Bubble{
private:
    Circle circle;  // the circle representing the bubble
    double vx, vy;  // velocity in x and y direction
    Color color;    // color of the bubble

public:
    Bubble(double cx, double cy, double r, double vx_=BUBBLE_DEFAULT_VX, double vy_=BUBBLE_DEFAULT_VY, Color color_=COLOR(0, 0, 255)){
            // Bubble constructor
            color = color_;
            circle = Circle(cx, cy, r);
            circle.setColor(color);
            circle.setFill(true);

            vx = vx_;
            vy = vy_;
        }
        
    double get_radius(){
        // return the radius of the bubble
        return circle.getRadius();
    }

    double get_center_x(){
        // return the x coordinate of the center of the bubble
        return circle.getX();
    }

    double get_center_y(){
        // return the y coordinate of the center of the bubble
        return circle.getY();
    }
    
    Color get_color(){
        // return the color of the bubble
        return color;
    }
    
    void nextStep(double t){
        // move the bubble
        double new_x = circle.getX() + vx*t; 
        double new_y = circle.getY() + vy*t + 5*t*t; //establishes parabolic movement
        
        if ((vx < 0 && new_x < circle.getRadius()) // bounce along X direction at left border
            ||
            (vx > 0 && new_x > (WINDOW_X - circle.getRadius()))) // bounce along X direction at right border
        {
            
            vx = -vx;          //Hence change vx direction
            new_x = circle.getX() + vx*t;    // Hence change new position along x
            
        }
        if ((vy > 0 && new_y > (PLAY_Y_HEIGHT - circle.getRadius())) //bounce along Y direxn at bottom.
            ||
            (vy < 0 && new_y < (0 + circle.getRadius())))//bounce along Y direxn at top of window
        {
        
            vy = -vy;                             //Hence change vy direction (assuming elastic collsion)
            new_y = circle.getY() + vy*t + 5*t*t;    //Hence change new position along y
            
        }
        
        circle.moveTo(new_x, new_y);
        vy = vy + 5*t;    //Finally updating vy for next round.
        
    }
   
};


