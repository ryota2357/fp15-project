FROM ubuntu:22.10

RUN apt update && \
    apt upgrade -y && \
    apt install -y build-essential cmake gcc ffmpeg