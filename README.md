# ft_irc

because we must burn webserv to the ground

Ref link:

1. On the project ft_irc: https://ircgod.com/
2. other project https://gitlab.com/dqtvictory/ft_irc/
3. Second best ref: http://chi.cs.uchicago.edu/chirc/irc.html
4. On Protocol of Irc: How to format 1 message between server and client: `google rfc 2812`.

How to install HexChat :

```shell
flatpak remote-add --user flathub https://flathub.org/repo/flathub.flatpakrepo
flatpak install flathub io.github.Hexchat --user
flatpak run io.github.Hexchat
```

config linter :
ctrl + p in vscode then :
	ext install ms-vscode.cpptools-extension-pack
Aller dans parametre puis cocher format on save (auto format lors de la sauvegarde)

Creation de classe :
ctrl + p in vscode then :
	ext install canonicalclasscpp
Generate a class template
	macOS : ⌘ + ⌥ + C
	Linux / Windows : Ctrl + alt + C.
    
this we can implement: 
        `"ADMIN",
        "AWAY",
        "DIE",
        "INVITE",
        "JOIN",
        "KICK",
        "KILL",
        "LIST",
        "MODE",
        "MOTD",
        "NAMES",
        "NICK",
        "NOTICE",
        "OPER",
        "PART",
        "PASS",
        "PING",
        "PRIVMSG",
        "QUIT",
        "TIME",
        "TOPIC",
        "USER",
        "VERSION",
        "WHO",`


this we can ignore: 
        `"CAP",
        "CNOTICE",
        "CPRIVMSG",
        "CONNECT",
        "ENCAP",
        "ERROR",
        "HELP",
        "INFO",
        "ISON",
        "KNOCK",
        "LINKS",
        "LUSERS",
        "NAMESX",
        "PONG",
        "REHASH",
        "RULES",
        "SERVER",
        "SERVICE",
        "SERVLIST",
        "SQUERY",
        "SQUIT",
        "SETNAME",
        "SILENCE",
        "STATS",
        "SUMMON",
        "TRACE",
        "UHNAMES",
        "USERHOST",
        "USERIP",
        "USERS",
        "WALLOPS",
        "WATCH",
        "WHOIS",
        "WHOWAS",`****


Parsing result: From `KICK #new_channel thi-nguy :Speaking_English\r\n` to `std::map<std::string, std::string> parsing_map`
`Keys are:  #command #channel #username #message #params`