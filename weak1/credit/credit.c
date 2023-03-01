#include <cs50.h>
#include <stdio.h>

//American Express:15 digits ,starts with 34 or 37

//Master card:16 digits ,starts with 51,52,53,54 or 55

//Visa card: 16 or 13 digits ,always starts with 4

long credit_card_number(void);
long get_digit(long number, int digit_index);
int number_of_digits(long numer);
long pow_10(long a);
bool is_AmericanExp(long card_number);
bool is_Mastercard(long card_number);
bool is_Visa(long card_number);



int main(void)
{
    long card_number=credit_card_number();
    long number_ofdigits=number_of_digits(card_number);
    long sum_of_multiples=0;
    long sum_of_non_multiples=0;


//"For loop" for getting the sum of the digits of the result of multiplication of even indexed digits by 2
    for(int i=2;i<=number_ofdigits;i+=2)
    {
        sum_of_multiples=sum_of_multiples+get_digit(get_digit(card_number,i)*2,1)+get_digit(get_digit(card_number,i)*2,2);
    }
//"For loop" for getting the sum of odd indexed digits
    for(int i=1;i<=number_ofdigits;i+=2)
    {
        sum_of_non_multiples=sum_of_non_multiples+get_digit(card_number,i);
    }
//checking if the sumation of the latter 2 results has 0 as its last digit
    if((sum_of_non_multiples+sum_of_multiples)%10==0)
    //applying the checking functions for each given card and return the corresponding card as A string output
    {
        if(is_AmericanExp(card_number))
        {
            printf("AMEX\n");
        }
        else if(is_Mastercard(card_number))
        {
            printf("MASTERCARD\n");
        }
        else if(is_Visa(card_number))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
      printf("INVALID\n");
    }

}

//Create a  function that prompts the user for the credit card number
long credit_card_number(void)
{
    long number;
    do
    {
        number = get_long("Enter the credit card number you want to check: ");

    }while (number<0);
    return number;
}

//create a function that gets the digit number
long get_digit( long number, int digit_index)
{
    if(digit_index==1)
    {
        return number%pow_10(digit_index);
    }
    else
    {
        return number%pow_10(digit_index)/pow_10(digit_index-1);
    }
}

//create a function that gets the number of digits of a given number

int number_of_digits(long numer)
{
    int sum=0;

    while(numer>0)
    {
        sum+=1;
        numer=numer/10;
    }
    return sum;
}

// checks if the card number is correct for AmericanExpress

bool is_AmericanExp(long card_number)
{
    if (number_of_digits(card_number)==15  && get_digit(card_number,15)==3 &&(get_digit(card_number,14)==4||get_digit(card_number,14)==7) )
    {
        return true;
    }
    return false;
}
// checks if the card number is correct for MasterCard

bool is_Mastercard(long card_number)
{
    if(number_of_digits(card_number)==16 && get_digit(card_number,16)==5 && (get_digit(card_number,15)==1||get_digit(card_number,15)==2||get_digit(card_number,15)==3||get_digit(card_number,15)==4||get_digit(card_number,15)==5))
    {
        return true;
    }
    return false;
}
// checks if the card number is correct for Visa
bool is_Visa(long card_number)
{
    if((number_of_digits(card_number)==16 && get_digit(card_number,16)==4)||(number_of_digits(card_number)==13 && get_digit(card_number,13)==4) )
    {
        return true;
    }
    return false;
}

//exponents of 10
long pow_10(long a)

{
    if (a==1)
    {
        return 10;
    }
    return 10*pow_10(a-1);
}
