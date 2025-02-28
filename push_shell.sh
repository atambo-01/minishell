#!/bin/bash

# Set the ultimate girly prompt 🌸💖✨
PS1="\[\e[1;95m\]💖🌸✨(✿◕‿◕) Cute Bash > 💕🦄 \[\e[0m\]"

# Make terminal text mostly pink 💗
echo -e "\e[38;5;206m"  # Sets foreground text to bright pink

# Start a new Bash shell with the custom prompt
bash --rcfile <(echo "PS1='$PS1'")

