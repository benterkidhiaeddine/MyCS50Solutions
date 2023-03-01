
from cs50 import SQL
from flask import Flask , render_template , request , redirect , 

app = Flask(__name__)

#the data base in which we store our data
db =SQL ("sqlite:///froshims.db")

SPORTS = ["Football","Basketball","Friesby","Golf","Handball"]

@app.route("/")
def index():
    return render_template("index.html",sports=SPORTS)



@app.route("/deregister",methods=["POST"])
def deregister():
    if id:
        id=request.form.get("id")
    db.execute("DELETE FROM registrants WHERE id = ?",id )
    return redirect("/registrants")

@app.route("/register",methods=["POST"])
def register():
    #validate name
    name = request.form.get("name")
    if not name:
        render_template("error.html",message="No name was given")


    #validate sport

    sport = request.form.get("sport")

    if not sport:
       return render_template("error.html",message="No sport was selected")

    if sport not in SPORTS:
       return render_template("error.html",message="No sport is not valid")

    #remember registrant

    db.execute("INSERT INTO REGISTRANTS (name,sport) VALUES(?,?)",name,sport)

    #confirm registration by rederecting to the registrants rout
    return redirect("/registrants")

@app.route("/registrants")
def registrants():
    registrants = db.execute("SELECT * FROM registrants")
    return render_template("registrants.html",registrants=registrants)