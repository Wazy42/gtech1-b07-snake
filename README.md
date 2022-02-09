Creating a snake using C++ (with SDL2 library)
Made for Linux environment 


```DONT MOVE THE WINDOW WHEN YOU PLAY, THE WINDOW CRASH```


# SDL2 library and G++ compiler 
 
Install SDL2 and SDL_image : (graphical library)
```bash
sudo apt install libsdl2-dev libsdl2-image-dev
```

Install G++ compiler and Make : 
```bash
sudo apt install g++ make 
```
note : the program should be able to run with other compilers.

# Launch the game & controls

### Launching 

Use Make to compile and launch the code (be sure to be in the snake folder)
```
make run
```
note: if the snake don't move at the start, please restart the game and X.org server.

note 2: if you want to quit the game, don't click the red cross (it crashes the window), press Alt+f4 instead or hit a wall

### Controls
```UP_ARROW``` -> GO UP   

```DOWN_ARROW``` -> GO DOWN 

```LEFT_ARROW``` -> GO LEFT 

```RIGHT_ARROW``` -> GO RIGHT

```P``` -> PAUSE/UNPAUSE THE GAME

# Features on the game

### Apple fruit 

The normal fruit from the basic snake game, when you eat the apple, you gain 1 body part and 10 points.

### Poop fruit

It's a fun addon who act like an apple, the poop appears on the tail if the apple keep spawning on the snake's body (solution for not fixing our shitty code).

### Jam

1 chance out of 5 to appears, he gives 3 parts of body and gives 30 points.

### Shield

1 chance out of 10 to appears, he gives 1 parts of body and gives 75 points. The shield gives one chance to hit a wall or himself, if u hit a wall, your snake continue to run and appears on the other side. You can walk through your body too. An icone is present at the bottom right if the shield is active.