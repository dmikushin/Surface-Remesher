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

ENV PATH=$PATH:/usr/local/cuda/bin

