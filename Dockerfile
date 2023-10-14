ARG QMK_CLI_VERSION=latest
FROM ghcr.io/qmk/qmk_cli:${QMK_CLI_VERSION} as base

RUN \
  apt-get update && \
  apt-get install -y --no-install-recommends sudo=* && \
  apt-get clean && \
  rm -rf /var/lib/apt/lists/*

RUN \
  useradd --shell /bin/bash --create-home --user-group nonroot && \
  echo "nonroot ALL=(root) NOPASSWD:ALL" > /etc/sudoers.d/nonroot && \
  chmod 0440 /etc/sudoers.d/nonroot

RUN install -o nonroot -g nonroot -d /code/

USER nonroot
WORKDIR /code

# --------------------------------------------------------------------------------

FROM base

ENV QMK_HOME=/home/nonroot/qmk_firmware

ARG QMK_REPOSITORY=qmk/qmk_firmware
ARG QMK_VERSION=master

RUN qmk setup --yes --home ${QMK_HOME} "${QMK_REPOSITORY}" --branch "${QMK_VERSION}"
