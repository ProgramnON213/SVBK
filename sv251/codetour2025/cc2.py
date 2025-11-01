def main():
    n = int(input())
    s = []
    for i in range(n):
        s.append(input())
    for i in range(n):
        if checkAn(s[i]):   print("YES", end=" ")
        else:   print("NO", end=" ")
        if checkBinh(s[i]):   print("YES")
        else:   print("NO")

def checkAn(s: str):
    for i in range(len(s)-1):
        if s[i] == "A" and s[i+1] == "A":   return False
    return True

def checkBinh(s: str):
    if not checkAn(s): return False
    return s[0] == "A"

main()