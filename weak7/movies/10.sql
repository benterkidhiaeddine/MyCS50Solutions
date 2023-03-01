--list the names of all people who have directed a movie that received a rating of at least 9.0--
SELECT DISTINCT people.name
FROM people
    JOIN
    directors
    JOIN
    movies
    JOIN ratings
    ON people.id = directors.person_id AND directors.movie_id = movies.id AND movies.id = ratings.movie_id
WHERE ratings.rating >= 9.0;