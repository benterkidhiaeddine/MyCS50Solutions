from flask import Flask,redirect, session,render_template,request
from flask_session import Session

#configure app

app= Flask(__name__)

#configure session

app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

@app.route("/")
def index():
    #if the session dosen't have any vale to the name key stored , then the user will be redirected to the login route
    if not session.get("name"):
        return redirect("/login")
    #else the user is remembered and will be shown the index page
    return render_template("index.html")


@app.route("/login",methods=["POST","GET"])
def login():

    if request.method=="POST":
            #store the name of the user in the session if the web app sent a post request to the server with a name
            session["name"]=request.form.get("name")
            return redirect("/")
    #if no post request was sent simply render the login page
    return render_template("login.html")

@app.route("/logout")
def logout():
    #somehow deletes the name from session["name"], then redirect the user to the login page
    session["name"]=None
    return redirect("/login")
