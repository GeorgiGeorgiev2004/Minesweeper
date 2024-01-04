# Minesweeper

<p>A minesweeper project for my Introduction to programing course in FMI.</p>
<p>
<strong>The project follows the most basic ruleset of the game :</strong> </br>
Mark all mines or discover all non-mined tiles and win. </br>
Hit a mine and get sent to the starting menu again.
</p>

## How to operate the program? 

On entry you will be prompted to choose a size for the board and the amount of mines.

![starting_screen](https://github.com/GeorgiGeorgiev2004/Minesweeper/blob/main/Images/starting_screen.png)

When the board is created the game begins!

![board_created](https://github.com/GeorgiGeorgiev2004/Minesweeper/blob/main/Images/board_created.png)

#### The following commands are available to you.

*They all have a similar structure -> Command (coordinate x)(coordinate y)*

><ol>
>	<li> Open : <strong>opens the tile that the coordinates are reffering to.</strong> </li>
>	<li> Mark : <strong>marks the tile that the coordinates are reffering to , blocking it from being opened.</strong> </li>
>	<li> Unmark : <strong>unmarks the tile that the coordinates are reffering to , allowing it to be opened.</strong> </li>
>	<li> end : <strong>closes the program with no clear winner or loser.</strong> </li>
</ol>

>>#### When a guess is made the '.' sign replaces all tiles that are connected to your guess </br>but not connected to any mines and are not numbers.
>![discover_field](https://github.com/GeorgiGeorgiev2004/Minesweeper/blob/main/Images/first_guess.png)

>>#### When a mine is hit the '*' sign replaces all tiles that were mines.

>![mine_hit](https://github.com/GeorgiGeorgiev2004/Minesweeper/blob/main/Images/hit_mine.png)

>>#### If you want to see the matrix as it's generated initially just remove the "//" where the arrow points.
>![cheat_off](https://github.com/GeorgiGeorgiev2004/Minesweeper/blob/main/Images/cheat_off.png)