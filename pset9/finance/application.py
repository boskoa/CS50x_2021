import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stcks = db.execute("SELECT stock_symbol, stock_name, SUM(stock_amount) AS sum FROM purchases \
    WHERE user_id=? GROUP BY stock_name", session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])[0]["cash"]
    value = cash
    cur_prices = {}
    for i in stcks:
        value += i["sum"] * lookup(i["stock_symbol"])["price"]
        cur_prices[i["stock_symbol"]] = lookup(i["stock_symbol"])["price"]
    return render_template("index.html", stcks=stcks, cash=cash, value=value, cur_prices=cur_prices)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        stock = lookup(request.form.get("symbol"))
        qty = int(request.form.get("shares"))
        budget = db.execute("SELECT cash FROM users")[0]["cash"]
        if not stock:
            return apology("Wrong index")
        elif qty < 0:
            return apology("Not a positive number")
        elif budget < stock["price"] * qty:
            return apology("Not enough money")
        else:
            db.execute("UPDATE users SET cash=? WHERE id=?", budget - stock["price"] * qty, session["user_id"])
            db.execute("INSERT INTO purchases (user_id, stock_name, stock_symbol, stock_amount, stock_price, time) \
            VALUES (?, ?, ?, ?, ?, datetime('now'))", session["user_id"], stock["name"], stock["symbol"], qty, stock["price"])
            return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    purchases = db.execute("SELECT * FROM purchases")
    return render_template("history.html", purchases=purchases)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        smb = request.form.get("symbol")
        quote = lookup(smb)
        if quote:
            return render_template("quoted.html", quote=quote)
        else:
            return apology("Wrong index")
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        uname = request.form.get("username")
        passw = request.form.get("password")
        conf = request.form.get("confirmation")
        if not uname:
            return apology("Missing user name")
        elif not passw or passw != conf:
            return apology("Missing password or wrong reentry")
        else:
            passw_hash = generate_password_hash(passw)
            db.execute("INSERT INTO users(username, hash) VALUES(?, ?)", uname, passw_hash)
            return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    stocks = db.execute("SELECT stock_symbol, stock_name, SUM(stock_amount) AS sum FROM purchases \
    WHERE user_id=? GROUP BY stock_name", session["user_id"])
    if request.method == "POST":
        stock = request.form.get("symbol")
        num = int(request.form.get("shares"))
        budget = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])[0]["cash"]
        stock_l= lookup(stock)
        cur_price = stock_l["price"]
        if num > stocks[0]["sum"]:
            return apology("Not enough stocks")
        else:
            db.execute("INSERT INTO purchases (user_id, stock_name, stock_symbol, stock_amount, stock_price, time) \
            VALUES (?, ?, ?, ?, ?, datetime('now'))", session["user_id"], stock_l["name"], stock_l["symbol"], num * -1, cur_price)
            db.execute("UPDATE users SET cash=? WHERE id=?", budget + num * cur_price, session["user_id"])
            return redirect("/")
    else:
        return render_template("sell.html", stocks=stocks)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
