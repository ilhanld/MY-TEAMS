# MyTeams

## About MyTeams

The goal of this project is to create a server and a CLI client for representing a simple chat application.

## TEAM MEMBER

- Maxime Coustabeay : <sub> maxime.coustabeau@epitech.eu </sub>
* Benjamin Migliani : <sub> benjamin.migliani@epitech.eu </sub>
+ Ilhan Laman-Duflot : <sub> ilhan.laman-duflot@epitech.eu </sub>


## USAGE

### PREREQUISITES MAC OS :

Make sure you have `docker` installed and running.

- Network : `docker network create -d bridge [your_network_name]`

- Terminal : `open a new terminal at the root of your repository`

- Server : `docker run -it --rm -v $(pwd):/home/project --network=[your_network_name] --name [your_server_name] -w /home/project epitechcontent/epitest-docker:latest /bin/bash`

- Terminal : `open a new terminal at the root of your repository`

- Client : `docker run -it --rm -v $(pwd):/home/project --network=[your_network_name] --name [your_client_name] -w /home/project epitechcontent/epitest-docker:latest /bin/bash`

- Ip : `docker inspect -f '{{range .NetworkSettings.Networks}}{{.IPAddress}}{{end}}' [your_server_name]`

### PREREQUISITES :

 Make sure you have done this command on your terminal:
   `export LD_LIBRARY_PATH=./libs/myteams/`

### Compilation & Run :

- Compile : `make`
- Run : `./myteams_server [port]`
- Run : `./myteams_cli [your_ip] [port]`
- Clean : `make fclean`

## COMMANDS

### HELP

- Help : do /help to get the list of available commands

### LOGIN

- Login : do /login "username" to login (quotes are required)\
`500` : Successfuly logged in.\
`501` : You are already logged in.\
`502` : Invalid Username.

### USER

- User : do /user "user_uuid" to get info about a user (quotes are required)\
`300` : Info of user.

### USERS

- Users : do /users to get the list of all users\
`350` : All informations of users.

### SEND

- Send : do /send "user_uuid" "message_body" to send a message (quotes are required)\
`400` : your message has been sent.\
`410` : you have recieve a message.

### CREATE

- Create : do /create "team_name" to create a new team (quotes are required)\
`800` : Team has been created.\
`801` : This team already exist.

### LOGOUT

- Logout : do /logout to logout\
`505` : Sucessfuly logout.

### ERROR

`100` : You must be logged in to use this command.\
`101` : User doesn't exist.

`600` : Invalid argument. See /help.\
`600` : Invalid argument. Args must be enclosed in quotes.

