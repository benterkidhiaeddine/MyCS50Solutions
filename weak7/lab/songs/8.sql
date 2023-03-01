--lists the names of the songs that feature other artists. a song that features others artists has "feat." in the song name--
SELECT name FROM songs WHERE name LIKE "%feat.%";