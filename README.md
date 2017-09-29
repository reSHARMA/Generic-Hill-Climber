# Generic-Hill-Climber
Generic algorithm approach to find global peak in hill climbing problem
## Problems in hill climbing solution ##
![problem](https://image.slidesharecdn.com/heuristicsearchtechniques-160509111230/95/heuristic-search-techniques-artificial-intelligence-8-638.jpg?cb=1462792952)
## Approach 1 ##
Changing the selection process 
### Parameters ###
* initial population ip
* maximum value MAX
* reproduction factor rp
* fit threshold height fsh
* fir threshold diversity fsd
* mutation rate mt
* retain rate rt
* target 
### Tuning fsh and fsd , in a complimentary fashion to ip in order to increase the population after every generation. ###
**With fsh .6 (60%) fsd .4 (40%) and ip 4 , the generation becomes extinct after first generation.**
With fsh .8 and fsd .6 , the population increases in a favourable fashion.

***
Testing phase could be seen [here](https://github.com/reSHARMA/Generic-Hill-Climber/wiki)



