#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

/* preferences[i][j] is number of voters who prefer i over j
which mean at the intersection of the i and colmun j you will find the number of
voters who prefered i over j.*/
int preferences[MAX][MAX];

/* locked[i][j] means i is locked in over j .it's a boolean array where
i is locked over j(in the case of our array it's the value true) means there exists
an arrow from candidate i to candidate j in the candidate graph and if the value is false
there dosen't exist such an arrow therein*/
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;//this  intger represnets the winner's index
    int loser;//this intger represnets the loser's index
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];/*we dereived  the max number of pairs using the binomial coeeficent
formula for n choose 2 where n is the number of diffrent candidates in this case MAX and 2 because
we are choosing distinct pairs of candidates*/

int pair_count=0;//number of pairs in the pairs array
int candidate_count;// number of candidates

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool is_cycle(int end ,int begin);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for(int i=0;i<candidate_count;i++)/*this loops over all the candidates in the candidates array
                                        looking for a match with the given name*/
    {
        if(!strcmp(name,candidates[i]))/*if the match is found and the given name is indeed in the array
                                        set it's index value(here the i in the candidates[i])
                                        to the rank index in the ranks array
                                        this way we will know that candidate i have rank j*/
        {
            ranks[rank]=i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    /*if candidate i has rank j that means that candidate i is prefered to all other candidates indexed >j
    in the ranks [] array*/

    for (int i=0;i<candidate_count;i++)/*the variable i here denotes the ranks as we are looping
                                        over all the ranks given by a single voter*/
    {
        for (int j=i+1;j<candidate_count;j++)/*the variable j here denotes the all the candidates whose rank
                                                is lower than i*/
        {
            preferences[ranks[i]][ranks[j]]++;/*following the above logic we add to the prefrences 2D array which
                                                denotes here that candidate ranks[i] is ranked better than candidate
                                                ranks[j]*/
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    /*to do this we are going to work on the prefrences array , remember that prefrences [i][j]
    the number of voters who prefer i over j  a pair has a winner and a loser when prefrences
    [i][j]>prefrences [j][i]*/

    for (int i=0;i<candidate_count;i++)
    {
        for (int j=0;j<candidate_count;j++)
        {
            if(preferences[i][j]>preferences[j][i])
            {
                pairs[pair_count].winner=i;
                pairs[pair_count].loser=j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
/*we will use here a selection sort to sort the pairs from strongest victory to weakst*/
      pair temp;//temporary variable for storing the pair with the strongest win so it can be swaped
      int tempdex;//temporary int to store the index of the pair with the strongest win so we know with
                    //which pair do we swap the first pair
      int strongest=preferences [pairs[0].winner][pairs[0].loser]-preferences [pairs[0].loser][pairs[0].winner];//calculates the strongest margin temporarirly and uppdates it accordignly

      for (int i=0;i<pair_count;i++)
      {
        tempdex=i;
        temp=pairs[i];
        for (int j=i+1;j<pair_count;j++)
        {
            if(strongest<preferences [pairs[j].winner][pairs[j].loser]-preferences [pairs[j].loser][pairs[j].winner])
            {
                strongest=preferences [pairs[j].winner][pairs[j].loser]-preferences [pairs[j].loser][pairs[j].winner];
                temp=pairs[j];
                tempdex=j;

            }
        }
        pairs[tempdex]=pairs[i];
        pairs[i]=temp;

      }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    /* locked [i][j]=true means i is a winner over j according to
    the pairs array that's locked[pairs[i].winner][pairs[i].loser]=true
*/
for(int i=0;i<pair_count;i++)
{
    if(!is_cycle(pairs[i].loser,pairs[i].winner))
    {
        locked[pairs[i].winner][pairs[i].loser]=true;
    }
}
    return;
}

// Print the winner of the election
void print_winner(void)
{
    /*the winner is the source the one that no arrows points to in the graph
    in our case in the locked array he iss i in the locked[j][i] array for each value j such that
    locked[j][i]=false */


    for (int i=0;i<pair_count;i++)/*i here represents the columns , we are looking if locked[j][i]=false for
    all values of j that can only be true if the condition is met and we add +1 to counter variable each time if counter = the
    number of pairs that means that is false for all cases and that i is the source*/
    {
        int counter=0;
        for (int j=0;j<pair_count;j++)// j  represents the row
        {
            if(locked[j][i]==false)
            {
                counter++;
            }
        }
        if(counter==pair_count)
        {
            printf("%s\n",candidates[i]);
            break;
        }
    }


    return;
}


bool is_cycle(int end ,int begin)
{
    if(end==begin)
    {
        return true;
    }
    else
    {
        for (int i =0;i<candidate_count;i++)
        {
            if(locked[end][i])
            {
                if(is_cycle(i,begin))
                {
                    return true;
                }
            }
        }
        return false;
    }
}

/*define a function that somehow  checks for cycles t

we have for example the the ordered pairs array from strongest victory to weakst
[a, b, c, d]
pair pairs[]=[(d, a), (a, b), (b, c), (c, a), (d, b), (d, c)]
bool  cycle(end , begin):
    if(end == being):
        return true
    else:
        for i in candidate_count:
            if(locked[end][i]):
                if(cycle(i,begin)):
                    return true
        return false
for i in pair_count:
    if(!cycle(pairs[i].loser,pairs[i].winner):
        locked[pairs[i].winner][pairs[i].loser]==true

test:
if i =0;
cycle(0,4)
0 not = 4
locked 0 0 = false
locked 0 1 = true
    cycle (1,4)
    1 not = 4
    locked [1][0] = false
    locked [1][1]= false
    locked [1][2]= true
        cycle(2,4)
        2 not = 4
        locked [2][0]=true
            cylce (0,4)
            0not = 4
            locked [0][0]= false
            locked [0][1]



a=0
b=1
c=2
d=3
before doing  locked[pairs[0].winner pairs[0].loser]=true
we check all the possible cycle formations
pairs[0].winner=0
pairs[0].loser=3
locked[0][3]
locked[3][1]
locked[1][0]
first we check if locked[3][1] is true if so we check if locked [1][0]is true ==>then a possible cylce
can be formed so we can't lock the values
the same can be said when locked [3][2]== true && locked [2][0]==true





    a  b  c  c
    0  1  2  3
a 0 0  0  0  0
b 1 0  0  0  0
c 2 0  0  0  0
d 3 0  0  0  0

*/