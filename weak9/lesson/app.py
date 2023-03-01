from flask import Flask , render_template, request

app =Flask(__name__)


#def index():
    #name = request.args.get("name")
    #to the left is the thing you want to use in the template
    #to the right in the value of the variable you fot from what is written in url
    #return render_template("index.html",name=name)
@app.route("/")
def index():
    return render_template("index.html")
#request.args for get requests and request.form for post requests
@app.route("/greet", methods=["POST"])
def greet():
    name = request.form.get("name","world")
    return render_template("greet.html",name=name)