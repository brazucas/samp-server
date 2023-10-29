FROM golang as sampctl_build

ENV SAMPCTL_VERSION=1.11.3

ADD https://github.com/Southclaws/sampctl/archive/refs/tags/${SAMPCTL_VERSION}.tar.gz /sampctl/sampctl.tar.gz
RUN cd /sampctl && \
    tar -xvf sampctl.tar.gz && \
    cd sampctl-${SAMPCTL_VERSION} && \
    go build && \
    chmod a+x sampctl && \
    mv sampctl /bin/sampctl

FROM ubuntu as sampctl

COPY --from=sampctl_build /bin/sampctl /bin/sampctl

RUN dpkg --add-architecture i386 && \
    apt update && \
    apt install -y g++-multilib git ca-certificates

FROM sampctl as build

ARG SAMPCTL_GITHUB_TOKEN
ENV SAMPCTL_GITHUB_TOKEN=${SAMPCTL_GITHUB_TOKEN}

ARG MYSQL_HOST
ARG MYSQL_PORT
ARG MYSQL_USER
ARG MYSQL_PASS
ARG MYSQL_DB

ENV MYSQL_HOST=$MYSQL_HOST
ENV MYSQL_PORT=$MYSQL_PORT
ENV MYSQL_USER=$MYSQL_USER
ENV MYSQL_PASS=$MYSQL_PASS
ENV MYSQL_DB=$MYSQL_DB
ENV CI=true

COPY . /server

WORKDIR /server

RUN sampctl ensure
RUN sampctl build main

FROM build as run_tests

RUN sampctl build tests
RUN if ! sampctl run | grep -q 'ALL TESTS PASSED2'; then \
        echo "::error title=Unit Tests Failed::Check Docker build logs for more information."; \
        exit 1; \
    fi

FROM sampctl as runtime

ARG SAMPCTL_GITHUB_TOKEN
ENV SAMPCTL_GITHUB_TOKEN=${SAMPCTL_GITHUB_TOKEN}

RUN useradd -rm -d /home/brz -s /bin/bash -g root -G sudo -u 1001 brz

WORKDIR /server

COPY --from=build /server/filterscripts /server/filterscripts
COPY --from=build /server/gamemodes /server/gamemodes
COPY --from=build /server/plugins /server/plugins
COPY --from=build /server/npcmodes /server/npcmodes

COPY --from=build /server/samp03svr /server
COPY --from=build /server/announce /server
COPY --from=build /server/samp-npc /server
COPY --from=build /server/server.cfg /server
COPY --from=build /server/pawn.json /server/pawn.json

COPY --from=build /server/dependencies /server/dependencies
COPY --from=build /root/.config/sampctl /root/.config/sampctl

COPY --from=build /server/scriptfiles /server/scriptfiles

RUN find ./gamemodes -type f ! -name '*.amx' -delete
RUN find ./filterscripts -type f ! -name '*.amx' -delete
RUN find ./plugins -type f ! -name '*.so' -delete

RUN chown -R brz /server
USER brz

ENTRYPOINT [ "sampctl", "run" ]
