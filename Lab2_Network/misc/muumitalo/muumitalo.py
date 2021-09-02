from flask import Flask, Response, request, json, render_template
import hashlib

app = Flask(__name__)

@app.route('/')
def portaat():
    data = {
            'Muumi'  : 'Muumimamma',
            'answer': 'Muumipappa has gone crazy. He is blocking the door and won\'t let anyone inside unless you guess his favourite drink! I know he loves vaapukkamehu, but I guess after watching all those hacker movies he is expecting a little twist to the name of the drink. Go there and bombard him with answers until he comes out! He is located at localhost:5000/ovi/'
            }
    js = json.dumps(data)
        
    resp = Response(js, status=200, mimetype='application/json')
    return resp

@app.route('/ovi/', methods=["GET","POST"])
def ovi():
    if request.method == 'POST':
        data = request.data
        dataDict = json.loads(data)
        secret_token = dataDict['answer'].encode('utf-8')
        hashed_pass = hashlib.sha1(secret_token).hexdigest()
        print(dataDict)
        if '171108b4c4ca0983911f6af233de18879ae96bbd' == hashed_pass:
            data = {
            'Muumi'  : 'MuumiPappa',
            'answer' : 'W0nd3rful! That\'s it!'
            }
            js = json.dumps(data)
            print(request.data)
            resp = Response(js, status=200, mimetype='application/json')
            return resp
        else:
            data = {
            'Muumi'  : 'MuumiPappa',
            'answer' : 'Th4t is n0t it!'
            }
            js = json.dumps(data)
            print(request.data)
            resp = Response(js, status=404, mimetype='application/json')
            return resp            
    else:
        data = {
            'Muumi'  : 'MuumiPappa',
            'answer' : 'Wh4t 1s my f4v0ur1t3 dr1nk?'
           }
        js = json.dumps(data)
        
        resp = Response(js, status=200, mimetype='application/json')
        return resp
