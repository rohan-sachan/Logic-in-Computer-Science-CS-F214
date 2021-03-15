/* Logic Homework 3, Part 1 */
/* Team Number: 47 */
/* Team Members:
1. <Jui Pradhan> <ID 2018B3A70984H>
2. <Harsh Daryani> <ID 2018B1A70645H>
3. <Rohan Sachan> <ID 2018B3A70992H>
4. <Aviral Kumar Tiwari> <ID 2018B3A70820H>
*/

#include <stdio.h>
#include <string.h>

#define MAX 100 // macro indicating the maximum size of stack




/*********************/
/*******stack operations**********/

// Inserting data onto top of stack. Takes as arguments the data to be pushed, the array used for implementing the stack and an integer pointer referencing the index of the top of that stack.

void push(char data, char stack[], int *top)
{
    if(*top != MAX-1) // if stack is not full
   {  *top = *top + 1;
      stack[*top] = data;
   }
   else
   {
      printf("Could not insert data, Stack is full.\n");
   }
}


// Removing element from top of stack. Takes as arguments the array used for implementing the stack and an integer pointer referencing the index of the top of that stack. Returns the popped character.

char pop(char stack[], int *top)
{
   char data;

   if(*top != -1) //checking whether stack contains some elements
   {
      data = stack[*top];
      *top = *top - 1;
      return data;
   }

   else
   {
      printf("Could not retrieve data, Stack is empty.\n");
   }
}

// NOTE:
// A pointer to the variable top is passed instead of passing the top variable itself. This is done to ensure top is passed as reference and any modifications to the top variable
// would be reflected in the calling function



/*********************/
/******* implementation **********/

// function to implement the solution for Part 1. Takes as arguments the number of atoms, the character array to store the completely parenthesized input formula and the array to store the valuation of the atoms
// returns the final result of evaluating the formula (either T or F)

char eval_formula(int n, char formula[], char operand_val[])
{
   char operand_stack[MAX];  // character array to implement operand stack
   char operator_stack[MAX]; // character array to implement operator stack
   int operand_top = -1; // integer pointing to the top of the operand stack
   int operator_top = -1;  // integer pointing to the top of the operand stack

   char a,b,c,z; 
   for(int j=1;j<=n;j++)
   {
       char r = j+'0'; // int to char conversion
       for(int i=0;i<strlen(formula);i++)
       {
            if(formula[i]==r)
                formula[i]=operand_val[j-1];
       }
   }
    for(int i=0;i<strlen(formula);i++)
    {
        if(formula[i]=='('||formula[i]=='~'||formula[i]=='>'||formula[i]=='V'||formula[i]=='^')
            push(formula[i],operator_stack,&operator_top);
        else if(formula[i]=='T'||formula[i]=='F')
            push(formula[i],operand_stack,&operand_top);
        else if(formula[i]==')')
        {
            a=pop(operator_stack,&operator_top); // pops the operator
            z=pop(operator_stack,&operator_top); // pops the opening bracket '('
            if(a=='>'||a=='^'||a=='V')
            {
                b = pop(operand_stack, &operand_top); // pops operand valuation
                c = pop(operand_stack, &operand_top); // pops operand valuation
                if(a=='>')
                {
                     if(b=='F'&&c=='T')
                        push('F',operand_stack,&operand_top);
                    else
                        push('T',operand_stack,&operand_top);
                }
                else if(a=='^')
                {
                     if(b=='T'&&c=='T')
                        push('T',operand_stack,&operand_top);
                    else
                        push('F',operand_stack,&operand_top);
                }
                else if(a=='V')
                {
                     if(b=='F'&&c=='F')
                        push('F',operand_stack,&operand_top);
                    else
                        push('T',operand_stack,&operand_top);
                }
            }
            else if(a=='~')
            {
                b=pop(operand_stack,&operand_top);	// pops operand valuation
                if(b=='F')
                    push('T',operand_stack,&operand_top);
                else
                    push('F',operand_stack,&operand_top);
            }
        }
    }
    return operand_stack[operand_top];
}

/*********************/
/********main function**********/

int main()
{
  int n; // number of operands
  char formula[MAX]; // character array to store the input formula
  char operand_val[10]; // array to store the valuation of operands (either T or F)//
  scanf("%d",&n);
  getchar();
  fgets(formula,MAX,stdin);
  fgets(operand_val,10,stdin);

  // line 147 to line 171 takes care of spaces entered between the operators and operands.
  char formula_duplicate[MAX];
  char operand_val_duplicate[10];
  int a=0,b=0;
  while (formula[a] != '\0')
  {
    if (!(formula[a] == ' '))
    {
        formula_duplicate[b] = formula[a];
        b++;
    }
      a++;
  }
  formula_duplicate[b] = '\0';
  a=0; // a stores the index for traversing array operand_val[]
  b=0; // b stores the index for traversing array operand_val_duplicate[]
  while (operand_val[a] != '\0')
  {
    if (!(operand_val[a] == ' '))
    {
        operand_val_duplicate[b] = operand_val[a];
        b++;
    }
      a++;
  }
  operand_val_duplicate[b] = '\0';
  printf("%c",eval_formula(n,formula_duplicate,operand_val_duplicate));
  return 0;
}
