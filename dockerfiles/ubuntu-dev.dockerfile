# This base docker image is hosted on the private docker registry appregistry. To pull it use `make setup` (for the 
# setup process) or `make setup-dev-base-image` to just do the setup to do with this base image.

# If you want to make changes to this base image, use ./tools/scripts/docker_build_base_dev.sh to build it manually
# after making your changes. After testing your changes you can make a MR. Once the MR has been merged, you can
# push your local image to the registry using ./tools/scripts/docker_push_base_dev.sh
#
# *** Replace TAG in .env DEV_BASE_IMAGE_TAG: apps.base.dev:TAG the hash number of the commit of the change.

FROM ubuntu:focal

### Required OpenShift Labels
LABEL   name="Simple App development Base Image" \
    maintainer="felix.clap@gmail.com" \
    vendor="ElixirTech" \
    version=1.0.0 \
    release=1.0.0 \
    summary="Base Image of for simple app development" \
    description="The base image required to build simple application."


ENV SCRIPT_LOC="."

COPY ${SCRIPT_LOC} /build

WORKDIR /build

RUN apt-get update
RUN apt-get upgrade -y --no-install-recommends

# every other dependencies that comes from ubuntu directly
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    software-properties-common \
    apt-utils \
    wget=1.20.3-1ubuntu2 \
    make=4.2.1-1.2 \
    libssl-dev \
    ninja-build=1.10.0-1build1 \
    ccache=3.7.7-1 \
    curl \
    g++-10 \
    gdb=9.2-0ubuntu1~20.04.1 \
    libgtest-dev=1.10.0-2 \
    cmake \
    clang-format \
    protobuf-compiler \
    libprotobuf-dev \
    libjsoncpp-dev \
    libcurl4-openssl-dev \
    libssl-dev \
    git \
    zip

# Logger library
RUN mkdir -p lib; cd lib; \
    git clone https://github.com/google/glog.git; cd glog; git checkout v0.5.0;\
    mkdir -p build; cd build; cmake ..; make; make install; cd ../..; rm -rf glog

# Building Amazon Lambda runtime
RUN git clone https://github.com/awslabs/aws-lambda-cpp-runtime.git; \
    cd aws-lambda-cpp-runtime; \
    mkdir build; \
    cd build; \
    cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF -DCMAKE_INSTALL_PREFIX=~/install \
    make; \
    make install; \
    cd ../..;