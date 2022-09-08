from flask import Flask, render_template, redirect, request, jsonify
import sqlite3

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():
    con = sqlite3.connect("/home/ubuntu/didagain/pset7/movies/movies.db")
    cur = con.cursor()
    cond = "%" + request.args.get("q") + "%"
    movies = cur.execute("SELECT * FROM movies WHERE title LIKE ?", (cond,)).fetchall()
    titles_list = []
    for i in movies:
        titles_list.append({"title": i[1]})
    titles = jsonify(titles_list)
    return titles