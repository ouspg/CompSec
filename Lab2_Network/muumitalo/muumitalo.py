import hashlib
import secrets

from fastapi import FastAPI, Request
from fastapi.responses import JSONResponse

app = FastAPI(default_response_class=JSONResponse)


@app.get('/')
def portaat(r: Request):
    return {
        'Muumi': 'MuumiMamma',
        'answer': 'MuumiPappa has gone crazy.'
                  ' He is blocking the door and won\'t let anyone inside unless you guess his favourite drink!'
                  ' I know he loves vaapukkamehu,'
                  ' but I guess after watching all those hacker movies'
                  ' he is expecting a little twist to the name of the drink.'
                  ' Go there and bombard him with answers until he comes out! He is located at '
                  f'{r.url_for("ovi_get")}'
    }


@app.get('/ovi')
def ovi_get():
    return {
        'Muumi': 'MuumiPappa',
        'answer': 'C4n u P05T my f4v0ur1t3 dr1nk?'
    }


@app.post('/ovi')
def ovi_post(answer: str):
    hashed_pass = hashlib.sha1(answer.encode('utf-8')).hexdigest()
    if secrets.compare_digest('171108b4c4ca0983911f6af233de18879ae96bbd', hashed_pass):
        return JSONResponse(status_code=200, content={
            'Muumi': 'MuumiPappa',
            'answer': 'W0nd3rful! That\'s it!'
        })
    else:
        return JSONResponse(status_code=404, content={
            'Muumi': 'MuumiPappa',
            'answer': 'Th4t is n0t it!'
        })
