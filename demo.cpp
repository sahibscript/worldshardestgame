//Name: Sahib Chandnani		Period: 1
//Program: World's Hardest Game

/*
	This program displays a red square which must be moved
	through a maze of blue circles. At each level, the maze 
	increases in difficulty. The program is used for purely
	for entertainment.
*/

#include <iostream>
#include <sstream>
#include <cmath>
#pragma comment (lib, "winmm.lib")
#include "CMUgraphicsLib\CMUgraphics.h"
#include "CMUgraphicsLib\auxil.h"	

//======================================================================
//										Global because deaths are common to all functions
int NbrDeaths;
void WaitNClear(window &inputWindow);
void LevelOne(window &testWindow);
void LevelTwo(window &testWindow);
void LevelThree(window &testWindow);
void LevelFour(window &testWindow);
void LevelFive(window &testWindow);
void Intro(window &testWindow);
void Instruction(window &testWindow);
//======================================================================

int main()
{
	window testWindow(1200, 700, 5, 5);
//										Plays music
	PlaySound("Geeking.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
	Intro(testWindow);
}

//======================================================================
//	Function name: Intro
//	Purpose: This function allows the user to navigate either to the 
//				game itself or to the instruction menu and includes all 
//				of the level function calls.
//	Note: This is basically the root of the program
//----------------------------------------------------------------------
void Intro(window &testWindow)
{
	int iX, iY, mcX, mcY;
	clicktype ctInput;
	bool bQuit = true;
//										Changes the window title
	testWindow.ChangeTitle("World's Hardest Game");
//										Declares the background of the intro screen
	image testImage("IntroWindow.jpg", JPEG);
//										Draws the background of the intro screen
	testWindow.DrawImage(testImage, 0, -130,1200,1050);
//										Draws the Instructions and Begin options along with the surrounding boxes
	testWindow.SetPen(WHITE, 5);
	testWindow.DrawRectangle(452,572, 748,676,FRAME); 
	testWindow.SetFont(100, BOLD, BY_NAME, "Arial");
	testWindow.DrawString(278, 427, "INSTRUCTIONS");
	testWindow.DrawRectangle(272, 435, 933, 518, FRAME);
//										Calls the function so that mouse coordinates can be tracked
	testWindow.GetMouseCoord(mcX,mcY);
//										Uses the coordinates to control the colors of the boxes in the intro
	do
	{
		while(bQuit == true)
		{
			testWindow.GetMouseCoord(mcX,mcY);
		
			if(mcY >= 572 && mcY <= 676)
				if(mcX >= 452 && mcX <=748)
				{
//										Change color of rectangle			
					testWindow.SetPen(BLUE,5);
					testWindow.SetBrush(BLUE);
					testWindow.DrawRectangle(452,572, 748,676,FRAME);
				}
	
				else
				{
//										Change color of rectangle			
					testWindow.SetPen(WHITE,5);
					testWindow.SetBrush(WHITE);
					testWindow.DrawRectangle(452,572, 748,676,FRAME);
	
				}
			else
			{
//										Change color of rectangle			
				testWindow.SetPen(WHITE,5);
				testWindow.SetBrush(WHITE);
				testWindow.DrawRectangle(452,572, 748,676,FRAME);
			}
			if(mcY >= 435 && mcY <= 518)
				if(mcX >= 272 && mcX <= 933)
				{
//										Change color of rectangle			
					testWindow.SetPen(BLUE,5);
					testWindow.SetBrush(BLUE);
					testWindow.DrawRectangle(272, 435, 933, 518, FRAME);
				}
				else
				{
//										Change color of rectangle	
					testWindow.SetPen(WHITE,5);
					testWindow.SetBrush(WHITE);
					testWindow.DrawRectangle(272, 435, 933, 518, FRAME);
				}
			else
			{
				testWindow.SetPen(WHITE,5);
				testWindow.SetBrush(WHITE);
				testWindow.DrawRectangle(272, 435, 933, 518, FRAME);
			}
//										Function call to receive click coordinates
			ctInput = testWindow.GetMouseClick(iX, iY);
//										Uses click coordinates to call either instructions or the game					

			if(iX<=933 & iX>=272 & iY>=435 & iY<=518)
				Instruction(testWindow);

			else if(iX <= 748 & iX >= 452 & iY >= 572 & iY <= 676)
			{
				LevelOne(testWindow);
				LevelTwo(testWindow);
				LevelThree(testWindow);
				LevelFour(testWindow);
				LevelFive(testWindow);
			}
		}
	}while((iX <= 748 & iX >= 452 & iY >= 572 & iY <= 676)||(iX<=933 & iX>=272 & iY>=435 & iY<=518));

}

//======================================================================
//	Function name: Instructions
//	Purpose: This function contains the instructions of how to play.
//	Note: Simply prints statements then returns to Intro
//----------------------------------------------------------------------
void Instruction(window &testWindow)
{
//										The following statements simply print the instructions
	testWindow.SetBrush(WHITE);
	testWindow.SetPen(WHITE, 5);
	testWindow.DrawRectangle(0, 0, testWindow.GetWidth(), testWindow.GetHeight());
	testWindow.SetPen(BLACK, 5);
	testWindow.SetFont(69, BOLD, BY_NAME, "Arial");
	testWindow.DrawString(365, 7, "INSTRUCTIONS");
	testWindow.SetFont(40, BOLD, BY_NAME, "Arial");
	testWindow.DrawString(7, 100, "1. Use the arrow keys to manipulate the position of the Red Square");
	testWindow.DrawString(7, 200, "2. Move the Red Square through the maze while avoiding the blue balls");
	testWindow.DrawString(7, 300, "3. Each time the square makes contact with a ball a death is added");
	testWindow.DrawString(7, 400, "4. The goal is to reach the green end zone while accumulating");
	testWindow.DrawString(45,450, "as little deaths as possible");
	testWindow.DrawString(7, 550, "5. At the end, total deaths will be printed and you may replay but beware");
	testWindow.DrawString(45,600, "some levels contain hidden tricks");
	testWindow.SetFont(20, BOLD, BY_NAME, "Arial");
//										Returns to main menu if clicked
	testWindow.DrawString(400, 650, "(Click Mouse to return to Introduction Window)");
	WaitNClear(testWindow);
	Intro(testWindow);
}

//======================================================================
//	Function name: Level One
//	Purpose: This function contains the maze of the first level and is 
//				composed of all necessary shapes and variables to navigate
//				through the maze.
//	Note: This is the first of five levels.
//----------------------------------------------------------------------
void LevelOne(window &testWindow)
{
	int iX, iY, X1, Y1, X2, Y2, s, p, r, BallX, BallX2, BallY, BallY2, BallY3, BallY4;
	bool bQuit = false;
	bool Left = false;
	keytype ktInput;
	clicktype ctInput;
	char cKeyData;

 	NbrDeaths = 0; 
 	r = 17; 
 	BallX2 = 860;
 	BallX = 340;
 	BallY = 258;
 	BallY2 = 317;
	BallY3 = 376;
	BallY4 = 435;
 	s = 356;
 	p = 263;
 	X1 = Y1 = 180;
 	X2 = Y2 = 210;
 	
//										Plays music
	PlaySound("Popcorn.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
//										Turns on double buffering
    testWindow.SetBuffering(true); 
    
//										Flush out the input queues before beginning
    testWindow.FlushMouseQueue();
    testWindow.FlushKeyQueue();
//										Sets word font
	testWindow.SetFont(20, BOLD, BY_NAME, "Arial");
    
	do
    {
//										Alters pause speed   
   		Pause(.01);
//										Draws Level
   		image testImage("Level1.jpg", JPEG);
   		testWindow.DrawImage(testImage, 0, -130,1200,950);
//										draws user rectangle and necessary white boxes over moving circles  
   		testWindow.SetPen(WHITE, 0);    
   		testWindow.SetBrush(WHITE);
   		testWindow.DrawRectangle(331,453,869,240);
  
   		testWindow.SetPen(WHITE, 0);    
   		testWindow.SetBrush(WHITE);
   		testWindow.DrawRectangle(331,449,378,514);
   
  		testWindow.SetPen(BLACK, 5);    
   		testWindow.SetBrush(RED);
   		testWindow.DrawRectangle(X1,Y1,X2,Y2,FILLED,5);
     	 
     	 
     	 
//										controls ball movement 	 
   		if(Left == false)
   		{
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX+=3, BallY, r, FILLED);

    
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX2-=3, BallY2, r, FILLED);
	
	    
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX, BallY3, r, FILLED);
	
	   
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX2, BallY4, r, FILLED);
			Pause(.5);
		}
	
	
	 
		if(BallX >= 860)
		{
			Left = true;
		}
		
		if(Left == true)
		{
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX-=3, BallY, r, FILLED);

		    
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX2+=3, BallY2, r, FILLED);
			
			    
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX, BallY3, r, FILLED);

			   
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX2, BallY4, r, FILLED);
			Pause(.5);
		}
	
		if(BallX <= 340)
		{
			Left = false;
		}
		
	    testWindow.SetBuffering(true);
	    
