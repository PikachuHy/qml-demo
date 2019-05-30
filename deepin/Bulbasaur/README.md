# ![icon](src/icon/icon40.png)Bulbasaur

TreeSize for Deepin, Quickly Scan Directory Sizes and Find Space Hogs.

![bulbasaur](https://s1.52poke.wiki/wiki/thumb/2/21/001Bulbasaur.png/300px-001Bulbasaur.png)

## Bulbapedia

**Bulbasaur** ([Japanese](https://bulbapedia.bulbagarden.net/wiki/List_of_Japanese_Pok%C3%A9mon_names): **フシギダネ** *Fushigidane*) is a dual-type [Grass](https://bulbapedia.bulbagarden.net/wiki/Grass_(type))/[Poison](https://bulbapedia.bulbagarden.net/wiki/Poison_(type)) [Pokémon](https://bulbapedia.bulbagarden.net/wiki/Pok%C3%A9mon_(species)) introduced in [Generation I](https://bulbapedia.bulbagarden.net/wiki/Generation_I).

It [evolves](https://bulbapedia.bulbagarden.net/wiki/Evolution) into [Ivysaur](https://bulbapedia.bulbagarden.net/wiki/Ivysaur_(Pok%C3%A9mon)) starting at [level](https://bulbapedia.bulbagarden.net/wiki/Level) 16, which evolves into [Venusaur](https://bulbapedia.bulbagarden.net/wiki/Venusaur_(Pok%C3%A9mon)) starting at level 32.

Along with [Charmander](https://bulbapedia.bulbagarden.net/wiki/Charmander_(Pok%C3%A9mon)) and [Squirtle](https://bulbapedia.bulbagarden.net/wiki/Squirtle_(Pok%C3%A9mon)), Bulbasaur is one of three [starter Pokémon](https://bulbapedia.bulbagarden.net/wiki/Starter_Pok%C3%A9mon) of [Kanto](https://bulbapedia.bulbagarden.net/wiki/Kanto) available at the beginning of [Pokémon Red, Green](https://bulbapedia.bulbagarden.net/wiki/Pok%C3%A9mon_Red_and_Green_Versions), [Blue](https://bulbapedia.bulbagarden.net/wiki/Pok%C3%A9mon_Red_and_Blue_Versions), [FireRed, and LeafGreen](https://bulbapedia.bulbagarden.net/wiki/Pok%C3%A9mon_FireRed_and_LeafGreen_Versions).

## Description

A disk consumption analyzing tool, which sorts folders according to their physical occupied sizes. The perfect tool to help you obtaining more disk free space, on your hard drive, usb pen drive or even on network folders (provided that they are mounted and you have access to them, of course ) 

Just like du, it counts hard links just once and the space utilized by different filesystems are not added together. 

## Contributing

### Building

install qt and qtcreator

```shell
sudo apt install qtcreator-dde
```

install dtk

```shell
sudo apt install libdtkwidget-dev
```

install cmake

```shell
sudo apt install cmake
```

build

```shell
mkdir build
cd build
cmake ..
make -j4
```

package

```shell
npm run package
```



### Commit

install node 

```shell
sudo apt install nodejs
```

install npm 

```shell
sudo apt install npm
```

install dependence

```shell
npm i
```

commit

```shell
npm run commit
```

![preview commit](https://github.com/commitizen/cz-cli/raw/master/meta/screenshots/add-commit.png)

why?

- [Conventional Commits](https://www.conventionalcommits.org)

- [commitizen/cz-cli](https://link.juejin.im/?target=https%3A%2F%2Flink.zhihu.com%2F%3Ftarget%3Dhttps%253A%2F%2Fgithub.com%2Fcommitizen%2Fcz-cli) 

## Bug

- [ ] double free or corruption (fasttop)

## Reference

- [TreeSize for Unix](http://treesize.sourceforge.net/)
- [TreeSize Free](https://www.jam-software.com/treesize_free/)
- [Folder Size](http://foldersize.sourceforge.net/)

