import os, itertools

tiles = []
guesses = []
letters = [[] for i in range(5)]
excludes = [[] for i in range(5)]

file_dir = {
    "one.txt": 0,
    "two.txt": 1,
    "three.txt": 2,
    "four.txt": 3,
    "five.txt": 4
}

with open("results/tiles.txt") as file:
    for line in file:
        tiles.append(line.strip())

with open("texts/guesses.txt") as file:
    for line in file:
        guesses.append(line.strip())
    
os.chdir("results/letters")
for i in range(len(os.listdir())):
    f = os.listdir()[i]
    with open(f) as file:
        for line in file:
            letters[file_dir[f]].append(line.strip())

os.chdir("../excludes")
for i in range(len(os.listdir())):
    f = os.listdir()[i]
    with open(f) as file:
        for line in file:
            excludes[file_dir[f]].append(line.strip())



####################################################

gains = [[] for i in range(5)]
alphabet = "abcdefghijklmnopqrstuvwxyz"

for tile in range(5):
    t_green, t_yellow, t_grey, t_total = map(int, tiles[tile*2].split())
    t_ent = 0 if tiles[tile*2+1] == "nan" else float(tiles[tile*2+1])
    for letter in range(26):
        l_green, l_yellow, l_grey, l_total = map(int, letters[tile][letter*2].split())
        l_ent = 0 if letters[tile][letter*2+1] == "nan" else float(letters[tile][letter*2+1])
        e_green, e_yellow, e_grey, e_total = map(int, excludes[tile][letter*2].split())
        e_ent = 0 if excludes[tile][letter*2+1] == "nan" else float(excludes[tile][letter*2+1])
        
        info_gain =  t_ent-(l_ent*(l_total/t_total) + e_ent*(e_total/t_total))
        gains[tile].append((info_gain*10, alphabet[letter]))

for i in range(5):
    gains[i] = sorted(gains[i], reverse=True)

top_letters = [[] for i in range(5)]

for i in range(5):
    for j in range(5):
        print(gains[i][j][1], gains[i][j][0])
        top_letters[i].append((gains[i][j][1], gains[i][j][0]))
    print("="*30)

top_combinations = list(itertools.product(*top_letters))
top_words = []

for combi in top_combinations:
    possible_word = ""
    score = 0
    for letter in combi:
        possible_word += letter[0]
        score += letter[1]
    if possible_word in guesses:
        top_words.append((score, possible_word))

print(top_words)