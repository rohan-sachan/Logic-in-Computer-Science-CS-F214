/* Logic Homework 3, Part 2 */
/* Team Number: 47 */
/* Team Members:
1. <Jui Pradhan> <ID 2018B3A70984H>
2. <Harsh Daryani> <ID 2018B1A70645H>
3. <Rohan Sachan> <ID 2018B3A70992H>
4. <Aviral Kumar Tiwari> <ID 2018B3A70820H>
*/

#include <stdio.h>
#include <string.h>

#define MAX 1000 // macro indicating the maximum size of stack




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
       char r=j+'0'; // int to char conversion
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
                b=pop(operand_stack,&operand_top); // pops the operand valuation
                c=pop(operand_stack,&operand_top); // pops the operand valuation
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
                b=pop(operand_stack,&operand_top);
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
char Test[1500][12]; // Stores all valuations of atoms
long int k=0;
char TruthTable[1500][12]; // Stores the Truth Table in form of a 2D array
void AssignTheBitStrings(char arr[], int n) // Function to store all the binary strings of n bits in a 2D array
{

    for (int i = 0; i < n; i++)
    {
        Test[k][i]=arr[i];
    }
    k=k+1;
}
void generateAllBinaryStrings(int n, char arr[], int i) // function to generate all the binary strings of n bits
{
    if (i == n) {
        AssignTheBitStrings(arr, n);
        return;
    }
    arr[i] = 'F';
    generateAllBinaryStrings(n, arr, i + 1);
    arr[i] = 'T';
    generateAllBinaryStrings(n, arr, i + 1);
}

void Issatisfiable(char Truth[]) // Function to check the satisfiability of the given propositional formula
{
    for(int i=0;i<k;i++)
    {
        if(Truth[i]=='T')
        {
            printf("Formula is satisfiable.\n");
            return;
        }
    }
    printf("Formula is not satisfiable.\n");
}

int Isvalid(char Truth[]) // Function to check the validity of the given propositional formula
{
    for(int i=0;i<k;i++)
    {
        if(Truth[i]=='F')
        {
            printf("Formula is not valid.\n");
            return 0;
        }
    }
    printf("Formula is valid.\n");
    return 1;
}

void printCNFofTautology(int no_of_atoms) // Function to generate CNF form of the given propositional formula when it is a Tautology
{
    char CNF[20000]; // stores the CNF formula
    int counter = 0; // counter to traverse CNF array
    CNF[counter]='(';
    counter=counter+1;
    CNF[counter]='1';
    counter=counter+1;
    CNF[counter]='V';
    counter=counter+1;
    CNF[counter]='(';
    counter=counter+1;
    CNF[counter]='~';
    counter=counter+1;
    CNF[counter]='1';
    counter=counter+1;
    CNF[counter]=')';
    counter=counter+1;
    char t;  
    if(no_of_atoms>1)
    {
        for(int i=1;i<no_of_atoms;i++)
        {
            CNF[counter]='V';
            counter=counter+1;
            t ='0' + i+1; // To convert from int to char
            CNF[counter]=t;
            counter=counter+1;
        }
    }
    CNF[counter]=')';
  for(int j=0; j<=strlen(CNF); j++)
    printf("%c", CNF[j]);
  printf("\n");
  printf("Given Propositional Formula is a Tautology\n");
}

void printCNF(int no_of_atoms) // Function to generate CNF form of the given propositional formula when it is not a Tautology
{
  char CNF[20000]; // stores the CNF formula
  int counter = 0; // counter to traverse CNF array
  int no_of_F=0; // counts the number of times the formula is false
  CNF[counter]='(';
  for(int i = 0; i < k; i++)
  {
      if(TruthTable[i][no_of_atoms]=='F')
        no_of_F=no_of_F+1;
  }
  for(int row=0; row<k; row++)
  {
      if(TruthTable[row][no_of_atoms]=='F')
      {
          CNF[++counter]='(';
          for(int i=0; i<no_of_atoms; i++)
          {
            if(TruthTable[row][i]=='F')
              CNF[++counter]= '0' + i+1;
            else
            {
              CNF[++counter]='(';
              CNF[++counter]='~';
              CNF[++counter]= '0' + i+1;
              CNF[++counter]=')';
            }
            if(i != no_of_atoms-1)
              CNF[++counter]='V';
          }
          CNF[++counter]=')';
          if(no_of_F>1)
          {
              CNF[++counter]='^';
              no_of_F=no_of_F-1;
          }
      }
  }
  CNF[++counter]=')';

  for(int j=0; j<=counter; j++)
    printf("%c", CNF[j]);
  printf("\n");
}
int main()
{
  int n; // number of operands
  char formula[MAX]; // character array to store the input formula
  scanf("%d",&n); // array to store the valuation of operands (either T or F)
  getchar();
  fgets(formula,MAX,stdin);
  //note: please enter correctly-formed formula and it should have all the brackets (even for V and ^).
  // line 278 to line 289 takes care of spaces entered between the operators and operands.
  char formula_duplicate[MAX]; // Stores the duplicated formula without spaces
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
  char arr[n];
  char Truth[k];
  generateAllBinaryStrings(n, arr, 0);   // generate all binary strings for n bits.
  char arr2[n];
   for(int i=0;i<k;i++)
   {
       for(int j=0;j<n;j++)
       {
           arr2[j]=Test[i][j];
           TruthTable[i][j]=arr2[j];
       }
       Truth[i]=eval_formula(n,formula_duplicate,arr2);
       TruthTable[i][n]=Truth[i];
        a=0;
        b=0;
        // loop to copy formula without spaces
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
   }
   Issatisfiable(Truth);
   int validity=Isvalid(Truth);
   if(validity==0)
    printCNF(n);
   else
    printCNFofTautology(n);
   return 0;
}
