---
sidebar_position: 2
---

# Quick Start

## 1. Install dependencies
Install the following software before proceeding:
- [sampctl](https://github.com/Southclaws/sampctl): SA-MP server dependency manager, also used to compile and run the server.
- [Docker](https://docs.docker.com/get-docker/): Containerization platform used to run the server in a container.

## 2. Clone the repository
```bash
git clone https://github.com/brazucas/samp-server.git
```

## 3. Ensure project dependencies
```bash
sampctl ensure
```

## 4. Compile gamemode
```bash
sampctl build main
```

## 4. Compile packages
The SA-MP server scripts are splitted into multiple packages, you need to compile them all before running the server. This also facilitates development, as you can compile only the filterscript you are working on and reload it without restarting the server. The packages lives under the `packages` directory, you need to run the compile command for each one of them:

- Example: Compile `player_authentication` package:
```bash
cd packages/brz/player_authentication
sampctl build main
```

## 5. Start docker services
External services like database runs in docker containers, you need to start them before running the server:
```bash
docker-compose up -d
```

## 6. Run server
After compiling all packages, run the server:
```bash
sampctl run
```

Voilà! If everything goes well the server is running and you can connect to it using the SA-MP client at the IP `localhost:7777`.