//										Draws instructions and level number with deaths
      	testWindow.SetPen(BLACK); 
      	testWindow.DrawString(5, 5, "Level 1");
      	testWindow.DrawString(1100, 5, "Deaths:");
      	testWindow.DrawInteger(1165, 5, NbrDeaths);
      	ktInput = testWindow.GetKeyPress(cKeyData);
      	ctInput = testWindow.GetMouseClick(iX, iY);
      
  
// 										Figures out what key was pressed and moves square
        if(ktInput == ARROW) {
       		switch(cKeyData)
       		{
	            case 1:
	              testWindow.DrawString(5, 30, "The End key was pressed.");
	              break;
	            case 2:
	              testWindow.FlushKeyQueue();
	              testWindow.UpdateBuffer();
	              testWindow.SetPen(BLACK, 5);    
	     		  testWindow.SetBrush(RED);
	     		  testWindow.DrawRectangle(X1,Y1+=12,X2,Y2+=12,FILLED,1,1);
	     		  Pause(.01);
	              break;
	            case 3:
	              testWindow.DrawString(5, 30, "The Page Down key was pressed.");
	              break;
	            case 4:
	              testWindow.FlushKeyQueue();
	              testWindow.UpdateBuffer();
	              testWindow.SetPen(BLACK, 5);    
	     		  testWindow.SetBrush(RED);
	     		  testWindow.DrawRectangle(X1-=12,Y1,X2-=12,Y2,FILLED,1,1);
	     		  Pause(.01);
	              break;
	            case 5:
	              testWindow.DrawString(5, 30, "The Center Keypad key was pressed.");
	              break;
	            case 6:
	                testWindow.FlushKeyQueue();
	              testWindow.UpdateBuffer();
	              testWindow.SetPen(BLACK, 5);    
	     		  testWindow.SetBrush(RED);
	     		  testWindow.DrawRectangle(X1+=12,Y1,X2+=12,Y2,FILLED,1,1);
	     		  Pause(.01);
	              break;
	            case 7:
	              testWindow.DrawString(5, 30, "The Home key was pressed.");
	              break;
	            case 8:
	              testWindow.FlushKeyQueue();
	              testWindow.UpdateBuffer();
	              testWindow.SetPen(BLACK, 5);    
	     		  testWindow.SetBrush(RED);
	     		  testWindow.DrawRectangle(X1,Y1-=12,X2,Y2-=12,FILLED,1,1);
	     		  Pause(.01);
	              break;
	            case 9:
	              testWindow.DrawString(5, 30, "The Page Up key was pressed.");
         	}
      } 
//										returns square and adds death when sqaure hits the ball									   	     
	  if(BallX-17 <= X2 && BallX+17 >=X1)
	  		if(BallY-17 <= Y2 && BallY+17 >= Y1)
	  		{
	  			NbrDeaths++;
	  			X1 = Y1 = 180;
	  			X2 = Y2 = 210;
	  		}
  
  
	  if(BallX-17 <= X2 && BallX+17 >= X1)
	  		if(BallY3-17 <= Y2 && BallY3+17 >= Y1)
	  		{
			  	NbrDeaths++;
			 	X1 = Y1 = 180;
			  	X2 = Y2 = 210;
			}
			  
	  if(BallX2-17 <= X2 && BallX2+17 >=X1)
	  		if(BallY2-17 <= Y2 && BallY2+17 >= Y1)
			{
			  	NbrDeaths++;
			  	X1 = Y1 = 180;
			 	X2 = Y2 = 210;
			}
	  
	  
	  if(BallX2-17 <= X2 && BallX2+17 >=X1)
		  	if(BallY4-17 <= Y2 && BallY4+17 >= Y1)
		  	{
		  		NbrDeaths++;
		  		X1 = Y1 = 180;
		  		X2 = Y2 = 210;
		  	}
  
