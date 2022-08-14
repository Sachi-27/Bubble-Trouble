Link to Drive containing mp4 files:
https://drive.google.com/drive/folders/1_-gAXXGrDv8jtT2j8M9eymS-EEATtPj3?usp=sharing

List of Video Files in Drive:
1) Victory - Winning all three rounds.
(Disclaimer: The above video has a background song. Just added so that the 1 min video doesn't seem boring :))
2) Lost due to Health - Lost because 5 Lives ended
3) Lost due to Time - Lost because timer reached 60 
4) Next Level Without Playing - Command 'n' takes you to next level with no score gained.
5) Hack - Command 'hack' will end the game without playing.

Features added/modified to bubble.h:    
1) Game Dimension Variables were included here and all other Variables will be defined in terms of them.     
2) The member function nextStep has been successfully modified:
a) Incorporated the parabolic motion of bubbles, using kinematics.
b) Bouncing of bubbles at ground/ceiling assuming elastic collision.
    
Features added/modified to bullet.h, which #includes "bubble.h":
1) Added a member function bool collision_check, which checks collision between bullet and bubble, using a geometrical logic. If it returns true, then both the bubble and the bullet are erased.
    
Features added/modified to shooter.h, which #includes "bullet.h":
Added member functions:
1) bool collision_check: checks collision betwee bubble and shooter, using geometrical logics. If it returns true, then the Shooter loses a life.
2) void change_color(arg): changes the color of shooter.
3) bool is_it_red(): checks whether the shooter is red in colour(i.e., was hit by a bubble)

Created a new header file named simulation.h which #includes "shooter.h":
1) This header file has no new Class defined. This header file is just to make our main file neat and less confusing, some of the major functions like creation and moving of bubbles and bullets are dealt here.
2) The vector<Bubble> create_bubbles(arg) takes in Level as argument and accordingly creates the bubbles of different sizes and colours.
3) The function move_bullets(args) takes in vectors of bullets and Bubbles as arguments and moves the bullet in each iteration if no collision. If it collides a bubble, then the bullet is destroyed and the bubble either gets destroyed or breaks down to new smaller bubbles. 

Features added/modified to main.cpp which #includes "simulation.h":
1) bool shooter_died: checks if the shooter died.
2) Healing_Mode and Normal_Mode : They change color of shooter to red and green respectively
3) Intro Message at beginning of each round and an ending message at completion of game with Final Score will be displayed.
4) Added a Time counter which will act as a timer, 60 secs will be provided per round. Exceeding this time limit will end the game.
5) Added a Health counter which gives 5 lives througout the game, When health bar dies, the game ends.
6) Added a score counter which displays the score you gain on destroying bubbles.
7) Added a level counter which diplays the current round number.
8) Hacks added! - type "hack" and you will end all three rounds without any score! Type n to skip the level, and l to giveup.

