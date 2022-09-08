-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Get Crime scene reports for that day and street.
SELECT * FROM crime_scene_reports WHERE year=2020 AND month=7 AND day=28 AND street='Chamberlin Street';
-- Get interviews for that time that mention 'courthouse'.
SELECT * FROM interviews WHERE transcript LIKE '%courthouse%' AND day=28 AND month=7;
-- Find car owners that left the scene within 10 minutes.
SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year=2020 AND month=7 AND day=28 AND hour=10 AND minute BETWEEN 15 AND 26);
-- Get the account owners who withdrawed the money that morning.
SELECT name FROM people INNER JOIN bank_accounts ON id=person_id WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year=2020 AND month=7 AND day=28 AND atm_location='Fifer Street' AND transaction_type='withdraw');
-- Get the passenger names.
SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city='Fiftyville') AND year=2020 AND month=7 AND day=29 ORDER BY hour, minute LIMIT 1));
-- Get the caller name.
SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year=2020 AND month=7 AND day=28 AND duration<60);
-- Get the thief / combine data from previous 3 queries.
SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year=2020 AND month=7 AND day=28 AND hour=10 AND minute BETWEEN 15 AND 26) AND
    passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city='Fiftyville') AND year=2020 AND month=7 AND day=29 ORDER BY hour, minute LIMIT 1)) AND
    name in (SELECT name FROM people INNER JOIN bank_accounts ON id=person_id WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year=2020 AND month=7 AND day=28 AND atm_location='Fifer Street' AND transaction_type='withdraw')) AND
    name IN (SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year=2020 AND month=7 AND day=28 AND duration<60));
-- Thief's destination.
SELECT city FROM airports WHERE id=(SELECT destination_airport_id FROM flights WHERE origin_airport_id=(SELECT id FROM airports WHERE city='Fiftyville') AND year=2020 AND month=7 AND day=29 ORDER BY hour, minute LIMIT 1);
-- GET an accomplice.
SELECT name FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE caller=(SELECT phone_number FROM people WHERE name='Ernest') AND year=2020 AND month=7 AND day=28 AND duration<60);