# Robot-Turtles
Robot Turtles takes place on a board of 8x8 squares and can be played by between 1 and 4 players.\

## Board preparation
Before starting the game, the following elements must be placed on the board:\
• One turtle per player (from 1 to 4).\
• As many jewels as there are players. The goal of the game is to be the first to get one of these jewels.\
• Between 0 and 20 stone walls. These walls are fixed and prevent the turtles from advancing.\
• Between 0 and 12 ice blocks. These blocks also prevent the turtles from advancing but they can melt if you use a laser gun.
• Between 0 and 8 boxes. The boxes can be pushed in the direction of movement of the turtle as long as there is a free square just behind in that direction to put it.
By pushing the box, both the box and the turtle advance one square.\
The initial board configurations will always be loaded from file, and will guarantee that all players can get a jewel.\

## The deck of cards
To reach the jewel, the turtle has cards of various types available:\
• "Advance" card: allows the turtle to advance one square in the direction in which it is looking if such movement is possible.
The turtle cannot leave the board, nor go through a wall, nor occupy the place that is already occupied by another turtle,
nor push a box that does not have a free square behind it, so in those cases the card will have no effect.
• “Turn right” card: allows the turtle to turn clockwise while staying in the same square.\
• “Turn left” card: allows the turtle to turn counterclockwise while staying in the same box.\
• “Laser Pistol” card: the pistol fires in the direction the turtle is facing and hits the first thing it reaches in that direction.\
  o If it is a wall of ice, it melts.\
  o In any other case, nothing happens.\
Each player has a group of cards called "hand" with which they can play and another group of cards called "deck" from which they can take more cards to add to their hand.\
Each player's starting deck consists of 38 cards:\
• 18 "Advance" cards\
• 8 “Turn Right” cards\
• 8 “Turn Left” cards\
• 4 “Laser Pistol” cards\
and in it the cards are randomly shuffled.\
The player draws three cards from the top of his deck to make the starting hand.

 ## The game
Players are numbered from 1 to the number of players, and in each round they play in increasing order of number.\
When a player has a turn, he can take one of the following actions:\
• Draw a card from the top of your deck and add it to your hand.\
• Form a sequence with a subset of the cards in the hand and execute that sequence according to the rules explained above. The used cards will return
to the bottom of your deck (in any order).\
The player who first places his turtle on a jewel is the winner.\
In case you achieved while a sequence is running, the sequence will stop.\
We are going to implement this game by also recording the players' scores in a Scores.txt file, which will be loaded when the application starts running and will be saved upon completion.
The names of the players are stored there along with their score.\
Every time a player collects a jewel they get a score that matches the initial number of players.
Thus, for example, if four players play, the one who wins gets 4 points; if they play two, the winner gets 2.
