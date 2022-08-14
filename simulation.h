#include <simplecpp>
#include "shooter.h" 

/* Simulation Vars */
const double STEP_TIME = 0.02;

/*String Display Vars*/
const int LEFT_MARGIN = 70;
const int RIGHT_MARGIN = WINDOW_X - 70;
const int TOP_MARGIN = 20;
const int BOTTOM_MARGIN = (WINDOW_Y+PLAY_Y_HEIGHT)/2.0;

/*Game Simulations*/
vector<Bubble> create_bubbles(int Level){
    // create initial bubbles in the game depending on Level. Bubble colors depend on their radius
    vector<Bubble> bubbles;
 
    if(Level == 1){   // 2 maroon bubbles
        bubbles.push_back(Bubble(BUBBLE_START_X, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS, -BUBBLE_DEFAULT_VX, 30, COLOR(128,0,0)));
        bubbles.push_back(Bubble(BUBBLE_START_X/2, BUBBLE_START_Y*1.4, BUBBLE_DEFAULT_RADIUS, BUBBLE_DEFAULT_VX, 20, COLOR(128,0,0)));       
    }
    
    if(Level==2){   //3 magenta bubbles        
        bubbles.push_back(Bubble(BUBBLE_START_X*0.4,BUBBLE_START_Y*1.3,2*BUBBLE_DEFAULT_RADIUS,300,50,COLOR(255,0,255)));
        bubbles.push_back(Bubble(BUBBLE_START_X*0.8,BUBBLE_START_Y*1.7,2*BUBBLE_DEFAULT_RADIUS,300,80,COLOR(255,0,255)));   
        bubbles.push_back(Bubble(BUBBLE_START_X*0.6,BUBBLE_START_Y*1.5,2*BUBBLE_DEFAULT_RADIUS,-290,60,COLOR(255,0,255)));
    }
    
    if(Level==3){    //3 red bubbles     
        bubbles.push_back(Bubble(BUBBLE_START_X*0.2,BUBBLE_START_Y*1.5,3*BUBBLE_DEFAULT_RADIUS,350,20,COLOR(255,0,0)));
        bubbles.push_back(Bubble(BUBBLE_START_X*0.7,BUBBLE_START_Y*2,3*BUBBLE_DEFAULT_RADIUS,-400,10,COLOR(255,0,0)));
        bubbles.push_back(Bubble(BUBBLE_START_X*0.5,BUBBLE_START_Y*1.7,3*BUBBLE_DEFAULT_RADIUS,-250,50,COLOR(255,0,0)));
    }   
    
    
    
   
    return bubbles;
}

void move_bubbles(vector<Bubble> &bubbles){
    // move all bubbles    
    for (unsigned int i=0; i < bubbles.size(); i++)   
        bubbles[i].nextStep(STEP_TIME);    
}

int move_bullets(vector<Bullet> &bullets, vector<Bubble> &bubbles){
    // move all bullets 
    int gain = 0; //local variable to store points gained in this round
    for(unsigned int i=0; i<bullets.size(); i++){
        if(!bullets[i].nextStep(STEP_TIME))
            bullets.erase(bullets.begin()+i); //erases the bullet as it moved out of screen
        
        for(unsigned int j=0; j<bubbles.size(); j++){
            //accounting for collision
            if(bullets[i].collision_check(bubbles[j].get_center_x(),bubbles[j].get_center_y(),bubbles[j].get_radius())){                               
                bullets.erase(bullets.begin()+i);
                      
                int new_radius = bubbles[j].get_radius() - BUBBLE_DEFAULT_RADIUS;
                if(new_radius>0){
                    bubbles.push_back(Bubble(bubbles[j].get_center_x(),bubbles[j].get_center_y(),new_radius,-300,0,bubbles[j].get_color()));
                    bubbles.push_back(Bubble(bubbles[j].get_center_x(),bubbles[j].get_center_y(),new_radius,300,0,bubbles[j].get_color()));
                    bubbles.erase(bubbles.begin()+j);
                    gain+=1; //1 point for each bubble destroyed
                }  
                else{
                    bubbles.erase(bubbles.begin()+j);
                    gain+=1; //1 point for each bubble destroyed
                }
            }
        }
    }
    return gain; //gained points in this iteration is returned.
}
