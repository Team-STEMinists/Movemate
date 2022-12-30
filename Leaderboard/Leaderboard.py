import csv
from time import sleep


def add_new_entry(score):
    with open('score.csv', 'a',newline='') as csvfile: 
        csvwriter = csv.writer(csvfile) 
        csvwriter.writerows([score])

def update_leaderboard():
    rows = []
    file = open('score.csv')
    csvreader = csv.reader(file)
    for row in csvreader:
        rows.append(row)

    bicep = []
    lat = []
    for i in rows:
        if i[2] == "Bicep Curls":
            bicep.append(i)
        else:
            lat.append(i)
            
    bicep.sort(key=lambda x: x[1],reverse=True)
    lat.sort(key=lambda x: x[1],reverse=True)
    print("\nCompetitors for Bicep curls\n")
    print("|Rank|Name                |Reps                |\n"+"-"*48)
    for index,i in enumerate(bicep):
        print("| "+str(index+1)+" "*(3-len(str(index+1)))+"| "+i[0]+" "*(19-len(i[0]))+"| "+i[1]+" "*(19-len(i[1]))+"|\n"+"-"*48)
    print("\nCompetitors for Lateral Raises\n")
    print("|Rank|Name                |Reps                |\n"+"-"*48)
    for index,i in enumerate(lat):
        print("| "+str(index+1)+" "*(3-len(str(index+1)))+"| "+i[0]+" "*(19-len(i[0]))+"| "+i[1]+" "*(19-len(i[1]))+"|\n"+"-"*48)
              
    




while(1):
    update_leaderboard()
    name = input("To Enter Competition enter your name:")
    reps = input("How many could you rep:")
    exercise = input("Which Exercise did you do(1 for Bicep Curls & 2 for Lateral Raises):")
    add_new_entry([name,reps,"Bicep Curls" if exercise == "1" else "Lateral Raises"])
    update_leaderboard()