//										Maze boundaries
      if(Y1<=165)
      {
	     	Y1+=12;
	     	Y2+=12;
      }
      
      if(X1 <= 105)
      {
      		X1+=12;
      		X2+=12;
      }
      
      if(Y2 >= 525)
      {
      		Y1-=12;
     		Y2-=12;
      }
     
      if(((X2 >= 278)&&(X2 <= 812))&&((Y1 >= 169)&&(Y1 <= 225)))
      {
	     	X1 = Y1 = 180;
	 	 	X2 = Y2 = 210;
      }
     
      if(((X1 >= 278)&&(X1 <= 812))&&((Y1 >= 169)&&(Y1 <= 225)))
      {
		    X1 = Y1 = 180;
		  	X2 = Y2 = 210;
      }
     
      if(((X2 >= 278)&&(X2 <= 324))&&((Y1 >= 169)&&(Y1 <= 454)))
      {
      		X1 = Y1 = 180;
 			X2 = Y2 = 210;
      }
     
      if(((X1 >= 278)&&(X1 <= 324))&&((Y1 >= 169)&&(Y1 <= 454)))
      {
      		X1 = Y1 = 180;
     		X2 = Y2 = 210;
      }
     
      if(((X2 >= 387)&&(X2 <= 922))&&((Y2 >= 465)&&(Y2 <= 525)))
      {
      		X1 = Y1 = 180;
  			X2 = Y2 = 210;
      }
     
      if(((X1 >= 387)&&(X1 <= 922))&&((Y2 >= 465)&&(Y2 <= 525)))
      {
      		X1 = Y1 = 180;
  			X2 = Y2 = 210;
      }
     
      if(((X2 >= 877)&&(X2 <= 922))&&((Y2 >= 232)&&(Y2 <= 525)))
      {
     		X1 = Y1 = 180;
  			X2 = Y2 = 210;
      }
     
      if(((X1 >= 877)&&(X1 <= 922))&&((Y2 >= 232)&&(Y2 <= 525)))
      {
     		X1 = Y1 = 180;
  			X2 = Y2 = 210;
      }
     
//										Update the screen buffer
      testWindow.UpdateBuffer();

//										Pause for half a second
      Pause(.1);

      if(X2 >= 928)
      		bQuit = true;

   }while(bQuit != true);
    

 
//										Loop until there is a mouse click
    while(testWindow.GetMouseClick(iX, iY) == NO_CLICK)
    {
      testWindow.DrawString(testWindow.GetWidth()/2 - 100, testWindow.GetHeight() - 25, "Click mouse to continue...");
	
//										Update the screen buffer
      testWindow.UpdateBuffer();
    }



}

//======================================================================
//	Function name: Level Two
//	Purpose: This function contains the maze of the second level and is 
//				composed of all necessary shapes and variables to navigate
//				through the maze.
//	Note: This is the second of five levels.
//----------------------------------------------------------------------
void LevelTwo(window &testWindow)
{    
	int iX, iY, X1, Y1, X2, Y2, s, p, r, BallY, BallY2, BallX, BallX2, BallX3, BallX4, BallX5, BallX6, BallX7, BallX8, BallX9, BallX10, BallX11;

	bool bQuit = false;
	bool Left = false;
	keytype ktInput;
	clicktype ctInput;
	char cKeyData;
	  
	r = 17; 
	BallY2 = 527;
	BallY = 147;
	BallX = 301;
	BallX2 = 360;
	BallX3 = 419;
	BallX4 = 479;
	BallX5 = 538;
	BallX6 = 597;
	BallX7 = 656;
	BallX8 = 715;
	BallX9 = 774;
	BallX10 = 833;
	BallX11 = 892;
	 
	s = 356;
	p = 263;
	X1 = Y1 = 180;
	X2 = Y2 = 210;
	 

//										Flush out the input queues before beginning
    testWindow.FlushMouseQueue();
    testWindow.FlushKeyQueue();
//										Sets font
    testWindow.SetFont(20, BOLD, BY_NAME, "Arial");    
//										Turns on double buffering
    testWindow.SetBuffering(true);
    
     
    do
    {
//										Draws the level and necessary white sqaures over balls
    	image testImage("Level2.jpg", JPEG);
   		testWindow.DrawImage(testImage, 0, -130,1200,950);
   
  
	   	testWindow.SetPen(WHITE, 0);    
		testWindow.SetBrush(WHITE);
		testWindow.DrawRectangle(926,139,276,544);
		    
		testWindow.SetPen(BLACK, 5);    
		testWindow.SetBrush(RED);
		testWindow.DrawRectangle(X1,Y1,X2,Y2,FILLED,5);
		    
//										Ball movement 	 
		if(Left == false)
		{
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX, BallY+=13, r, FILLED);

	    
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX2, BallY2-=13, r, FILLED);
			
			    
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX3, BallY, r, FILLED);
			
		   
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX4, BallY2, r, FILLED);
			
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX5, BallY, r, FILLED);

		    
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX6, BallY2, r, FILLED);

			    
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX7, BallY, r, FILLED);
			
			   
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX8, BallY2, r, FILLED);
			
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX9, BallY, r, FILLED);

		    
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX10, BallY2, r, FILLED);
			
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX11, BallY, r, FILLED);
			Pause(.1);
		}
		
		
		 
		if(BallY >= 515)
		{
			Left = true;
		}
		
		if(Left == true)
		{
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX, BallY-=13, r, FILLED);

		    
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX2, BallY2+=13, r, FILLED);
			
			    
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX3, BallY, r, FILLED);
			
			   
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX4, BallY2, r, FILLED);


			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX5, BallY, r, FILLED);

		    
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX6, BallY2, r, FILLED);
			
			    
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX7, BallY, r, FILLED);
			
			   
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX8, BallY2, r, FILLED);
			
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX9, BallY, r, FILLED);

		    
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX10, BallY2, r, FILLED);
			
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX11, BallY, r, FILLED);
			Pause(.1);
		}
		
		if(BallY <= 159)
		{
			Left = false;
		}
		
//										Turn on double buffering
	    testWindow.SetBuffering(true);
//										Updates buffer	  
	  	testWindow.UpdateBuffer();
//										Draws instructions and other information
	    testWindow.SetPen(BLACK); 
	    testWindow.DrawString(5, 5, "Level 2");
	    testWindow.DrawString(1100, 5, "Deaths:");
	    testWindow.DrawInteger(1165, 5, NbrDeaths);
	    ktInput = testWindow.GetKeyPress(cKeyData);
	    ctInput = testWindow.GetMouseClick(iX, iY);
	      
//										Figure out what key was pressed and move square
	    if(ktInput == ARROW) 
	    {
	  		 switch(cKeyData)
	         {
	       		case 1:
	         	  testWindow.DrawString(5, 30, "The End key was pressed.");
	              break;
	            case 2:
	              testWindow.FlushKeyQueue();
	              testWindow.UpdateBuffer();
	              testWindow.SetPen(BLACK, 5);    
	     		  testWindow.SetBrush(RED);
	     		  testWindow.DrawRectangle(X1,Y1+=12,X2,Y2+=12,FILLED,1,1);
	     		  Pause(.01);
	              break;
	            case 3:
	              testWindow.DrawString(5, 30, "The Page Down key was pressed.");
	              break;
	            case 4:
	              testWindow.FlushKeyQueue();
	              testWindow.UpdateBuffer();
	              testWindow.SetPen(BLACK, 5);    
	     		  testWindow.SetBrush(RED);
	     		  testWindow.DrawRectangle(X1-=12,Y1,X2-=12,Y2,FILLED,1,1);
	     		  Pause(.01);
	              break;
	            case 5:
	              testWindow.DrawString(5, 30, "The Center Keypad key was pressed.");
	              break;
	            case 6:
	                testWindow.FlushKeyQueue();
	              testWindow.UpdateBuffer();
	              testWindow.SetPen(BLACK, 5);    
	     		  testWindow.SetBrush(RED);
	     		  testWindow.DrawRectangle(X1+=12,Y1,X2+=12,Y2,FILLED,1,1);
	     		  Pause(.01);
	              break;
	            case 7:
	              testWindow.DrawString(5, 30, "The Home key was pressed.");
	              break;
	            case 8:
	              testWindow.FlushKeyQueue();
	              testWindow.UpdateBuffer();
	              testWindow.SetPen(BLACK, 5);    
	     		  testWindow.SetBrush(RED);
	     		  testWindow.DrawRectangle(X1,Y1-=12,X2,Y2-=12,FILLED,1,1);
	     		  Pause(.01);
	              break;
	            case 9:
	              testWindow.DrawString(5, 30, "The Page Up key was pressed.");
	        }
	   }  

