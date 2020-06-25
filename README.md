# linuxconfig
```
pacman -S alacritty i3wm fish qutebrowser
```

## Browser
qutebrowser - Blinkbasert, tastaturdrevet
```
cd ~/.config && ln -s ~/git/linuxconfig/qutebrowser
cd ~/.config && ln -s ~/git/linuxconfig/lpass
```
Konfigurasjon
- quicksearch 
- Bokmerker
- Lastpass - https://www.cedric.io/2019/qutebrowser-and-lastpass
```
sudo pacman -S lastpass-cli
pip install tldextract --user
sudo pacman -S rofi
```

##Fish
```
chsh -l
chsh -s /bin/fish
```
Oppdatere completions:
```
fish_update_completions
```

##Environmentvariabler
globalt:  /etc/environment (styres av pam_env)
lokale: ~/.config/environment.d (styres av systemd)
```
cd ~/.config && ln -s ~/git/linuxconfig/environment.d
```

Globale:
```

```

##Windowmanager
i3 - tiling, tastaturdrevet
```
cd ~ && ln -s ~/git/linuxconfig/i3 .i3
```
Config
- Bytter til hjkl som retningstaster
- Alacritty som terminal


##Andre Programmer:
Filutforsker - pcmanfm
