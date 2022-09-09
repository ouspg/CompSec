FROM alpine:latest
RUN apk add qemu qemu-img qemu-system-x86_64
WORKDIR /build
COPY entrypoint.sh entrypoint.sh
ENTRYPOINT [ "/bin/sh", "entrypoint.sh" ]