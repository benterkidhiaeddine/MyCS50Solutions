-- list the names of all people who starred in a movie released in 2004, ordered by birth year.--
SELECT DISTINCT name
FROM people
    JOIN
    stars
    JOIN
    movies
    ON people.id = stars.person_id AND stars.movie_id = movies.id
WHERE movies.year = 2004
ORDER BY people.birth;