FROM debian:11 AS afl_builder
WORKDIR /opt
RUN apt-get update && apt-get --no-install-recommends -y install ca-certificates build-essential
RUN echo "LLVM Toolchain and GCC" \
    && apt-get install --no-install-recommends -y \
    llvm-13 llvm-13-dev lld-13 clang-13
RUN echo "GCC dev deps" \
    && apt-get install --no-install-recommends -y \
    gcc-$(gcc --version|head -n1|sed 's/\..*//'|sed 's/.* //')-plugin-dev \
    libstdc++-$(gcc --version|head -n1|sed 's/\..*//'|sed 's/.* //')-dev
RUN echo "AFL++ Deps" \
    && apt-get install --no-install-recommends -y \
    build-essential python3-dev automake \
    cmake git flex bison libglib2.0-dev \
    libpixman-1-dev python3-setuptools cargo \
    libgtk-3-dev
RUN echo "Install AFL++" \
    && git clone https://github.com/AFLplusplus/AFLplusplus \
    && cd AFLplusplus \
    && export LLVM_CONFIG='llvm-config-13' \
    && make source-only

FROM debian:11 AS radamsa_builder
WORKDIR /opt
RUN apt-get update && apt-get --no-install-recommends -y install ca-certificates build-essential
RUN echo "Radamsa Deps" \
    && apt-get --no-install-recommends -y \
    install wget make gcc git
RUN echo "Install Radamsa" \
    && git clone https://gitlab.com/akihe/radamsa.git \
    && cd radamsa \
    && make

FROM debian:11 AS final_stage
COPY --from=afl_builder /opt/AFLplusplus /opt/AFLplusplus
COPY --from=radamsa_builder /opt/radamsa/bin/radamsa /usr/bin/radamsa
RUN apt-get update && apt-get --no-install-recommends -y install ca-certificates build-essential \
    python3-dev python3-setuptools llvm-13 llvm-13-dev lld-13 clang-13 \
    libglib2.0 valgrind \
    git cmake make wget curl nano python3-pip \
    && cd /opt/AFLplusplus  \
    && make install  \
    && rm -rf /opt/AFLplusplus \
    && ln /usr/bin/clang-13 /usr/bin/clang
RUN useradd -ms /bin/bash -G sudo -u 69 compsec \
    && mkdir -p /home/compsec/.local/bin
ENV PATH=/home/compsec/.local/bin:$PATH
USER compsec
WORKDIR /home/compsec