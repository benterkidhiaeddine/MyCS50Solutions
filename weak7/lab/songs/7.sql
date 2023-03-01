-- the average energy of songs that are by Drake--
SELECT AVG(energy) from songs WHERE name IN (SELECT name FROM songs WHERE artist_id IN(SELECT id from artists WHERE name = "Drake"));