//										Ball reset for when the sqaure makes contact	               
	   if(BallY-17 <= Y2 && BallY+17 >= Y1)
	  	    if(BallX-17 <= X2 && BallX+17 >= X1)
	  	    {
	  	    	NbrDeaths++;
	        	X1 = Y1 = 180;
	        	X2 = Y2 = 210;
	  	    }
	  		
	   if(BallY-17 <= Y2 && BallY+17 >= Y1)
	  		if(BallX3-17 <= X2 && BallX3+17 >= X1)
	  		{
	  			NbrDeaths++;
	  			X1 = Y1 = 180;
	  			X2 = Y2 = 210;
	  		}
	  
	   if(BallY2-17 <= Y2 && BallY2+17 >= Y1)
	  		if(BallX2-17 <= X2 && BallX2+17 >= X1)
	  		{
	  			NbrDeaths++;
	  			X1 = Y1 = 180;
	  			X2 = Y2 = 210;
	 		}
	  
	   if(BallY2-17 <= Y2 && BallY2+17 >=Y1)
	  		if(BallX4-17 <= X2 && BallX4+17 >= X1)
	  		{
	  			NbrDeaths++;
	  			X1 = Y1 = 180;
	  			X2 = Y2 = 210;
	  		}
	  
	   if(BallY-17 <= Y2 && BallY+17 >= Y1)
	  		if(BallX5-17 <= X2 && BallX5+17 >= X1)
	  		{
	  			NbrDeaths++;
	  			X1 = Y1 = 180;
	  			X2 = Y2 = 210;
	  		}
	  
	   if(BallY-17 <= Y2 && BallY+17 >= Y1)
	  		if(BallX7-17 <= X2 && BallX7+17 >= X1)
	  		{
				NbrDeaths++;
				X1 = Y1 = 180;
				X2 = Y2 = 210;
	  		}
	  
	   if(BallY2-17 <= Y2 && BallY2+17 >= Y1)
	  		if(BallX6-17 <= X2 && BallX6+17 >= X1)
	  		{
			    NbrDeaths++;
			    X1 = Y1 = 180;
				X2 = Y2 = 210;
	 		}
	  
	  
	   if(BallY2-17 <= Y2 && BallY2+17 >=Y1)
	  		if(BallX8-17 <= X2 && BallX8+17 >= X1)
	  		{
				NbrDeaths++;
				X1 = Y1 = 180;
				X2 = Y2 = 210;
	  		}
	  
	   if(BallY-17 <= Y2 && BallY+17 >= Y1)
	  		if(BallX9-17 <= X2 && BallX9+17 >= X1)
	  		{
	  			NbrDeaths++;
	  			X1 = Y1 = 180;
	  			X2 = Y2 = 210;
	  		}
	  
	   if(BallY-17 <= Y2 && BallY+17 >= Y1)
	  		if(BallX11-17 <= X2 && BallX11+17 >= X1)
	  		{
	 			NbrDeaths++;
	  			X1 = Y1 = 180;
	  			X2 = Y2 = 210;
	  		}
	  
	   if(BallY2-17 <= Y2 && BallY2+17 >= Y1)
	  		if(BallX10-17 <= X2 && BallX10+17 >= X1)
	  		{
	  			NbrDeaths++;
	  			X1 = Y1 = 180;
	  			X2 = Y2 = 210;
	  		}

//										Update the screen buffer
	      testWindow.UpdateBuffer();

//										Pause for half a second
	      Pause(.1);
	      
//										Top Boundary
	   if(Y1<=130)
	   {
	      Y1+=12;
	      Y2+=12;
	   }
	      
//										Left Boundary
	   if(X1 <= 107)
	   {
	      X1+=12;
	      X2+=12;
	   }
	      
//										Bottom Boundary
	   if(Y2 >= 548)
	   {
	      Y1-=12;
	      Y2-=12;
	   }
	     
	      
	      
//										Update the screen buffer
	   testWindow.UpdateBuffer();
// 										Pause for half a second
	      Pause(1);

	 
	      
	   if(X2 >= 928)
	      bQuit = true;
	   
    }while(bQuit != true);
    

 
// 										Loop until there is a mouse click
    while(testWindow.GetMouseClick(iX, iY) == NO_CLICK)
    {  
        testWindow.DrawString(testWindow.GetWidth()/2 - 100, testWindow.GetHeight() - 25, "Click mouse to continue...");
	
//										Update the screen buffer
        testWindow.UpdateBuffer();
    }
    
}

//======================================================================
//	Function name: Level Three
//	Purpose: This function contains the maze of the third level and is 
//				composed of all necessary shapes and variables to navigate
//				through the maze.
//	Note: This is the third of five levels.
//----------------------------------------------------------------------
void LevelThree(window &testWindow)
{
    
	int iX, iY, X1, Y1, X2, Y2, s, p, r, BallY, BallY2, BallX, BallX2, BallX3, BallX4, BallX5, BallX6;

	bool bQuit = false;
	bool Left = false;
	keytype ktInput;
	clicktype ctInput;
	char cKeyData;

	r = 20; 
 	BallX = 425;
	BallX2 = 492;
	BallX3 = 559;
	BallX4 = 626;
	BallX5 = 693;
	BallX6 = 760;
	BallY = 630;
	BallY2 = 176;
	 
	s = 356;
	p = 263;
	X1 = 150;
	Y1 = 360;
	X2 = 180;
	Y2 = 390;

    
//										Flush out the input queues before beginning
    testWindow.FlushMouseQueue();
    testWindow.FlushKeyQueue();
//										Set font
    testWindow.SetFont(20, BOLD, BY_NAME, "Arial"); 
//										Turn on double buffering   
    testWindow.SetBuffering(true);
    
    
    
    do
    {
//										Draws level and necessary boxes over balls
	    Pause(.01);
	    
	    image testImage("Level3.jpg", JPEG);
	    testWindow.DrawImage(testImage, 0, -130,1200,950);
	  
	    testWindow.SetPen(WHITE, 0);    
	    testWindow.SetBrush(WHITE);
	    testWindow.DrawRectangle(331,453,869,240);
	    
	    testWindow.SetPen(BLACK, 5);    
	    testWindow.SetBrush(RED);
	    testWindow.DrawRectangle(X1,Y1,X2,Y2,FILLED,5);
     	 
     	 
     	 
//										Ball movement 	 
	    if(Left == false)
		{
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX, BallY-=10, r, FILLED);

	    
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX2, BallY, r, FILLED);
			
			    
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX3, BallY2+=10, r, FILLED);
			
			   
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX4, BallY2, r, FILLED);
			
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX5, BallY, r, FILLED);
			
			   
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX6, BallY, r, FILLED);
			Pause(.1);
	    }
		
		
		 
		if(BallY <= 176)
		{
			Left = true;
		}
		
		if(Left == true)
		{
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX, BallY+=15, r, FILLED);

	    
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX2, BallY, r, FILLED);
			
			    
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX3, BallY2-=15, r, FILLED);
			
			   
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX4, BallY2, r, FILLED);
			
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX5, BallY, r, FILLED);
			
			   
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX6, BallY, r, FILLED);
			Pause(.1);
		}
		
		if(BallY >= 630)
		{
			Left = false;
		}
