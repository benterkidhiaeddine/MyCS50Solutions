--titles and release years of all Harry Potter movies, in chronological order--
-- a harry potter movie is a movie whose title starts with "Harry Potter"--

SELECT title,year
  FROM movies
 WHERE title
  LIKE "Harry Potter%"
ORDER BY year;