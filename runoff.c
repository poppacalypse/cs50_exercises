#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// 2-dimensional array. preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            printf(" won the election\n");
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            printf("It's a tie\n");
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Iterate over each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if candidate's name matches given name
        if (strcmp(candidates[i].name, name) == 0)
        {
            // If yes, record the preference
            preferences[voter][rank] = i;
            return true;
        }
    }
    // If not match, return false
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Iterate over each voter
    for (int i = 0; i < voter_count; i++)
    {
        // Iterate over each preference for the current voter
        for (int j = 0; j < candidate_count; j++)
        {
            // Get the candidate index for the current preference
            int candidate_index = preferences[i][j];

            // Check if the candidate is not eliminated
            if (!candidates[candidate_index].eliminated)
            {
                // Update the vote count for the non-eliminated candidate
                candidates[candidate_index].votes++;
                // Break out of the inner loop since we found a non-eliminated candidate
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // Calculate the number of votes needed to win the election
    int winning_threshold = (voter_count / 2) + 1;

    // Iterate over each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if candidate has enough votes to win
        if (candidates[i].votes >= winning_threshold)
        {
            // Print winner's name
            printf("%s\n", candidates[i].name);
            // Return true to indicate winner has been found
            return true;
        }
    }
    // Return false if no winner has been found`
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Find the minimum number of votes
    int min_votes = voter_count;
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if candidate is not eliminate and has fewer votes than current minimum
        if (!candidates[i].eliminated && candidates[i].votes < min_votes)
        {
            min_votes = candidates[i].votes;
        }
    }
    return min_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // Iterate over all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if candidate is not eliminated and has a different vote count than min
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            // If the above is true, it's not a tie.
            return false;
        }
    }
    // If all candidates have the same vote count (== min), it's a tie.
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
