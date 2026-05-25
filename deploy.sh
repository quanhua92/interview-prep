#!/usr/bin/env bash
set -euo pipefail

IMAGE="quanhua92/interview-prep"
PLATFORMS="linux/amd64,linux/arm64"

if ! git diff --quiet || ! git diff --cached --quiet; then
  echo "ERROR: Uncommitted changes detected. Commit or stash before deploying."
  git diff --stat
  git diff --cached --stat
  exit 1
fi

echo "==> Building ${IMAGE} for platforms: ${PLATFORMS}..."
docker buildx build --platform "${PLATFORMS}" -t "${IMAGE}:latest" --push .

echo "==> Done! Pushed ${IMAGE}:latest supporting (${PLATFORMS})"
