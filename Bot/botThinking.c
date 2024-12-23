#include "../headerFile.h"
/*
requires: a reference to currentPlayer when current player is bot
          a reference to opposingPlayer 
          
effects:  determines the bot's next move based on the current state of the game.
          the bot will first attempt to use a radar sweep, then a torpedo if available, followed by artillery if applicable.
          if no special actions are available, the bot will perform a regular attack.
*/
          


void botThinking(PLAYER *currentPlayer, PLAYER *opposingPlayer)
{
 
    
    //first we do the radars
    if(difficulty!=EASY)
    {
        int radarResult = handleRadar(currentPlayer,opposingPlayer);
        if(radarResult==1)
        {
            return; //done
        }


        if(currentPlayer->torpedo==2)
        {
            
            handleTorpedo(currentPlayer,opposingPlayer);
            return; //always end and done
            //do the torpedo first
        }

        if(currentPlayer->artillery ==2)
        {
            INPUT input;
            handleArtillery(currentPlayer,opposingPlayer);
            //handleArtillery(currentPlayer,opposingPlayer);
            return; //always end

            //do artillery
        }
    }
    
    
    INPUT input;
    handleFire(currentPlayer,opposingPlayer);

    //smoke screen is useless 

     
}
