import sqlite3

db = sqlite3.connect("songs.db")
c = db.cursor()

c.execute("SELECT name FROM artists")
fa = c.fetchall()
for sklj in fa:
    print(sklj)