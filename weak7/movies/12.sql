--list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred--
--first we get the title of the movies johony depp starred in --
SELECT  title
FROM movies
WHERE id IN
    (SELECT movie_id
    FROM stars
    WHERE person_id IN
        (SELECT id
            FROM people
            WHERE name = "Johnny Depp"
        ))
--and we get intersection with the movies   Helena Bonham Carter starred in
INTERSECT
    SELECT  title
FROM movies
WHERE id IN
    (SELECT movie_id
    FROM stars
    WHERE person_id IN
        (SELECT id
            FROM people
            WHERE name = "Helena Bonham Carter"
        ));
