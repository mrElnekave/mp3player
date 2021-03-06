// Inspired by James K. Lawless remade by Yamm Elnekave
/*
// cmdmp3
// A command-line MP3 player for Windows
// (console-mode version)
//
// License: MIT / X11
// Copyright (c) 2009, 2015 by James K. Lawless
// jimbo@radiks.net  http://jiml.us
// See http://www.mailsend-online.com/license2015.php
//
// To build, use the following MinGW command:
//    gcc -o cmdmp3.exe -lwinmm cmdmp3.c

#include <windows.h>
#include <stdio.h>
#include <string.h>

void sendCommand(char *);

int main(int argc,char **argv) {
   char shortBuffer[MAX_PATH];
   char cmdBuff[MAX_PATH + 64];
   printf("cmdmp3 v2.0\n");
   printf("Command-line MP3 player\n");
   printf("by Jim Lawless - http://jiml.us\n\n");
   
   if(argc<2) {
      fprintf(stderr,"Syntax:\n\tcmdmp3 \"c:\\path to file\\file.mp3\"\n");
      return 1;
   }
      // Get the shortened path because the MCI string interpreter uses spaces
      // as a separator.  If spaces appear in the commands, parts of the filename
      // would be interpreted as paramters to the given command.
   GetShortPathName(argv[1],shortBuffer,sizeof(shortBuffer));
   if(!*shortBuffer) {
      fprintf(stderr,"Cannot shorten filename \"%s\"\n",argv[1]);
      return 1;
   }   
   sendCommand("Close All");

   sprintf(cmdBuff,"Open %s Type MPEGVideo Alias theMP3",shortBuffer);
   sendCommand(cmdBuff);

   sendCommand("Play theMP3 Wait");
   return 0;
}

   // Send a string to the Media Control Interface
   // If an error occurs, display it and the string
   // that produced the error.
void sendCommand(char *s) {
   int i;
   i=mciSendString(s,NULL,0,0);
   if(i) {
         fprintf(stderr,"Error %d when sending %s\n",i,s);
   }
}
*/

// ---------- TO COMPILE: gcc mp3player.c -lwinmm -o mp3player.exe 
#include <windows.h>
#include <stdio.h>
#include <string.h>

// Send a string to the Media Control Interface
// If an error occurs, display it and the string
// that produced the error.
#define sendCommand(s)	commandReturn = mciSendString(s,NULL,0,0);\
                  if (commandReturn) fprintf(stderr,"Error %d when sending %s\n",commandReturn,s);

int main(int argc,char **argv) {
   int commandReturn;
   char shortBuffer[MAX_PATH];
   const int commandLength = 34;
   char cmdBuff[MAX_PATH + commandLength];
   printf("MP3 player running\n");
   
   if(argc<2) {
      fprintf(stderr,"Syntax:\n\tmp3player \"c:\\path to file\\file.mp3\"\n");
      return 1;
   }
   // Get the shortened path because the MCI string interpreter uses spaces
   // as a separator.  If spaces appear in the commands, parts of the filename
   // would be interpreted as paramters to the given command.
   char* filename = argv[1];
   GetShortPathName(filename, shortBuffer, sizeof(shortBuffer));
   if(!*shortBuffer) {
      fprintf(stderr,"Cannot shorten filename \"%s\"\n", filename);
      return 1;
   }
   // make sure nothing is running
   sendCommand("Close All");
   printf("playing %s\n", shortBuffer);
   // https://www.toolbox.com/tech/programming/question/mp3s-using-mpegvideo-type-do-not-work-051614/
   //mciSendString(???open ????????? & MyMP3File & ????????? type MPEGVideo alias PlayThis???, ??????, 0, 0)
   sprintf(cmdBuff,"Open %s Type MPEGVideo Alias toPlay",shortBuffer);
   sendCommand(cmdBuff);

   sendCommand("Play toPlay Wait");
   return 0;
}
