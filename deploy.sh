#!/usr/bin/env bash
set -euo pipefail

IMAGE="quanhua92/interview-prep"
PLATFORM="linux/amd64"

if ! git diff --quiet || ! git diff --cached --quiet; then
  echo "ERROR: Uncommitted changes detected. Commit or stash before deploying."
  git diff --stat
  git diff --cached --stat
  exit 1
fi

echo "==> Building ${IMAGE} for ${PLATFORM}..."
docker buildx build --platform "${PLATFORM}" -t "${IMAGE}:latest" --push .

echo "==> Done! Pushed ${IMAGE}:latest (${PLATFORM})"