//											Boundary lines drawn
		testWindow.DrawLine(393,235,804,235);
		testWindow.DrawLine(393,562,804,562);
	    
//											Turn on double buffering
	    testWindow.SetBuffering(true);
	    

// 											Draws instructions and imformation like deaths and level number
	    testWindow.SetPen(BLACK); 
	    testWindow.DrawString(5, 5, "Level 3");
	    testWindow.DrawString(1100, 5, "Deaths:");
	    testWindow.DrawInteger(1165, 5, NbrDeaths);
	    ktInput = testWindow.GetKeyPress(cKeyData);
	    ctInput = testWindow.GetMouseClick(iX, iY);
	      
	  
//											Figure out what key was pressed and move square
	    if(ktInput == ARROW) {
	            switch(cKeyData)
	            {
		            case 1:
		              testWindow.DrawString(5, 30, "The End key was pressed.");
		              break;
		            case 2:
		              testWindow.FlushKeyQueue();
		              testWindow.UpdateBuffer();
		              testWindow.SetPen(BLACK, 5);    
		     		  testWindow.SetBrush(RED);
		     		  testWindow.DrawRectangle(X1,Y1+=12,X2,Y2+=12,FILLED,1,1);
		     		  Pause(.01);
		              break;
		            case 3:
		              testWindow.DrawString(5, 30, "The Page Down key was pressed.");
		              break;
		            case 4:
		              testWindow.FlushKeyQueue();
		              testWindow.UpdateBuffer();
		              testWindow.SetPen(BLACK, 5);    
		     		  testWindow.SetBrush(RED);
		     		  testWindow.DrawRectangle(X1-=12,Y1,X2-=12,Y2,FILLED,1,1);
		     		  Pause(.01);
		              break;
		            case 5:
		              testWindow.DrawString(5, 30, "The Center Keypad key was pressed.");
		              break;
		            case 6:
		                testWindow.FlushKeyQueue();
		              testWindow.UpdateBuffer();
		              testWindow.SetPen(BLACK, 5);    
		     		  testWindow.SetBrush(RED);
		     		  testWindow.DrawRectangle(X1+=12,Y1,X2+=12,Y2,FILLED,1,1);
		     		  Pause(.01);
		              break;
		            case 7:
		              testWindow.DrawString(5, 30, "The Home key was pressed.");
		              break;
		            case 8:
		              testWindow.FlushKeyQueue();
		              testWindow.UpdateBuffer();
		              testWindow.SetPen(BLACK, 5);    
		     		  testWindow.SetBrush(RED);
		     		  testWindow.DrawRectangle(X1,Y1-=12,X2,Y2-=12,FILLED,1,1);
		     		  Pause(.01);
		              break;
		            case 9:
		              testWindow.DrawString(5, 30, "The Page Up key was pressed.");
	            }



	    } 

//										Ball reset when square makes contact          
		if(BallY-17 <= Y2 && BallY+17 >= Y1)
	  	 		if(BallX-17 <= X2 && BallX+17 >= X1)
	  			{
	  				NbrDeaths++;
	  				X1 = 150;
					Y1 = 360;
	 				X2 = 180;
	 				Y2 = 390;
	  			}
	  
	  	if(BallY-17 <= Y2 && BallY+17 >= Y1)
	  			if(BallX2-17 <= X2 && BallX2+17 >= X1)
	  			{
	  				NbrDeaths++;
	   				X1 = 150;
	 				Y1 = 360;
	 				X2 = 180;
	 				Y2 = 390;
	  			}
	  
	  	if(BallY2-17 <= Y2 && BallY2+17 >= Y1)
	  			if(BallX3-17 <= X2 && BallX3+17 >= X1)
	  			{
	  				NbrDeaths++;
	   				X1 = 150;
	 				Y1 = 360;
	 				X2 = 180;
	 				Y2 = 390;
	  			}
	  
	  	if(BallY2-17 <= Y2 && BallY2+17 >=Y1)
	  			if(BallX4-17 <= X2 && BallX4+17 >= X1)
	  			{
	  				NbrDeaths++;
	   				X1 = 150;
	 				Y1 = 360;
	 				X2 = 180;
	 				Y2 = 390;
	  			}
	  
	    if(BallY-17 <= Y2 && BallY+17 >= Y1)
	  			if(BallX5-17 <= X2 && BallX5+17 >= X1)
	  			{
	  				NbrDeaths++;
	  				X1 = 150;
					Y1 = 360;
	 				X2 = 180;
	 				Y2 = 390;
	  			}
	  
	  	if(BallY-17 <= Y2 && BallY+17 >= Y1)
	  			if(BallX6-17 <= X2 && BallX6+17 >= X1)
	  			{
	  				NbrDeaths++;
	  				X1 = 150;
	 				Y1 = 360;
	 				X2 = 180;
	 				Y2 = 390;
	  			}

    
//										Update the screen buffer
      	testWindow.UpdateBuffer();

//										Pause for half a second
     	Pause(.1);
      
//										Top Boundary
    	if(Y1<=238)
    	{
      		Y1+=12;
      		Y2+=12;
    	}
      
//										Left Boundary
	    if(X1 <= 113)
	    {
	      		X1+=12;
	      		X2+=12;
	    }
      
//										Bottom Boundary
	    if(Y2 >= 560)
	    {
	      		Y1-=12;
	      		Y2-=12;
	    }
      
//										Update the screen buffer
    	testWindow.UpdateBuffer();

//										Pause for half a second
      	Pause(1);

      
      	if(X2 >= 948)
      			bQuit = true;
      	
      	testWindow.UpdateBuffer(); 
   
    }while(bQuit != true);
    

 
//										Loop until there is a mouse click
    while(testWindow.GetMouseClick(iX, iY) == NO_CLICK)
    {
        testWindow.DrawString(testWindow.GetWidth()/2 - 100, testWindow.GetHeight() - 25, "Click mouse to continue...");
	
//										Update the screen buffer
        testWindow.UpdateBuffer();
    }
}

