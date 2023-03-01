-- list the names of all people who starred in a movie in which Kevin Bacon also starred--
--then we get the names of all people starring in those movies

SELECT DISTINCT name
FROM people
WHERE id IN(SELECT person_id
FROM stars
WHERE movie_id IN(
--first we get the movie_id of all the movies kevin bacon starred in --
SELECT stars.movie_id
FROM people
    JOIN
    stars
    JOIN
    movies
    ON people.id = stars.person_id AND stars.movie_id = movies.id
WHERE people.name = "Kevin Bacon" AND people.birth =1958)) AND  NOT name = "Kevin Bacon" ;
