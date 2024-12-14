# Craps Game with Multiple Players

## Description
This project implements a multiplayer version of the game "Craps" in C++. It supports 2 to 5 players and incorporates betting mechanics. Players take turns rolling the dice, following specific rules to determine wins, losses, and payouts.

The program ensures seamless gameplay and provides an interactive experience for players. The game never terminates, allowing continuous play or waiting for new players to join.

---

## Features
1. **Multiplayer Setup**:  
   - Supports 2 to 5 players per game.  
   - Determines the play order based on dice rolls.  
   - Resolves ties during the order determination phase.

2. **Betting Mechanics**:  
   - Players place bets before the game begins.  
   - The first roller wins or loses based on the sum of the dice:  
     - Wins with 7 or 11.  
     - Loses with 2, 3, or 12.  
   - Subsequent players win by matching the first roller's score or lose with a sum of 7.

3. **Turn-Based Gameplay**:  
   - Players take turns rolling the dice in the established order.  
   - The game continues until a player wins.  

4. **Error Handling**:  
   - Prevents invalid inputs (e.g., fewer than 2 or more than 5 players).  
   - Guides users to provide correct inputs.

5. **Game Persistence**:  
   - Continuously runs without interruptions.  
   - Automatically starts a new game after completing the current one.  
   - Reports each player's winnings and losses at the end of each game.

---

## How to Run
1. Compile the program using a C++ compiler.
2. Run the program from the command line.
3. Follow on-screen prompts to enroll players and start playing.

---

## Requirements
- The program handles:
  - Invalid inputs (e.g., incorrect number of players, non-numeric inputs).
  - Continuous gameplay without crashes.
  - Detailed player win/loss reporting.
