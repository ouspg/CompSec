from fastapi import FastAPI, Request
from fastapi.responses import JSONResponse

app = FastAPI(default_response_class=JSONResponse)


@app.get('/')
def example():
    return {
        'Hello': 'World',
        'guide': 'You can modify this server skeleton to receive your CSRF results. '
                 'The server will auto-reload on save.'
    }


@app.post('/')
def post(r: Request):
    return {**r.query_params}
