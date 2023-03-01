from cs50 import get_int
from math import floor

#American Express:15 digits ,starts with 34 or 37

#Master card:16 digits ,starts with 51,52,53,54 or 55

#Visa card: 16 or 13 digits ,always starts with 4


card_number = get_int("Card number: ")
#copy to test which card
card_copy = card_number
#to keep track if the number is evenly placed or oddly placed and also of how many digits in the number
counter = 1

sum_odd = 0

sum_even = 0

while card_number>0:
    #every other number from left to right 2 4 6 ...
    if counter%2 ==0:
        #if the multiplication of the digit by two gives a number with two digits we need to sum those two digits and add them to the even sum
        if card_number%10 * 2 > 9:
            sum_even += (card_number%10 *2)%10 + floor((card_number%10 *2)/10)
        else :
            sum_even += card_number%10 * 2
    #odd placed digits 1 3 5 7 ..
    else:
        #simply add the digit to the sum
        sum_odd += card_number%10
    card_number = floor(card_number/10)
    counter +=1


total = sum_odd + sum_even
#check if the card number is mathematicaly valid
if total%10 == 0:
    #check for Master Card
    if counter-1 == 16 and (floor(card_copy /  10**14) == 51 or floor(card_copy /  10**14) == 52 or floor(card_copy /  10**14) == 53 or floor(card_copy /  10**14) == 54 or floor(card_copy /  10**14) == 55):
        print("MASTERCARD")
    #check for American express
    elif counter-1 == 15 and (floor(card_copy /  10**13) == 34 or floor(card_copy /  10**13) == 37):
        print("AMEX")
    elif (counter-1 == 16  and floor (card_copy /  10**15) ==4) or ( counter-1 == 13 and floor(card_copy /  10**12) == 4):
        print("VISA")
    else:
        print("INVALID")
else:
     print("INVALID")




