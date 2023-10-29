# samp-server

Our SA-MP server codebase.

## [![sampctl](https://img.shields.io/badge/sampctl-brz-2f2f2f.svg?style=for-the-badge)](https://github.com/pedropapa/samp-server)

This API uses sampctl to manage dependencies, compile and run the server. You can find more information about sampctl [here](https://github.com/Southclaws/sampctl).

# 👨‍💻 Contributing

Feel free to contribute to the project, whether it's fixing bugs, adding new features or improving the documentation.

## 🧞 Basic Commands

All avaliable commands in [pawn.json](pawn.json):

| Command                | Action                                               |
| :--------------------- | :--------------------------------------------------- |
| `sampctl ensure`       | Ensures all project dependencies (Only needed once)  |
| `sampctl build main`   | Build the main gamemode                              |
| `sampctl build tests`  | Build the gamemode for running tests                 |
| `sampctl run`          | Runs the server with the built gamemode              |
| `docker-compose up`    | Uses Docker for running dev environment dependencies |

## 👀 Interested in joining the team? 

Keep in touch with us at [Discord](http://discord.brz.gg).