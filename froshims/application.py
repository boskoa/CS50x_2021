from flask import Flask, render_template, request, redirect
import sqlite3

app = Flask(__name__)

SPORTS = ["Dodgeball", "Flag Football", "Football", "Voleyball", "Ultimate Frisbee"]

con = sqlite3.connect("registrants.db")
cur = con.cursor()
"""
cur.execute("CREATE TABLE registrants (id INTEGER, name TEXT NOT NULL, sport TEXT NOT NULL, PRIMARY KEY(id))")
con.commit()
con.close()
"""

@app.route('/')
def index():
    return render_template("index.html", sports=SPORTS)

@app.route("/register", methods=["POST"])
def register():
    if request.form.get("name") and request.form.get("sport") in SPORTS:
        con.execute("INSERT INTO registrants(name, sport) VALUES(?, ?)", (request.form.get("name"), request.form.get("sport")))
        return redirect("/registrants")
    else:
        return render_template("failure.html")

@app.route("/registrants")
def registrants():
    return render_template("registrants.html", registrants=con.execute("SELECT name, sport FROM registrants"))