import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print ("Usage : dna.py FILE.csv SEQUENCE.txt")

    # TODO: Read database file into a variable
    #create a list of STRs
    STR_list=[]


    #create a list of dictionnaries to store the database
    db_list = []

    with open(sys.argv[1],"r") as db:
        #to store the first row's STRS in a list
        db_reader = csv.reader(db)
        for row in db_reader:
            STR_list=row[1 :]
            break

    with open(sys.argv[1],"r") as db:
        #to store the data base in a list of dicts
        db_dictreader=csv.DictReader(db)
        for row in db_dictreader:
            db_list.append(row)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2],"r") as file:
        DNA = file.read()

    # TODO: Find longest match of each STR in DNA sequence

    #create  a dictionnary of STRS where each STR  as a key will correspond to larget consecutive run in the DNA sequence
    STR_dict ={}

    #itterate over STR_list and use longest match_function to get a value the store the key value pair in STR_dict
    for str in STR_list:
        STR_dict[str]=longest_match(DNA,str)


    # TODO: Check database for matching profiles
    #define the length of the STR_list as whole_match
    whole_match = len(STR_list)

    #iiterate over the list of dictionnaires equivelant to our database
    for dict in db_list:

        counter =0
        #itterate over the list of strs and compare if the number of occurences of that str in the DNA sequence is equivelante to the number of occurences in the current dictionnary sequence if so print the corresponding name and break
        for str in STR_list:
            if int(STR_dict[str]) == int(dict[str]):
                counter +=1

        #if counter is equivalent to whole_match means that there is a match
        if counter == whole_match:
            print(dict["name"])
            break
    #if no match is found
    print("No match")


    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
