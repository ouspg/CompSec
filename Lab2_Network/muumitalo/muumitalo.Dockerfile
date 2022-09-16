FROM python:3.9-alpine
WORKDIR /opt/muumitalo
RUN pip3 install fastapi uvicorn
COPY muumitalo.py muumitalo.py
EXPOSE 80
ENTRYPOINT python3 -m uvicorn muumitalo:app --host=0.0.0.0 --port=80