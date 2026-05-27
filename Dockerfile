FROM python:3.14-slim

RUN apt-get update && apt-get install -y --no-install-recommends \
    gcc g++ rustc nodejs curl ca-certificates xz-utils \
  && rm -rf /var/lib/apt/lists/*

RUN curl https://wasmtime.dev/install.sh -sSf | bash
ENV PATH="/root/.wasmtime/bin:${PATH}"

ARG WASI_SDK_VERSION=33
RUN ARCH=$(case "$(uname -m)" in x86_64) echo "x86_64" ;; aarch64|arm64) echo "arm64" ;; esac) && \
    curl -L "https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-${WASI_SDK_VERSION}/wasi-sdk-${WASI_SDK_VERSION}.0-${ARCH}-linux.tar.gz" \
    | tar xz -C /opt/ && \
    ln -s /opt/wasi-sdk-${WASI_SDK_VERSION}.0-${ARCH}-linux /opt/wasi-sdk

RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y --default-toolchain stable --profile minimal \
    && /root/.cargo/bin/rustup target add wasm32-wasip1
ENV PATH="/root/.cargo/bin:${PATH}"

ARG JAVY_VERSION=8.1.1
RUN ARCH=$(case "$(uname -m)" in x86_64) echo "x86_64" ;; aarch64|arm64) echo "arm" ;; esac) && \
    curl -L "https://github.com/bytecodealliance/javy/releases/download/v${JAVY_VERSION}/javy-${ARCH}-linux-v${JAVY_VERSION}.gz" \
    | gunzip > /usr/local/bin/javy && chmod +x /usr/local/bin/javy

ARG PYTHON_WASM_VERSION=3.12.0
RUN curl -L "https://github.com/vmware-labs/webassembly-language-runtimes/releases/download/python%2F${PYTHON_WASM_VERSION}%2B20231211-040d5a6/python-${PYTHON_WASM_VERSION}.wasm" \
    -o /opt/python.wasm

COPY --from=ghcr.io/astral-sh/uv:latest /uv /usr/local/bin/uv

WORKDIR /app

COPY pyproject.toml uv.lock ./
RUN uv sync --frozen --no-dev

COPY . .

EXPOSE 8888

CMD ["uv", "run", "python", "main.py", "start"]
