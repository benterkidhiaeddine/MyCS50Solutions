--list the names of all people who starred in Toy Story--
SELECT people.name
FROM people
    JOIN
    stars
    JOIN
    movies
    ON
    people.id = stars.person_id AND stars.movie_id = movies.id
WHERE movies.title = "Toy Story";