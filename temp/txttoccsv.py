import fileinput

def main():
    t = []
    with fileinput.input(files=('input.txt')) as f:
        for line in f:
            t.append(line.removesuffix("\n").replace("\t", ","))
    for i in range(4):   t.pop(1)
    title = t.pop(0).removesuffix("\n")
    print(title)
    for line in t:  print(line)
    with open(title, "w", encoding="utf-8") as f:
        for line in t:
            f.write(line + "\n")


if __name__ == "__main__":
    main()