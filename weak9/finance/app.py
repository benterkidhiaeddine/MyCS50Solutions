import os
from re import match
from time import ctime
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    #get information about current holdings
    #check if user has any stocks
    user_id = session["user_id"]


    informations=db.execute("SELECT * FROM stocks WHERE (user_id = ?)",user_id)
    #add to this information the current price for each stock and the total value of the holding of said stock
    networth = 0
    #check if the user has no stocks

    if informations != []:
        for dict in informations:
            dict["price"]=lookup(dict["symbol"])["price"]
            dict["total"]=dict["price"]*dict["quantity"]
            networth += dict["total"]

    #get information about the current money of user
    funds = db.execute("SELECT cash FROM  users WHERE(id = ?)",session["user_id"])[0]["cash"]
    #net worth of user
    networth += funds



    return render_template("portfolio.html",informations=informations,funds=funds,networth=networth)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    #POST
    if request.method == "POST":
        #check if user entered a symbol
        if not request.form.get("symbol"):
            return apology("Pleas enter a symbol",400)

        #check if user specified a quanitity
        elif not request.form.get("shares")   :
            return apology("Pleas enter a valid  quantity",400)


        elif not match("^\d+$",request.form.get("shares")):
            return apology("Pleas enter a valid  quantity",400)

        elif float(request.form.get("shares"))<=0 or float(request.form.get("shares")) != int(float(request.form.get("shares"))):

            return apology("Pleas enter a valid  quantity",400)

        #check if the symbol exists
        symbol = request.form.get("symbol")

        result = lookup(symbol)

        if result == None:
            return apology("the stock you tried to look up dosen't exist",400)

        user_id = session["user_id"]
        #price of stock
        price = result["price"]
        #quantity of stocks
        quantity = float(request.form.get("shares"))
        #check if the quanity is not a negative or zero number

        #funds
        funds = db.execute("SELECT cash FROM  users WHERE(id = ?)",user_id)[0]["cash"]
        #check if transaction is possible
        if  price*quantity >funds:
            return apology("Your funds are not sufficent",400)

        #reduce money from cash in users table
        money_lost = quantity * price
        updated_funds = funds - money_lost
        db.execute("UPDATE users SET cash = ? WHERE (id = ?)",updated_funds,session["user_id"])

        #if stock for this user already exist in table update the quantity only
        current_quantity=db.execute("SELECT quantity FROM stocks  WHERE (user_id = ? AND symbol = ?)",user_id,symbol)
        if current_quantity !=[]:
            db.execute("UPDATE stocks SET quantity = ? WHERE (user_id = ? AND symbol = ?)",current_quantity[0]["quantity"] + quantity,user_id,symbol)

        #add the stock and the bought quantity
        else:
            db.execute("INSERT INTO stocks (user_id,symbol,quantity) VALUES (?,?,?)",user_id,symbol,quantity)

        #add transaction to history


        transaction_type="BUY"
        current_time = ctime()

        db.execute("INSERT INTO history (user_id,type,symbol,quantity,price,totalValue,time) VALUES(?,?,?,?,?,?,?)",user_id,transaction_type,symbol,quantity,price,money_lost,current_time)

        return redirect("/")

        #CREATE TABLE stocks (stock_id INTEGER NOT NULL,user_id INTEGER NOT NULL,symbol TEXT NOT NULL,quantity FLOAT NOT NULL DEFAULT 0.00,PRIMARY KEY (stock_id),FOREIGN KEY (user_id) REFERENCES users(id));



    #GET
    else:
        return render_template("buy.html")
    return apology("TODO")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    #get information from history database
    informations=db.execute("SELECT * FROM history WHERE (user_id = ?)",user_id)
    print(informations)


    return render_template("history.html",informations=informations)


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

        #ensure password is of the specified format





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
    #POST
    if request.method == "POST":
        symbol = request.form.get("symbol")
        #if lookup was sucessful
        if  lookup(symbol) != None:
            result = lookup(symbol)
            return render_template("quote.html",result=result)


        #lookup failed
        else:
            return apology("the stock you tried to look up dosen't exist",400)



    #GET
    else:
        return render_template("quote.html")
    return apology("TODO")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    #POST

    if request.method == "POST":
        #check for providing name
        if not request.form.get("username"):
            return apology("pleas enter a username", 400)

        #check for providing password
        elif not request.form.get("password"):
            return apology("pleas enter a password", 400)

        #check for confirming password
        elif not request.form.get("confirmation"):
            return apology("pleas confirm your password", 400)

        #check if the user confirmed the pass-word correctly
        elif  request.form.get("confirmation") != request.form.get("password"):
            return apology("pleas re-enter a matching password to the previous one", 400)

        password_pattern ="^(?=.*?[A-Z])(?=.*?[a-z])(?=.*?[0-9])(?=.*?[#?!@$%^&*-]).{8,}$"
        if match(password_pattern,request.form.get("password")) == None:
            return apology("password must have : Has minimum 8 characters in length,At least one uppercase English letter,At least one lowercase English letter,At least one digit,At least one special character",400)

        #check if the user used a name that was already taken
        usernames_dict=db.execute("SELECT username FROM users")
        usernames=[]
        for dict in usernames_dict:
            usernames.append(dict["username"])
        if request.form.get("username") in usernames:
            return apology("User was already taken , Select a diffrenet user",400)

        #add the user to the database
        username=request.form.get("username")
        db.execute("INSERT INTO users (username,hash) VALUES (?,?)",username,generate_password_hash(request.form.get("password")))

        #remember that the user is loged in
        session["user_id"]=db.execute("SELECT id FROM users WHERE (username = ?)",username )[0]["id"]

        #login the user
        return redirect("/")

    #GET
    else:
        return render_template("register.html")








