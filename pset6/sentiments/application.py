from flask import Flask, redirect, render_template, request, url_for

import helpers
from analyzer import Analyzer
import os
import sys
import nltk

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "").lstrip("@")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name)

    # TODO
    if tweets == None:
        return redirect(url_for("index"))
        
    # absolute paths to lists
    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")
    
    # instantiate analyzer & tokenizer
    analyzer = Analyzer(positives, negatives)
    tokenizer = nltk.tokenize.TweetTokenizer()
    
    pos = 0.0
    neg = 0.0
    neu = 0.0
        
    for tweet in tweets:
        score = 0
        token = tokenizer.tokenize(tweet)
        for word in token:
            score += analyzer.analyze(word)
        if score > 0.0:
            pos +=1
        elif score < 0.0:
            neg +=1
        else:
            neu +=1
    
    positive, negative, neutral = pos, neg, neu

    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
