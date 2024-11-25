# First year project at ISIMA (engineering school)
Made by Antonin Devidal, Ivan Le Teuff, Thomas Quentel.

This is a 2-week project during the first year of engineering school at ISIMA.

## Technologies: 
- C
- SDL2

## Requirements:
- SDL2 must be installed to run the project

**This was tested only on Debian**

## Project organization 


This 2-week long project can be divided in multiple little projects;
 - SDL2 hands on (2 days)
 - Conway's game of life (1 day)
 - Implementing Markov's chains (2 days)
 - Create an automatic game with Q-Learning algorithm (5 days)




## Q-learning project : automatic football game

We created a football pitch with physics for the ball and the players and a game loop with score tracking.

The aim of this project is to create an AI using Q-learning so the game plays itsef (Ai against AI).

![Q-learning game](Doc\projet_final_jeu_J4.gif)

### Q-learning algorithm
Before running this, we must train the AI using algorithm to reward the computer for its action if it was positive.
So we set a list of actions : Up, Down, Left, Right, UpLeft, UpRight, DownLeft, DownRight, Shoot.
And we set a list of states : Up1, Down1, Left1, Right1, UpLeft1, UpRight1, DownLeft1, DownRight1, Up2, Up3, Down2, Down3, Left2, Left3, Right2, Right3, UpLeft2, UpLeft3, UpRight2, UpRight3, DownLeft2, DownLeft3, DownRight2, DownRight3

Where 1 2 and 3 represent the distance of the player from the ball.

![States](Doc\etats.png)

We create a matrix for each with those parameters and each cell has a value representing the weight of the action of a specific state. The higher is the weight, the higher is the probability for this action to be played.

For the learning we can either start with a blank matrix or we can fill a matrix to influence the behaviour of th AI.

![Matrix](Doc\projet_final_matrice_main.png)





Here is an example for a 2v2 IA game.

![alt](Doc\projet_final_jeu_J4_4v4.gif)


## Markov chains game

This second game was a way to learn about Markov chains, a simple way to give life to enemies in games.

![alt](Doc\JeuPremiereSemaineDroit.gif)


This is a simple side scroller shooter where we must shoot the UFOs.

We used markov chains here to create the UFO beahviour. Markovs chains work by using the last movement to decide on the next one.
Here, the left column represents the last state and then, randomly, we choose a new state with weights for each value. Here, if the last state of the UFO was -20°, it has a lot of chance to do another -20° (to encourage full loop) or to go back to a straight trajectory (10° or 20 °).
We also apply a constant speed to the UFOs to make them go to the left of the screen. Unless, they will almost never go normally to the left of the screen.

|    | -20  | -10  | 0  | 10 | 20 | 
| --- | ---  |--- | ---| --- | --- |
| -20 | 0.3| 0.05| 0.2| 0.25| 0.2 |
| -10 | 0.3| 0.1| 0.2| 0.3| 0.1  |
|   0 | 0.05| 0.15| 0.6| 0.15| 0.05 |
|  10 | 0.1 | 0.3| 0.2| 0.1| 0.3 |
|  20 | 0.2| 0.25| 0.2| 0.05| 0.3 |


## Conway's game of life

During 2 days, we implemented a version of Conway's Game of life. 

### Controls
 - You can accelerate time with the left and right arrows.
 - Space pauses time.
 - Click 'M' to changes from limited to O-ring mode
 - Left click to draw on the screen.
 - Save current state with 'S' and load last saved state with 'C'
 - By changing data.h, you can modify the rules 


![Game of life](Doc\jeu_de_la_vie_3.gif)

