#include <simplecpp>
#include "bubble.h"

class Bullet{
private:
    Rectangle rect; // the rectangle representing the bullet
    double vy; // velocity in y direction
                // Also assuming bullet velocity is quiet high. It outnumbers the effect of gravity.

public:
    Bullet(double center_x, double center_y, double width=10, double height=10, double vy_=200, Color color=COLOR(255, 0, 0)){
        // Bullet constructor 
        rect = Rectangle(center_x, center_y, width, height);
        rect.setColor(color);
        rect.setFill(true);
        vy = vy_;
    }

    bool nextStep(double t){
        // move the bullet
        double new_y = rect.getY() - vy*t;
        if(new_y < (0-rect.getHeight()/2.0))   // Completely out of canvas, so delete it.        
            return false;       
        rect.moveTo(rect.getX(), new_y); //Within the canvas, so move it normally.
        return true;
    }
    
    bool collision_check(double Bx,double By,double R){    
        double R1x = rect.getX() - rect.getWidth()/2.0;
        double R2x = rect.getX() + rect.getWidth()/2.0;
        double R1y = rect.getY() + rect.getHeight()/2.0;
        double R2y = rect.getY() - rect.getHeight()/2.0;
        double Nx = max(R1x, min(Bx, R2x)); //Nearest point to Center of bubble in x coordinate
        double Ny = min(R1y, max(By,R2y)); // Nearest point to center of bubble in y coordinate
        return (pow(Nx-Bx,2)+pow(Ny-By,2) < R*R);// Comparing distance from center to nearest point
    }                                            // and Radius of circle.
                     
};

