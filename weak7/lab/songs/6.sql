--lists the names of songs that are by Post Malone--
SELECT name FROM songs WHERE artist_id IN (SELECT id from artists WHERE name = "Post Malone");