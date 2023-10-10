# First year project at ISIMA (engineering school)

Technologies: C, SDL2

Made by Antonin Devidal, Ivan Le Teuff, Thomas Quentel

This 2-week long project can be divided in multiple little projects;
 - SDL2 hands on (2 days)
 - Conway's game of life (1 day)
 - Implementing Markov's chains (2 days)
 - Create an automatic game with Q-Learning algorithm (5 days)







## SDL2 hands on

During those 3 days, the goal was to create small samples to understand how SDL2 works:
 - Animation with windows (1 day)
 - Animating lines (1 day)
 - Moving a sprite


Individual code for those samples:
- [Antonin Devidal](/Exos/Antonin)<br/>
- [Thomas Quentel](/Exos/Thomas)<br/>
- [Ivan Le Teuff](/Exos/Ivan)<br/>

[The result can be seen here](https://perso.isima.fr/~andevidal/archive/projet-zz1-site-web/XFenetre.html)

## Conway's game of life

During 2 days, we implemented a version of Conway's Game of life. 

### Controls
 - You can accelerate time with the left and right arrows.
 - Space pauses time.
 - Click 'M' to changes from limited to O-ring mode
 - Left click to draw on the screen.
 - Save current state with 'S' and load last saved state with 'C'
 - By changing data.h, you can modify the rules 


[The result can be seen here](https://perso.isima.fr/~andevidal/archive/projet-zz1-site-web/JeuDeLaVie.html)

## Implementing Markov's chains

[CODE](/JeuPremiereSemaine)

To implement Markov's chains, we decided to create a little space shooter were you need to defend your spaceship by destroying UFOs. You control the ship with UP and DOWN arrows and shoot with the left click.
We used markovs chains to define the UFOs behaviour. In fact, Markovs chains help to define the angle of the UFO.
We used a 5 by 5 matrix where we define all possible angle we can add to the existing one.
|    | -20  | -10  | 0  | 10 | 20 | 
| --- | ---  |--- | ---| --- | --- |
| -20 | 0.3| 0.05| 0.2| 0.25| 0.2 |
| -10 | 0.3| 0.1| 0.2| 0.3| 0.1  |
|   0 | 0.05| 0.15| 0.6| 0.15| 0.05 |
|  10 | 0.1 | 0.3| 0.2| 0.1| 0.3 |
|  20 | 0.2| 0.25| 0.2| 0.05| 0.3 |

Here, the left column represents the last state and then, randomly, we choose a new state with weights for each value. Here, if the last state of the UFO was -20°, it has a lot of chance to do another -20° (to encourage full loop) or to go back to a straight trajectory (10° or 20 °).
We also apply a constant speed to the UFOs to make them go to the left of the screen. Unless, they will almost never go normally to the left of the screen.


[The result can be seen here](https://perso.isima.fr/~andevidal/archive/projet-zz1-site-web/ChefOeuvre.html)

## Implementing Q-Learning

[CODE](/ProjetFinal)

The goal was to implement a game that plays itself using Q-Learning. So we decided to create a basic football game.

First, we implemented the base game with players, the game loop, and the physics for the ball.
While doing that, we also started to think about the implmentation of Q-Learning.

In the game, the computer choose between 9 options each frame:
| States |
| ------ |
|  Up |
| Down|
| Left|
| Right|
| UpLeft|
| UpRight|
| DownLeft|
| DownRight|
| Shoot|

The most important/difficult part in this project was the reinforcment. In fact, it was the longest because of debugging. 
But in the end, how it works:
- The computer trains in front of another computer in a game (with a set number of turn (the more turn there are, the more time it takes for the computer to train ).
- They will act randomly at the begining and we reward the computer if the "play" was good ( if the computer scores we reward better than if it just shoot the ball in the direction of the goal)
- Accumulating those rewards, we create a more and more efficient Q-Table (table were the computer choose its next move)
- After the training, we can use the computer with the table we just saved.

The Q-Table looks like this:

|State/ Action|  Up | Down |Left| Right| UpLeft| UpRight| DownLeft| DownRight| Shoot|
| -| -| -| -| -| -| -| -| -| -
|  Up1 | 0|0|0|0|0|0|0|0|0|
| Down1|0|0|0|0|0|0|0|0|0|
| Left1|0|0|0|0|0|0|0|0|0|
| Right1|0|0|0|0|0|0|0|0|0|
| UpLeft1|0|0|0|0|0|0|0|0|0|
| UpRight1|0|0|0|0|0|0|0|0|0|
| DownLeft1|0|0|0|0|0|0|0|0|0|
| DownRight1|0|0|0|0|0|0|0|0|0|
|  Up2 |0|0|0|0|0|0|0|0|0|
|  Up3 |0|0|0|0|0|0|0|0|0|
| Down2|0|0|0|0|0|0|0|0|0|
| Down3|0|0|0|0|0|0|0|0|0|
| Left2|0|0|0|0|0|0|0|0|0|
| Left3|0|0|0|0|0|0|0|0|0|
| Right2|0|0|0|0|0|0|0|0|0|
| Right3|0|0|0|0|0|0|0|0|0|
| UpLeft2|0|0|0|0|0|0|0|0|0|
| UpLeft3|0|0|0|0|0|0|0|0|0|
| UpRight2|0|0|0|0|0|0|0|0|0|
| UpRight3|0|0|0|0|0|0|0|0|0|
| DownLeft2|0|0|0|0|0|0|0|0|0|
| DownLeft3|0|0|0|0|0|0|0|0|0|
| DownRight2|0|0|0|0|0|0|0|0|0|
| DownRight3|0|0|0|0|0|0|0|0|0|

The column represents where the computer is from the ball perspective ( the number represents how far it is ) and the row represents the probability  of the next move.
This is a blank Q-table that will be filled during reinforcement. But, to help the computer's training, we can fill the matrix beforehand to help it chose some options and "decide" what type of behaviour the computer will have. Negative values will mean that the move is not interesting and a bigger value will mean a better solution.

From that, we can enjoy looking at our computer playing football. Of course, the behaviour is a bit weird, and sometimes, the computers will block themselves but it works! They will try to score and score !
From the start, we trained  in 1v1 but we can change that and do 2v2 or even 4v4 (the training will be longer). 


[The result can be seen here](https://perso.isima.fr/~andevidal/archive/projet-zz1-site-web/ProjetFinal.html)






