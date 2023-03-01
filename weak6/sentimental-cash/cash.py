from cs50 import get_float
while True:
    change_in_dollars = get_float("Change owed: ")
    if change_in_dollars > 0:
        break

change_in_cents = change_in_dollars * 100
quarters=(change_in_cents-(change_in_cents%25))/25
change_in_cents = change_in_cents - (quarters * 25)

dimes=(change_in_cents-(change_in_cents%10))/10
change_in_cents = change_in_cents - (dimes * 10)

nickles=(change_in_cents-(change_in_cents%5))/5
change_in_cents = change_in_cents - (nickles * 5)

pennies=(change_in_cents-(change_in_cents%1))/1
change_in_cents = change_in_cents - (pennies * 1)

number_of_coins = quarters + dimes + nickles + pennies
print(int(number_of_coins))