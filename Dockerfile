FROM python:3.14-slim

RUN apt-get update && apt-get install -y --no-install-recommends \
    gcc g++ rustc nodejs curl ca-certificates xz-utils unzip \
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

RUN ARCH=$(case "$(uname -m)" in x86_64) echo "x86_64" ;; aarch64|arm64) echo "arm64" ;; esac) && \
    curl -L "https://github.com/quickjs-ng/quickjs/releases/download/v0.15.0/qjs-wasi.wasm" \
    -o /opt/quickjs.wasm && chmod +x /opt/quickjs.wasm

ARG CPYTHON_WASM_VERSION=3.14.5
RUN curl -L "https://github.com/brettcannon/cpython-wasi-build/releases/download/v${CPYTHON_WASM_VERSION}/python-${CPYTHON_WASM_VERSION}-wasi_sdk-24.zip" \
    -o /tmp/python-wasi.zip \
    && unzip -q /tmp/python-wasi.zip -d /opt/python-wasi \
    && rm /tmp/python-wasi.zip \
    && wasmtime compile -W fuel=1 -W epoch-interruption=y -W max-memory-size=536870912 /opt/python-wasi/python.wasm -o /opt/python-wasi/python.cwasm

COPY --from=ghcr.io/astral-sh/uv:latest /uv /usr/local/bin/uv

WORKDIR /app

COPY pyproject.toml uv.lock ./
RUN uv sync --frozen --no-dev

COPY . .

EXPOSE 8888

CMD ["uv", "run", "python", "main.py", "start"]
