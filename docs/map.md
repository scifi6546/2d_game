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
then the numeral will be a 1 instead of a 0. The numeral is determed 
using the following chart: 
```
|------|------|------|
|      |      |      |
| N/A  | 10^0 |      |
|------|------|------|
|      |block |      |
| 10^1 |needed| 10^2 |
|------|------|------|
|      |      |      |
| N/A  | 10^3 | N/A  |
|------|------|------|
```