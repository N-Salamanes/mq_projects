/***************************************************************************
 * Dr. Evil's Insidious Bomb, Version 1.3
 * Copyright 2016, Dr. Evil Incorporated. All rights reserved.
 *
 * New and improved version. All the clues on the Internet are useless!
 * -- Dr. Evil
 *
 * LICENSE:
 *
 * Dr. Evil Incorporated (the PERPETRATOR) hereby grants you (the
 * VICTIM) explicit permission to use this bomb (the BOMB).  This is a
 * time limited license, which expires on the death of the VICTIM.
 * The PERPETRATOR takes no responsibility for damage, frustration,
 * insanity, bug-eyes, carpal-tunnel syndrome, loss of sleep, or other
 * harm to the VICTIM.  Unless the PERPETRATOR wants to take credit,
 * that is.  The VICTIM may not distribute this bomb source code to
 * any enemies of the PERPETRATOR.  No VICTIM may debug,
 * reverse-engineer, run "strings" on, decompile, decrypt, or use any
 * other technique to gain knowledge of and defuse the BOMB.  BOMB
 * proof clothing may not be worn when handling this program.  The
 * PERPETRATOR will not apologize for the PERPETRATOR's poor sense of
 * humor.  This license is null and void where the BOMB is prohibited
 * by law.
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "support.h"
#include "phases.h"

/* 
 * Note to self: Remember to erase this file so my victims will have no
 * idea what is going on, and so they will all blow up in a
 * spectaculary fiendish explosion. -- Dr. Evil 
 */

FILE *infile;

int main(int argc, char *argv[])
{
    char *input;
    int status;
    int k, a, b, c;

    /* Note to self: remember to port this bomb to Windows and put a 
     * fantastic GUI on it. */

    /* When run with no arguments, the bomb reads its input lines 
     * from standard input. */
    if (argc == 1) {  
        infile = stdin;
    } 

    /* When run with one argument <file>, the bomb reads from <file> 
     * until EOF, and then switches to standard input. Thus, as you 
     * defuse each phase, you can add its defusing string to <file> and
     * avoid having to retype it. */
    else if (argc == 2) {
        if (!(infile = fopen(argv[1], "r"))) {
            printf("%s: Error: Couldn't open %s\n", argv[0], argv[1]);
            exit(8);
        }
    }

    /* You can't call the bomb with more than 1 command line argument. */
    else {
        printf("Usage: %s [<input_file>]\n", argv[0]);
        exit(8);
    }

    /* Do all sorts of secret stuff that makes the bomb harder to defuse. */
    initialize_bomb();

    printf("Welcome to my fiendish little bomb. You have 6 phases with\n");
    printf("which to blow yourself up. Have a nice day!\n");

    /* Hmm...  Six phases must be more secure than one phase! */
    /* A secure password has random characters.  They'll never guess
     * my password. Especially because it is encoded in ASCII! */
    input = read_line();             /* Get input                   */
    status = phase_1(input);         /* Run the phase               */
    phase_defused(status);           /* Drat!  They figured it out!
                                      * Let me know how they did it. */
    printf("Phase 1 defused. How about the next one?\n");
    if (status > 0) printf ("Congratulations, expert!\n");

    /* They won't crack this one.  No one learns arithmetic anymore... */
    input = read_line();
    k = sscanf(input, "%d %d %d", &a, &b, &c);
    status = phase_2(k, a, b, c);
    phase_defused(status);
    printf("That's number 2.  Keep going!\n");
    if (status > 0) printf ("An excellent solution!\n");

    /* You think you know how to solve bombs, but I've switched the way I do things this time.
     * You're not going to break this! */
    input = read_line();
    k = sscanf(input, "%d %d", &a, &b);
    status = phase_3(k, a, b);
    phase_defused(status);
    printf("Halfway there!\n");
    if (status > 0) printf ("Your bomb defusing skills are great!\n");

    /* Is it a bug or a feature? Only a security hacker can work this one out.
     * Get with the flow...  buffer overflow, that is.  Mua ha ha!  */
    input = read_line();
    status = phase_4(input);
    phase_defused(status);
    printf("So you got that one.  Try this one.\n");
    
    /* They guessed my password coded in ASCII but they won't guess my encrypted password! */
    input = read_line();
    status = phase_5(input);
    phase_defused(status);
    printf("Good work!  On to the next...\n");
    if (status > 0) printf ("Perfect bomb defusing skill!\n");

    /* This phase will never be used, since no one will get past the
     * earlier ones.  But just in case, make this one extra hard. */
    input = read_line();
    status = phase_6(input);
    phase_defused(status);

    /* Wow, they got it!  But isn't something... missing?  Perhaps
     * something they overlooked?  Mua ha ha ha ha! */
    
    return 0;
}
