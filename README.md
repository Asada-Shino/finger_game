# Finger Game
A two-player game using ten fingers.
## Introduction
### Background
In China, each number of 0~9 can be represented with one hand(five fingers). To practice kid's addition within 10, an interesting game was born.
### Rule
In the beginning, there are **two players**, with their four hands representing the number '**1**'. Let's call them **A** and **B**, respectively.  

To start the game, **A** chooses one of **B**'s hands and add the number it represents to one of **A**'s hands. If the result is larger than 9, minus 10. For example, in the beginning all hands are representing 1. **A** chooses one of **B**'s hands then adds the number to his left hand. Then **A**'s left hand now represents '**2**'.  

To develop the game, after **A**'s round, it's **B**'s turn to do the task. **B** chooses one of **A**'s hands and adds the number to his(**B**'s) left or right hand. Then **A** takes turn. **A** and **B** repeats above operations **until**:  
1. someone's one hand represents '0'. Then we call the hand is *finished*. A *finished* hand cannot be selected by the opponent to do addition. For example, let's consider the situation where **A**'s hands represent '5' and '6' and **B**'s hands represent '5' and '8'.It's **A**'s turn and **A** chooses **B**'s '5' to do the addition with his(**A**'s) '5'. Then A gets a '0'(5+5-10=0), which means that his hand(the one representing '5' before) is now *finished*. Then when **B** chooses **A**'s hand to do addition, he has only one choice, the hand that represents '6'.  
2. someone's both hands are *finished*. Then the game ends. The one with both of his hands finished was the winner.  

It's an easy game, right?

Not exactly. I've played the game lots of times. Sometimes I win, sometimes I lose, sometimes I end up with loops. For example, when I have one hand finished and the other hand representing '7', and my opponent has one hand *finished* and the other hand representing '6', and it is my turn, we will come to an endless loop, namely 7->6->3->9->2->1->3->4->7->1>8->9->7->6. I call this situation *Tie*. And it makes me think deeper.  
Why or when will the game come to a tie? Can the first player find a way to always win the game, no matter how his opponent play? How many tie situations are there?  
To answer all my question, I create this repository to code and find. I cannot find some mathematical methods to creatively proof or draw some conclusions, so I decide to enumerate all possible situations by programming.
## Solution
### Mathematical Model
I use a tuple of five elements to express one stage. (a1, a2, b1, b2, round), where a1 and a2 represents **A**'s left and right hands' numbers respectively, b1 and b2 represents **B**'s left and right hands' numbers respectively, and round represents whose turn now. a1, a2, b1, b2 ranges from 0 to 9, and round ranges from 0 to 1 (0 means it's **A**'s turn, 1 means it's **B**'s turn).For example, the initial stage can be written as (1,1,1,1,0);
### Algorithm
I use dfs to search through all stages. When the algorithm is processing a stage, it sets all_status\[this_stage_id\] to PROCESSING. Then it goes through all stages starts with the given stage. For A's turn, if all results it finds contain 'A_WIN', then this stage is labeled as 'A_WIN'. If all results contain no 'A_WIN' but some 'TIE' or 'PROCESSING', then this stage is labeled as 'TIE', as it is the best result for A. If all results are 'B_WIN', then this stage is labeled 'B_WIN'. That's all what the algorithm does. For B's turn, it works similarly. So the algorithm repeats recursively, and finally returns the result we want.
## Result
For the starting stage (1,1,1,1,0), the game will come to a tie. It's interesting that for all possible starting stage (i, j, k, l, 0), where i,j,k,l ranges from 1~9, there are 222 stages that A has a must-win strategy. But B got no must-win strategies. All the left 6339 starting stages will come to a tie.