//======================================================================
//	Function name: Level Four
//	Purpose: This function contains the maze of the fourth level and is 
//				composed of all necessary shapes and variables to navigate
//				through the maze.
//	Note: This is the fourth of five levels.
//----------------------------------------------------------------------
void LevelFour(window &testWindow)
{
    
	int iX, iY, X1, Y1, X2, Y2, s, p, r, BallX, BallX2, BallY, BallY2, BallY3;

	bool bQuit = false;
	bool Left = false;
	keytype ktInput;
	clicktype ctInput;
	char cKeyData;
  
	r = 17; 
	BallY3 = 448;
	BallY2 = 398;
	BallY = 348;
	BallX = 299;
	BallX2 = 599;
	s = 356;
 	p = 263;
	X1 = 107;
	X2 = 137;
	Y1 = 384;
	Y2 = 414;


//										Turns on double buffering
    testWindow.SetBuffering(true);
    
    
    
//										Flush out the input queues before beginning
    testWindow.FlushMouseQueue();
    testWindow.FlushKeyQueue();
//										Sets the font
   	testWindow.SetFont(20, BOLD, BY_NAME, "Arial"); 
    
	
    do
    {
//										Pause is set and level is drawn
    	Pause(.01);
    
	    image testImage("Level4.jpg", JPEG);
	    testWindow.DrawImage(testImage, 0, -130,1200,950);
	  
	    testWindow.SetPen(WHITE, 0);    
	    testWindow.SetBrush(WHITE);
	    testWindow.DrawRectangle(182,324,1015,476);
	    
	    testWindow.SetPen(BLACK, 5);    
	    testWindow.SetBrush(RED);
	    testWindow.DrawRectangle(X1,Y1,X2,Y2,FILLED,5);
	     	 
//										Ball movement 	 
	    if(Left == false)
	    {
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX+=3, BallY, r, FILLED);

			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX, BallY2, r, FILLED);
			
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX, BallY3, r, FILLED);
			
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX2+=3, BallY, r, FILLED);   
			   
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX2, BallY2, r, FILLED);
			
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX2, BallY3, r, FILLED);
			Pause(.5);
		}
		
		
		 
		if(BallX2 >= 998)
		{
			Left = true;
		}
		
		if(Left == true)
		{
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX-=3, BallY, r, FILLED);

			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX, BallY2, r, FILLED);
			
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX, BallY3, r, FILLED);
			
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX2-=3, BallY, r, FILLED);   
			   
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX2, BallY2, r, FILLED);
			
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX2, BallY3, r, FILLED);
			Pause(.5);
		}
		
		if(BallX <= 199)
		{
			Left = false;
		}
		
//										Turn on double buffering
	    testWindow.SetBuffering(true);
	    
//										Draws instructions and information like deaths and number of level
	    testWindow.SetPen(BLACK); 
	    testWindow.DrawString(5, 5, "Level 4");
	    testWindow.DrawString(1100, 5, "Deaths:");
	    testWindow.DrawInteger(1165, 5, NbrDeaths);
	    ktInput = testWindow.GetKeyPress(cKeyData);
	    ctInput = testWindow.GetMouseClick(iX, iY);
	      
	  
//										Figure out what key was pressed and moves square
	    if(ktInput == ARROW) {
	    	 switch(cKeyData)
	         {
	            case 1:
	              testWindow.DrawString(5, 30, "The End key was pressed.");
	              break;
	            case 2:
	              testWindow.FlushKeyQueue();
	              testWindow.UpdateBuffer();
	              testWindow.SetPen(BLACK, 5);    
	     		  testWindow.SetBrush(RED);
	     		  testWindow.DrawRectangle(X1,Y1+=12,X2,Y2+=12,FILLED,1,1);
	     		  Pause(.01);
	              break;
	            case 3:
	              testWindow.DrawString(5, 30, "The Page Down key was pressed.");
	              break;
	            case 4:
	              testWindow.FlushKeyQueue();
	              testWindow.UpdateBuffer();
	              testWindow.SetPen(BLACK, 5);    
	     		  testWindow.SetBrush(RED);
	     		  testWindow.DrawRectangle(X1-=12,Y1,X2-=12,Y2,FILLED,1,1);
	     		  Pause(.01);
	              break;
	            case 5:
	              testWindow.DrawString(5, 30, "The Center Keypad key was pressed.");
	              break;
	            case 6:
	                testWindow.FlushKeyQueue();
	              testWindow.UpdateBuffer();
	              testWindow.SetPen(BLACK, 5);    
	     		  testWindow.SetBrush(RED);
	     		  testWindow.DrawRectangle(X1+=12,Y1,X2+=12,Y2,FILLED,1,1);
	     		  Pause(.01);
	              break;
	            case 7:
	              testWindow.DrawString(5, 30, "The Home key was pressed.");
	              break;
	            case 8:
	              testWindow.FlushKeyQueue();
	              testWindow.UpdateBuffer();
	              testWindow.SetPen(BLACK, 5);    
	     		  testWindow.SetBrush(RED);
	     		  testWindow.DrawRectangle(X1,Y1-=12,X2,Y2-=12,FILLED,1,1);
	     		  Pause(.01);
	              break;
	            case 9:
	              testWindow.DrawString(5, 30, "The Page Up key was pressed.");
	        }



	    } 
//										Ball Reset when square makes contact	               
	    if(BallX-17 <= X2 && BallX+17 >=X1)
	  		if(BallY-17 <= Y2 && BallY+17 >= Y1)
	  		{
	  			NbrDeaths++;
	  			X1 = 107;
	 			X2 = 137;
	 			Y1 = 384;
	 			Y2 = 414;
	  		}
	  
	  	if(BallX-17 <= X2 && BallX+17 >=X1)
	  		if(BallY2-17 <= Y2 && BallY2+17 >= Y1)
	  		{
	  			NbrDeaths++;
	 			X1 = 107;
	 			X2 = 137;
	 			Y1 = 384;
	 			Y2 = 414;
	  		}

	  
	  
	  	if(BallX-17 <= X2 && BallX+17 >= X1)
	  		if(BallY3-17 <= Y2 && BallY3+17 >= Y1)
	  		{
	  			NbrDeaths++;
	  			X1 = 107;
	 			X2 = 137;
	 			Y1 = 384;
	 			Y2 = 414;
	  		}
	  
	  	if(BallX2-17 <= X2 && BallX2+17 >=X1)
	  		if(BallY2-17 <= Y2 && BallY2+17 >= Y1)
	  		{
	 			NbrDeaths++;
	  			X1 = 107;
	 			X2 = 137;
	 			Y1 = 384;
	 			Y2 = 414;
	 		}
	  
	  
	  	if(BallX2-17 <= X2 && BallX2+17 >=X1)
	  		if(BallY-17 <= Y2 && BallY+17 >= Y1)
	  		{
	  			NbrDeaths++;
	  			X1 = 107;
	 			X2 = 137;
	 			Y1 = 384;
	 			Y2 = 414;
	  		}
	  
	    
	  	if(BallX2-17 <= X2 && BallX2+17 >=X1)
	  		if(BallY3-17 <= Y2 && BallY3+17 >= Y1)
	  		{
	  			NbrDeaths++;
	  			X1 = 107;
	 			X2 = 137;
		 		Y1 = 384;
	 			Y2 = 414;
	  		}
	  
