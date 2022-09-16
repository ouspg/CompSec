FROM python:3.9-alpine
WORKDIR /opt/csrfserver
RUN pip3 install fastapi uvicorn
EXPOSE 80
ENTRYPOINT python3 -m uvicorn app:app --host=0.0.0.0 --port=80 --reload