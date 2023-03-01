from flask import Flask , render_template , request , redirect

app = Flask(__name__)

SPORTS = ["Football","Basketball","Friesby","Golf","Handball"]

REGISTRANTS ={}

@app.route("/")
def index():
    return render_template("index.html",sports=SPORTS)


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

    REGISTRANTS[name]=sport

    #confirm registration by rederecting to the registrants rout
    return redirect("/registrants")

@app.route("/registrants")
def registrants():
    return render_template("registrants.html",registrants=REGISTRANTS)