//										Maze Boundaries
	    if(X1 >= 306 && X2 <= 352)
	      	if(Y1 <= 320)
	      	{
	      		Y1-=12;
	      		Y2-=12;
	      	}
	      
	    if(X1 >= 838 && X2 <= 880)
	     	if(Y1 <= 320)
	      	{
	      		Y1-=12;
	      		Y2-=12;
	      	}
	      
	    if(X1 >= 566 && X2 <= 612)
	      	if(Y2 >= 476)
	      	{
	      		Y1+=12;
	      		Y2+=12;
	      	}
	      
	      
	    if(Y1 <= 320)
	    {
	      	Y1+=12;
	      	Y2+=12;
	    }
	      
	    if(X1 <= 45)
	    {
	      	X1+=12;
	        X2+=12;
	    }
	      
	    if(Y2 >= 476)
	    {
	      	Y1-=12;
	      	Y2-=12;
	    }
	      
	    if(Y1 <= 270)
	    {
	      	Y1+=12;
	      	Y2+=12;
	    }
	      
	    if(Y2 >= 526)
	    {
	      	Y1-=12;
	      	Y2-=12;
	    }
	      
//										Update the screen buffer
	    testWindow.UpdateBuffer();

//										Pause for half a second
	    Pause(.1);

	    if(X2 >= 1015)
	      	bQuit = true;
	      	
	    testWindow.UpdateBuffer(); 
	   
    }while(bQuit != true);
    

 
//										Loop until there is a mouse click
    while(testWindow.GetMouseClick(iX, iY) == NO_CLICK)
    {
        testWindow.DrawString(testWindow.GetWidth()/2 - 100, testWindow.GetHeight() - 25, "Click mouse to continue...");
//										Update the screen buffer
        testWindow.UpdateBuffer();
    }
}

//======================================================================
//	Function name: Level Five
//	Purpose: This function contains the maze of the fifth level and is 
//				composed of all necessary shapes and variables to navigate
//				through the maze.
//	Note: This is the last of five levels.
//----------------------------------------------------------------------
void LevelFive(window &testWindow)
{
	int iX, iY, X1, Y1, X2, Y2, r, BallX, BallX2, BallX3, BallX4, BallX5, BallX6, BallY, BallY2, BallY3, BallY4, BallY5, BallY6;

	bool Down = false;
	bool bQuit = false;
	bool Left = false;
	bool Shine = true;
	keytype ktInput;
	clicktype ctInput;
	char cKeyData;

	r = 17; 
	BallX6 = 515;
	BallX5 = 564;
	BallX4 = 623;
	BallX3 = 682;
	BallX2 = 860;
	BallX = 340;
	BallY = 280;
	BallY2 = 339;
	BallY3 = 398;
	BallY4 = 457;
    BallY5 = 98; 
	BallY6 = 633;
	X1 = 375;
	Y1 = 540;
	X2 = 405;
    Y2 = 570;
    
//										Plays music
 	PlaySound("MyLove.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
 	
//										Turns on double buffering
    testWindow.SetBuffering(true);
    
//										Flush out the input queues before beginning
    testWindow.FlushMouseQueue();
    testWindow.FlushKeyQueue();

    testWindow.SetFont(20, BOLD, BY_NAME, "Arial"); 
    
	
    do
    {
    	
	    Pause(.01);
//										Draws level and necessary white boxes on top of circles
	    image testImage("Level5.jpg", JPEG);
	    testWindow.DrawImage(testImage, 0, -130,1200,950);
	  
	    testWindow.SetPen(WHITE, 0);    
	    testWindow.SetBrush(WHITE);
	    testWindow.DrawRectangle(331,465,869,262);
	   
	    testWindow.SetPen(BLACK, 5);    
	    testWindow.SetBrush(RED);
	    testWindow.DrawRectangle(X1,Y1,X2,Y2,FILLED,5);
	    
//										Ball Movement 	 
	    if(Down == false)
	    {  	 
	    	testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX3, BallY5+=23, r, FILLED);
		
		   
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX4, BallY6-=23, r, FILLED);


			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX5, BallY5, r, FILLED);

		    
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX6, BallY6, r, FILLED);
	   }
		
	   if(BallY5 >= 633)
	   {
			Down = true;
	   }
		
		 
	   if(Down == true)
	   {  	 
	    	testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX3, BallY5-=23, r, FILLED);
			
			   
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX4, BallY6+=23, r, FILLED);


			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX5, BallY5, r, FILLED);

		    
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX6, BallY6, r, FILLED);
	   }
		
	   if(BallY5 <= 98)
	   {
			Down = false;
	   }
		   
	   if(Left == false)
	   {
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX+=16, BallY, r, FILLED);

		    
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX2-=16, BallY2, r, FILLED);
			
			    
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX, BallY3, r, FILLED);
			
			   
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX2, BallY4, r, FILLED);
			Pause(.5);
		}
		
		
		 
		if(BallX >= 860)
		{
		Left = true;
		}
		
		if(Left == true)
		{
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX-=16, BallY, r, FILLED);

		    
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX2+=16, BallY2, r, FILLED);
			
			 
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX, BallY3, r, FILLED);
			
			   
			testWindow.SetPen(BLACK, 5);
			testWindow.SetBrush(BLUE);
			testWindow.DrawCircle(BallX2, BallY4, r, FILLED);
			Pause(.5);
		}
		
		if(BallX <= 340)
		{
			Left = false;
		}
		
//										Turn on double buffering
	    testWindow.SetBuffering(true);
	    
//										Draws instructions and information about level and deaths
	    testWindow.SetPen(BLACK); 
	    testWindow.DrawString(5, 5, "Level 5");
	    testWindow.DrawString(1100, 5, "Deaths:");
	    testWindow.DrawInteger(1165, 5, NbrDeaths);
	    ktInput = testWindow.GetKeyPress(cKeyData);
	    ctInput = testWindow.GetMouseClick(iX, iY);
	      	  
