FROM ubuntu:18.04
COPY . /CSAPP-projects/
RUN apt-get update && apt-get install -y \
    git \
    python3 \
    openjdk-17-jdk \
    gcc \
    gdb \
    g++ \
    make \
&& rm -rf /var/lib/apt/lists/*

WORKDIR /CSAPP-projects 


# 运行这个docker，只需要执行如下命令：
#docker build -t projects .
#docker run -v C:/users/kevin/projects:/projects -it projects

# apt-get update
# apt-get install libcunit1 libcunit1-doc libcunit1-dev python3-dev  




