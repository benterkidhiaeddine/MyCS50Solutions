--determine the number of movies with an IMDb rating of 10.0--


SELECT COUNT(movies.title)
FROM 
    movies
    JOIN
    ratings
    ON  movies.id = ratings.movie_id
WHERE ratings.rating = 10.0;