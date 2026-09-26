#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

void parse_and_roll(const char *spec){
    int num_dice = 1;
    int sides = 6;
    int modifier = 0;
    int i, roll, total = 0;

    const char *p = spec;

    //Parse the number of dice provided
    if (isdigit((unsigned char)*p)){
        num_dice = atoi(p);
        while (isdigit((unsigned char)*p)) p++;
    }

    //Check for the d or D indicator
    if(*p == 'd' || *p == 'D'){
        p++;
        if (isdigit((unsigned char)*p)){
            sides = atoi(p);
            while (isdigit((unsigned char)*p)) p++;
        }
    }
    else{
        printf("Invalid dice notation: %s\n", spec);
        return;
    }

    //Parse + or - indicator
    if(*p == '+' || *p == '-'){
        modifier = atoi(p);
    }

    printf("Rolling %dd%d", num_dice, sides);
    if (modifier != 0) printf("%+d", modifier);
    printf(":\n");

    //Get rolls
    printf("Individual rolls: ( ");
    for (i = 0; i < num_dice; i++){
        roll = (rand() % sides) +1;
        printf("%d ", roll);
        total += roll;
    }
    total += modifier;
    printf(")\nTotal result: %d\n\n", total);
}

int main(int argc, char **argv){
    int i;
    srand((unsigned int)time(NULL));//RNG seed

    if (argc < 2){
        printf("MSDOS Rolldice (386 Protected Mode Port)\n");
        printf("Usage: ROLLDICE <dice_specification> [more_specs...]\n");
        printf("Example: ROLLDICE 3d6 1d20+5\n");
        return 1;
    }

    for (i = 1; i < argc; i++){
        parse_and_roll(argv[i]);
    }
    return 0;
}
