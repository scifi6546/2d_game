# Map Format
How Blocks will be loaded?
--------------------------
Blocks wil be stored in files stored in blocks/{{BLOCK_NAME}}/
blocks file names will be {{BLOCK_NUMBER}}_{{BLOCK_HEIGHT}}.obj
for example: 0000_bot.obj

How Are the Numbers determined?
-------------------------------

The blocks are determined using the neighboring block heights.
If a neighboring tile has the same height type (top, mid or bot) 
then the numeral will be a 1 instead of a 0. If the block iun question 
neigboors the end of the chunk then that part is numbered with a 1. The 
numeral is determed using the following chart: 
```
|------|------|------|
|      |      |      |
| N/A  | 10^0 | N/A  |
|------|------|------|
|      |block |      |
| 10^1 |needed| 10^2 |
|------|------|------|
|      |      |      |
| N/A  | 10^3 | N/A  |
|------|------|------|
```

blocks to do:
|Block               |Not Started|Done|
|--------------------|-----------|----|
|(Rock)  0000_bot.obj | X         |    |
|(Rock)  0001_bot.obj | X         |    |
|(Rock)  0010_bot.obj | X         |    |
|(Rock)  0011_bot.obj | X         |    |
|(Rock)  0100_bot.obj | X         |    |
|(Rock)  0101_bot.obj | X         |    |
|(Rock)  0110_bot.obj | X         |    |
|(Rock)  0111_bot.obj | X         |    |
|(Rock)  1000_bot.obj | X         |    |
|(Rock)  1001_bot.obj | X         |    |
|(Rock)  1010_bot.obj | X         |    |
|(Rock)  1011_bot.obj | X         |    |
|(Rock)  1100_bot.obj | X         |    |
|(Rock)  1101_bot.obj | X         |    |
|(Rock)  1110_bot.obj | X         |    |
|(Rock)  1111_bot.obj | X         |    |
|(Grass) 0000_bot.obj | X         |    |
|(Grass) 0001_bot.obj | X         |    |
|(Grass) 0010_bot.obj | X         |    |
|(Grass) 0011_bot.obj | X         |    |
|(Grass) 0100_bot.obj | X         |    |
|(Grass) 0101_bot.obj | X         |    |
|(Grass) 0110_bot.obj | X         |    |
|(Grass) 0111_bot.obj | X         |    |
|(Grass) 1000_bot.obj | X         |    |
|(Grass) 1001_bot.obj | X         |    |
|(Grass) 1010_bot.obj | X         |    |
|(Grass) 1011_bot.obj | X         |    |
|(Grass) 1100_bot.obj | X         |    |
|(Grass) 1101_bot.obj | X         |    |
|(Grass) 1110_bot.obj | X         |    |
|(Grass) 1111_bot.obj | X         |    |

