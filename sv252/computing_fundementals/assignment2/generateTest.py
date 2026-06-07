import random
import subprocess
import sys
import os

# --- CONFIGURATION ---
NUM_TESTS = 25000  # Start with 1,000. Increase to 10,000 once you know it works!
OUTPUT_CPP_FILE = "GiaBaoSieuDepTrai.cpp"
TEMP_FILE = "temp_oracle_input.txt"
MAIN_EXECUTABLE = "./main"  # Change to "main.exe" if you are on standard Windows CMD

# --- ENTITY POOLS ---
# Assignment specifies 7 Straw Hats and 7 CP9 Agents
STRAW_HATS = ["Luffy", "Zoro", "Sanji", "Nami", "Usopp", "Chopper", "Franky"]
CP9_AGENTS = ["Lucci", "Kaku", "Jabra", "Blueno", "Kumadori", "Fukurou", "Kalifa"]
BUILDINGS = ["MainGate", "Courthouse", "TowerOfJustice", "BridgeOfHesitation", "BusterCallShip"]

def generate_random_battle():
    lines = []
    
    # 1. Generate Context (6 non-negative numbers)
    # turnCount, morale, alarmLevel, rescueProgress, escapeProgress, busterCallTimer
    ctx = [random.randint(0, 100) for _ in range(6)]
    lines.append(f"CONTEXT {' '.join(map(str, ctx))}")
    
    # 2. Generate Buildings (0 to 5 random buildings)
    num_buildings = random.randint(0, len(BUILDINGS))
    for b in random.sample(BUILDINGS, num_buildings):
        hp = random.randint(1, 500) # Positive numbers only
        lines.append(f"BUILDING {b} {hp}")
        
    # 3. Generate Straw Hats (0 to 7)
    num_sh = random.randint(0, len(STRAW_HATS))
    for sh in random.sample(STRAW_HATS, num_sh):
        hp, atk, def_stat, spd, eng = [random.randint(1, 300) for _ in range(5)]
        bounty = random.randint(1000, 999999999)
        lines.append(f"STRAW_HAT {sh} {hp} {atk} {def_stat} {spd} {eng} {bounty}")
        
    # 4. Generate CP9 Agents (0 to 7)
    num_cp9 = random.randint(0, len(CP9_AGENTS))
    for cp9 in random.sample(CP9_AGENTS, num_cp9):
        hp, atk, def_stat, spd, eng = [random.randint(1, 300) for _ in range(5)]
        extra = random.randint(10, 9999) 
        lines.append(f"CP9 {cp9} {hp} {atk} {def_stat} {spd} {eng} {extra}")
        
    # 5. Shuffle all lines so the parser is tested on random ordering
    random.shuffle(lines)
    
    # Join with newlines
    return "\n".join(lines) + "\n"

def get_expected_result(input_text):
    # Write the generated test to a temp file
    with open(TEMP_FILE, 'w') as f:
        f.write(input_text)
        
    # Run the compiled oracle program
    try:
        # timeout=2 ensures that if the generated input causes an infinite loop in your main,
        # the python script won't freeze forever.
        result = subprocess.run([MAIN_EXECUTABLE, TEMP_FILE], capture_output=True, text=True, timeout=2)
        
        if result.returncode != 0:
            print(f"WARNING: ./main crashed with return code {result.returncode}")
            return "CRASHED"
            
        # Return the stripped standard output
        return result.stdout.strip()
        
    except subprocess.TimeoutExpired:
        print("WARNING: ./main infinite loop detected (Timeout)")
        return "TIMEOUT"
    except FileNotFoundError:
        print(f"ERROR: Could not find '{MAIN_EXECUTABLE}'. Did you compile your main.cpp?")
        sys.exit(1)

def build_cpp_file():
    print(f"Generating {NUM_TESTS} tests. This may take a minute or two depending on your CPU...")
    
    with open(OUTPUT_CPP_FILE, 'w') as cpp:
        # Write C++ Boilerplate
        cpp.write("#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN\n")
        cpp.write("#include \"doctest.h\"\n")
        cpp.write("#include \"eniesLobby.h\"\n")
        cpp.write("#include <fstream>\n")
        cpp.write("#include <string>\n\n")
        cpp.write("using namespace std;\n\n")
        
        cpp.write("struct ExactCaseData { const char* input; const char* expected; };\n\n")
        
        cpp.write("static string runExactCase(int index, const char* input) {\n")
        cpp.write("    string filename = \"auto_test_\" + to_string(index) + \".txt\";\n")
        cpp.write("    ofstream fout(filename.c_str());\n")
        cpp.write("    fout << input;\n")
        cpp.write("    fout.close();\n")
        cpp.write("    EniesLobbyBattle battle(filename);\n")
        cpp.write("    battle.runBattle();\n")
        cpp.write("    string result = battle.getResult();\n")
        cpp.write("    remove(filename.c_str());\n")
        cpp.write("    return result;\n")
        cpp.write("}\n\n")
        
        cpp.write("static const ExactCaseData EXACT_CASES[] = {\n")
        
        # Loop and generate tests
        for i in range(NUM_TESTS):
            input_text = generate_random_battle()
            expected_output = get_expected_result(input_text)
            
            # Skip writing this case if the oracle crashed/timed out 
            # (unless you want to test if your assignment also crashes!)
            if expected_output in ["CRASHED", "TIMEOUT"]:
                continue
            
            # Write the raw string literal to C++
            cpp.write("    {\n")
            cpp.write(f'        R"__CASE__({input_text})__CASE__",\n')
            cpp.write(f'        "{expected_output}"\n')
            cpp.write("    },\n")
            
            # Print progress every 10%
            if (i + 1) % max(1, (NUM_TESTS // 10)) == 0:
                print(f"Progress: {i + 1} / {NUM_TESTS} tests generated...")
                
        cpp.write("};\n\n")
        
        # Write the Doctest loop
        cpp.write('TEST_CASE("Massive Randomized Data-Driven Tests") {\n')
        cpp.write('    int numCases = sizeof(EXACT_CASES) / sizeof(EXACT_CASES[0]);\n')
        cpp.write('    for (int i = 0; i < numCases; i++) {\n')
        cpp.write('        SUBCASE(("Randomized Case " + to_string(i)).c_str()) {\n')
        cpp.write('            string result = runExactCase(i, EXACT_CASES[i].input);\n')
        cpp.write('            CHECK(result == EXACT_CASES[i].expected);\n')
        cpp.write('        }\n')
        cpp.write('    }\n')
        cpp.write('}\n')

    # Cleanup temp file
    if os.path.exists(TEMP_FILE):
        os.remove(TEMP_FILE)
        
    print(f"\n✅ Success! Saved all tests to '{OUTPUT_CPP_FILE}'.")

if __name__ == "__main__":
    build_cpp_file()