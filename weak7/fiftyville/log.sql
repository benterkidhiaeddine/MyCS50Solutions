-- Keep a log of any SQL queries you execute as you solve the mystery.

--theft took place on july 28 2021 --
--place humphery street --
--first we need to check the crime_scene_reports table on the particular day of the crime and on humphery street--
SELECT description
  FROM crime_scene_reports
 WHERE day = 28 AND month =7 AND year = 2021
   AND street = "Humphrey Street";
--this description mentions that there have been a theft of CS50 duck at the Humphery street bakery around 10:15 am and it mentions there have been three witnesses  --
--the three witnesses were interviewed , so we will check the interviews tables for these particular witnesses --
SELECT transcript
  FROM interviews
 WHERE day = 28 AND month = 7 and year = 2021;
 --relevant information in the transript : within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away --
 -- we can check the security logs of the bakery parking lot in that time frame--
 --the thief was seen by the ATM early in the morning on Leggett Street withdrawing  a small amount of money--
 --the thief called someone he was talking less than a minute : said he was planning to take the earliest flight out of town tommorow and that the other person on the phone wil purchase the tickets--

 --we will start be checking the security logs of the bakery parking lot from 10:16 to 10:25  for any car that drove away--
 SELECT  license_plate
  FROM bakery_security_logs
 WHERE year= 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25
 AND activity = "exit";

 --now we have a list of all the license plates of the suspects we should cross refrence it with the list of people who have the same plate numbers and have regirstered activity   around the ATM and the airport--

 --we check for the transactions in the ATM in the morning on Leggett Street for withdrawal of a small amount of money and we get the acount number of the people who have done these transactions --
 SELECT account_number
 FROM atm_transactions
 WHERE year = 2021 AND month = 7 AND DAY = 28 AND atm_location = "Leggett Street"
 AND transaction_type = "withdraw";

 --now we should query the bank_accounts table to get the person_id of the people with the resulting acount_number from the previous queryy--
 SELECT person_id
 FROM bank_accounts
 WHERE account_number IN
        ( SELECT account_number
 FROM atm_transactions
 WHERE year = 2021 AND month = 7 AND DAY = 28 AND atm_location = "Leggett Street"
 AND transaction_type = "withdraw");

 --now we check the phone_calls table for calls that lasted less than a minute  on the sme day of the robbery--
SELECT caller,receiver,duration
FROM phone_calls
WHERE year = 2021 AND month = 7 AND day = 28 and duration < 60 ;

--we need the name of the fiftyville Regional Airport --

SELECT full_name , abbreviation
FROM airports
WHERE city = "Fiftyville";

--the result is Fiftyville Regional Airport , CSF --

--now we go to the flights table and look for the earliest flight from fifty ville on the 29 july 2021 to look for the destination airport--

SELECT  destination_airport_id
FROM flights
WHERE year = 2021 AND month = 7 AND day = 29
AND origin_airport_id IN
    (SELECT id
    FROM airports
    WHERE abbreviation = "CSF")
ORDER BY hour , minute
LIMIT 1;

--this query is to get the city name of the destination--
SELECT city
FROM airports
WHERE id IN
    (SELECT  destination_airport_id
    FROM flights
    WHERE year = 2021 AND month = 7 AND day = 29
    AND origin_airport_id IN
        (SELECT id
        FROM airports
        WHERE abbreviation = "CSF")
    ORDER BY hour , minute
    LIMIT 1);

--now we got the destination_airport_id the origin_airport_id the day of the flight and the exact time on which the flight went we can get the flight_id and from that get the list of all the passengers and their passports--
SELECT id
FROM flights
WHERE origin_airport_id IN
    (SELECT id
    FROM airports
    WHERE abbreviation = "CSF")
AND destination_airport_id IN
    (SELECT  destination_airport_id
    FROM flights
    WHERE year = 2021 AND month = 7 AND day = 29
    AND origin_airport_id IN
        (SELECT id
        FROM airports
        WHERE abbreviation = "CSF")
    ORDER BY hour , minute
    LIMIT 1)
AND day = 29 AND month = 7 AND year = 2021;


--now we get the list of passengers and their passports --
SELECT passport_number
FROM passengers
WHERE flight_id IN
        (SELECT id
    FROM flights
    WHERE origin_airport_id IN
        (SELECT id
        FROM airports
        WHERE abbreviation = "CSF")
    AND destination_airport_id IN
        (SELECT  destination_airport_id
        FROM flights
        WHERE year = 2021 AND month = 7 AND day = 29
        AND origin_airport_id IN
            (SELECT id
            FROM airports
            WHERE abbreviation = "CSF")
        ORDER BY hour , minute
        LIMIT 1)
    AND day = 29 AND month = 7 AND year = 2021);


--now we got a list of passport_number , license plates , id number and phone numbers of the suspects when we cross refrence them all we should get the identity of our thief --


SELECT name
FROM people
WHERE phone_number IN
    (SELECT caller
    FROM phone_calls
    WHERE year = 2021 AND month = 7 AND day = 28 and duration < 60 )
AND passport_number IN
    (SELECT passport_number
    FROM passengers
    WHERE flight_id IN
            (SELECT id
            FROM flights
            WHERE origin_airport_id IN
                (SELECT id
                FROM airports
                WHERE abbreviation = "CSF")
            AND destination_airport_id IN
                (SELECT  destination_airport_id
                FROM flights
                WHERE year = 2021 AND month = 7 AND day = 29
                AND origin_airport_id IN
                    (SELECT id
                    FROM airports
                    WHERE abbreviation = "CSF")
                ORDER BY hour , minute
                LIMIT 1)
            AND day = 29 AND month = 7 AND year = 2021))
AND license_plate IN
    (SELECT  license_plate
    FROM bakery_security_logs
    WHERE year= 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25
    AND activity = "exit")
AND id IN
    (SELECT person_id
    FROM bank_accounts
    WHERE account_number IN
            ( SELECT account_number
            FROM atm_transactions
            WHERE year = 2021 AND month = 7 AND DAY = 28 AND atm_location = "Leggett Street"
            AND transaction_type = "withdraw"));
-- the name of our thief is bruce --
--now to get the name of the accomplice we go to the phone_calls table and use the name of the thief the day of the crime and the duration that is less than one minute --
SELECT receiver
FROM phone_calls
WHERE caller IN
    (SELECT phone_number
    FROM people
    WHERE name = "Bruce")
AND day  = 28 and year = 2021 and month = 7 AND duration < 60;

--use the phone number to get the person name --
SELECT name
FROM people
WHERE phone_number IN
    (SELECT receiver
    FROM phone_calls
    WHERE caller IN
        (SELECT phone_number
        FROM people
        WHERE name = "Bruce")
    AND day  = 28 and year = 2021 and month = 7 AND duration < 60);