@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    #POST
    if request.method == "POST":
        #check if the symbol was specified
        if not request.form.get("symbol"):
            return apology("pleas specify a symbol",403)
        #check if the quantity was specified
        elif not request.form.get("shares"):
            return apology("pleas specify the quantity",403)

        symbol=request.form.get("symbol")

        quantity = int(request.form.get("shares"))

        user_id = session["user_id"]
        #check if the specified quantity is not a negative number
        if quantity <= 0 :
            return apology("pleas enter a non zero non negative quantity",400)

        result = lookup(symbol)
        #check if the symbol exists
        if result == None:
            return apology("pleas enter a valid symbol",400)

        #check if the sufficent quantity of the stock exists to sell it
        current_quantity=db.execute("SELECT quantity FROM stocks WHERE (user_id = ? AND symbol = ?)",user_id,symbol)[0]["quantity"]
        if current_quantity < quantity:
            return apology("The number of stocks you want to sell exceeds the quantity avaiable",400)
        #update the stocks database
        new_quantity = current_quantity - quantity
        db.execute("UPDATE stocks SET quantity = ? WHERE (user_id = ? AND symbol = ?)",new_quantity,user_id,symbol)

        #update cash in the users database
        current_price = result["price"]
        money_gained = current_price * quantity
        current_cash = db.execute("SELECT cash FROM users WHERE (id = ?)",user_id)[0]["cash"]

        new_cash = current_cash + money_gained
        db.execute("UPDATE users SET cash = ? WHERE (id = ?)",new_cash,user_id)
        #get current date and time and update the transactions database : transaction_id , user_id , symbol , quantity , price , total value , time
        current_time = ctime()
        transaction_type="SELL"
        #schema for transaction table : CREATE TABLE history(transaction_id INTEGER NOT NULL,user_id INTEGER NOT NULL ,symbol TEXT NOT NULL,quantity INTEGER NOT NULL,price INTEGER NOT NULL,totalValue INTEGER NOT NULL, time TEXT NOT NULL,type TEXT NOT NULL,PRIMARY KEY(transaction_id),FOREIGN KEY(user_id) REFERENCES users(id));
        db.execute("INSERT INTO history (user_id,type,symbol,quantity,price,totalValue,time) VALUES(?,?,?,?,?,?,?)",user_id,transaction_type,symbol,quantity,current_price,money_gained,current_time)
        #redirect to portfolio page
        return redirect("/")

    #GET
    return render_template("sell.html")
