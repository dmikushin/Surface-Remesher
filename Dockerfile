FROM nvidia/cuda:12.6.1-devel-ubuntu22.04

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update && apt-get upgrade -y && apt-get install -y --no-install-recommends \
    ca-certificates \
    build-essential \
    cmake \
    ninja-build \
    libboost-all-dev \
    libeigen3-dev \
    libgmp-dev \
    libmpfr-dev \
    libopencv-dev \
    mesa-common-dev \
    libglu1-mesa-dev \
    freeglut3-dev \
    libglew-dev \
    libglfw3-dev \
    libxrandr-dev \
    libxi-dev \
    wget

# Clean up
RUN apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# Download and install CGAL
RUN wget https://github.com/CGAL/cgal/releases/download/releases%2FCGAL-5.0.2/CGAL-5.0.2.tar.xz \
    && tar -xf CGAL-5.0.2.tar.xz \
    && cd CGAL-5.0.2 \
    && cmake . \
    && make \
    && make install

# Copy the current directory contents into the container at /app
COPY . /app

# Set the working directory in the container to /app
WORKDIR /app

ENV PATH=$PATH:/usr/local/cuda/bin

# Run CMake to build the project
RUN mkdir build \
    && cd build \
    && cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CUDA_ARCHITECTURES=86 -G Ninja \
    && ninja

