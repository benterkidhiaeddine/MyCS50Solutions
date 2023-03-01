from cs50 import get_string

def main():
    #get input
    input = get_string("Text: ")
    #calculate letters  , words and sentences
    l = letters(input)
    w = words (input)
    s = sentences (input)

    #calculate the average number of letters for 100 words
    L = (l /(w)) * 100
    #calculate the average number of sentences for 100 words
    S = (s / (w))* 100
    #calculate index : index = 0.0588 * L - 0.296 * S - 15.8
    index = round(0.0588 * L - 0.296 * S - 15.8)
    #print index
    if index < 1:
        print("Before Grade 1")
    if index >= 1 and index <= 16:
        print(f"Grade {index}")
    if index >= 16:
        print ("Grade 16+")




#function that count letters
def letters(string):
    count = 0
    for char in string:
        if (char.isalpha()):
            count += 1
    return count

#function that count words
def words (string):
    count = 1
    for word in string :
        if " " in word:
            count +=1
    return count


#function that count sentences
def sentences(string):
    count=0
    for word in string:
        if "!" in word or "?" in word or "." in word:
            count += 1
    return count


if __name__ == "__main__":
    main()