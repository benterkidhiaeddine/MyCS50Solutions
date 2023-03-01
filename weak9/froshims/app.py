from flask import Flask , render_template , request

app = Flask(__name__)

SPORTS = ["Football","Basketball","Friesby","Golf","Handball"]

@app.route("/")
def index():
    return render_template("index.html",sports=SPORTS)


@app.route("/register",methods=["POST"])
def register():
    name = request.form.get("name")

    #validate submission
    if not request.form.get("name") or request.form.get("sport") not in SPORTS:
        return render_template("faliure.html")
    else:
        return render_template("sucess.html")


    