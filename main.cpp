#include <simplecpp>
#include "simulation.h"

bool shooter_died( Shooter &Sachi, vector<Bubble> &bubbles){
    //Checks whether Bubbles touched Sachi or not. 
    //Only valid when it's not Healing.
    if (!Sachi.am_i_red()){
        for(unsigned int j=0; j<bubbles.size(); j++){
            if(Sachi.collision_check(bubbles[j].get_center_x(),bubbles[j].get_center_y(),bubbles[j].get_radius()))
                return true;
        }
    }
    return false;
}

void Healing_Mode(Shooter &Sachi){
    Sachi.change_color(COLOR(255,0,0)); //changes colour of shooter to red 
}

void Normal_Mode(Shooter &Sachi){
    Sachi.change_color(COLOR(0,255,0)); // changes colour of shooter back to green
}

int main(){          
    int Level = 1; // stores Level of round
    int score = 0; // stores current score
    int hack = 0;  //stores hackability
    initCanvas("Bubble Trouble", WINDOW_X, WINDOW_Y);
    
    Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
    b1.setColor(COLOR(0, 0, 255));
    
    string msg_cmd("Cmd: _"); //Command Counter
    Text charPressed(LEFT_MARGIN, BOTTOM_MARGIN, msg_cmd);
    
    string msg_score("Score:00"); //Score counter
    Text calcscore(RIGHT_MARGIN, BOTTOM_MARGIN, msg_score);
    
    string msg_time("Time:00/60"); //Time counter
    Text timer(LEFT_MARGIN, TOP_MARGIN, msg_time);
    
    string msg_health("Lives:5/5"); //Health counter
    Text health(RIGHT_MARGIN,TOP_MARGIN, msg_health);   
    
    string msg_level("Level:1/3"); //Level counter    
    Text level((LEFT_MARGIN+RIGHT_MARGIN)/2, BOTTOM_MARGIN, msg_level); 
    
    // Intialize the shooter
    Shooter Sachi(SHOOTER_START_X, SHOOTER_START_Y, SHOOTER_VX);
        
    // Main game loop
    do{  
    
    // Display Intro Message before beginning the round
    if (Level==1){
        Text level11(WINDOW_X/2,WINDOW_Y/2-60,"Welcome to Bubble trouble");
        Text level12(WINDOW_X/2,WINDOW_Y/2-30, "Level-1");
        Text level13(WINDOW_X/2,WINDOW_Y/2, "Movement Keys: A = Left, D = Right");
        Text level14(WINDOW_X/2,WINDOW_Y/2+30, "Shoot Bullets: W");
        wait(2);
    }
    else if(Level==2){
        Text level21(WINDOW_X/2,WINDOW_Y/2-30,"Cool! You passed the basic level!");
        Text level22(WINDOW_X/2,WINDOW_Y/2,"Get Your fingers ready for:");
        Text level23(WINDOW_X/2,WINDOW_Y/2+30,"Level-2");
        wait(2);
    }
    else if (Level==3){
        Text level31(WINDOW_X/2,WINDOW_Y/2-30,"Excellent!");
        Text level32(WINDOW_X/2,WINDOW_Y/2,"The Ultimate Trouble Awaits");
        Text level33(WINDOW_X/2,WINDOW_Y/2+30,"Level-3");
        wait(2);
    }      
       
    // Initialize the bubbles
    vector<Bubble> bubbles = create_bubbles(Level);
    
    // Initialize the bullets (empty)
    vector<Bullet> bullets;

    XEvent event;
   
    bool Win = true;  // variable stores end status of game
    double  peon = 0, heal_peon = 0;  //work of peons is to count time.
    int time=0;
   
    // Round loop
    while (true){
        bool pendingEvent = checkEvent(event);
        if (pendingEvent){   
            // Get the key pressed
            char c = charFromEvent(event);
            msg_cmd[msg_cmd.length() - 1] = c;
            charPressed.setMessage(msg_cmd);
            
            // Update the shooter
            if(c == 'a' and hack!=1){
                Sachi.move(STEP_TIME, true);
                hack=0;
            }
            else if(c == 'd'){
                Sachi.move(STEP_TIME, false);
                hack=0;
            }
            else if(c == 'w'){
                bullets.push_back(Sachi.shoot()); //append a new Bullet to the vector
                hack=0;
            }
            else if(c == 'q')
                return 0;
            else if(c == 'l'){ // Loses the games - jff 
                Win = false;
                break;
                hack=0;
            }
            else if(c == 'n'){ // Moves directly to next level
                break;
                hack=0;
            }
            else if(c == 'h' or 'a' or 'c' or 'k')
                hack++;
            else
                hack=0;
            if(hack==4) break; //hackable- you reach end of game
        }
       
        // Update the bubbles
        move_bubbles(bubbles);        
        
        // Updates the bullets 
        int gain = move_bullets(bullets,bubbles);
        
        // Updates score counter
        if(gain>0){  
            score+=gain;
            int b = (48 + score%10);
            int a = (48 + score/10);             
            msg_score[msg_score.length() - 2] = char(a);
            msg_score[msg_score.length() - 1] = char(b);            
            calcscore.setMessage(msg_score);
        }       
                            
        // If all bubbles destroyed, then end round loop                       
        if (bubbles.empty()){
           break;
        } 
        
        // Shooter is healed upon being hit by a bubble     
        bool Death = shooter_died(Sachi, bubbles);      
        if (Death){
            heal_peon = 25;
            Healing_Mode(Sachi);
            int a = int(msg_health[msg_health.length() - 3]) - 1;                        
            msg_health[msg_health.length()-3] = char(a);
            health.setMessage(msg_health); 
            if(a==48){
                Win = false;
                break;
            }
        } 
        if (heal_peon!=0) heal_peon-=1;        
        if (!Death && (heal_peon == 0)) Normal_Mode(Sachi); 
        
        // Updates time counter               
        peon = peon + 2*STEP_TIME;
        time = int(peon);  
        int b = (48 + time%10);
        int a = (48 + time/10);            
        msg_time[msg_time.length() - 5] = char(a);
        msg_time[msg_time.length() - 4] = char(b);
        timer.setMessage(msg_time); 
        if(time == 60) {
            Win = false;
            break;  
        }
        
        wait(STEP_TIME);
    }  
    
    //Erase bullets before entering into next round
    for(unsigned int i=0;i<bullets.size();)
        bullets.erase(bullets.begin()+i); 
      
    //If we won move to next round       
    if (Win) {
        Level++;
        if (hack==4){   
            msg_level[msg_level.length() - 3] = char(48+3);
            level.setMessage(msg_level);
            Text t(WINDOW_X/2,WINDOW_Y/2-15,"Congratulations! You are a Pro!");
            wait(1);
            Text t1(WINDOW_X/2,WINDOW_Y/2+30, "Hacker!!! Hello Police");
            getClick();
            break;
        }        
        else if(Level==4){ // 3rd round is the last round
            Text t(WINDOW_X/2,WINDOW_Y/2,"Congratulations! You are a Pro!");
            Text calcscore(WINDOW_X/2,WINDOW_Y/2+30, msg_score); //Final Score is displayed
            getClick();
        }
        else{
            msg_level[msg_level.length() - 3] = char(48+Level);
            level.setMessage(msg_level);
        }
            
    }  
    //If we lost, then Game over  
    else{ 
        Text t1(WINDOW_X/2,WINDOW_Y/2,"Game Over!");        
        Text calcscore(WINDOW_X/2,WINDOW_Y/2+30, msg_score); //Final Score is displayed
        getClick();
        break;
   }     
                  
   }
   while(Level<=3);     
}


