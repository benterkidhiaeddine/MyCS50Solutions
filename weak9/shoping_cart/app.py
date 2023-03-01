from flask import Flask , render_template, redirect , request , session
from flask_session import Session
from cs50 import SQL


#configure app

app = Flask(__name__)

#configure session

app.config["SESSION_PERMENANT"] = False
app.config["SESSION_TYPE"]="filesystem"
Session(app)

#communicate with the database

db = SQL("sqlite:///books.db")

@app.route("/")
def index():
    books = db.execute("SELECT * FROM books")
    return render_template("index.html",books=books)


@app.route("/cart",methods=["POST","GET"])
def cart():


    # we need to first make sure there is a shoping cart
    if "cart" not in session:
        session["cart"] = []

    # POST
    if request.method == "POST":
        # store the id of the book that was added into the card into id variable
        id = request.form.get("id")
        ids = db.execute("SELECT id FROM books ")
        # add that id (if it exists in our database to counter user manipulating the id)into the cart wich is a list of ids that is stored in the "cart" key in the session
        if id in ids:
            session["cart"].append(id)
            # after that is done we redirect the use to the "/cart" route but this time it will by the default GET method
            return redirect("/cart")

     # GET
     # we create a books variable (it's a list of dictionnaries who keys are id and book_title with corresponding value)
     # this books variable will get it's content from our database
    books = db.execute("SELECT * FROM books WHERE id IN (?)",session["cart"])
     #we render the template of cart.html page containing all the items in our cart with books placeholder = our books variable
    return render_template("cart.html",books=books)


