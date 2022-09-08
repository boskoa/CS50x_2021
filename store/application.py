import sqlite3
from flask import Flask, render_template, redirect, session, request
from flask_session import Session

app = Flask(__name__)

conn = sqlite3.connect("store.db")
cur = conn.cursor()

app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

@app.route("/")
def index():
    books = {k: v for (k, v) in cur.execute("SELECT * FROM books")}
    return render_template("index.html", books=books)

@app.route("/cart", methods=["GET", "POST"])
def cart():
    if "cart" not in session:
        session["cart"] = []

    if request.method == "POST":
        id = request.form.get("id")
        if id:
            session["cart"].append(id)
        return redirect("/")

    cond = [int(i) for i in session["cart"]]
    books = {}
    for i in cond:
        books[i] = list(cur.execute("SELECT title FROM books WHERE id=?", (i,)))[0][0]
    return render_template("cart.html", books=books)