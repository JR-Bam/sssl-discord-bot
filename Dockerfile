FROM ubuntu:latest

# Update and install dependencies
RUN apt-get update && apt-get install -y \
    libssl-dev \
    g++ \
    gdb \
    make \
    ninja-build \
    rsync \
    zip \
    cmake \
    libopus-dev \
    zlib1g-dev \
    wget \
    && rm -rf /var/lib/apt/lists/*

# Download and install the D++ package
RUN wget -O dpp.deb https://dl.dpp.dev/ && \
    dpkg -i dpp.deb && \
    rm dpp.deb

# Set the working directory
WORKDIR /usr/src/app

COPY . .

# Create the build directory and build the project in it
RUN mkdir /usr/src/app/build && \
    cmake -B /usr/src/app/build -H. -DCMAKE_BUILD_TYPE=Release && \
    cmake --build /usr/src/app/build

CMD ["/usr/src/app/build/sssl-discord-bot"]