FROM ubuntu:22.10

ENV DEBIAN_FRONTEND=noninteractive
ENV CC=clang

RUN apt update && \
    apt upgrade -y && \
    apt install -y build-essential cmake gcc clang ffmpeg