//										Figure out what key was pressed and moves square
	    if(ktInput == ARROW) {
	    	switch(cKeyData)
	        {
	            case 1:
	              testWindow.DrawString(5, 30, "The End key was pressed.");
	              break;
	            case 2:
	              testWindow.FlushKeyQueue();
	              testWindow.UpdateBuffer();
	              testWindow.SetPen(BLACK, 5);    
	     		  testWindow.SetBrush(RED);
	     		  testWindow.DrawRectangle(X1,Y1+=12,X2,Y2+=12,FILLED,1,1);
	     		  Pause(.01);
	              break;
	            case 3:
	              testWindow.DrawString(5, 30, "The Page Down key was pressed.");
	              break;
	            case 4:
	              testWindow.FlushKeyQueue();
	              testWindow.UpdateBuffer();
	              testWindow.SetPen(BLACK, 5);    
	     		  testWindow.SetBrush(RED);
	     		  testWindow.DrawRectangle(X1-=12,Y1,X2-=12,Y2,FILLED,1,1);
	     		  Pause(.01);
	              break;
	            case 5:
	              testWindow.DrawString(5, 30, "The Center Keypad key was pressed.");
	              break;
	            case 6:
	                testWindow.FlushKeyQueue();
	              testWindow.UpdateBuffer();
	              testWindow.SetPen(BLACK, 5);    
	     		  testWindow.SetBrush(RED);
	     		  testWindow.DrawRectangle(X1+=12,Y1,X2+=12,Y2,FILLED,1,1);
	     		  Pause(.01);
	              break;
	            case 7:
	              testWindow.DrawString(5, 30, "The Home key was pressed.");
	              break;
	            case 8:
	              testWindow.FlushKeyQueue();
	              testWindow.UpdateBuffer();
	              testWindow.SetPen(BLACK, 5);    
	     		  testWindow.SetBrush(RED);
	     		  testWindow.DrawRectangle(X1,Y1-=12,X2,Y2-=12,FILLED,1,1);
	     		  Pause(.01);
	              break;
	            case 9:
	              testWindow.DrawString(5, 30, "The Page Up key was pressed.");
	        }



	   } 
	   
//										Horizontal ball reset when square makes contact            
	   if(BallX-50 <= X2 && BallX+50 >=X1)
	  		if(BallY-17 <= Y2 && BallY+17 >= Y1)
	  		{
	  			NbrDeaths++;
	  			X1 = 375;
	 			Y1 = 540;
	 			X2 = 405;
	 			Y2 = 570;
	  		}
	  
	   if(BallX-50 <= X2 && BallX+50 >= X1)
	  		if(BallY3-17 <= Y2 && BallY3+17 >= Y1)
	  		{
	  			NbrDeaths++;
				X1 = 375;
	 			Y1 = 540;
	 			X2 = 405;
	 			Y2 = 570;
	  		}
	  
	   if(BallX2-50 <= X2 && BallX2+50 >=X1)
	  		if(BallY2-17 <= Y2 && BallY2+17 >= Y1)
	  		{
	  			NbrDeaths++;
	 			X1 = 375;
	 			Y1 = 540;
	 			X2 = 405;
	 			Y2 = 570;
	  		}
	  
	  
	   if(BallX2-50 <= X2 && BallX2+50 >=X1)
	  		if(BallY4-17 <= Y2 && BallY4+17 >= Y1)
	  		{
	  			NbrDeaths++;
	 			X1 = 375;
	 			Y1 = 540;
	 			X2 = 405;
	 			Y2 = 570;
	  		}
	  
//										Vertical ball reset when square makes contact  
	   if(BallY5-17 <= Y2 && BallY5+17 >= Y1)
	  		if(BallX3-17 <= X2 && BallX3+17 >= X1)
	  		{
	  			NbrDeaths++;
	  			X1 = 375;
	 			Y1 = 540;
	 			X2 = 405;
	 			Y2 = 570;
	  		}
	  
	  
	   if(BallY6-17 <= Y2 && BallY6+17 >=Y1)
	  		if(BallX4-17 <= X2 && BallX4+17 >= X1)
	  		{
	  			NbrDeaths++;
				X1 = 375;
				Y1 = 540;
	 			X2 = 405;
	 			Y2 = 570;
	  		}
	  
	   if(BallY5-17 <= Y2 && BallY5+17 >= Y1)
	  		if(BallX5-17 <= X2 && BallX5+17 >= X1)
	  		{
	  			NbrDeaths++;
	  			X1 = 375;
				Y1 = 540;
	 			X2 = 405;
	 			Y2 = 570;
	  		}
	  
	   if(BallY6-17 <= Y2 && BallY6+17 >= Y1)
	  		if(BallX6-17 <= X2 && BallX6+17 >= X1)
	  		{
	  			NbrDeaths++;
	  			X1 = 375;
	 			Y1 = 540;
	 			X2 = 405;
	 			Y2 = 570;
	  		}
	  
	    
//										Top Boundary
	   if(Y1<=68)
	   {
	      	Y1+=12;
	      	Y2+=12;
	   }
	      
//										Left Boundary
	   if(X1 <= 310)
	   {
	      	X1+=12;
	      	X2+=12;
	   }
	      
//										Bottom Boundary
	   if(Y2 >= 662)
	   {
	      	Y1-=12;
	      	Y2-=12;
	   }
	      
//										Right Boundary
	   if(X2 >= 880)
	   {
	      	X1-=12;
	      	X2-=12;
	   }
	        
//										Update the screen buffer
	   testWindow.UpdateBuffer();

//										Pause for half a second
	   Pause(.1);


	   if((X2 >= 717)&&(Y1 <= 253))
	        bQuit = true;

	}while(bQuit != true);
	
//										plays music
	PlaySound("Geeking.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
	
//										Sets font and turns screen black
	testWindow.SetFont(80, BOLD, BY_NAME, "Arial");
	testWindow.SetPen(BLACK,5);
	testWindow.SetBrush(BLACK);
	testWindow.DrawRectangle(0, 0, 2000, 2000);
//										Prints the number of deaths finished with		
	testWindow.SetPen(BLUE, 5);
	testWindow.DrawString(35, 30, "You have finished the game with a");
	testWindow.DrawString(testWindow.GetWidth()/2 - 225,160, "death count of");
	testWindow.DrawInteger(testWindow.GetWidth()/2 - 40, 290, NbrDeaths);

//										offers a replay option below
	testWindow.SetPen(WHITE, 5);
	testWindow.DrawRectangle(452,572, 748,676,FRAME); 
		
//										Loop until there is a mouse click
    while(testWindow.GetMouseClick(iX, iY) == NO_CLICK)
    {
    
       testWindow.DrawString(458,586, "REPLAY");
	
//										Update the screen buffer
        testWindow.UpdateBuffer();
	}
}

//======================================================================
//	Function name: WaitNClear
//	Purpose: This function allows the user to click and then clear the
//				the screen.
//	Note: This is used once to clear the instruction screen.
//----------------------------------------------------------------------
void WaitNClear(window &inputWindow)
{
 	int iX, iY;
 
 	inputWindow.SetPen(BLACK);
	inputWindow.SetFont(16, BOLD, SWISS);

//										Flush the mouse queue
    inputWindow.FlushMouseQueue();

//										Ignore return value since we don't care what type of click it was
    inputWindow.WaitMouseClick(iX, iY);

//										Set the brush and pen white so we can clear the background
    inputWindow.SetPen(WHITE, 0);    
    inputWindow.SetBrush(WHITE);
    
//										Draw a rectangle that covers the entire window
    inputWindow.DrawRectangle(0, 0, inputWindow.GetWidth(), inputWindow.GetHeight());
}	







 
     
  

