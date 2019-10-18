#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    /* **********
    *   BIDMAS Precedence
    *
    *   Brackets-1
    *   Indices-2
    *   Division-3
    *   Multiplication-3
    *   Addition-4
    *   Subtraction-4
    **********************/


    char input[100], output[100], stack[100];

    printf("Enter equation\n");
    fgets(input, sizeof(input),stdin);
    int inputCounter=0;
    int outputCounter=0;
    int stackCounter=0;
    while(input[inputCounter]!='\n' && input[inputCounter]!='\0')
    {
        if(isdigit(input[inputCounter]))
        {
            output[outputCounter]=input[inputCounter];
            outputCounter++;
        }
        else
        {
            switch(input[inputCounter])
            {
            case '(': stack[stackCounter]=input[inputCounter]; stackCounter++; break;       //Assign input and move to new empty input

            case ')':{  if(stackCounter>0)                                                  //Prevents stack underflow
                        {
                            stackCounter--;                                                 //Return counter to the last input
                            while(stack[stackCounter]!='(')
                            {
                                output[outputCounter]=stack[stackCounter];                  //Pop top input onto output stack and advance output stack
                                outputCounter++;
                                if(stackCounter>=0)                                         //Prevents underflow of stack
                                {
                                    stackCounter--;                                         //Current input has been popped, therefore advance back one step to previous input
                                }
                                else{ printf("Non-Paired brackets.\n");break;}
                            }

                            break;                                                          //If '(' is encountered the stack counter does not move. Allows overwrite of '('
                        }
                        else{stack[stackCounter]=input[inputCounter]; stackCounter++; break;}
                    }


            case '^':stack[stackCounter]=input[inputCounter]; stackCounter++; break;       //Assign input and move to new empty input

            case '/':
            case '*':{
                        if(stackCounter>0)                                                  //Prevents stack underflow
                        {
                            stackCounter--;                                                 //Return counter to the last input
                            switch(stack[stackCounter])
                            {
                            case '-':
                            case '+':{
                                        stackCounter++;                                     //Advance Counter to empty cell
                                        stack[stackCounter]=input[inputCounter];            //Input into cell and advance
                                        stackCounter++;
                                        break;
                                     }
                            case '*':
                            case '/':
                            case '^':{                                                      //equal precedence and left associative
                                        output[outputCounter]=stack[stackCounter];          //Pop '/' to output and advance output counter
                                        outputCounter++;
                                        stack[stackCounter]=input[inputCounter];            //Push '/' onto stack and advance stack Counter
                                        stackCounter++;
                                        break;
                                     }
                            default : ;stack[stackCounter]=input[inputCounter]; stackCounter++; break;
                            }

                        }
                        else{stack[stackCounter]=input[inputCounter]; stackCounter++; break;}
                        break;
                    }
            case '+':
            case '-': {
                        if(stackCounter>0)                                                  //Prevents stack underflow
                        {
                            stackCounter--;                                                 //Return counter to the last input
                            switch(stack[stackCounter])
                            {
                            case '-':
                            case '+':
                            case '*':
                            case '/':
                            case '^':{
                                        output[outputCounter]=stack[stackCounter];          //Pop '*' to output and advance output counter
                                        outputCounter++;
                                        stack[stackCounter]=input[inputCounter];            //Push '/' onto stack and advance stack Counter
                                        stackCounter++;
                                        break;
                                     }
                            default : stackCounter++;stack[stackCounter]=input[inputCounter]; stackCounter++; break;
                            }

                        }
                        else{stack[stackCounter]=input[inputCounter]; stackCounter++; break;}
                        break;
                    }
            default : break;


            }
        }
        inputCounter++;
    }
    stackCounter--;
    for(stackCounter;stackCounter>=0;stackCounter--)
    {
        output[outputCounter]=stack[stackCounter];
        outputCounter++;
    }
    int i;

    for(i=0;i<outputCounter;i++)
    {
        printf("%c",output[i]);
    }
    return(0);
}
