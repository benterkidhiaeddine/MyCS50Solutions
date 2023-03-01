--list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated--
SELECT  movies.title
FROM people
    JOIN
    stars
    JOIN
    movies
    JOIN ratings
    ON people.id = stars.person_id AND stars.movie_id = movies.id AND movies.id = ratings.movie_id
WHERE people.name = "Chadwick Boseman"
ORDER BY ratings.rating DESC
LIMIT 5;
