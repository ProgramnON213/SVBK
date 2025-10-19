import math

class Player:
    def __init__(self, current, potential):
        self.current = int(current)
        self.potential = int(potential)
        pass
    def __repr__(self):
        return (str(self.current) + " " + str(self.potential))

def main():
    n, number_of_practice, requirement = input().split()
    number_of_practice = int(number_of_practice)
    requirement = int(requirement)
    players = []
    for i in range(int(n)):
        current, potential = input().split()
        players.append(Player(current=current, potential=potential))
    numbers_of_practice_required = []
    for player in players:
        numbers_of_practice_required.append(math.ceil((requirement-player.current)/player.potential))
    numbers_of_practice_required.sort()
    ans = 0
    while number_of_practice > 0:
        if number_of_practice >= numbers_of_practice_required[ans]:
            number_of_practice -= numbers_of_practice_required[ans]
            ans += 1
        else:   break
    print(ans)

main()