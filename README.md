# avr-projects
Collection of comprehensive example projects on AVR architecture

## Things to do After a Fresh Ubuntu Install
This repository is configured to use with Linux. We need to follow these steps.
### SSH Connection Steps
#### Create an ssh key
`ssh-keygen -t ed25519 -C "<my.mail@example.com>"`
#### Add to ssh agent
run ssh-agent

`eval "$(ssh-agent -s)"`

add key to ssh-agent

`ssh-add ~/.ssh/id_ed25519`

#### Add ssh key to Github
Follow these https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account

### Git Related Steps
`sudo apt install git`

installs `git`, `git-man`, and `liberror-perl`

Clone the repository

`git clone git@github.com:Sefik-Palazoglu/avr-projects.git`

## AVR related steps
### Installing `binutils-avr`
run `sudo apt install binutils-avr`

Notable tools from this package:
- `/usr/bin/avr-ar`
- `/usr/bin/avr-as`
- `/usr/bin/avr-ld`
- `/usr/bin/avr-nm`
- `/usr/bin/avr-objcopy`
- `/usr/bin/avr-objdump`
- `/usr/bin/avr-readelf`
- `/usr/bin/avr-strip`

### installing `gcc-avr`
run `sudo apt install gcc-avr`
