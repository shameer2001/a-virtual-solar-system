FROM mcr.microsoft.com/devcontainers/cpp:0-ubuntu-22.04

RUN apt-get update \
        && export DEBIAN_FRONTEND=noninteractive \
        && apt-get -y install --no-install-recommends clang-format clang-tidy python3-pip openmpi-bin libopenmpi-dev \
        && apt-get autoremove -y \
        && apt-get clean -y \
        && rm -rf /var/lib/apt/lists/*

RUN pip install conan \
        && conan profile detect --force